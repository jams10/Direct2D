#pragma once

#include "SpriteSheet.h"

class GameLevel
{
protected:
	static class Graphics* gfx;

public:
	static void Init(Graphics* graphics)
	{
		gfx = graphics;
	}

	virtual void Load() = 0;
	virtual void UnLoad() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

