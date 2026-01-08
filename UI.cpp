#include <iostream>
#include "include/UI.h"

UI::~UI()
{
    UnloadTexture(progressBar);
}
void UI::LoadTextures()
{
    progressBar = LoadTexture("../assets/ProgressBarR.png");

    progressBarBorderRect = {0.f, 0.f, (float)progressBar.width, (float)progressBar.height / frameNumProgressBar};
    progressBarProgressRect = {0.f, (float)progressBar.height / frameNumProgressBar, (float)progressBar.width, (float)progressBar.height / frameNumProgressBar};
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
