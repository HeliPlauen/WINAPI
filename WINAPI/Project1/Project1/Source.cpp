#include <Windows.h>
#include <stdio.h>


int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int nCmdShow) {
	// First - is a pointer to the executive module
	// Second - useless
	// Third - pointer to the string (arguments)
	// Fourth - how to show window

	MSG msg{};
	HWND hwnd{};

	// Create Window class
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;

	// Lambda-function (The main procedure, which handles messages)
	wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT  
	{
		switch (uMsg) 
		{
			case WM_DESTROY: 
			{
				PostQuitMessage(EXIT_SUCCESS);
			}
			return 0;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);  // If message was not processed
	};

	wc.lpszClassName = L"MyAppClass";
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	printf("Window class created!\n");

	// Register Window Class, if not success - exit with the error
	if (!RegisterClassEx(&wc)) {
		printf("Window class was not registered!\n");
		return EXIT_FAILURE;
	}

	// Create Window
	hwnd = CreateWindow(wc.lpszClassName, L"Header", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr);
	printf("Window was created!\n");

	// If Window was not created - exit with error
	if (hwnd == INVALID_HANDLE_VALUE) {
		printf("Window was not created!\n");
		return EXIT_FAILURE;
	}

	// Show Window
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	printf("Window was shown!\n");

	// Handle messages
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//
	return static_cast<int>(msg.wParam);
}