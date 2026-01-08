#include <iostream>
#include "include/UI.h"
#include "include/InputState.h"

UI::~UI()
{
    UnloadTexture(progressBar);
}
void UI::LoadTextures()
{
    progressBar = LoadTexture("../assets/ui/ProgressBarR.png");
    buttonPlay = LoadTexture("../assets/ui/buttonPlay.png");

    progressBarBorderRect = {0.f, 0.f, (float)progressBar.width, (float)progressBar.height / frameNumProgressBar};
    progressBarProgressRect = {0.f, (float)progressBar.height / frameNumProgressBar, (float)progressBar.width, (float)progressBar.height / frameNumProgressBar};

    buttonPlayHitbox = {ctx.screenWidth / 2 - buttonPlay.width / 2, ctx.screenHeight / 2 - buttonPlay.height / 2, (float)buttonPlay.width, (float)buttonPlay.height};
}

void UI::Draw()
{
    progressBarProgressRect.width = progressBar.width * ((float)player.getNumOfCollectedDiamonds() / (float)allDiamonds);
    DrawTextureRec(progressBar, progressBarProgressRect, {(float)(40), (float)(13)}, WHITE);
    DrawTextureRec(progressBar, progressBarBorderRect, {(float)(40), (float)(13)}, WHITE);

    progressBarProgressRect.width = progressBar.width * max(0.0, (player.getHealthPoints() / 100.0));
    DrawTextureRec(progressBar, progressBarProgressRect, {(float)(40), (float)(53)}, RED);
    DrawTextureRec(progressBar, progressBarBorderRect, {(float)(40), (float)(53)}, RED);
}

void UI::DrawPlayButton()
{
    DrawTexture(buttonPlay, ctx.screenWidth / 2 - buttonPlay.width / 2, ctx.screenHeight / 2 - buttonPlay.height / 2, WHITE);
}