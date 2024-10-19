"""Luces fuera
Este juego fue realizado solo con la base del 2048 modificado y una implementación logica propia.

- iniciar_juego: Contiene los datos principales en una lista que sera guardada en la variable 'juego'.
- verificar_tamano_tablero: Antes de comenzar el juego, verifica que el tamaño del tablero sea el adecuado para jugar.
- mostrar_juego: Imprime por pantalla el tablero del juego.
- juego_ganado: Si se completaron los 5 niveles, se da que el juego esta terminado y ganado. 
    Al final devuelve los movimientos totales realizados.
- juego_perdido: Si se acaban los movimientos, el juego se da por perdido.
    Al final devuelve los movimientos totales realizados.
- pedir_movimiento: Pide el movimiento y la guarda en la variable movimiento.
- actualizar_tablero: Se realizan los movimientos y actualiza el tablero y los guarda como un nuevo_juego.
- actualizar_juego: Actualiza el juego, cambios de niveles, movimientos e intentos.
- nivel_ganado = Se fija que todas las filas de ese nivel esten vacias y muestra que has pasado de nivel.
"""

import luces_fuera

def main():
    juego = luces_fuera.iniciar_juego()
    if luces_fuera.verificar_tamano_tablero():
            print("El minimo tamano del tablero es 1 y el maximo tamano del tablero es 26")
            return
    while True:
        luces_fuera.mostrar_juego(juego)
        if luces_fuera.juego_ganado(juego):
            print(f"¡Felicidades! ¡Has completado los {luces_fuera.juego_cantidad_niveles()} niveles del juego!")
            print("Movimientos totales realizados :", luces_fuera.juego_cantidad_mov_totales(juego))
            return
        if luces_fuera.juego_perdido(juego):
            print("Si ves esto, es porque perdiste. Suerte para la próxima.")
            print("Movimientos totales realizados :", luces_fuera.juego_cantidad_mov_totales(juego))
            return
        movimiento = luces_fuera.pedir_movimiento(juego)
        nuevo_juego = luces_fuera.actualizar_tablero(juego, movimiento)
        #print(nuevo_juego)
        if luces_fuera.nivel_ganado(nuevo_juego):
            print(f"Nivel Superado. Sig. Nivel: {luces_fuera.juego_nivel_sig(juego)}")
        juego = luces_fuera.actualizar_juego(nuevo_juego)

main()