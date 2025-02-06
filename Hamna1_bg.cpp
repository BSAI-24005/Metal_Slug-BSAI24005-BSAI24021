#include<iostream>
#include <raylib.h>

const int screenwidth = 500;
const int screenheight = 750;

struct background
{
	int x, y;

};
int main()
{ 
	background bg1;
	background bg2;
	bg1.x = 0; bg2.x = screenwidth;
	bg1.y = 0.528 * screenheight;
	bg2.y = 0.528 * screenheight;
	InitWindow(screenwidth, screenheight, "METAL SLUG");
	SetTargetFPS(60);
	
	Color sky = { 167,199,231,255 };
	Texture2D background1 = LoadTexture("BG 1.png");
	Texture2D background2 = LoadTexture("BG 2.png");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(sky);
		
			DrawTexture(background1, bg1.x, bg1.y, WHITE);
			if (bg1.x == -screenwidth)
			{
				bg1.x = screenwidth;
			}
			DrawTexture(background2, bg2.x, bg2.y, WHITE);
			if (bg2.x == -screenwidth)
			{
				bg2.x = screenwidth;
			}
		EndDrawing();
		bg1.x--;
		bg2.x--;


	}
	CloseWindow();
}
