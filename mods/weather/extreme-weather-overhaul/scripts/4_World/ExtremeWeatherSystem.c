// =============================================================================
// ExtremeWeatherSystem.c  —  ExtremeWeatherOverhaul  (4_World layer)
// =============================================================================
//
// Core server-side weather controller.  Every 10–45 minutes (configurable) the
// system randomly selects a new weather event from the weighted table below and
// smoothly transitions to it.  Events can also escalate:
//
//   RAIN_STORM  ---(15 % chance)---> THUNDERSTORM
//   THUNDERSTORM ---(10 % chance)---> SUPERCELL
//
// Weather event constants are exposed as a global enum so StormDamageSystem.c
// and MissionWeatherInit.c can reference them without a circular dependency.
//
// All public state is accessed through the singleton g_ExtremeWeather.
// =============================================================================

// ---------------------------------------------------------------------------
// Enum — one value per named weather event
// ---------------------------------------------------------------------------
enum EWeatherEvent
{
    CALM         = 0,
    OVERCAST     = 1,
    RAIN_STORM   = 2,
    THUNDERSTORM = 3,
    SUPERCELL    = 4,
    BLIZZARD     = 5,
    FOG_WALL     = 6,
    PERFECT_DAY  = 7,
    HEAT_WAVE    = 8
};

// ---------------------------------------------------------------------------
// Global singleton — set by ExtremeWeatherSystem on creation
// ---------------------------------------------------------------------------
ExtremeWeatherSystem g_ExtremeWeather;

// ---------------------------------------------------------------------------
// ExtremeWeatherSystem
// ---------------------------------------------------------------------------
class ExtremeWeatherSystem
{
    // ---- tunables (match weather_config.json defaults) --------------------
    protected float m_MinDurationSec          = 600;   // 10 min
    protected float m_MaxDurationSec          = 2700;  // 45 min
    protected float m_TransitionSec           = 180;   // 3 min
    protected float m_EscalationRainToThunder = 0.15;
    protected float m_EscalationThunderToSuper = 0.10;
    protected bool  m_DebugLogging            = true;

    // ---- runtime state ----------------------------------------------------
    protected EWeatherEvent m_CurrentEvent    = EWeatherEvent.CALM;
    protected bool          m_Running         = false;

    // ---- weighted event table (index → weight) ----------------------------
    // Must mirror EWeatherEvent enum order.
    protected int m_Weights[9] = {20, 20, 18, 12, 5, 5, 8, 5, 7};  // total = 100

    // ==========================================================================
    // Construction / initialisation
    // ==========================================================================

    void ExtremeWeatherSystem()
    {
        g_ExtremeWeather = this;
        DebugLog("ExtremeWeatherSystem created.");
    }

    // Called from MissionWeatherInit after the DayZ weather object is ready.
    void Init()
    {
        if (!GetGame().IsServer())
            return;

        m_Running = true;
        DebugLog("Initialised — scheduling first weather event in 30 s.");

        // Open all weather limits to their maximums so we have full control.
        Weather weather = GetGame().GetWeather();
        if (weather)
        {
            weather.MissionWeather(false);

            weather.GetOvercast().SetLimits(0.0, 1.0);
            weather.GetRain().SetLimits(0.0, 1.0);
            weather.GetFog().SetLimits(0.0, 1.0);

            weather.GetOvercast().SetForecastChangeLimits(0.0, 1.0);
            weather.GetRain().SetForecastChangeLimits(0.0, 1.0);
            weather.GetFog().SetForecastChangeLimits(0.0, 1.0);

            weather.GetOvercast().SetForecastTimeLimits(60, 600);
            weather.GetRain().SetForecastTimeLimits(60, 600);
            weather.GetFog().SetForecastTimeLimits(60, 600);
        }

        // First transition fires 30 seconds after server start.
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(
            this, "PickAndApplyNextEvent", 30000, false
        );
    }

    // ==========================================================================
    // Public API
    // ==========================================================================

    // Returns the currently active weather event so damage systems can query it.
    EWeatherEvent GetCurrentEvent()
    {
        return m_CurrentEvent;
    }

    // ==========================================================================
    // Internal — event selection
    // ==========================================================================

    // Rolls a weighted random selection across the nine event types.
    protected EWeatherEvent RollNextEvent()
    {
        int roll = Math.RandomInt(0, 100);  // 0..99
        int cumulative = 0;
        for (int i = 0; i < 9; i++)
        {
            cumulative += m_Weights[i];
            if (roll < cumulative)
                return i;
        }
        return EWeatherEvent.CALM;  // fallback
    }

