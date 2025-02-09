#include <raylib.h>

const int ScreenWidth = 1878;
const int ScreenHeight = 448;

void DrawMenu(int& menuSelection) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Metal Slug", ScreenWidth / 2 - MeasureText("Metal Slug", 50) / 2, 50, 50, WHITE);

    Color startColor = WHITE, controlsColor = WHITE, quitColor = WHITE;
    if (menuSelection == 0) startColor = YELLOW;
    else if (menuSelection == 1) controlsColor = YELLOW;
    else if (menuSelection == 2) quitColor = YELLOW;

    DrawText("Start Game", ScreenWidth / 2 - MeasureText("Start Game", 30) / 2, 200, 30, startColor);
    DrawText("Controls", ScreenWidth / 2 - MeasureText("Controls", 30) / 2, 250, 30, controlsColor);
    DrawText("Quit", ScreenWidth / 2 - MeasureText("Quit", 30) / 2, 300, 30, quitColor);

    EndDrawing();
}

void DrawControls() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Controls", ScreenWidth / 2 - MeasureText("Controls", 50) / 2, 50, 50, WHITE);
    DrawText("Left Arrow: Move Left", ScreenWidth / 2 - MeasureText("Left Arrow: Move Left", 30) / 2, 150, 30, WHITE);
    DrawText("Right Arrow: Move Right", ScreenWidth / 2 - MeasureText("Right Arrow: Move Right", 30) / 2, 200, 30, WHITE);
    DrawText("Space: Jump", ScreenWidth / 2 - MeasureText("Space: Jump", 30) / 2, 250, 30, WHITE);
    DrawText("Left Shift: Shoot", ScreenWidth / 2 - MeasureText("Left Shift: Shoot", 30) / 2, 300, 30, WHITE);
    DrawText("Press B to go back", ScreenWidth / 2 - MeasureText("Press B to go back", 30) / 2, 350, 30, WHITE);
    EndDrawing();
}

void DrawGameOver() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Game Over", ScreenWidth / 2 - MeasureText("Game Over", 50) / 2, 150, 50, RED);
    DrawText("Press R to Restart", ScreenWidth / 2 - MeasureText("Press R to Restart", 30) / 2, 250, 30, WHITE);
    DrawText("Press Q to Quit", ScreenWidth / 2 - MeasureText("Press Q to Quit", 30) / 2, 300, 30, WHITE);
    EndDrawing();
}

void DrawGameWon() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("You Win!", ScreenWidth / 2 - MeasureText("You Win!", 50) / 2, 150, 50, GREEN);
    DrawText("Press R to Restart", ScreenWidth / 2 - MeasureText("Press R to Restart", 30) / 2, 250, 30, WHITE);
    DrawText("Press Q to Quit", ScreenWidth / 2 - MeasureText("Press Q to Quit", 30) / 2, 300, 30, WHITE);
    EndDrawing();
}

void DrawLevelTransition(int level) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText(TextFormat("Level %d", level), ScreenWidth / 2 - MeasureText(TextFormat("Level %d", level), 50) / 2, ScreenHeight / 2 - 50, 50, WHITE);
    DrawText("Get Ready!", ScreenWidth / 2 - MeasureText("Get Ready!", 30) / 2, ScreenHeight / 2 + 50, 30, YELLOW);
    EndDrawing();
}
