#include "pa2m.h"
#include "src/cola.h"
#include "src/lista.h"
#include "src/pila.h"

#include <stdio.h>
#include <stdlib.h>

int es_elemento(void *elemento, void *numero)
{
	if (elemento == numero)
		return 0;

	return -1;
}

bool buscar_elemento(void *elemento, void *buscado)
{
	if (elemento == buscado) {
		return false;
	}
	return true;
}

void iniciar_lista_vacia()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_tamanio(lista) == 0, "creo la lista vacia.");
	pa2m_afirmar(lista_vacia(lista) == true, "La lista está vacía.");
	lista_destruir(lista);
}

void iniciar_lista_vacia_y_tamanio()
{
	lista_t *lista = NULL;

	pa2m_afirmar(lista_tamanio(lista) == 0,
		     "La lista es NULL y está vacía.");
	pa2m_afirmar(lista_vacia(lista) == true,
		     "La lista es NULL y está vacía.");
	lista_destruir(lista);
}

//---------------------Insertar--------------------

void lista_con_un_elemento()
{
	printf("\nPrueba de Insertar Un Elemento\n");
	lista_t *lista = lista_crear();
	int num = 3;
	lista_insertar(lista, &num);

	pa2m_afirmar(lista_tamanio(lista) == 1, "El tamaño de la lista es 1.");

	int *numero = lista_primero(lista);
	int *ult_numero = lista_ultimo(lista);
	pa2m_afirmar(*numero == 3, "El numero del primero de la lista es 3.");
	pa2m_afirmar(*ult_numero == 3,
		     "El numero del ultimo de la lista es 3.");

	lista_destruir(lista);
}

void lista_con_dos_elementos()
{
	printf("\nPrueba de Insertar Dos Elementos\n");
	lista_t *lista = lista_crear();
	int num = 1, num2 = 2;
	lista_insertar(lista, &num);
	lista_insertar(lista, &num2);

	pa2m_afirmar(lista_tamanio(lista) == 2, "El tamaño de la lista es 1.");

	int *numero = lista_primero(lista);
	int *ult_numero = lista_ultimo(lista);
	pa2m_afirmar(*numero == 1, "El numero del primero de la lista es 3.");
	pa2m_afirmar(*ult_numero == 2,
		     "El numero del ultimo de la lista es 3.");

	lista_destruir(lista);
}

void lista_insertar_elementos_e_imprimir()
{
	printf("\nPrueba de Insertar Elementos e iterador a mano\n");
	lista_t *lista = lista_crear();
	int num = 1, num2 = 2, num3 = 3, num4 = 4, num5 = 5;

	lista_insertar(lista, &num);
	lista_insertar(lista, &num2);
	lista_insertar(lista, &num3);
	lista_insertar(lista, &num4);
	lista_insertar(lista, &num5);

	lista_iterador_t *it = NULL;

	printf("Uso el iterador externo para imprimir la lista con el nuevo numero "
	       "agregado. ");
	for (it = lista_iterador_crear(lista);
	     lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it))
		printf("%i ", *(int *)lista_iterador_elemento_actual(it));
	printf("\n\n");

	lista_iterador_destruir(it);

	lista_destruir(lista);
}

void lista_insertar_elementos()
{
	printf("\nPrueba de Insertar Varios Elementos\n");
	lista_t *lista = lista_crear();
	int num = 1, num2 = 2, num3 = 3, num4 = 4, num5 = 5;
	lista_insertar(lista, &num);
	lista_insertar(lista, &num2);

	pa2m_afirmar(lista_tamanio(lista) == 2, "El tamaño de la lista es 1.");
	pa2m_afirmar(*(int *)lista_primero(lista) == 1,
		     "El primero de la lista es 1.");
	pa2m_afirmar(*(int *)lista_ultimo(lista) == 2,
		     "El ultimo de la lista es 2.");

	lista_insertar(lista, &num4);
	lista_insertar(lista, &num5);
	lista_insertar_en_posicion(lista, &num3, 0);
	pa2m_afirmar(*(int *)lista_primero(lista) == 3,
		     "El numero del primero de la lista es 3.");
	pa2m_afirmar(*(int *)lista_ultimo(lista) == 5,
		     "El numero del ultimo de la lista es 5.");

	lista_iterador_t *it = NULL;

	printf("\nUso el iterador externo para imprimir la lista. ");
	for (it = lista_iterador_crear(lista);
	     lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it))
		printf("%i ", *(int *)lista_iterador_elemento_actual(it));
	printf("\n\n");

	lista_iterador_destruir(it);

	int num6 = 6;
	lista_insertar_en_posicion(lista, &num6, 65);

	printf("Uso el iterador externo para imprimir la lista con el nuevo numero "
	       "agregado. ");
	for (it = lista_iterador_crear(lista);
	     lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it))
		printf("%i ", *(int *)lista_iterador_elemento_actual(it));
	printf("\n\n");

	lista_iterador_destruir(it);

	pa2m_afirmar(lista_tamanio(lista) == 6, "El tamaño de la lista es 6.");
	pa2m_afirmar(*(int *)lista_elemento_en_posicion(lista, 5) == 6,
		     "Devuelve de la lista el 6 que está en la posición 1.");

	lista_destruir(lista);
}

