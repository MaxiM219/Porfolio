#include "pa2m.h"
#include "src/hash.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool ver_elementos(const char *clave, void *valor, void *aux)
{
	char *elemento = valor;
	printf("Elemento: %s\n", elemento);
	return true;
}

bool ver_elementos_numeros(const char *clave, void *valor, void *aux)
{
	if (!clave) {
		return false;
	}
	if (valor == NULL) {
		printf("Clave: %s, Valor: NULL\n", clave);
		return true;
	}

	int *elemento = valor;

	aux = aux;

	printf("Clave: %s, Valor: %i\n", clave, *elemento);
	return true;
}

void iniciar_dicc_vacio()
{
	printf("\nIniciar el Diccionario vacío\n");
	hash_t *diccionario = hash_crear(3);

	pa2m_afirmar(hash_cantidad(diccionario) == 0,
		     "Creo el diccionario vacio.");
	hash_destruir(diccionario);
}

void iniciar_dicc_con_elementos()
{
	printf("\nEl Diccionario no fue creado\n");
	hash_t *diccionario = hash_crear(3);

	pa2m_afirmar(hash_cantidad(diccionario) == 0,
		     "Creo el diccionario vacio.");
	void *anterior = NULL;
	hash_insertar(diccionario, "hola", "hola", &anterior);
	hash_insertar(diccionario, "como", "como", &anterior);
	hash_insertar(diccionario, "estas", "estas?", &anterior);

	hash_con_cada_clave(diccionario, ver_elementos, NULL);

	hash_destruir(diccionario);
}

void insertar_elementos_con_misma_clave()
{
	printf("\nInsertar elementos en el Diccionario con la misma clave\n");
	hash_t *diccionario = hash_crear(3);

	void *anterior1 = NULL;
	void *anterior2 = NULL;
	void *anterior3 = NULL;
	void *anterior4 = NULL;
	void *anterior5 = NULL;

	int num1 = 1, num2 = 2, num3 = 3, num4 = 4, num5 = 5;

	int reemplazo1 = 10, reemplazo2 = 40;

	printf("\nPaso 1\n");
	pa2m_afirmar(hash_insertar(diccionario, "1", &num1, &anterior1) ==
			     diccionario,
		     "Inserto la clave 1 y valor 1");
	pa2m_afirmar(hash_insertar(diccionario, "2", &num2, &anterior2) ==
			     diccionario,
		     "Inserto la clave 2 y valor 2");
	pa2m_afirmar(hash_insertar(diccionario, "3", &num3, &anterior3) ==
			     diccionario,
		     "Inserto la clave 3 y valor 3");
	pa2m_afirmar(hash_insertar(diccionario, "4", &num4, &anterior4) ==
			     diccionario,
		     "Inserto la clave 4 y valor 4");
	pa2m_afirmar(hash_insertar(diccionario, "5", &num5, &anterior5) ==
			     diccionario,
		     "Inserto la clave 5 y valor 5");

	pa2m_afirmar(hash_cantidad(diccionario) == 5,
		     "El diccionario tiene 5 items.");

	printf("Paso 2\n");

	pa2m_afirmar(hash_contiene(diccionario, "1") == true,
		     "Contiene la Clave 1");
	pa2m_afirmar(hash_contiene(diccionario, "2") == true,
		     "Contiene la Clave 2");
	pa2m_afirmar(hash_contiene(diccionario, "3") == true,
		     "Contiene la Clave 3");
	pa2m_afirmar(hash_contiene(diccionario, "4") == true,
		     "Contiene la Clave 4");
	pa2m_afirmar(hash_contiene(diccionario, "5") == true,
		     "Contiene la Clave 5");

	printf("\nPaso 3\n");

	hash_con_cada_clave(diccionario, ver_elementos_numeros, NULL);

	printf("\nPaso 4 Reemplazar\n");

	pa2m_afirmar(hash_insertar(diccionario, "1", &reemplazo1, &anterior1) ==
			     diccionario,
		     "La clave es la misma y cambia de valor. de 1 a 10");
	pa2m_afirmar(hash_insertar(diccionario, "4", &reemplazo2, &anterior4) ==
			     diccionario,
		     "La clave es la misma y cambia de valor. de 4 a 40");

	printf("anterior de clave 1 %i\n", *(int *)anterior1);
	printf("anterior de clave 1 %i\n", *(int *)anterior1);
	printf("Actual de 4 %i\n", *(int *)hash_obtener(diccionario, "4"));

	hash_con_cada_clave(diccionario, ver_elementos_numeros, NULL);

	hash_destruir(diccionario);
}

