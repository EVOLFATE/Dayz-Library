// DayZ config.cpp Template
// This template provides the basic structure for a DayZ mod configuration

class CfgPatches
{
    class YourModName
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data"};
    };
};

class CfgMods
{
    class YourModName
    {
        dir = "YourModName";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        name = "Your Mod Name";
        credits = "Your Name";
        author = "Your Name";
        authorID = "0";
        version = "1.0";
        extra = 0;
        type = "mod";
        
        dependencies[] = {"Game", "World", "Mission"};
        
        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"YourModName/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"YourModName/scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"YourModName/scripts/5_Mission"};
            };
        };
    };
};

// Example: Custom Weapon Configuration
class CfgWeapons
{
    class Rifle_Base;
    class YourCustomRifle : Rifle_Base
    {
        scope = 2;
        displayName = "Your Custom Rifle";
        descriptionShort = "A custom rifle for your mod";
        model = "\YourModName\data\weapons\your_rifle.p3d";
        weight = 3500;
        itemSize[] = {8,3};
        
        // Magazine compatibility
        magazines[] = {"Mag_STANAG_30Rnd"};
        
        // Attachment slots
        attachments[] = {"weaponOptics","weaponFlashlight","weaponMuzzle","weaponWrap"};
        
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 250;
                    healthLevels[] = {
                        {1.0, {"DZ\weapons\firearms\your_rifle\data\your_rifle.rvmat"}},
                        {0.7, {"DZ\weapons\firearms\your_rifle\data\your_rifle.rvmat"}},
                        {0.5, {"DZ\weapons\firearms\your_rifle\data\your_rifle_damage.rvmat"}},
                        {0.3, {"DZ\weapons\firearms\your_rifle\data\your_rifle_damage.rvmat"}},
                        {0.0, {"DZ\weapons\firearms\your_rifle\data\your_rifle_destruct.rvmat"}}
                    };
                };
            };
        };
        
        class Particles
        {
            class OnFire
            {
                class MuzzleFlash
                {
                    overrideParticle = "weapon_shot_fnx_01";
                };
                class ChamberSmoke
                {
                    overrideParticle = "weapon_shot_chamber_smoke";
                };
            };
            class OnBulletCasingEject
            {
                class ChamberSmokeRaise
                {
                    overrideParticle = "weapon_shot_chamber_smoke_raise";
                };
            };
        };
    };
};

// Example: Custom Clothing Configuration
class CfgVehicles
{
    class Clothing_Base;
    class YourCustomJacket : Clothing_Base
    {
        scope = 2;
        displayName = "Your Custom Jacket";
        descriptionShort = "A warm jacket";
        model = "\YourModName\data\clothes\jacket.p3d";
        inventorySlot = "Body";
        itemInfo[] = {"Clothing","Body"};
        weight = 1200;
        itemSize[] = {4,3};
        
        // Inventory capacity
        itemsCargoSize[] = {6,4};
        
        // Temperature insulation
        heatIsolation = 0.7;
        
        // Visibility
        visibilityModifier = 0.85;
        
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    healthLevels[] = {
                        {1.0, {"YourModName\data\clothes\jacket.rvmat"}},
                        {0.7, {"YourModName\data\clothes\jacket.rvmat"}},
                        {0.5, {"YourModName\data\clothes\jacket_damage.rvmat"}},
                        {0.3, {"YourModName\data\clothes\jacket_damage.rvmat"}},
                        {0.0, {"YourModName\data\clothes\jacket_destruct.rvmat"}}
                    };
                };
            };
        };
        
        class ClothingTypes
        {
            male = "\YourModName\data\clothes\jacket_m.p3d";
            female = "\YourModName\data\clothes\jacket_f.p3d";
        };
    };
    
    // Example: Custom Food Item
    class Edible_Base;
    class YourCustomFood : Edible_Base
    {
        scope = 2;
        displayName = "Your Custom Food";
        descriptionShort = "Delicious custom food";
        model = "\YourModName\data\food\custom_food.p3d";
        weight = 200;
        itemSize[] = {2,2};
        
        class Nutrition
        {
            fullnessIndex = 2;
            energy = 150;
            water = 50;
            nutritionalIndex = 80;
            toxicity = 0;
        };
        
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 50;
                };
            };
        };
    };
    
    // Example: Custom Tool
    class ItemBase;
    class YourCustomTool : ItemBase
    {
        scope = 2;
        displayName = "Your Custom Tool";
        descriptionShort = "A useful tool";
        model = "\YourModName\data\tools\custom_tool.p3d";
        weight = 400;
        itemSize[] = {2,2};
        
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                };
            };
        };
    };
};

// Example: Custom Sounds
class CfgSounds
{
    class YourCustomSound_SoundSet
    {
        soundShaders[] = {"YourCustomSound_SoundShader"};
    };
};

class CfgSoundShaders
{
    class YourCustomSound_SoundShader
    {
        samples[] = {
            {"YourModName\sounds\your_sound", 1}
        };
        volume = 1.0;
    };
};

// Example: Custom Ammo Type
class CfgAmmo
{
    class Bullet_Base;
    class YourCustomBullet : Bullet_Base
    {
        scope = 2;
        hit = 12;
        indirectHit = 0;
        indirectHitRange = 0;
        caliber = 1.0;
        deflecting = 25;
        typicalSpeed = 900;
        airFriction = -0.001;
        weight = 0.01;
    };
};

// Example: Custom Magazine
class CfgMagazines
{
    class Magazine_Base;
    class YourCustomMagazine : Magazine_Base
    {
        scope = 2;
        displayName = "Your Custom Magazine";
        descriptionShort = "30 round magazine";
        model = "\YourModName\data\magazines\custom_mag.p3d";
        weight = 200;
        itemSize[] = {2,2};
        count = 30;
        ammo = "YourCustomBullet";
    };
};
