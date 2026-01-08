#pragma once
#include "../include/Player.h"
#include <iostream>
#include <raylib.h>

class UI
{
private:
    int allDiamonds = 0;
    Player &player;
    GameContext &ctx;

    Texture2D progressBar;
    Texture2D buttonPlay;

    Rectangle progressBarBorderRect;
    Rectangle progressBarProgressRect;

    Rectangle buttonPlayHitbox;

    int frameNumProgressBar = 2;

public:
    UI(GameContext &ctx, int allDiamonds, Player &player) : ctx(ctx), allDiamonds(allDiamonds), player(player) {};
    ~UI();
    void LoadTextures();
    void Draw();
    void DrawPlayButton();
    void DrawBlurredMap();
    Rectangle getButtonPlayHitbox()
    {
        return buttonPlayHitbox;
    }
};
