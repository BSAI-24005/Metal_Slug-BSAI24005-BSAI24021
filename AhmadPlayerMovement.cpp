const int Gravity = 1;
const int Jump = -15;
struct Player {
	int x, y, px;
	int vy = 0;
	bool isJumping = false;
}

int main()  {
  Texture2D player = LoadTexture("player.png");
  Player p1;
  p1.px = 100;
  p1.x = ScreenWidth / 2 - (p1.px / 2);
  p1.y = ScreenHeight - p1.px + 3;
  if (IsKeyDown(KEY_LEFT))
  	p1.x -= 3;
  if (IsKeyDown(KEY_RIGHT))
  	p1.x += 3;
  if (IsKeyPressed(KEY_SPACE) && !p1.isJumping) {
  	p1.vy = Jump;
  	p1.isJumping = true;
  }
  
  p1.y += p1.vy;
  p1.vy += Gravity;
  return 0;
}
