#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "constants.h"

int generate_random_number(){
	return (rand() % 50);
}


void cerrar_pipes(int pipes[][2], int i, int n, int start){
	if(i == start){
		close(pipes[n+1][PIPE_WRITE]);
		close(pipes[n+2][PIPE_READ]);
	} else {
		close(pipes[n+1][PIPE_WRITE]);
		close(pipes[n+1][PIPE_READ]);
		close(pipes[n+2][PIPE_WRITE]);
		close(pipes[n+2][PIPE_READ]);
	}
	if(i == 0){
		close(pipes[0][PIPE_READ]);
		close(pipes[n][PIPE_WRITE]);
		for(int j= 1; j< n; j++){
			close(pipes[j][PIPE_READ]);
			close(pipes[j][PIPE_WRITE]);
		}
	} else {
		for(int j = 0; j < i-1; j++){
			close(pipes[j][PIPE_READ]);
			close(pipes[j][PIPE_WRITE]);
		}
		for(int j = i+1; j <= n; j++){
			close(pipes[j][PIPE_READ]);
			close(pipes[j][PIPE_WRITE]);
		}
		close(pipes[i-1][PIPE_WRITE]);
		close(pipes[i][PIPE_READ]);
	}

}

void ejecutar_hijo_inicial(int pipes[][2], int i, int n){
	int k;
	read(pipes[n+1][PIPE_READ], k, sizeof(k));
	write(pipes[i][PIPE_WRITE],k+1, sizeof(k));	
	if(i == 0){
		while(read(pipes[n][PIPE_READ], k, sizeof(k))){
			int secreto;
			read(pipes[n+1][PIPE_READ], secreto, sizeof(secreto));
			if(k>secreto){
				write(pipes[n+2][PIPE_WRITE],k, sizeof(k));
				exit(-1);
			} else {
				write(pipes[0][PIPE_WRITE], k+1, sizeof(k));
			}
		}
	}	
	while(read(pipes[i-1][PIPE_READ], k, sizeof(k))){
		int secreto;
		read(pipes[n+1][PIPE_READ], secreto, sizeof(secreto));
		if(k>secreto){
			write(pipes[n+2][PIPE_WRITE],k, sizeof(k));
		} else {
			write(pipes[i][PIPE_WRITE], k+1, sizeof(k));
		}
	}
	



}

void ejecutar_hijo(int pipes[][2], int i, int n, int start){
	int k;
	cerrar_pipes(pipes, i, n, start);
	if(i == start){
		ejecutar_hijo_inicial(pipes,i,  n);
	}
	if(i == 0){
		while(read(pipes[n][PIPE_READ], k, sizeof(k))){
			write(pipes[0][PIPE_WRITE], k+1, sizeof(k));
		}
		exit(-1);
	}
	while(read(pipes[i-1][PIPE_READ],k, sizeof(k))){
		write(pipes[i][PIPE_WRITE],k+1, sizeof(k));
	}
	exit(-1);
}



int main(int argc, char **argv)
{	
	//Funcion para cargar nueva semilla para el numero aleatorio
	srand(time(NULL));

	if (argc != 4){ printf("Uso: anillo <n> <c> <s> \n"); exit(0);}

	int status, pid, n, start, buffer;
	n = atoi(argv[1]);
	buffer = atoi(argv[2]);
	start = atoi(argv[3]);
	int pipes[n+2][2];
	
    
  	/* COMPLETAR */
    printf("Se crearán %i procesos, se enviará el caracter %i desde proceso %i \n", n, buffer, start);
    
    /* COMPLETAR */
	
	write(pipes[n+1][PIPE_WRITE], buffer, sizeof(buffer));
	for(int i=0; i <= n+2; i++){
		pipe(pipes[i]);
	}
	
	int i = 1;
	while(i <= n){
		if(fork()==0){
			ejecutar_hijo(pipes, i, n, start);
		}
		i++;
	}
	int k;
	read(pipes[n+2][PIPE_READ],k ,sizeof(k));
	printf(k);

}
