#include <stdio.h>
#include <string.h>
#include <math.h>
#include "raylib.h"
#include "world.h"
#include "player.h"

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Laughing Octo Journey 🐙");

    Location* start = init_world();
    Player player;
    init_player(&player, start);

    SetTargetFPS(60);

    Vector2 octoPos = {(float)screenWidth / 2, (float)screenHeight / 2};
    float bobbingAmount = 0;
    float timer = 0;

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        timer += GetFrameTime();
        bobbingAmount = sinf(timer * 2.0f) * 10.0f; // Bobbing animation

        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            move_player(&player, 'n');
        } else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            move_player(&player, 's');
        } else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
            move_player(&player, 'e');
        } else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            move_player(&player, 'w');
        } else if (IsKeyPressed(KEY_L)) {
            laugh(&player);
        }

        // Draw
        BeginDrawing();

            ClearBackground(SKYBLUE); // Default ocean color

            // Draw current location info
            DrawRectangle(10, 10, 780, 100, Fade(BLACK, 0.3f));
            DrawText(player.current_location->name, 20, 20, 30, WHITE);
            DrawText(player.current_location->description, 20, 60, 20, LIGHTGRAY);

            // Draw status
            char laughterText[32];
            sprintf(laughterText, "Laughter: %d%%", player.laughter_level);
            DrawText(laughterText, 20, screenHeight - 40, 20, MAGENTA);

            // Draw inventory count
            char invText[32];
            sprintf(invText, "Items: %d", player.inventory_count);
            DrawText(invText, 200, screenHeight - 40, 20, YELLOW);

            // Draw instructions
            DrawText("Arrows/WASD to move, 'L' to laugh", screenWidth - 300, screenHeight - 40, 15, WHITE);

            // Draw the Octopus (Placeholder: A cute pink circle with eyes)
            DrawCircleV((Vector2){octoPos.x, octoPos.y + bobbingAmount}, 40, PINK);
            DrawCircle(octoPos.x - 15, octoPos.y + bobbingAmount - 10, 5, BLACK); // Left eye
            DrawCircle(octoPos.x + 15, octoPos.y + bobbingAmount - 10, 5, BLACK); // Right eye
            DrawText("🐙", octoPos.x - 20, octoPos.y + bobbingAmount - 20, 40, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
