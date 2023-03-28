#include <signal.h> /* constantes como SIGINT*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
-Se lanzan 2 procesos, uno siendo el padre (hai64) y el otro siendo el hijo
que se crea clonando a hai64
-El padre utiliza kill para enviar la señal SIGURG al hijo, que hace un write con el 
mensaje "ya va"
-El programa crea un hijo (clon del padre), y hace que cada uno haga un write.
El padre imprime en pantalla "sup?" y le manda una señal al hijo, para que diga "ya va", 
esto se repite varias veces hasta 
*/
int contador = 0;

void sigurg_handler(int sig){
	printf("ya va!\n");
	contador++;

}

int main(int argc, char* argv[]) {
  	// Completar
	pid_t* pid = fork();
	int i=0;
	if(pid ==0){
		signal(SIGURG, sigurg_handler);
		while (contador < 4){}
		execvp(argv[1], argv + 1);
		exit(EXIT_SUCCESS);
	} else {
		while(i< 4){
			sleep(1);
			printf("sup!\n");
			kill(pid, SIGURG);
			i++;
	    }
		wait(NULL);
	}
	
	
	return 0;
}
