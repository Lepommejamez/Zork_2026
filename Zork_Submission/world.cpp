#include "world.h"

GameWorld::GameWorld()
    : knife("knife", "A rusty kitchen knife. Still sharp.", 4),
      canOfBeans("can of beans", "A dented tin of beans. Probably fine."),
      cupboard("cupboard", "A wooden cupboard, slightly ajar."),
      oldRecipe("old recipe", "A handwritten recipe, barely legible."),
      tvRemote("TV remote", "Dead batteries. Of course."),
      newspaper("newspaper", "Dated three years ago. Yellowed at the edges."),
      toolbox("toolbox", "A heavy red metal toolbox."),
      wrench("wrench", "A solid steel wrench. Could do some damage.", 6),
      oilCan("oil can", "Half-full of motor oil. Smells awful."),
      rock("rock", "A fist-sized rock. Satisfyingly heavy."),
      brokenKey("broken key", "Half a key. Useless on its own."),
      wardrobe("wardrobe", "An old wardrobe. The door creaks when I open it."),
      basementKey("basement key", "A small iron key. A tag on it reads 'basement'."),
      dustyJacket("dusty jacket", "Someone's old jacket. Hasn't been worn in years."),
      oldPapers("old papers", "A stack of yellowed documents. Hard to make out."),
      brokenLamp("broken lamp", "A floor lamp, snapped at the base. Useless now.")
{
    cupboard.items.push_back(&oldRecipe);
    toolbox.items.push_back(&wrench);
    wardrobe.items.push_back(&basementKey);

    kitchen.name = "Kitchen";
    kitchen.description = "A messy kitchen. Something smells burnt and the sink is full.";
    kitchen.items.push_back(&knife);
    kitchen.items.push_back(&canOfBeans);
    kitchen.items.push_back(&cupboard);

    livingRoom.name = "Living Room";
    livingRoom.description = "A dusty living room. An old TV sits dead in the corner.";
    livingRoom.items.push_back(&tvRemote);
    livingRoom.items.push_back(&newspaper);

    bedroom.name = "Bedroom";
    bedroom.description = "A small, dim bedroom. Smells stale. There's a wardrobe in the corner.";
    bedroom.items.push_back(&wardrobe);
    bedroom.items.push_back(&dustyJacket);

    garage.name = "Garage";
    garage.description = "A dark garage. Oil stains cover the concrete floor.";
    garage.items.push_back(&toolbox);
    garage.items.push_back(&oilCan);

    outside.name = "Outside";
    outside.description = "I step outside. The sun is blinding after the gloom indoors.";
    outside.items.push_back(&rock);
    outside.items.push_back(&brokenKey);

    basement.name = "Basement";
    basement.description = "It's damp down here. The air is thick and the light barely reaches the corners.";
    basement.isLocked = true;
    basement.items.push_back(&oldPapers);
    basement.items.push_back(&brokenLamp);

    kitchen.west = &livingRoom;
    kitchen.south = &garage;
    kitchen.north = &outside;
    kitchen.down = &basement;

    livingRoom.east = &kitchen;
    livingRoom.west = &bedroom;

    bedroom.east = &livingRoom;

    garage.north = &kitchen;

    outside.south = &kitchen;

    basement.up = &kitchen;
}

Room* GameWorld::GetStartingRoom()
{
    return &kitchen;
}
