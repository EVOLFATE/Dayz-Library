// DayZ Custom Item Class Template
// This template shows how to create a custom item with basic functionality

modded class MissionServer
{
    void MissionServer()
    {
        // Your initialization code here
    }
}

// Example: Custom consumable item
class YourCustomItem : Edible_Base
{
    // Override methods to customize behavior
    override void SetActions()
    {
        super.SetActions();
        
        // Add custom actions here
        // Example: AddAction(ActionEatCustom);
    }
    
    override void OnConsume(float amount, PlayerBase consumer)
    {
        super.OnConsume(amount, consumer);
        
        // Add custom consume effects
        // Example: Healing, buffs, debuffs, etc.
        if (consumer)
        {
            // Add health
            consumer.AddHealth("", "Health", 25);
            
            // Add blood
            consumer.AddHealth("", "Blood", 50);
            
            // Add energy
            consumer.GetStatEnergy().Add(100);
            
            // Add water
            consumer.GetStatWater().Add(50);
        }
    }
}

// Example: Custom weapon with special properties
class YourCustomWeapon : Weapon_Base
{
    override void SetActions()
    {
        super.SetActions();
        
        // Add custom weapon actions
    }
    
    override void OnFire(int muzzle_index)
    {
        super.OnFire(muzzle_index);
        
        // Custom firing behavior
        // Example: Special effects, sounds, damage modifiers
    }
    
    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);
        
        // Handle attachment events
        // Example: Update weapon stats when scope attached
    }
}

// Example: Custom clothing with special effects
class YourCustomClothing : Clothing_Base
{
    // Temperature modifiers
    override float GetHeatIsolation()
    {
        return 0.7; // 0.0 to 1.0, higher = better insulation
    }
    
    // Wetness protection
    override float GetWetness()
    {
        return 0.3; // 0.0 to 1.0, lower = better protection
    }
    
    // Inventory capacity (in slots)
    override int GetNumberOfItems()
    {
        return 20; // Number of inventory slots
    }
}

// Example: Custom container
class YourCustomContainer : Container_Base
{
    override void SetActions()
    {
        super.SetActions();
        
        // Add custom container actions
    }
    
    override bool CanReceiveItemIntoCargo(EntityAI item)
    {
        super.CanReceiveItemIntoCargo(item);
        
        // Custom item restrictions
        // Example: Only allow certain item types
        // if (item.IsKindOf("Food")) return true;
        // return false;
        
        return true;
    }
}

// Example: Custom tool with durability
class YourCustomTool : ItemBase
{
    override void SetActions()
    {
        super.SetActions();
        
        // Add custom tool actions
        // AddAction(ActionRepairVehicle);
    }
    
    // Called when tool is used
    void UseTool(PlayerBase player)
    {
        // Decrease durability
        DecreaseHealth("", "", 1);
        
        // Check if tool is broken
        if (GetHealth() <= 0)
        {
            // Break the tool
            SetHealth(0);
            player.MessageStatus("Tool broke!");
        }
    }
}

// Example: Custom vehicle part
class YourCustomVehiclePart : CarScript
{
    override void EEInit()
    {
        super.EEInit();
        
        // Initialize vehicle part
    }
    
    override void OnEngineStart()
    {
        super.OnEngineStart();
        
        // Custom behavior when engine starts
    }
    
    override void OnEngineStop()
    {
        super.OnEngineStop();
        
        // Custom behavior when engine stops
    }
}

// Utility functions
class YourModUtils
{
    // Example: Spawn item near player
    static EntityAI SpawnItemNearPlayer(PlayerBase player, string itemType, float distance = 2.0)
    {
        if (!player) return null;
        
        vector position = player.GetPosition();
        vector spawn_pos = position + (player.GetDirection() * distance);
        
        EntityAI item = GetGame().CreateObject(itemType, spawn_pos, false, true);
        return item;
    }
    
    // Example: Check if player has item
    static bool PlayerHasItem(PlayerBase player, string itemType)
    {
        if (!player) return false;
        
        return player.GetInventory().FindAttachment(Class.CastTo(itemType, EntityAI)) != null;
    }
    
    // Example: Send notification to player
    static void NotifyPlayer(PlayerBase player, string message)
    {
        if (!player) return;
        
        player.MessageStatus(message);
    }
}