    // Escalation logic: RAIN_STORM may become THUNDERSTORM;
    // THUNDERSTORM may become SUPERCELL.
    protected EWeatherEvent MaybeEscalate(EWeatherEvent ev)
    {
        if (ev == EWeatherEvent.RAIN_STORM)
        {
            if (Math.RandomFloat01() < m_EscalationRainToThunder)
            {
                DebugLog("Storm escalation: RAIN_STORM → THUNDERSTORM");
                return EWeatherEvent.THUNDERSTORM;
            }
        }
        else if (ev == EWeatherEvent.THUNDERSTORM)
        {
            if (Math.RandomFloat01() < m_EscalationThunderToSuper)
            {
                DebugLog("Storm escalation: THUNDERSTORM → SUPERCELL ⚠");
                return EWeatherEvent.SUPERCELL;
            }
        }
        return ev;
    }

    // ==========================================================================
    // Internal — event application
    // ==========================================================================

    // Main scheduled callback — picks, escalates, then applies the next event.
    void PickAndApplyNextEvent()
    {
        if (!m_Running)
            return;

        EWeatherEvent next = MaybeEscalate(RollNextEvent());
        ApplyWeatherEvent(next);

        // Schedule the next transition after a random hold duration.
        int holdMs = (int)(Math.RandomFloatInclusive(m_MinDurationSec, m_MaxDurationSec) * 1000);
        DebugLog("Next weather change in " + (holdMs / 1000) + " s.");
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(
            this, "PickAndApplyNextEvent", holdMs, false
        );
    }

