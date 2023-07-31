#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>


// Window dimentions
int width{}, heigth{};


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
			case WM_CREATE: {
				MessageBox(hWnd, L"Hello!", L"OK", MB_ICONINFORMATION);
				HWND hButton = CreateWindow(
					L"BUTTON",                              // Long pointer to class name
					L"OK",                                  // Button text
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // Flags
					0, 0, 300, 30, hWnd, 
					reinterpret_cast<HMENU>(1337), nullptr, nullptr               // hMenu, instance, lparam
				);
			}
			return 0;

			case WM_COMMAND: {
				switch (LOWORD(wParam)) {
					case 1337: {
						MessageBox(hWnd, L"DO", L"NE", MB_ICONINFORMATION);
					}
					break;
				}
			}

			case WM_SIZE: {
				width = LOWORD(lParam);
				heigth = HIWORD(lParam);
			}
			return 0;

			case WM_DESTROY: {
				PostQuitMessage(EXIT_SUCCESS);
			}
			return 0;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);  // If message was not processed
	};

	wc.lpszClassName = L"MyAppClass";
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	// Register Window Class, if not success - exit with the error
	if (!RegisterClassEx(&wc)) {
		return EXIT_FAILURE;
	}

	// Create Window
	hwnd = CreateWindow(wc.lpszClassName, L"Header", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr);

	// If Window was not created - exit with error
	if (hwnd == INVALID_HANDLE_VALUE) {
		return EXIT_FAILURE;
	}

	// Show Window
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Handle messages
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//
	return static_cast<int>(msg.wParam);
}