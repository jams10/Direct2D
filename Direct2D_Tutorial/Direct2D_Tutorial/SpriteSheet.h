#pragma once

#include <wincodec.h> // ���Ϸ� ���� �̹����� ���ڵ� �ϱ� ���� WIC codec.
#include "Graphics.h" // �츮�� windows�� d2d1.h ��� ������ include ���־���.
// Link to windowscodecs.lib
#pragma comment(lib, "windowscodecs.lib")

class SpriteSheet
{
	Graphics* gfx;      // Graphics Ŭ���� ��ü�� ���� ����.
	ID2D1Bitmap* bmp;   // �̹��� ������ �ε��� Direct2D �������� ��ȯ�� ��Ʈ��.
public:
	SpriteSheet(const wchar_t* filename, Graphics* gfx);
	~SpriteSheet();

	// ���� Ÿ�ٿ� ��Ʈ�� �׸���.
	void Draw();
};

