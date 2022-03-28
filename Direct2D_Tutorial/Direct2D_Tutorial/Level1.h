#pragma once

#include "GameLevel.h"

class Level1 :public GameLevel
{
	float y;
	float ySpeed;

	SpriteSheet* sprites;	

	int frame;
	int count = 0;

public:
	void Load()   override;
	void UnLoad() override;
	void Update() override;
	void Render() override;

};