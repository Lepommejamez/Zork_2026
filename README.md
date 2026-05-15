# Jork — House of Locked Doors

A text-based adventure game built in C++ for the Advanced Programming for AAA Video Games course.
You wake up in a strange house with no memory of how you got there. Something is wrong here.
Find the key. Get to the basement. Figure out what happened.

**Repository:** [https://github.com/Lepommejamez/Zork_2026]

**Author:** YOUR NAME

**License:** MIT — see LICENSE file

---

## How to play

Run `zork.exe` from the command line or double-click it. The game is text-based — you type
commands and press Enter.

### Commands

| Command | What it does |
|---|---|
| `north` / `south` / `east` / `west` / `down` / `up` | Move between rooms |
| `look` | Get a description of your current surroundings |
| `inspect` | Look around for items in the room |
| `pick up <item>` | Pick something up and put it in your inventory |
| `drop <item>` | Leave something behind in the current room |
| `inventory` | Check what you're carrying |
| `equip <item>` | Get a weapon ready in your hand |
| `put <item> in <container>` | Store an item inside a container |
| `take <item> from <container>` | Take an item out of a container |
| `help` | List all available commands |
| `quit` | Exit the game |

### Tips

- Item names are case-sensitive. Type them exactly as they appear when you `inspect` a room.
- Containers like the wardrobe and toolbox hold items inside them — use `take <item> from <container>` to retrieve them.
- You need an item in your **inventory** (not inside another container) to use it.

---

## Map

```
  [Outside]
      |
      N
      |
[Bedroom] - W - [Living Room] - E - [Kitchen] - S - [Garage]
                                        |
                                       Down
                                        |
                                    [Basement] (locked)
```

---

## How to finish the game

The goal is to reach the basement.

1. Start in the **Kitchen**. Head west to the **Living Room**, then west again to the **Bedroom**.
2. In the bedroom, `inspect` the room, then `take basement key from wardrobe`.
3. With the key in your inventory, go back east twice to the **Kitchen**.
4. Type `down`. The key unlocks the basement door.

That's it. What you find down there is up to interpretation.

---

## What I struggled with / design notes

The extra feature implemented is a **locked room mechanic** — the basement can only be entered
if the player is carrying the basement key. The lock is permanent; the door does not stay open,
so the player must keep the key on them.

The game uses polymorphism through the `Item` class hierarchy (`Weapon`, `Container`,
`GenericItem`), with `dynamic_cast` used at runtime to identify weapon types for equipping
and notifying the player. Containers hold their own `vector<Item*>`, allowing arbitrary
nesting of items inside items.

**On the class hierarchy:** The assignment suggested a single shared base class connecting
rooms, items, exits, and creatures under one `Entity` tree. I chose not to follow that
structure because it didn't feel intuitive to me — I couldn't find a natural reason for
a `Room` and an `Item` to share a parent. Having them inherit from the same root felt like
it would add coupling without adding clarity. Instead I went with separate, independent
hierarchies for each concept. It achieves the same end goal and I think the relationships
between classes are easier to reason about this way, but I wanted to flag the departure
in case it reads as an oversight.

**On tooling:** I normally work in VS Code, so setting up and working inside Visual Studio
was a bigger time sink than expected. Getting comfortable with the project structure,
build configuration, and the IDE's quirks ate up a meaningful chunk of the time I had
allocated for actual development.

**On scope:** I had originally wanted to add NPCs and a larger map — a few more rooms and
at least one character to interact with. The Visual Studio friction meant that didn't make
it in. The locked door mechanic became the focus instead, which I think works well within
the scope of the game as it stands.

The writing is intentionally first-person and internal — the player character thinks out loud
rather than receiving instructions from a narrator.