#include "tp.h"
#include "lista.h"
#include "abb.h"
#include "split.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

#define MODO_LECTURA "r"
#define IDENTIFICADOR_OBSTACULO_NULO 'N'
#define VACIO 0
#define MAX_LINEA 200

struct tp {
	int cantidad_pokemon;
	abb_t *abb;
	lista_t *obstaculos_j1;
	lista_t *obstaculos_j2;
	struct pokemon_info *pokemon_j1;
	struct pokemon_info *pokemon_j2;
};

typedef struct {
	int obstaculo;
	char identificador;
	int tiempo;
} datos_obstaculo;

typedef struct {
	char *nombres_disponibles;
	int cantidad;
	int actual;
	struct pokemon_info *pokemon_j1;
	struct pokemon_info *pokemon_j2;
} datos;

int comparar_string(void *nomb1, void *nomb2)
{
	struct pokemon_info *poke_1 = nomb1;
	struct pokemon_info *poke_2 = nomb2;
	return (strcmp(poke_1->nombre, poke_2->nombre));
}

/*Ajusta el nombre del pokémon antes de ser guardado.
Por ejemplo: Si tengo piKaCHU, este va a cambiarlo por Pikachu.
*/
void ajustar_nombre(char *nombre)
{
	for (int i = 0; i != strlen(nombre); i++) {
		nombre[i] = (char)tolower(nombre[i]);
	}
	nombre[0] = (char)toupper(nombre[0]);
}

/*Copia el nombre del pokemon para que sea guardado.*/
char *copiar_clave(const char *clave)
{
	if (!clave) {
		return NULL;
	}
	char *clave_copia = malloc(strlen(clave) + 1);
	if (!clave_copia) {
		free(clave_copia);
		return NULL;
	}
	strcpy(clave_copia, clave);
	ajustar_nombre(clave_copia);
	return clave_copia;
}

/*Destruye la información del pokémon.
Sirve para destruir el tp.*/
void destruir_info(void *estructura)
{
	struct pokemon_info *pokemon = estructura;
	free(pokemon->nombre);
	free(pokemon);
}

/*Creo la información del pokémon a partir del nombre y de los atributos obtenidos del archivo.*/
struct pokemon_info *crear_pokemon_info(const char *nombre, int fuerza,
					int destreza, int inteligencia)
{
	struct pokemon_info *pokemon = calloc(1, sizeof(struct pokemon_info));
	if (!pokemon) {
		free(pokemon);
		return NULL;
	}
	pokemon->nombre = copiar_clave(nombre);
	pokemon->fuerza = fuerza;
	pokemon->destreza = destreza;
	pokemon->inteligencia = inteligencia;
	return pokemon;
}

/*Obtengo el largo del vector. Para verificar que tengo lo justo para iniciar el tp.*/
size_t obtener_largo(char **vector)
{
	size_t largo = 0;
	while (vector[largo] != NULL) {
		largo++;
	}

	return largo;
}

/*Recibo el archivo y el tp.
Si el archivo es el incorrecto devuelvo false.
Leo las linea del archivo y voy a seperar su nombre y sus atributos para luego crear la estructura del pokémon
y guardarlo en el abb. Libero los datos del vector y al vector con cada pokémon dado. 
Cierro el archivo cuando ya finalizo todo y devuelvo true para decir que cargo todo con éxito.*/
bool crear_abb_pokemon(TP *tp, const char *nombre_archivo)
{
	FILE *archivo = fopen(nombre_archivo, MODO_LECTURA);
	if (!archivo) {
		return false;
	}
	char leido[MAX_LINEA];
	char *linea_leida = fgets(leido, MAX_LINEA, archivo);
	tp->abb = abb_crear(comparar_string);
	if (!tp->abb) {
		free(tp->abb);
		fclose(archivo);
		return false;
	}

	struct pokemon_info *pokemon_actual;
	size_t i = 0;

	char **vector = NULL;
	while (linea_leida) {
		vector = split(leido, ',');
		size_t largo = obtener_largo(vector);

		if (largo <= 3) {
			for (size_t i = 0; i < largo; i++) {
				free(vector[i]);
			}
			free(vector);
			fclose(archivo);
			return false;
		}

		pokemon_actual = crear_pokemon_info(vector[0], atoi(vector[1]),
						    atoi(vector[2]),
						    atoi(vector[3]));

		abb_insertar(tp->abb, pokemon_actual);

		linea_leida = fgets(leido, MAX_LINEA, archivo);
		i++;
		free(vector[0]);
		free(vector[1]);
		free(vector[2]);
		free(vector[3]);
		free(vector);
	}
	fclose(archivo);
	return true;
}

