
#include "Trans.h"
#include "Win.h"
#include "Img.h"

#include <iostream>
using std::cout;
using std::endl;


int main(void)
{

	HWND hwnd;
	hwnd = RunWindow();
	
	
	SOCKET sock;
	sock = Trans_Start();
	Trans_Text(sock);
	Trans_File(sock);
	Trans_Text(sock);
	Trans_End(sock);

	DrawImage(hwnd, L"ghost.png");
	
	LoopWindow(hwnd);
	


	ExitImage(hwnd);
	ExitWindow();

	
	return 0;

}