void lista_insertar_varios_elementos()
{
	printf("\nPrueba de Insertar varios elementos\n");
	lista_t *lista = lista_crear();
	int num = 1, num2 = 2, num3 = 3, num4 = 4, num5 = 5, num6 = 6, num7 = 7;
	lista_insertar_en_posicion(lista, &num2, 10);
	lista_insertar_en_posicion(lista, &num, 0);
	lista_insertar_en_posicion(lista, &num3, 1);

	printf("%i", num);
	printf("%i", num2);
	printf("%i, %i, %i, %i, %i", num3, num4, num5, num6, num7);

	lista_iterador_t *it = NULL;

	printf("\nUso el iterador externo para imprimir la lista. ");
	for (it = lista_iterador_crear(lista);
	     lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it))
		printf("%i ", *(int *)lista_iterador_elemento_actual(it));
	printf("\n\n");

	lista_iterador_destruir(it);

	lista_destruir(lista);
}

void lista_insertar_varios_elementos_en_distintas_posiciones()
{
	printf("\nPrueba de Insertar varios elementos\n");
	lista_t *lista = lista_crear();
	lista_iterador_t *it = NULL;

	int num = 1, num2 = 2, num3 = 3, num4 = 4, num5 = 5, num6 = 6, num7 = 7;
	lista_insertar(lista, &num);
	pa2m_afirmar(lista_tamanio(lista) == 1, "La lista tiene 1 elemento.");
	lista_insertar_en_posicion(lista, &num2, 0);
	pa2m_afirmar(lista_tamanio(lista) == 2, "La lista tiene 2 elemento.");
	lista_insertar_en_posicion(lista, &num3, 1);
	pa2m_afirmar(lista_tamanio(lista) == 3, "La lista tiene 3 elemento.");
	lista_insertar_en_posicion(lista, &num4, 100);
	pa2m_afirmar(lista_tamanio(lista) == 4, "La lista tiene 4 elemento.");
	lista_insertar_en_posicion(lista, &num5, 2);
	pa2m_afirmar(lista_tamanio(lista) == 5, "La lista tiene 5 elemento.");
	lista_insertar_en_posicion(lista, &num6, 4);
	pa2m_afirmar(lista_tamanio(lista) == 6, "La lista tiene 6 elemento.");
	lista_insertar_en_posicion(lista, &num7, 6);
	pa2m_afirmar(lista_tamanio(lista) == 7, "La lista tiene 7 elemento.");

	pa2m_afirmar(*(int *)lista_elemento_en_posicion(lista, 0) == 2,
		     "El primer numero de la lista es 2.");
	pa2m_afirmar(*(int *)lista_elemento_en_posicion(lista, 1) == 3,
		     "El primer numero de la lista es 3.");
	pa2m_afirmar(*(int *)lista_elemento_en_posicion(lista, 2) == 5,
		     "El primer numero de la lista es 5.");
	pa2m_afirmar(*(int *)lista_elemento_en_posicion(lista, 3) == 1,
		     "El primer numero de la lista es 1.");
	pa2m_afirmar(*(int *)lista_elemento_en_posicion(lista, 4) == 6,
		     "El primer numero de la lista es 6.");
	pa2m_afirmar(*(int *)lista_elemento_en_posicion(lista, 5) == 4,
		     "El primer numero de la lista es 4.");
	pa2m_afirmar(*(int *)lista_elemento_en_posicion(lista, 6) == 7,
		     "El primer numero de la lista es 7.");

	printf("\nUso el iterador externo para imprimir la lista. ");
	for (it = lista_iterador_crear(lista);
	     lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it))
		printf("%i ", *(int *)lista_iterador_elemento_actual(it));
	printf("\n\n");

	lista_iterador_destruir(it);

	lista_destruir(lista);
}

