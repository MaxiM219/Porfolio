#include <string.h>
#include <stdlib.h>
#include "hash.h"

#define FACTOR_CARGA_MAXIMA 0.7
#define REDIMENSION 2
#define CAPACIDAD_DEFAULT 3

//Estados de la tabla. Vacio si no tiene nada. Ocupado, si hay algún elemento. Borrado si el elemento fue quitado.
enum ESTADOS { VACIO, OCUPADO, BORRADO };

typedef struct celda {
	char *clave;
	void *valor;
	int estado;
} celda_t;

struct hash {
	celda_t *tabla;
	size_t capacidad;
	size_t cantidad;
	size_t borrados;
};

hash_t *hash_crear(size_t capacidad)
{
	hash_t *hash = calloc(1, sizeof(hash_t));
	if (!hash) {
		free(hash);
		return NULL;
	}
	hash->capacidad = capacidad;
	if (capacidad < CAPACIDAD_DEFAULT) {
		hash->capacidad = CAPACIDAD_DEFAULT;
	}
	hash->tabla = calloc(1, sizeof(celda_t) * hash->capacidad);
	if (!hash->tabla) {
		free(hash->tabla);
		free(hash);
		return NULL;
	}
	return hash;
}

/*PRE y POST: Recibo la clave y devuelve la copia de la misma clave o NULL si no pudo.
La función pide memoria y para crear una copia de la clave uso strcpy. 
*/
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
	return clave_copia;
}

//-------------Función de Hash-------------//

