#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>


#define PORT 1702
#define BUF_SIZE 1024





int main ( void )
{
	int socket_fd;
	struct sockaddr_in server_addr;

	char message[BUF_SIZE];
	int recv_length;
	
	socket_fd = socket(PF_INET, SOCK_STREAM, 0 );
	
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("192.168.0.2");
	server_addr.sin_port=htons(PORT);
	
	if ( connect ( socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr) ) == -1)
		puts("connect() error"); 
	else
		puts("Connected");
	
	
		
	
	return 0;
}