    // Applies the chosen weather event by pushing values to the DayZ Weather API.
    // All Set() calls use m_TransitionSec as the transition time so changes are
    // gradual rather than instant — this feels far more natural in-game.
    protected void ApplyWeatherEvent(EWeatherEvent ev)
    {
        m_CurrentEvent = ev;

        Weather weather = GetGame().GetWeather();
        if (!weather)
        {
            Print("[ExtremeWeather] WARNING: Weather object unavailable.");
            return;
        }

        float t = m_TransitionSec;  // transition time alias for brevity

        switch (ev)
        {
            // ------------------------------------------------------------------
            // CALM — mild pleasant weather, light breeze, partly cloudy
            // ------------------------------------------------------------------
            case EWeatherEvent.CALM:
                weather.GetOvercast().Set(0.3, t, 0);
                weather.GetRain().Set(0.0, t, 0);
                weather.GetFog().Set(0.05, t, 0);
                weather.SetWindFunctionParams(0.1, 0.3, 50);
                BroadcastWeatherMessage("The weather has calmed. A welcome respite.");
                break;

            // ------------------------------------------------------------------
            // OVERCAST — heavy cloud build-up, eerie calm before the storm
            // ------------------------------------------------------------------
            case EWeatherEvent.OVERCAST:
                weather.GetOvercast().Set(0.85, t, 0);
                weather.GetRain().Set(0.0, t, 0);
                weather.GetFog().Set(0.15, t, 0);
                weather.SetWindFunctionParams(0.05, 0.15, 60);
                BroadcastWeatherMessage("Thick clouds roll in. The air grows heavy and still.");
                break;

            // ------------------------------------------------------------------
            // RAIN_STORM — moderate-to-heavy rain, reduced visibility
            // ------------------------------------------------------------------
            case EWeatherEvent.RAIN_STORM:
                weather.GetOvercast().Set(0.9, t, 0);
                weather.GetRain().Set(0.65, t, 0);
                weather.GetFog().Set(0.2, t, 0);
                weather.SetWindFunctionParams(0.3, 0.6, 40);
                BroadcastWeatherMessage("A storm is moving in. Find shelter soon.");
                break;

            // ------------------------------------------------------------------
            // THUNDERSTORM — extreme rain, high wind, fog rolls in
            // ------------------------------------------------------------------
            case EWeatherEvent.THUNDERSTORM:
                weather.GetOvercast().Set(1.0, t, 0);
                weather.GetRain().Set(0.9, t, 0);
                weather.GetFog().Set(0.35, t, 0);
                weather.SetWindFunctionParams(0.6, 1.0, 30);
                BroadcastWeatherMessage("⚡ A violent thunderstorm erupts! Lightning rends the sky!");
                break;

            // ------------------------------------------------------------------
            // SUPERCELL — DEADLY: hurricane-force wind, near-zero visibility,
            //             players take exposure damage if caught outside
            // ------------------------------------------------------------------
            case EWeatherEvent.SUPERCELL:
                weather.GetOvercast().Set(1.0, t, 0);
                weather.GetRain().Set(1.0, t, 0);
                weather.GetFog().Set(0.7, t, 0);
                weather.SetWindFunctionParams(1.5, 2.0, 20);
                BroadcastWeatherMessage(
                    "🌀 SUPERCELL WARNING — A catastrophic supercell has formed! GET INSIDE NOW!"
                );
                break;

            // ------------------------------------------------------------------
            // BLIZZARD — DEADLY: extreme fog + wind + freezing
            //            hypothermia accelerates massively for outdoor players
            // ------------------------------------------------------------------
            case EWeatherEvent.BLIZZARD:
                weather.GetOvercast().Set(1.0, t, 0);
                weather.GetRain().Set(0.4, t, 0);   // snow/sleet
                weather.GetFog().Set(0.8, t, 0);
                weather.SetWindFunctionParams(1.2, 1.8, 25);
                BroadcastWeatherMessage(
                    "❄ BLIZZARD WARNING — A deadly blizzard descends! Exposure will kill you!"
                );
                break;

            // ------------------------------------------------------------------
            // FOG_WALL — near-zero visibility, eerie silence, wind drops
            // ------------------------------------------------------------------
            case EWeatherEvent.FOG_WALL:
                weather.GetOvercast().Set(0.5, t, 0);
                weather.GetRain().Set(0.0, t, 0);
                weather.GetFog().Set(0.95, t, 0);
                weather.SetWindFunctionParams(0.0, 0.05, 80);
                BroadcastWeatherMessage(
                    "A wall of fog swallows the land. Dead silence. You can barely see your hands."
                );
                break;

            // ------------------------------------------------------------------
            // PERFECT_DAY — RARE: crystal-clear sky, gentle breeze, warm
            // ------------------------------------------------------------------
            case EWeatherEvent.PERFECT_DAY:
                weather.GetOvercast().Set(0.0, t, 0);
                weather.GetRain().Set(0.0, t, 0);
                weather.GetFog().Set(0.0, t, 0);
                weather.SetWindFunctionParams(0.05, 0.2, 100);
                BroadcastWeatherMessage(
                    "✨ The skies have cleared... a rare perfect day. Cherish it."
                );
                break;

            // ------------------------------------------------------------------
            // HEAT_WAVE — harsh sun, shimmer haze, dehydration accelerates
            // ------------------------------------------------------------------
            case EWeatherEvent.HEAT_WAVE:
                weather.GetOvercast().Set(0.05, t, 0);
                weather.GetRain().Set(0.0, t, 0);
                weather.GetFog().Set(0.02, t, 0);
                weather.SetWindFunctionParams(0.05, 0.15, 90);
                BroadcastWeatherMessage(
                    "🌡 An oppressive heat wave grips the land. Stay hydrated or die."
                );
                break;

            default:
                DebugLog("Unknown weather event value: " + ev);
                break;
        }

        Print("[ExtremeWeather] Weather event applied: " + WeatherEventName(ev));
    }

    // ==========================================================================
    // Helpers
    // ==========================================================================

    // Sends a global status message to every connected player.
    protected void BroadcastWeatherMessage(string msg)
    {
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man m : players)
        {
            PlayerBase pb = PlayerBase.Cast(m);
            if (pb)
                pb.MessageStatus(msg);
        }
    }

    // Returns a human-readable name for log output.
    string WeatherEventName(EWeatherEvent ev)
    {
        switch (ev)
        {
            case EWeatherEvent.CALM:         return "CALM";
            case EWeatherEvent.OVERCAST:     return "OVERCAST";
            case EWeatherEvent.RAIN_STORM:   return "RAIN_STORM";
            case EWeatherEvent.THUNDERSTORM: return "THUNDERSTORM";
            case EWeatherEvent.SUPERCELL:    return "SUPERCELL";
            case EWeatherEvent.BLIZZARD:     return "BLIZZARD";
            case EWeatherEvent.FOG_WALL:     return "FOG_WALL";
            case EWeatherEvent.PERFECT_DAY:  return "PERFECT_DAY";
            case EWeatherEvent.HEAT_WAVE:    return "HEAT_WAVE";
        }
        return "UNKNOWN";
    }

    // Conditional debug print — only outputs when m_DebugLogging is true.
    protected void DebugLog(string msg)
    {
        if (m_DebugLogging)
            Print("[ExtremeWeather] " + msg);
    }
}
