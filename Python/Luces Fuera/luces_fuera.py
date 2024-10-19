from string import ascii_uppercase

#constantes
TAMANO = 5
INTENTOS = 3 * TAMANO
#luces 0 apagado 1 prendido
APAGADO = 0
PRENDIDO = 1
#Constantes del juego
GRILLA = 0
MOV_TOTAL = 1
NIVEL_ACTUAL = 2
INTENTOS_ACTUAL = 3
POSICION_NIVEL = 4
#Niveles 
NIVEL_1 = ((1,1,0,1,1),(1,0,1,0,1),(0,1,1,1,0),(1,0,1,0,1),(1,1,0,1,1))

NIVEL_2 = ((0,1,0,1,0),(1,1,0,1,1),(0,1,0,1,0),(1,0,1,0,1),(1,0,1,0,1))

NIVEL_3 = ((1,0,0,0,1),(1,1,0,1,1),(0,0,1,0,0),(1,0,1,0,0),(1,0,1,1,0))

NIVEL_4 = ((1,1,0,1,1),(0,0,0,0,0),(1,1,0,1,1),(0,0,0,0,1),(1,1,0,0,0))

NIVEL_5 = ((0,0,0,1,1),(0,0,0,1,1),(0,0,0,0,0),(1,1,0,0,0),(1,1,0,0,0))

#Niveles guardados. Una vez terminado uno, pasa al siguiente.
NIVELES = (NIVEL_1, NIVEL_2, NIVEL_3, NIVEL_4, NIVEL_5)

def verificar_tamano_tablero():
    """Verifica el tamano del juego, si el tamaño del juego no esta entre lo acordado
    devuelve True y no se realiza el juego."""   
    if TAMANO < 1 or TAMANO > 26:
        return True

def inicializar_nivel(n):
    """Recibe la posicion del nivel actual y lo convierte en una lista de listas."""
    return [[j for j in i] for i in NIVELES[n]]

def iniciar_juego():
    """Contiene los datos iniciales del juego y los devuelve en una lista con sus valores.
    tablero que inicia en el nivel 1, mov_total son los movimientos totales que empiezan en 0,
    el nivel del tablero y los intentos que son 3 por el tamano del tablero.
    *Ahora contiene la posicion del nivel que esta asociado a la posicion de la variable NIVELES."""
    mov_total = 0
    nivel_tablero = 0
    posicion_nivel = 0
    intentos = INTENTOS
    tablero = inicializar_nivel(posicion_nivel)
    return [tablero, mov_total, nivel_tablero, intentos, posicion_nivel]

def juego_ganado(juego):
    """En base al tablero y al ultimo nivel. Si todas las casillas estan vacias y es el ultimo
    nivel devuelve True y termina el juego como ganado."""
    tablero = juego[GRILLA]
    nivel_tablero = juego[NIVEL_ACTUAL]
    if esta_vacio(tablero) and nivel_tablero == len(NIVELES) - 1:
        return True

def nivel_ganado(nuevo_juego):
    """Si se apagaron las luces en dicho nivel (y que no sea el ultimo) devuelve True"""
    tablero = nuevo_juego[GRILLA]
    nivel_tablero = nuevo_juego[NIVEL_ACTUAL]
    if esta_vacio(tablero) and nivel_tablero != len(NIVELES) - 1:
        return True

def juego_perdido(juego):
    """Para que el juego se de por perdido la cantidad de intentos 
    debe ser 0. si los movimientos_restantes llegan a 0 se da por perdido."""
    movimientos_restantes = juego[INTENTOS_ACTUAL]
    if not movimientos_restantes:
        return True

def esta_vacio(grilla):
    """Recorre el tablero para verificar si todas las filas estan apagadas.
    Si no lo están, devuelve False y continua el juego, en lo contrario devuelve
    True."""
    tablero = grilla
    for fila in tablero:
        if not all(luz == APAGADO for luz in fila):
            return False
    return True

def juego_cantidad_mov_totales(juego):
    #Devuelve la cantidad de movimientos realizados
    return juego[MOV_TOTAL]

def juego_nivel_sig(juego):
    """Devuelve el siguiente nivel"""
    return juego[NIVEL_ACTUAL] + 2

def juego_cantidad_niveles():
    """Devuelve la cantidad de niveles"""
    return len(NIVELES)