void buscar_elemento_en_dicc()
{
	printf("\nBuscar un elemento en el diccionario\n");
	hash_t *diccionario = hash_crear(3);

	pa2m_afirmar(hash_cantidad(diccionario) == 0,
		     "Creo el diccionario vacio.");
	void *anterior = NULL;
	hash_insertar(diccionario, "hola", "hola", &anterior);
	hash_insertar(diccionario, "como", "como", &anterior);
	hash_insertar(diccionario, "estas", "estas?", &anterior);

	pa2m_afirmar(hash_cantidad(diccionario) == 3, "Tiene 3 items.");

	int resultado = strcmp(hash_obtener(diccionario, "como"), "como");
	pa2m_afirmar((resultado == 0), "El elemento está en el diccionario.");
	pa2m_afirmar(hash_obtener(diccionario, "adios") == NULL,
		     "El elemento no está en el diccionario.");

	hash_destruir(diccionario);
}

void usar_anterior_diccionario()
{
	printf("\nRecorro el diccionario\n");
	hash_t *diccionario = hash_crear(3);

	int num1 = 1, num2 = 2, num3 = 3, num4 = 4, num5 = 5;
	int num6 = 6, num7 = 7, num8 = 8;
	int num9 = 9;
	//int num10 = 10;
	//int num11 = 11;

	void *anterior1 = NULL;
	void *anterior2 = NULL;
	void *anterior3 = NULL;
	void *anterior4 = NULL;
	void *anterior5 = NULL;
	void *anterior6 = NULL;
	void *anterior7 = NULL;
	void *anterior8 = NULL;
	void *anterior9 = NULL;

	pa2m_afirmar(hash_insertar(diccionario, "1", &num1, &anterior1) ==
			     diccionario,
		     "Inserto la clave 1 y valor 1");
	pa2m_afirmar(hash_insertar(diccionario, "2", NULL, &anterior2) ==
			     diccionario,
		     "Inserto la clave 2 y valor 2");
	pa2m_afirmar(hash_insertar(diccionario, "3", &num3, &anterior3) ==
			     diccionario,
		     "Inserto la clave 3 y valor 3");
	pa2m_afirmar(hash_insertar(diccionario, "4", &num4, &anterior4) ==
			     diccionario,
		     "Inserto la clave 4 y valor 4");

	pa2m_afirmar(hash_cantidad(diccionario) == 4,
		     "El diccionario tiene  items.");

	hash_con_cada_clave(diccionario, ver_elementos_numeros, NULL);

	pa2m_afirmar(hash_insertar(diccionario, "1", &num9, &anterior1) ==
			     diccionario,
		     "Inserto la clave 1 y valor 9");

	pa2m_afirmar(hash_insertar(diccionario, "2", &num2, &anterior2) ==
			     diccionario,
		     "Inserto la clave 2 y valor 9");

	pa2m_afirmar(*(int *)anterior1 == 1, "El anterior es 1");
	pa2m_afirmar(anterior2 == NULL, "El anterior es NULL");
	//printf("anterior vale %i", *(int*)anterior1);

	pa2m_afirmar(hash_insertar(diccionario, "5", &num5, &anterior5) ==
			     diccionario,
		     "Inserto la clave 5 y valor 5");
	pa2m_afirmar(hash_insertar(diccionario, "6", &num6, &anterior6) ==
			     diccionario,
		     "Inserto la clave 6 y valor 6");
	pa2m_afirmar(hash_insertar(diccionario, "7", &num7, &anterior7) ==
			     diccionario,
		     "Inserto la clave 7 y valor 7");
	pa2m_afirmar(hash_insertar(diccionario, "8", &num8, &anterior8) ==
			     diccionario,
		     "Inserto la clave 8 y valor 8");

	pa2m_afirmar(hash_insertar(diccionario, "9", &num9, &anterior9) ==
			     diccionario,
		     "Inserto la clave 9 y valor 9");

	pa2m_afirmar(*(int *)anterior1 == 1, "El anterior de la clave 1 es 1");
	pa2m_afirmar(anterior2 == NULL, "El anterior de la clave 2 es NULL");

	pa2m_afirmar(anterior5 == NULL, "El anterior de la clave 5 es NULL");
	pa2m_afirmar(anterior6 == NULL, "El anterior de la clave 6 es NULL");
	pa2m_afirmar(anterior7 == NULL, "El anterior de la clave 7 es NULL");

	hash_destruir(diccionario);
}

