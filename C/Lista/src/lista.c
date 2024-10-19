#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	nodo_t *nodo_final;
	size_t tamanio;
};

struct lista_iterador {
	nodo_t *actual;
	lista_t *lista;
};

nodo_t *crear_nodo(void *dato)
{
	nodo_t *nodo = calloc(1, sizeof(nodo_t));
	nodo->elemento = dato;
	nodo->siguiente = NULL;
	return nodo;
}

lista_t *lista_crear()
{
	return calloc(1, sizeof(lista_t));
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	nodo_t *nuevo_nodo = crear_nodo(elemento);
	if (lista == NULL || nuevo_nodo == NULL) {
		free(nuevo_nodo);
		return NULL;
	}

	if (lista_vacia(lista)) {
		lista->nodo_inicio = nuevo_nodo;
	} else {
		lista->nodo_final->siguiente = nuevo_nodo;
	}
	lista->nodo_final = nuevo_nodo;
	lista->tamanio++;
	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	nodo_t *nuevo_nodo = crear_nodo(elemento);

	if (lista == NULL || nuevo_nodo == NULL) {
		free(nuevo_nodo);
		return NULL;
	}

	size_t posicion_actual = 0;
	nodo_t *actual = lista->nodo_inicio;
	nodo_t *anterior = NULL;

	if (posicion == 0 && lista_tamanio(lista) >= 1) {
		// Inserta en la posicion inicial y tiene 1 elemento.
		nuevo_nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nuevo_nodo;
	} else if ((lista_tamanio(lista) == 0 &&
		    posicion >= lista_tamanio(lista)) ||
		   (posicion == 0 && lista_tamanio(lista) == 0) ||
		   (lista_tamanio(lista) > 0 &&
		    posicion > lista_tamanio(lista) - 1)) {
		// Usa la lista insertar. Agrega al final o agrega si la posicion es 0 y el
		// tamaño de la lista sea 0;
		free(nuevo_nodo);
		return lista_insertar(lista, elemento);
	} else {
		// Caso posición del medio.
		while (posicion_actual < posicion) {
			anterior = actual;
			actual = actual->siguiente;
			posicion_actual++;
		}
		anterior->siguiente = nuevo_nodo;
		nuevo_nodo->siguiente = actual;
	}

	lista->tamanio++;
	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if (lista == NULL || lista_vacia(lista)) {
		return NULL;
	}
	nodo_t *anterior = NULL;
	nodo_t *actual = lista->nodo_inicio;

	while (actual != lista->nodo_final) {
		anterior = actual;
		actual = actual->siguiente;
	}

	void *elemento = actual->elemento;
	lista->nodo_final = anterior;
	if (lista_tamanio(lista) == 1) {
		lista->nodo_inicio = anterior;
	} else {
		lista->nodo_final->siguiente = NULL;
	}

	free(actual);
	lista->tamanio--;
	return elemento;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (lista == NULL || lista_vacia(lista)) {
		return NULL;
	}
	size_t posicion_actual = 0;
	nodo_t *actual = lista->nodo_inicio;
	nodo_t *anterior = NULL;
	void *elemento;
	if ((posicion == 0 && lista_tamanio(lista) == 1) ||
	    (posicion > lista_tamanio(lista) - 1)) {
		// Usa la lista quitar. Quita el primer elemento de la posicion 0 y si es el
		// unico que hay o quita el ultimo elemento si la posicion dada es mayor o
		// si es igual a la posicion final.
		return lista_quitar(lista);
	} else if (posicion == 0 && lista_tamanio(lista) > 1) {
		// Caso quitar la primera y hay más nodos.
		elemento = lista->nodo_inicio->elemento;
		lista->nodo_inicio = lista->nodo_inicio->siguiente;

		free(actual);
	} else {
		// Caso quito del medio.

		while (posicion_actual < posicion) {
			anterior = actual;
			actual = actual->siguiente;
			posicion_actual++;
		}
		elemento = actual->elemento;
		anterior->siguiente = actual->siguiente;
		free(actual);
	}
	lista->tamanio--;
	return elemento;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (lista == NULL || lista_vacia(lista) ||
	    posicion > lista_tamanio(lista) - 1) {
		return NULL;
	}

	size_t posicion_actual = 0;
	nodo_t *actual = lista->nodo_inicio;

	while (actual != NULL) {
		if (posicion == posicion_actual) {
			return actual->elemento;
		}
		actual = actual->siguiente;
		posicion_actual++;
	}

	return actual->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (lista == NULL || lista_vacia(lista) || comparador == NULL) {
		return NULL;
	}

	nodo_t *actual = lista->nodo_inicio;
	while (actual) {
		if (comparador(actual->elemento, contexto) == 0) {
			return actual->elemento;
		}
		actual = actual->siguiente;
	}
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if (lista == NULL || lista_vacia(lista)) {
		return NULL;
	}
	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if (lista == NULL || lista_vacia(lista)) {
		return NULL;
	}
	return lista->nodo_final->elemento;
}

bool lista_vacia(lista_t *lista)
{
	if (lista == NULL) {
		return true;
	}
	return lista->tamanio == 0;
}

size_t lista_tamanio(lista_t *lista)
{
	if (lista == NULL) {
		return 0;
	}
	return lista->tamanio;
}

void lista_destruir(lista_t *lista)
{
	if (lista == NULL) {
		return;
	}
	nodo_t *aux;
	nodo_t *actual = lista->nodo_inicio;

	while (actual != NULL) {
		aux = actual;
		actual = actual->siguiente;
		free(aux);
	}
	free(lista);
	return;
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if ((lista == NULL && funcion == NULL) ||
	    (lista == NULL && funcion != NULL)) {
		return;
	} else if (lista != NULL && lista == NULL) {
		lista_destruir(lista);
		return;
	}

	nodo_t *aux;
	nodo_t *actual = lista->nodo_inicio;
	while (actual != NULL) {
		aux = actual;
		if (aux->elemento != NULL && funcion != NULL) {
			funcion(aux->elemento);
		}
		actual = actual->siguiente;
		free(aux);
	}
	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (lista == NULL) {
		return NULL;
	}
	lista_iterador_t *iterador = calloc(1, sizeof(lista_t));
	iterador->lista = lista;
	iterador->actual = lista->nodo_inicio;
	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if (iterador == NULL) {
		return false;
	}
	return iterador->actual != NULL;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (iterador == NULL) {
		return false;
	} else if (lista_iterador_tiene_siguiente(iterador)) {
		iterador->actual = iterador->actual->siguiente;
		return lista_iterador_tiene_siguiente(iterador);
	}
	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if (iterador == NULL) {
		return false;
	}

	if (lista_iterador_tiene_siguiente(iterador)) {
		return iterador->actual->elemento;
	}
	return NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if (iterador == NULL) {
		return;
	}
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (lista_vacia(lista) || funcion == NULL) {
		return 0;
	}

	size_t contador = 0;
	nodo_t *actual = lista->nodo_inicio;
	while (actual != NULL) {
		contador++;
		if (!funcion(actual->elemento, contexto)) {
			return contador;
		}
		actual = actual->siguiente;
	}

	return contador;
}