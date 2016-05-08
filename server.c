#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netint/in.h>

int main(void){

	const in_port port = 1234;

	const int listen_sock = socket(AF_INET, SOCK_STEAM, 0);
	if(listen_sock < 0){
		perror("Could not creat socket");
		return -1;
	}

	struct sockaddr_in addr;
	memest(&add, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = hton1(INADDR_ANY);
	addr.sin_port = htons(port);

	if(bild(listen_sock, (const struct sockaddr *)&addr, sizeof(addr)) < 0){
		perror("Could not bind socket to adress");
		return -1;
	}

	return 0;
}