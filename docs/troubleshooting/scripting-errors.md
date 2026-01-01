# Scripting & EnScript Errors

## Complete Guide to DayZ Scripting Issues

EnScript is the scripting language used by DayZ (based on Enfusion engine). This guide covers every common error and how to fix it.

---

## Common Syntax Errors

### Missing Semicolon

**Error Message**:
```
Error: Missing ; before '}'
Line: 45
```

**Problem**: Every statement must end with a semicolon

**Wrong**:
```cpp
void MyFunction()
{
    int value = 10
    Print(value)
}
```

**Correct**:
```cpp
void MyFunction()
{
    int value = 10;
    Print(value);
}
```

### Unmatched Brackets

**Error Message**:
```
Error: Unexpected end of file
```

**Problem**: Opening bracket without closing bracket (or vice versa)

**Wrong**:
```cpp
class MyClass
{
    void Function1()
    {
        if (condition)
        {
            DoSomething();
        // Missing closing bracket
    }
}
```

**Correct**:
```cpp
class MyClass
{
    void Function1()
    {
        if (condition)
        {
            DoSomething();
        }
    }
}
```

**Debugging Tip**: Use IDE with bracket matching (VSCode + Enforce extension)

### Incorrect String Syntax

**Error Message**:
```
Error: Unterminated string constant
```

**Wrong**:
```cpp
string message = "Hello World;  // Missing closing quote
string path = "MyMod\Data";    // Wrong slash in string
```

**Correct**:
```cpp
string message = "Hello World";
string path = "MyMod\\Data";   // Escaped backslash
```

**String Rules**:
```cpp
// Use double quotes
string text = "Correct";

// Escape special characters
string path = "C:\\Path\\To\\File";
string quote = "He said \"Hello\"";

// Use single quotes for chars
char letter = 'A';
```

---

## Class Definition Errors

### "Cannot Find Class"

**Error Message**:
```
Error: Cannot find class 'MyCustomClass'
```

**Problem**: Class not defined or not in correct scope

**Solution 1: Define the Class**
```cpp
// MyCustomClass.c
class MyCustomClass
{
    void DoSomething()
    {
        Print("Doing something");
    }
}
```

**Solution 2: Check File Structure**
```
Scripts/
└── 4_World/          // DayZ world scripts
    └── MyCustomClass.c

Config/config.cpp must reference this path
```

**Solution 3: Verify config.cpp**
```cpp
class CfgPatches
{
    class MyMod
    {
        requiredAddons[] = {"DZ_Data"};
    };
};

class CfgMods
{
    class MyMod
    {
        dir = "MyMod";
        name = "My Mod";
        type = "mod";
        dependencies[] = {"Game", "World", "Mission"};
        
        class defs
        {
            class worldScriptModule
            {
                value = "";
                files[] = {"MyMod/Scripts/4_World"};
            };
        };
    };
};
```

### "Member Already Defined"

**Error Message**:
```
Error: Member already defined in class 'PlayerBase'
```

**Problem**: Trying to define variable/function that already exists

**Wrong**:
```cpp
modded class PlayerBase
{
    int m_HealthValue;  // Already exists in base class!
}
```

**Correct**:
```cpp
modded class PlayerBase
{
    int m_MyCustomValue;  // New unique variable
    
    override void EEInit()
    {
        super.EEInit();
        m_MyCustomValue = 0;
    }
}
```

### Incorrect Modded Class Syntax

**Error Message**:
```
Error: 'modded' keyword used incorrectly
```

**Problem**: Using 'modded' for new classes or missing it for existing classes

**Wrong**:
```cpp
// Don't use 'modded' for NEW classes
modded class MyBrandNewClass
{
}

// Must use 'modded' for EXISTING classes
class PlayerBase  // Should be 'modded class'
{
}
```

**Correct**:
```cpp
// New class - no 'modded' keyword
class MyBrandNewClass
{
}

// Modifying existing class - use 'modded'
modded class PlayerBase
{
}
```

---

## Inheritance Errors

### "Cannot Inherit from Final Class"

**Error Message**:
```
Error: Cannot inherit from final class
```

**Problem**: Trying to inherit from a class marked as 'final'

**Solution**: Use composition instead of inheritance

**Wrong**:
```cpp
class MyItem extends FinalItemClass  // Can't do this
{
}
```

**Correct**:
```cpp
class MyItem extends ItemBase  // Inherit from base
{
    protected FinalItemClass m_Component;  // Use composition
}
```

### Missing Super Call

**Error Message**:
```
Runtime Error: Parent function not called
```

**Problem**: Override function without calling parent

**Wrong**:
```cpp
modded class PlayerBase
{
    override void EEInit()
    {
        // Missing super.EEInit()!
        m_MyVar = 10;
    }
}
```

**Correct**:
```cpp
modded class PlayerBase
{
    override void EEInit()
    {
        super.EEInit();  // MUST call parent!
        m_MyVar = 10;
    }
}
```

