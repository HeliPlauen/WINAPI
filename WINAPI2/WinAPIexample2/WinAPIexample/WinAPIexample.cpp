#include <Windows.h>


// The main procedure
LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	static HWND hStatic;                               // Global descriptor text
	static HWND hEdit;                                 // Global text field

	// Event processing
	switch (msg) {
	case WM_CREATE: {                                  // Create Window
		HWND hBtn = CreateWindow(
			L"BUTTON",                                 // Call for class button
			L"this_btn", 
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,     // Not independent Window, but child | wisible | button
			200, 300, 200, 35, 
			hwnd,                                      // Parent window handle
			reinterpret_cast<HMENU>(1),                // Menu (button ID = 1)
			NULL, NULL                                 // HINSTANCE | LPARAM
		);
		hStatic = CreateWindow(
			L"static",
			L"This_text",
			WS_CHILD | WS_VISIBLE,
			200, 100, 200, 20,
			hwnd, NULL, NULL, NULL
		);
		hEdit = CreateWindow(
			L"eDit",
			L"querty",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
			200, 200, 200, 20,
			hwnd, NULL, NULL, NULL
		);
		break;
	}
	case WM_COMMAND: {                                      // Process ou button click
		switch (LOWORD(wparam)) {
		case 1: {                                           // Give button ID to handler
			wchar_t buf[15];
			MessageBox(NULL, L"press_btn", L"app", MB_OK);
			GetWindowText(hEdit, buf, 14);
			SetWindowText(hStatic, buf);                    // Change text when button is pressed
			break;
		}
		}
		break;
	}
	case WM_KEYDOWN: {               // When any key was pressed		
		switch (LOWORD(wparam)) {
		case VK_ESCAPE: {
			MessageBox(NULL, L"escape", L"app", MB_OK);
			break;
		}
		case VK_TAB: {
			MessageBox(hwnd, L"tab", L"app", MB_YESNO | MB_ICONERROR);
			break;
		}
		case VK_SHIFT: {
			MessageBox(NULL, L"shift", L"app", MB_YESNOCANCEL | MB_ICONQUESTION);
			break;
		}
		}
		break;
	}
	case WM_DESTROY: {               // The cross button was clicked
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
}


// Create the main function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// Create Window descriptor
	HWND hwnd;

	// Create messdage handler
	MSG msg;

	// Create the class (structure) containing Window information an fill it by data
	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbSize = sizeof(WNDCLASSEX);                          // Window size
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);              // Large Icon
	wc.hIconSm = LoadIcon(NULL, IDI_ASTERISK);               // Small icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);                // Cursor deccriptor
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  // Window background
	wc.hInstance = hInstance;                                // Entrance point
	wc.cbClsExtra = 0;                                       // 
	wc.cbWndExtra = 0;                                       //
	wc.lpfnWndProc = WndProc;                                // !!!! Call for the main procedure function
	wc.lpszMenuName = NULL;                                  // 
	wc.lpszClassName = L"WinMainClass";                      //

	// Register the Window class
	RegisterClassEx(&wc);

	// Create our window
	hwnd = CreateWindow(
		wc.lpszClassName,
		L"App",
		WS_OVERLAPPEDWINDOW,
		0, 0, 640, 480,              // Window position and dimensions
		NULL,                        // We have no parent
		NULL, hInstance, NULL
	);

	// Show Window
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Handle messages
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
