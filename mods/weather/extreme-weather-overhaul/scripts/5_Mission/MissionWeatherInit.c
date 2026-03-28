// =============================================================================
// MissionWeatherInit.c  —  ExtremeWeatherOverhaul  (5_Mission layer)
// =============================================================================
//
// Modded MissionServer that creates and starts the ExtremeWeatherSystem and
// StormDamageSystem on server start.
//
// Placement:  ExtremeWeatherOverhaul/scripts/5_Mission/MissionWeatherInit.c
// =============================================================================

modded class MissionServer
{
    // -------------------------------------------------------------------------
    // OnInit — called once when the server mission starts
    // -------------------------------------------------------------------------
    override void OnInit()
    {
        super.OnInit();

        // Guard: these systems are server-side only.
        if (!GetGame().IsServer())
            return;

        Print("[ExtremeWeather] MissionServer.OnInit — starting Extreme Weather Overhaul.");

        // ------------------------------------------------------------------
        // 1. Hand weather control to our mod
        //    MissionWeather(false) tells the engine to use values we supply
        //    rather than its own random forecast system.
        // ------------------------------------------------------------------
        Weather weather = GetGame().GetWeather();
        if (weather)
        {
            weather.MissionWeather(false);

            // Open all parameter limits to their absolute maximums so we can
            // push the weather to full extremes when required.
            weather.GetOvercast().SetLimits(0.0, 1.0);
            weather.GetRain().SetLimits(0.0, 1.0);
            weather.GetFog().SetLimits(0.0, 1.0);

            weather.GetOvercast().SetForecastChangeLimits(0.0, 1.0);
            weather.GetRain().SetForecastChangeLimits(0.0, 1.0);
            weather.GetFog().SetForecastChangeLimits(0.0, 1.0);

            weather.GetOvercast().SetForecastTimeLimits(60, 600);
            weather.GetRain().SetForecastTimeLimits(60, 600);
            weather.GetFog().SetForecastTimeLimits(60, 600);

            // Start the server in a calm state so players experience a brief
            // peaceful window before the first random event fires.
            weather.GetOvercast().Set(0.3, 60, 0);
            weather.GetRain().Set(0.0, 60, 0);
            weather.GetFog().Set(0.05, 60, 0);
            weather.SetWindFunctionParams(0.1, 0.3, 50);

            Print("[ExtremeWeather] Weather control acquired — initial calm state set.");
        }
        else
        {
            Print("[ExtremeWeather] WARNING: Weather object unavailable at OnInit.");
        }

        // ------------------------------------------------------------------
        // 2. Create the core weather controller (sets g_ExtremeWeather)
        // ------------------------------------------------------------------
        ExtremeWeatherSystem weatherSystem = new ExtremeWeatherSystem();

        // ------------------------------------------------------------------
        // 3. Create the player damage system (sets g_StormDamage)
        // ------------------------------------------------------------------
        StormDamageSystem damageSystem = new StormDamageSystem();

        // ------------------------------------------------------------------
        // 4. Schedule Init() calls with a 30-second warm-up delay so the
        //    world is fully loaded before we start pushing weather changes.
        //    ExtremeWeatherSystem.Init() also re-applies the limit settings
        //    as a safety net.
        // ------------------------------------------------------------------
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(
            weatherSystem, "Init", 30000, false
        );
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(
            damageSystem, "Init", 31000, false  // stagger by 1 s
        );

        Print("[ExtremeWeather] Systems registered — first weather event in ~30 s.");
    }
}
