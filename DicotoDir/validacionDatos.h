#ifndef VALIDATOS_H
#define VALIDATOS_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief 				Hace verificaciones básicas de si un string puede ser 
 * 						un nombre de archivo válido. NO verifica si el archivo
 * 						o si el directorio existe. 
 * 
 * @param nombreArchivo El nombre del archivo en cuestión.
 * @return true 
 * @return false 
 */
bool esNombreArchivoValido(const char *nombreArchivo);

/**
 * @brief 		Verifica si el string en cuestión está vacío
 * 				
 * @param linea String a verificar
 * @return int 
 */
bool esLineaVacia(const char *linea);

/**
 * @brief 			Copia un string manejando la memoria de forma segura.
 * 					Aunque existe strdup, es específico de UNIX.
 * 					Esta función debería ser compatible con cualquier sistema.
 * @param s 		String a copiar
 * @return char* 	El puntero con el string copiado
 */
char *mi_strdup(const char *s);

/**
 * @brief 			Hace append a un buffer de forma segura.
 * 
 * @param dest 		Buffer al cual agregarle más caracteres
 * @param dest_tam 	Tamaño del buffer
 * @param src 		String a agregar en el buffer
 */
void mi_strcat(char *dest, size_t dest_tam, const char *src);

/**
 * @brief					Determina si un archivo existe
 * 
 * @param nombreArchivo 	Dirección del archivo a buscar
 * @return true 
 * @return false 
 */
bool existeArchivo(const char *nombreArchivo);

/**
 * @brief 					Determina si un archivo tiene una determina extension.
 * 							Solo revisa la extensión del archivo, no garantiza su formato adecuado
 * @param nombreArchivo 	Dirección del archivo a buscar
 * @param extension 		Extensión a buscar (con el punto)
 * @return true 
 * @return false 
 */
bool tieneExtension(const char *nombreArchivo, const char* extension);

/**
 * @brief 	Imprime en consola un mensaje de error e inmediatamente termina el programa
 * 
 */
void salirPorErrMem();

#endif