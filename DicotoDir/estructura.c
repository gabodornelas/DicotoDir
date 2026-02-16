#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "estructura.h"
#include "impresion.h"
#include "validacionDatos.h"

#define TAM_BUFFER 1024

struct nodo *crearNodo(char *nombre){
    // Al usar calloc en vez de malloc se inicializan todos los campos del struct
    struct nodo *nuevoNodo = calloc(1, sizeof(struct nodo));
    if (!nuevoNodo) {
        fprintf(stderr, "❗ Error al asignar memoria.\n");
        return NULL;
    }
    nuevoNodo->nombre = nombre;
    //por defecto diremos que es 2, o sea, que no tiene caracteristica
    nuevoNodo->caracteristica = 2;
    return nuevoNodo;
}

struct elemNodo *crearElemNodo(struct nodo *nodo) {
    struct elemNodo *nuevoElem = calloc(1, sizeof(struct elemNodo));
    if (!nuevoElem) {
        fprintf(stderr, "❗ Error al asignar memoria.\n");
        return NULL;
    }
    nuevoElem->nodo = nodo;
    return nuevoElem;
}

struct pilaNodo *crearPilaNodo(struct elemNodo *elemNodo) {
    struct pilaNodo *nuevaPila = calloc(1, sizeof(struct pilaNodo));
    if (!nuevaPila) {
        fprintf(stderr, "❗ Error al asignar memoria.\n");
        return NULL;
    }
    nuevaPila->primerNodo = elemNodo;
    nuevaPila->ultimoNodo = elemNodo;
    return nuevaPila;
}

void apilarNodo(struct pilaNodo *pila, struct nodo *nodo) {
    struct elemNodo *nuevo = crearElemNodo(nodo);
    if (!nuevo) return;

    if (!pila->primerNodo) {
        pila->primerNodo = pila->ultimoNodo = nuevo;
    } 
    else {
        pila->ultimoNodo->sigElemNodo = nuevo;
        nuevo->antElemNodo = pila->ultimoNodo;
        pila->ultimoNodo = nuevo;
    }
}

void desapilarNodo(struct pilaNodo *pila) {
    if (!pila->primerNodo) 
        return;

    struct elemNodo *aEliminar = pila->ultimoNodo;
    pila->ultimoNodo = aEliminar->antElemNodo;

    if (pila->ultimoNodo) {
        pila->ultimoNodo->sigElemNodo = NULL;
    }
    else {
        pila->primerNodo = NULL; // Pila vacía
    }

    free(aEliminar);
}

char *crearRutaDir(struct pilaNodo *pila, char *rutaRaiz, char *trueTexto, char *falseTexto, bool concatPre, bool concatSuf) {
    struct elemNodo *elemAct = pila->primerNodo;
    char *rutaDir = calloc(TAM_BUFFER, sizeof(char));
    if (!rutaDir) {
        fprintf(stderr, "❗ Error al asignar memoria.\n");
        return NULL;
    }
    mi_strcat(rutaDir, TAM_BUFFER, rutaRaiz);
    if (!elemAct) return rutaDir;

    while(elemAct) {
        mi_strcat(rutaDir, TAM_BUFFER, "/");
        if (concatPre) {
            if (elemAct->nodo->caracteristica != 2 &&
                elemAct->nodo->caracteristica != -1) {
                if (elemAct->nodo->caracteristica == 1) {
                    mi_strcat(rutaDir, TAM_BUFFER, trueTexto);
                }
                else if (elemAct->nodo->caracteristica == 0) {
                    mi_strcat(rutaDir, TAM_BUFFER, falseTexto);
                }
                mi_strcat(rutaDir, TAM_BUFFER, " ");
            }
        }
        mi_strcat(rutaDir, TAM_BUFFER, elemAct->nodo->nombre);
        if (concatSuf) {
            if (elemAct->nodo->caracteristica != 2 &&
                elemAct->nodo->caracteristica != -1) {
                mi_strcat(rutaDir, TAM_BUFFER, " ");
                if (elemAct->nodo->caracteristica == 1) {
                    mi_strcat(rutaDir, TAM_BUFFER, trueTexto);
                }
                else if (elemAct->nodo->caracteristica == 0) {
                    mi_strcat(rutaDir, TAM_BUFFER, falseTexto);
                }
            }
        } 
        elemAct = elemAct->sigElemNodo;
    }
    return rutaDir;
}