void quitar_elemento()
{
	printf("\nQuitar un elemento del Diccionario\n");
	hash_t *diccionario = hash_crear(3);

	void *anterior = NULL;
	void *anterior1 = NULL;
	pa2m_afirmar(hash_insertar(diccionario, "hola", "hola", &anterior1) ==
			     diccionario,
		     "Inserta la clave hola y valor");

	pa2m_afirmar(hash_insertar(diccionario, "como", "como", &anterior) ==
			     diccionario,
		     "Inserta la clave como y valor");
	pa2m_afirmar(hash_insertar(diccionario, "estas", "estas?", &anterior) ==
			     diccionario,
		     "Inserta la clave estas y valor");

	pa2m_afirmar(hash_cantidad(diccionario) == 3, "Tiene 3 items.");

	int resultado = strcmp(hash_quitar(diccionario, "hola"), "hola");
	pa2m_afirmar(resultado == 0, "Quito 'hola' del diccionario.");
	pa2m_afirmar(hash_cantidad(diccionario) == 2, "Tiene 2 items.");

	pa2m_afirmar(hash_insertar(diccionario, "hola", "holas", &anterior1) ==
			     diccionario,
		     "Inserta la clave hola y valor");

	pa2m_afirmar(hash_cantidad(diccionario) == 3, "Tiene 3 items.");

	hash_destruir(diccionario);
}

void quitar_elemento_que_no_esta()
{
	printf("\nDevuelve NULL al tratar quitar un elemento que no está en el Diccionario\n");
	hash_t *diccionario = hash_crear(3);

	void *anterior = NULL;
	pa2m_afirmar(hash_insertar(diccionario, "hola", "hola", &anterior) ==
			     diccionario,
		     "Inserta la clave hola y valor");
	pa2m_afirmar(hash_insertar(diccionario, "como", "como", &anterior) ==
			     diccionario,
		     "Inserta la clave como y valor");
	pa2m_afirmar(hash_insertar(diccionario, "estas", "estas?", &anterior) ==
			     diccionario,
		     "Inserta la clave estas y valor");

	pa2m_afirmar(hash_cantidad(diccionario) == 3, "Tiene 3 items.");

	pa2m_afirmar(hash_quitar(diccionario, "blablabla") == NULL,
		     "Es NULL porque no existe el elemento en el diccionario.");
	pa2m_afirmar(hash_cantidad(diccionario) == 3,
		     "Tiene 3 items, no hizo ningún cambio.");

	hash_destruir(diccionario);
}

void guardar_elemento(hash_t *diccionario, const char *clave, void *elemento)
{
	void *anterior = NULL;
	pa2m_afirmar(hash_insertar(diccionario, clave, elemento, &anterior) ==
			     diccionario,
		     "Inserto correctamente.");

	if (anterior != NULL) {
		printf("anterior: %i\n", *(int *)anterior);
	}
	printf("anterior: %p\n", anterior);
}

void borrar_elemento(hash_t *diccionario, const char *clave, void *elemento)
{
	pa2m_afirmar(hash_quitar(diccionario, clave) == elemento,
		     "Quitó correctamente.");
}

void quitar_elemento_y_volver_a_insertar()
{
	printf("\nQuito un elemento y vuelvo a insertarlo en el diccionario\n");
	hash_t *diccionario = hash_crear(3);
	void *anterior = NULL;
	int valor1 = 1;
	int valor2 = 2;

	pa2m_afirmar(hash_insertar(diccionario, "1", &valor1, &anterior) ==
			     diccionario,
		     "Inserto par clave valor 1 por primera vez.");
	pa2m_afirmar(anterior == NULL,
		     "Al insertar por primera vez, anterior es NULL");

	pa2m_afirmar(*(int *)hash_obtener(diccionario, "1") == valor1,
		     "se busca por clave y se obtiene num1");

	pa2m_afirmar(hash_insertar(diccionario, "1", &valor2, &anterior) ==
			     diccionario,
		     "se actualiza el par clave-valor1 por clave-valor2");
	pa2m_afirmar(
		*(int *)anterior == valor1,
		"Al insertar otro valor con la misma clave, anterior es 1");

	pa2m_afirmar(*(int *)hash_obtener(diccionario, "1") == valor2,
		     "se busca por clave y ahora se obtiene valor2");

	pa2m_afirmar(*(int *)hash_quitar(diccionario, "1") == valor2,
		     "se borra por clave y se obtiene el valor2");
	pa2m_afirmar(hash_obtener(diccionario, "1") == NULL,
		     "se busca por clave y ahora se obtiene NULL");

	pa2m_afirmar(
		hash_insertar(diccionario, "1", &valor2, &anterior) ==
			diccionario,
		"se vuelve a insertar el par clave-valor1 por clave-valor2");
	pa2m_afirmar(anterior == NULL,
		     "Al volver a insertar la clave el valor anterior es NULL");

	hash_destruir(diccionario);
}

