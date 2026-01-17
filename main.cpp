#include "raylib.h"
#include "include/GameController.h"
#include <filesystem>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    InitWindow(800, 450, "Platformer with Camera");
    SetExitKey(KEY_NULL);
    InitAudioDevice();
    SetTargetFPS(120);

    Settings setting;
    SaveManager saveManager;

    saveManager.LoadData(setting);

    GameController game(setting);
    game.Initialize();
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (IsWindowResized())
        {
            game.OnWindowResized(GetScreenWidth(), GetScreenHeight());
        }

        game.Update(dt);

        BeginDrawing();
        ClearBackground(WHITE);
        game.Draw();
        EndDrawing();
    }

    saveManager.SaveData(setting);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
