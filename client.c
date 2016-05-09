#include <stdio.h>
#include <srting.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char **argv){

	const char *port = "1234";
	const size_t buf_size = 1024;

	if(argc != 2){
		fprintf(stderr, "usage: %s HOSTNAME\n", argv[0]);
		return -1;
	}

	struct addrifo hints;
	memset(&hints, 0, sizeof (hints));
	hints.ai_flags = AI_NUMERICSERV;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;

	struct addrinfo *gai_res;
	const int gai_status = getaddrinfo(argv[1], port, &hints, &gai_res);
	if(gai_status != 0){
		fprintf(stderr, "Could not resolve hostname: %s\n", gai_strerror(gai_sta));
	}

	int sock = -1;
	for(const struct addrinfo *it=gai_res; it!= NULL && sock==-1; it=it -> ai_next){
		sock = socket(it->ai_family, it->ai_socktype, it->ai_protocol);
		if(sock >= 0){
			if(connect(sock, it->ai_addr, it->ai_addrlen) != -1){
				fprintf(stderr, "Connected.\n");
			}else{
				close(sock);
			}
		}
	}

	freeaddrinfo(gai_res);

	if(sock == -1){
		fprintf(stderr, "Unable to get a connection.\n");
		return -1;
	}

	char buff[buf_size];
	ssiz_t bytes_read_stdin, bytes_read_socket;
	while((bytes_read_socket = read(STDIN_FILENO, buf, buf_size)) > 0){
		if(write(sock, buf, (size_t)bytes_read_socket) != bytes_read_stdin){
			perror("Error sending message");
			return -1;
		}

		bytes_read_socket = read(sock, buf, buf_size);
		if(bytes_read_socket < 0){
			perror("Error receiving data");
			return -1;
		}

		printf("respinse: ");
		fwrite(buf, 1, bytes_read_socket, stdout);
		fflush(stdout);
	}

	close(sock);

	return 0;
}