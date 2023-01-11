#pragma once
#include <windows.h>

template <class DERIVED> 
class Control // base window class
{
protected:
	virtual LRESULT MessageHandler(HWND hWND, UINT uMsg, WPARAM wParam,  LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWND, uMsg, wParam, lParam);
			break;
		}
	}

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

		void Move()
		{
			if (hWND != NULL)
			{
				MoveWindow(hWND, x, y, width, height, TRUE);
			}
		}

	public: 
		static LRESULT CALLBACK WindowProc(HWND hWND, UINT uMessage, WPARAM wParam, LPARAM lParam) {

			DERIVED* pClass = NULL;

			if (uMessage == WM_CREATE)
			{
				//Set Long ptr to the class derived from base
				CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
				pClass = (DERIVED*)pCreate->lpCreateParams;
				SetWindowLongPtr(hWND, GWLP_USERDATA, (LONG_PTR)pClass);
			}
			else 
			{
				//Get the derived class
				pClass = (DERIVED*)GetWindowLongPtr(hWND, GWLP_USERDATA);
			}

			if (pClass)
			{
				return pClass->MessageHandler(hWND, uMessage, wParam, lParam);
			}
			else
			{
				return DefWindowProc(hWND, uMessage, wParam, lParam);
			}
		}

		int getX() // returbs the x position of the window
		{
			return x;
		}

		int getY() // returns the y position of the window
		{
			return y;
		}

		void setX(int x) // sets the X position of the window
		{
			this->x = x;

			Move();
		}

		void setY(int y) // sets the Y position of the window
		{
			this->y = y;
			Move();
		}
		
		int getWidth()//returns the width of the window
		{
			return width;
		}

		int getHeight()//returns the height of the window
		{
			return height;
		}

		void setHeight(int newHeight) // sets the height of the window
		{
			height = newHeight;
			Move();
		}

		void setWidth(int newWidth) // sets the width of the window
		{
			width = newWidth;
			Move();
		}

		void setStyles(DWORD styles)
		{
			this->Styles = styles;

			if (hWND != NULL)
			{
				SetWindowLongPtrW(hWND, GWL_STYLE, styles);
				Move();//some styles require a reposition
			}
		}

		DWORD getStyles() {
			return Styles;
		}

		void setExStyles(DWORD exStyles) {
			this->ExStyles = ExStyles;

			if (hWND != NULL) {
				SetWindowLongPtrW(hWND, GWL_EXSTYLE, ExStyles);
				Move();//some styles require a reposition
			}
		}

		DWORD getExStyles() {
			return ExStyles;
		}


		WCHAR* GetWindowName() //returns the caption of the window frame
		{
			return WindowName;
		}

		void setWindowName(WCHAR newName[]) // sets the caption of the window frame 
		{
			WindowName = newName;

			if (hWND != NULL)
			{
				SetWindowTextW(hWND, newName);
			}
		}

		LPVOID getLpParam() // returns the pointer to extra data stored with window, see CREATESTRUCT
		{
			return (LPVOID)GetWindowLongPtr(hWND, GWLP_USERDATA);
		}

		void setLpParam(LPVOID lpParam) // sets the pointer to new extra data
		{}

		HWND getHandle() // returns the handle of the window
		{
			return hWND;
		}

		HWND getParentHandle() //returns parent's window handle
		{
			return hParent;
		}

		void setParentHandle(HWND hParent) // sets window to new parent.
		{
			this->hParent = hParent;

			if (hWND != NULL)
			{
				SetParent(hWND, hParent);
			}

		}


		 // intitialises class
		Control(HINSTANCE hInstance, WCHAR ClassName[]) {
			this->ClassName = ClassName;
			this->hInstance = hInstance;
			wc.hInstance = hInstance;
			wc.lpszClassName = ClassName;
			wc.lpfnWndProc = DERIVED::WindowProc;

			RegisterClass(&wc);
		};

		BOOL Create(HWND hParent, HMENU hMenu, LPVOID lpParam) // creates and displays(by default) window. Returns false if procedure fails.
		{
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
				return TRUE;
			}

			return FALSE;
		}


		BOOL Show(int nShowWindow)
		{
			return ShowWindow(hWND, nShowWindow);
		}		
};

class Form : public Control<Form> 
{
	

};