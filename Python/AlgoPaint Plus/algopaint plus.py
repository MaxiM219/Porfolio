import gamelib
import png
from pila import Pila
#Se uso una pila como se vio en clases
#Se agregaron 2 pilas al paint

#Ventana
ANCHO_VENTANA = 300
ALTO_VENTANA = 400

#dibujo del tablero
MARGEN_TABLERO = 10
SECCION_CONTROLES = 75
ANCHO_VENTANA_TABLERO = ANCHO_VENTANA - MARGEN_TABLERO * 2
ALTO_VENTANA_TABLERO = ALTO_VENTANA - MARGEN_TABLERO * 2 - SECCION_CONTROLES

#tablero
TABLERO_INICIO_X = ANCHO_VENTANA - ANCHO_VENTANA_TABLERO
TABLERO_INICIO_Y = ALTO_VENTANA - ALTO_VENTANA_TABLERO

#Constantes
TABLERO = 0
DIMENSIONES = 1
COLORES = 2
MOV_DESHACER = 3
MOV_REHACER = 4
#Paleta de colores
PALETA = {"white": (255,255,255), "black": (0,0,0), "red": (255,0,0), "lime": (0,255,0), "blue": (0,0,255), "yellow": (255,255,0)}

#Tamano de los colores a mostrar
ANCHO_COLOR = 20
ALTO_COLOR = 20


def crear_tablero(ancho, alto):
    """Crea el tablero del paint"""
    return [([(255,255,255)] * alto) for _ in range(ancho)]

def paint_nuevo(ancho, alto):
    """inicializa el estado del programa con una imagen vacía de ancho x alto pixels"""
    tablero = crear_tablero(ancho, alto)
    dimensiones = (ancho, alto)
    color_seleccionado = PALETA["black"]
    mov_deshacer = Pila()
    mov_rehacer = Pila()
    return [tablero, dimensiones, color_seleccionado, mov_deshacer, mov_rehacer]

def abrir_imagen_ppm(ruta_archivo, paint):
    """Abre la imagen del archivo ppm."""
    _, _, color, deshacer, rehacer = paint
    tablero_imagen = []
    with open(ruta_archivo) as datos:
        header = next(datos)
        ancho, alto = tuple(int(i) for i in ((next(datos)).rstrip().split()))
        intensidad = next(datos)
        for linea in datos:
            lista = []
            color = []
            for i in linea.rstrip().split():
                color.append(int(i))
                if len(color) == 3:
                    #Si la lista de color tiene 3 elementos este se agrega a una lista
                    lista.append(tuple(color))
                    color = []
                if len(lista) == ancho:
                    #Si el largo de la lista coincide con el ancho este se agrega al tablero
                    tablero_imagen.append(lista)
                    lista = []

    dimensiones = ancho, alto
    paint = tablero_imagen, dimensiones, color, deshacer, rehacer
    return paint

def guardar_imagen_ppm(ruta, paint):
    """Guarda la imagen en formato ppm."""
    tablero, dimensiones, _, _, _ = paint
    ancho, alto = dimensiones
    with open(ruta, "w") as imagen:
        imagen.write("P3"+ "\n")
        #Guarda el ancho y el alto del tablero
        imagen.write(f"{ancho} {alto}"+ "\n")
        imagen.write("255"+ "\n")
        for i in tablero:
            for j in i:
                ppm = ""
                for color in j:
                    ppm += f"{color} "
                imagen.write(ppm)
                ppm = ""
            imagen.write("\n")

def guardar_paleta(tablero):
    """Guarda la paleta de colores al recorrer el tablero,
    si el color no esta en la lista, lo agrega y si ya
    estaba, este pasa de largo."""
    paleta = []
    for i in tablero:
        for color in i:
            if i not in paleta:
                paleta.append(color)
    return paleta

def guardar_lista_imagen(tablero, paleta, dimensiones):
    """Recorre el tablero, y al encontrar dicho color este
    se fija en la paleta de colores y guarda el valor en la
    lista de imagen."""
    imagen = []
    ancho, alto = dimensiones
    for i in range(ancho):
        indexado = []
        for j in range(alto):
            indexado.append(paleta.index(tablero[j][i]))
        imagen.append(indexado)
    return imagen

