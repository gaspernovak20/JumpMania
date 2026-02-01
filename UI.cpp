#include <iostream>
#include "include/UI.h"
#include "include/InputState.h"
#include "include/GameState.h"

UI::~UI()
{
    UnloadTexture(fighterPlayer);
    UnloadTexture(samuraiPlayer);
    UnloadTexture(titleScreen);
    UnloadTexture(progressBar);
    UnloadTexture(playBtn);
    UnloadTexture(restartBtn);
    UnloadTexture(soundBtn);
    UnloadTexture(soundBtnZero);
    UnloadTexture(musicBtn);
    UnloadTexture(musicBtnZero);
    UnloadTexture(star1);
    UnloadTexture(star2);
    UnloadTexture(star3);
}
void UI::LoadTextures(int numOfAllDiamonds)
{
    allDiamonds = numOfAllDiamonds;

    fighterPlayer = LoadTexture("../assets/player/Fighter/Fighter.png");
    samuraiPlayer = LoadTexture("../assets/player/Samurai/Samurai.png");
    titleScreen = LoadTexture("../assets/ui/titleScreen.jpeg");
    progressBar = LoadTexture("../assets/ui/ProgressBarR.png");
    playBtn = LoadTexture("../assets/ui/PlayBTN.png");
    restartBtn = LoadTexture("../assets/ui/BTN/BTN_Basic/Replay_BTN.png");
    soundBtn = LoadTexture("../assets/ui/BTN/BTN_Basic/Sound_BTN.png");
    soundBtnZero = LoadTexture("../assets/ui/BTN/BTN_Active/Sound_BTN.png");
    musicBtn = LoadTexture("../assets/ui/BTN/BTN_Basic/Music_BTN.png");
    musicBtnZero = LoadTexture("../assets/ui/BTN/BTN_Active/Music_BTN.png");
    star1 = LoadTexture("../assets/ui/Star_01.png");
    star2 = LoadTexture("../assets/ui/Star_02.png");
    star3 = LoadTexture("../assets/ui/Star_03.png");

    progressBarBorderRect = {0.f, 0.f, (float)progressBar.width, (float)progressBar.height / frameNumProgressBar};
    progressBarProgressRect = {0.f, (float)progressBar.height / frameNumProgressBar, (float)progressBar.width, (float)progressBar.height / frameNumProgressBar};

    btnPlayHitbox = {ctx.screenWidth / 2 - playBtn.width / 2, ctx.screenHeight / 2 - playBtn.height / 2, (float)playBtn.width, (float)playBtn.height};
    btnRestartHitbox = {ctx.screenWidth / 2 - restartBtn.width / 2, ctx.screenHeight / 2 - restartBtn.height / 2 + 150, (float)restartBtn.width, (float)restartBtn.height};
    btnSoundHitbox = {ctx.screenWidth - 70, 20, (float)soundBtn.width, (float)soundBtn.height};
    btnMusicHitbox = {ctx.screenWidth - 70, 70, (float)musicBtn.width, (float)musicBtn.height};

    samuraiHitbox = {ctx.screenWidth / 2 + 50,
                     ctx.screenHeight / 2,
                     (float)samuraiPlayer.width,
                     (float)samuraiPlayer.height};

    fighterHitbox = {ctx.screenWidth / 2 - fighterPlayer.width - 50,
                     ctx.screenHeight / 2,
                     (float)fighterPlayer.width,
                     (float)fighterPlayer.height};
}

void UI::Draw(GameState &gameState, float gameTime)
{
    int minutes = (int)gameTime / 60;
    int seconds = (int)gameTime % 60;

    char timeText[32];
    snprintf(timeText, sizeof(timeText), "%02d:%02d", minutes, seconds);

    DrawText(timeText, ctx.screenWidth / 2 - 20, 20, 24, BLACK);

    progressBarProgressRect.width = progressBar.width * ((float)player.getNumOfCollectedDiamonds() / (float)allDiamonds);
    DrawTextureRec(progressBar, progressBarProgressRect, {(float)(40), (float)(13)}, WHITE);
    DrawTextureRec(progressBar, progressBarBorderRect, {(float)(40), (float)(13)}, WHITE);

    progressBarProgressRect.width = progressBar.width * max(0.0, (player.getHealthPoints() / 100.0));
    DrawTextureRec(progressBar, progressBarProgressRect, {(float)(40), (float)(53)}, RED);
    DrawTextureRec(progressBar, progressBarBorderRect, {(float)(40), (float)(53)}, RED);

    if (gameState == GameState::TITLE)
    {
        DrawTitleMenu();
    }
    if (gameState == GameState::MENU)
    {
        DrawMenu();
    }
    else if (gameState == GameState::FINISH)
    {
        DrawFinishMenu(gameTime);
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

void UI::DrawFinishMenu(float gameTime)
{
    DrawRectangle(0, 0, ctx.screenWidth, ctx.screenHeight, Fade(BLACK, 0.5f));
    if (gameTime < 25.0f && ((float)player.getNumOfCollectedDiamonds() / (float)allDiamonds > 0.8))
    {
        DrawTexture(star3, ctx.screenWidth / 2 - star1.width / 2, ctx.screenHeight / 2 - restartBtn.height / 2 - 50, WHITE);
    }
    else if (gameTime < 35.0f && ((float)player.getNumOfCollectedDiamonds() / (float)allDiamonds > 0.5))
    {
        DrawTexture(star2, ctx.screenWidth / 2 - star1.width / 2, ctx.screenHeight / 2 - restartBtn.height / 2 - 50, WHITE);
    }
    else
    {
        DrawTexture(star1, ctx.screenWidth / 2 - star1.width / 2, ctx.screenHeight / 2 - restartBtn.height / 2 - 50, WHITE);
    }
    DrawTexture(restartBtn, ctx.screenWidth / 2 - restartBtn.width / 2, ctx.screenHeight / 2 - restartBtn.height / 2 + 150, WHITE);
}

void UI::DrawTitleMenu()
{
    DrawTexturePro(
        titleScreen,
        {0, 0, (float)titleScreen.width, (float)titleScreen.height}, // source
        {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},   // destination
        {0, 0},
        0.0f,
        WHITE);

    DrawTexture(fighterPlayer, ctx.screenWidth / 2 - fighterPlayer.width - 50, ctx.screenHeight / 2, WHITE);
    DrawTexture(samuraiPlayer, ctx.screenWidth / 2 + 50, ctx.screenHeight / 2, WHITE);

    char titleText[32];
    snprintf(titleText, sizeof(titleText), "Jump Mania");

    int fontSize = 50;
    int textWidth = MeasureText(titleText, fontSize);

    int x = ctx.screenWidth / 2 - textWidth / 2;
    int y = 30;

    DrawText(titleText, x, y, fontSize, BLACK);
}