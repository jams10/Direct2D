#include "Level1.h"
#include "Graphics.h"
#include "GameController.h"

void Level1::Load()
{
	y = ySpeed = 0.0f;

	sprites = new SpriteSheet(L"test.png", gfx);
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
}

void Level1::Render()
{
	gfx->ClearScreen(0.0f, 0.1f, 0.5f);

	sprites->Draw();

	gfx->DrawCircle(375.0f, y, 50.f, 0.0f, 1.0f, 0.0f, 1.0f);

}

