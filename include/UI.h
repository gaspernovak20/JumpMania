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

    bool isMenuOpen = true;

    Vector2 mouse;

    Texture2D progressBar;
    Texture2D buttonPlay;

    Rectangle progressBarBorderRect;
    Rectangle progressBarProgressRect;

    Rectangle buttonPlayHitbox;

    int frameNumProgressBar = 2;

    void DrawMenu();

public:
    UI(GameContext &ctx, Player &player) : ctx(ctx), player(player) {};
    ~UI();
    void LoadTextures(int numOfAllDiamonds);
    void Draw();
    Rectangle getButtonPlayHitbox()
    {
        return buttonPlayHitbox;
    }
    void menuOpen() { isMenuOpen = true; };
    void menuClose() { isMenuOpen = false; };
};
