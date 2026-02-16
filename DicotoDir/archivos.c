#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "archivos.h"
#include "estructura.h"
#include "procesos.h"
#include "validacionDatos.h"

#define TAM_BUFFER 1024

/**
 * @brief 					Transforma el contenido de un archivo .json a un string
 * 
 * @param nombreArchivo     Nombre del archivo .json
 * @return char*            String con la informacion del archivo .json
 */
static char* deArchivoACadena(char *nombreArchivo) {
    FILE* json_derulo = fopen(nombreArchivo, "rb");
    if (!json_derulo) {
        perror("Error abriendo el archivo");
        return NULL;
    }

    fseek(json_derulo, 0, SEEK_END);
    long longitud = ftell(json_derulo);
    fseek(json_derulo, 0, SEEK_SET);

    char* buffer = (char*)malloc(longitud + 1);
    if (!buffer) {
        fclose(json_derulo);
        fprintf(stderr, "Error asignando memoria\n");
        return NULL;
    }

    fread(buffer, 1, longitud, json_derulo);
    buffer[longitud] = '\0'; // La cadena debe terminar en null

    fclose(json_derulo);
    return buffer;
}

struct nodo *leerArchivo(char *nombreArchivo) {
	struct nodo *raiz;
    char* json_momoa = deArchivoACadena(nombreArchivo);
    if (json_momoa) {
        //printf("Contenido JSON:\n%s\n", json_momoa);
        //json_momoa tiene el resto del contenido
		raiz = arbolizar(json_momoa);
        // Impresion para testing si hace falta
        //impresion(raiz,0);
        free(json_momoa);
		return raiz;
    }
	return NULL;
}

void recorridoDir(struct args args) {
	// Uso el macro definido en estructura.h para desempaquetar las variables en args
	UNPACK_ARGS(args, nodoActual, pila, dir, trueTexto, falseTexto, concatPre, concatSuf);

	if (!nodoActual) return;

    char *rutaDir = crearRutaDir(pila, dir, trueTexto, falseTexto, concatPre, concatSuf);
	struct stat st = {0};
	if (stat(rutaDir, &st) == -1) {
		mkdir(rutaDir, 0700);
	}

	int status;

	// Si la caracteristica es distinta de 2, estamos en un nodo, creamos una carpeta
	if (nodoActual->caracteristica != 2) {
		apilarNodo(pila, nodoActual);
		
		// Llama a la creacion de un proceso por cada hijo
		args.nodoActual = nodoActual->sitiene;
		pid_t pid1 = crearProceso(tareaRecorrido, &args);
		args.nodoActual = nodoActual->archivo;
		pid_t pid2 = crearProceso(tareaRecorrido, &args);
		args.nodoActual = nodoActual->notiene;
		pid_t pid3 = crearProceso(tareaRecorrido, &args);
		
		// Espera a que termine su ejecucion
		waitpid(pid1, &status, 0);
		verificarEstadoProc(status);
		waitpid(pid2, &status, 0);
		verificarEstadoProc(status);
		waitpid(pid3, &status, 0);
		verificarEstadoProc(status);

		desapilarNodo(pila);
		
		// Tengo que liberar la memoria de una vez, porque cada proceso tiene su propia copia del árbol
		if (nodoActual->caracteristica == 1) {
			// De tener un solo proceso, bastaría con desapilar un nodo a la vez
			// Pero al tener varios procesos cada uno con su copia de la pila, 
			// entonces hay que desapilarlos todos en cada proceso.
			while (pila->primerNodo)
				desapilarNodo(pila);
			free(pila);
			liberarMemoriaArbol(nodoActual);
		}
	}
	// En este caso estamos en una hoja, creamos el txt de la especie
	else {
		char *rutaArchivo;
		
		if ((rutaArchivo = calloc(TAM_BUFFER, sizeof(char)))) {
			mi_strcat(rutaArchivo, TAM_BUFFER, rutaDir);
			mi_strcat(rutaArchivo, TAM_BUFFER, "/");
			mi_strcat(rutaArchivo, TAM_BUFFER, nodoActual->nombre);
			mi_strcat(rutaArchivo, TAM_BUFFER, ".txt");
			
			FILE *fptr;
			// Crea el archivo cuando usamos "w"
			fptr = fopen(rutaArchivo, "w");
			fclose(fptr);
	
			//llamamos a la siguiente hoja que comparte la misma ruta
			args.nodoActual = nodoActual->sig;
			pid_t pid4 = crearProceso(tareaRecorrido, &args);
			// Espera a que termine su ejecucion
			waitpid(pid4, &status, 0);
			verificarEstadoProc(status);
		}

		// Libera la memoria de cada copia por cada proceso
		while (pila->primerNodo)
			desapilarNodo(pila);
		free(pila);
		liberarMemoriaArbol(nodoActual);
	}
}

int crearDirectorios(struct nodo *nodoRaiz, char *dir, char *trueTexto, char *falseTexto, bool concatPre, bool concatSuf) {
	// A pesar de que esta función principalmente llama a recorridoDir
	// me gustaría conservar esta separación entre la función recorridoDir
	// y esta que el usuario llama, así se logra un mejor encapsulamiento
	struct pilaNodo *pila = crearPilaNodo(NULL);

	// Ahora creo la estructura que pasaré como argumento al llamar a las otras funciones
	struct args args = {
		nodoRaiz,
		pila,
		dir,
		trueTexto,
		falseTexto,
		concatPre,
		concatSuf
	};

	recorridoDir(args);

	return 1;
}
