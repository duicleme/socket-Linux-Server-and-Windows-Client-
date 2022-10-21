#include "Trans.h"

#define BUF_SIZE 1024
#define PORT 1702
#define SERVER_IP "192.168.0.2"

SOCKET Trans_Start(void)
{

	SOCKET clntSd = INVALID_SOCKET;
	SOCKADDR_IN srvAddr;

	WSADATA wsa;

	int res;

	res = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (res != 0) {
		fprintf(stderr, "Winsock Load Error:%d\n", res);
		WSACleanup();
		return 0;
	}

	clntSd = WSASocket(PF_INET, SOCK_STREAM, IPPROTO_TCP, 0, NULL, 0);
	if (clntSd == INVALID_SOCKET) {
		fprintf(stderr, "Socket Error: %d\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}

	ZeroMemory(&srvAddr, sizeof(srvAddr));
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(PORT);
	srvAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	res = connect(clntSd, (SOCKADDR*)&srvAddr, sizeof(srvAddr));
	if (res == SOCKET_ERROR) {
		fprintf(stderr, "connect error: %d\n", WSAGetLastError());
		closesocket(clntSd);
		WSACleanup();
		return 0;
	}

	printf("Start Trans...\n");

	return clntSd;
}

int Trans_End(SOCKET clntSd)
{
	if (clntSd != 0) closesocket(clntSd);
	WSACleanup();

	printf("End Trans...\n");
	return 1;
}


int Trans_Text(SOCKET clntSd)
{
	if (clntSd == 0) return 0;

	char writeBuff[BUF_SIZE] = "ABCDEFG";
	char readBuff[BUF_SIZE];

	int recv_length = 0;

	send(clntSd, writeBuff, (int)strlen(writeBuff), 0);

	ZeroMemory(readBuff, BUF_SIZE);
	recv_length = recv(clntSd, readBuff, BUF_SIZE, 0);

	printf("%d bytes are Received... \n", recv_length);
	fputs(readBuff, stdout);
	fputs("\n", stdout);

	puts("Text Trnas...");
	return 1;
}

int Trans_File(SOCKET clntSd)
{
	char writeBuff[BUF_SIZE] = "ghost.png";
	char readBuff[BUF_SIZE];

	send(clntSd, writeBuff, (int)strlen(writeBuff)+1, 0);


	FILE* fp;
	fp = fopen(writeBuff, "wb");

	DWORD data_transferred = 0;
	int recv_length = 0;
	int i = 0;
	while (1)
	{
		ZeroMemory(readBuff, BUF_SIZE);
		recv_length = recv(clntSd, readBuff, BUF_SIZE, 0);
		data_transferred += recv_length;
		if (recv_length != BUF_SIZE ) 
		{
			fwrite(readBuff, 1, recv_length,  fp);
			printf("(%d,%d) ", i, recv_length);
			break;
		}
		fwrite(readBuff, 1, BUF_SIZE,  fp);
		
		printf("(%d,%d) ", i, recv_length);
		i++;
		
	}
	printf("\n");
	printf("Data Transferred : %d\n", data_transferred);


	fclose(fp);

	printf("ok. image.\n");


	return 1;
}