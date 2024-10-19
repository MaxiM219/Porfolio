#include "pa2m.h"
#include "src/abb.h"
#include <stdio.h>

int comparar_numeros(void *num1, void *num2)
{
	return (int)((*(int *)num1) - (*(int *)num2));
}

bool mostrar_elemento(void *elemento, void *extra)
{
	extra = extra; // para que no se queje el compilador, gracias -Werror -Wall
	if (elemento)
		printf("%i ", *(int *)elemento);
	return true;
}

bool mostrar_hasta_5(void *elemento, void *extra)
{
	extra = extra; // para que no se queje el compilador, gracias -Werror -Wall
	if (elemento) {
		printf("%i ", *(int *)elemento);
		if (*(int *)elemento == 5)
			return false;
	}
	return true;
}

void iniciar_abb_vacia()
{
	printf("\nIniciar el ABB vacío\n");
	abb_t *arbol = abb_crear(comparar_numeros);

	pa2m_afirmar(abb_tamanio(arbol) == 0, "creo el arbol vacio.");
	pa2m_afirmar(abb_vacio(arbol) == true, "El árbol está vacía.");
	abb_destruir(arbol);
}

void iniciar_abb_un_elemento()
{
	printf("\nIniciar el ABB e insertar un elemento\n");
	abb_t *arbol = abb_crear(comparar_numeros);
	int num1 = 1;

	pa2m_afirmar(abb_insertar(arbol, &num1) == arbol,
		     "Inserto un elemento.");
	pa2m_afirmar(abb_tamanio(arbol) == 1, "El árbol tiene la raiz.");
	abb_destruir(arbol);
}

void insertar_elemento_en_abb()
{
	printf("\nInsertar elementos\n");
	abb_t *arbol = abb_crear(comparar_numeros);
	int num1 = 5, num2 = 2, num3 = 8;

	pa2m_afirmar(abb_insertar(arbol, &num1) == arbol, "Inserto el 5.");
	pa2m_afirmar(abb_insertar(arbol, &num2) == arbol, "Inserto el 2.");
	pa2m_afirmar(abb_insertar(arbol, &num3) == arbol, "Inserto el 8.");
	pa2m_afirmar(abb_tamanio(arbol) == 3, "El árbol tiene 3 elementos.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, mostrar_elemento,
					   NULL) == 3,
		     "Tiene 3.");
	abb_destruir(arbol);
}

void insertar_elemento_repetido_en_abb()
{
	printf("\nInsertar elemento repetido\n");
	abb_t *arbol = abb_crear(comparar_numeros);
	int num1 = 5, num2 = 2, num3 = 8;

	pa2m_afirmar(abb_insertar(arbol, &num1) == arbol, "Inserto el 5.");
	pa2m_afirmar(abb_insertar(arbol, &num2) == arbol, "Inserto el 2.");
	pa2m_afirmar(abb_insertar(arbol, &num3) == arbol, "Inserto el 8.");
	pa2m_afirmar(abb_insertar(arbol, &num1) == arbol, "Inserto el 5.");
	pa2m_afirmar(abb_tamanio(arbol) == 4, "El árbol tiene 3 elementos.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, mostrar_elemento,
					   NULL) == 4,
		     "Tiene 4 en INORDEN.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, mostrar_elemento,
					   NULL) == 4,
		     "Tiene 4 en PREORDEN.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, mostrar_elemento,
					   NULL) == 4,
		     "Tiene 4 en POSTORDEN.");
	abb_destruir(arbol);
}

//------------Buscar-----------

void buscar_elemento_en_abb()
{
	printf("\nBuscar elemento en el ABB\n");
	abb_t *arbol = abb_crear(comparar_numeros);
	int num1 = 5, num2 = 2, num3 = 8;
	int num4 = 1, num5 = 15, num6 = 4;
	int num7 = 6, num8 = 9, num9 = 20;
	int num10 = 300;

	pa2m_afirmar(abb_insertar(arbol, &num1) == arbol, "Inserto el 5.");
	pa2m_afirmar(abb_insertar(arbol, &num2) == arbol, "Inserto el 2.");
	pa2m_afirmar(abb_insertar(arbol, &num3) == arbol, "Inserto el 8.");
	pa2m_afirmar(abb_insertar(arbol, &num4) == arbol, "Inserto el 1.");
	pa2m_afirmar(abb_insertar(arbol, &num5) == arbol, "Inserto el 15.");
	pa2m_afirmar(abb_insertar(arbol, &num6) == arbol, "Inserto el 4.");
	pa2m_afirmar(abb_insertar(arbol, &num7) == arbol, "Inserto el 6.");
	pa2m_afirmar(abb_insertar(arbol, &num8) == arbol, "Inserto el 9.");
	pa2m_afirmar(abb_insertar(arbol, &num9) == arbol, "Inserto el 20.");
	pa2m_afirmar(abb_tamanio(arbol) == 9, "El árbol tiene 9 elementos.");
	pa2m_afirmar(*(int *)abb_buscar(arbol, &num7) == 6, "Encontro al 6");
	pa2m_afirmar((void *)abb_buscar(arbol, &num10) == NULL,
		     "No encontro al 300");
	abb_destruir(arbol);
}

