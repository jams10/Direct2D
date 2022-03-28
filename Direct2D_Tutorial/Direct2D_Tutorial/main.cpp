#include<Windows.h>
#include "Graphics.h"

#include "Level1.h"
#include "GameController.h"

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

	GameController::LoadInitialLevel(new Level1());

	MSG msg;
	msg.message = WM_NULL;

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ������Ʈ
			GameController::Update();

			// ������
			graphics->BeginDraw();
			
			GameController::Render(graphics);

			graphics->EndDraw();
		}
	}

	return 0;
}