def guardar_imagen_png(ruta, paint):
    """Guarda el tablero del paint en formato png."""
    tablero, dimensiones, _, _, _ = paint
    paleta = guardar_paleta(tablero)
    imagen = guardar_lista_imagen(tablero, paleta, dimensiones)
    png.escribir(ruta, paleta, imagen)

def convertir_decimal_o_hex(color):
    """Convierte los valores decimales a hexadecimales"""
    color_hex = ""
    for i in color:
        color_hex += f"{i:02x}"
    return color_hex
    
def convertir_pixel_a_numero_tablero(dimensiones, x, y):
    """Convierte las posiciones cliqueadas x e y en numeros validos que estan dentro del tablero"""
    ancho, alto = dimensiones
    
    posicion_x = (x - MARGEN_TABLERO) // (ANCHO_VENTANA_TABLERO // ancho)
    posicion_y = (y - MARGEN_TABLERO) // (ALTO_VENTANA_TABLERO // alto)

    return posicion_x, posicion_y

def convertir_numero_tablero_a_pixel(ancho, alto, pos_x, pos_y):
    """Convierte las posiciones del tablero en las coordenadas en pixels"""
    pixel_x = pos_x * (ANCHO_VENTANA_TABLERO // ancho) + (ANCHO_VENTANA_TABLERO // ancho) // 2
    pixel_y = pos_y * (ALTO_VENTANA_TABLERO // alto) + (ALTO_VENTANA_TABLERO // alto) // 2
    return pixel_x, pixel_y

def convertir_a_color(color_ingresado):
    """Convierte los numeros de los colores a enteros y la lista de 
    colores en una tupla"""
    color_convertido = []
    for color in color_ingresado:
        color_convertido.append(int(color))
    return tuple(color_convertido)

def pintar_tablero(paint, x, y):
    """Pinta en la posicion seleccionada del tablero usando las posiciones
    "x" e "y" en pixeles y las convierte en un numero del tablero.
    Devuelve el tablero modificado"""
    tablero, dimensiones, color_seleccionado, _ , _ = paint
    ancho, alto = dimensiones
    if esta_en_tablero(x, y):
        guardar_mov_realizado(paint)
        pos_x, pos_y = convertir_pixel_a_numero_tablero(dimensiones, x, y)
        tablero[pos_x][pos_y] = color_seleccionado
        borrar_rehacer(paint)
    return paint

def seleccionar_color(paint, numero):
    """Selecciona el color mediante el teclado. 
    Devuelve el paint con el color seleccionado"""
    tablero, dimensiones, color_seleccionado, deshacer, rehacer = paint
    colores = list(PALETA.keys())
    numero_seleccionado = int(numero)
    if 1 <= numero_seleccionado <= 6:
        color_seleccionado = PALETA[colores[numero_seleccionado - 1]]
    if numero_seleccionado == 7:
        return tablero, dimensiones, PALETA["black"], deshacer, rehacer
    return tablero, dimensiones, color_seleccionado, deshacer, rehacer
    
def esta_en_tablero(x, y):
    """Verifica que x e y esten dentro del tablero"""
    tablero_inicio_x = MARGEN_TABLERO
    tablero_inicio_y = MARGEN_TABLERO

    return tablero_inicio_x <= x < (tablero_inicio_x + ANCHO_VENTANA_TABLERO) and tablero_inicio_y <= y < (tablero_inicio_y + ALTO_VENTANA_TABLERO)

def _es_color_valido(color_ingresado):
    """Verifica que el color tenga los valores necesarios, si algun valor no
    concuerda con lo ingresado este devolvería falso."""
    for i in range(len(color_ingresado)):
        #Si el valor ingresado es vacio, o si el largo del numero es menor a 0 o mayor igual a 4, o si el numero se pasa de los 255 devuelve falso.
        if color_ingresado[i] == "" or len(color_ingresado[i]) < 0 or len(color_ingresado[i]) >= 4 or 0 < int(color_ingresado[i]) > 255:
            return False
    return True

def ingresar_color(paint):
    """Se ingresa los colores mediante la forma rr,gg,bb.
    Luego de ser ingresado se verifica que:
    - Tenga dos comas
    - Si no se ingreso nada, advierte al usuario que ingrese los colores
    - Verifica que lo ingresado sean numeros
    Despues de estas verificaciones, se convierte lo ingresado en
    una lista separado por ',' y luego verifica que el color sea valido
    Una vez terminado devuelve el paint con el nuevo color ingresado"""
    tablero, dimensiones, color_seleccionado, deshacer, rehacer = paint
    comas = 2
    contador_comas = 0
    color_actual = ""
    color = gamelib.input('Escribe un color en forma rr,gg,bb (con ,)')
    if not color:
        gamelib.say("Ingrese los colores.")
        return paint
    for i in range(len(color)):
        if color[i] == ",":
            contador_comas += 1
            color_actual += color[i]
        if color[i].isnumeric():
            color_actual += (color[i])
        if not color[i].isnumeric() and not color[i] == ",":
            gamelib.say("No se ingreso un numero")
            return paint

    color_ingresado = color_actual.split(",")

    if contador_comas != comas:
        gamelib.say("Falto una o pusiste mas comas.")
        return paint
    if not _es_color_valido(color_ingresado):
        gamelib.say("Faltaron o pusiste mas numeros de lo debido.")
        return paint
    
    nuevo_color_seleccionado = convertir_a_color(color_ingresado)
    return tablero, dimensiones, nuevo_color_seleccionado, deshacer, rehacer

def mostrar_grilla(paint):
    """Muestra el tablero segun sus dimensiones y el color que tiene dicho posicion en el tablero."""
    tablero, dimensiones, _,_,_ = paint
    ancho, alto = dimensiones
    tablero_inicio_x = MARGEN_TABLERO
    tablero_inicio_y = MARGEN_TABLERO
    ancho_pixel = ANCHO_VENTANA_TABLERO // ancho
    alto_pixel = ALTO_VENTANA_TABLERO // alto

    for i in range(tablero_inicio_x, ANCHO_VENTANA_TABLERO + tablero_inicio_x - ancho_pixel + 1, ancho_pixel):
        for j in range(tablero_inicio_y, ALTO_VENTANA_TABLERO + tablero_inicio_y - alto_pixel + 1, alto_pixel):
            x, y = convertir_pixel_a_numero_tablero(dimensiones, i, j)
            gamelib.draw_rectangle(i, j, i + ancho_pixel, j + alto_pixel, fill= f"#{convertir_decimal_o_hex(tablero[x][y])}")

def mostrar_colores(paint):
    """Muestra por pantalla los colores predeterminados de este paint."""
    _, dimensiones, color_seleccionado,_,_ = paint
    paleta_inicio_x = MARGEN_TABLERO
    paleta_inicio_y = ALTO_VENTANA_TABLERO + 2 * MARGEN_TABLERO
    #lista de los nombres de los colores del diccionario
    colores = list(PALETA.keys())

    for i in range(len(colores)):
        key_color_actual = colores[i]
        value_color_actual = PALETA[key_color_actual]
        color_actual_x = i * (ANCHO_COLOR + MARGEN_TABLERO) + MARGEN_TABLERO
        if PALETA[colores[i]] == color_seleccionado:
            """Si el color seleccionado coincide con los colores del diccionario, 
            se indicara el color que se esta usando (Si se ingresa un color que no esta en el diccionario, no lo va a marcar)."""
            gamelib.draw_rectangle(color_actual_x - paleta_inicio_x // 5, paleta_inicio_y - 2, color_actual_x + ANCHO_COLOR + paleta_inicio_x // 5, paleta_inicio_y + ALTO_COLOR + 2, fill = f"white", outline = "white")
        gamelib.draw_rectangle(color_actual_x, paleta_inicio_y, color_actual_x + ANCHO_COLOR, paleta_inicio_y + ALTO_COLOR, fill = f"{key_color_actual}")

def paint_mostrar(paint):
    """Dibuja la interfaz de la aplicación en la ventana"""
    tablero, dimensiones, color_seleccionado ,deshacer , rehacer = paint
    ancho, alto = dimensiones
    tablero_inicio_x = ANCHO_VENTANA - ANCHO_VENTANA_TABLERO
    tablero_inicio_y = ALTO_VENTANA - ALTO_VENTANA_TABLERO

    gamelib.draw_rectangle(0, 0, ANCHO_VENTANA + 1, ALTO_VENTANA + 1, outline= "grey", fill ="grey")
    gamelib.draw_text("A: Abrir ppm G: Guardar ppm P: Guardar PNG", ANCHO_VENTANA // 2, ALTO_VENTANA - 30, size = 10, fill = "white")
    gamelib.draw_text("Elegir colores: 1-6 Atajo al negro: 7 I: Información", ANCHO_VENTANA // 2, ALTO_VENTANA - 10, size = 10, fill = "white")
    mostrar_grilla(paint)
    mostrar_colores(paint)


def copiar_tablero(paint):
    """Copia las filas del tablero"""
    tablero = paint[TABLERO]
    copia_tablero = []
    for fila in tablero:
        copia_tablero.append(fila[:])
    return copia_tablero

def guardar_mov_realizado(paint):
    """Guarda una copia del tablero antes de ser modificado 
    y la apila en la pila de deshacer."""
    mov_deshacer = paint[MOV_DESHACER]
    copia_tablero = copiar_tablero(paint)
    mov_deshacer.apilar(copia_tablero)

def deshacer(paint):
    """Una vez tocada la tecla de deshacer: si la pila no está vacía, desapila el tablero anterior
    al actual y el tablero actual lo apila en la pila de rehacer. Devuelve el tablero anterior
    que se guardo en la pila de deshacer.
    Si no hay un tablero guardado en la pila deshacer solo devuelve el paint sin ninguna
    modificación."""
    tablero, dimension, color, deshacer, rehacer = paint
    if not deshacer.esta_vacia():
        guardar_mov_rehacer(paint)
        tablero_anterior = deshacer.desapilar()
        return tablero_anterior, dimension, color, deshacer, rehacer
    return paint

def guardar_mov_rehacer(paint):
    """Guarda una copia del tablero actual y lo apila en la pila de rehacer."""
    mov_rehacer = paint[MOV_REHACER]
    copia_tablero = copiar_tablero(paint)
    mov_rehacer.apilar(copia_tablero)

def borrar_rehacer(paint):
    """Desapila los tableros de la pila rehacer cuando se modifica alguno
    de los tableros de la pila deshacer."""
    rehacer = paint[MOV_REHACER]
    while not rehacer.esta_vacia():
        rehacer.desapilar()

def rehacer(paint):
    """Una vez tocada la tecla de rehacer: si la pila no está vacía, desapila el tablero
    proximo al actual y el tablero actual lo apila en la pila de deshacer.
    Devuelve el tablero proximo que se guardo en la pila de rehacer.
    Si no hay un tablero guardado en la pila deshacer solo devuelve el paint sin ninguna
    modificación."""
    tablero, dimension, color, deshacer, rehacer = paint
    if not rehacer.esta_vacia():
        tablero_proximo = rehacer.desapilar()
        guardar_mov_realizado(paint)
        return tablero_proximo, dimension, color, deshacer, rehacer
    return paint

def pintar_con_balde(paint, x, y):
    """Wrapper de 'pintar con balde': Primero si x e y no estan en el tablero devuelvo el paint.
    Antes de pintar, guarda en la pila de deshacer el tablero antes de ser modificado, luego convierte
    x e y en posiciones del tablero.
    'color a pintar' es el color que se necesita en el tablero que se necesita cambiar por el color seleccionado.
    tablero va a llamar a la función recursiva que tiene el paint, las posiciones del tablero, el color a pintar, el color seleccionado
    y una lista que va a servir para guardar las posiciones ya visitadas.
    El mouse debe estar dentro del tablero y luego tocar la tecla B para efectuar dicha acción."""
    color_seleccionado = paint[COLORES]
    dimensiones = paint[DIMENSIONES]
    tablero = paint[TABLERO]
    if not esta_en_tablero(x, y):
        return paint
    guardar_mov_realizado(paint)
    pos_x, pos_y = convertir_pixel_a_numero_tablero(dimensiones, x, y)
    color_a_pintar = tablero[pos_x][pos_y]
    tablero = _pintar_con_balde(paint, pos_x, pos_y, color_a_pintar, color_seleccionado, [])
    return paint

def _pintar_con_balde(paint, pos_x, pos_y, color_a_pintar, color_seleccionado, lista_visitados):
    """Pinta las posiciones de forma recursiva."""
    tablero = paint[TABLERO]
    dimensiones = paint[DIMENSIONES]
    ancho, alto = dimensiones
    
    #Pinto dicha posición con el color seleccionado y luego agrego a la lista la posición usada.
    tablero[pos_x][pos_y] = color_seleccionado
    lista_visitados.append((pos_x, pos_y))
    
    #Posiciones que se deberan recorrer para pintar el tablero
    deltas = [(1, 0), (-1, 0), (0, -1), (0, 1)]

    #Uso las posiciones que se van a usar
    for delta_x, delta_y in deltas:
        #Sumo dichas posiciones y las llamo vecinos
        vecino_x, vecino_y = pos_x + delta_x, pos_y + delta_y
        #Verifica que los vecinos de la posicion en la que estoy actualmente no se vayan de rango de la lista y ademas
        #que los vecinos no esten en la lista de visitados.
        if 0 <= vecino_x < ancho and 0 <= vecino_y < alto and (vecino_x, vecino_y) not in lista_visitados:
            #Toma el color del tablero en dicha posicion
            color_vecino = tablero[vecino_x][vecino_y]
            #Si el color vecino coincide con el color a pintar entonces se usa la forma recursiva.
            if color_vecino == color_a_pintar:
                _pintar_con_balde(paint, vecino_x, vecino_y, color_a_pintar, color_seleccionado, lista_visitados)

def mostrar_información():
    """Información adicional del paint."""
    gamelib.say("Adicional: B: Balde: Si el mouse esta en el tablero,\npulsa B para pintar con el balde.\nD: Deshacer, R: Rehacer")
    

def main():
    gamelib.title("AlgoPaint")
    gamelib.resize(ANCHO_VENTANA, ALTO_VENTANA)

    paint = paint_nuevo(20, 20)

    while gamelib.is_alive():
        gamelib.draw_begin()
        paint_mostrar(paint)
        gamelib.draw_end()

        ev = gamelib.wait()
        if not ev:
            break

        if ev.type == gamelib.EventType.ButtonPress and ev.mouse_button == 1:
            print(f'se ha presionado el botón del mouse: {ev.x} {ev.y}')
            x, y = ev.x, ev.y
            paint = pintar_tablero(paint, x, y)

        # elif ev.type == gamelib.EventType.Motion:
        #     print(f'se ha movido el puntero del mouse: {ev.x} {ev.y}')
        # elif ev.type == gamelib.EventType.ButtonRelease and ev.mouse_button == 1:
        #     print(f'se ha soltado el botón del mouse: {ev.x} {ev.y}')
        elif ev.type == gamelib.EventType.KeyPress:
            print(f'se ha presionado la tecla: {ev.key}')
        if ev.type == gamelib.EventType.KeyPress and (ev.key == "a" or ev.key == "A"):
            try:
                paint = abrir_imagen_ppm(gamelib.input('Abrir imagen ppm'), paint)
            except:
                gamelib.say("No existe ese archivo.")
        if ev.type == gamelib.EventType.KeyPress and (ev.key == "g" or ev.key == "G"):
            try:
                guardar_imagen_ppm(gamelib.input('Guardar imagen ppm'), paint)
            except:
                gamelib.say("No se puede guardar archivo.")
        if ev.type == gamelib.EventType.KeyPress and (ev.key == "p" or ev.key == "P"):
            try:
                guardar_imagen_png(gamelib.input('Guardar imagen png'), paint)
            except:
                gamelib.say("No se puede guardar archivo.")
        if ev.type == gamelib.EventType.KeyPress and (ev.key == "c" or ev.key == "C"):
            paint = ingresar_color(paint)
        if ev.type == gamelib.EventType.KeyPress and (ev.key == "1" or ev.key == "2" or ev.key == "3" or ev.key == "4" or ev.key == "5" or ev.key == "6" or ev.key == "7"):
            paint = seleccionar_color(paint, ev.key)
        if ev.type == gamelib.EventType.KeyPress and (ev.key == "d" or ev.key == "D"):
            paint = deshacer(paint)
        if ev.type == gamelib.EventType.KeyPress and (ev.key == "r" or ev.key == "R"):
            paint = rehacer(paint)
        if ev.type == gamelib.EventType.KeyPress and (ev.key == "b" or ev.key == "B"):
            x, y = ev.x, ev.y
            paint = pintar_con_balde(paint, x, y)
        if ev.type == gamelib.EventType.KeyPress and (ev.key == "i" or ev.key == "I"):
            mostrar_información()
            
    
gamelib.init(main)