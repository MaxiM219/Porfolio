#include "menu.h"
#include "tp.h"
#include "abb.h"
#include "split.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>

#define MAX_LINEA 100

void imprimir_logo()
{
	printf("\n\n");
	printf("                                //\n");
	printf("PPPPPP     OOOOO    KK    KK  EEEEEE   MM       MM    OOOOO    NN      NN\n");
	printf("PP   PP   OO   OO   KK   KK   EE       MMMM   MMMM   OO   OO   NNNN    NN\n");
	printf("PP   PP  OOO   OOO  KK  KK    EE       MM MM MM MM  OOO   OOO  NN NN   NN\n");
	printf("PPPPPP   OOO   OOO  KKKK      EEEEEE   MM   M   MM  OOO   OOO  NN  NN  NN\n");
	printf("PP       OOO   OOO  KK  KK    EE       MM       MM  OOO   OOO  NN   NN NN\n");
	printf("PP        OO   OO   KK   KK   EE       MM       MM   OO   OO   NN    NNNN\n");
	printf("PP         OOOOO    KK    KK  EEEEEE   MM       MM    OOOOO    NN      NN\n");
	printf("                    _____________________________\n");
	printf("                   /    CARRERA DE OBSTÁCULOS    /\n");
	printf("                  /_____________________________/\n");
	printf("\n\n");
}

/*Obtengo el número que escribio el usuario.*/
int obtener_tecla_numero()
{
	char numero[MAX_LINEA];
	if (fgets(numero, sizeof(numero), stdin) == NULL) {
		return -1;
	}
	return atoi(numero);
}
/*Obtengo el caracter que escribio el usuario.*/
char obtener_tecla()
{
	char letra[MAX_LINEA];
	if (fgets(letra, sizeof(letra), stdin) == NULL) {
		return 0;
	}
	return (char)*letra;
}

/*Obtengo el string que escribio el usuario para elegir al pokémon.*/
char *obtener_caracteres()
{
	char string[MAX_LINEA];

	char *linea = fgets(string, sizeof(string), stdin);
	if (linea) {
		linea[strlen(linea) - 1] = 0;
	}

	return linea;
}

void mostrar_ayuda_opciones_menu()
{
	printf(" _________________Menú principal_________________\n");
	printf("|       '?': Mostrar ayuda                       |\n");
	printf("|       'M': Mostrar datos del Pokémon           |\n");
	printf("|       'P': Agregar Obstáculos en la pista      |\n");
	printf("|       'R': Quitar Obstáculos de la pista       |\n");
	printf("|       'L': Limpiar Obstáculos de la pista      |\n");
	printf("|       'C': Empezar carrera de obstáculos       |\n");
	printf("|       'S': Selección de Pokémon                |\n");
	printf("|       'Q': Salir del programa                  |\n");
	printf("|________________________________________________|\n");
}

/*Le pide al usuario una dificultad del 1 al 4. 
En caso de que no ingresar un número se pide ingresar otro hasta poner lo pedido.*/
void elegir_dificultad(Juego *menu)
{
	printf("Elige la dificultad del juego con los números.\n Luego de elegir la dificultad no se podrá cambiar.\n");
	printf(" ________________________________________________________ \n");
	printf("|     1     FACIL: Tendrás 7 intentos                    |\n");
	printf("|     2    NORMAL: Tendrás 5 intentos                    |\n");
	printf("|     3   DIFÍCIL: Tendrás 3 intentos                    |\n");
	printf("|     4 IMPOSIBLE: Tendrás 2 intentos                    |\n");
	printf("|________________________________________________________|\n");
	printf("\n");
	printf("Elige un número entre el 1-4 para la dificultad: \n");

	int numero = -1;
	bool seguir = true;
	char *dificultades[] = { "FÁCIL", "NORMAL", "DIFÍCIL", "IMPOSIBLE" };
	while (seguir) {
		numero = obtener_tecla_numero();
		numero -= 1;
		if (numero >= FACIL && numero <= IMPOSIBLE) {
			menu->dificultad = numero;
			printf("Dificultad: %s\n\n\n", dificultades[numero]);
			seguir = false;
		} else {
			printf(" _________________\n");
			printf("|Número no válido.|\n");
			printf("|_________________|\n");
		}
	}
}

