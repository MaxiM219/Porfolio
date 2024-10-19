#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>

#define VACIO 0

//---------Funciones---------//

typedef struct {
	void **array;
	size_t tamano_array;
	size_t cantidad;
} elementos_t;

//Estructura para quitar un elemento.
//Un booleano para ver si se borro el elemento. En caso de false, la función de quitar devuelve NULL;
//El elemento_borrado inicialmente es NULL, si encuentra el elemento lo guarda y lo devuelve.
typedef struct {
	bool borrado;
	void **elemento_borrado;
} quitado_t;

abb_t *abb_crear(abb_comparador comparador)
{
	abb_t *arbol = calloc(1, sizeof(abb_t));
	if (arbol == NULL || comparador == NULL) {
		free(arbol);
		return NULL;
	}
	arbol->comparador = comparador;
	return arbol;
}

/*Crea un nodo a partir de un elemento que es recibido por parámetro.
Devuelve el nodo en caso de exito o NULL en caso de error. */
nodo_abb_t *crear_nodo(void *elemento)
{
	nodo_abb_t *nodo = calloc(1, sizeof(nodo_abb_t));
	if (nodo == NULL) {
		free(nodo);
		return NULL;
	}
	nodo->elemento = elemento;
	return nodo;
}

/*Inserta el nodo en el árbol de forma recursiva a partir de 
un comparador, el nodo actual y el elemento a insertar.*/
nodo_abb_t *abb_insertar_recursivo(abb_comparador comparador,
				   nodo_abb_t *actual, void *elemento)
{
	if (actual == NULL) {
		actual = crear_nodo(elemento);
		return actual;
	}
	if (comparador(elemento, actual->elemento) < 0 ||
	    comparador(elemento, actual->elemento) == 0) {
		actual->izquierda = abb_insertar_recursivo(
			comparador, actual->izquierda, elemento);
	} else {
		actual->derecha = abb_insertar_recursivo(
			comparador, actual->derecha, elemento);
	}
	return actual;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL) {
		return NULL;
	}

	arbol->nodo_raiz = abb_insertar_recursivo(arbol->comparador,
						  arbol->nodo_raiz, elemento);
	arbol->tamanio++;
	return arbol;
}

//---------Quitar---------//

//Recibe el nodo del hijo izquierdo.
//Devuelve el nodo derecho que más se acerca al nodo que voy a reemplazar.
nodo_abb_t *buscar_reemplazo(nodo_abb_t *actual)
{
	if (actual->derecha == NULL) {
		return actual;
	}
	actual = actual->derecha;
	return buscar_reemplazo(actual);
}

//Recibe el nodo del hijo izquierdo.
//Borra el nodo que usamos para reemplazar al elemento y devolvemos si tiene su hijo como el nodo padre.
nodo_abb_t *borrar_nodo(nodo_abb_t *actual)
{
	if (actual == NULL) {
		return NULL;
	} else if (actual->derecha == NULL) {
		nodo_abb_t *hijo_izq = actual->izquierda;
		free(actual);
		return hijo_izq;
	}
	actual->derecha = borrar_nodo(actual->derecha);
	return actual;
}

//Recibe un comparador, el nodo actual, un booleano si se borró el nodo,
//elemento_actual que guarda el elemento que voy a devolver y el elemento a borrar.
void *abb_quitar_recursivo(abb_comparador comparador, nodo_abb_t *actual,
			   quitado_t *quitado, void *elemento)
{
	if (actual == NULL) {
		return NULL;
	}

	if (comparador(elemento, actual->elemento) == 0) {
		quitado->borrado = true;
		quitado->elemento_borrado = actual->elemento;
		if (actual->izquierda == NULL && actual->derecha == NULL) {
			free(actual);
			return NULL;
		} else if (actual->derecha == NULL) {
			nodo_abb_t *hijo_izq = actual->izquierda;
			free(actual);
			return hijo_izq;
		} else if (actual->izquierda == NULL) {
			nodo_abb_t *hijo_der = actual->derecha;
			free(actual);
			return hijo_der;
		}

		nodo_abb_t *reemplazo = buscar_reemplazo(actual->izquierda);
		actual->elemento = reemplazo->elemento;
		actual->izquierda = borrar_nodo(actual->izquierda);

	} else if (comparador(elemento, actual->elemento) < 0) {
		actual->izquierda = abb_quitar_recursivo(
			comparador, actual->izquierda, quitado, elemento);
	} else {
		actual->derecha = abb_quitar_recursivo(
			comparador, actual->derecha, quitado, elemento);
	}
	return actual;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL) {
		return NULL;
	}
	quitado_t elemento_quitado;
	elemento_quitado.borrado = false;
	elemento_quitado.elemento_borrado = NULL;
	arbol->nodo_raiz = abb_quitar_recursivo(arbol->comparador,
						arbol->nodo_raiz,
						&elemento_quitado, elemento);
	if (elemento_quitado.borrado == false) {
		return NULL;
	}
	arbol->tamanio--;
	return elemento_quitado.elemento_borrado;
}

//---------Buscar---------//

//Recibo un comparador, el nodo actual, y el elemento que estoy buscando.
//Devuelvo el nodo encontrado o NULL si no pudo.
nodo_abb_t *abb_buscar_recursivo(abb_comparador comparador, nodo_abb_t *actual,
				 void *elemento)
{
	if (actual == NULL || comparador(elemento, actual->elemento) == 0) {
		return actual;
	}
	if (comparador(elemento, actual->elemento) < 0) {
		return abb_buscar_recursivo(comparador, actual->izquierda,
					    elemento);
	} else {
		return abb_buscar_recursivo(comparador, actual->derecha,
					    elemento);
	}
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL) {
		return NULL;
	}

	nodo_abb_t *actual = abb_buscar_recursivo(arbol->comparador,
						  arbol->nodo_raiz, elemento);
	if (actual == NULL) {
		return NULL;
	}
	return actual->elemento;
}