void lista_insertar_varios_elementos_en_posicion()
{
	printf("\nPrueba de Insertar varios elementos en posición\n");
	lista_t *lista = lista_crear();
	int edad_a = 22, edad_m = 53, edad_s = 52, edad_v = 37, edad_l = 13,
	    edad_r = 22;

	pa2m_afirmar(lista == lista_insertar_en_posicion(lista, &edad_a, 0),
		     "Es posible");
	pa2m_afirmar(lista == lista_insertar_en_posicion(lista, &edad_m, 1),
		     "Es posible");
	pa2m_afirmar(lista == lista_insertar_en_posicion(lista, &edad_s, 2),
		     "Es posible");
	pa2m_afirmar(lista == lista_insertar_en_posicion(lista, &edad_v, 3),
		     "Es posible");
	pa2m_afirmar(lista == lista_insertar_en_posicion(lista, &edad_l, 4),
		     "Es posible");
	pa2m_afirmar(lista == lista_insertar_en_posicion(lista, &edad_r, 5),
		     "Es posible");

	pa2m_afirmar(edad_a == *(int *)lista_elemento_en_posicion(lista, 0),
		     "El elemento de la lista es correcto");
	pa2m_afirmar(edad_m == *(int *)lista_elemento_en_posicion(lista, 1),
		     "El elemento de la lista es correcto");
	pa2m_afirmar(edad_s != *(int *)lista_elemento_en_posicion(lista, 4),
		     "El elemento de la lista no es correcto");
	pa2m_afirmar(edad_s == *(int *)lista_elemento_en_posicion(lista, 2),
		     "El elemento de la lista es correcto");
	pa2m_afirmar(edad_v == *(int *)lista_elemento_en_posicion(lista, 3),
		     "El elemento de la lista es correcto");
	pa2m_afirmar(edad_l == *(int *)lista_elemento_en_posicion(lista, 4),
		     "El elemento de la lista es correcto");
	pa2m_afirmar(edad_r == *(int *)lista_elemento_en_posicion(lista, 0),
		     "El elemento de la lista es correcto");

	lista_iterador_t *it = NULL;

	printf("\nPrimero: %i ", *(int *)lista_primero(lista));

	printf("\nUso el iterador externo para imprimir la lista. ");
	for (it = lista_iterador_crear(lista);
	     lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it)) {
		printf("%i ", *(int *)lista_iterador_elemento_actual(it));
	}
	printf("\n\n");

	lista_iterador_destruir(it);

	lista_destruir(lista);
}
//---------------------Borrar--------------------

void lista_borrar_elementos()
{
	printf("\nPrueba de Borrar Elementos\n");
	lista_t *lista = lista_crear();
	int num = 1, num2 = 2;

	pa2m_afirmar(lista_quitar(lista) == NULL,
		     "Error. No hay nada en la lista.");

	lista_insertar(lista, &num);
	lista_insertar(lista, &num2);

	pa2m_afirmar(lista_tamanio(lista) == 2, "El tamaño de la lista es 2.");
	pa2m_afirmar(lista_tamanio(lista) == 2, "El tamaño de la lista es 1.");
	pa2m_afirmar(*(int *)lista_quitar(lista) == 2,
		     "El numero del primero de la lista es 2.");
	pa2m_afirmar(*(int *)lista_quitar(lista) == 1,
		     "El numero del ultimo de la lista es 1.");
	pa2m_afirmar(lista_quitar(lista) == NULL, "No hay nada en la lista.");
	pa2m_afirmar(lista_tamanio(lista) == 0, "El tamaño de la lista es 0.");

	lista_destruir(lista);
}

