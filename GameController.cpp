#include "raylib.h"
#include "include/Player.h"
#include "include/InputState.h"
#include "include/Level.h"
#include "include/Background.h"
#include "include/UI.h"
#include "include/GameContext.h"
#include "include/GameController.h"
#include "include/GameState.h"
#include "include/AudioManager.h"
#include <filesystem>
#include <cmath>
using namespace std;

InputState input;

void GameController::Initialize()
{
    Anemy::LoadTextures();
    background.LoadTextures();
    level.LoadTextures();
    ui.LoadTextures(level.getNumOfAllDiamonds());
    audioManager.Initial();
    audioManager.ApplySettings(settings);
    currentState = GameState::TITLE;

    gameTime = 0.0;

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

    if (player.getHealthPoints() <= 0)
    {
        gameTime = 0;
        player.setHealthPoints(100);
        player.setNumOfCollectedDiamonds(0);
        level.LoadTextures();
        player.setPosition({ctx.tileSize * 5, 296});
        currentState = GameState::MENU;
    }

    if (currentState == GameState::TITLE)
    {
        if (CheckCollisionPointRec(mouse, ui.getFighterHitbox()) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            player.LoadTextures("Fighter");
            currentState = GameState::MENU;
        }
        else if (CheckCollisionPointRec(mouse, ui.getSamuraiHitbox()) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            player.LoadTextures("Samurai");
            currentState = GameState::MENU;
        }
    }

    if (currentState == GameState::PLAYING)
    {
        gameTime += dt;
        if (input.pouse)
        {
            currentState = GameState::MENU;
        }
        else
        {
            level.Update(dt, input, currentState);
        }
    }
    else if (currentState == GameState::MENU)
    {

        if (CheckCollisionPointRec(mouse, ui.getButtonPlayHitbox()) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            currentState = GameState::PLAYING;
        }
        else if (CheckCollisionPointRec(mouse, ui.getButtonSoundHitbox()) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            audioManager.changeSoundState();
        }
        else if (CheckCollisionPointRec(mouse, ui.getButtonMusicHitbox()) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            audioManager.changeMusicState();
        }
    }
    else if (currentState == GameState::FINISH)
    {

        if (CheckCollisionPointRec(mouse, ui.getButtonRestartHitbox()) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            gameTime = 0;
            player.setHealthPoints(100);
            player.setNumOfCollectedDiamonds(0);
            level.LoadTextures();
            player.setPosition({ctx.tileSize * 5, 296});
            currentState = GameState::MENU;
        }
    }

    background.Update(dt);
    audioManager.Update();
}

void GameController::Draw()
{

    background.Draw();

    BeginMode2D(camera);

    level.Draw();

    EndMode2D();

    ui.Draw(currentState, gameTime);
}

void GameController::OnWindowResized(int screenWidth, int screenHeight)
{
    ctx.screenWidth = screenWidth;
    ctx.screenHeight = screenHeight;
}