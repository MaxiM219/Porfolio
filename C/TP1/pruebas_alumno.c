#include "pa2m.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "src/tp.h"

void crear_tp_vacio(const char *nombre_archivo)
{
	printf("Creo por primera vez el TP.\n");
	TP *tp = tp_crear(nombre_archivo);
	pa2m_afirmar(tp != NULL, "El TP fue creado.");
	tp_destruir(tp);
}

void crear_tp_sin_archivo()
{
	printf("\nCreo por primera vez el TP sin pasarle el archivo.\n");
	TP *tp = tp_crear(NULL);
	pa2m_afirmar(tp == NULL, "El TP no fue creado.");
}

void crear_tp_con_archivo_incorrecto(const char *archivo_malo)
{
	printf("\nCreo por primera vez el TP con un archivo con los datos incorrectos.\n");
	TP *tp = tp_crear(archivo_malo);
	pa2m_afirmar(tp == NULL, "El TP no fue creado.");
}

void tp_cantidad_de_pokemon(const char *nombre_archivo)
{
	printf("\nHay una cierta cantidad de pokemones.\n");
	TP *tp = tp_crear(nombre_archivo);
	pa2m_afirmar(tp != NULL, "EL TP fue creado.");
	pa2m_afirmar(tp_cantidad_pokemon(tp) != 0,
		     "Hay 25 pokemones en el TP.");
	tp_destruir(tp);
}

void nombres_disponibles(const char *nombre_archivo)
{
	printf("\nMostrar los pokemones disponibles.\n");
	TP *tp = tp_crear(nombre_archivo);
	char *nombres = tp_nombres_disponibles(tp);
	printf("%s\n", nombres);
	pa2m_afirmar(
		strcmp(nombres,
		       "Blastoise,Charizard,Dragonite,Geodude,Pikachu,Raichu,Vulpix,Wartortle,Zapdos") ==
			0,
		"Los nombres de los pokemones están ordenados");
	free(nombres);
	tp_destruir(tp);
}

void tp_buscar_un_pokemon(const char *nombre_archivo)
{
	printf("Busco un pokemon en el TP.\n");
	TP *tp = tp_crear(nombre_archivo);
	pa2m_afirmar(tp != NULL, "El TP fue creado.");
	pa2m_afirmar(strcmp(tp_buscar_pokemon(tp, "Meowth")->nombre,
			    "Meowth") == 0,
		     "Se encontro al pokemon Meowth en la búsqueda.");
	pa2m_afirmar(
		strcmp(tp_buscar_pokemon(tp, "piKAChu")->nombre, "Pikachu") ==
			0,
		"Se encontro al pokemon Pikachu en la búsqueda con su nombre mal escrito (piKAChu).");
	tp_destruir(tp);
}

void tp_buscar_un_pokemon_no_valido(const char *nombre_archivo)
{
	printf("\nBusco un pokemon que no está en el TP.\n");
	TP *tp = tp_crear(nombre_archivo);
	pa2m_afirmar(tp_buscar_pokemon(tp, "Bonsly") == NULL,
		     "No se encontro al pokemon Bonsly en la búsqueda.");

	tp_destruir(tp);
}

//---------------Seleccionar Pokemon---------------//

void tp_seleccionar_pokemon_inicio(const char *nombre_archivo)
{
	printf("\nSelecciono un pokemon por primera vez\n");
	TP *tp = tp_crear(nombre_archivo);

	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu") == true,
		     "El jugador 1 selecciona a Pikachu.");
	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_2, "Moltres") == true,
		     "El jugador 2 selecciona a Moltres, el guajolote Macías.");

	tp_destruir(tp);
}