**Rule**: ALWAYS call `super.FunctionName()` when overriding

---

## Type Errors

### Type Mismatch

**Error Message**:
```
Error: Type mismatch: Cannot convert 'string' to 'int'
```

**Wrong**:
```cpp
int age = "25";  // String to int
```

**Correct**:
```cpp
int age = 25;
// Or convert:
string ageStr = "25";
int age = ageStr.ToInt();
```

**Common Conversions**:
```cpp
// String to Number
string str = "123";
int num = str.ToInt();
float fnum = str.ToFloat();

// Number to String
int num = 123;
string str = num.ToString();

// Bool to Int
bool flag = true;
int value = flag;  // 1 or 0

// Int to Bool
int value = 1;
bool flag = (value != 0);
```

### Null Reference Error

**Error Message**:
```
Runtime Error: Null pointer access
```

**Problem**: Trying to use object that is null

**Wrong**:
```cpp
PlayerBase player;
player.SetHealth(100);  // player is null!
```

**Correct**:
```cpp
PlayerBase player;
player = PlayerBase.Cast(GetGame().GetPlayer());

if (player)  // Always check for null!
{
    player.SetHealth(100);
}
```

**Always Check Before Using**:
```cpp
// Pattern 1: If check
if (myObject)
{
    myObject.DoSomething();
}

// Pattern 2: Early return
if (!myObject)
    return;

myObject.DoSomething();

// Pattern 3: Null coalescing
auto result = myObject ? myObject.GetValue() : defaultValue;
```

---

## Function Errors

### Wrong Number of Parameters

**Error Message**:
```
Error: Function expects 2 parameters, got 1
```

**Wrong**:
```cpp
void MyFunction(int a, int b)
{
    Print(a + b);
}

MyFunction(5);  // Missing second parameter!
```

**Correct**:
```cpp
MyFunction(5, 10);  // Both parameters provided
```

### Return Type Mismatch

**Error Message**:
```
Error: Function must return a value of type 'int'
```

**Wrong**:
```cpp
int GetValue()
{
    Print("Getting value");
    // Missing return statement!
}
```

**Correct**:
```cpp
int GetValue()
{
    Print("Getting value");
    return 42;  // Must return int
}
```

### Void Function Returning Value

**Error Message**:
```
Error: Void function cannot return a value
```

**Wrong**:
```cpp
void DoSomething()
{
    return 5;  // Can't return from void!
}
```

**Correct**:
```cpp
// Option 1: Change to int
int DoSomething()
{
    return 5;
}

// Option 2: Just return (no value)
void DoSomething()
{
    Print("Done");
    return;  // Early return, no value
}
```

---

## Array & Collection Errors

### Index Out of Bounds

**Error Message**:
```
Runtime Error: Array index out of bounds
```

**Wrong**:
```cpp
array<int> numbers = {1, 2, 3};
int value = numbers[5];  // Only 3 elements (0-2)!
```

**Correct**:
```cpp
array<int> numbers = {1, 2, 3};

// Always check bounds
if (index < numbers.Count())
{
    int value = numbers[index];
}
```

**Safe Array Access Patterns**:
```cpp
// Pattern 1: Check count
if (myArray.Count() > 0)
{
    auto item = myArray[0];
}

// Pattern 2: Loop with bounds
for (int i = 0; i < myArray.Count(); i++)
{
    auto item = myArray[i];
}

// Pattern 3: Foreach (safest)
foreach (auto item : myArray)
{
    // Use item
}
```

### TArray vs array Confusion

**Problem**: DayZ uses different array types

**Types**:
```cpp
// Dynamic array (use this most of the time)
array<int> dynamicArray = new array<int>;
dynamicArray.Insert(5);

// Static array (fixed size)
int staticArray[10];
staticArray[0] = 5;

// TArray (template array, less common)
TIntArray tarray = new TIntArray;
```

**Recommended**: Use `array<T>` for most cases

---

## Network Synchronization Errors

### "Variable Not Networked"

**Error Message**:
```
Warning: Variable 'myVar' not synchronized
```

**Problem**: Trying to sync variable without proper setup

**Wrong**:
```cpp
modded class MyItem extends ItemBase
{
    int m_Count;  // Not networked!
}
```

**Correct**:
```cpp
modded class MyItem extends ItemBase
{
    int m_Count;
    
    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        ctx.Write(m_Count);  // Save variable
    }
    
    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
            return false;
        
        if (!ctx.Read(m_Count))  // Load variable
            return false;
        
        return true;
    }
    
    override void OnSynchronize()
    {
        super.OnSynchronize();
        // Sync to clients if needed
    }
}
```

### RPC Errors

**Error Message**:
```
Error: RPC function not registered
```

**Wrong**:
```cpp
// Just calling RPC without registration
void MyRPC(CallType type, ParamsReadContext ctx)
{
}
```

