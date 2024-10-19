#include "split.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split(const char *string, char separador)
{
	char **cadenas = NULL;

	if (string == NULL) {
		return cadenas;
	}

	int i = 0;
	int posicion = 0;
	int cantidad = 0;

	cadenas = malloc(1 * sizeof(char *));
	cadenas[cantidad] = calloc(1, sizeof(char));

	while (string[i] != 0) {
		if (string[i] == separador) {
			cantidad++;
			cadenas = realloc(cadenas, (size_t)(cantidad + 1) *
							   sizeof(char *));
			cadenas[cantidad] = calloc(1, sizeof(char));
			posicion = 0;
		} else {
			cadenas[cantidad][posicion] = string[i];
			cadenas[cantidad] =
				realloc(cadenas[cantidad],
					(size_t)(posicion + 2) * sizeof(char));
			posicion++;
			cadenas[cantidad][posicion] = '\0';
		}
		i++;
	}
	cantidad++;
	cadenas = realloc(cadenas, (size_t)(cantidad + 1) * sizeof(char *));
	cadenas[cantidad] = NULL;

	return cadenas;
}