void lista_borrar_primera_posicion()
{
	printf("\nPrueba de Borrar la Primera Posición\n");
	lista_t *lista = lista_crear();
	int num = 1, num2 = 2, num3 = 3, num4 = 4, num5 = 5;

	lista_insertar(lista, &num);
	lista_insertar(lista, &num2);
	lista_insertar(lista, &num3);
	lista_insertar(lista, &num4);
	lista_insertar(lista, &num5);

	pa2m_afirmar(lista_tamanio(lista) == 5, "El tamaño de la lista es 5.");

	size_t tam = lista_tamanio(lista);
	for (size_t i = 0; i < tam; i++) {
		printf("%i: ", *(int *)lista_primero(lista));
		pa2m_afirmar(*(int *)lista_quitar_de_posicion(lista, 0) ==
				     i + 1,
			     "El numero de la posicion fue borrado.");
	}
	pa2m_afirmar(lista_tamanio(lista) == 0, "El tamaño de la lista es 0.");

	lista_destruir(lista);
}

void lista_borrar_elemento_en_posicion()
{
	printf("\nPrueba de Borrar en Posición\n");
	lista_t *lista = lista_crear();
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
	char f = 'f', g = 'g', h = 'h', i = 'i', j = 'j';

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);
	lista_insertar(lista, &e);

	//lista_elemento_en_posicion(lista, d)
	pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista, 3) == d,
		     "La letra d fue hallada.");

	printf("Imprimo TODOS LOS ELEMENTOS DE LA LISTA usando el iterador externo: \n");
	lista_iterador_t *it = NULL;

	for (it = lista_iterador_crear(lista);
	     lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it))
		printf("%c ", *(char *)lista_iterador_elemento_actual(it));
	printf("\n\n");

	lista_iterador_destruir(it);

	pa2m_afirmar(*(char *)lista_quitar_de_posicion(lista, 2) == c,
		     "La letra c fue removida.");

	printf("\n");
	printf("Imprimo TODOS LOS ELEMENTOS DE LA LISTA usando el iterador externo: \n");
	for (it = lista_iterador_crear(lista);
	     lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it))
		printf("%c ", *(char *)lista_iterador_elemento_actual(it));
	printf("\n\n");

	lista_iterador_destruir(it);

	lista_insertar(lista, &f);
	lista_insertar(lista, &g);
	lista_insertar(lista, &h);
	lista_insertar(lista, &i);
	lista_insertar(lista, &j);

	printf("Imprimo TODOS LOS ELEMENTOS DE LA LISTA usando el iterador externo: \n");
	for (it = lista_iterador_crear(lista);
	     lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it))
		printf("%c ", *(char *)lista_iterador_elemento_actual(it));
	printf("\n\n");

	lista_iterador_destruir(it);

	pa2m_afirmar(
		*(char *)lista_quitar(lista) == j,
		"La posición es 65 y la letra j fue removida por ser la última.");
	printf("\nImprimo TODOS LOS ELEMENTOS DE LA LISTA usando el iterador "
	       "externo: \n");
	for (it = lista_iterador_crear(lista);
	     lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it))
		printf("%c ", *(char *)lista_iterador_elemento_actual(it));
	printf("\n\n");

	lista_iterador_destruir(it);
	pa2m_afirmar(lista_tamanio(lista) == 8, "El tamaño de la lista es 8.");

	lista_destruir(lista);
}

//---------------------Buscar--------------------

void lista_buscar_elemento_por_posicion()
{
	printf("\nPrueba de Buscar Elemento Por Posición\n");
	lista_t *lista = lista_crear();
	int num = 1, num2 = 2, num3 = 3, num4 = 4, num5 = 5;

	lista_insertar(lista, &num);
	lista_insertar(lista, &num2);
	lista_insertar(lista, &num3);
	lista_insertar(lista, &num4);
	lista_insertar(lista, &num5);

	pa2m_afirmar(lista_tamanio(lista) == 5, "El tamaño de la lista es 5.");
	pa2m_afirmar((void *)lista_elemento_en_posicion(lista, 8) == NULL,
		     "No existe tal elemento en la posicion 8.");
	pa2m_afirmar(*(int *)lista_elemento_en_posicion(lista, 2) == 3,
		     "El numero de la posicion 2 es 3.");
	pa2m_afirmar(*(int *)lista_elemento_en_posicion(lista, 4) == 5,
		     "El numero de la posicion 4 es 5.");
	pa2m_afirmar((void *)lista_elemento_en_posicion(lista, 5) == NULL,
		     "No existe tal elemento en la posicion 5.");

	lista_destruir(lista);
}

