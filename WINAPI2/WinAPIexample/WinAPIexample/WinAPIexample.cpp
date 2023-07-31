#include <Windows.h>


// The main procedure
LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

	// Event processing
	switch (msg) {
	case WM_DESTROY: {    // The cross button was clicked
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
