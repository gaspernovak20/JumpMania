#pragma once
#include <string>
#include <vector>
#include <string>

#include "raylib.h"
#include "../include/GameContext.h"

using namespace std;

class Background
{
private:
    GameContext &ctx;

    Texture2D background;
    Texture2D cloud1;
    Texture2D cloud2;

    float cloud1Speed = 20.0f;
    float cloud2Speed = 28.0f;
    float cloud3Speed = 23.0f;

    Vector2 cloud1Pos = {100, 30};
    Vector2 cloud2Pos = {300, 307};
    Vector2 cloud1Pos1 = {400, 205};
    Vector2 cloud2Pos1 = {200, 105};

public:
    Background(GameContext &ctx)
        : ctx(ctx) {};
    ~Background();
    void LoadTextures();
    void Draw();
    void Update(float dt);
};