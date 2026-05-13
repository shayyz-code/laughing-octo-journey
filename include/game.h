#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define MAX_ITEMS 10
#define MAX_DESC 256
#define MAX_NAME 64

typedef struct {
    char name[MAX_NAME];
    char description[MAX_DESC];
} Item;

typedef struct Location {
    char name[MAX_NAME];
    char description[MAX_DESC];
    struct Location *north;
    struct Location *south;
    struct Location *east;
    struct Location *west;
    Item *items[MAX_ITEMS];
    int item_count;
} Location;

typedef struct {
    Location *current_location;
    Item *inventory[MAX_ITEMS];
    int inventory_count;
    int laughter_level;
} Player;

#endif
