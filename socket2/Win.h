#pragma once

#include <windows.h>
#include <stdio.h>
#include <tchar.h>




HWND GetConsoleHwnd(void);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wPARAM, LPARAM lParam);

HWND	RunWindow(void);
int		LoopWindow(HWND hwnd);
int		ExitWindow(void);



