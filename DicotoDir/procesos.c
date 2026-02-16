#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "estructura.h"
#include "archivos.h"

pid_t crearProceso(void (*func)(void *), void *args) {
	pid_t pid = fork();

	if (pid < 0) {
		perror("Falló el fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) {
		// Ejecutado por el hijo
		func(args);
		exit(EXIT_SUCCESS);
	}

	// Ejecutado por el padre
	return pid;
}

void tareaRecorrido(void *args) {
	struct args arg = *(struct args *)args;
	recorridoDir(arg);
}

void verificarEstadoProc(int status) {
	if (WIFEXITED(status)) { 
		int cod_exit = WEXITSTATUS(status);
		if (cod_exit != 0) {
			exit(EXIT_FAILURE);
		}
	}
}