void recorridos_en_abb()
{
	printf("\nRecorridos pre, in, post orden\n");
	abb_t *arbol = abb_crear(comparar_numeros);
	int num1 = 5, num2 = 2, num3 = 8;
	//int num4 = 1;

	pa2m_afirmar(abb_insertar(arbol, &num3) == arbol, "Inserto el 8.");
	pa2m_afirmar(abb_insertar(arbol, &num2) == arbol, "Inserto el 2.");
	pa2m_afirmar(abb_insertar(arbol, &num1) == arbol, "Inserto el 5.");
	//pa2m_afirmar(abb_insertar(arbol, &num4) == arbol, "Inserto el 10.");
	pa2m_afirmar(abb_tamanio(arbol) == 3, "El árbol tiene 3 elementos.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, mostrar_hasta_5,
					   NULL) == 2,
		     "Tiene 2 en INORDEN: 2 5.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, mostrar_hasta_5,
					   NULL) == 3,
		     "Tiene 3 en PREORDEN: 8 2 5.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, mostrar_hasta_5,
					   NULL) == 1,
		     "Tiene 1 en POSTORDEN hasta 5: 5.");
	printf("\n Tiene recorrido %li",
	       abb_con_cada_elemento(arbol, POSTORDEN, mostrar_hasta_5, NULL));
	abb_destruir(arbol);
}

void recorridos_externos_en_abb()
{
	printf("\nRecorridos pre, in, post orden externos\n");
	abb_t *arbol = abb_crear(comparar_numeros);
	int num1 = 5, num2 = 2, num3 = 8;

	int *elementos[10];

	pa2m_afirmar(abb_insertar(arbol, &num1) == arbol, "Inserto el 5.");
	pa2m_afirmar(abb_insertar(arbol, &num2) == arbol, "Inserto el 2.");
	pa2m_afirmar(abb_insertar(arbol, &num3) == arbol, "Inserto el 8.");
	size_t cantidad = abb_recorrer(arbol, INORDEN, (void **)elementos, 10);
	pa2m_afirmar(abb_tamanio(arbol) == 3, "El árbol tiene 3 elementos.");

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *elementos[i]);
	printf("\n");
	// pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, mostrar_hasta_5, NULL)
	// == 1, "Tiene 1 en INORDEN."); pa2m_afirmar(abb_con_cada_elemento(arbol,
	// PREORDEN, mostrar_hasta_5, NULL) == 0, "Tiene 0 en PREORDEN.");
	// pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, mostrar_hasta_5, NULL)
	// == 2, "Tiene 4 en POSTORDEN.");
	// printf("\n Tiene recorrido %li", abb_con_cada_elemento(arbol, POSTORDEN,
	// mostrar_hasta_5, NULL));
	abb_destruir(arbol);
}

void eliminar_elemento_hoja_en_abb()
{
	printf("\nEliminar el nodo hoja\n");
	abb_t *arbol = abb_crear(comparar_numeros);
	int num1 = 5, num2 = 2, num3 = 8;

	pa2m_afirmar(abb_insertar(arbol, &num1) == arbol, "Inserto el 5.");
	pa2m_afirmar(abb_insertar(arbol, &num2) == arbol, "Inserto el 2.");
	pa2m_afirmar(abb_insertar(arbol, &num3) == arbol, "Inserto el 8.");
	pa2m_afirmar(abb_tamanio(arbol) == 3, "El árbol tiene 3 elementos.");
	pa2m_afirmar(*(int *)abb_buscar(arbol, &num3) == 8, "Busco el 8");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, mostrar_elemento,
					   NULL) == 3,
		     "Tiene 3 en INORDEN.");
	pa2m_afirmar(*(int *)abb_quitar(arbol, &num3) == 8, "Borro el 8");
	pa2m_afirmar((void *)abb_buscar(arbol, &num3) == NULL,
		     "Ya no está el 8");
	pa2m_afirmar((void *)abb_quitar(arbol, &num3) == NULL,
		     "Borro devuelta el 8 y no está");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, mostrar_elemento,
					   NULL) == 2,
		     "Tiene 2 en INORDEN.");
	abb_destruir(arbol);
}

