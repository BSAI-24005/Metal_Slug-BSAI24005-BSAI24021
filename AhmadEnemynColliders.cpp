struct enemy {
	int x, y, px;
};

//main
	Rectangle p1Collider;
	Rectangle e1Collider;
  Texture2D Enemy = LoadTexture("enemy.png");
  enemy e1;
  e1.px = 100;
  e1.x = ScreenWidth + 5;
  e1.y= ScreenHeight - p1.px + 3;\
	e1.x-=4;
	p1Collider.x = p1.x;
	p1Collider.y = p1.y;
	e1Collider.x = e1.x;
	e1Collider.y = e1.y;
