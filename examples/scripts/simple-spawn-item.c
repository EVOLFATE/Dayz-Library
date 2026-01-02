// Simple Item Spawner Example
// This script shows how to spawn items at specific locations

class SimpleItemSpawner
{
    // Spawn a single item at a position
    static EntityAI SpawnItem(string itemType, vector position)
    {
        // Validate position
        if (position == "0 0 0")
        {
            Print("[ItemSpawner] ERROR: Invalid spawn position");
            return null;
        }
        
        // Create the item
        EntityAI item = GetGame().CreateObject(itemType, position, false, true);
        
        if (item)
        {
            Print("[ItemSpawner] Spawned " + itemType + " at " + position.ToString());
            return item;
        }
        else
        {
            Print("[ItemSpawner] ERROR: Failed to spawn " + itemType);
            return null;
        }
    }
    
    // Spawn item with random rotation
    static EntityAI SpawnItemRandomRotation(string itemType, vector position)
    {
        EntityAI item = SpawnItem(itemType, position);
        
        if (item)
        {
            // Set random rotation
            vector rotation = Vector(0, Math.RandomFloat(0, 360), 0);
            item.SetOrientation(rotation);
        }
        
        return item;
    }
    
    // Spawn item near a player
    static EntityAI SpawnItemNearPlayer(PlayerBase player, string itemType, float distance = 2.0)
    {
        if (!player)
        {
            Print("[ItemSpawner] ERROR: Invalid player");
            return null;
        }
        
        // Calculate spawn position in front of player
        vector playerPos = player.GetPosition();
        vector playerDir = player.GetDirection();
        vector spawnPos = playerPos + (playerDir * distance);
        
        // Make sure item spawns on the ground
        spawnPos[1] = GetGame().SurfaceY(spawnPos[0], spawnPos[2]);
        
        return SpawnItemRandomRotation(itemType, spawnPos);
    }
    
    // Spawn multiple items in a circle
    static array<EntityAI> SpawnItemsInCircle(string itemType, vector center, float radius, int count)
    {
        array<EntityAI> items = new array<EntityAI>;
        
        float angleStep = 360.0 / count;
        
        for (int i = 0; i < count; i++)
        {
            float angle = i * angleStep;
            float radians = angle * Math.DEG2RAD;
            
            vector offset = Vector(
                Math.Cos(radians) * radius,
                0,
                Math.Sin(radians) * radius
            );
            
            vector spawnPos = center + offset;
            spawnPos[1] = GetGame().SurfaceY(spawnPos[0], spawnPos[2]);
            
            EntityAI item = SpawnItemRandomRotation(itemType, spawnPos);
            if (item)
            {
                items.Insert(item);
            }
        }
        
        Print("[ItemSpawner] Spawned " + items.Count() + " items in circle");
        return items;
    }
    
    // Spawn item with specific health/quantity
    static EntityAI SpawnItemWithHealth(string itemType, vector position, float health)
    {
        EntityAI item = SpawnItem(itemType, position);
        
        if (item)
        {
            item.SetHealth("", "", health);
            Print("[ItemSpawner] Set item health to " + health);
        }
        
        return item;
    }
    
    // Spawn container with items inside
    static EntityAI SpawnContainerWithItems(string containerType, vector position, array<string> itemsToAdd)
    {
        EntityAI container = SpawnItem(containerType, position);
        
        if (container)
        {
            foreach (string itemType : itemsToAdd)
            {
                EntityAI item = container.GetInventory().CreateInInventory(itemType);
                if (item)
                {
                    Print("[ItemSpawner] Added " + itemType + " to container");
                }
            }
        }
        
        return container;
    }
}

// Example usage in your mission or mod:
/*
modded class MissionServer
{
    void MissionServer()
    {
        // Example 1: Spawn single item
        vector pos1 = "7500 0 5500";
        pos1[1] = GetGame().SurfaceY(pos1[0], pos1[2]);
        SimpleItemSpawner.SpawnItem("AKM", pos1);
        
        // Example 2: Spawn items in circle
        vector centerPos = "7600 0 5600";
        centerPos[1] = GetGame().SurfaceY(centerPos[0], centerPos[2]);
        SimpleItemSpawner.SpawnItemsInCircle("Apple", centerPos, 5.0, 8);
        
        // Example 3: Spawn container with loot
        vector pos3 = "7700 0 5700";
        pos3[1] = GetGame().SurfaceY(pos3[0], pos3[2]);
        array<string> loot = {"Rag", "Bandage", "PainkillerTablets", "Morphine"};
        SimpleItemSpawner.SpawnContainerWithItems("MedicalBox", pos3, loot);
    }
    
    override void PlayerConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.PlayerConnect(player, identity);
        
        // Example 4: Give player a welcome gift
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GiveWelcomeGift, 1000, false, player);
    }
    
    void GiveWelcomeGift(PlayerBase player)
    {
        if (player)
        {
            SimpleItemSpawner.SpawnItemNearPlayer(player, "WaterBottle", 1.5);
            SimpleItemSpawner.SpawnItemNearPlayer(player, "Apple", 1.5);
            player.MessageStatus("Welcome! Here's a small gift to get started.");
        }
    }
}
*/
