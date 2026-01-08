#pragma once
#include "raylib.h"
#include "InputState.h"
#include "../include/GameContext.h"

#include <string>
#include <vector>
using namespace std;

#define SPEED 150.0f;
#define GRAVITY 900.0f;
#define JUMP_STRENGTH 450.0f;

static constexpr float BODY_WIDTH = 32.0f;
static constexpr float BODY_HEIGHT = 78.0f;
static constexpr float BODY_OFFSET_X = 48.0f;
static constexpr float BODY_OFFSET_Y = 50.0f;

typedef enum
{
    STATE_IDLE,
    STATE_WALK,
    STATE_JUMP,
    STATE_ATTACK,
    STATE_DEAD,
    STATE_SHIELD,
    STATE_HURT
} PlayerState;

class Anemy;

class Player
{
private:
    GameContext &ctx;
    Vector2 position;
    int healthPoints = 100;
    Vector2 velocity = {0.0f, 0.0f};
    bool isGrounded = false;
    bool isAttacking = false;
    bool isWalking = false;
    bool isDefending = false;
    bool facingRight = true;

    int numOfCollectedDiamonds = 0;

    PlayerState playerState = STATE_IDLE;

    Sound swordSound;
    Sound walkSound;
    Sound diamondSound;
    Sound hurtSound;

    Texture2D spriteIdle;
    Texture2D spriteWalk;
    Texture2D spriteJump;
    Texture2D spriteAttack1;
    Texture2D spriteDead;
    Texture2D spriteShield;
    Texture2D spriteHurt;

    int frameNumIdle;
    int frameNumWalk;
    int frameNumJump;
    int frameNumAttack1;
    int frameNumDead;
    int frameNumShield;
    int frameNumHurt;

    Rectangle frameRecIdle;
    Rectangle frameRecWalk;
    Rectangle frameRecJump;
    Rectangle frameRecAttack1;
    Rectangle frameRecDead;
    Rectangle frameRecShield;
    Rectangle frameRecHurt;

    int walkFrameIndex = 0;
    int jumpFrameIndex = 0;
    int attackFrameIndex = 0;
    int idleFrameIndex = 0;
    int deadFrameIndex = 0;
    int shieldFrameIndex = 0;
    int hurtFrameIndex = 0;

    float idleTime = 0.0f;
    float actionTime = 0.0f;
    float walkTimer = 0.0f;
    float attackTimer = 0.0f;
    float jumpTimer = 0.0f;
    float deadTimer = 0.0f;
    float shieldTimer = 0.0f;
    float hurtTimer = 0.0f;

    Rectangle bodyHitBox = {position.x + BODY_OFFSET_X, position.y + BODY_OFFSET_Y, BODY_WIDTH, BODY_HEIGHT};
    Rectangle attackHitBox;

public:
    Player(Vector2 position, GameContext &ctx);
    ~Player();

    bool isAlive = true;

    void LoadTextures();
    void Draw();
    void Update(float dt, const InputState &input);

    void applyPosition(Vector2 pos);
    void stopVerticalVelocity();
    void diamondCollected();
    void takeDamage(float damage);

    Vector2 getPosition()
    {
        return position;
    }

    Vector2 getVelocity()
    {
        return velocity;
    }

    int getNumOfCollectedDiamonds()
    {
        return numOfCollectedDiamonds;
    }

    int getHealthPoints()
    {
        return healthPoints;
    }

    Vector2 getRenderPosition() const
    {
        return {
            position.x + frameRecIdle.width / 2.0f,
            position.y};
    }

    Rectangle getHitboxAt(Vector2 pos)
    {
        return {
            pos.x + BODY_OFFSET_X,
            pos.y + BODY_OFFSET_Y,
            BODY_WIDTH,
            BODY_HEIGHT};
    };

    Rectangle getHitbox()
    {
        return bodyHitBox;
    }

    Vector2 getNextPosition(float dt)
    {
        return {
            position.x + velocity.x * dt,
            position.y + velocity.y * dt};
    };

    PlayerState getPlayerState()
    {
        return playerState;
    }

    void setGrounded(bool grounded)
    {
        isGrounded = grounded;
    }
};