void quitar_elemento_y_volver_a_insertar_pedir_memoria()
{
	printf("\nQuito un elemento y vuelvo a insertarlo en el diccionario pidiendo memoria\n");
	hash_t *diccionario = hash_crear(3);
	void *anterior = NULL;
	int *valor1 = malloc(sizeof(int));
	int *valor2 = malloc(sizeof(int));

	*valor1 = 1;
	*valor2 = 2;

	pa2m_afirmar(hash_insertar(diccionario, "1", valor1, &anterior) ==
			     diccionario,
		     "Inserto par clave valor 1 por primera vez.");
	pa2m_afirmar(anterior == NULL,
		     "Al insertar por primera vez, anterior es NULL");

	pa2m_afirmar(*(int *)hash_obtener(diccionario, "1") == *valor1,
		     "se busca por clave y se obtiene num1");

	pa2m_afirmar(hash_insertar(diccionario, "1", valor2, &anterior) ==
			     diccionario,
		     "se actualiza el par clave-valor1 por clave-valor2");
	pa2m_afirmar(
		*(int *)anterior == *valor1,
		"Al insertar otro valor con la misma clave, anterior es 1");

	free(valor1);

	pa2m_afirmar(*(int *)hash_obtener(diccionario, "1") == *valor2,
		     "se busca por clave y ahora se obtiene valor2");

	pa2m_afirmar(*(int *)hash_quitar(diccionario, "1") == *valor2,
		     "se borra por clave y se obtiene el valor2");
	pa2m_afirmar(hash_obtener(diccionario, "1") == NULL,
		     "se busca por clave y ahora se obtiene NULL");

	pa2m_afirmar(
		hash_insertar(diccionario, "1", &valor2, &anterior) ==
			diccionario,
		"se vuelve a insertar el par clave-valor1 por clave-valor2");
	pa2m_afirmar(anterior == NULL,
		     "Al volver a insertar la clave el valor anterior es NULL");

	//free(valor1);
	free(valor2);
	hash_destruir(diccionario);
}

void recorrer_diccionario()
{
	printf("\nRecorro el diccionario\n");
	hash_t *diccionario = hash_crear(3);

	int num1 = 1, num2 = 2, num3 = 3, num4 = 4, num5 = 5;
	int num6 = 6, num7 = 7, num8 = 8;

	void *anterior1 = NULL;
	void *anterior2 = NULL;
	void *anterior3 = NULL;
	void *anterior4 = NULL;
	void *anterior5 = NULL;
	void *anterior6 = NULL;
	void *anterior7 = NULL;
	void *anterior8 = NULL;

	pa2m_afirmar(hash_insertar(diccionario, "1", &num1, &anterior1) ==
			     diccionario,
		     "Inserto la clave 1 y valor 1");
	pa2m_afirmar(hash_insertar(diccionario, "2", &num2, &anterior2) ==
			     diccionario,
		     "Inserto la clave 2 y valor 2");
	pa2m_afirmar(hash_insertar(diccionario, "3", &num3, &anterior3) ==
			     diccionario,
		     "Inserto la clave 3 y valor 3");
	pa2m_afirmar(hash_insertar(diccionario, "4", &num4, &anterior4) ==
			     diccionario,
		     "Inserto la clave 4 y valor 4");
	pa2m_afirmar(hash_insertar(diccionario, "5", &num5, &anterior5) ==
			     diccionario,
		     "Inserto la clave 5 y valor 5");
	pa2m_afirmar(hash_insertar(diccionario, "6", &num6, &anterior6) ==
			     diccionario,
		     "Inserto la clave 6 y valor 6");
	pa2m_afirmar(hash_insertar(diccionario, "7", &num7, &anterior7) ==
			     diccionario,
		     "Inserto la clave 7 y valor 7");
	pa2m_afirmar(hash_insertar(diccionario, "8", &num8, &anterior8) ==
			     diccionario,
		     "Inserto la clave 8 y valor 8");

	pa2m_afirmar(hash_cantidad(diccionario) == 8,
		     "El diccionario tiene 8 items.");

	hash_con_cada_clave(diccionario, ver_elementos_numeros, NULL);

	hash_destruir(diccionario);
}

