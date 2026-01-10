#pragma once
#include "../include/Player.h"
#include "../include/AudioManager.h"
#include <iostream>
#include <raylib.h>

class UI
{
private:
    int allDiamonds = 0;
    Player &player;
    GameContext &ctx;
    AudioManager &audioManager;
    bool isMenuOpen = true;

    Vector2 mouse;

    Texture2D progressBar;
    Texture2D playBtn;
    Texture2D soundBtn;
    Texture2D soundBtnZero;
    Texture2D musicBtn;
    Texture2D musicBtnZero;

    Rectangle progressBarBorderRect;
    Rectangle progressBarProgressRect;

    Rectangle btnPlayHitbox;
    Rectangle btnSoundHitbox;
    Rectangle btnMusicHitbox;

    int frameNumProgressBar = 2;

    void DrawMenu();

public:
    UI(GameContext &ctx, AudioManager &audioManager, Player &player) : ctx(ctx), audioManager(audioManager), player(player) {};
    ~UI();
    void LoadTextures(int numOfAllDiamonds);
    void Draw();

    void menuOpen() { isMenuOpen = true; };
    void menuClose() { isMenuOpen = false; };

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
};