void tp_seleccionar_pokemon_reemplazo(const char *nombre_archivo)
{
	printf("\nSelecciono un pokemon de reemplazo\n");
	TP *tp = tp_crear(nombre_archivo);

	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu") == true,
		     "El jugador 1 selecciona a Pikachu.");
	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_2, "Squirtle") == true,
		     "El jugador 2 selecciona a Squirtle.");

	pa2m_afirmar(
		tp_seleccionar_pokemon(tp, JUGADOR_2, "Pikachu") == false,
		"El jugador 2 no puede seleccionar a Pikachu. J1 lo tiene asignado.");

	pa2m_afirmar(
		tp_seleccionar_pokemon(tp, JUGADOR_2, "Diglett") == true,
		"El jugador 2 pudo seleccionar a Diglett. J1 no lo tiene asignado.");

	tp_destruir(tp);
}

void seleccionar_pokemon_y_comparar_nombre(const char *nombre_archivo)
{
	printf("\nSelecciono un pokemon de reemplazo\n");
	TP *tp = tp_crear(nombre_archivo);

	pa2m_afirmar(
		tp_pokemon_seleccionado(tp, JUGADOR_1) == NULL,
		"El jugador 1 al inicio no tiene un pokémon para mostrar los datos.");

	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu") == true,
		     "El jugador 1 selecciona a Pikachu.");
	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_2, "Squirtle") == true,
		     "El jugador 2 selecciona a Squirtle.");

	pa2m_afirmar(strcmp(tp_pokemon_seleccionado(tp, JUGADOR_1)->nombre,
			    "Pikachu") == 0,
		     "El nombre del pokémon del jugador 1 es Pikachu.");

	pa2m_afirmar(
		tp_seleccionar_pokemon(tp, JUGADOR_2, "Diglett") == true,
		"El jugador 2 pudo seleccionar a Diglett. J1 no lo tiene asignado.");

	pa2m_afirmar(strcmp(tp_pokemon_seleccionado(tp, JUGADOR_2)->nombre,
			    "Diglett") == 0,
		     "El nombre del pokémon del jugador 2 es Diglett.");

	tp_destruir(tp);
}

void agregar_obstaculos(const char *nombre_archivo)
{
	printf("\nAgrego obstáculos a la pista\n");
	TP *tp = tp_crear(nombre_archivo);

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_FUERZA, 0) ==
			     1,
		     "Agrego el primer obstáculo a la lista.");
	pa2m_afirmar(
		tp_agregar_obstaculo(tp, 3, OBSTACULO_FUERZA, 0) == 0,
		"No agrego el obstáculo a la lista porque tiene un jugador no valido.");
	pa2m_afirmar(
		tp_agregar_obstaculo(tp, JUGADOR_1, 5, 0) == 0,
		"No agrego el obstáculo a la lista porque tiene un obstáculo no valido.");
	pa2m_afirmar(
		tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_FUERZA, 100) == 2,
		"Agrego el obstáculo a la lista con una posición mayor a la que tengo actualmente.");

	tp_destruir(tp);
}

void quitar_obstaculos(const char *nombre_archivo)
{
	printf("\nQuito los obstáculos de la pista\n");
	TP *tp = tp_crear(nombre_archivo);

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA,
					  0) == 1,
		     "Agrego el obstaculo I.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_FUERZA, 1) ==
			     2,
		     "Agrego el obstaculo F.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA,
					  2) == 3,
		     "Agrego el obstaculo D.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA,
					  3) == 4,
		     "Agrego el obstaculo D.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA,
					  4) == 5,
		     "Agrego el obstaculo D.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA,
					  5) == 6,
		     "Agrego el obstaculo D.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA,
					  6) == 7,
		     "Agrego el obstaculo I.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA,
					  7) == 8,
		     "Agrego el obstaculo I.");

	char *obstaculos = tp_obstaculos_pista(tp, JUGADOR_1);
	pa2m_afirmar(strcmp(obstaculos, "IFDDDDII") == 0,
		     "El string es IFDDDDII");
	free(obstaculos);

	pa2m_afirmar(tp_quitar_obstaculo(tp, JUGADOR_1, 0) == 7,
		     "Quito el obstaculo I del comienzo.");
	obstaculos = tp_obstaculos_pista(tp, JUGADOR_1);
	pa2m_afirmar(strcmp(obstaculos, "FDDDDII") == 0,
		     "El string es FDDDDII");
	free(obstaculos);

	pa2m_afirmar(tp_quitar_obstaculo(tp, 3, 0) == 0,
		     "No puedo quitar un obstaculo con un jugador no valido.");

	pa2m_afirmar(tp_quitar_obstaculo(tp, JUGADOR_1, 100) == 6,
		     "Puedo quitar un obstaculo con una posición muy grande.");
	obstaculos = tp_obstaculos_pista(tp, JUGADOR_1);
	pa2m_afirmar(strcmp(obstaculos, "FDDDDI") == 0, "El string es FDDDDI");
	free(obstaculos);

	tp_destruir(tp);
}

