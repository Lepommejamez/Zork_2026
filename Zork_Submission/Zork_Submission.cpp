#include <iostream>
#include <string>
#include <vector>

#include "classes.h"
#include "player.h"
#include "world.h"

using namespace std;

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
        cout << "I'm not carrying anything. Probably should fix that." << endl;
        return;
    }

    cout << "Let's see what I've got on me:" << endl;
    for (const Item* item : player.inventory)
    {
        cout << "  - " << item->name;

        if (player.equippedWeapon == item)
            cout << " (in hand)";

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
    GameWorld world;
    Room* currentRoom = world.GetStartingRoom();
    Player player;
    ShowRoom(currentRoom);

    string command;

    while (true)
    {
        cout << "> ";
        getline(cin, command);

        if (command == "quit")
        {
            cout << "Yeah... maybe another time." << endl;
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
                cout << "I look around. Nothing worth grabbing." << endl;
            }
            else
            {
                cout << "I scan the room. I can make out:" << endl;
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
                cout << "I don't see any " << itemName << " here." << endl;
            }
            else
            {
                player.inventory.push_back(item);
                cout << "I grab the " << item->name << " and pocket it." << endl;

                // Notify the player if it is a weapon so they know to equip it
                if (dynamic_cast<Weapon*>(item) != nullptr)
                {
                    cout << "Could be useful in a fight. I should equip it." << endl;
                }
            }
        }
        else if (command.substr(0, 5) == "drop ")
        {
            string itemName = command.substr(5);
            Item* item = TakeItemByName(player.inventory, itemName);

            if (item == nullptr)
            {
                cout << "I don't have a " << itemName << " on me." << endl;
            }
            else
            {
                // Unequip if the dropped item was the equipped weapon
                if (player.equippedWeapon == item)
                    player.equippedWeapon = nullptr;

                currentRoom->items.push_back(item);
                cout << "I leave the " << item->name << " behind." << endl;
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
                cout << "I don't have a " << itemName << "." << endl;
            }
            else
            {
                Weapon* weapon = dynamic_cast<Weapon*>(found);

                if (weapon == nullptr)
                {
                    cout << "I can't really fight with a " << itemName << "." << endl;
                }
                else
                {
                    player.equippedWeapon = weapon;
                    cout << "I get the " << weapon->name << " ready." << endl;
                }
            }
        }
        else if (command.substr(0, 4) == "put ")
        {
            // Expected format: "put <item> in <container>"
            size_t inPos = command.find(" in ");

            if (inPos == string::npos)
            {
                cout << "Put what where? Try: put <item> in <container>" << endl;
            }
            else
            {
                string itemName      = command.substr(4, inPos - 4);
                string containerName = command.substr(inPos + 4);

                // Item must be in the player's inventory
                Item* item = TakeItemByName(player.inventory, itemName);

                if (item == nullptr)
                {
                    cout << "I don't have a " << itemName << " on me." << endl;
                }
                else
                {
                    Container* container = FindContainer(containerName, currentRoom, player);

                    if (container == nullptr)
                    {
                        // Item was already removed from inventory, put it back
                        player.inventory.push_back(item);
                        cout << "I don't see a " << containerName << " anywhere." << endl;
                    }
                    else
                    {
                        // Unequip if putting away the equipped weapon
                        if (player.equippedWeapon == item)
                            player.equippedWeapon = nullptr;

                        container->items.push_back(item);
                        cout << "I tuck the " << item->name
                             << " into the " << container->name << "." << endl;
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
                cout << "Take what from where? Try: take <item> from <container>" << endl;
            }
            else
            {
                string itemName      = command.substr(5, fromPos - 5);
                string containerName = command.substr(fromPos + 6);

                Container* container = FindContainer(containerName, currentRoom, player);

                if (container == nullptr)
                {
                    cout << "I don't see a " << containerName << " anywhere." << endl;
                }
                else
                {
                    Item* item = TakeItemByName(container->items, itemName);

                    if (item == nullptr)
                    {
                        cout << "There's no " << itemName
                             << " in the " << container->name << "." << endl;
                    }
                    else
                    {
                        player.inventory.push_back(item);
                        cout << "I pull the " << item->name
                             << " out of the " << container->name << "." << endl;

                        if (dynamic_cast<Weapon*>(item) != nullptr)
                        {
                            cout << "Could be useful in a fight. I should equip it." << endl;
                        }
                    }
                }
            }
        }
        else if (command == "north" || command == "south" ||
                 command == "east"  || command == "west"  ||
                 command == "down"  || command == "up")
        {
            Room* next = nullptr;

            if (command == "north") next = currentRoom->north;
            if (command == "south") next = currentRoom->south;
            if (command == "east")  next = currentRoom->east;
            if (command == "west")  next = currentRoom->west;
            if (command == "down")  next = currentRoom->down;
            if (command == "up")    next = currentRoom->up;

            if (next == nullptr)
            {
                cout << "Nothing that way. I'd just walk into a wall." << endl;
            }
            else if (next->isLocked)
            {
                // Check if the player has the basement key anywhere in their inventory
                bool hasKey = false;
                for (const Item* item : player.inventory)
                {
                    if (item->name == "basement key")
                    {
                        hasKey = true;
                        break;
                    }
                }

                if (!hasKey)
                {
                    cout << "The door is locked tight. There must be a key somewhere." << endl;
                }
                else
                {
                    cout << "I try the key. It fits. The door groans open." << endl;
                    currentRoom = next;
                    ShowRoom(currentRoom);
                }
            }
            else
            {
                currentRoom = next;
                ShowRoom(currentRoom);
            }
        }
        else
        {
            cout << "I'm not sure what I mean by that. Maybe try 'help'." << endl;
        }
    }

    return 0;
}