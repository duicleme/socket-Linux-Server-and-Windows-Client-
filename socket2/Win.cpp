
#include "Win.h"

HWND hCmdWnd;


HWND GetConsoleHwnd(void)
{
#define MY_BUFSIZE 1024						// Buffer size for console window title.
	HWND hwndFound;							// This is what is returned to the caller.
	char pszNewWindowTitle[MY_BUFSIZE];		// Contains fabricated WindodwTitle.
	char pszOldWindowTitle[MY_BUFSIZE];		// Condtains original WindowTitle.

	// Fetch current window title.
	GetConsoleTitle((LPWSTR)pszOldWindowTitle, MY_BUFSIZE);

	// Format a "unique" NewWindowTitle.
	wsprintf((LPWSTR)pszNewWindowTitle, L"%d/%d", GetTickCount(), GetCurrentProcessId());

	// Change current window title.
	SetConsoleTitle((LPWSTR)pszNewWindowTitle);

	// Ensure window title has been updated.
	Sleep(40);

	// Look for NewWindowTitle.
	hwndFound = FindWindow(NULL, (LPWSTR)pszNewWindowTitle);

	// Restore original window title.
	SetConsoleTitle((LPWSTR)pszOldWindowTitle);

	return (hwndFound);

}


HWND RunWindow(void)
{
	HWND hCmdWnd = GetConsoleHwnd();
	HINSTANCE hInst = GetModuleHandle(NULL);
	const wchar_t CLASS_NAME[] = L"Window Class";

	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInst;
	wc.lpszClassName = CLASS_NAME;
	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Program Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 820, 420 + 40,
		NULL,
		NULL,
		hInst,
		NULL
	);
	if (hwnd == NULL) return 0;

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);


	return hwnd;
}

int LoopWindow(HWND hwnd)
{
	MSG Message;
	while (1)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE)) {
			if (Message.message == WM_QUIT) break;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else {

		}
	}

	return 1;

}

int ExitWindow(void)
{
	SetFocus(hCmdWnd);

	return 1;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_QUIT:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN:
		printf("Test\n");
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


