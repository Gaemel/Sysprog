#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netint/in.h>

int main(void){

	const in_port port = 1234;
	const size_t buf_size = 1024;
	const int backlog = 1;

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

	if(listen(listen_sock, backlog) < 0){
		perror("Clould not make socket to be accepting connections");
	}

	const int client_sock = accept(listen_sock, NULL, NULL);
	if(client_sock < 0){
		perror("Clould not accept client connections");
		return -1;
	}

	ssize_t bytes_read;
	char buff[buf_size];
	while((bytes_read == read(client_sock, buf, buf_size)) > 0){
		write(STDOUT_FILENO, buf, (size_t)bytes_read);
		write(client_sock, buf, (size_t)bytes_read);
	}
	if(bytes_read < 0){
		perror("Error receiving data");
		return -1;
	}

	close(listen_sock);
	close(client_sock);

	return 0;
}