#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "../include/player.h"

void init_player(Player* player, Location* start_location) {
    player->current_location = start_location;
    player->inventory_count = 0;
    player->laughter_level = 50; // Neutral laughter
    player->sprite = (Texture2D){ 0 };
    player->currentFrame = 0;
    player->frameCount = 4;
    player->frameTimer = 0.0f;
    player->frameSpeed = 8.0f; // Frames per second
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
    }
}

void laugh(Player* player) {
    player->laughter_level += 10;
    if (player->laughter_level > 100) player->laughter_level = 100;
}

void take_item(Player* player, const char* item_name) {
    Location* loc = player->current_location;
    for (int i = 0; i < loc->item_count; i++) {
        if (strcasecmp(loc->items[i]->name, item_name) == 0) {
            if (player->inventory_count < MAX_ITEMS) {
                player->inventory[player->inventory_count++] = loc->items[i];
                player->laughter_level += 5;
                if (player->laughter_level > 100) player->laughter_level = 100;

                for (int j = i; j < loc->item_count - 1; j++) {
                    loc->items[j] = loc->items[j+1];
                }
                loc->item_count--;
                return;
            }
        }
    }
}