void recorrer_y_destruir_diccionario()
{
	printf("\nRecorro el diccionario con elementos en memoria\n");
	hash_t *diccionario = hash_crear(3);

	void *anterior1 = NULL;
	void *anterior2 = NULL;
	void *anterior3 = NULL;
	void *anterior4 = NULL;
	void *anterior5 = NULL;

	int *num1 = malloc(sizeof(int)), *num2 = malloc(sizeof(int)),
	    *num3 = malloc(sizeof(int)), *num4 = malloc(sizeof(int)),
	    *num5 = malloc(sizeof(int));
	int *num6 = malloc(sizeof(int)), *num7 = malloc(sizeof(int)),
	    *num8 = malloc(sizeof(int));

	*num1 = 1, *num2 = 2, *num3 = 3, *num4 = 4, *num5 = 5;
	*num6 = 6, *num7 = 7, *num8 = 8;

	pa2m_afirmar(hash_insertar(diccionario, "1", num1, &anterior1) ==
			     diccionario,
		     "Inserto la clave 1 y valor 1");
	pa2m_afirmar(hash_insertar(diccionario, "2", num2, &anterior2) ==
			     diccionario,
		     "Inserto la clave 2 y valor 2");
	pa2m_afirmar(hash_insertar(diccionario, "3", num3, &anterior3) ==
			     diccionario,
		     "Inserto la clave 3 y valor 3");
	pa2m_afirmar(hash_insertar(diccionario, "4", num4, &anterior4) ==
			     diccionario,
		     "Inserto la clave 4 y valor 4");
	pa2m_afirmar(hash_insertar(diccionario, "5", num5, &anterior5) ==
			     diccionario,
		     "Inserto la clave 5 y valor 5");
	printf("\n");
	pa2m_afirmar(hash_cantidad(diccionario) == 5,
		     "El diccionario tiene 5 items.");
	printf("\n");

	pa2m_afirmar(hash_insertar(diccionario, "1", num8, &anterior1) ==
			     diccionario,
		     "Misma clave 1 y cambia de valor a 8");
	pa2m_afirmar(hash_insertar(diccionario, "3", num6, &anterior3) ==
			     diccionario,
		     "Misma clave 3 y cambia de valor a 6");
	pa2m_afirmar(hash_insertar(diccionario, "5", num7, &anterior5) ==
			     diccionario,
		     "Misma clave 5 y cambia de valor a 7");
	printf("\n");

	hash_con_cada_clave(diccionario, ver_elementos_numeros, NULL);
	printf("\n");

	pa2m_afirmar(*(int *)anterior1 == 1, "Clave 1, anterior 1");
	pa2m_afirmar(*(int *)anterior3 == 3, "Clave 3, anterior 3");
	pa2m_afirmar(*(int *)anterior5 == 5, "Clave 5, anterior 5");
	free(anterior1);
	free(anterior3);
	free(anterior5);

	hash_destruir_todo(diccionario, free);
}

int main()
{
	pa2m_nuevo_grupo("\nIniciar Diccionario");
	iniciar_dicc_vacio();

	pa2m_nuevo_grupo("\nInsertar en Diccionario");
	iniciar_dicc_con_elementos();
	insertar_elementos_con_misma_clave();

	pa2m_nuevo_grupo("\nAnterior en Diccionario");
	usar_anterior_diccionario();

	pa2m_nuevo_grupo("\nBuscar y contiene en Diccionario");
	buscar_elemento_en_dicc();

	pa2m_nuevo_grupo("\nQuitar del Diccionario");
	quitar_elemento();
	quitar_elemento_que_no_esta();
	quitar_elemento_y_volver_a_insertar();
	quitar_elemento_y_volver_a_insertar_pedir_memoria();

	pa2m_nuevo_grupo("\nRecorrer Diccionario");
	recorrer_diccionario();
	recorrer_y_destruir_diccionario();

	return pa2m_mostrar_reporte();
}