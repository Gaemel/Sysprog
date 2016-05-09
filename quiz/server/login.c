/*
 * Systemprogrammierung
 * Multiplayer-Quiz
 *
 * Server
 * 
 * login.c: Implementierung des Logins
 */
#include "login.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv){
	in_port_t port = 8200; 		//default port
	const size_t buf_size = 1024;
	const int backlog = 1;

	const int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	//const int listen_sock = socket(AF_INET, SOCK_STREAM, 4);

	if(listen_sock < 0){
		perror("Could not creat socket");
		return -1;
	}

	struct sockaddr_in addr;
	memset(&addr, 0 , sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	if(bind(listen_sock, (const struct sockaddr *)&addr, sizeof(addr)) < 0){
		perror("Cloud not bind socket to adress");
		return -1;
	}		

	if(lsiten(listen_sock, backlog) < 0){
		perror("Cloud not make socket to be accepting connection");
		return -1;
	}

	const int client_sock = accept(listen_sock, NULL, NULL);
	if(client_sock < 0){
		perror("Cloud not accept client connection");
		return -1;
	}

	printf("ende\n");

	return 0;
}