def mostrar_juego(juego):
    """Imprime el tablero"""
    tablero = juego[GRILLA]
    letras = " ".join(list(ascii_uppercase[:TAMANO]))

    #Imprime las letras
    for _ in range(1):
        print(f"   {letras}")
    
    for i in range(TAMANO):
        if 0 <= i <= 8:
            #Agrega un espacio cuando el tamaño es menor a 8
            print(end=" ")
        print(f"{i + 1}", end= "|")
        for j in range(TAMANO):
            if tablero[i][j] == APAGADO:
                print("□", end= " ")
            if tablero[i][j] == PRENDIDO:
                print("o", end= " ")
        print()
    
def pasar_letra_a_numero(letra):
    #Pasa la letra ingresada a un numero segun su valor ascii.
    for numero in range(len(ascii_uppercase)):
        if ascii_uppercase[numero] == letra:
            return numero

def cadena_a_lista(movimiento):
    #Agarra la cadena que se ingreso y se separa la letra y el numero y lo devuelve como una lista
    letra = movimiento[:1]
    numero = int(movimiento[1:])
    return [letra, numero]

def pasar_a_posicion(movimiento):
    """Toma el movimiento dado por el usuario y los convierte en una posicion
        valida dentro del tablero."""
    movimiento_valido = cadena_a_lista(movimiento.upper())
    letra = pasar_letra_a_numero(movimiento_valido[0])
    numero = movimiento_valido[1] - 1
    movimiento_valido[0], movimiento_valido[1] = numero, letra
    return movimiento_valido

def cambiar_estado(valor):
    """Cambia el estado de las luces entre 0 y 1"""
    return PRENDIDO if valor == APAGADO else APAGADO

def validar_movimiento(movimiento):
    """Valida el movimiento ingresado.
    Se tienen que cumplir ciertos requisitos:
    - El largo del movimiento tiene que ser mayor o igual a 2.
    - La letra va a estar en mayuscula, así que solo verifica si esta dentro del rango de los caracteres ascii en mayuscula.
    - Luego verifica si lo ingresado despues de la letra es un numero y esta dentro del rango del tamano.
    Si cumple esto devuelve verdadero."""
    
    if len(movimiento) >= 2 and movimiento[:1].upper() in ascii_uppercase[:TAMANO] and movimiento[1:].isdigit() and 1 <= int(movimiento[1:]) <= TAMANO:
        return True
    return False

def pedir_movimiento(juego):
    """Pide el movimiento, toma la letra y el numero y los devuelve como una posicion del tablero, en caso de no estar dentro
    del tablero muestra el tablero sin ningun tipo de movimiento."""

    while True:
        movimiento = input("Ingrese su jugada: ")

        if validar_movimiento(movimiento):
            return movimiento
        mostrar_juego(juego)

def actualizar_tablero(juego, mov):
    """Uso juego y el movimiento."""
    tablero = juego[GRILLA]
    fila, columna = pasar_a_posicion(mov)

    #Cambia el estado del valor en esa posicion
    tablero[fila][columna] = cambiar_estado(tablero[fila][columna])

    """Cambia el estado de los valores en las posiciones de los alrededores (no las diagonales)
    este va entre solo -1 y 1. Si dicha fila o columna esta dentro del tablero este va a cambiar
    su estado entre prendido o apagado"""
    for i in range(-1, 2, 2):
        if fila + i in range(len(tablero)):
            tablero[fila + i][columna] = cambiar_estado(tablero[fila + i][columna])
        
        if columna + i in range(len(tablero)):
         tablero[fila][columna + i] = cambiar_estado(tablero[fila][columna + i])

    #Devuelvo todo en una lista para actualizar los estados en actualizar juego.
    return juego

def actualizar_juego(nuevo_juego):
    """Actualiza el estado del juego."""
    tablero, mov_total, nivel_tablero, intentos, posicion_nivel = nuevo_juego

    """Verifica que todas las casillas esten apagadas y si el nivel esta terminado,
        pase al siguiente nivel. En caso de que sea el último nivel no entrará en este y terminará con
        el juego."""
    if esta_vacio(tablero) and nivel_tablero == posicion_nivel and posicion_nivel != len(NIVELES) - 1:
        #Cambia el nivel del juego
        posicion_nivel += 1
        nivel_tablero += 1
        tablero = inicializar_nivel(posicion_nivel)
        intentos = INTENTOS

    mov_total += 1
    intentos -= 1

    return  [tablero, mov_total, nivel_tablero, intentos, posicion_nivel]