struct nodo *principal(char* contenido){
    int longitudNombre = 0, i=0;
    long longitud = strlen(contenido);
    struct nodo *raiz = NULL;
    char *nombre = NULL;
    while(i < longitud) {
        if(contenido[i] == '"') {
            i++;
            while (contenido[i] != '"') {
                //reservar espacio para longitud + 1 (nuevo caracter + '\0')
                nombre = realloc(nombre, (longitudNombre + 2));
                if (!nombre) {
                    fprintf(stderr, "❗ Error al asignar memoria.\n");
                    return NULL;
                }
                nombre[longitudNombre] = contenido[i];// Agregar letra
                nombre[longitudNombre + 1] = '\0';// Terminar cadena
                longitudNombre++;
                i++;
            }
            int tamNombre = strlen(nombre) + 1;
            char *nombreRaiz = calloc(tamNombre, sizeof(char));
            if (!nombreRaiz) salirPorErrMem();
            mi_strcat(nombreRaiz, tamNombre, nombre);
            raiz = crearNodo(nombreRaiz);
            i++;
            raiz->indiceRetorno = i;
            raiz->caracteristica = -1;
            return raiz;
        }
        i++;
    }
    return NULL;
}

struct nodo *ubicarEnArbol(struct nodo *actual, int caracteristica, char *pregunta, struct nodo *especie) {
    //Verifico si ese nodo existe
    if(caracteristica) {
        if(actual->sitiene != NULL){
            if(strcmp(pregunta,actual->sitiene->nombre) == 0) {
                return actual->sitiene;
            }
            else {
                warning(especie,pregunta,actual->sitiene);
                return NULL;
            }  
        }
    }
    else {
        if(actual->notiene != NULL){
            if(strcmp(pregunta,actual->notiene->nombre) == 0) {
                return actual->notiene;
            }
            else {
                warning(especie,pregunta,actual->notiene);
                return NULL;
            }
        }
    }
    return actual;
}

bool nombreRepetido(struct nodo *raiz, char *nombreEspecie){
    bool si = false, no = false, ar = false, sig = false;
    if(raiz->caracteristica == 2 && strcmp(raiz->nombre,nombreEspecie) == 0){
        return true;
    }
	if(raiz->sitiene != NULL){
		si = nombreRepetido(raiz->sitiene,nombreEspecie);
        if(si){
            return si;
        }
    }
	if(raiz->archivo != NULL){
		ar = nombreRepetido(raiz->archivo,nombreEspecie);
        if(ar){
            return ar;
        }
    }
    if(raiz->sig != NULL){
        sig = nombreRepetido(raiz->sig,nombreEspecie);
        if(sig){
            return sig;
        }
    }
	if(raiz->notiene != NULL){
        no = nombreRepetido(raiz->notiene,nombreEspecie);
    }
    return no;
}

