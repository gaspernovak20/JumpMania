#pragma once
#include "raylib.h"
#include "../include/GameContext.h"
#include "../include/Player.h"
#include <string>
using namespace std;

static constexpr float ANEMY_BODY_WIDTH = 32.0f;
static constexpr float ANEMY_BODY_HEIGHT = 50.0f;
static constexpr float ANEMY_BODY_OFFSET_X = 48.0f;
static constexpr float ANEMY_BODY_OFFSET_Y = 50.0f;

constexpr float CHARGE_DISTANCE = 35.f;
constexpr float AGRO_DISTANCE = 250.f;
constexpr float RETURN_EPSILON = 2.0f;

constexpr float IDLE_FRAME_TIME = 0.1f;
constexpr float WALK_FRAME_TIME = 0.1f;
constexpr float CHARGE_FRAME_TIME = 0.05f;
constexpr float DEATH_FRAME_TIME = 0.2f;

constexpr float ATTACK_DAMAGE = 25.0f;

typedef enum
{
    ANEMY_STATE_IDLE,
    ANEMY_STATE_WALK,
    ANEMY_STATE_CHARGE,
    ANEMY_STATE_DEATH,
} AnemyState;

struct EnemyTextures
{
    Texture2D spriteIdle;
    Texture2D spriteWalk;
    Texture2D spriteCharge;
    Texture2D spriteDead;

    int frameNumIdle;
    int frameNumWalk;
    int frameNumCharge;
    int frameNumDead;

    Rectangle frameRecIdle;
    Rectangle frameRecWalk;
    Rectangle frameRecCharge;
    Rectangle frameRecDead;
};

class Anemy
{
private:
    string name;
    Vector2 originPosition;
    Vector2 position;
    int healthPoints = 100;

    Vector2 velocity = {0.0f, 0.0f};
    const float speed = 100.f;

    bool isDying = false;
    bool hountingPlayer = false;
    bool facingRight = true;
    bool hasHitPlayer = false;

    AnemyState anemyState = ANEMY_STATE_IDLE;

    static EnemyTextures anemyTexture;

    float idleTimer = 0.0f;
    float walkTimer = 0.0f;
    float chargeTimer = 0.0f;
    float deadTimer = 0.0f;

    int idleFrameIndex = 0;
    int walkFrameIndex = 0;
    int chargeFrameIndex = 0;
    int deadFrameIndex = 0;

    Rectangle bodyHitBox;
    void moveTo(Vector2 toPosition, float dt);
    void updateState(float distanceFromPlayer);
    float getHorizontalDistanceFromPlayer(const Rectangle &playerPos);

public:
    bool isAlive = true;

    Anemy(string name, Vector2 position);
    static void LoadTextures();
    static void UnloadTextures();
    void Draw();
    void Update(float dt, const Vector2 playerPos, const Rectangle playerHitbox);
    void takeDamage(int damage);
    void applyPosition(Vector2 pos);

    Rectangle getHitboxAt(Vector2 pos)
    {
        return {
            pos.x + ANEMY_BODY_OFFSET_X,
            pos.y + ANEMY_BODY_OFFSET_Y,
            ANEMY_BODY_WIDTH,
            ANEMY_BODY_HEIGHT};
    };

    Rectangle getHitbox()
    {
        return bodyHitBox;
    }

    Vector2 getPosition()
    {
        return position;
    }

    Vector2 getNextPosition(float dt)
    {
        return {
            position.x + velocity.x * dt,
            position.y};
    };

    AnemyState getAnemyState()
    {
        return anemyState;
    }

    float getAttackDamage()
    {
        return ATTACK_DAMAGE;
    }

    bool hasHit()
    {
        return hasHitPlayer;
    }

    void markHit()
    {
        hasHitPlayer = true;
    }
};