void lista_buscar_elemento_con_Comparador()
{
	printf("\nPrueba de Buscar Elemento Por Comparador\n");
	lista_t *lista = lista_crear();
	int num = 4, num2 = 21, num3 = 32, num4 = 76, num5 = 64;

	lista_insertar(lista, &num);
	lista_insertar(lista, &num2);
	lista_insertar(lista, &num3);
	lista_insertar(lista, &num4);
	lista_insertar(lista, &num5);

	int numero = 15;
	pa2m_afirmar(*(int *)lista_buscar_elemento(lista, es_elemento, &num4) ==
			     76,
		     "Existe el 76.");
	pa2m_afirmar((void *)lista_buscar_elemento(lista, es_elemento,
						   &numero) == NULL,
		     "No existe el 15.");

	pa2m_afirmar((void *)lista_buscar_elemento(lista, NULL, &num4) == NULL,
		     "Buscar con la función en NULL devuelve NULL.");

	lista_destruir(lista);
}

//---------------------Destruir--------------------

void probar_operaciones_destruir_lista_Null()
{
	lista_t *lista = NULL;

	// Esto debería liberar la lista y cada bloque
	lista_destruir(lista);
}

void probar_operaciones_destructor_lista_Null()
{
	lista_t *lista = NULL;

	// Esto debería liberar la lista y cada bloque
	lista_destruir_todo(lista, free);

	lista_t *lista2 = lista_crear();
	lista_destruir_todo(lista2, NULL);
	//lista_destruir(lista2);
}

void probar_operaciones_destructor_lista()
{
	printf("\nPrueba de lista destructora con calloc\n");
	lista_t *lista = lista_crear();

	// Inserto varios bloques reservados con malloc
	pa2m_afirmar(lista_insertar(lista, malloc(sizeof(int))) == lista,
		     "Reservo memoria.");
	pa2m_afirmar(lista_insertar(lista, malloc(sizeof(int))) == lista,
		     "Reservo memoria.");
	pa2m_afirmar(lista_insertar(lista, malloc(sizeof(int))) == lista,
		     "Reservo memoria.");
	pa2m_afirmar(lista_insertar(lista, malloc(sizeof(int))) == lista,
		     "Reservo memoria.");
	pa2m_afirmar(lista_insertar(lista, malloc(sizeof(int))) == lista,
		     "Reservo memoria.");
	//lista_insertar(lista, malloc(sizeof(int)));

	// Esto debería liberar la lista y cada bloque
	lista_destruir_todo(lista, free);
}

void probar_operaciones_destructor_lista_con_calloc_malloc()
{
	printf("\nPrueba de lista destructora con calloc\n");
	lista_t *lista = lista_crear();

	//lista_destruir_todo(lista, NULL);

	// Inserto varios bloques reservados con malloc
	pa2m_afirmar(lista_insertar(lista, calloc(1, sizeof(int))) == lista,
		     "Reservo memoria.");
	pa2m_afirmar(lista_insertar(lista, calloc(1, sizeof(int))) == lista,
		     "NULL en la posicion 1.");
	pa2m_afirmar(lista_insertar(lista, malloc(sizeof(int))) == lista,
		     "Reservo memoria.");
	pa2m_afirmar(lista_insertar(lista, malloc(sizeof(int))) == lista,
		     "Reservo memoria.");
	pa2m_afirmar(lista_insertar(lista, malloc(sizeof(int))) == lista,
		     "Reservo memoria.");

	// Esto debería liberar la lista y cada bloque
	lista_destruir_todo(lista, free);
}

//---------------------Iterador Interno--------------------

