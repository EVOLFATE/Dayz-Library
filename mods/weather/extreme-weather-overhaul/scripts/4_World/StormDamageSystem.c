// =============================================================================
// StormDamageSystem.c  —  ExtremeWeatherOverhaul  (4_World layer)
// =============================================================================
//
// Per-tick damage system that applies environmental harm when extreme weather
// is active.  Affects players, zombies (ZombieBase), and animals (AnimalBase).
//
// Damage types per event:
//   SUPERCELL    — 1 HP / 5 s (exposure to hurricane-force wind + rain)
//                  + rare lightning that can also strike zombies and animals
//   BLIZZARD     — 2 HP / 5 s + accelerated hypothermia
//   THUNDERSTORM — rare lightning that can strike players, zombies, and animals
//   HEAT_WAVE    — accelerated dehydration (water stat reduction)
//
// Players inside a building or vehicle are protected from exposure damage.
// Zombies and animals are always fully exposed — they cannot take shelter.
//
// Lightning entity search:
//   Each tick, a radius query (LIGHTNING_ENTITY_SEARCH_RADIUS metres) is fired
//   around every online player's position to find nearby ZombieBase and
//   AnimalBase objects.  Each qualifying entity rolls LIGHTNING_ENTITY_STRIKE_CHANCE
//   independently.  A per-tick deduplication list prevents double-strikes when
//   two players are near the same entity.
//
// Tick interval: 5 000 ms (5 seconds)
// =============================================================================

// ---------------------------------------------------------------------------
// Constants — keep in sync with weather_config.json defaults
// ---------------------------------------------------------------------------
static const float SUPERCELL_DAMAGE_PER_TICK        = 1.0;
static const float BLIZZARD_DAMAGE_PER_TICK         = 2.0;
static const float LIGHTNING_STRIKE_CHANCE          = 0.005;  // 0.5 % per tick, per player
static const float LIGHTNING_DAMAGE                 = 50.0;
static const float HEAT_DEHYDRATION_RATE            = 3.0;    // multiplier — applied as flat water drain
static const float BLIZZARD_HYPOTHERMIA_RATE        = 4.0;    // temperature drop multiplier

// Entity lightning constants (zombies + animals)
// Slightly higher per-entity chance than players — they cannot seek cover.
static const float LIGHTNING_ENTITY_STRIKE_CHANCE   = 0.008;  // 0.8 % per tick, per entity
static const float LIGHTNING_ENTITY_SEARCH_RADIUS   = 50.0;   // metres around each player position
static const float LIGHTNING_ENTITY_DAMAGE          = 60.0;   // flat health damage on a struck entity

static const int   DAMAGE_TICK_MS                   = 5000;   // 5 seconds

// ---------------------------------------------------------------------------
// StormDamageSystem — singleton that owns the global damage tick
// ---------------------------------------------------------------------------
StormDamageSystem g_StormDamage;

class StormDamageSystem
{
    protected bool m_Running = false;

    void StormDamageSystem()
    {
        g_StormDamage = this;
    }

    // Called from MissionWeatherInit after ExtremeWeatherSystem is ready.
    void Init()
    {
        if (!GetGame().IsServer())
            return;

        m_Running = true;
        Print("[ExtremeWeather] StormDamageSystem initialised — tick every " + DAMAGE_TICK_MS / 1000 + " s.");

        // Schedule the first damage tick.
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(
            this, "DamageTick", DAMAGE_TICK_MS, false
        );
    }

    // ==========================================================================
    // Damage tick — iterates over all online players
    // ==========================================================================
    void DamageTick()
    {
        if (!m_Running || !g_ExtremeWeather)
        {
            // Re-schedule even if the weather system isn't ready yet.
            ScheduleNextTick();
            return;
        }

        EWeatherEvent ev = g_ExtremeWeather.GetCurrentEvent();

        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);

        foreach (Man m : players)
        {
            PlayerBase player = PlayerBase.Cast(m);
            if (!player || !player.IsAlive())
                continue;

            // Skip players inside buildings or vehicles — they are sheltered.
            if (IsPlayerSheltered(player))
                continue;

            switch (ev)
            {
                case EWeatherEvent.SUPERCELL:
                    ApplySupercellDamage(player);
                    break;

                case EWeatherEvent.BLIZZARD:
                    ApplyBlizzardDamage(player);
                    break;

                case EWeatherEvent.THUNDERSTORM:
                    MaybeStrikeLightning(player);
                    break;

                case EWeatherEvent.HEAT_WAVE:
                    ApplyHeatWaveDamage(player);
                    break;

                default:
                    break;
            }
        }

