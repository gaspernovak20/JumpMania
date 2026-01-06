#include <iostream>
#include <fstream>
#include <vector>

#include "raylib.h"
#include "include/Level.h"
#include "include/GameContext.h"
#include "include/InputState.h"

using namespace std;

Level::~Level()
{
    UnloadTexture(grassTexture);
    UnloadTexture(dirtBlock);
}

void Level::LoadTextures()
{
    numberOfDiamonds = 0;
    loadLevel(levelName);

    grassTexture = LoadTexture("../assets/GrasBlock.png");
    dirtBlock = LoadTexture("../assets/DirtBlock.png");
    diamond = LoadTexture("../assets/Diamond.png");

    dimondRec = {0.f, 0.f, (float)diamond.width / frameNumDiamond, (float)diamond.height};

    for (int i = 0; i < levelHeight; i++)
    {
        for (int j = 0; j < levelWidth; j++)
        {
            if (level[i][j] == '!')
            {
                Vector2 spawnPos = {
                    j * ctx.tileSize,
                    i * ctx.tileSize - ctx.tileSize};

                anemies.emplace_back("FireSpirit", spawnPos);

                level[i][j] = ' ';
            }
        }
    }
};

void Level::Draw()
{

    for (int i = 0; i < levelHeight; i++)
    {
        for (int j = 0; j < levelWidth; j++)
        {
            if (level[i][j] == '#')
            {
                DrawTexturePro(grassTexture, {0.0f, 0.0f, (float)grassTexture.width, (float)grassTexture.height},
                               {(float)(j * ctx.tileSize), (float)(i * ctx.tileSize), (float)ctx.tileSize, (float)ctx.tileSize},
                               {0.0f, 0.0f}, 0.0f, WHITE);
            }
            else if (level[i][j] == '=')
            {
                DrawTexturePro(dirtBlock, {0.0f, 0.0f, (float)dirtBlock.width, (float)dirtBlock.height},
                               {(float)(j * ctx.tileSize), (float)(i * ctx.tileSize), (float)ctx.tileSize, (float)ctx.tileSize},
                               {0.0f, 0.0f}, 0.0f, WHITE);
            }
            else if (level[i][j] == '*')
            {
                DrawTextureRec(diamond, dimondRec, {(float)(j * ctx.tileSize), (float)(i * ctx.tileSize)}, WHITE);
            }
        }
    }

    player.Draw();

    for (Anemy &anemy : anemies)
    {
        if (anemy.isAlive)
        {
            anemy.Draw();
        }
    }
};

void Level::Update(float dt, InputState input)
{
    player.Update(dt, input);

    Vector2 playerNextPos = player.getNextPosition(dt);

    // X axis
    Rectangle hitX = player.getHitboxAt({playerNextPos.x, player.getPosition().y});
    if (!checkCollision(hitX))
    {
        player.applyPosition({playerNextPos.x, player.getPosition().y});
    }

    // Y axis
    Rectangle hitY = player.getHitboxAt({player.getPosition().x, playerNextPos.y});
    if (!checkCollision(hitY))
    {
        player.applyPosition({player.getPosition().x, playerNextPos.y});
        player.setGrounded(false);
    }
    else
    {
        if (player.getVelocity().y > 0)
            player.setGrounded(true);
        player.stopVerticalVelocity();
    }

    // Diamond collected
    if (checkIfDiamondCollected(player.getHitbox()))
    {
        player.diamondCollected();
    }

    for (Anemy &anemy : anemies)
    {
        if (!anemy.isAlive)
        {
            continue;
        }

        if (anemy.getAnemyState() == ANEMY_STATE_CHARGE &&
            !anemy.hasHit() &&
            aabbCollision(anemy.getHitbox(), player.getHitbox()) &&
            player.getPlayerState() != STATE_DEFEND)
        {
            player.takeDamage(anemy.getAttackDamage());
            anemy.markHit();
        }

        anemy.Update(dt, player.getPosition(), player.getHitbox());

        Vector2 anemyNextPos = anemy.getNextPosition(dt);

        // X axis
        hitX = anemy.getHitboxAt({anemyNextPos.x, anemy.getPosition().y});
        if (!checkCollision(hitX))
        {
            anemy.applyPosition({anemyNextPos.x, anemy.getPosition().y});
        }
    }

    dimondTime += dt;
    if (dimondTime >= 0.1f)
    {
        dimondTime = 0;
        dimondRecIndex = (dimondRecIndex + 1) % 8;
    }
    dimondRec.x = dimondRec.width * dimondRecIndex;
};

void Level::loadLevel(string levelName)
{
    ifstream inFile(levelName);

    if (!inFile.is_open())
    {
        cerr << "Unable to open file datafile.txt";
        exit(1); // call system to stop
    }

    string line;
    while (getline(inFile, line))
    {
        numberOfDiamonds += count(line.begin(), line.end(), '*');
        level.insert(level.end(), line);
    }

    if (!level.empty())
    {
        levelHeight = level.size();
        levelWidth = level[0].size();
    }
}

bool Level::isSolid(int x, int y)
{
    if (x < 0 || y < 0 || levelWidth <= x || levelHeight <= y)
    {
        return true;
    }

    return level[y][x] == '#' || level[y][x] == '=';
}

bool Level::isDiamond(int x, int y)
{
    if (level[y][x] == '*')
    {
        level[y][x] = ' ';
        return true;
    }
    return false;
}

bool Level::checkCollision(Rectangle &rec)
{
    const int left = rec.x / ctx.tileSize;
    const int top = rec.y / ctx.tileSize;
    const int right = (rec.x + rec.width - 1) / ctx.tileSize;
    const int bottom = (rec.y + rec.height - 1) / ctx.tileSize;

    return isSolid(left, top) || isSolid(right, top) || isSolid(left, bottom) || isSolid(right, bottom);
}

bool Level::checkIfDiamondCollected(const Rectangle &rec)
{

    const int left = rec.x / ctx.tileSize;
    const int top = rec.y / ctx.tileSize;
    const int right = (rec.x + rec.width - 1) / ctx.tileSize;
    const int bottom = (rec.y + rec.height - 1) / ctx.tileSize;

    return isDiamond(left, top) || isDiamond(right, top) || isDiamond(left, bottom) || isDiamond(right, bottom);
}

bool Level::aabbCollision(const Rectangle &a, const Rectangle &b)
{
    return (
        a.x < b.x + b.width &&
        a.x + a.width > b.x &&
        a.y < b.y + b.height &&
        a.y + a.height > b.y);
}
