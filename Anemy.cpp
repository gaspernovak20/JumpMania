#include <iostream>
#include <string>
#include "include/Anemy.h"
#include "include/Player.h"
using namespace std;

EnemyTextures Anemy::anemyTexture;

Anemy::Anemy(string name, Vector2 position) : name(name), position(position), originPosition(position) {};

void Anemy::LoadTextures()
{
    anemyTexture.spriteIdle = LoadTexture("../assets/anemy/Fire_Spirit/Idle.png");
    anemyTexture.spriteWalk = LoadTexture("../assets/anemy/Fire_Spirit/Walk.png");
    anemyTexture.spriteCharge = LoadTexture("../assets/anemy/Fire_Spirit/Charge.png");
    anemyTexture.spriteDead = LoadTexture("../assets/anemy/Fire_Spirit/Dead.png");

    anemyTexture.frameNumIdle = 6;
    anemyTexture.frameNumWalk = 7;
    anemyTexture.frameNumCharge = 8;
    anemyTexture.frameNumDead = 5;

    anemyTexture.frameRecIdle = {
        0.f,
        0.f,
        (float)anemyTexture.spriteIdle.width / anemyTexture.frameNumIdle,
        (float)anemyTexture.spriteIdle.height,
    };

    anemyTexture.frameRecWalk = {
        0.f,
        0.f,
        (float)anemyTexture.spriteWalk.width / anemyTexture.frameNumWalk,
        (float)anemyTexture.spriteWalk.height,
    };

    anemyTexture.frameRecCharge = {
        0.f,
        0.f,
        (float)anemyTexture.spriteCharge.width / anemyTexture.frameNumCharge,
        (float)anemyTexture.spriteCharge.height,
    };

    anemyTexture.frameRecDead = {
        0.f,
        0.f,
        (float)anemyTexture.spriteDead.width / anemyTexture.frameNumDead,
        (float)anemyTexture.spriteDead.height,
    };
}

void Anemy::UnloadTextures()
{
    UnloadTexture(anemyTexture.spriteIdle);
    UnloadTexture(anemyTexture.spriteWalk);
    UnloadTexture(anemyTexture.spriteCharge);
}

void Anemy::Draw()
{

    switch (anemyState)
    {
    case ANEMY_STATE_WALK:
        DrawTextureRec(anemyTexture.spriteWalk, facingRight ? anemyTexture.frameRecWalk : Rectangle{anemyTexture.frameRecWalk.x, anemyTexture.frameRecWalk.y, -anemyTexture.frameRecWalk.width, anemyTexture.frameRecWalk.height}, position, WHITE);
        DrawRectangleLines(bodyHitBox.x, bodyHitBox.y, bodyHitBox.width, bodyHitBox.height, RED);
        break;
    case ANEMY_STATE_CHARGE:

        DrawTexturePro(anemyTexture.spriteCharge, facingRight ? anemyTexture.frameRecCharge : Rectangle{anemyTexture.frameRecCharge.x, anemyTexture.frameRecCharge.y, -anemyTexture.frameRecCharge.width, anemyTexture.frameRecCharge.height}, {position.x, position.y, anemyTexture.frameRecCharge.width * 2, anemyTexture.frameRecCharge.height * 2}, {0.f, 0.f}, 0.f, WHITE);
        DrawRectangleLines(bodyHitBox.x, bodyHitBox.y, bodyHitBox.width, bodyHitBox.height, RED);
        break;
    case ANEMY_STATE_DEATH:
        DrawTextureRec(anemyTexture.spriteDead, anemyTexture.frameRecDead, position, WHITE);
        break;
    default:
        DrawTextureRec(anemyTexture.spriteIdle, anemyTexture.frameRecIdle, position, WHITE);
        break;
    }
}

