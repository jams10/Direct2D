#include<Windows.h>
#include "Graphics.h"

Graphics* graphics;

LRESULT CALLBACK WindowProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	if (uMsg == WM_PAINT) // �����찡 �ٽ� �׷��� �� ȣ��Ǵ� �޽���.
	{
		graphics->BeginDraw();

		graphics->ClearScreen(0.0f, 0.0f, 0.5f);

		graphics->DrawCircle(100, 100, 50, 0.0f, 1.0f, 0.0f, 1.0f);

		graphics->EndDraw();
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPWSTR cmd,
	int nCmdShow)
{
	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = L"MainWindow";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowClass);

	//
	// ������ Ŭ���̾�Ʈ ������ ����� ����.
	//
	RECT rect = {0, 0, 800, 600};
	// AdjustWindowRectEx: �Ѱ��� rect ũ�⿡ �°� ������ Ŭ���̾�Ʈ ���� ����� ������, rect�� ��ü ������ ũ�⸦ �����ϴ� ��ǥ�� �Ѱ���.
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW); 

	HWND hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MainWindow", L"D2D Tutorial", WS_OVERLAPPEDWINDOW, 100, 100, 
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);
	
	if (!hWnd)
	{
		return -1;
	}

	// Direct2D API ����� ���� ĸ��ȭ�� Graphics Ŭ���� ��ü ���� �� �ʱ�ȭ �Լ� ȣ��.
	graphics = new Graphics();
	if (!graphics->Init(hWnd))
	{
		delete graphics;
		return -1;
	}

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, hWnd, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}