#pragma once

#include <Windows.h>
#include <d2d1.h>

class Graphics
{

	ID2D1Factory* factory;			     // 여러 Direct2D 리소스를 만드는데 사용함.
	ID2D1HwndRenderTarget* renderTarget; // 윈도우 화면에 그리기 위한 렌더 타겟.
	ID2D1SolidColorBrush* brush;
public:
	Graphics();
	~Graphics();

	bool Init(HWND hWnd);

	// Direct2D에서는 렌더 타겟의 BeginDraw() 함수를 호출한다음 렌더링 관련 코드를 써넣고,
	// EndDraw()를 해야 비로소 설정한 렌더 타겟에 그려진다.
	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
};