void limpiar_pista(const char *nombre_archivo)
{
	printf("\nQuito todos los obstáculos de la pista\n");
	TP *tp = tp_crear(nombre_archivo);

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA,
					  0) == 1,
		     "Agrego el obstaculo I.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_FUERZA, 1) ==
			     2,
		     "Agrego el obstaculo F.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA,
					  2) == 3,
		     "Agrego el obstaculo D.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA,
					  3) == 4,
		     "Agrego el obstaculo D.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA,
					  4) == 5,
		     "Agrego el obstaculo D.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA,
					  5) == 6,
		     "Agrego el obstaculo D.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA,
					  6) == 7,
		     "Agrego el obstaculo I.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA,
					  7) == 8,
		     "Agrego el obstaculo I.");

	char *obstaculos = tp_obstaculos_pista(tp, JUGADOR_1);
	pa2m_afirmar(strcmp(obstaculos, "IFDDDDII") == 0,
		     "El string es IFDDDDII");
	free(obstaculos);

	tp_limpiar_pista(tp, JUGADOR_1);

	obstaculos = tp_obstaculos_pista(tp, JUGADOR_1);
	pa2m_afirmar(obstaculos == NULL,
		     "Ya no hay una pista de obstaculos por que fue limpiada.");
	free(obstaculos);

	tp_destruir(tp);
}

void calcular_tiempo_pista(const char *nombre_archivo)
{
	printf("\nCalculcar el tiempo de los obstáculos de la pista\n");
	TP *tp = tp_crear(nombre_archivo);

	pa2m_afirmar(
		tp_calcular_tiempo_pista(tp, JUGADOR_1) == 0,
		"No se puede calcular el tiempo por que el jugador no selecciono un pokémon.");
	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu") == true,
		     "El jugador 1 selecciona a Pikachu.");
	pa2m_afirmar(
		tp_calcular_tiempo_pista(tp, JUGADOR_1) == 0,
		"No se puede calcular el tiempo por que el jugador no agrego obstaculos.");

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA,
					  0) == 1,
		     "Agrego el obstaculo I.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_FUERZA, 1) ==
			     2,
		     "Agrego el obstaculo F.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA,
					  2) == 3,
		     "Agrego el obstaculo D.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA,
					  3) == 4,
		     "Agrego el obstaculo D.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA,
					  4) == 5,
		     "Agrego el obstaculo D.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA,
					  5) == 6,
		     "Agrego el obstaculo D.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA,
					  6) == 7,
		     "Agrego el obstaculo I.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA,
					  7) == 8,
		     "Agrego el obstaculo I.");

	char *obstaculos = tp_obstaculos_pista(tp, JUGADOR_1);
	pa2m_afirmar(strcmp(obstaculos, "IFDDDDII") == 0,
		     "El string es IFDDDDII");
	free(obstaculos);

	pa2m_afirmar(tp_calcular_tiempo_pista(tp, JUGADOR_1) == 6,
		     "El tiempo con Pikachu es 6.");

	tp_destruir(tp);
}

