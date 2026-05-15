#pragma once

#include "classes.h"

struct GameWorld
{
    Weapon knife;
    GenericItem canOfBeans;
    Container cupboard;
    GenericItem oldRecipe;

    GenericItem tvRemote;
    GenericItem newspaper;

    Container toolbox;
    Weapon wrench;
    GenericItem oilCan;

    GenericItem rock;
    GenericItem brokenKey;

    Container wardrobe;
    GenericItem basementKey;
    GenericItem dustyJacket;

    GenericItem oldPapers;
    GenericItem brokenLamp;

    Room kitchen;
    Room livingRoom;
    Room bedroom;
    Room garage;
    Room outside;
    Room basement;

    GameWorld();
    Room* GetStartingRoom();
};
