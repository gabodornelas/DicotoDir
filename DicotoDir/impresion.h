#ifndef IMPRESION_H
#define IMPRESION_H
#include "estructura.h"
/**
 * @brief Imprime un mensaje de ayuda para usar el programa en la terminal.
 * 
 */
void mensajeAyuda();

/**
 * @brief           Imprime la estructura del arbol, solo para debugging
 * 
 * @param raiz      la carpeta raiz
 * @param esp       un caracter de espacio para la impresion
 */
void impresion(struct nodo *raiz, int esp);

/**
 * @brief               Imprime un warning cuando no se cumple el orden de las preguntas
 * 
 * @param especie       la especie que tiene las preguntas desordenadas /o que comparte ruta con otra
 * @param pregunta      el nombre del nodo a ubicar en el arbol /o un texto para el caso de que la condicion sea 2
 * @param hijo          el nodo hijo que correspondia /o  el archivo que ya pertenece a la ruta
 */
void warning(struct nodo *especie, char *pregunta, struct nodo *hijo);

/**
 * @brief           funcion que imprime una advertencia de especie repetida
 * 
 * @param especie   el nombre de la especie repetida
 */
void repetido(char *especie);

#endif