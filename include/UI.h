#pragma once
#include "../include/Player.h"
#include <iostream>
#include <raylib.h>

class UI
{
private:
    int allDiamonds = 0;
    Player &player;

    Texture2D progressBar;

    Rectangle progressBarBorderRect;
    Rectangle progressBarProgressRect;

    int frameNumProgressBar = 2;

public:
    UI(int allDiamonds, Player &player) : allDiamonds(allDiamonds), player(player) {};
    ~UI();
    void LoadTextures();
    void Draw();
};
