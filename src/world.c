#include <stdlib.h>
#include <string.h>
#include "../include/world.h"

Location* create_location(const char* name, const char* desc) {
    Location* loc = malloc(sizeof(Location));
    strncpy(loc->name, name, MAX_NAME);
    strncpy(loc->description, desc, MAX_DESC);
    loc->north = loc->south = loc->east = loc->west = NULL;
    loc->item_count = 0;
    return loc;
}

Item* create_item(const char* name, const char* desc) {
    Item* item = malloc(sizeof(Item));
    strncpy(item->name, name, MAX_NAME);
    strncpy(item->description, desc, MAX_DESC);
    return item;
}

Location* init_world() {
    Location* reef = create_location("Coral Reef", "A vibrant reef full of colorful fish and swaying anemones.");
    Location* cave = create_location("Dark Cave", "A mysterious, bioluminescent cave with strange echoes.");
    Location* ship = create_location("Sunken Shipwreck", "An ancient wooden ship resting on the sandy floor.");
    Location* abyss = create_location("The Abyss", "A deep, dark trench where the pressure is immense.");

    // Add items
    reef->items[reef->item_count++] = create_item("Shiny Pearl", "A perfectly round, lustrous pearl.");
    ship->items[ship->item_count++] = create_item("Golden Dubloon", "A weathered gold coin from a lost era.");
    cave->items[cave->item_count++] = create_item("Glow-Shrimp", "A tiny shrimp that emits a faint blue light.");

    // Connect locations
    reef->north = cave;
    cave->south = reef;
    reef->east = ship;
    ship->west = reef;
    ship->south = abyss;
    abyss->north = ship;

    return reef; // Starting location
}
