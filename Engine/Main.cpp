#include <Windows.h>
#include <string>
#include <stdint.h>

LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);

int main()
{



	std::wstring className = L"Craft Engine Window";
	std::wstring title = L"Craft Engine";

	uint32_t width = 1280;
	uint32_t height = 800;


	HINSTANCE hInstance = GetModuleHandle(nullptr);
	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className.c_str();


	if (!RegisterClass(&wc))
	{
		return 0;
	}


	RECT rect = {};
	rect.left = 0;
	rect.top = 0;
	rect.right = width;
	rect.bottom = height;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);


	uint32_t windowWidth = rect.right - rect.left;
	uint32_t windowHeight = rect.bottom - rect.top;


	uint32_t positionX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
	uint32_t positionY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;


	HWND hwnd = CreateWindow(
		className.c_str(),               // Window class
		title.c_str(),                   // Window text
		WS_OVERLAPPEDWINDOW,            // Window style


		positionX, positionY,
		windowWidth, windowHeight,

		nullptr,       // Parent window    
		nullptr,       // Menu
		hInstance,      // Instance handle
		nullptr        // Additional application data
	);


	if (!hwnd)
	{
		return 0;
	}


	//RECT rect2;
	//GetClientRect(hwnd, &rect2);


	ShowWindow(hwnd, SW_SHOW);


	MSG msg = { };

	while (msg.message != WM_QUIT)
	{


		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{

			TranslateMessage(&msg);


			DispatchMessage(&msg);
		}

	
		else
		{

		}
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}