#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include <stdbool.h>
#include "estructura.h"
#include "procesos.h"

/**
 * @brief                  	Procesa los datos del archivo .json para crear el arbol de directorios
 * 
 * @param nombreArchivo		Nombre del archivo .json  
 * @return struct nodo* 	Nodo raíz
 */
struct nodo* leerArchivo(char *nombreArchivo);

/**
 * @brief			Crea la ruta completa de un arbol dicotomico de forma recursiva 
 * 					manipulando la pila dada en los argumentos
 * @param args 		Estructura con todos los argumentos a utilizar
 */
void recorridoDir(struct args args);

/**
 * @brief 				Crea los directorios del árbol dicotómico
 * 
 * @param nodoRaiz 		El nodo raiz del arbol de directorios
 * @param dir 			La ruta raíz a la cual añadir la ruta de la pila
 * @param trueTexto 	El texto a colocar cuando se cumple la condición
 * @param falseTexto 	El texto a colocar cuando NO se cumple la condición
 * @param concatPre 	Determina si se coloca el texto como prefijo
 * @param concatSuf 	Determina si se coloca el texto como sufijo
 * @return int 			Retorna 1 si todo sale bien
 */
int crearDirectorios(struct nodo *nodoRaiz, char *dir, char *trueTexto, char *falseTexto, bool concatPre, bool concatSuf);

#endif