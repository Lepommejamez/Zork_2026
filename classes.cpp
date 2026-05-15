#include "classes.h"

#include <iostream>

Item::Item(const std::string& itemName, const std::string& itemDescription)
{
    name = itemName;
    description = itemDescription;
}

Item::~Item() = default;

void Item::Use()
{
    if (useText != "")
    {
        std::cout << useText << std::endl;
    }
    else
    {
        std::cout << "I'm not sure what I expected to happen." << std::endl;
    }
}

void Item::Inspect() const
{
    std::cout << description << std::endl;
}

Weapon::Weapon(const std::string& itemName, const std::string& itemDescription, int itemDamage)
    : Item(itemName, itemDescription)
{
    damage = itemDamage;
}

void Weapon::Use()
{
    std::cout << "I swing the " << name << ". Feels good in my hand." << std::endl;
}

Container::Container(const std::string& itemName, const std::string& itemDescription)
    : Item(itemName, itemDescription)
{
}

void Container::Use()
{
    std::cout << "I open the " << name << "." << std::endl;

    if (items.empty())
    {
        std::cout << "Nothing inside. Figures." << std::endl;
    }
    else
    {
        std::cout << "Let's see what's in here..." << std::endl;

        for (const Item* item : items)
        {
            std::cout << "  - " << item->name << std::endl;
        }
    }
}

GenericItem::GenericItem(const std::string& itemName, const std::string& itemDescription)
    : Item(itemName, itemDescription)
{
}

void GenericItem::Use()
{
    std::cout << "I fiddle with the " << name << ". Nothing useful comes of it." << std::endl;
}

void ShowRoom(const Room* room)
{
    std::cout << std::endl;
    std::cout << "=== " << room->name << " ===" << std::endl;
    std::cout << room->description << std::endl;
    std::cout << std::endl;

    std::cout << "I could head: ";
    if (room->north != nullptr) std::cout << "north ";
    if (room->south != nullptr) std::cout << "south ";
    if (room->east != nullptr) std::cout << "east ";
    if (room->west != nullptr) std::cout << "west ";
    if (room->down != nullptr) std::cout << "down ";
    if (room->up != nullptr) std::cout << "up ";
    std::cout << std::endl;
}

void ShowHelp()
{
    std::cout << std::endl;
    std::cout << "Let me think about what I can do..." << std::endl;
    std::cout << "  - north / south / east / west / down / up  (move around)" << std::endl;
    std::cout << "  - look                         (take in my surroundings)" << std::endl;
    std::cout << "  - inspect                      (look for anything useful)" << std::endl;
    std::cout << "  - pick up <item>               (grab something)" << std::endl;
    std::cout << "  - drop <item>                  (leave something behind)" << std::endl;
    std::cout << "  - put <item> in <container>    (stash something away)" << std::endl;
    std::cout << "  - take <item> from <container> (fish something out)" << std::endl;
    std::cout << "  - equip <item>                 (get a weapon ready)" << std::endl;
    std::cout << "  - inventory                    (check what I'm carrying)" << std::endl;
    std::cout << "  - help                         (think this through again)" << std::endl;
    std::cout << "  - quit                         (give up)" << std::endl;
    std::cout << std::endl;
}
