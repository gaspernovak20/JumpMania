#include <iostream>
#include "include/UI.h"
#include "include/InputState.h"

UI::~UI()
{
    UnloadTexture(progressBar);
}
void UI::LoadTextures(int numOfAllDiamonds)
{
    allDiamonds = numOfAllDiamonds;

    progressBar = LoadTexture("../assets/ui/ProgressBarR.png");
    playBtn = LoadTexture("../assets/ui/PlayBTN.png");
    soundBtn = LoadTexture("../assets/ui/BTN/BTN_Basic/Sound_BTN.png");
    soundBtnZero = LoadTexture("../assets/ui/BTN/BTN_Active/Sound_BTN.png");
    musicBtn = LoadTexture("../assets/ui/BTN/BTN_Basic/Music_BTN.png");
    musicBtnZero = LoadTexture("../assets/ui/BTN/BTN_Active/Music_BTN.png");

    progressBarBorderRect = {0.f, 0.f, (float)progressBar.width, (float)progressBar.height / frameNumProgressBar};
    progressBarProgressRect = {0.f, (float)progressBar.height / frameNumProgressBar, (float)progressBar.width, (float)progressBar.height / frameNumProgressBar};

    btnPlayHitbox = {ctx.screenWidth / 2 - playBtn.width / 2, ctx.screenHeight / 2 - playBtn.height / 2, (float)playBtn.width, (float)playBtn.height};
    btnSoundHitbox = {ctx.screenWidth - 70, 20, (float)soundBtn.width, (float)soundBtn.height};
    btnMusicHitbox = {ctx.screenWidth - 70, 70, (float)musicBtn.width, (float)musicBtn.height};
}

void UI::Draw()
{
    progressBarProgressRect.width = progressBar.width * ((float)player.getNumOfCollectedDiamonds() / (float)allDiamonds);
    DrawTextureRec(progressBar, progressBarProgressRect, {(float)(40), (float)(13)}, WHITE);
    DrawTextureRec(progressBar, progressBarBorderRect, {(float)(40), (float)(13)}, WHITE);

    progressBarProgressRect.width = progressBar.width * max(0.0, (player.getHealthPoints() / 100.0));
    DrawTextureRec(progressBar, progressBarProgressRect, {(float)(40), (float)(53)}, RED);
    DrawTextureRec(progressBar, progressBarBorderRect, {(float)(40), (float)(53)}, RED);

    if (isMenuOpen)
    {
        DrawMenu();
    }
}

void UI::DrawMenu()
{
    DrawRectangle(0, 0, ctx.screenWidth, ctx.screenHeight, Fade(BLACK, 0.5f));
    DrawTexture(playBtn, ctx.screenWidth / 2 - playBtn.width / 2, ctx.screenHeight / 2 - playBtn.height / 2, WHITE);

    if (audioManager.getSoundVolume() <= 0.0)
        DrawTexture(soundBtnZero, ctx.screenWidth - 70, 20, WHITE);
    else
        DrawTexture(soundBtn, ctx.screenWidth - 70, 20, WHITE);

    if (audioManager.isMusicPlaying())
        DrawTexture(musicBtn, ctx.screenWidth - 70, 70, WHITE);
    else
        DrawTexture(musicBtnZero, ctx.screenWidth - 70, 70, WHITE);
}