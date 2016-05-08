#include <stdio.h>
#include <unistd.h>

int main(void){

	const char *program_name = "/home/user/Schreibtisch/Uni/SysProg/neu/Aufgabe_2/waitForME.c";
	pid_t forkResult;

	int stdinPipe[2];
	int stdouPipe[2];

	// creating pipes

	if(pipe(stdinPipe) == -1 || pipe(stdouPipe) == -1){
		perror("pipe");
		return -1;
	} 

	// Kindprozess abschnitt

	forkResult = fork();
	if(forkResult < 0){
		perror("fork");
		return 1;
	}
	else if(forkResult == 0){
		//child
		execl(program_name, program_name, NULL);
		perror("execlr");
		return -1;
	}
	else{
		//parent
		printf("child was stated.");
		return 0;
	}
}