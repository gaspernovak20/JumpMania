#include "raylib.h"
#include "include/Anemy.h"
#include "include/Player.h"
#include "include/InputState.h"
#include "include/Level.h"
#include "include/Background.h"
#include "include/UI.h"
#include "include/GameContext.h"
#include "include/GameController.h"
#include "include/GameState.h"
#include <filesystem>
#include <vector>
#include <cmath>
using namespace std;

InputState input;

void GameController::Initialize()
{
    Anemy::LoadTextures();
    background.LoadTextures();
    level.LoadTextures();
    player.LoadTextures();
    ui.LoadTextures(level.getNumOfAllDiamonds());
    currentState = GameState::MENU;

    camera = {0};
    camera.offset = {ctx.screenWidth / 2.0f, ctx.screenHeight / 2.0f};
    camera.zoom = 1.0f;
}

void GameController::Update(float dt)
{
    mouse = GetMousePosition();

    input.pouse = IsKeyDown(KEY_ESCAPE);
    input.moveRight = IsKeyDown(KEY_D);
    input.moveLeft = IsKeyDown(KEY_A);
    input.jump = IsKeyDown(KEY_SPACE);
    input.attack = IsKeyDown(KEY_K);
    input.shield = IsKeyDown(KEY_J);

    camera.target = {player.getRenderPosition().x, (float)(ctx.screenHeight / 2)};

    if (currentState == GameState::PLAYING)
    {
        if (input.pouse)
        {
            currentState = GameState::MENU;
            ui.menuOpen();
        }
        else
        {
            level.Update(dt, input);
        }
    }
    else if (currentState == GameState::MENU)
    {

        bool mouseOver = CheckCollisionPointRec(mouse, ui.getButtonPlayHitbox());

        if (mouseOver && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            currentState = GameState::PLAYING;
            ui.menuClose();
        }
    }

    background.Update(dt);
}

void GameController::Draw()
{

    background.Draw();

    BeginMode2D(camera);

    level.Draw();

    EndMode2D();

    ui.Draw();
}

void GameController::OnWindowResized(int screenWidth, int screenHeight)
{
    ctx.screenWidth = screenWidth;
    ctx.screenHeight = screenHeight;
}