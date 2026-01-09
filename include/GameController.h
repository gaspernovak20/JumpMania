#include "raylib.h"
#include "../include/Anemy.h"
#include "../include/Player.h"
#include "../include/InputState.h"
#include "../include/Level.h"
#include "../include/Background.h"
#include "../include/UI.h"
#include "../include/GameContext.h"
#include "../include/GameState.h"
#include <filesystem>
#include <vector>
#include <cmath>
using namespace std;

class GameController
{
private:
    GameContext ctx{800, 450, (float)(800 / 15)};
    Background background;
    Level level;
    Player player;
    UI ui;
    Vector2 playerPos = {ctx.tileSize * 10, 296};

    Camera2D camera;
    GameState currentState;

    Vector2 mouse;

public:
    GameController() : background(ctx),
                       player({ctx.tileSize * 10, 296}, ctx),
                       level("..//Level.txt", ctx, player),
                       ui(ctx, player) {};
    // ~GameController();
    void Initialize();
    void Update(float dt);
    void Draw();
    void OnWindowResized(int screenWidth, int screenHeigth);
};