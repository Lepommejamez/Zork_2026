#include <iostream>
#include <string>
#include <vector>

using namespace std;

// =====================================================================
// Items
// =====================================================================

class Item
{
public:
    string name;
    string description;
    string pickupText;
    string useText;

    Item(const string& itemName, const string& itemDescription)
    {
        name = itemName;
        description = itemDescription;
    }

    virtual ~Item() {}

    virtual void Use()
    {
        if (useText != "")
        {
            cout << useText << endl;
        }
        else
        {
            cout << "Nothing happens." << endl;
        }
    }

    virtual void Inspect() const
    {
        cout << description << endl;
    }
};

class Weapon : public Item
{
public:
    int damage;

    Weapon(const string& itemName, const string& itemDescription, int itemDamage)
        : Item(itemName, itemDescription)
    {
        damage = itemDamage;
    }

    void Use() override
    {
        cout << "You swing the " << name << "." << endl;
    }
};

class Container : public Item
{
public:
    vector<Item*> items;

    Container(const string& itemName, const string& itemDescription)
        : Item(itemName, itemDescription)
    {
    }

    void Use() override
    {
        cout << "You open the " << name << "." << endl;

        if (items.empty())
        {
            cout << "It is empty." << endl;
        }
        else
        {
            cout << "Inside you find:" << endl;

            for (const Item* item : items)
            {
                cout << "- " << item->name << endl;
            }
        }
    }
};

class GenericItem : public Item
{
public:
    GenericItem(const string& itemName, const string& itemDescription)
        : Item(itemName, itemDescription)
    {
    }

    void Use() override
    {
        cout << "You use the " << name << "." << endl;
    }
};

// =====================================================================
// Room
// =====================================================================

class Room
{
public:
    string name;
    string description;

    Room* north = nullptr;
    Room* south = nullptr;
    Room* east  = nullptr;
    Room* west  = nullptr;

    vector<Item*> items;
};

// =====================================================================
// Display helpers
// =====================================================================

void ShowRoom(const Room* room)
{
    cout << endl;
    cout << "=== " << room->name << " ===" << endl;
    cout << room->description << endl;
    cout << endl;

    cout << "Exits: ";
    if (room->north != nullptr) cout << "north ";
    if (room->south != nullptr) cout << "south ";
    if (room->east  != nullptr) cout << "east ";
    if (room->west  != nullptr) cout << "west ";
    cout << endl;
}

void ShowHelp()
{
    cout << endl;
    cout << "Available commands:" << endl;
    cout << "  - north / south / east / west" << endl;
    cout << "  - look" << endl;
    cout << "  - inspect" << endl;
    cout << "  - pick up <item>" << endl;
    cout << "  - drop <item>" << endl;
    cout << "  - put <item> in <container>" << endl;
    cout << "  - take <item> from <container>" << endl;
    cout << "  - equip <item>" << endl;
    cout << "  - inventory" << endl;
    cout << "  - help" << endl;
    cout << "  - quit" << endl;
    cout << endl;
}

// =====================================================================
// Player
// =====================================================================

struct Player
{
    vector<Item*> inventory;
    Weapon* equippedWeapon = nullptr;
};

// =====================================================================
// Helpers
// =====================================================================

// Finds an item by name, removes it from the vector, and returns it.
// Returns nullptr if not found.
Item* TakeItemByName(vector<Item*>& items, const string& itemName)
{
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        if ((*it)->name == itemName)
        {
            Item* found = *it;
            items.erase(it);
            return found;
        }
    }
    return nullptr;
}

void ShowInventory(const Player& player)
{
    if (player.inventory.empty())
    {
        cout << "Your inventory is empty." << endl;
        return;
    }

    cout << "You are carrying:" << endl;
    for (const Item* item : player.inventory)
    {
        cout << "  - " << item->name;

        if (player.equippedWeapon == item)
            cout << " (equipped)";

        cout << endl;
    }
}

// Searches the room and player inventory for a Container with the given name.
// Returns nullptr if not found or if the item found is not a Container.
Container* FindContainer(const string& containerName, Room* room, Player& player)
{
    // Check room items first
    for (Item* item : room->items)
    {
        if (item->name == containerName)
            return dynamic_cast<Container*>(item);
    }

    // Then check player inventory
    for (Item* item : player.inventory)
    {
        if (item->name == containerName)
            return dynamic_cast<Container*>(item);
    }

    return nullptr;
}

