#include <iostream>
#include <string>
#include <vector>

#include "include/Player.h"
#include "include/InputState.h"
#include "include/GameContext.h"
#include "include/Anemy.h"

using namespace std;

Player::Player(Vector2 position, GameContext &ctx) : position(position), ctx(ctx) {};

Player::~Player()
{
    UnloadTexture(spriteIdle);
    UnloadTexture(spriteWalk);
    UnloadTexture(spriteJump);
    UnloadTexture(spriteAttack1);
}

void Player::LoadTextures()
{
    spriteIdle = LoadTexture("../assets/player/Idle.png");
    spriteWalk = LoadTexture("../assets/player/Walk.png");
    spriteJump = LoadTexture("../assets/player/Jump.png");
    spriteAttack1 = LoadTexture("../assets/player/Attack_1.png");

    frameNumIdle = 6;
    frameNumWalk = 8;
    frameNumJump = 12;
    frameNumAttack1 = 6;

    frameRecIdle = {0.f, 0.f, (float)spriteIdle.width / frameNumIdle, (float)spriteIdle.height};
    frameRecWalk = {0.f, 0.f, (float)spriteWalk.width / frameNumWalk, (float)spriteWalk.height};
    frameRecJump = {0.f, 0.f, (float)spriteJump.width / frameNumJump, (float)spriteJump.height};
    frameRecAttack1 = {0.f, 0.f, (float)spriteAttack1.width / frameNumAttack1, (float)spriteAttack1.height};

    int frameWidth = frameRecWalk.width;
    int frameWidthJump = frameRecJump.width;
}

void Player::Draw()
{

    switch (playerState)
    {
    case STATE_WALK:
        DrawTextureRec(spriteWalk, (facingRight ? frameRecWalk : Rectangle{frameRecWalk.x, 0, -frameRecWalk.width, frameRecWalk.height}), position, WHITE);
        break;
    case STATE_JUMP:
        DrawTextureRec(spriteJump, (facingRight ? frameRecJump : Rectangle{frameRecJump.x, 0, -frameRecJump.width, frameRecJump.height}), position, WHITE);
        break;
    case STATE_ATTACK:
        DrawTextureRec(spriteAttack1, (facingRight ? frameRecAttack1 : Rectangle{frameRecAttack1.x, 0, -frameRecAttack1.width, frameRecAttack1.height}), position, WHITE);
        DrawRectangleLines(attackHitBox.x, attackHitBox.y, attackHitBox.width, attackHitBox.height, GREEN);
        break;
    default:
        DrawTextureRec(spriteIdle, (facingRight ? frameRecIdle : Rectangle{frameRecIdle.x, 0, -frameRecIdle.width, frameRecIdle.height}), position, WHITE);
    }
    DrawRectangleLines(bodyHitBox.x, bodyHitBox.y, bodyHitBox.width, bodyHitBox.height, BLUE);
}

void Player::Update(float dt, const InputState &input)
{
    isWalking = false;
    isAttacking = false;

    // Horizontal movement
    if (input.moveRight)
    {
        velocity.x = SPEED;
        facingRight = true;
        isWalking = true;
    }
    else if (input.moveLeft)
    {
        velocity.x = -SPEED;
        facingRight = false;
        isWalking = true;
    }
    else
    {
        velocity.x = 0;
    }

    // Jump
    if (isGrounded && input.jump)
    {
        velocity.y = -JUMP_STRENGTH;
        isGrounded = false;
    }

    // Attack
    if (input.attack)
    {
        isAttacking = true;
    }

    // Gravity (vedno)
    velocity.y += dt * GRAVITY;

    if (isAttacking)
    {
        playerState = STATE_ATTACK;
        if (facingRight)
        {
            attackHitBox = {
                bodyHitBox.x + bodyHitBox.width,
                bodyHitBox.y + 25,
                35,
                30};
        }
        else
        {
            attackHitBox = {
                bodyHitBox.x - 35,
                bodyHitBox.y + 25,
                35,
                30};
        }
    }
    else if (!isGrounded)
    {
        playerState = STATE_JUMP;
    }
    else if (isWalking)
    {
        playerState = STATE_WALK;
    }
    else
    {
        playerState = STATE_IDLE;
    }

    if (playerState == STATE_IDLE)
    {
        idleTime += dt;
        if (idleTime >= 0.1f)
        {
            idleTime = 0.0f;
            idleFrameIndex = (idleFrameIndex + 1) % frameNumIdle;
        }
        frameRecIdle.x = frameRecIdle.width * idleFrameIndex;
    }

    if (playerState == STATE_WALK && isGrounded)
    {
        walkTimer += dt;
        if (walkTimer >= 0.1f)
        {
            walkTimer = 0.0f;
            walkFrameIndex = (walkFrameIndex + 1) % frameNumWalk;
        }
        frameRecWalk.x = frameRecWalk.width * walkFrameIndex;
    }
    if (playerState == STATE_JUMP)
    {
        jumpTimer += dt;
        if (jumpTimer >= 0.2f)
        {
            jumpTimer = 0.0f;
            jumpFrameIndex = (jumpFrameIndex + 1) % frameNumJump;
        }
        frameRecJump.x = frameRecJump.width * jumpFrameIndex;
    }
    if (playerState == STATE_ATTACK)
    {
        attackTimer += dt;
        if (attackTimer > 0.09f)
        {
            attackTimer = 0.0f;
            attackFrameIndex++;
            if (attackFrameIndex > frameNumAttack1)
            {
                playerState = STATE_IDLE;
                isAttacking = false;
                attackFrameIndex = 0;
            }
        }
        frameRecAttack1.x = frameRecAttack1.width * attackFrameIndex;
    }
}

void Player::applyPosition(Vector2 pos)
{
    position = pos;

    bodyHitBox = getHitboxAt(position);
};

void Player::stopVerticalVelocity()
{
    velocity.y = 0;
}

void Player::diamondCollected()
{
    numOfCollectedDiamonds++;
}

void Player::takeDamage(float damage)
{
    healthPoints -= damage;
}