/*Asigna los pokemones de los jugadores al azar usando un vector y el split.
Separo los pokemones y a partir de un número random, se le asigna un pokémon dentro
del vector con los pokemones.*/
void asignar_pokemon_al_azar(Juego *menu)
{
	char **vector = NULL;
	char *pokemones = tp_nombres_disponibles(menu->tp);
	vector = split(pokemones, ',');

	srand((unsigned)time(NULL));

	int numero_random_j1 = 0;
	int numero_random_j2 = 0;

	while (numero_random_j1 == numero_random_j2) {
		numero_random_j1 = (rand() % tp_cantidad_pokemon(menu->tp));
		numero_random_j2 = (rand() % tp_cantidad_pokemon(menu->tp));
	}

	tp_seleccionar_pokemon(menu->tp, JUGADOR_1, vector[numero_random_j1]);
	tp_seleccionar_pokemon(menu->tp, JUGADOR_2, vector[numero_random_j2]);

	menu->pokemon_j1 = tp_pokemon_seleccionado(menu->tp, JUGADOR_1);
	menu->pokemon_j2 = tp_pokemon_seleccionado(menu->tp, JUGADOR_2);

	for (int i = 0; i < tp_cantidad_pokemon(menu->tp); i++) {
		free(vector[i]);
	}
	free(vector);
	free(pokemones);
}

/*Al seleccionar la dificultad, se asigna los intentos.*/
void asignar_intentos(Juego *menu)
{
	switch (menu->dificultad) {
	case FACIL:
		menu->intentos = INTENTOS_FACIL;
		return;
	case NORMAL:
		menu->intentos = INTENTOS_NORMAL;
		return;
	case DIFICIL:
		menu->intentos = INTENTOS_DIFICIL;
		return;
	case IMPOSIBLE:
		menu->intentos = INTENTOS_IMPOSIBLE;
		return;
	default:
		return;
	}
}

int cantidad_de_obstaculos(Juego *menu)
{
	srand((unsigned)time(NULL));
	switch (menu->dificultad) {
	case FACIL:
		return (rand() % 8 + 3);
	case NORMAL:
		return (rand() % 10 + 3);
	case DIFICIL:
		return (rand() % 13 + 3);
	case IMPOSIBLE:
		return (rand() % 18 + 3);
	}
	return 0;
}

void iniciar_pista_jugador_dos(Juego *menu)
{
	int cantidad_obstaculos = cantidad_de_obstaculos(menu);
	srand((unsigned)time(0));
	for (int i = 0; i < cantidad_obstaculos; i++) {
		int obstaculos = rand() % 3;
		unsigned posicion = (unsigned int)(rand() % 31);
		menu->tamanio_pista_j2 = (int)tp_agregar_obstaculo(
			menu->tp, JUGADOR_2, obstaculos, posicion);
	}
}

Juego *iniciar_juego(TP *tp)
{
	Juego *menu = calloc(1, sizeof(Juego));
	if (!menu) {
		free(menu);
		return NULL;
	}
	menu->partida = true;
	menu->carrera_iniciada = false;
	menu->tp = tp;
	imprimir_logo();
	elegir_dificultad(menu);
	asignar_pokemon_al_azar(menu);
	asignar_intentos(menu);
	iniciar_pista_jugador_dos(menu);
	return menu;
}

