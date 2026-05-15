#pragma once

#include <vector>

#include "classes.h"

struct Player
{
    std::vector<Item*> inventory;
    Weapon* equippedWeapon = nullptr;
};
