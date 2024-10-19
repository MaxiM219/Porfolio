#ifndef __MENU_H__
#define __MENU_H__
#include <stdbool.h>
#include "tp.h"

#define INTENTOS_FACIL 7
#define INTENTOS_NORMAL 5
#define INTENTOS_DIFICIL 3
#define INTENTOS_IMPOSIBLE 2

enum DIFICULTAD { FACIL, NORMAL, DIFICIL, IMPOSIBLE };

typedef struct {
	TP *tp;
	bool partida;
	bool carrera_iniciada;
	int dificultad;
	int intentos;
	const struct pokemon_info *pokemon_j1;
	const struct pokemon_info *pokemon_j2;
	int tamanio_pista_j1;
	int tamanio_pista_j2;
} Juego;

/*Creo un menu que a partir del TP creado.
Este inicia la partida. La dificultad será a partir de las opciones del jugador. 
Se asigna un pokémon al jugador 2, la pista y los intentos del jugador 1 a partir de la dificultad.
Devuelve NULL en caso de que el TP o el menu no se hayan creado.*/
Juego *iniciar_juego(TP *tp);

/*A partir del menú se va a ejecutar las acciones que el jugador va a realizar.
Devuelve si no hay un menu.*/
void menu_ejecutar(Juego *menu);

/*Destruye el todo lo relacionado con el menú.
*/
void destruir_menu(Juego *menu);

#endif /*__MENU_H__*/