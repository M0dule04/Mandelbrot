#include "WindowClasses.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	WCHAR classname[] = L"Mandelbrot";
	Control* frame = new Control(hInstance,classname);

	frame->setWindowName(classname);
	frame->setHeight(500);
	frame->setWidth(500);
	frame->setX(15);
	frame->setY(15);
	frame->setStyles(WS_VISIBLE || WS_MINIMIZEBOX);

	if (!frame->Create(NULL, NULL, NULL))
	{
		return 0;
	}

	//frame->Show(SW_NORMAL);

	return 0;
}