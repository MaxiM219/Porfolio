#include "src/tp.h"
#include "src/menu.h"
#include "src/split.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	//Se recomienda pasar el archivo de texto con los pokemon como argumento al ejecutar el programa
	TP *tp = tp_crear(argv[1]);

	if (!tp) {
		printf("No se pudo crear el tp.\n");
		return 0;
	}

	Juego *menu = iniciar_juego(tp);

	if (!menu) {
		printf("No se pudo iniciar el menu.\n");
		return 0;
	}
	menu_ejecutar(menu);

	destruir_menu(menu);

	tp_destruir(tp);

	return 0;
}
