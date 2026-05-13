#include <stdio.h>
#include <string.h>
#include <math.h>
#include "raylib.h"
#include "world.h"
#include "player.h"
#include "particles.h"

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Laughing Octo Journey 🐙");

    Location* start = init_world();
    Player player;
    init_player(&player, start);

    // Create procedural Octopus Animation Sheet (4 frames)
    Image octoSheet = GenImageColor(80 * 4, 80, BLANK);
    for (int f = 0; f < 4; f++) {
        int offsetX = f * 80;
        ImageDrawCircle(&octoSheet, offsetX + 40, 40, 35, PINK);
        ImageDrawCircle(&octoSheet, offsetX + 25, 30, 5, BLACK);
        ImageDrawCircle(&octoSheet, offsetX + 55, 30, 5, BLACK);
        // Draw moving tentacles
        for (int i = 0; i < 8; i++) {
            float tentacleOffset = sinf((float)f * 1.5f + (float)i) * 5.0f;
            ImageDrawCircle(&octoSheet, offsetX + 15 + i*7, 65 + tentacleOffset, 8, PINK);
        }
    }
    player.sprite = LoadTextureFromImage(octoSheet);
    UnloadImage(octoSheet);

    // Load Shaders
    Shader waterShader = LoadShader(0, "shaders/water.fs");
    int secondsLoc = GetShaderLocation(waterShader, "seconds");

    // Initialize RenderTexture for post-processing
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    InitParticles();

    SetTargetFPS(60);

    Vector2 octoPos = {(float)screenWidth / 2, (float)screenHeight / 2};
    float bobbingAmount = 0;
    float timer = 0;
    float moveSpeed = 300.0f;

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        float dt = GetFrameTime();
        timer += dt;
        
        // Update shader uniform
        SetShaderValue(waterShader, secondsLoc, &timer, SHADER_UNIFORM_FLOAT);

        UpdateParticles(dt);

        // Update Animation
        player.frameTimer += dt;
        if (player.frameTimer >= (1.0f / player.frameSpeed)) {
            player.frameTimer = 0.0f;
            player.currentFrame++;
            if (player.currentFrame >= player.frameCount) player.currentFrame = 0;
        }

        bobbingAmount = sinf(timer * 2.0f) * 10.0f; // Bobbing animation

        // Continuous Movement
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) octoPos.y -= moveSpeed * dt;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) octoPos.y += moveSpeed * dt;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) octoPos.x -= moveSpeed * dt;
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) octoPos.x += moveSpeed * dt;

        // Edge Detection and Room Transitions
        if (octoPos.x < 0) {
            if (player.current_location->west) {
                move_player(&player, 'w');
                octoPos.x = screenWidth - 5;
            } else {
                octoPos.x = 0;
            }
        } else if (octoPos.x > screenWidth) {
            if (player.current_location->east) {
                move_player(&player, 'e');
                octoPos.x = 5;
            } else {
                octoPos.x = screenWidth;
            }
        }

        if (octoPos.y < 110) { // Offset for the HUD area
            if (player.current_location->north) {
                move_player(&player, 'n');
                octoPos.y = screenHeight - 45;
            } else {
                octoPos.y = 110;
            }
        } else if (octoPos.y > screenHeight - 40) { // Offset for the status area
            if (player.current_location->south) {
                move_player(&player, 's');
                octoPos.y = 115;
            } else {
                octoPos.y = screenHeight - 40;
            }
        }

        if (IsKeyPressed(KEY_L)) {
            laugh(&player);
        } else if (IsKeyPressed(KEY_T)) {
            if (player.current_location->item_count > 0) {
                take_item(&player, player.current_location->items[0]->name);
            }
        }

        // Draw to RenderTexture
        BeginTextureMode(target);
            if (player.current_location->background.id != 0) {
                DrawTexture(player.current_location->background, 0, 0, WHITE);
            } else {
                ClearBackground(player.current_location->bgColor); // Location-specific color
            }

            // Simple procedural background elements
            if (strcmp(player.current_location->name, "Coral Reef") == 0) {
                DrawCircle(100, 400, 50, PINK);
                DrawCircle(200, 450, 40, LIME);
                DrawCircle(600, 380, 60, MAROON);
            } else if (strcmp(player.current_location->name, "Dark Cave") == 0) {
                for(int i=0; i<20; i++) DrawCircle(150 + i*30, 200 + (i%5)*50, 2, YELLOW);
            } else if (strcmp(player.current_location->name, "Sunken Shipwreck") == 0) {
                DrawRectangle(300, 350, 200, 100, BROWN);
                DrawRectangle(350, 300, 20, 50, DARKBROWN); // Mast
            }

            DrawParticles();

            // Draw current location info
            DrawRectangle(10, 10, 780, 100, Fade(BLACK, 0.3f));
            DrawText(player.current_location->name, 20, 20, 30, WHITE);
            DrawText(player.current_location->description, 20, 60, 20, LIGHTGRAY);

            // Draw items in the location
            for (int i = 0; i < player.current_location->item_count; i++) {
                int itemX = 100 + (i * 100);
                int itemY = 500;
                // Draw glow for items
                DrawCircleGradient(itemX, itemY, 30, Fade(YELLOW, 0.3f), BLANK);
                DrawCircle(itemX, itemY, 15, YELLOW);
                DrawText(player.current_location->items[i]->name, itemX - 20, itemY + 20, 10, WHITE);
            }

            // Draw the Octopus (With Glow and Animation)
            Vector2 drawPos = {octoPos.x - 40, octoPos.y + bobbingAmount - 40};
            
            // Draw bioluminescent glow
            DrawCircleGradient(octoPos.x, octoPos.y + bobbingAmount, 60, Fade(PINK, 0.2f), BLANK);
            
            // Draw current frame from animation sheet
            Rectangle sourceRec = { (float)player.currentFrame * 80, 0, 80, 80 };
            DrawTextureRec(player.sprite, sourceRec, drawPos, WHITE);
            
            DrawText("🐙", octoPos.x - 20, octoPos.y + bobbingAmount - 20, 40, WHITE);
        EndTextureMode();

        // Draw RenderTexture to Screen with Shader
        BeginDrawing();
            ClearBackground(BLACK);
            
            BeginShaderMode(waterShader);
                // NOTE: Render texture must be y-flipped because of OpenGL coordinates
                DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2){ 0, 0 }, WHITE);
            EndShaderMode();

            // Draw UI Elements (Top layer, no shader)
            // Draw status
            char laughterText[32];
            sprintf(laughterText, "Laughter: %d%%", player.laughter_level);
            DrawText(laughterText, 20, screenHeight - 40, 20, MAGENTA);

            // Draw inventory count
            char invText[32];
            sprintf(invText, "Items: %d", player.inventory_count);
            DrawText(invText, 200, screenHeight - 40, 20, YELLOW);

            // Draw instructions
            DrawText("Hold Arrows/WASD to swim. Touch edges to change locations.", screenWidth - 450, screenHeight - 40, 15, WHITE);
            DrawText("'L' to laugh, 'T' to take", screenWidth - 250, screenHeight - 20, 12, LIGHTGRAY);

        EndDrawing();
    }

    UnloadShader(waterShader);
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}