//Referencia: https://www.programmingalgorithms.com/algorithm/sdbm-hash/c/#google_vignette
unsigned int SDBMHash(char *str, unsigned int length)
{
	unsigned int hash = 0;
	unsigned int i = 0;

	for (i = 0; i < length; str++, i++) {
		hash = (unsigned int)(*str) + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

/*PRE y POST: Recibo la clave y la capacidad y devuelve la posición.
La función obtiene el largo de la clave y luego con la función de hash me da la posición en
donde se va a almacenar o buscar.
*/
size_t obtener_posicion(const char *clave, size_t capacidad)
{
	unsigned int largo = (unsigned int)strlen(clave);
	size_t posicion = SDBMHash((char *)clave, largo) % capacidad;
	return posicion;
}

//-------------Función de Redimensión-------------//
/*PRE y POST: Recibe el valor de la nueva capacidad y devuelve un valor booleano.
La función va ver si la nueva capacidad que fue recibida es un numero primo, si es falso,
la función de siguiente primo me mandará el siguiente numero.
Si es verdadera, la función de siguiente_primo habrá encontrado la nueva capacidad que es un numero primo. */
bool es_primo(size_t nueva_capacidad)
{
	for (size_t i = 2; i < nueva_capacidad; i++) {
		if (nueva_capacidad % i == 0) {
			return false;
		}
	}
	return true;
}

/*PRE y POST: Recibe la capacidad que fue multiplicada por su redimensión y devuelve una nueva capacidad que va a ser un número primo.
La función va a iterar hasta que encuentre un numero primo dada por otra función, mientras no lo sea, aumenta la capacidad +1.*/
size_t siguiente_primo(size_t capacidad)
{
	while (!es_primo(capacidad)) {
		capacidad++;
	}
	return capacidad;
}

/*PRE y POST: Recibo el hash.
La función lo que hará es agrandar la tabla de hash. Pido una nueva capacidad que será un número primo.
También pido un nuevo hash con la nueva capacidad.
Itero la tabla original e inserto el par clave, valor en el nuevo hash y libero las claves.
Libero la tabla original y luego le asigno los cambios del nuevo hash al hash original, para terminar libero el nuevo hash.
*/
void redimensionar(hash_t *hash)
{
	if (!hash) {
		return;
	}
	size_t nueva_capacidad = siguiente_primo(hash->capacidad * REDIMENSION);
	hash_t *nuevo_hash = hash_crear(nueva_capacidad);

	for (size_t i = 0; i < hash->capacidad; i++) {
		if (hash->tabla[i].estado == OCUPADO) {
			void *anterior = NULL;
			hash_insertar(nuevo_hash, hash->tabla[i].clave,
				      hash->tabla[i].valor, &anterior);
			free(hash->tabla[i].clave);
			free(anterior);
		}
	}

	free(hash->tabla);
	hash->tabla = nuevo_hash->tabla;
	hash->capacidad = nueva_capacidad;
	hash->cantidad = nuevo_hash->cantidad;
	hash->borrados = 0;
	free(nuevo_hash);
}

/*PRE y POST: recibo el hash y devuelve el resultado del factor de carga.
La función calcula el factor de carga cuando la tabla de hash está casi llena o llena.*/
float calcular_factor_carga(hash_t *hash)
{
	float resultado = ((float)hash->borrados + (float)hash->cantidad) /
			  (float)hash->capacidad;
	return resultado;
}
//---------------------------------------//

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (!hash || !clave) {
		return NULL;
	}

	size_t posicion = obtener_posicion(clave, hash->capacidad);

	while (hash->tabla[posicion].estado != VACIO) {
		if (hash->tabla[posicion].estado == OCUPADO &&
		    strcmp(hash->tabla[posicion].clave, clave) == 0) {
			if (anterior) {
				*anterior = hash->tabla[posicion].valor;
			}
			hash->tabla[posicion].valor = elemento;
			return hash;
		}
		posicion = (posicion + 1) % hash->capacidad;
	}

	if (hash->tabla[posicion].estado == VACIO) {
		hash->cantidad++;
	}

	hash->tabla[posicion].clave = copiar_clave(clave);
	hash->tabla[posicion].valor = elemento;
	hash->tabla[posicion].estado = OCUPADO;
	if (anterior != NULL) {
		*anterior = NULL;
	}

	if ((float)calcular_factor_carga(hash) >= FACTOR_CARGA_MAXIMA) {
		redimensionar(hash);
	}

	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if (!hash || !clave) {
		return NULL;
	}
	size_t posicion = obtener_posicion(clave, hash->capacidad);

	while (hash->tabla[posicion].estado != VACIO) {
		if (hash->tabla[posicion].estado == OCUPADO &&
		    strcmp(hash->tabla[posicion].clave, clave) == 0) {
			void *elemento = hash->tabla[posicion].valor;
			hash->tabla[posicion].valor = NULL;
			hash->tabla[posicion].estado = BORRADO;
			hash->cantidad--;
			free(hash->tabla[posicion].clave);
			return elemento;
		}
		posicion = (posicion + 1) % hash->capacidad;
	}

	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if (!hash || !clave) {
		return NULL;
	}
	size_t posicion = obtener_posicion(clave, hash->capacidad);

	while (hash->tabla[posicion].estado != VACIO) {
		if (hash->tabla[posicion].estado == OCUPADO) {
			if (strcmp(hash->tabla[posicion].clave, clave) == 0) {
				return hash->tabla[posicion].valor;
			}
		}
		posicion = (posicion + 1) % hash->capacidad;
	}
	return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if (!hash || !clave) {
		return false;
	}

	size_t posicion = obtener_posicion(clave, hash->capacidad);

	while (hash->tabla[posicion].estado != VACIO) {
		if (hash->tabla[posicion].estado == OCUPADO) {
			if (strcmp(hash->tabla[posicion].clave, clave) == 0) {
				return true;
			}
		}
		posicion = (posicion + 1) % hash->capacidad;
	}
	return false;
}

size_t hash_cantidad(hash_t *hash)
{
	if (!hash) {
		return VACIO;
	}
	return hash->cantidad;
}

void hash_destruir(hash_t *hash)
{
	if (!hash) {
		return;
	}
	for (size_t i = 0; i < hash->capacidad; i++) {
		if (hash->tabla[i].estado == OCUPADO) {
			free(hash->tabla[i].clave);
		}
	}
	free(hash->tabla);
	free(hash);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash || !destructor) {
		hash_destruir(hash);
		return;
	}

	for (size_t i = 0; i < hash->capacidad; i++) {
		if (hash->tabla[i].estado == OCUPADO) {
			destructor(hash->tabla[i].valor);
		}
	}
	hash_destruir(hash);
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	if (!hash || !f) {
		return VACIO;
	}

	size_t posicion = 0;
	size_t cantidad = 0;
	bool seguir = true;
	while (seguir && posicion < hash->capacidad) {
		if (hash->tabla[posicion].estado == OCUPADO) {
			seguir = f(hash->tabla[posicion].clave,
				   hash->tabla[posicion].valor, aux);
			cantidad++;
		}
		posicion++;
	}
	return cantidad;
}