/*Termina la partida del juego. Cambiar la partida en false y deja
de ejecutarse los comandos. También cuando el jugador ya no puede
reintentar las partidas.*/
void salir(Juego *menu)
{
	if (!menu) {
		return;
	}
	menu->partida = false;
	printf("     GGGGGGGGGG   AA        MMMM     MMMM       EEEEEEEEE   \n");
	printf("    GG          AAAAAA      MM  MM MM  MM      EE           \n");
	printf("   GG   GGGGG  AA    AA     MM     M   MM     EEEEEEE       \n");
	printf("  GG      GG  AAAAAAAAAA    MM         MM    EE             \n");
	printf(" GG      GG  AA        AA   MM         MM   EE              \n");
	printf("GGGGGGGGGG  AA          AA  MM         MM  EEEEEEEEE        \n");
	printf("     OOOOOOOOOO  VV         VV  EEEEEEEEE  RRRRRRRR         \n");
	printf("    OO      OO    VV       VV  EE         RR      RR        \n");
	printf("   OO      OO      VV     VV  EEEEEEE    RR      RR         \n");
	printf("  OO      OO        VV   VV  EE         RRRRRRRRR           \n");
	printf(" OO      OO          VV VV  EE         RR       RR          \n");
	printf("OOOOOOOOOO            VVV  EEEEEEEEE  RR         RR         \n");
	printf("                   (GAME OVER)\n");
}

//---------------Seleccionar Pokemon---------------//

/*Selecciona al pokémon por el jugador. 
Si la carrera inició, se mostrará un mensaje de que no puede cambiar el pokémon.
Muestra los pokemones disponibles y a partir de ahí el usuario puede elegir al escribir
su nombre completo.
Si el pokémon del jugador contrario es el mismo, no se le asignará.
En caso de ser asignado, busco sus datos y los guardo en la estructura.*/
void Seleccionar_Pokemon(Juego *menu)
{
	if (!menu) {
		return;
	}
	if (menu->carrera_iniciada == true) {
		printf(" __________________________________________________\n");
		printf("|      No es posible seleccionar un pokémon.       |\n");
		printf("| Al comenzar la carrera, ya no es posible cambiar |\n");
		printf("|                  de pokémon.                     |\n");
		printf("|__________________________________________________|\n");
		return;
	}
	char *nombres_disponibles = tp_nombres_disponibles(menu->tp);
	printf("Nombres Disponibles: %s\n\n", nombres_disponibles);
	free(nombres_disponibles);
	printf("Escribe el nombre completo del pokémon.\n");
	printf("Escribe un Pokemon para elegir.\nPokemon a seleccionar: ");
	char *string = obtener_caracteres();
	bool asignado = tp_seleccionar_pokemon(menu->tp, JUGADOR_1, string);
	if (asignado == false) {
		printf("No se pudo realizar la selección.\n");
		return;
	}
	menu->pokemon_j1 = tp_buscar_pokemon(menu->tp, string);
	printf("Se asigno al Pokemon %s\n", menu->pokemon_j1->nombre);
	printf("\n");
}

//---------------Agregar pista---------------//

void mostrar_ayuda_agregar_obstaculos()
{
	printf("Ingresa primero el obstaculo:\n'F': Fuerza. 'D': Destreza. 'I': Inteligencia\n'?': Mostrar ayuda.\n'S': Salir de agregar el obstaculo.\n");
}

/*Lee la linea para asignar un identificador para agregarlo en la lista.
También recibe otros comando para Salir y pedir ayuda.*/
int ejecutar_accion_agregar_obstaculo(char linea)
{
	switch (linea) {
	case IDENTIFICADOR_OBSTACULO_FUERZA:
		return OBSTACULO_FUERZA;
	case IDENTIFICADOR_OBSTACULO_DESTREZA:
		return OBSTACULO_DESTREZA;
	case IDENTIFICADOR_OBSTACULO_INTELIGENCIA:
		return OBSTACULO_INTELIGENCIA;
	case 'S':
		return -2;
	case 's':
		return -2;
	case '?':
		return -3;
	default:
		return -1;
	}
}

