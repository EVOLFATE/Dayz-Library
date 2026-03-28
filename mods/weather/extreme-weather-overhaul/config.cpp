// ExtremeWeatherOverhaul — config.cpp
// Registers the mod with the DayZ engine, declares script module paths,
// and sets required dependencies.

class CfgPatches
{
    class ExtremeWeatherOverhaul
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data"};
    };
};

class CfgMods
{
    class ExtremeWeatherOverhaul
    {
        dir = "ExtremeWeatherOverhaul";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        name = "Extreme Weather Overhaul";
        credits = "DayZ Library";
        author = "DayZ Library";
        authorID = "0";
        version = "1.0";
        extra = 0;
        type = "mod";

        // Load Game, World, and Mission script layers
        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class worldScriptModule
            {
                value = "";
                files[] = {"ExtremeWeatherOverhaul/scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"ExtremeWeatherOverhaul/scripts/5_Mission"};
            };
        };
    };
};