// =====================================================================
// Main
// =====================================================================

int main()
{
    // -----------------------------------------------------------------
    // Items
    // -----------------------------------------------------------------

    // Kitchen items
    Weapon      knife      ("knife",        "A rusty kitchen knife. Still sharp.",       4);
    GenericItem canOfBeans ("can of beans", "A dented tin of beans. Probably fine.");
    Container   cupboard   ("cupboard",     "A wooden cupboard, slightly ajar.");
    GenericItem oldRecipe  ("old recipe",   "A handwritten recipe, barely legible.");

    // Old recipe sits inside the cupboard
    cupboard.items.push_back(&oldRecipe);

    // Living room items
    GenericItem tvRemote  ("TV remote",  "Dead batteries. Of course.");
    GenericItem newspaper ("newspaper",  "Dated three years ago. Yellowed at the edges.");

    // Garage items
    Container   toolbox   ("toolbox",   "A heavy red metal toolbox.");
    Weapon      wrench    ("wrench",    "A solid steel wrench. Could do some damage.", 6);
    GenericItem oilCan    ("oil can",   "Half-full of motor oil. Smells awful.");

    // Wrench sits inside the toolbox
    toolbox.items.push_back(&wrench);

    // Outside items
    GenericItem rock      ("rock",        "A fist-sized rock. Satisfyingly heavy.");
    GenericItem brokenKey ("broken key",  "Half a key. Useless on its own.");

    // -----------------------------------------------------------------
    // Rooms
    // -----------------------------------------------------------------

    Room kitchen;
    kitchen.name        = "Kitchen";
    kitchen.description = "A messy kitchen. Something smells burnt and the sink is full.";
    kitchen.items.push_back(&knife);
    kitchen.items.push_back(&canOfBeans);
    kitchen.items.push_back(&cupboard);

    Room livingRoom;
    livingRoom.name        = "Living Room";
    livingRoom.description = "A dusty living room. An old TV sits dead in the corner.";
    livingRoom.items.push_back(&tvRemote);
    livingRoom.items.push_back(&newspaper);

    Room garage;
    garage.name        = "Garage";
    garage.description = "A dark garage. Oil stains cover the concrete floor.";
    garage.items.push_back(&toolbox);
    garage.items.push_back(&oilCan);

    Room outside;
    outside.name        = "Outside";
    outside.description = "You step outside. The sun is blinding after the gloom indoors.";
    outside.items.push_back(&rock);
    outside.items.push_back(&brokenKey);

    // -----------------------------------------------------------------
    // Connect rooms
    // -----------------------------------------------------------------

    kitchen.west    = &livingRoom;
    kitchen.south   = &garage;

    livingRoom.east  = &kitchen;
    livingRoom.north = &outside;

    garage.north    = &kitchen;

    outside.south   = &livingRoom;

    // -----------------------------------------------------------------
    // Game loop
    // -----------------------------------------------------------------

    Room* currentRoom = &kitchen;
    Player player;
    ShowRoom(currentRoom);

    string command;

    while (true)
    {
        cout << "> ";
        getline(cin, command);

        if (command == "quit")
        {
            cout << "Goodbye." << endl;
            break;
        }
        else if (command == "help")
        {
            ShowHelp();
        }
        else if (command == "look")
        {
            ShowRoom(currentRoom);
        }
        else if (command == "inspect")
        {
            if (currentRoom->items.empty())
            {
                cout << "There is nothing of interest here." << endl;
            }
            else
            {
                cout << "You look around and see:" << endl;
                for (const Item* item : currentRoom->items)
                {
                    cout << "  - " << item->name << endl;
                }
            }
        }
        else if (command == "inventory")
        {
            ShowInventory(player);
        }
        else if (command.substr(0, 8) == "pick up ")
        {
            string itemName = command.substr(8);
            Item* item = TakeItemByName(currentRoom->items, itemName);

            if (item == nullptr)
            {
                cout << "There is no " << itemName << " here." << endl;
            }
            else
            {
                player.inventory.push_back(item);
                cout << "You pick up the " << item->name << "." << endl;

                // Notify the player if it is a weapon so they know to equip it
                if (dynamic_cast<Weapon*>(item) != nullptr)
                {
                    cout << "It's a weapon. Use 'equip " << item->name
                         << "' to equip it." << endl;
                }
            }
        }
        else if (command.substr(0, 5) == "drop ")
        {
            string itemName = command.substr(5);
            Item* item = TakeItemByName(player.inventory, itemName);

            if (item == nullptr)
            {
                cout << "You are not carrying a " << itemName << "." << endl;
            }
            else
            {
                // Unequip if the dropped item was the equipped weapon
                if (player.equippedWeapon == item)
                    player.equippedWeapon = nullptr;

                currentRoom->items.push_back(item);
                cout << "You drop the " << item->name << "." << endl;
            }
        }
        else if (command.substr(0, 6) == "equip ")
        {
            string itemName = command.substr(6);

            // Find the item in inventory without removing it
            Item* found = nullptr;
            for (Item* item : player.inventory)
            {
                if (item->name == itemName)
                {
                    found = item;
                    break;
                }
            }

            if (found == nullptr)
            {
                cout << "You don't have a " << itemName << "." << endl;
            }
            else
            {
                Weapon* weapon = dynamic_cast<Weapon*>(found);

                if (weapon == nullptr)
                {
                    cout << "The " << itemName << " is not a weapon." << endl;
                }
                else
                {
                    player.equippedWeapon = weapon;
                    cout << "You equip the " << weapon->name << "." << endl;
                }
            }
        }
        else if (command.substr(0, 4) == "put ")
        {
            // Expected format: "put <item> in <container>"
            size_t inPos = command.find(" in ");

            if (inPos == string::npos)
            {
                cout << "Put what in what? Try: put <item> in <container>" << endl;
            }
            else
            {
                string itemName      = command.substr(4, inPos - 4);
                string containerName = command.substr(inPos + 4);

                // Item must be in the player's inventory
                Item* item = TakeItemByName(player.inventory, itemName);

                if (item == nullptr)
                {
                    cout << "You are not carrying a " << itemName << "." << endl;
                }
                else
                {
                    Container* container = FindContainer(containerName, currentRoom, player);

                    if (container == nullptr)
                    {
                        // Item was already removed from inventory, put it back
                        player.inventory.push_back(item);
                        cout << "There is no " << containerName << " here." << endl;
                    }
                    else
                    {
                        // Unequip if putting away the equipped weapon
                        if (player.equippedWeapon == item)
                            player.equippedWeapon = nullptr;

                        container->items.push_back(item);
                        cout << "You put the " << item->name
                             << " in the " << container->name << "." << endl;
                    }
                }
            }
        }
        else if (command.substr(0, 5) == "take ")
        {
            // Expected format: "take <item> from <container>"
            size_t fromPos = command.find(" from ");

            if (fromPos == string::npos)
            {
                cout << "Take what from what? Try: take <item> from <container>" << endl;
            }
            else
            {
                string itemName      = command.substr(5, fromPos - 5);
                string containerName = command.substr(fromPos + 6);

                Container* container = FindContainer(containerName, currentRoom, player);

                if (container == nullptr)
                {
                    cout << "There is no " << containerName << " here." << endl;
                }
                else
                {
                    Item* item = TakeItemByName(container->items, itemName);

                    if (item == nullptr)
                    {
                        cout << "There is no " << itemName
                             << " in the " << container->name << "." << endl;
                    }
                    else
                    {
                        player.inventory.push_back(item);
                        cout << "You take the " << item->name
                             << " from the " << container->name << "." << endl;

                        if (dynamic_cast<Weapon*>(item) != nullptr)
                        {
                            cout << "It's a weapon. Use 'equip " << item->name
                                 << "' to equip it." << endl;
                        }
                    }
                }
            }
        }
        else if (command == "north" || command == "south" ||
                 command == "east"  || command == "west")
        {
            Room* next = nullptr;

            if (command == "north") next = currentRoom->north;
            if (command == "south") next = currentRoom->south;
            if (command == "east")  next = currentRoom->east;
            if (command == "west")  next = currentRoom->west;

            if (next == nullptr)
            {
                cout << "You can't go that way." << endl;
            }
            else
            {
                currentRoom = next;
                ShowRoom(currentRoom);
            }
        }
        else
        {
            cout << "Unknown command. Type 'help' for a list of commands." << endl;
        }
    }

    return 0;
}