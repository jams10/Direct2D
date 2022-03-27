#pragma once

#include <Windows.h>
#include <d2d1.h>

class Graphics
{

	ID2D1Factory* factory;			     // ���� Direct2D ���ҽ��� ����µ� �����.
	ID2D1HwndRenderTarget* renderTarget; // ������ ȭ�鿡 �׸��� ���� ���� Ÿ��.
	ID2D1SolidColorBrush* brush;
public:
	Graphics();
	~Graphics();

	bool Init(HWND hWnd);

	// Direct2D������ ���� Ÿ���� BeginDraw() �Լ��� ȣ���Ѵ��� ������ ���� �ڵ带 ��ְ�,
	// EndDraw()�� �ؾ� ��μ� ������ ���� Ÿ�ٿ� �׷�����.
	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
};