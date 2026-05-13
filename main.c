#include <stdio.h>
#include <string.h>
#include "world.h"
#include "player.h"

int main() {
    Location* start = init_world();
    Player player;
    init_player(&player, start);

    printf("Welcome to the Laughing Octo Journey!\n");
    printf("Type 'help' for commands.\n");

    char input[64];
    while (1) {
        printf("\n> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        input[strcspn(input, "\n")] = 0; // Remove newline

        if (strcmp(input, "quit") == 0) {
            printf("Thanks for playing! Stay octo-awesome!\n");
            break;
        } else if (strcmp(input, "help") == 0) {
            printf("Commands: north, south, east, west, look, inventory, take <item>, laugh, status, quit\n");
        } else if (strcmp(input, "north") == 0) {
            move_player(&player, 'n');
        } else if (strcmp(input, "south") == 0) {
            move_player(&player, 's');
        } else if (strcmp(input, "east") == 0) {
            move_player(&player, 'e');
        } else if (strcmp(input, "west") == 0) {
            move_player(&player, 'w');
        } else if (strcmp(input, "look") == 0) {
            look_around(&player);
        } else if (strcmp(input, "inventory") == 0) {
            list_inventory(&player);
        } else if (strcmp(input, "laugh") == 0) {
            laugh(&player);
        } else if (strcmp(input, "status") == 0) {
            show_status(&player);
        } else if (strncmp(input, "take ", 5) == 0) {
            take_item(&player, input + 5);
        } else {
            printf("Unknown command. Type 'help' for options.\n");
        }
    }

    return 0;
}
