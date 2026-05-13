#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"

void init_player(Player* player, Location* start_location);
void move_player(Player* player, char direction);
void look_around(Player* player);
void take_item(Player* player, const char* item_name);
void list_inventory(Player* player);
void laugh(Player* player);
void show_status(Player* player);

#endif