bool abb_vacio(abb_t *arbol)
{
	if (arbol == NULL) {
		return true;
	}
	return arbol->nodo_raiz == NULL;
}

size_t abb_tamanio(abb_t *arbol)
{
	if (arbol == NULL) {
		return VACIO;
	}
	return arbol->tamanio;
}

//---------Destruir---------//

//Recibo el nodo raíz y a partir de ahí empiezo a recorrer el árbol.
//Destruyo los nodos del árbol.
void abb_destruir_recursivo(nodo_abb_t *actual)
{
	if (actual == NULL) {
		return;
	}
	abb_destruir_recursivo(actual->izquierda);
	abb_destruir_recursivo(actual->derecha);
	free(actual);
}

void abb_destruir(abb_t *arbol)
{
	if (arbol == NULL) {
		return;
	}

	abb_destruir_recursivo(arbol->nodo_raiz);
	free(arbol);
}
//Recibo el nodo raíz y a partir de ahí empiezo a recorrer el árbol.
//Destruyo los elementos de los nodos y luego al nodo del árbol.
void abb_destruir_todo_recursivo(nodo_abb_t *actual, void (*destructor)(void *))
{
	if (actual == NULL) {
		return;
	}
	abb_destruir_todo_recursivo(actual->izquierda, destructor);
	abb_destruir_todo_recursivo(actual->derecha, destructor);
	if (actual->elemento != NULL) {
		destructor(actual->elemento);
	}
	free(actual);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (arbol == NULL) {
		return;
	}
	if (destructor != NULL) {
		abb_destruir_todo_recursivo(arbol->nodo_raiz, destructor);
	} else {
		abb_destruir_recursivo(arbol->nodo_raiz);
	}
	free(arbol);
}

//---------Iteradores---------//

//---------Recorridos Internos---------//

bool insertar_elementos(void *elemento, void *extra)
{
	elementos_t *elementos = extra;

	if (elementos->cantidad < elementos->tamano_array) {
		elementos->array[elementos->cantidad] = elemento;
		elementos->cantidad++;
		return true;
	}
	return false;
}

//Recorro el árbol preorden a partir de la raíz, la función dada por el usuario, un auxiliar,
//recibe la cantidad de veces que va a ser invocada la función
//y un booleano por si la función da false y termina de iterar.
void preorden(nodo_abb_t *actual, bool (*funcion)(void *, void *), void *aux,
	      size_t *cantidad, bool *seguir)
{
	if (actual == NULL || *seguir == false) {
		return;
	}
	if (*seguir) {
		*cantidad += 1;
		*seguir = funcion(actual->elemento, aux);
	} else {
		return;
	}
	preorden(actual->izquierda, funcion, aux, cantidad, seguir);
	preorden(actual->derecha, funcion, aux, cantidad, seguir);
}

//Recorro el árbol inorden a partir de la raíz, la función dada por el usuario, un auxiliar,
//recibe la cantidad de veces que va a ser invocada la función
//y un booleano por si la función da false y termina de iterar.
void inorden(nodo_abb_t *actual, bool (*funcion)(void *, void *), void *aux,
	     size_t *cantidad, bool *seguir)
{
	if (actual == NULL || !seguir) {
		return;
	}
	inorden(actual->izquierda, funcion, aux, cantidad, seguir);
	if (*seguir) {
		*cantidad += 1;
		*seguir = funcion(actual->elemento, aux);
	} else {
		return;
	}
	inorden(actual->derecha, funcion, aux, cantidad, seguir);
}

//Recorro el árbol postorden a partir de la raíz, la función dada por el usuario, un auxiliar,
//recibe la cantidad de veces que va a ser invocada la función
//y un booleano por si la función da false y termina de iterar.
void postorden(nodo_abb_t *actual, bool (*funcion)(void *, void *), void *aux,
	       size_t *cantidad, bool *seguir)
{
	if (actual == NULL || !seguir) {
		return;
	}
	postorden(actual->izquierda, funcion, aux, cantidad, seguir);
	postorden(actual->derecha, funcion, aux, cantidad, seguir);
	if (*seguir) {
		*cantidad += 1;
		*seguir = funcion(actual->elemento, aux);
	}
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (arbol == NULL || funcion == NULL) {
		return VACIO;
	}
	size_t cantidad = 0;
	bool seguir = true;
	if (recorrido == INORDEN) {
		inorden(arbol->nodo_raiz, funcion, aux, &cantidad, &seguir);
	} else if (recorrido == PREORDEN) {
		preorden(arbol->nodo_raiz, funcion, aux, &cantidad, &seguir);
	} else if (recorrido == POSTORDEN) {
		postorden(arbol->nodo_raiz, funcion, aux, &cantidad, &seguir);
	}

	return cantidad;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (arbol == NULL) {
		return VACIO;
	}
	//size_t cantidad = 0;
	elementos_t elementos_guardados;
	elementos_guardados.array = array;
	elementos_guardados.cantidad = 0;
	elementos_guardados.tamano_array = tamanio_array;

	return abb_con_cada_elemento(arbol, recorrido, insertar_elementos,
				     &elementos_guardados);
}
