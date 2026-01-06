#include <iostream>

#include "raylib.h"
#include "include/Background.h"
using namespace std;

Background::~Background()
{
    UnloadTexture(background);
    UnloadTexture(cloud1);
    UnloadTexture(cloud2);
}

void Background::LoadTextures()
{
    background = LoadTexture("../assets/background.png");
    cloud1 = LoadTexture("../assets/Cloud1Background.png");
    cloud2 = LoadTexture("../assets/Cloud2Background.png");
};

void Background::Draw()
{
    DrawTexturePro(background, {0.0f, 0.0f, (float)background.width, (float)background.height},
                   {0.0f, 0.0f, (float)ctx.screenWidth, (float)ctx.screenHeight}, {0.0f, 0.0f}, 0.0f, WHITE);
    DrawTexture(cloud1, (int)cloud1Pos.x, (int)cloud1Pos.y, WHITE);
    DrawTexture(cloud2, (int)cloud2Pos.x, (int)cloud2Pos.y, WHITE);
    DrawTexture(cloud1, (int)cloud1Pos1.x, (int)cloud1Pos1.y, WHITE);
    DrawTexture(cloud2, (int)cloud2Pos1.x, (int)cloud2Pos1.y, WHITE);
};

void Background::Update(float dt)
{
    // Move clouds
    cloud1Pos.x += cloud1Speed * dt;
    cloud1Pos1.x += cloud2Speed * dt;
    cloud2Pos.x -= cloud2Speed * dt;
    cloud2Pos1.x -= cloud3Speed * dt;

    if (cloud1Pos.x > ctx.screenWidth)
        cloud1Pos.x = -cloud1.width;
    if (cloud1Pos1.x > ctx.screenWidth)
        cloud1Pos1.x = -cloud1.width;
    if (cloud2Pos.x < -cloud2.width)
        cloud2Pos.x = ctx.screenWidth;
    if (cloud2Pos1.x < -cloud2.width)
        cloud2Pos1.x = ctx.screenWidth;
}