**Correct**:
```cpp
// Register RPC IDs
enum MyRPCEnums
{
    MY_RPC_ID = 12345
}

modded class MyClass
{
    void SendRPC()
    {
        if (GetGame().IsServer())
        {
            ScriptRPC rpc = new ScriptRPC();
            rpc.Write(someData);
            rpc.Send(null, MY_RPC_ID, true, null);
        }
    }
    
    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, target, rpc_type, ctx);
        
        if (rpc_type == MY_RPC_ID)
        {
            // Handle RPC
        }
    }
}
```

---

## Memory & Resource Errors

### Memory Leak

**Problem**: Objects not properly cleaned up

**Wrong**:
```cpp
void SpawnLots()
{
    for (int i = 0; i < 1000; i++)
    {
        Object obj = GetGame().CreateObject("SomeClass", position);
        // Never cleaned up!
    }
}
```

**Correct**:
```cpp
array<Object> m_SpawnedObjects = new array<Object>;

void SpawnLots()
{
    for (int i = 0; i < 1000; i++)
    {
        Object obj = GetGame().CreateObject("SomeClass", position);
        m_SpawnedObjects.Insert(obj);
    }
}

void Cleanup()
{
    foreach (Object obj : m_SpawnedObjects)
    {
        if (obj)
            obj.Delete();  // Properly delete
    }
    m_SpawnedObjects.Clear();
}
```

### Stack Overflow

**Error Message**:
```
Runtime Error: Stack overflow
```

**Problem**: Infinite recursion

**Wrong**:
```cpp
void RecursiveFunction()
{
    RecursiveFunction();  // Calls itself forever!
}
```

**Correct**:
```cpp
void RecursiveFunction(int depth)
{
    if (depth <= 0)
        return;  // Base case
    
    RecursiveFunction(depth - 1);
}
```

---

## Common Runtime Errors

### "Cannot Cast to Type"

**Error Message**:
```
Error: Cannot cast object to 'PlayerBase'
```

**Wrong**:
```cpp
PlayerBase player = entity;  // Direct assignment
```

**Correct**:
```cpp
PlayerBase player = PlayerBase.Cast(entity);

if (player)
{
    // Safely use player
}
```

**Cast Pattern**:
```cpp
// Always use Type.Cast()
PlayerBase player = PlayerBase.Cast(someEntity);
ItemBase item = ItemBase.Cast(someObject);
WeaponBase weapon = WeaponBase.Cast(someItem);

// Check result
if (player)
{
    // Cast succeeded
}
else
{
    // Cast failed
}
```

### "Division by Zero"

**Error Message**:
```
Runtime Error: Division by zero
```

**Wrong**:
```cpp
int result = value / divisor;  // divisor might be 0
```

**Correct**:
```cpp
int result = 0;
if (divisor != 0)
{
    result = value / divisor;
}
```

---

## Debugging Tips

### Enable Detailed Logging

**Add to Scripts**:
```cpp
void DebugPrint(string message)
{
    Print("[MyMod] " + message);
}

void DebugObject(string name, Object obj)
{
    if (obj)
        DebugPrint(name + " = " + obj.GetType());
    else
        DebugPrint(name + " = NULL");
}
```

### Use Workbench Debugger

**Setup**:
```
1. Launch DayZ with: -filePatching
2. Workbench → Debug → Attach to Process
3. Select DayZ.exe
4. Set breakpoints in code
5. Step through execution
```

### Check RPT Logs

**Location**:
```
C:\Users\[YourName]\AppData\Local\DayZ\

Files:
- script.log (script errors)
- client_*.rpt (client log)
- server_*.rpt (server log)
```

### Common Log Patterns

**Script Error**:
```
SCRIPT       : Error: Member already defined
SCRIPT       : File: MyMod/Scripts/MyClass.c
SCRIPT       : Line: 45
```

**Runtime Error**:
```
SCRIPT       : Runtime Error: Null pointer access
SCRIPT       : Stack trace:
SCRIPT       :   MyClass::MyFunction
SCRIPT       :   PlayerBase::OnUpdate
```

---

## Best Practices to Avoid Errors

1. **Use IDE with syntax checking** (VSCode + Enforce)
2. **Always initialize variables**
3. **Check for null before using objects**
4. **Call super when overriding**
5. **Use proper naming conventions**
6. **Comment your code**
7. **Test incrementally**
8. **Use version control**
9. **Read vanilla code examples**
10. **Ask community when stuck**

---

## Resources

### Official Documentation
- **Bohemia Wiki**: https://community.bistudio.com/wiki/DayZ
- **Workbench Docs**: In Workbench Help menu

### Community Resources
- **DayZ Modding Discord**: Active scripters
- **Reddit r/dayzmodding**: Code help
- **YouTube Tutorials**: Visual guides

### Example Code
- **DayZ Samples**: In Workbench samples folder
- **Open Source Mods**: Learn from existing mods
- **This Repository**: Check examples/ folder

---

**Pro Tip**: Most errors can be found by reading the FULL error message and checking the exact line number in your code!

