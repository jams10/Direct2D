#pragma once

#include "GameLevel.h"

class Level1 :public GameLevel
{
	float y;
	float ySpeed;
public:
	void Load()   override;
	void UnLoad() override;
	void Update() override;
	void Render(class Graphics* gfx) override;

};