TP *tp_crear(const char *nombre_archivo)
{
	TP *tp = calloc(1, sizeof(TP));
	if (tp == NULL || !nombre_archivo) {
		free(tp);
		return NULL;
	}
	bool creado = crear_abb_pokemon(tp, nombre_archivo);
	if (creado == false) {
		abb_destruir_todo(tp->abb, destruir_info);
		free(tp);
		return NULL;
	}

	tp->cantidad_pokemon = (int)abb_tamanio(tp->abb);
	tp->obstaculos_j1 = lista_crear();
	tp->obstaculos_j2 = lista_crear();
	return tp;
}

int tp_cantidad_pokemon(TP *tp)
{
	if (!tp) {
		return VACIO;
	}
	return tp->cantidad_pokemon;
}

const struct pokemon_info *tp_buscar_pokemon(TP *tp, const char *nombre)
{
	if (!tp || nombre == NULL) {
		return NULL;
	}

	struct pokemon_info *pokemon_buscado =
		crear_pokemon_info(nombre, 0, 0, 0);
	const struct pokemon_info *pokemon_encontrado =
		abb_buscar(tp->abb, pokemon_buscado);

	free(pokemon_buscado->nombre);
	free(pokemon_buscado);
	if (!pokemon_encontrado || !pokemon_buscado) {
		return NULL;
	}
	return pokemon_encontrado;
}

/*Agrego los nombres a partir de una función booleana para el abb que recorre todos los pokemones.
Recibe el elemento que es la estructura del pokémon y un aux que es una estructura de datos que tiene
el string que voy a devolver.*/
bool agregar_listado(void *elemento, void *aux)
{
	struct pokemon_info *pokemon = elemento;
	datos *datos = aux;
	if (datos->pokemon_j1 != NULL && datos->pokemon_j2 != NULL) {
		if (datos->pokemon_j1 == pokemon ||
		    datos->pokemon_j2 == pokemon) {
			return true;
		}
	}
	const char *nombre = pokemon->nombre;
	const char *separador = ",";
	datos->nombres_disponibles =
		realloc(datos->nombres_disponibles,
			sizeof(char) * (strlen(datos->nombres_disponibles) +
					strlen(nombre)) +
				2);
	strcat(datos->nombres_disponibles, nombre);
	datos->actual++;
	if (datos->actual < datos->cantidad) {
		strcat(datos->nombres_disponibles, separador);
	}
	return true;
}

char *tp_nombres_disponibles(TP *tp)
{
	if (!tp) {
		return NULL;
	}
	datos datos;
	datos.nombres_disponibles = calloc(1, sizeof(char));
	datos.cantidad = tp->cantidad_pokemon;
	datos.actual = 0;
	datos.pokemon_j1 = tp->pokemon_j1;
	datos.pokemon_j2 = tp->pokemon_j2;

	abb_con_cada_elemento(tp->abb, INORDEN, agregar_listado, &datos);

	return datos.nombres_disponibles;
}

bool tp_seleccionar_pokemon(TP *tp, enum TP_JUGADOR jugador, const char *nombre)
{
	if (!tp) {
		return false;
	}

	struct pokemon_info *pokemon_buscado =
		crear_pokemon_info(nombre, 0, 0, 0);
	if (!pokemon_buscado) {
		free(pokemon_buscado->nombre);
		free(pokemon_buscado);
		return false;
	}
	struct pokemon_info *pokemon = abb_buscar(tp->abb, pokemon_buscado);
	free(pokemon_buscado->nombre);
	free(pokemon_buscado);

	if (jugador == JUGADOR_1) {
		if (!pokemon || pokemon == tp->pokemon_j2) {
			return false;
		}
		tp->pokemon_j1 = pokemon;
	} else if (jugador == JUGADOR_2) {
		if (!pokemon || pokemon == tp->pokemon_j1) {
			return false;
		}
		tp->pokemon_j2 = pokemon;
	}
	return true;
}

