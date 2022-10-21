#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>


#define PORT 702
#define BUF_SIZE 1024





int main ( void )
{
	printf("START ##\n");
	int server_fd;
	int client_fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t size;
	
	int recv_length;
	int send_length;
	char buf[BUF_SIZE];
	
	server_fd = socket(PF_INET, SOCK_STREAM, 0);
	if ( server_fd == -1)
		puts("socket() error");
	
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("192.168.0.2");
	server_addr.sin_port = htons(1702);
	if(bind ( server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		puts("bind() error");
	
	
	printf("Running Listen\n");
	if ( listen(server_fd, 5) == -1)
		puts("listen() error");
	
	
	size = sizeof(client_addr);
	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &size);
	if (client_fd == -1)
		puts("accept() error");
		
		
	
	// Trans_Text
	memset(buf,0,BUF_SIZE );
	recv_length = recv(client_fd, buf, BUF_SIZE, 0 );
	puts(buf);
	send( client_fd, "ACKKK",6,0);
	
	
	
	// Trans_File
	memset(buf,0,BUF_SIZE );
	recv_length = recv(client_fd, buf, BUF_SIZE, 0 );
	puts(buf);
	
	FILE *fp;
	fp = fopen(buf,"rb");
	if (fp == 0 ) 
		puts("fopen() error");
	int i = 0;
	while(1)
	{
		memset(buf,0,BUF_SIZE );
		send_length = fread( buf, 1, BUF_SIZE, fp);
		if (send_length != BUF_SIZE) 
		{
			send( client_fd, buf, send_length, 0);
			printf ("(%d,%d) ",i, send_length);
			break;
		}
		send(client_fd,buf, BUF_SIZE,0);
		printf ("(%d,%d) ",i, send_length);
		i++;
	}
	
	fclose(fp);
	puts("ENDING FILE TRANS");
	
	
	// Trans_Text
	memset(buf,0,BUF_SIZE );
	recv_length = recv(client_fd, buf, BUF_SIZE, 0 );
	puts(buf);
	send( client_fd, "ACKKK",6,0);
	
		
		
		
		
		
	close(client_fd);
	
	close ( server_fd );
		
	puts("END");
	
	return 0;
}
