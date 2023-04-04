#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "constants.h"
#include "mini-shell-parser.c"

//execvp()

void ejecutar_hijo_n(int pipes[][2], int i, char** progs,  int count){
	//BORDE IZQUIERDO
	if(i == 0){
		close(pipes[0][PIPE_READ]);
		for(int j=1; j < count; j++){
			close(pipes[j][PIPE_READ]);
			close(pipes[j][PIPE_WRITE]);
		}
		dup2(pipes[0][PIPE_WRITE], STD_OUTPUT);
		execvp(progs[0], progs);
		exit(-1);
	}
	//BORDE DERECHO
	if(i == count){
		for(int j = 0; j < count-1 ; j++){
			close(pipes[j][PIPE_READ]);
			close(pipes[j][PIPE_WRITE]);
		}
		close(pipes[count-1][PIPE_WRITE]);
		dup2(pipes[count-1][PIPE_READ], STD_INPUT);
		execvp(progs[0], progs);
		exit(-1);
	}
	//MEDIO
	for(int j= 0; j < i-1; j++){
		close(pipes[j][PIPE_READ]);
		close(pipes[j][PIPE_WRITE]);
	}
	for(int j= i+1; j < count - 1; j++){
		close(pipes[j][PIPE_READ]);
		close(pipes[j][PIPE_WRITE]);
	}
	close(pipes[i-1][PIPE_WRITE]);
	close(pipes[i][PIPE_READ]);
	dup2(pipes[i-1][PIPE_READ], STD_INPUT);
	dup2(pipes[i][PIPE_WRITE], STD_OUTPUT);
	execvp(progs[0], progs);
	exit(-1);

}

static int run(char ***progs, size_t count)
{	
	int r, status;

	//Reservo memoria para el arreglo de pids
	//TODO: Guardar el PID de cada proceso hijo creado en children[i]
	pid_t *children = malloc(sizeof(*children) * count);

	int pipes[count -1][2];
	//TODO: Pensar cuantos procesos necesito
    for(int i = 0; i< count-1; i++){
		pipe(pipes[i]);
	}

	for(int i=0; i < count; i++){
		children[i] = fork();
		if(children[i] == 0){
			ejecutar_hijo_n(pipes,i, progs[i], count);
		}
		
	}
	//TODO: Pensar cuantos pipes necesito.


	//TODO: Para cada proceso hijo:
			//1. Redireccionar los file descriptors adecuados al proceso
			//2. Ejecutar el programa correspondiente

	//Espero a los hijos y verifico el estado que terminaron
	for (int i = 0; i < count; i++) {
		waitpid(children[i], &status, 0);

		if (!WIFEXITED(status)) {
			fprintf(stderr, "proceso %d no terminó correctamente [%d]: ",
			    (int)children[i], WIFSIGNALED(status));
			perror("");
			return -1;
		}
	}
	r = 0;
	free(children);

	return r;
}



int main(int argc, char **argv)
{
	int programs_count;
	char*** programs_with_parameters = parse_input(argv, &programs_count);

	printf("status: %d\n", run(programs_with_parameters, programs_count));

	fflush(stdout);
	fflush(stderr);

	return 0;
}
