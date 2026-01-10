#include "raylib.h"
#include "../include/Anemy.h"
#include "../include/Player.h"
#include "../include/InputState.h"
#include "../include/Level.h"
#include "../include/Background.h"
#include "../include/UI.h"
#include "../include/GameContext.h"
#include "../include/GameState.h"
#include "../include/AudioManager.h"
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
    AudioManager audioManager;
    Vector2 playerPos = {ctx.tileSize * 10, 296};

    Camera2D camera;
    GameState currentState;

    Vector2 mouse;

public:
    GameController() : background(ctx),
                       audioManager(),
                       player({ctx.tileSize * 10, 296}, ctx, audioManager),
                       level("..//Level.txt", ctx, audioManager, player),
                       ui(ctx, audioManager, player) {};
    // ~GameController();
    void Initialize();
    void Update(float dt);
    void Draw();
    void OnWindowResized(int screenWidth, int screenHeigth);
};