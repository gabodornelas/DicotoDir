#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <unistd.h>
#include <stdio.h>
#include "validacionDatos.h"

bool esNombreArchivoValido(const char *nombreArchivo) {
	if (nombreArchivo == NULL || strlen(nombreArchivo) == 0) {
		return false;
	}
	// Check de caracteres inválidos para Windows
	const char *invalidChars = "<>:\"/\\|?*";
	for (int i = 0; nombreArchivo[i] != '\0'; ++i) {
		if (strchr(invalidChars, nombreArchivo[i]) != NULL || iscntrl(nombreArchivo[i])) {
			return false;
		}
	}

	return true;
}

bool esLineaVacia(const char *linea) {
	if (linea == NULL) 
		return true;
	
    // Verifica si la línea solo tiene espacios en blanco
    for (int i = 0; linea[i] != '\0'; i++) {
        if (!isspace((unsigned char)linea[i])) {
            return false;  // No vacía
        }
    }
    return true;  // vacía
}

char *mi_strdup(const char *s) {
	if (!s) return NULL;
	// +1 por el bit de terminación
	char *copia = malloc(strlen(s) + 1);
	if (!copia) {
		salirPorErrMem();
	}
	else {
		strcpy(copia, s);
	}
	return copia;
}

void mi_strcat(char *dest, size_t dest_tam, const char *src) {
	size_t usado = strlen(dest);
	size_t libre = dest_tam - usado;

	if (strlen(src) >= libre) {
		fprintf(stderr, "❗  Error fatal: overflow en el buffer de destino.\n");
		exit(EXIT_FAILURE);
	}
	// Espacio extra para el bit de terminación
	strncat(dest, src, libre - 1);
}

bool existeArchivo(const char *nombreArchivo) {
	// access tiene un modo dedicado a ver si existe un archivo.
	// stat también puede ser usado pero introduce mucho overhead
	// puesto que devuelve muchas variables que no necesitamos.
	if (access(nombreArchivo, F_OK) != -1) {
		return true;
	}
	else {
		return false;
	}
}

bool tieneExtension(const char *nombreArchivo, const char* extension) {
    const char *dot = strrchr(nombreArchivo, '.');
    return dot && strcmp(dot, extension) == 0;
}

void salirPorErrMem() {
	fprintf(stderr, "❗ Error fatal: no se pudo asignar la memoria. \n");
    exit(EXIT_FAILURE); 
}