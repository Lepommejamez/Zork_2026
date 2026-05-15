#pragma once

#include <string>
#include <vector>

class Item
{
public:
    std::string name;
    std::string description;
    std::string pickupText;
    std::string useText;

    Item(const std::string& itemName, const std::string& itemDescription);
    virtual ~Item();

    virtual void Use();
    virtual void Inspect() const;
};

class Weapon : public Item
{
public:
    int damage;

    Weapon(const std::string& itemName, const std::string& itemDescription, int itemDamage);
    void Use() override;
};

class Container : public Item
{
public:
    std::vector<Item*> items;

    Container(const std::string& itemName, const std::string& itemDescription);
    void Use() override;
};

class GenericItem : public Item
{
public:
    GenericItem(const std::string& itemName, const std::string& itemDescription);
    void Use() override;
};

class Room
{
public:
    std::string name;
    std::string description;

    Room* north = nullptr;
    Room* south = nullptr;
    Room* east = nullptr;
    Room* west = nullptr;
    Room* down = nullptr;
    Room* up = nullptr;

    bool isLocked = false;

    std::vector<Item*> items;
};

void ShowRoom(const Room* room);
void ShowHelp();
