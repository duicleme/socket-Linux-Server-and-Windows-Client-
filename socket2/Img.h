#pragma once

#include <string>
using std::wstring;


#include <Windows.h>
#include <Gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;


#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

int DrawImage(HWND hwnd, wstring filename);
int ExitImage(HWND hwnd);