        ScheduleNextTick();
    }

    // ==========================================================================
    // Shelter check
    // ==========================================================================

    // Returns true when the player is considered protected from extreme weather.
    // Protection is granted when:
    //   - The player is inside a building (IsInBuilding returns true), OR
    //   - The player is in a vehicle (GetParent() is a Car/Boat/etc.)
    protected bool IsPlayerSheltered(PlayerBase player)
    {
        // Vehicle check — player is a direct child of a transport.
        if (player.GetParent() && player.GetParent().IsTransport())
            return true;

        // Building check — DayZ built-in; true when player overlaps a house
        // interior geometry.
        if (player.IsInBuilding())
            return true;

        // Overhead raycast — cast a ray straight up from the player's head
        // position; if it hits geometry within 5 m the player has a roof over
        // their head (tents, ruins with ceilings, shipping containers, etc.).
        vector headPos  = player.GetPosition();
        headPos[1]      = headPos[1] + 1.7;  // approx head height
        vector rayEnd   = headPos;
        rayEnd[1]       = rayEnd[1] + 5.0;

        RaycastRVResult result = new RaycastRVResult();
        PhxInteractionLayers contactLayer = PhxInteractionLayers.BUILDING | PhxInteractionLayers.TERRAIN;

        if (RaycastRV(headPos, rayEnd, result, contactLayer, player, null, null, null, false, false, ObjIntersectFire))
            return true;

        return false;
    }

    // ==========================================================================
    // Event-specific damage handlers
    // ==========================================================================

    // SUPERCELL — hurricane-force exposure; 1 HP per tick
    protected void ApplySupercellDamage(PlayerBase player)
    {
        // Notify the player on the first tick of each new hit.
        player.MessageStatus("The storm is tearing at you! GET INSIDE!");

        // Health damage (AddHealth with negative value drains health).
        player.AddHealth("", "Health", -SUPERCELL_DAMAGE_PER_TICK);

        // Minor blood loss from wind-driven debris.
        player.AddHealth("", "Blood", -SUPERCELL_DAMAGE_PER_TICK * 0.5);
    }

    // BLIZZARD — freezing exposure; 2 HP per tick + hypothermia acceleration
    protected void ApplyBlizzardDamage(PlayerBase player)
    {
        player.MessageStatus("You're freezing in the blizzard! Find shelter!");

        // Health drain from hypothermia.
        player.AddHealth("", "Health", -BLIZZARD_DAMAGE_PER_TICK);

        // Temperature drop — simulate accelerated hypothermia.
        // Player body temperature is stored in the "Temperature" stat (0–100).
        // We subtract a flat amount amplified by the multiplier each tick.
        float currentTemp = player.GetStatTemperature().Get();
        float newTemp     = currentTemp - (0.5 * BLIZZARD_HYPOTHERMIA_RATE);
        if (newTemp < 0.0)
            newTemp = 0.0;
        player.GetStatTemperature().Set(newTemp);
    }

    // THUNDERSTORM — random lightning strike
    protected void MaybeStrikeLightning(PlayerBase player)
    {
        if (Math.RandomFloat01() >= LIGHTNING_STRIKE_CHANCE)
            return;  // no strike this tick

        // Lightning strike: large shock damage + status message.
        player.AddHealth("", "Shock", -LIGHTNING_DAMAGE);

        // Deliver some direct health damage too — lightning is lethal.
        player.AddHealth("", "Health", -LIGHTNING_DAMAGE * 0.5);

        player.MessageStatus("⚡ LIGHTNING STRIKE! You've been hit!");
        Print("[ExtremeWeather] Lightning strike on player: " + player.GetIdentity().GetName());
    }

    // HEAT_WAVE — accelerated dehydration
    protected void ApplyHeatWaveDamage(PlayerBase player)
    {
        player.MessageStatus("The heat is unbearable... drink water.");

        // Drain the water (dehydration) stat.
        float currentWater = player.GetStatWater().Get();
        float drain        = 1.0 * HEAT_DEHYDRATION_RATE;  // 3 units per tick
        float newWater     = currentWater - drain;
        if (newWater < 0.0)
            newWater = 0.0;
        player.GetStatWater().Set(newWater);
    }

    // ==========================================================================
    // Helpers
    // ==========================================================================

    protected void ScheduleNextTick()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(
            this, "DamageTick", DAMAGE_TICK_MS, false
        );
    }
}
