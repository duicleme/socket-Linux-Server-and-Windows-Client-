#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

SOCKET	Trans_Start(void);
int		Trans_End(SOCKET clntSd);

int		Trans_Text(SOCKET clntSd);
int		Trans_File(SOCKET clntSd);