void Anemy::Update(float dt, const Vector2 playerPos, const Rectangle playerHitbox)
{
    float distanceFromPlayer = getHorizontalDistanceFromPlayer(playerHitbox);
    Anemy::updateState(distanceFromPlayer);

    if (anemyState == ANEMY_STATE_WALK)
    {
        if (hountingPlayer)
            moveTo(playerPos, dt);
        else
            moveTo(originPosition, dt);
    }

    if (anemyState == ANEMY_STATE_IDLE && !hountingPlayer)
    {
        idleTimer += dt;
        if (idleTimer >= 0.1f)
        {
            idleTimer = 0;
            idleFrameIndex = ++idleFrameIndex % anemyTexture.frameNumIdle;
        }
        anemyTexture.frameRecIdle.x = anemyTexture.frameRecIdle.width * idleFrameIndex;
    }
    else if (anemyState == ANEMY_STATE_WALK)
    {
        walkTimer += dt;
        if (walkTimer >= 0.1)
        {
            walkTimer = 0;
            walkFrameIndex = ++walkFrameIndex % anemyTexture.frameNumWalk;
        }
        anemyTexture.frameRecWalk.x = anemyTexture.frameRecWalk.width * walkFrameIndex;
    }
    else if (anemyState == ANEMY_STATE_CHARGE)
    {
        chargeTimer += dt;
        if (chargeTimer >= 0.05)
        {
            chargeTimer = 0;
            chargeFrameIndex++;
        }
        anemyTexture.frameRecCharge.x = anemyTexture.frameRecCharge.width * chargeFrameIndex;
        if (chargeFrameIndex >= anemyTexture.frameNumCharge)
        {
            isAlive = false;
            anemyState = ANEMY_STATE_DEATH;
        }
    }
    else if (anemyState == ANEMY_STATE_DEATH)
    {
        deadTimer += dt;
        if (deadTimer >= 0.2)
        {
            deadTimer = 0;
            deadFrameIndex++;
        }
        anemyTexture.frameRecDead.x = anemyTexture.frameRecDead.width * deadFrameIndex;
        if (deadFrameIndex >= anemyTexture.frameNumDead)
        {
            isAlive = false;
            isDying = false;
        }
    }
}

void Anemy::updateState(float distanceFromPlayer)
{
    if (isDying)
    {
        anemyState = ANEMY_STATE_DEATH;
        hountingPlayer = false;
        return;
    }

    if (fabs(distanceFromPlayer) < CHARGE_DISTANCE)
    {
        anemyState = ANEMY_STATE_CHARGE;
        return;
    }

    if (fabs(distanceFromPlayer) < AGRO_DISTANCE)
    {
        anemyState = ANEMY_STATE_WALK;
        hountingPlayer = true;
        return;
    }

    if (fabs(position.x - originPosition.x) > RETURN_EPSILON)
    {
        anemyState = ANEMY_STATE_WALK;
        hountingPlayer = false;
        return;
    }

    anemyState = ANEMY_STATE_IDLE;
    velocity.x = 0.0;
    hountingPlayer = false;
}

void Anemy::takeDamage(int damage)
{
    healthPoints -= damage;
    if (healthPoints <= 0)
    {
        isDying = true;
        anemyState = ANEMY_STATE_DEATH;
    }
}
float Anemy::getHorizontalDistanceFromPlayer(const Rectangle &playerHitbox)
{
    float enemyLeft = bodyHitBox.x;
    float enemyRight = bodyHitBox.x + bodyHitBox.width;

    float playerLeft = playerHitbox.x;
    float playerRight = playerHitbox.x + playerHitbox.width;

    if (playerLeft > enemyRight)
    {
        return playerLeft - enemyRight;
    }

    if (playerRight < enemyLeft)
    {
        return playerRight - enemyLeft;
    }

    return 0.0f;
}

void Anemy::moveTo(Vector2 toPosition, float dt)
{
    if ((toPosition.x - position.x) > 0)
    {
        velocity.x = speed;
        facingRight = true;
    }
    else
    {
        velocity.x = -speed;
        facingRight = false;
    }
}

void Anemy::applyPosition(Vector2 pos)
{
    position = pos;
    bodyHitBox = getHitboxAt(position);
}