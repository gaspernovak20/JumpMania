#pragma once
#include <string>
#include <vector>
#include <string>
#include "../include/GameContext.h"
#include "../include/Player.h"
#include "../include/Anemy.h"
#include "../include/AudioManager.h"
#include "../include/GameState.h"

using namespace std;

static constexpr float CHECKPOINT_WIDTH = 30.0f;
static constexpr float CHECKPOINT_HEIGHT = 50.0f;
static constexpr float CHECKPOINT_OFFSET_X = 3306.0f;
static constexpr float CHECKPOINT_OFFSET_Y = 328.0f;

class Level
{
private:
    GameContext &ctx;
    Player &player;
    AudioManager &audioManager;

    vector<Anemy> anemies;

    vector<string> level;
    string levelName;

    int levelHeight;
    int levelWidth;
    int numberOfDiamonds;

    Texture2D grassTexture;
    Texture2D dirtBlock;
    Texture2D diamond;
    Texture2D checkPointIdle;

    int frameNumDiamond = 8;
    int frameNumCheckPointIdle = 10;

    Rectangle dimondRec;
    Rectangle checkPointIdleRec;

    Rectangle checkPointHitbox;

    int dimondRecIndex = 0;
    int checkPointIdleRecIndex = 0;

    float dimondTime = 0.0f;
    float checkPointIdleTime = 0.0f;

public:
    Level(string levelName, GameContext &ctx, AudioManager &audioManager, Player &player)
        : levelName(levelName), ctx(ctx), audioManager(audioManager), player(player) {};
    ~Level();
    void LoadTextures();
    void Draw();
    void Update(float dt, InputState input, GameState &gameState);
    void loadLevel(string levelName);
    bool isSolid(int x, int y);
    bool checkCollision(Rectangle &rec);
    bool isDiamond(int x, int y);
    bool isCheckpoint(int x, int y);
    bool checkIfCollected(bool (Level::*isSomething)(int, int), const Rectangle &rec);
    bool aabbCollision(const Rectangle &a, const Rectangle &b);

    int getNumOfAllDiamonds()
    {
        return numberOfDiamonds;
    }
};