/*Agrega un obstáculo cuando a partir de lo que ingrese el jugador.
Si recibe los atributos por el usuario, se pedirá la posición y luego
agregará dicho obstáculo a la lista. Muestra la pista y pide otra
En caso de que la pista sea una S o s, sale del agregar obstáculo.*/
void agregar_obstaculo(Juego *menu)
{
	mostrar_ayuda_agregar_obstaculos();
	bool seguir = true;
	while (seguir) {
		printf("Ingrese el atributo: ");
		char linea = obtener_tecla();
		printf("\n");
		int atributo = ejecutar_accion_agregar_obstaculo(linea);
		if (atributo == -1) {
			printf("Atributo no valida\n");
		} else if (atributo == -2) {
			seguir = false;
			return;
		} else if (atributo == -3) {
			mostrar_ayuda_agregar_obstaculos();
		} else {
			printf("Ingrese la posicion (Inicia en 0): ");
			int posicion = obtener_tecla_numero();
			printf("\n");

			if (atributo >= 0 && atributo <= 2 && posicion >= 0) {
				unsigned cantidad = tp_agregar_obstaculo(
					menu->tp, JUGADOR_1, atributo,
					(unsigned)posicion);
				menu->tamanio_pista_j1 = (int)cantidad;
				char *pista_j1 = tp_obstaculos_pista(menu->tp,
								     JUGADOR_1);
				printf("Pista: %s\n\n", pista_j1);
				free(pista_j1);

			} else {
				printf("Vuelve a ingresar una posicion valida.\n");
			}
		}
	}
}

//---------------Quitar obstaculo---------------//
void mostrar_ayuda_quitar_obstaculos()
{
	printf("Ingresa la posición del obstaculo que quieres quitar.\n'-1': Salir de quitar el obstaculo.\n");
}
/*Si todavía no hay obstáculos, devuelve un mensaje y vuelve a la pantalla del
menú principal.
Si el usuario ingresa una posición, este la quitará de la lista y mostrará
el resultado de como quedo la lista.
Si la posición es -1, sale de esta ejecución.
Si la pista quedo vacía devuelvo un mensaje que ya no quedaron obstáculos.*/
void quitar_obstaculo(Juego *menu)
{
	if (menu->tamanio_pista_j1 == 0) {
		printf("Aún no se han creado los obstaculos.\n");
		return;
	}

	mostrar_ayuda_quitar_obstaculos();
	bool seguir = true;
	while (seguir) {
		if (menu->tamanio_pista_j1 == 0) {
			seguir = false;
			printf("Ya no hay obstaculos en la pista.\n\n");
			return;
		}

		char *pista_jugador = tp_obstaculos_pista(menu->tp, JUGADOR_1);
		printf("Pista: %s\n\n", pista_jugador);
		free(pista_jugador);

		printf("Ingrese la posicion (Inicia en 0): ");
		int posicion = obtener_tecla_numero();
		printf("\n");

		if (posicion >= 0) {
			unsigned cantidad = tp_quitar_obstaculo(
				menu->tp, JUGADOR_1, (unsigned)posicion);
			menu->tamanio_pista_j1 = (int)cantidad;
			printf("Cantidad de obstaculos: %i\n", cantidad);
		} else if (posicion == -1) {
			seguir = false;
		} else {
			printf("Posición no valida.\n");
		}
	}
}

//---------------Mostrar---------------//

/*Muestra las estadísticas del pokémon seleccionadom la pista y su tiempo.*/
void mostrar_pokemon_y_pista(Juego *menu)
{
	char *pista_jugador = tp_obstaculos_pista(menu->tp, JUGADOR_1);
	char *tiempo_pista_jugador =
		tp_tiempo_por_obstaculo(menu->tp, JUGADOR_1);
	printf("Pokemon:      %s\n", menu->pokemon_j1->nombre);
	printf("Fuerza:       %i\n", menu->pokemon_j1->fuerza);
	printf("Destreza:     %i\n", menu->pokemon_j1->destreza);
	printf("Inteligencia: %i\n", menu->pokemon_j1->inteligencia);
	if (pista_jugador == NULL) {
		printf("Pista: No hay obstaculos en la pista.\n");
	} else {
		printf("Pista: %s\n", pista_jugador);
		printf("Tiempo por obstaculo: %s\n", tiempo_pista_jugador);
	}
	printf("\n");
	free(pista_jugador);
	free(tiempo_pista_jugador);
}

//---------------Carrera---------------//
/*Calcula el puntaje del jugador una vez finalizada la carrera.*/
int calcular_puntaje(unsigned tiempo_uno, unsigned tiempo_dos)
{
	float constante = 100;
	float tiempo_a = (float)tiempo_uno;
	float tiempo_b = (float)tiempo_dos;

	float tiempo_a_b = tiempo_a - tiempo_b;
	if (tiempo_a_b < 0) {
		tiempo_a_b = -tiempo_a_b;
	}
	return (int)(constante -
		     constante * (tiempo_a_b / (tiempo_a + tiempo_b)));
}

