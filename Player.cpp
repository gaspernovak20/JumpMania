#include <iostream>
#include <string>
#include <vector>

#include "include/Player.h"
#include "include/InputState.h"
#include "include/GameContext.h"
#include "include/AudioManager.h"
#include "include/Anemy.h"

using namespace std;

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
    spriteDead = LoadTexture("../assets/player/Dead.png");
    spriteHurt = LoadTexture("../assets/player/Hurt.png");
    spriteShield = LoadTexture("../assets/player/Hurt.png");

    frameNumIdle = 6;
    frameNumWalk = 8;
    frameNumJump = 12;
    frameNumAttack1 = 6;
    frameNumDead = 3;
    frameNumShield = 2;
    frameNumHurt = 2;

    frameRecIdle = {0.f, 0.f, (float)spriteIdle.width / frameNumIdle, (float)spriteIdle.height};
    frameRecWalk = {0.f, 0.f, (float)spriteWalk.width / frameNumWalk, (float)spriteWalk.height};
    frameRecJump = {0.f, 0.f, (float)spriteJump.width / frameNumJump, (float)spriteJump.height};
    frameRecAttack1 = {0.f, 0.f, (float)spriteAttack1.width / frameNumAttack1, (float)spriteAttack1.height};
    frameRecDead = {0.f, 0.f, (float)spriteDead.width / frameNumDead, (float)spriteDead.height};
    frameRecShield = {0.f, 0.f, (float)spriteShield.width / frameNumShield, (float)spriteShield.height};
    frameRecHurt = {0.f, 0.f, (float)spriteHurt.width / frameNumHurt, (float)spriteHurt.height};

    swordSound = LoadSound("../assets/sound/swordSound.mp3");
    walkSound = LoadSound("../assets/sound/walkingSound.mp3");
    diamondSound = LoadSound("../assets/sound/diamondSound.mp3");
    hurtSound = LoadSound("../assets/sound/hurtSound.mp3");

    audioManager.registerSfx(swordSound);
    audioManager.registerSfx(walkSound);
    audioManager.registerSfx(diamondSound);
    audioManager.registerSfx(hurtSound);
}

void Player::Draw()
{

    switch (playerState)
    {
    case STATE_DEAD:
        DrawTextureRec(spriteDead, (facingRight ? frameRecDead : Rectangle{frameRecDead.x, 0, -frameRecDead.width, frameRecDead.height}), position, WHITE);
        break;
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
    case STATE_SHIELD:
        DrawTextureRec(spriteShield, (facingRight ? frameRecShield : Rectangle{frameRecShield.x, 0, -frameRecShield.width, frameRecShield.height}), position, WHITE);
        break;
    case STATE_HURT:
        DrawTextureRec(spriteHurt, (facingRight ? frameRecHurt : Rectangle{frameRecHurt.x, 0, -frameRecHurt.width, frameRecHurt.height}), position, WHITE);
        break;
    default:
        DrawTextureRec(spriteIdle, (facingRight ? frameRecIdle : Rectangle{frameRecIdle.x, 0, -frameRecIdle.width, frameRecIdle.height}), position, WHITE);
    }
    DrawRectangleLines(bodyHitBox.x, bodyHitBox.y, bodyHitBox.width, bodyHitBox.height, BLUE);
}

void Player::Update(float dt, const InputState &input)
{
    isWalking = false;

    // Horizontal movement
    if (input.moveRight)
    {
        velocity.x = SPEED;
        facingRight = true;
        isWalking = true;
        if (!IsSoundPlaying(walkSound))
        {
            PlaySound(walkSound);
        }
    }
    else if (input.moveLeft)
    {
        velocity.x = -SPEED;
        facingRight = false;
        isWalking = true;
        if (!IsSoundPlaying(walkSound))
        {
            PlaySound(walkSound);
        }
    }
    else
    {
        if (IsSoundPlaying(walkSound))
        {
            StopSound(walkSound);
        }
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
        PlaySound(swordSound);
        isAttacking = true;
    }

    // Shield
    if (input.shield)
    {
        isDefending = true;
    }

    // Gravity (vedno)
    velocity.y += dt * GRAVITY;

    if (healthPoints <= 0.0)
    {
        playerState = STATE_DEAD;
    }
    else if (playerState == STATE_HURT)
    {
    }
    else if (isAttacking)
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
    else if (isDefending)
    {
        playerState = STATE_SHIELD;
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
    else if (playerState == STATE_WALK && isGrounded)
    {
        walkTimer += dt;
        if (walkTimer >= 0.1f)
        {
            walkTimer = 0.0f;
            walkFrameIndex = (walkFrameIndex + 1) % frameNumWalk;
        }
        frameRecWalk.x = frameRecWalk.width * walkFrameIndex;
    }
    else if (playerState == STATE_JUMP)
    {
        jumpTimer += dt;
        if (jumpTimer >= 0.2f)
        {
            jumpTimer = 0.0f;
            jumpFrameIndex = (jumpFrameIndex + 1) % frameNumJump;
        }
        frameRecJump.x = frameRecJump.width * jumpFrameIndex;
    }
    else if (playerState == STATE_ATTACK)
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
    else if (playerState == STATE_DEAD)
    {
        deadTimer += dt;
        if (deadTimer > 0.1f)
        {
            deadTimer = 0.0f;
            deadFrameIndex++;
            if (deadFrameIndex >= frameNumDead)
            {
                isAttacking = false;
                deadFrameIndex = 0;
                isAlive = false;
            }
        }
        frameRecDead.x = frameRecDead.width * deadFrameIndex;
    }
    else if (playerState == STATE_SHIELD)
    {
        shieldTimer += dt;
        if (shieldTimer > 0.09f)
        {
            shieldTimer = 0.0f;
            shieldFrameIndex++;
            if (shieldFrameIndex > frameNumShield)
            {
                playerState = STATE_IDLE;
                isDefending = false;
                shieldFrameIndex = 0;
            }
        }
        frameRecShield.x = frameRecShield.width * shieldFrameIndex;
    }
    else if (playerState == STATE_HURT)
    {
        hurtTimer += dt;
        if (hurtTimer > 0.1f)
        {
            hurtTimer = 0.0f;
            hurtFrameIndex++;
            if (hurtFrameIndex >= frameNumHurt)
            {
                hurtFrameIndex = 0;
                playerState = STATE_IDLE;
            }
        }
        frameRecHurt.x = frameRecHurt.width * hurtFrameIndex;
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
    PlaySound(diamondSound);
    numOfCollectedDiamonds++;
}

void Player::takeDamage(float damage)
{
    PlaySound(hurtSound);
    healthPoints -= damage;
    playerState = STATE_HURT;
}
