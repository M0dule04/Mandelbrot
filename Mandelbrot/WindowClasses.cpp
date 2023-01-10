#include "WindowClasses.h"

Control::Control(HINSTANCE hInstance, WCHAR ClassName[]) {
	this->ClassName = ClassName;
	this->hInstance = hInstance;
	wc.hInstance = hInstance;
	wc.lpszClassName = ClassName;
	wc.lpfnWndProc = DefWindowProc;

	RegisterClass(&wc);
}

int Control::getX()
{
	return x;
}

int Control::getY()
{
	return y;
}

void Control::setX(int x)
{
	this->x = x;

	Move();
}

void Control::setY(int y)
{
	this->y = y;
	Move();
}

void Control::Move()
{
	if (hWND != NULL)
	{
		MoveWindow(hWND, x, y, width, height, TRUE);
	}
}

int Control::getWidth()
{
	return width;
}

int Control::getHeight()
{
	return height;
}

void Control::setHeight(int newHeight) {
	height = newHeight;
	Move();
}

void Control::setWidth(int newWidth) {
	width = newWidth;
	Move();
}

void Control::setWindowName(WCHAR newName[])
{
	WindowName = newName;

	if (hWND != NULL)
	{
		SetWindowTextW(hWND, newName);
	}	
}

WCHAR* Control::GetWindowName() {
	return WindowName;
}

LPVOID Control::getLpParam(){
	return (LPVOID)GetWindowLongPtr(hWND, GWLP_USERDATA);
}

void Control::setLpParam(LPVOID lpParam){

}

HWND Control::getHandle(){
	return hWND;
}

HWND Control::getParentHandle(){
	return hParent;
}

void Control::setParentHandle(HWND hParent){
	this->hParent = hParent;

	if (hWND != NULL )
	{
		SetParent(hWND, hParent);
	}
	
}

BOOL Control::Create(HWND hParent, HMENU hMenu, LPVOID lpParam){

	hWND = CreateWindowEx(
		ExStyles, 
		ClassName, 
		WindowName, 
		Styles, 
		x, y, width, height,
		hParent, 
		hMenu, 
		hInstance, 
		lpParam);

	if (hWND != NULL)
	{
		Show(SW_SHOW);
		MessageHandler();
		return TRUE;
	}

	return FALSE;
}

void Control::Show(int nShowWindow) {

	ShowWindow(hWND, nShowWindow);
}

void Control::MessageHandler() {
	MSG msg = {};

	while (GetMessage(&msg, NULL, 0, 0) != 0) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}

void Control::setStyles(DWORD styles) {
	this->Styles = styles;

	if (hWND != NULL)
	{
		SetWindowLongPtrW(hWND, GWL_STYLE, styles);
		Move();//some styles require a reposition
	}
}

void Control::setExStyles(DWORD ExStyles) {
	this->ExStyles = ExStyles;

	if (hWND != NULL) {
		SetWindowLongPtrW(hWND, GWL_EXSTYLE, ExStyles);
		Move();//some styles require a reposition
	}
}

DWORD Control::getExStyles() {
	return ExStyles;
}

DWORD Control::getStyles() {
	return Styles;
}

