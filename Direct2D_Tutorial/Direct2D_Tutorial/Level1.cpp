#include "Level1.h"
#include "Graphics.h"
#include "GameController.h"

void Level1::Load()
{
	y = ySpeed = 0.0f;

	sprites = new SpriteSheet(L"mario2.png", gfx, 19, 34);

	frame = 0;
}

void Level1::UnLoad()
{
	delete sprites;
}

void Level1::Update()
{
	ySpeed += 1.0f;
	y += ySpeed;

	if (y + 50.f > 600)
	{
		y = 600.f - 50.f;
		ySpeed *= -0.8f;
	}

	if (count > 5)
	{
		count = 0;
		frame++;
	}
	count++;
}

void Level1::Render()
{
	gfx->ClearScreen(0.0f, 0.1f, 0.5f);

	gfx->DrawCircle(375.0f, y, 50.f, 0.0f, 1.0f, 0.0f, 1.0f);

	sprites->Draw(frame % 5, 100, 100);
}

