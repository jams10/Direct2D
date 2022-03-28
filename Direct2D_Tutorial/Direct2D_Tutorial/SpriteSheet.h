#pragma once

#include <wincodec.h> // 파일로 부터 이미지를 디코딩 하기 위한 WIC codec.
#include "Graphics.h" // 우리가 windows와 d2d1.h 헤더 파일을 include 해주었음.
// Link to windowscodecs.lib
#pragma comment(lib, "windowscodecs.lib")

class SpriteSheet
{
	Graphics* gfx;      // Graphics 클래스 객체에 대한 참조.
	ID2D1Bitmap* bmp;   // 이미지 파일을 로드해 Direct2D 포맷으로 변환한 비트맵.
public:
	SpriteSheet(const wchar_t* filename, Graphics* gfx);
	~SpriteSheet();

	// 렌더 타겟에 비트맵 그리기.
	void Draw();
};