const struct pokemon_info *tp_pokemon_seleccionado(TP *tp,
						   enum TP_JUGADOR jugador)
{
	if (!tp) {
		return NULL;
	}
	if (jugador == JUGADOR_1 && tp->pokemon_j1 != NULL) {
		return tp->pokemon_j1;
	} else if (jugador == JUGADOR_2 && tp->pokemon_j2 != NULL) {
		return tp->pokemon_j2;
	}
	return NULL;
}

/*Creo la estructura de obstaculos recibida por los parametros dados.
Esto lo guardo en la lista. Contiene el enum del obstaculo, el identificador
y el tiempo de dicho obstáculo que va a recorrer el pokémon.*/
datos_obstaculo *crear_obstaculo(enum TP_OBSTACULO obstaculo)
{
	datos_obstaculo *obstaculo_datos = calloc(1, sizeof(datos_obstaculo));
	if (!obstaculo_datos) {
		free(obstaculo_datos);
		return NULL;
	}
	obstaculo_datos->obstaculo = obstaculo;
	if (obstaculo == OBSTACULO_FUERZA) {
		obstaculo_datos->identificador = IDENTIFICADOR_OBSTACULO_FUERZA;
	} else if (obstaculo == OBSTACULO_DESTREZA) {
		obstaculo_datos->identificador =
			IDENTIFICADOR_OBSTACULO_DESTREZA;
	} else if (obstaculo == OBSTACULO_INTELIGENCIA) {
		obstaculo_datos->identificador =
			IDENTIFICADOR_OBSTACULO_INTELIGENCIA;
	}
	return obstaculo_datos;
}

unsigned tp_agregar_obstaculo(TP *tp, enum TP_JUGADOR jugador,
			      enum TP_OBSTACULO obstaculo, unsigned posicion)
{
	if (!tp || obstaculo > 2 || jugador > 2) {
		return VACIO;
	}

	datos_obstaculo *obstaculo_datos = crear_obstaculo(obstaculo);

	if (!obstaculo_datos) {
		free(obstaculo_datos);
		return VACIO;
	}

	if (jugador == JUGADOR_1) {
		lista_insertar_en_posicion(tp->obstaculos_j1, obstaculo_datos,
					   posicion);
		return (unsigned)lista_tamanio(tp->obstaculos_j1);
	} else if (jugador == JUGADOR_2) {
		lista_insertar_en_posicion(tp->obstaculos_j2, obstaculo_datos,
					   posicion);
		return (unsigned)lista_tamanio(tp->obstaculos_j2);
	}
	return VACIO;
}

unsigned tp_quitar_obstaculo(TP *tp, enum TP_JUGADOR jugador, unsigned posicion)
{
	if (!tp || jugador > 2) {
		return VACIO;
	}
	if (jugador == JUGADOR_1) {
		void *elemento =
			lista_quitar_de_posicion(tp->obstaculos_j1, posicion);
		free(elemento);
		return (unsigned)lista_tamanio(tp->obstaculos_j1);
	} else if (jugador == JUGADOR_2) {
		void *elemento =
			lista_quitar_de_posicion(tp->obstaculos_j2, posicion);
		free(elemento);
		return (unsigned)lista_tamanio(tp->obstaculos_j2);
	}
	return VACIO;
}

/*Dado la lista y el tamano de la pista de los obstáculos, voy a
devolver el string de la pista de obstáculos.
Mientra i sea menor al tamano de la lista hago lo siguiente. Uso el iterador externo para recorrer la lista. 
Luego asigno el obstáculo con la elemento actual del iterador para guardar el identificador al string.
Si i llego a ser el tamaño guardo el \0 para decir que termino el string.
Al final libero el iterador y devuelvo el string con los obstáculos.*/
char *obstaculos(lista_t *pista, size_t tamano)
{
	char *pista_elemento = malloc(sizeof(char) * (tamano) + 1);

	if (!pista_elemento) {
		free(pista_elemento);
		return NULL;
	}

	size_t posicion = 0;
	size_t i = 0;
	lista_iterador_t *it = NULL;
	it = lista_iterador_crear(pista);
	while (i < tamano) {
		datos_obstaculo *obstaculo = lista_iterador_elemento_actual(it);
		pista_elemento[posicion] = obstaculo->identificador;
		posicion++;
		i++;
		if (i == tamano) {
			pista_elemento[posicion] = '\0';
		}
		lista_iterador_tiene_siguiente(it);
		lista_iterador_avanzar(it);
	}
	lista_iterador_destruir(it);
	return pista_elemento;
}

