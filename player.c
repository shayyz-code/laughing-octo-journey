#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "player.h"

void init_player(Player* player, Location* start_location) {
    player->current_location = start_location;
    player->inventory_count = 0;
    player->laughter_level = 50; // Neutral laughter
}

void move_player(Player* player, char direction) {
    Location* next = NULL;
    switch (direction) {
        case 'n': next = player->current_location->north; break;
        case 's': next = player->current_location->south; break;
        case 'e': next = player->current_location->east; break;
        case 'w': next = player->current_location->west; break;
    }

    if (next) {
        player->current_location = next;
        printf("You swim to the %s%s%s.\n", CYAN, next->name, RESET);
    } else {
        printf("%sYou can't go that way! There's nothing but ink!%s\n", RED, RESET);
    }
}

void look_around(Player* player) {
    Location* loc = player->current_location;
    printf("\n--- %s%s%s ---\n", BLUE, loc->name, RESET);
    printf("%s\n", loc->description);
    
    if (loc->item_count > 0) {
        printf("You see:");
        for (int i = 0; i < loc->item_count; i++) {
            printf(" %s[%s]%s", YELLOW, loc->items[i]->name, RESET);
        }
        printf("\n");
    }

    printf("Exits:");
    if (loc->north) printf(" %snorth%s", GREEN, RESET);
    if (loc->south) printf(" %ssouth%s", GREEN, RESET);
    if (loc->east) printf(" %seast%s", GREEN, RESET);
    if (loc->west) printf(" %swest%s", GREEN, RESET);
    printf("\n");
}

void laugh(Player* player) {
    player->laughter_level += 10;
    if (player->laughter_level > 100) player->laughter_level = 100;
    
    const char* puns[] = {
        "That was ink-redible!",
        "You're a real octo-pi!",
        "Stop kraken me up!",
        "Tentacle-y speaking, you're hilarious!",
        "You're squidding me!"
    };
    int pun_idx = player->laughter_level % 5;

    printf("%s%s%s\n", MAGENTA, puns[pun_idx], RESET);
    printf("You let out a bubbly octopus giggle! Laughter Level: %s%d%%%s\n", 
           (player->laughter_level > 80 ? GREEN : YELLOW), 
           player->laughter_level, RESET);

    if (player->laughter_level == 100) {
        printf("%sULTIMATE HAPPINESS REACHED! You are the jolliest octopus in the sea!%s\n", YELLOW, RESET);
    }
}

void show_status(Player* player) {
    printf("\n--- %sStatus%s ---\n", MAGENTA, RESET);
    printf("Location: %s%s%s\n", CYAN, player->current_location->name, RESET);
    printf("Laughter Level: %s%d%%%s\n", (player->laughter_level > 50 ? GREEN : RED), player->laughter_level, RESET);
    printf("Items Carried: %d\n", player->inventory_count);
}

void take_item(Player* player, const char* item_name) {
    Location* loc = player->current_location;
    for (int i = 0; i < loc->item_count; i++) {
        if (strcasecmp(loc->items[i]->name, item_name) == 0) {
            if (player->inventory_count < MAX_ITEMS) {
                player->inventory[player->inventory_count++] = loc->items[i];
                printf("You took the %s.\n", loc->items[i]->name);
                
                // Finding something shiny makes you happy
                player->laughter_level += 5;
                if (player->laughter_level > 100) player->laughter_level = 100;

                // Remove from location
                for (int j = i; j < loc->item_count - 1; j++) {
                    loc->items[j] = loc->items[j+1];
                }
                loc->item_count--;
                return;
            } else {
                printf("Your inventory is full!\n");
                return;
            }
        }
    }
    printf("There is no %s here.\n", item_name);
}

void list_inventory(Player* player) {
    if (player->inventory_count == 0) {
        printf("Your inventory is empty.\n");
        return;
    }
    printf("Your inventory:\n");
    for (int i = 0; i < player->inventory_count; i++) {
        printf("- %s: %s\n", player->inventory[i]->name, player->inventory[i]->description);
    }
}