struct nodo *arbolizar(char* contenido){
    char *nombre = NULL;
    int longitudNombre, i = 0, caracteristica = 2, j;
    bool ultimo = false;
    long longitud = strlen(contenido);
    struct nodo *actual = NULL;
    struct nodo *especie = NULL;
    struct nodo *chivo = NULL;
    struct nodo *pregunta1 = NULL, *pregunta2 = NULL;
    struct nodo *raiz = principal(contenido);
    i = raiz->indiceRetorno;
    actual = raiz;
    while(i < longitud) {
        if(contenido[i] == '"') {
            /* Aquí recibo el nombre */
            i++;
            longitudNombre = 0;
            while (contenido[i] != '"') {
                //reservar espacio para longitud + 1 (nuevo caracter + '\0')
                nombre = realloc(nombre, (longitudNombre + 2));
                if (!nombre) {
                    fprintf(stderr, "❗ Error al asignar memoria.\n");
                    return NULL;
                }
                nombre[longitudNombre] = contenido[i];// Agregar letra
                nombre[longitudNombre + 1] = '\0';// Terminar cadena
                longitudNombre++;
                i++;
            }
            /* Se crea el nodo para la especie, si aplica */
            if(contenido[i+2] == '['){
                int tamNombre = strlen(nombre) + 1;
                char *nombreEspecie = calloc(tamNombre, sizeof(char));
                if (!nombreEspecie) salirPorErrMem();
                mi_strcat(nombreEspecie, tamNombre, nombre);
                if(!nombreRepetido(raiz, nombreEspecie)) {
                    especie = crearNodo(nombreEspecie);
                }
                else {
                    repetido(nombreEspecie);
                    free(nombreEspecie);
                    while(contenido[i] != ']'){
                        // voy hasta el corchete que cierra la especie con nombre repetido
                        i++;
                    }
                }

            }
            i++;
        }
        /* Se crea el nodo para una pregunta, si aplica */
        else if(contenido[i] == 't' || contenido[i] == 'f'){
            int tamNombre = strlen(nombre) + 1;
            char *nombreDefinitivo = calloc(tamNombre, sizeof(char));
            if (!nombreDefinitivo) salirPorErrMem();
            mi_strcat(nombreDefinitivo, tamNombre, nombre);
            if(contenido[i] == 't') {
                caracteristica = 1;
                actual = ubicarEnArbol(actual,caracteristica,nombreDefinitivo,especie);
            }
            else if(contenido[i] == 'f') {
                caracteristica = 0;
                actual = ubicarEnArbol(actual,caracteristica,nombreDefinitivo,especie);
            }
            if(actual == NULL){
                //no se cumplio el orden de la especie
                while(contenido[i] != ']'){
                    i++;//voy hasta el corchete que cierra la especie desordenada
                }
                //libero la memoria de la especie y el nombreDefinitivo
                free(nombreDefinitivo);//no se va a usar el nombre definitivo
                free(especie->nombre);
                free(especie);//se descarta la especie
                actual = raiz;//se reestablece el nodo actual    
            }
            else {
                //si son iguales ya existe ese nodo
                if(strcmp(actual->nombre,nombreDefinitivo) != 0) {
                    //nodo al que pertenece mi especie
                    pregunta1 = crearNodo(nombreDefinitivo);
                    pregunta1->caracteristica = caracteristica;
                    //nodo al que no pertenece mi especie
                    pregunta2 = crearNodo(nombreDefinitivo);
                    if(caracteristica) {
                        pregunta2->caracteristica = 0;
                        actual->sitiene = pregunta1;
                        actual->notiene = pregunta2;
                    }
                    else {
                        pregunta2->caracteristica = 1;
                        actual->notiene = pregunta1;
                        actual->sitiene = pregunta2;
                    }
                    pregunta1->padre = actual;
                    pregunta2->padre = actual;
                    actual = pregunta1;
                }
                else {
                    //como ya existe el nodo tengo que liberar la memoria de nombreDefinitivo
                    free(nombreDefinitivo);
                }
            }
        }
        /* Se establece que el nodo actual contiene la especie */
        else if(contenido[i] == ']') {
            j=i+1;//reviso si es el ultimo corchete
            while(j < longitud && contenido[j] != ']' && contenido[j] != '"') 
                j++;

            if(j >= longitud) ultimo = true;

            // en los casos que no son el ultimo
            if(!ultimo){
                if(actual->archivo == NULL){
                    actual->archivo = especie;
                }
                // caso donde mas de un archivo va en la misma carpeta
                else {
                    chivo = actual->archivo;
                    while(chivo->sig != NULL){chivo = chivo->sig;}
                    chivo->sig = especie;
                }
                especie->padre = actual;
            }
            actual = raiz;
        }
        i++;
    }
    // Se libera nombre porque los nombreDefinitivo son copias con su memoria aparte
    free(nombre);
    return raiz;
}

void liberarMemoriaArbol(struct nodo *nodo) {
    if (nodo == NULL) return;

    liberarMemoriaArbol(nodo->sitiene);
    liberarMemoriaArbol(nodo->archivo);
    liberarMemoriaArbol(nodo->sig);
    liberarMemoriaArbol(nodo->notiene);

    // El mismo nombre se comparte entre dos nodos de pregunta (true y false)
    // La idea es liberar la memoria del nombre solo en el segundo nodo.
    if (nodo->caracteristica != 1) 
        free(nodo->nombre);
    free(nodo);
}
