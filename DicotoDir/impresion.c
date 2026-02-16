#include <stdio.h>
#include "impresion.h"
#include "estructura.h"

void mensajeAyuda() {
    char *nombrePrograma = "dicotodir";
    printf("Programa %s\n", nombrePrograma);
    printf("Descripción: Crea un directorio de archivos en base a una clave dicotómica.\n");
    printf("Uso: %s <clave> [opciones] [argumentos] \n", nombrePrograma);
	printf("     <clave> es un archivo en JavaScript Object Notation (JSON) conteniendo\n");
	printf("     la clave dicotómica\n");
    printf("\n Opciones:\n\n");
    printf("  %-3s %-14s %s\n", "-h,", 	"--help", "Muestra este mensaje de ayuda.");
	printf("\n");
	printf("  %-3s %-14s %s\n", "-d,", 	"--dir <dir>", "Indica la ruta donde se crearán los directorios");
	printf("  %-3s %-14s %s\n", "", "",	"dicotómicos.");
	printf("  %-3s %-14s %s\n", "", "",	"Si no se indica, se asume que será en una carpeta dentro");
	printf("  %-3s %-14s %s\n", "", "",	"del directorio actual.");
	printf("\n");
	printf("  %-3s %-14s %s\n", "-t,", 	"--true <p1>", "Indica qué se le debe concatenar a las preguntas para");
	printf("  %-3s %-14s %s\n", "", "",	"formar el nombre del directorio donde la pregunta sí se");
	printf("  %-3s %-14s %s\n", "", "",	"cumple.");
	printf("  %-3s %-14s %s\n", "", "",	"<p1> es este texto (por defecto \"Sí tiene\")");
	printf("\n");
	printf("  %-3s %-14s %s\n", "-f,", 	"--false <p2>", "Indica qué se le debe concatenar a las preguntas para");
	printf("  %-3s %-14s %s\n", "", "",	"formar el nombre del directorio donde la pregunta NO se");
	printf("  %-3s %-14s %s\n", "", "",	"cumple.");
	printf("  %-3s %-14s %s\n", "", "",	"<p2> es este texto (por defecto \"No tiene\")");
	printf("\n");
	printf("  %-3s %-14s %s\n", "-p,", 	"--pre", "Indica que los textos deben ser concatenados como prefijos.");
	printf("  %-3s %-14s %s\n", "", "", "Este flag está activo por defecto.");
	printf("\n");
	printf("  %-3s %-14s %s\n", "-s,", 	"--suf", "Indica que los textos deben ser concatenados como sufijos.");
	printf("  %-3s %-14s %s\n", "", "",	"Este flag está inactivo por defecto, su activación resulta");
	printf("  %-3s %-14s %s\n", "", "",	"en la desactivación de pre, a menos que ambas flag sean");
	printf("  %-3s %-14s %s\n", "", "",	"recibidas.");
}

void impresion(struct nodo *raiz, int esp){
	struct nodo *actual = raiz;
	for(int i=0;i<esp;i++) 
		printf("\t");

	printf("%s%d\n",raiz->nombre,raiz->caracteristica);

	if(actual->sitiene != NULL)
		impresion(actual->sitiene,esp+1);

	if(actual->archivo != NULL)
		impresion(actual->archivo,esp+1);

	if(actual->sig != NULL)
		impresion(actual->sig,esp);

	if(actual->notiene != NULL)
		impresion(actual->notiene,esp+1);
}

void warning(struct nodo *especie, char *pregunta, struct nodo *hijo){
	printf("⚠️ La especie '%s' tenia las preguntas desordenadas,\n'%s' no coincide con '%s', que era el nodo establecido previamente. Se omitio la especie por no seguir el orden\n",especie->nombre, pregunta,hijo->nombre);
	printf("\n");
}

void repetido(char *especie){
	printf("⚠️ La especie '%s' se omitio porque tiene el mismo nombre que otra especie previamente establecida.\n", especie);
	printf("\n");
}
