#include "Img.h"






ULONG_PTR gdiplusToken;
GdiplusStartupInput gdiplusStartupInput;

HDC hdc = 0;
Image* image = NULL;

int DrawImage(HWND hwnd, wstring filename)
{
	wstring pathfilename;
	pathfilename = L".\\" + filename;

	

	int fileExist = 0;
	fileExist = PathFileExists((LPCWSTR)pathfilename.c_str());
	if (fileExist == 0) {
		puts("FILE NOT EXISTS !");
		return 0;
	}


	
	if (fileExist)
	{
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		hdc = GetDC(hwnd);
		image = Image::FromFile((LPCWSTR)filename.c_str());
		::Graphics g(hdc);
	
		int x = 0, y = 0;
		int width	= 820;
		int height	= 420;

		g.DrawImage(image, x, y, width, height);


	}

	return 1;
}

int ExitImage(HWND hwnd)
{
	delete image;
	ReleaseDC(hwnd, hdc);


	return 1;
}

