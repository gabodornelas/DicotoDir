#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H
#include <stdbool.h>

/**
 * @brief Este macro es para obtener rápidamente las variables desde el struct de argumentos
 * 
 */
#define UNPACK_ARGS(args_, nodoActual, pila, dir, trueTexto, falseTexto, concatPre, concatSuf) \
	struct nodo *nodoActual = (args).nodoActual; \
	struct pilaNodo *pila = (args).pila; \
	char *dir = (args).dir; \
	char *trueTexto = (args).trueTexto; \
	char *falseTexto = (args).falseTexto; \
	bool concatPre = (args).concatPre; \
	bool concatSuf = (args).concatSuf;

struct nodo {
	char *nombre;
    int caracteristica; //true = 1, false = 0, si el nodo es una hoja = 2
    int indiceRetorno;
    struct nodo *padre;
    struct nodo *sitiene;
    struct nodo *notiene;
    struct nodo *archivo;
    struct nodo *sig; //si mas de una especie tiene la misma ruta
};

struct elemNodo {
    struct nodo *nodo;
    struct elemNodo *sigElemNodo;
    struct elemNodo *antElemNodo;
};

struct pilaNodo {
    struct elemNodo *primerNodo;
    struct elemNodo *ultimoNodo;
};

struct args {
    struct nodo *nodoActual;
    struct pilaNodo *pila;
    char *dir;
    char *trueTexto;
    char *falseTexto;
    bool concatPre;
    bool concatSuf;
};

/**
 * @brief                   Crea la estructura nodo asignando la memoria requerida
 * 
 * @param nombre            El nombre del nodo
 * @return struct nodo*     El nodo creado
 */
struct nodo *crearNodo(char *nombre);

/**
 * @brief                   Crea un elemento de una lista/pila de nodos
 * 
 * @param nodo              Nodo del elemento en cuestión
 * @return struct elemNodo* Devuelve el elemento creado
 */
struct elemNodo *crearElemNodo(struct nodo *nodo);

/**
 * @brief                   Crea una pila de elementos de nodos
 * 
 * @param elemNodo          Elemento del nodo en cuestión
 * @return struct pilaNodo* Pila creada
 */
struct pilaNodo *crearPilaNodo(struct elemNodo *elemNodo);

/**
 * @brief       Apila un nodo en la lista de nodos
 * 
 * @param pila  Pila de elementos de nodos
 * @param nodo  Nodo a agregar
 */
void apilarNodo(struct pilaNodo *pila, struct nodo *nodo);
/**
 * @brief           Remueve el último elemento de nodo añadido
 * 
 * @param pilaNodo  Pila de elementos de nodos
 */
void desapilarNodo(struct pilaNodo *pilaNodo);

/**
 * @brief               Crea la ruta completa de un directorio basado en la pila dada
 * 
 * @param pila          Pila en cuestión
 * @param rutaRaiz      La ruta raíz a la cual añadir la ruta de la pila
 * @param trueTexto     El texto a colocar cuando se cumple la condición
 * @param falseTexto    El texto a colocar cuando NO se cumple la condición
 * @param concatPre     Determina si se coloca el texto como prefijo
 * @param concatSuf     Determina si se coloca el texto como sufijo
 * @return char*        La ruta completa
 */
char *crearRutaDir(struct pilaNodo *pila, char *rutaRaiz, char *trueTexto, char *falseTexto, bool concatPre, bool concatSuf);

/**
 * @brief                       Obtiene el nombre y crea el nodo raiz
 * 
 * @param contenido             el contenido del archivo .json
 * @return struct nodo*         el nodo raiz creada
 */
struct nodo *principal(char* contenido);

/**
 * @brief                       Ubica el nuevo nodo en el árbol de nodos
 * 
 * @param actual                el nodo actual en el árbol
 * @param caracteristica        la caracteristica del nodo a agregar
 * @param pregunta              el nombre del nuevo nodo a ubicar
 * @param especie               la especie que se esta procesando
 * @return struct nodo* 
 */
struct nodo *ubicarEnArbol(struct nodo *actual, int caracteristica, char *pregunta, struct nodo *especie);

/**
 * @brief                   funcion que verifica si un nombre de especie esta repetido
 * 
 * @param raiz              el nodo raiz del arbol
 * @param nombreEspecie     el nombre a verificar
 * @return true             cuando se encuentra el nombre
 * @return false            cuando no se encuentra el nombre
 */
bool nombreRepetido(struct nodo *raiz, char *nombreEspecie);

/**
 * @brief                       Convierte el contenido del archivo .json en nodos para su posterior manipulacion
 * 
 * @param contenido             el contenido del archivo .json en un string
 * @return struct nodo*         el nodo raiz
 */
struct nodo *arbolizar(char* contenido);

/**
 * @brief           Libera de la memoria todos los nodos de un arbol desde su raíz
 *                  yendo por cada hijo de forma recursiva
 * @param nodo      La raíz desde la cual partir
 */
void liberarMemoriaArbol(struct nodo *nodo);

#endif