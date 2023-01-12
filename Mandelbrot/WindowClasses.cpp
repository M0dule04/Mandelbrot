#include "WindowClasses.h"

BOOL Canvas::InitDirect2D(HWND hWnd, ID2D1Factory* pD2DFactory, ID2D1HwndRenderTarget* pRT)
{
	pD2DFactory = NULL;
	pRT = NULL;

	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &pD2DFactory);

	if (FAILED(hr))
	{
		pD2DFactory = NULL;
		return FALSE;
	}

	RECT rc;
	GetClientRect(hWnd, &rc);

	hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd,D2D1::SizeU(rc.right-rc.left, rc.bottom-rc.top)),
		&pRT);

	return SUCCEEDED(hr);

}

LRESULT Canvas::MessageHandler(HWND hWND, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		InitDirect2D(hWND, pFactory, pRT);
		break;
	default:
		return Canvas::MessageHandler(hWND, uMsg, wParam, lParam);
		break;
	}

	return 0;	
}
