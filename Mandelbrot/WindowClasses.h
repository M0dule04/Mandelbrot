#pragma once
#include <windows.h>

class Control // base window class
{
	private:
		WNDCLASS wc = {};
		WCHAR *ClassName; //Name used to reference window
		WCHAR *WindowName; //name that the windows receives (caption of the window)
		HWND hWND = NULL; //handle of the window
		HWND hParent;//parent handle of the window
		HINSTANCE hInstance;

		DWORD ExStyles; //Extended Styles grouped togheter by an OR operation
		DWORD Styles; //Styles grouped togheter by an OR operation

		int x = CW_USEDEFAULT; // X position of window relative to parent
		int y = CW_USEDEFAULT; // Y position of window relatiive to parent
		int width = CW_USEDEFAULT; // width of the window
		int height = CW_USEDEFAULT; // height of the window
		void Move();
		void MessageHandler();
	public: 
		int getX(); // returbs the x position of the window
		int getY(); // returns the y position of the window
		void setX(int x); // sets the X position of the window
		void setY(int y); // sets the Y position of the window
		
		int getWidth();//returns the width of the window
		int getHeight();//returns the height of the window
		void setHeight(int newHeight); // sets the height of the window
		void setWidth(int newWidth); // sets the width of the window

		void setStyles(DWORD styles);
		DWORD getStyles();
		void setExStyles(DWORD exStyles);
		DWORD getExStyles();

		WCHAR* GetWindowName(); //returns the caption of the window frame
		void setWindowName(WCHAR newName[]); // sets the caption of the window frame 

		LPVOID getLpParam(); // returns the pointer to extra data stored with window, see CREATESTRUCT
		void setLpParam(LPVOID lpParam); // sets the pointer to new extra data

		HWND getHandle(); // returns the handle of the window

		HWND getParentHandle(); //returns parent's window handle
		void setParentHandle(HWND hParent); // sets window to new parent.

		 // intitialises class
		Control(HINSTANCE hInstance, WCHAR ClassName[]);

		BOOL Create(HWND hParent, HMENU hMenu, LPVOID lpParam); // creates and displays(by default) window. Returns false if procedure fails.

		void Show(int nShowWindow);
};

class Form : protected Control 
{
	

};