void mostrar_tiempo_pista(const char *nombre_archivo)
{
	printf("\nCalculcar el tiempo de los obstáculos de la pista\n");
	TP *tp = tp_crear(nombre_archivo);

	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_2, "Pikachu") == true,
		     "El jugador 2 selecciona a Pikachu.");

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_INTELIGENCIA,
					  0) == 1,
		     "Agrego el obstaculo I.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_FUERZA, 1) ==
			     2,
		     "Agrego el obstaculo F.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_DESTREZA,
					  2) == 3,
		     "Agrego el obstaculo D.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_DESTREZA,
					  3) == 4,
		     "Agrego el obstaculo D.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_DESTREZA,
					  4) == 5,
		     "Agrego el obstaculo D.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_DESTREZA,
					  5) == 6,
		     "Agrego el obstaculo D.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_INTELIGENCIA,
					  6) == 7,
		     "Agrego el obstaculo I.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_INTELIGENCIA,
					  7) == 8,
		     "Agrego el obstaculo I.");

	char *obstaculos = tp_obstaculos_pista(tp, JUGADOR_2);
	pa2m_afirmar(strcmp(obstaculos, "IFDDDDII") == 0,
		     "El string es IFDDDDII");
	free(obstaculos);

	char *tiempo = tp_tiempo_por_obstaculo(tp, JUGADOR_2);
	pa2m_afirmar(tp_calcular_tiempo_pista(tp, JUGADOR_2) == 6,
		     "El tiempo con Pikachu es 6.");
	pa2m_afirmar(strcmp(tiempo, "2,0,1,0,0,0,2,1") == 0,
		     "El tiempo con Pikachu es (2,0,1,0,0,0,2,1).");
	free(tiempo);
	pa2m_afirmar(tp_quitar_obstaculo(tp, JUGADOR_2, 3) == 7,
		     "Quito el obstaculo de la posicion 3 (D).");
	tiempo = tp_tiempo_por_obstaculo(tp, JUGADOR_2);
	pa2m_afirmar(strcmp(tiempo, "2,0,1,0,0,2,1") == 0,
		     "El tiempo con Pikachu es (2,0,1,0,0,2,1).");

	free(tiempo);
	tp_destruir(tp);
}

int main()
{
	const char *archivo = "ejemplo/pokemones.txt";
	const char *archivo_malo = "ejemplo/pokemones mod.txt";
	const char *archivo_corto = "ejemplo/pocos_pokemones.txt";
	pa2m_nuevo_grupo("Iniciar TP");
	crear_tp_vacio(archivo);
	crear_tp_sin_archivo();
	crear_tp_con_archivo_incorrecto(archivo_malo);
	tp_cantidad_de_pokemon(archivo);

	pa2m_nuevo_grupo("Nombres disponibles en TP");
	nombres_disponibles(archivo_corto);

	pa2m_nuevo_grupo("Buscar pokemon en TP");
	tp_buscar_un_pokemon(archivo);
	tp_buscar_un_pokemon_no_valido(archivo);

	pa2m_nuevo_grupo("Seleccionar pokemon en TP");
	tp_seleccionar_pokemon_inicio(archivo);
	tp_seleccionar_pokemon_reemplazo(archivo);

	pa2m_nuevo_grupo("Pokemon seleccionado en TP");
	seleccionar_pokemon_y_comparar_nombre(archivo);

	pa2m_nuevo_grupo("Agregar obstáculos en TP");
	agregar_obstaculos(archivo);

	pa2m_nuevo_grupo("Quitar obstáculos en TP");
	quitar_obstaculos(archivo);

	pa2m_nuevo_grupo("Limpiar pista de obstáculos en TP");
	limpiar_pista(archivo);

	pa2m_nuevo_grupo("Calculo el tiempo de la pista de obstaculos en TP");
	calcular_tiempo_pista(archivo);

	pa2m_nuevo_grupo("Muestro el tiempo de la pista de obstaculos en TP");
	mostrar_tiempo_pista(archivo);

	return pa2m_mostrar_reporte();
}
