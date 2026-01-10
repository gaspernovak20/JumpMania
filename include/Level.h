#pragma once
#include <string>
#include <vector>
#include <string>
#include "../include/GameContext.h"
#include "../include/Player.h"
#include "../include/Anemy.h"
#include "../include/AudioManager.h"

using namespace std;

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

    int frameNumDiamond = 8;

    Rectangle dimondRec;

    int dimondRecIndex = 0;
    float dimondTime = 0.0f;

public:
    Level(string levelName, GameContext &ctx, AudioManager &audioManager, Player &player)
        : levelName(levelName), ctx(ctx), audioManager(audioManager), player(player) {};
    ~Level();
    void LoadTextures();
    void Draw();
    void Update(float dt, InputState input);
    void loadLevel(string levelName);
    bool isSolid(int x, int y);
    bool checkCollision(Rectangle &rec);
    bool isDiamond(int x, int y);
    bool checkIfDiamondCollected(const Rectangle &rec);
    bool aabbCollision(const Rectangle &a, const Rectangle &b);

    int getNumOfAllDiamonds()
    {
        return numberOfDiamonds;
    }
};