void lista_insertar_elementos_y_recorrer_con_it_iterno()
{
	printf("\nPrueba de Insertar Elementos e iterador a mano\n");
	lista_t *lista = lista_crear();
	int num = 1, num2 = 2, num3 = 3, num4 = 4;

	lista_insertar(lista, &num);

	size_t elementos_recorridos = 0;
	elementos_recorridos =
		lista_con_cada_elemento(lista, buscar_elemento, &num);
	pa2m_afirmar(elementos_recorridos == 1,
		     "Busca el primer elemento y devuelve 1 elemento iterado.");

	printf("Recorri %lu elementos con el iterador interno elementos\n",
	       elementos_recorridos);

	printf("\n");

	lista_insertar(lista, &num2);

	elementos_recorridos =
		lista_con_cada_elemento(lista, buscar_elemento, &num2);
	pa2m_afirmar(
		elementos_recorridos == 2,
		"Busca el segundo elemento y devuelve 2 elementos iterados.");

	printf("Recorri %lu elementos con el iterador interno elementos\n",
	       elementos_recorridos);

	printf("\n");
	lista_insertar(lista, &num3);
	elementos_recorridos =
		lista_con_cada_elemento(lista, buscar_elemento, &num3);
	pa2m_afirmar(
		elementos_recorridos == 3,
		"Busca el tercer elemento y devuelve 3 elementos iterados.");

	printf("Recorri %lu elementos con el iterador interno elementos\n",
	       elementos_recorridos);

	printf("\n");
	pa2m_afirmar(lista_insertar(lista, &num4) == lista,
		     "Se inserta al final.");
	elementos_recorridos =
		lista_con_cada_elemento(lista, buscar_elemento, &num4);
	pa2m_afirmar(
		elementos_recorridos == 4,
		"Busca el elemento insertado y devuelve 4 elementos iterados.");

	printf("Recorri %lu elementos con el iterador interno elementos\n",
	       elementos_recorridos);

	printf("\n");

	elementos_recorridos =
		lista_con_cada_elemento(lista, buscar_elemento, &num3);
	pa2m_afirmar(
		elementos_recorridos == 3,
		"Busca el tercer elemento y devuelve 3 elementos iterados.");

	printf("Recorri %lu elementos con el iterador interno elementos\n",
	       elementos_recorridos);

	printf("\n");

	lista_destruir(lista);
}

//---------------------Iterador Externo--------------------

void lista_insertar_elementos_y_recorrer_con_it_externo()
{
	printf("\nPrueba de Insertar Elementos e iterador a mano\n");
	lista_t *lista = lista_crear();
	int num = 1, num2 = 2, num3 = 3, num4 = 4;

	pa2m_afirmar(lista_insertar(lista, &num) == lista,
		     "Se inserta al inicio ya que está vacía.");
	pa2m_afirmar(lista_insertar(lista, &num2) == lista,
		     "Se inserta al final.");
	pa2m_afirmar(lista_insertar(lista, &num3) == lista,
		     "Se inserta al final.");
	pa2m_afirmar(lista_insertar(lista, &num4) == lista,
		     "Se inserta al final.");

	lista_iterador_t *it = NULL;

	for (it = lista_iterador_crear(lista);
	     lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it))
		printf("%i ", *(int *)lista_iterador_elemento_actual(it));
	printf("\n\n");

	lista_iterador_destruir(it);

	lista_iterador_t *it_manual = NULL;

	printf("\nA mano\n");
	it_manual = lista_iterador_crear(lista);
	printf("%i ", *(int *)lista_iterador_elemento_actual(it_manual));
	lista_iterador_avanzar(it_manual);
	printf("%i ", *(int *)lista_iterador_elemento_actual(it_manual));
	lista_iterador_avanzar(it_manual);
	printf("%i ", *(int *)lista_iterador_elemento_actual(it_manual));
	lista_iterador_avanzar(it_manual);
	printf("%i ", *(int *)lista_iterador_elemento_actual(it_manual));
	lista_iterador_avanzar(it_manual);

	lista_iterador_destruir(it_manual);

	lista_destruir(lista);
}

//---------------------Pila--------------------

void probar_operaciones_pila()
{
	printf("\nPrueba de Pila\n");
	pila_t *pila = pila_crear();
	char *algo = "somtirogla";
	char *resultado = "algoritmos";

	for (int i = 0; algo[i] != 0; i++) {
		printf("Apilo %c\n", algo[i]);
		pila_apilar(pila, &algo[i]);
	}

	int i = 0;
	printf("\nDesapilo y muestro los elementos apilados: \n");
	while (!pila_vacia(pila)) {
		printf("%c", *(char *)pila_tope(pila));
		pa2m_afirmar(*(char *)pila_tope(pila) == resultado[i],
			     "El caracter coincide.");
		pila_desapilar(pila);
		i++;
	}
	printf("\n");

	pila_destruir(pila);
}