/*Recibe la pista del jugador 2 y oculta su pista cada vez que 
se inicia la carrera. Este puede variar lo que esconde.*/
void ocultar_obstaculos_pista(char *pista_j2, Juego *menu)
{
	srand((unsigned)time(NULL));
	int numeros = cantidad_de_obstaculos(menu);
	for (int i = 0; i < strlen(pista_j2); i++) {
		int ocultar = rand() % 2;
		if (numeros == 0) {
			break;
		} else if (ocultar == 1) {
			pista_j2[i] = '?';
			numeros--;
		}
	}
}

/*Muestra las estadísticas de los pokemones de ambos jugadores, sus tiempos y pistas.
Carrera iniciada será true para que el jugador ya no pueda cambiar de pokémon pero si su pista
Ocultar pista, esconde alguno de sus obstáculos.*/
void mostrar_pokemon_elegido(Juego *menu)
{
	menu->carrera_iniciada = true;
	char *pista_j1 = tp_obstaculos_pista(menu->tp, JUGADOR_1);
	char *pista_j2 = tp_obstaculos_pista(menu->tp, JUGADOR_2);
	ocultar_obstaculos_pista(pista_j2, menu);
	printf("________________________________________________________ \n");
	printf("           JUGADOR 1                                   \n");
	printf("          Pokémon: %s                                   \n",
	       menu->pokemon_j1->nombre);
	printf("           Fuerza: %i                                   \n",
	       menu->pokemon_j1->fuerza);
	printf("         Destreza: %i                                   \n",
	       menu->pokemon_j1->destreza);
	printf("     Inteligencia: %i                                   \n",
	       menu->pokemon_j1->inteligencia);
	printf("  Tamaño de Pista: %i                                   \n",
	       menu->tamanio_pista_j1);
	printf("            Pista: %s\n", pista_j1);
	printf("__________________________V\n");
	printf("                             S__________________________\n");
	printf("                                 JUGADOR 2              \n");
	printf("                                Pokémon: %s             \n",
	       menu->pokemon_j2->nombre);
	printf("                                 Fuerza: %i             \n",
	       menu->pokemon_j2->fuerza);
	printf("                               Destreza: %i             \n",
	       menu->pokemon_j2->destreza);
	printf("                           Inteligencia: %i             \n",
	       menu->pokemon_j2->inteligencia);
	printf("                        Tamaño de Pista: %i             \n",
	       menu->tamanio_pista_j2);
	printf("                                  Pista: %s\n", pista_j2);
	printf("________________________________________________________\n");
	free(pista_j1);
	free(pista_j2);
}

/*Recibe el menu el resultado del jugador 1 y el tiempo de cada jugador.
Ganador es para que imprima el jugador que ganó por pantalla, si el tiempo del jugador 2 es 
menor al del jugador 1, aumenta el ganador a uno para que imprima al jugador 2.
Si los intentos son distintos a 0, puede volver a reintentar la partida si el jugador quiere.
En caso de no querer reintentar o no tener intentos, se termina el juego.*/
void carrera_terminada(Juego *menu, int resultado_j1, unsigned tiempo_j1,
		       unsigned tiempo_j2)
{
	int ganador = 1;
	if (tiempo_j2 < tiempo_j1) {
		ganador += 1;
	}
	printf("\n\n");
	printf("________________RESULTADOS_____________________\n");
	printf("Pokémon del Jugador 1: %s. Tiempo: %i          \n",
	       menu->pokemon_j1->nombre,
	       tp_calcular_tiempo_pista(menu->tp, JUGADOR_1));
	printf("Pokémon del Jugador 2: %s. Tiempo: %i          \n",
	       menu->pokemon_j2->nombre,
	       tp_calcular_tiempo_pista(menu->tp, JUGADOR_2));
	printf("Puntaje del jugador 1: %i                      \n",
	       resultado_j1);
	printf("_______________________________________________\n");
	if (tiempo_j1 == tiempo_j2) {
		printf("EMPATE                           \n");
	} else {
		printf("GANADOR: JUGADOR %i                            \n",
		       ganador);
	}
	printf("_______________________________________________\n");
	printf("\n\n");

	if (menu->intentos != 0) {
		bool seguir = true;
		while (seguir) {
			printf("¿Reintentar? 'S': Sí / 'N': No  (Intentos: %i)\n >> ",
			       menu->intentos);
			char reintentar = obtener_tecla();

			switch (reintentar) {
			case 'S':
				printf("¡¡¡Adelante!!!\n");
				seguir = false;
				break;
			case 'N':
				seguir = false;
				salir(menu);
				break;
			default:
				printf(" __________________\n");
				printf("|Comando no válido.|\n");
				printf("|__________________|\n\n");
			}
		}
	}
}