char *tp_obstaculos_pista(TP *tp, enum TP_JUGADOR jugador)
{
	if (!tp || jugador > 2) {
		return NULL;
	}

	if (jugador == JUGADOR_1) {
		size_t tamano = lista_tamanio(tp->obstaculos_j1);
		if (tamano == 0) {
			return NULL;
		}
		return obstaculos(tp->obstaculos_j1, tamano);

	} else if (jugador == JUGADOR_2) {
		size_t tamano = lista_tamanio(tp->obstaculos_j2);
		if (tamano == 0) {
			return NULL;
		}
		return obstaculos(tp->obstaculos_j2, tamano);
	}

	return NULL;
}

/*Destruyo la lista del jugador pedido y vuelvo a crear la lista.*/
void tp_limpiar_pista(TP *tp, enum TP_JUGADOR jugador)
{
	if (!tp || jugador > 2) {
		return;
	}
	if (jugador == JUGADOR_1) {
		lista_destruir_todo(tp->obstaculos_j1, free);
		tp->obstaculos_j1 = lista_crear();
	} else if (jugador == JUGADOR_2) {
		lista_destruir_todo(tp->obstaculos_j2, free);
		tp->obstaculos_j2 = lista_crear();
	}
}

/*Calculo el tiempo del obstaculos con el tipo de obstáculo, el atributo, el anterior y el identificador del obstáculo anterior.
anterior vendría a ser el número que se va a aumentar si el identificador anterior es el mismo, se aumentar de a 1. 
Si el identificador es distinto, anterior vuelve a 0.
Devuelvo el tiempo de dicho obstáculo.*/
int calcular_tiempo(int tiempo_pista, char tipo_obstaculo, int atributo,
		    int *anterior, char *obstaculo_anterior)
{
	if (*obstaculo_anterior != tipo_obstaculo) {
		*anterior = 0;
	}
	tiempo_pista = 10 - *anterior - atributo;
	if (tiempo_pista < 0) {
		tiempo_pista = 0;
	}
	*anterior += 1;
	*obstaculo_anterior = tipo_obstaculo;

	return tiempo_pista;
}
/*Recibo la lista de obstáculos del jugador y su pokémon.
anterior viene a ser un contador de veces que se repitio el mismo identificador para hacer la cuenta.
Con el iterador externo recorro la lista de obstáculos y verifico los identificadores.
Calcula el tiempo de dicho obstaculo en la función de calcular tiempo. 
Luego suma el total del tiempo por todos los obstáculos recorridos.*/
unsigned calcular_tiempo_total(lista_t *obstaculos_jugador,
			       struct pokemon_info *pokemon_jugador)
{
	lista_iterador_t *it = NULL;
	int anterior = 0;
	char obstaculo_anterior = IDENTIFICADOR_OBSTACULO_NULO;
	unsigned int total = 0;
	for (it = lista_iterador_crear(obstaculos_jugador);
	     lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it)) {
		datos_obstaculo *datos_pista =
			lista_iterador_elemento_actual(it);
		if (datos_pista->identificador ==
		    IDENTIFICADOR_OBSTACULO_FUERZA) {
			datos_pista->tiempo = calcular_tiempo(
				datos_pista->tiempo, datos_pista->identificador,
				pokemon_jugador->fuerza, &anterior,
				&obstaculo_anterior);
			total += (unsigned)datos_pista->tiempo;
		} else if (datos_pista->identificador ==
			   IDENTIFICADOR_OBSTACULO_DESTREZA) {
			datos_pista->tiempo = calcular_tiempo(
				datos_pista->tiempo, datos_pista->identificador,
				pokemon_jugador->destreza, &anterior,
				&obstaculo_anterior);
			total += (unsigned)datos_pista->tiempo;
		} else if (datos_pista->identificador ==
			   IDENTIFICADOR_OBSTACULO_INTELIGENCIA) {
			datos_pista->tiempo = calcular_tiempo(
				datos_pista->tiempo, datos_pista->identificador,
				pokemon_jugador->inteligencia, &anterior,
				&obstaculo_anterior);
			total += (unsigned)datos_pista->tiempo;
		}
	}

	lista_iterador_destruir(it);
	return total;
}

