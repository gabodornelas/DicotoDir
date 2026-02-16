#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
// Headers de nuestros archivos
#include "validacionDatos.h"
#include "archivos.h"
#include "impresion.h"
#include "estructura.h"

int main(int argc, char** argv) {
	/* Parámetros, con valores predeterminados */
	char *clave = argv[1];
	char *dir = mi_strdup("./dicot");
	char *trueTexto = mi_strdup("Sí tiene");
	char *falseTexto = mi_strdup("No tiene");
	bool concatPrefijo = true;
	bool concatSufijo = false;

	// Para comprobación
	bool hayPre = false;
	bool haySuf = false;

	/* Aquí empieza el manejo de las flags de la terminal */
	
	// Esto se usa para verificar opciones largas y cortas
	static struct option long_options[] ={
		// Estas opciones las distinguimos por sus índices.
		{"dir",	required_argument,	0, 'd'},
		{"true",	required_argument,	0, 't'},
		{"false",	required_argument,	0, 'f'},
		{"pre",	no_argument,		0, 'p'},
		{"suf",	no_argument,		0, 's'},
		{"help",	no_argument,		0, 'h'},
		{0, 0, 0, 0}
	};

	int opt;
	int opt_ind = 0;

	// Manejo de flags
	while ((opt = getopt_long(argc, argv, ":d:t:f:psh", long_options, &opt_ind)) != -1) {
		switch (opt) {
			case 'd': 
				free(dir);
				dir = mi_strdup(optarg);
				if (!dir) salirPorErrMem();
				struct stat st = {0};
				if (stat(dir, &st) == -1) {
					if (mkdir(dir, 0700) == -1)
						printf("Error: %s\n", strerror(errno));
				}
				break;
				
			case 't': 
				free(trueTexto);
				trueTexto = mi_strdup(optarg);
				if (!trueTexto) salirPorErrMem();
				break;

			case 'f':
				free(falseTexto);
				falseTexto = mi_strdup(optarg);
				if (!falseTexto) salirPorErrMem();
				break;

			case 'p':
				hayPre = true;
				concatPrefijo = true;
				break;
			
			case 's':
				haySuf = true;
				concatSufijo = true;
				break;

			case 'h':
				mensajeAyuda();
				return 0;

			case ':':
				fprintf(stderr, "❌ No ingresaste los argumentos necesarios para la opción %s\n", argv[optind - 1]);
				return 1;

			case '?':
				if (optopt)
					fprintf(stderr, "❌ Opción inválida: -%c\nUsa la flag --help para más información.\n", optopt);
				else if (argv[optind - 1])
					fprintf(stderr, "❌ Opción inválida: %s\nUsa la flag --help para más información.\n", argv[optind - 1]);
				else
					fprintf(stderr, "❌ Ocurrió un error. Usa la flag --help para más información.\n");
                return 1;
		}
	}

	/* Comprobación del nombre de archivo adecuado */
	if (!clave) {
		printf("❌ Necesitas indicar el nombre del archivo .json con la clave dicotómica.\n\n");
		return -1;
	}
	else if (!tieneExtension(clave, ".json")) {
		printf("❌ Necesitas indicar un archivo .json.\n\n");
		return -1;
	}
	else if (!existeArchivo(clave)) {
		printf("❌ La dirección que indicaste es incorrecta, no se encontró el archivo.\n\n");
		return -1;
	}
	
	// Al activar -s se debe desactivar -p, a menos que -p también se active expresamente.
	if (haySuf && !hayPre)
		concatPrefijo = false;

	clock_t inicio = clock();
	
	struct nodo *raiz = leerArchivo(clave);

	if (crearDirectorios(raiz, dir, trueTexto, falseTexto, concatPrefijo, concatSufijo)) {
		printf("✅ Se ha creado el directorio %s para su árbol dicotómico %s con éxito.\n\n", dir, clave);
	}
	else {
		printf("❌ Ocurrió un error. Asegúrate de que el directorio sea correcto.\n");
	}

	liberarMemoriaArbol(raiz);
	
	clock_t final = clock();
	double tiempo_ejecucion = (double)(final - inicio) / CLOCKS_PER_SEC;
	printf("⏱️  Tiempo de ejecución para la creación de directorios: %fs\n", tiempo_ejecucion);
	return 0;
}