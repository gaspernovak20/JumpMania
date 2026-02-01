#pragma once
#include "../include/Player.h"
#include "../include/AudioManager.h"
#include "../include/GameState.h"
#include <iostream>
#include <raylib.h>

class UI
{
private:
    int allDiamonds = 0;
    Player &player;
    GameContext &ctx;
    AudioManager &audioManager;

    Vector2 mouse;

    Texture2D titleScreen;
    Texture2D progressBar;
    Texture2D playBtn;
    Texture2D restartBtn;
    Texture2D soundBtn;
    Texture2D soundBtnZero;
    Texture2D musicBtn;
    Texture2D musicBtnZero;
    Texture2D star1;
    Texture2D star2;
    Texture2D star3;
    Texture2D fighterPlayer;
    Texture2D samuraiPlayer;

    Rectangle progressBarBorderRect;
    Rectangle progressBarProgressRect;

    Rectangle btnPlayHitbox;
    Rectangle btnRestartHitbox;
    Rectangle btnSoundHitbox;
    Rectangle btnMusicHitbox;
    Rectangle samuraiHitbox;
    Rectangle fighterHitbox;

    int frameNumProgressBar = 2;

    void DrawMenu();
    void DrawFinishMenu(float gameTime);
    void DrawTitleMenu();

public:
    UI(GameContext &ctx, AudioManager &audioManager, Player &player) : ctx(ctx), audioManager(audioManager), player(player) {};
    ~UI();
    void LoadTextures(int numOfAllDiamonds);
    void Draw(GameState &gameState, float gameTime);

    Rectangle getButtonPlayHitbox()
    {
        return btnPlayHitbox;
    }

    Rectangle getButtonSoundHitbox()
    {
        return btnSoundHitbox;
    }

    Rectangle getButtonMusicHitbox()
    {
        return btnMusicHitbox;
    }

    Rectangle getButtonRestartHitbox()
    {
        return btnRestartHitbox;
    }

    Rectangle getSamuraiHitbox()
    {
        return samuraiHitbox;
    }

    Rectangle getFighterHitbox()
    {
        return fighterHitbox;
    }
};