/*Recibe el menú. En caso de que el jugador tenga una pista menor a 3 no se iniciará la carrera y saltará un mensaje.
Muestra las estadísticas de los pokemones. Luego comparo ambos tiempos y si el jugador 2 tiene menos tiempo que el jugador 1,
los intentos disminuirán. Luego mostrará los resultados, si no tengo más intentos se terminará el juego.*/
void comenzar_carrera(Juego *menu)
{
	if (menu->tamanio_pista_j1 < 3) {
		printf(" _________________________________________________\n");
		printf("|      No es posible comenzar la carrera.         |\n");
		printf("|No tienes los suficientes obstaculos para correr.|\n");
		printf("|*Se necesitan al menos 3 obstaculos para iniciar*|\n");
		printf("|_________________________________________________|\n");
		return;
	}
	mostrar_pokemon_elegido(menu);
	unsigned int tiempo_j1 = tp_calcular_tiempo_pista(menu->tp, JUGADOR_1);
	unsigned int tiempo_j2 = tp_calcular_tiempo_pista(menu->tp, JUGADOR_2);
	if (tiempo_j2 < tiempo_j1) {
		menu->intentos--;
	}
	int resultado_j1 = (int)calcular_puntaje(tiempo_j1, tiempo_j2);

	carrera_terminada(menu, resultado_j1, tiempo_j1, tiempo_j2);

	if (menu->intentos == 0) {
		salir(menu);
	}

	return;
}

/*Recibe el menú y la línea que escribió el jugador. Si cumple alguna de estas
se realizará dicha acción.*/
void ejecutar_accion(Juego *menu, char linea)
{
	if (!menu) {
		return;
	}
	switch (linea) {
	case '?':
		mostrar_ayuda_opciones_menu();
		break;
	case 'P':
		printf("Agregar obstaculos a la pista.\n");
		agregar_obstaculo(menu);
		break;
	case 'M':
		mostrar_pokemon_y_pista(menu);
		break;
	case 'C':
		printf("Comenzar carrera obstaculos.\n");
		comenzar_carrera(menu);
		break;
	case 'S':
		printf("Selección de pokemon.\n");
		Seleccionar_Pokemon(menu);
		break;
	case 'R':
		quitar_obstaculo(menu);
		break;
	case 'L':
		tp_limpiar_pista(menu->tp, JUGADOR_1);
		menu->tamanio_pista_j1 = 0;
		break;
	case 'Q':
		salir(menu);
		break;
	default:
		printf(" __________________\n");
		printf("|Comando no válido.|\n");
		printf("|__________________|\n\n");
		break;
	}
}

void menu_ejecutar(Juego *menu)
{
	if (!menu) {
		return;
	}
	char buffer[512];
	buffer[0] = 0;
	mostrar_ayuda_opciones_menu();

	while (menu->partida == true) {
		printf("Ingrese un comando. '?' Mostrar ayuda.\nComando: ");
		char linea = obtener_tecla(buffer, 512);
		printf("\n");
		ejecutar_accion(menu, linea);
	}
	printf("\n");
}

void destruir_menu(Juego *menu)
{
	if (!menu) {
		return;
	}
	free(menu);
}