void eliminar_elemento_con_un_hijo_en_abb()
{
	printf("\nEliminar un nodo con un hijo\n");
	abb_t *arbol = abb_crear(comparar_numeros);
	int num1 = 5, num2 = 2, num3 = 8;
	int num4 = 1, num5 = 15, num6 = 4;

	pa2m_afirmar(abb_insertar(arbol, &num1) == arbol, "Inserto el 5.");
	pa2m_afirmar(abb_insertar(arbol, &num2) == arbol, "Inserto el 2.");
	pa2m_afirmar(abb_insertar(arbol, &num3) == arbol, "Inserto el 8.");
	pa2m_afirmar(abb_insertar(arbol, &num4) == arbol, "Inserto el 1.");
	pa2m_afirmar(abb_insertar(arbol, &num5) == arbol, "Inserto el 15.");
	pa2m_afirmar(abb_insertar(arbol, &num6) == arbol, "Inserto el 4.");

	pa2m_afirmar(abb_tamanio(arbol) == 6, "El árbol tiene 6 elementos.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, mostrar_elemento,
					   NULL) == 6,
		     "Tiene 6 en INORDEN.");
	pa2m_afirmar(*(int *)abb_quitar(arbol, &num3) == 8,
		     "Borro el 8 y me tiene que quedar como padre el 15");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, mostrar_elemento,
					   NULL) == 5,
		     "Tiene 5 en INORDEN ya que se borro el 8.");
	printf("\n Tiene recorrido %li",
	       abb_con_cada_elemento(arbol, INORDEN, mostrar_hasta_5, NULL));
	abb_destruir(arbol);
}

void eliminar_elemento_con_dos_hijo_en_abb()
{
	printf("\nEliminar un nodo con dos hijo\n");
	abb_t *arbol = abb_crear(comparar_numeros);
	int num1 = 5, num2 = 2, num3 = 8;
	int num4 = 1, num5 = 15, num6 = 4;

	pa2m_afirmar(abb_insertar(arbol, &num1) == arbol, "Inserto el 5.");
	pa2m_afirmar(abb_insertar(arbol, &num2) == arbol, "Inserto el 2.");
	pa2m_afirmar(abb_insertar(arbol, &num3) == arbol, "Inserto el 8.");
	pa2m_afirmar(abb_insertar(arbol, &num4) == arbol, "Inserto el 1.");
	pa2m_afirmar(abb_insertar(arbol, &num5) == arbol, "Inserto el 15.");
	pa2m_afirmar(abb_insertar(arbol, &num6) == arbol, "Inserto el 4.");
	pa2m_afirmar(abb_tamanio(arbol) == 6, "El árbol tiene 6 elementos.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, mostrar_elemento,
					   NULL) == 6,
		     "Tiene 6 elementos en INORDEN.");
	pa2m_afirmar(*(int *)abb_quitar(arbol, &num1) == 5,
		     "Borro el 5 y me tiene que quedar como padre el 4");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, mostrar_elemento,
					   NULL) == 5,
		     "Tiene 5 elementos en INORDEN ya que se borro el 5.");
	pa2m_afirmar((void *)abb_buscar(arbol, &num1) == NULL,
		     "Ya no está el 5");
	pa2m_afirmar((void *)abb_quitar(arbol, &num1) == NULL,
		     "Devuelve NULL ya que no está el 5.");
	abb_destruir(arbol);
}

void eliminar_elemento_que_no_esta()
{
	printf("\nTrata de eliminar un nodo que no está\n");
	abb_t *arbol = abb_crear(comparar_numeros);
	int num1 = 5, num2 = 2, num3 = 8;
	int num4 = 15;

	pa2m_afirmar(abb_insertar(arbol, &num1) == arbol, "Inserto el 5.");
	pa2m_afirmar(abb_insertar(arbol, &num2) == arbol, "Inserto el 2.");
	pa2m_afirmar(abb_insertar(arbol, &num3) == arbol, "Inserto el 8.");
	pa2m_afirmar(abb_tamanio(arbol) == 3, "El árbol tiene 3 elementos.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, mostrar_elemento,
					   NULL) == 3,
		     "Tiene 6 elementos en INORDEN.");
	pa2m_afirmar((void *)abb_quitar(arbol, &num4) == NULL,
		     "Devuelve NULL ya que no está el 15 en el ABB.");
	abb_destruir(arbol);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	pa2m_nuevo_grupo("\nIniciar ABB");
	iniciar_abb_vacia();
	iniciar_abb_un_elemento();

	pa2m_nuevo_grupo("\nInsertar ABB");
	insertar_elemento_en_abb();
	insertar_elemento_repetido_en_abb();

	pa2m_nuevo_grupo("\nBuscar ABB");
	buscar_elemento_en_abb();

	pa2m_nuevo_grupo("\nRecorridos c/elemento ABB");
	recorridos_en_abb();
	recorridos_externos_en_abb();

	pa2m_nuevo_grupo("\nEliminar ABB");
	eliminar_elemento_hoja_en_abb();
	eliminar_elemento_con_un_hijo_en_abb();
	eliminar_elemento_con_dos_hijo_en_abb();
	eliminar_elemento_que_no_esta();

	return pa2m_mostrar_reporte();
}
