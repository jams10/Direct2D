#pragma once

class GameLevel
{
public:
	bool Loading = false;

	virtual void Load() = 0;
	virtual void UnLoad() = 0;
	virtual void Update() = 0;
	virtual void Render(class Graphics* gfx) = 0;
};