void probar_operaciones_pila_con_lista()
{
	printf("\nPrueba de Lista comportandose como pila\n");
	lista_t *pila = lista_crear();
	char *algo = "somtirogla";
	char *resultado = "algoritmos";

	for (int i = 0; algo[i] != 0; i++) {
		printf("Apilo %c\n", algo[i]);
		lista_insertar_en_posicion(pila, &algo[i], 0);
	}
	lista_iterador_t *it = NULL;

	for (it = lista_iterador_crear(pila);
	     lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it))
		printf("%c ", *(char *)lista_iterador_elemento_actual(it));
	printf("\n\n");

	lista_iterador_destruir(it);

	pa2m_afirmar(*(char *)lista_primero(pila) == 'a',
		     "El tope de la pila (usando lista) es 'a'.");
	pa2m_afirmar(lista_tamanio(pila) == 10,
		     "El tamaño de la pila (usando lista) es 10.");

	printf("\nDesapilo y muestro los elementos apilados: \n");

	int i = 0;
	while (!lista_vacia(pila) || resultado[i]) {
		printf("%c:  ", *(char *)lista_primero(pila));
		pa2m_afirmar(*(char *)lista_primero(pila) == resultado[i],
			     "El caracter coincide.");
		lista_quitar_de_posicion(pila, 0);
		i++;
	}
	printf("\n");
	lista_destruir(pila);
}
//---------------------Cola--------------------

void probar_operaciones_cola()
{
	printf("\nPrueba de Cola\n");
	cola_t *cola = cola_crear();
	char *algo = "algoritmos";

	pa2m_afirmar(cola_vacia(cola) == true, "Al inicio la cola está vacía.");

	for (int i = 0; algo[i] != 0; i++) {
		printf("Encolo %c\n", algo[i]);
		cola_encolar(cola, &algo[i]);
	}
	printf("\n");
	pa2m_afirmar(cola_tamanio(cola) == 10, "El tamaño de la cola es 10.");
	pa2m_afirmar(*(char *)cola_frente(cola) == 'a',
		     "El caracter 'a' coincide con el frente de la cola.");

	printf("\n");
	int i = 0;
	while (!cola_vacia(cola)) {
		printf("Desencolo %c  ", algo[i]);
		pa2m_afirmar(*(char *)cola_desencolar(cola) == algo[i],
			     "El caracter coincide al desencolar.");
		i++;
	}
	cola_destruir(cola);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== PRUEBAS =======================");
	pa2m_nuevo_grupo("\nLista Vacia");
	iniciar_lista_vacia();
	iniciar_lista_vacia_y_tamanio();

	pa2m_nuevo_grupo("\nInserto y Muestro");
	lista_con_un_elemento();
	lista_con_dos_elementos();
	lista_insertar_elementos();
	lista_insertar_varios_elementos();
	lista_insertar_varios_elementos_en_posicion();
	lista_insertar_elementos_e_imprimir();
	lista_insertar_varios_elementos_en_distintas_posiciones();

	pa2m_nuevo_grupo("\nPrueba de Borrar");
	lista_borrar_elementos();
	lista_borrar_primera_posicion();
	lista_borrar_elemento_en_posicion();

	pa2m_nuevo_grupo("\nPrueba de Buscar Elemento");
	lista_buscar_elemento_por_posicion();
	lista_buscar_elemento_con_Comparador();

	pa2m_nuevo_grupo("\nPrueba Destructora");
	probar_operaciones_destructor_lista();
	probar_operaciones_destruir_lista_Null();
	probar_operaciones_destructor_lista_Null();
	probar_operaciones_destructor_lista_con_calloc_malloc();

	pa2m_nuevo_grupo("\nPrueba de Iterador Interno");
	lista_insertar_elementos_y_recorrer_con_it_iterno();

	pa2m_nuevo_grupo("\nPrueba de Iterador Externo");
	lista_insertar_elementos_y_recorrer_con_it_externo();

	pa2m_nuevo_grupo("\nPila");
	probar_operaciones_pila();
	probar_operaciones_pila_con_lista();

	pa2m_nuevo_grupo("\nCola");
	probar_operaciones_cola();

	return pa2m_mostrar_reporte();
}
