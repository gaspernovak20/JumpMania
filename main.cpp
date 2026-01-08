#include "raylib.h"
#include "include/Anemy.h"
#include "include/Player.h"
#include "include/InputState.h"
#include "include/Level.h"
#include "include/Background.h"
#include "include/UI.h"
#include "include/GameContext.h"
#include <filesystem>
#include <vector>
#include <cmath>
using namespace std;

enum GameState
{
    MENU,
    PLAYING
};

InputState input;

int main()
{
    GameContext ctx{800, 450, (float)(800 / 15)};

    GameState currentState = MENU;

    InitWindow(ctx.screenWidth, ctx.screenHeight, "Platformer with Camera");
    SetExitKey(KEY_NULL);
    InitAudioDevice();
    SetTargetFPS(120);

    Vector2 playerPos = {ctx.tileSize * 10, 296};

    Background background = Background(ctx);
    Player player = Player(playerPos, ctx);
    Level level = Level("..//Level.txt", ctx, player);

    Anemy::LoadTextures();
    background.LoadTextures();
    level.LoadTextures();
    player.LoadTextures();

    UI ui = UI(ctx, level.getNumOfAllDiamonds(), player);
    ui.LoadTextures();

    Camera2D camera = {0};
    camera.offset = {ctx.screenWidth / 2.0f, ctx.screenHeight / 2.0f};
    camera.zoom = 1.0f;

    while (!WindowShouldClose())
    {
        if (IsWindowResized())
        {
            ctx.screenWidth = GetScreenWidth();
            ctx.screenHeight = GetScreenHeight();
        }

        float deltaTime = GetFrameTime();

        Vector2 mouse = GetMousePosition();

        input.pouse = IsKeyDown(KEY_ESCAPE);
        input.moveRight = IsKeyDown(KEY_D);
        input.moveLeft = IsKeyDown(KEY_A);
        input.jump = IsKeyDown(KEY_SPACE);
        input.attack = IsKeyDown(KEY_K);
        input.shield = IsKeyDown(KEY_J);

        camera.target = {player.getRenderPosition().x, (float)(ctx.screenHeight / 2)};

        if (currentState == PLAYING)
        {

            if (input.pouse)
                currentState = MENU;

            level.Update(deltaTime, input);
        }
        background.Update(deltaTime);

        BeginDrawing();
        ClearBackground(WHITE);

        background.Draw();
        ui.Draw();

        BeginMode2D(camera);

        level.Draw();

        EndMode2D();

        if (currentState == MENU)
        {

            bool mouseOver =
                CheckCollisionPointRec(mouse, ui.getButtonPlayHitbox());

            if (mouseOver && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentState = PLAYING;
            }

            DrawRectangle(0, 0, ctx.screenWidth, ctx.screenHeight, Color{0, 0, 0, 50});
            ui.DrawPlayButton();
        }
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    Anemy::UnloadTextures();
    return 0;
}
