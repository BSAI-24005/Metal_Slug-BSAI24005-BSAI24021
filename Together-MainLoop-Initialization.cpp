#include <iostream>
#include <raylib.h>

using namespace std;

const int ScreenWidth = 1878;
const int ScreenHeight = 448;
const int Gravity = 1;
const int Jump = -15;
const int BulletSpeed = 10;
const int MaxEnemies = 5;
const int MaxLevels = 3;

struct Player {
    int x, y, px;
    int vy = 0;
    bool isJumping = false;
    int health = 100;
};

struct Background {
    int x, y;
};

struct Enemy {
    int x, y, px;
    bool active = false;
};

struct Bullet {
    int x, y;
    bool active = false;
};

enum GameState {
    MENU,
    PLAYING,
    GAME_OVER,
    GAME_WON,
    CONTROLS,
    LEVEL_TRANSITION
};

void DrawMenu(int& menuSelection);
void DrawControls();
void DrawGameOver();
void DrawGameWon();
void DrawLevelTransition(int level);

int main() {
    InitWindow(ScreenWidth, ScreenHeight, "Metal Slug");
    SetTargetFPS(60);
    Color sky = { 167, 199, 231, 255 };

    Texture2D playerTex = LoadTexture("player.png");
    Texture2D enemyTex = LoadTexture("enemy.png");
    Texture2D bulletTex = LoadTexture("bullet.png");
    Texture2D bg1Tex = LoadTexture("BG 1.png");
    Texture2D bg2Tex = LoadTexture("BG 2.png");

    Player p1 = { ScreenWidth / 2 - 50, ScreenHeight - 103, 100 };
    Background bg1 = { 0, 0 }, bg2 = { ScreenWidth, 0 };
    Enemy enemies[MaxEnemies];
    Bullet b = { 0, 0, false };

    int score = 0;
    int level = 1;
    int enemyCount = 1;
    int spawnCounter = 0;

    GameState gameState = MENU;
    int menuSelection = 0;
    int transitionTimer = 0;

    while (!WindowShouldClose()) {
        switch (gameState) {
        case MENU: {
            if (IsKeyPressed(KEY_DOWN)) menuSelection = (menuSelection + 1) % 3;
            if (IsKeyPressed(KEY_UP)) menuSelection = (menuSelection - 1 + 3) % 3;
            if (IsKeyPressed(KEY_ENTER)) {
                if (menuSelection == 0) {
                    gameState = PLAYING;
                    p1 = { ScreenWidth / 2 - 50, ScreenHeight - 103, 100 };
                    score = 0;
                    level = 1;
                    enemyCount = 1;
                    spawnCounter = 0;
                    for (int i = 0; i < MaxEnemies; i++) enemies[i].active = false;
                    b.active = false;
                }
                else if (menuSelection == 1) {
                    gameState = CONTROLS;
                }
                else if (menuSelection == 2) {
                    CloseWindow();
                    return 0;
                }
            }
            DrawMenu(menuSelection);
            break;
        }
        case CONTROLS: {
            if (IsKeyPressed(KEY_B)) gameState = MENU;
            DrawControls();
            break;
        }
        case PLAYING: {
            if (p1.health <= 0) {
                gameState = GAME_OVER;
                break;
            }

            if (level == MaxLevels && score >= 10) {
                gameState = GAME_WON;
                break;
            }

            if (IsKeyDown(KEY_LEFT)) p1.x -= 4;
            if (IsKeyDown(KEY_RIGHT)) p1.x += 4;
            if (IsKeyPressed(KEY_SPACE) && !p1.isJumping) {
                p1.vy = Jump;
                p1.isJumping = true;
            }
            p1.y += p1.vy;
            p1.vy += Gravity;
            if (p1.y >= ScreenHeight - p1.px + 3) {
                p1.y = ScreenHeight - p1.px + 3;
                p1.isJumping = false;
            }

            if (spawnCounter % 120 == 0) {
                for (int i = 0; i < enemyCount; i++) {
                    if (!enemies[i].active) {
                        enemies[i] = { ScreenWidth + (i * 200), ScreenHeight - 103, 100, true };
                    }
                }
            }
            spawnCounter++;

            for (int i = 0; i < enemyCount; i++) {
                if (enemies[i].active) {
                    enemies[i].x -= 4;
                    if (enemies[i].x < -100) {
                        enemies[i].active = false;
                    }
                    
                    if (p1.x + 50 >= enemies[i].x && p1.x <= enemies[i].x + 100) {
                        p1.health -= 1;
                    }
                }
            }

            if (IsKeyPressed(KEY_LEFT_SHIFT) && !b.active) {
                b.x = p1.x + 50;
                b.y = p1.y + 30;
                b.active = true;
            }
            if (b.active) {
                b.x += BulletSpeed;
                if (b.x > ScreenWidth) {
                    b.active = false;
                }
                for (int i = 0; i < enemyCount; i++) {
                    if (enemies[i].active && b.x >= enemies[i].x && b.x <= enemies[i].x + 100 && b.y >= enemies[i].y && b.y <= enemies[i].y + 100) {
                        enemies[i].active = false;
                        b.active = false;
                        score++;
                    }
                }
            }

            if (score >= 3 * level && level < MaxLevels) {
                level++;
                enemyCount = level + 1;
                gameState = LEVEL_TRANSITION;
                transitionTimer = 120;
            }

            bg1.x--;
            bg2.x--;
            if (bg1.x <= -ScreenWidth) bg1.x = ScreenWidth;
            if (bg2.x <= -ScreenWidth) bg2.x = ScreenWidth;

            BeginDrawing();
            ClearBackground(sky);
            DrawTexture(bg1Tex, bg1.x, bg1.y, WHITE);
            DrawTexture(bg2Tex, bg2.x, bg2.y, WHITE);
            DrawTexture(playerTex, p1.x, p1.y, WHITE);
            for (int i = 0; i < enemyCount; i++) {
                if (enemies[i].active) DrawTexture(enemyTex, enemies[i].x, enemies[i].y, WHITE);
            }
            if (b.active) DrawTexture(bulletTex, b.x, b.y, WHITE);
            DrawText(TextFormat("Score: %d", score), 20, 20, 30, RED);
            DrawText(TextFormat("Health: %d", p1.health), 20, 60, 30, GREEN);
            DrawText(TextFormat("Level: %d", level), 20, 100, 30, BLUE);
            EndDrawing();
            break;
        }
        case LEVEL_TRANSITION: {
            if (transitionTimer > 0) {
                transitionTimer--;
                DrawLevelTransition(level);
            }
            else {
                gameState = PLAYING;
            }
            break;
        }
        case GAME_OVER: {
            if (IsKeyPressed(KEY_R)) {
                gameState = MENU;
            }
            else if (IsKeyPressed(KEY_Q)) {
                CloseWindow();
                return 0;
            }
            DrawGameOver();
            break;
        }
        case GAME_WON: {
            if (IsKeyPressed(KEY_R)) {
                gameState = MENU;
            }
            else if (IsKeyPressed(KEY_Q)) {
                CloseWindow();
                return 0;
            }
            DrawGameWon();
            break;
        }
        }
    }

    CloseWindow();
    return 0;
}
