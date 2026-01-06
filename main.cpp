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

InputState input;

int main()
{
    cout << __cplusplus << endl;
    GameContext ctx{800, 450, (float)(800 / 15)};

    InitWindow(ctx.screenWidth, ctx.screenHeight, "Platformer with Camera");
    SetTargetFPS(120);

    Vector2 playerPos = {ctx.tileSize * 10, 200};

    Background background = Background(ctx);
    Player player = Player(playerPos, ctx);
    Level level = Level("..//Level.txt", ctx, player);

    Anemy::LoadTextures();
    background.LoadTextures();
    level.LoadTextures();
    player.LoadTextures();

    UI ui = UI(level.getNumOfAllDiamonds(), player);
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

        input.moveRight = IsKeyDown(KEY_D);
        input.moveLeft = IsKeyDown(KEY_A);
        input.jump = IsKeyDown(KEY_SPACE);
        input.attack = IsKeyDown(KEY_K);

        camera.target = {player.getRenderPosition().x, (float)(ctx.screenHeight / 2)};

        background.Update(deltaTime);
        level.Update(deltaTime, input);

        BeginDrawing();
        ClearBackground(WHITE);

        background.Draw();

        ui.Draw();

        BeginMode2D(camera);

        level.Draw();

        EndMode2D();
        EndDrawing();
    }

    CloseWindow();
    Anemy::UnloadTextures();
    return 0;
}