unsigned tp_calcular_tiempo_pista(TP *tp, enum TP_JUGADOR jugador)
{
	if (!tp) {
		return VACIO;
	}

	if (jugador == JUGADOR_1) {
		if (!tp->obstaculos_j1 ||
		    lista_tamanio(tp->obstaculos_j1) == 0 || !tp->pokemon_j1) {
			return VACIO;
		}
		return calcular_tiempo_total(tp->obstaculos_j1, tp->pokemon_j1);
	}
	if (jugador == JUGADOR_2) {
		if (!tp->obstaculos_j2 ||
		    lista_tamanio(tp->obstaculos_j2) == 0 || !tp->pokemon_j2) {
			return VACIO;
		}
		return calcular_tiempo_total(tp->obstaculos_j2, tp->pokemon_j2);
	}
	return VACIO;
}

/*Dado la lista y el tamano de la pista de los obstáculos, voy a
devolver el string del tiempo de la pista de obstáculos.
Mientra i sea menor al tamano de la lista hago lo siguiente. Uso el iterador externo para recorrer la lista. 
Luego asigno el obstáculo con la elemento actual del iterador para guardar el identificador al string.
Si i llego a ser el tamaño guardo el \0 para decir que termino el string,
sino agrego la ',' para separar los números.
Al final libero el iterador y devuelvo el string con el tiempo de los obstáculos.*/

char *obstaculos_tiempo(lista_t *pista, size_t tamano)
{
	char *pista_elemento = malloc(sizeof(char) * (tamano * 3));

	if (!pista_elemento) {
		free(pista_elemento);
		return NULL;
	}

	size_t posicion = 0;
	size_t i = 0;
	lista_iterador_t *it = NULL;
	it = lista_iterador_crear(pista);
	while (i < tamano) {
		datos_obstaculo *obstaculo = lista_iterador_elemento_actual(it);
		pista_elemento[posicion] = (char)obstaculo->tiempo + '0';
		posicion++;
		i++;
		if (i == tamano) {
			pista_elemento[posicion] = '\0';
		} else {
			pista_elemento[posicion] = ',';
			posicion++;
		}
		lista_iterador_tiene_siguiente(it);
		lista_iterador_avanzar(it);
	}
	lista_iterador_destruir(it);
	return pista_elemento;
}

char *tp_tiempo_por_obstaculo(TP *tp, enum TP_JUGADOR jugador)
{
	if (!tp || jugador > 2) {
		return NULL;
	}

	if (jugador == JUGADOR_1) {
		size_t tamano = lista_tamanio(tp->obstaculos_j1);
		if (tamano == 0 || tp->pokemon_j1 == NULL) {
			return NULL;
		}
		calcular_tiempo_total(tp->obstaculos_j1, tp->pokemon_j1);
		return obstaculos_tiempo(tp->obstaculos_j1, tamano);

	} else if (jugador == JUGADOR_2) {
		size_t tamano = lista_tamanio(tp->obstaculos_j2);
		if (tamano == 0 || tp->pokemon_j2 == NULL) {
			return NULL;
		}
		calcular_tiempo_total(tp->obstaculos_j2, tp->pokemon_j2);
		return obstaculos_tiempo(tp->obstaculos_j2, tamano);
	}

	return NULL;
}

void tp_destruir(TP *tp)
{
	if (!tp) {
		return;
	}

	abb_destruir_todo(tp->abb, destruir_info);
	lista_destruir_todo(tp->obstaculos_j1, free);
	lista_destruir_todo(tp->obstaculos_j2, free);
	free(tp);
}
