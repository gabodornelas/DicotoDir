#ifndef PROCESOS_H
#define PROCESOS_H
#include <unistd.h>

/**
 * @brief 			Crea un proceso con una función y argumentos genéricos
 * 
 * @param func 		Apuntador a la función a ejecutar
 * @param args 		Variable o estructura de argumentos a pasar a la función
 * @return pid_t 	Devuelve el pid del proceso
 */
pid_t crearProceso(void (*func)(void *), void *args);

/**
 * @brief 			Hace los castings necesarios para crear la tarea de la función de recorridoDir
 * 					y así crear un proceso
 * @param args 		Estructura de argumentos tal como se define para los nodos del árbol
 */
void tareaRecorrido(void *args);

/**
 * @brief 			Verifica que el proceso hijo haya sido exitoso.
 * 					De lo contrario, termina la ejecución.
 * @param status 	el status del proceso hijo.
 */
void verificarEstadoProc(int status);

#endif