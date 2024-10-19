# TP: Carrera de obstáculos

## Repositorio de (Nombre Apellido) - (Padrón) - (Mail)

- Para compilar:

```bash
línea de compilación
```

- Para ejecutar:

```bash
línea de ejecución
```

- Para ejecutar con valgrind:
```bash
línea con valgrind
```
---
##  Funcionamiento

Explicación de cómo funcionan las estructuras desarrolladas en el TP y el funcionamiento general del mismo.

Aclarar en esta parte todas las decisiones que se tomaron al realizar el TP, cosas que no se aclaren en el enunciado, fragmentos de código que necesiten explicación extra, etc.

Incluír **EN TODOS LOS TPS** los diagramas relevantes al problema (mayormente diagramas de memoria para explicar las estructuras, pero se pueden utilizar otros diagramas si es necesario).

### Por ejemplo:

El programa funciona abriendo el archivo pasado como parámetro y leyendolo línea por línea. Por cada línea crea un registro e intenta agregarlo al vector. La función de lectura intenta leer todo el archivo o hasta encontrar el primer error. Devuelve un vector con todos los registros creados.

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---

## Respuestas a las preguntas teóricas
Incluír acá las respuestas a las preguntas del enunciado (si aplica).


Para ejecutar de forma rápida el juego copiar esto en el makefile.

```bash
VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g
CC = gcc

all: ejecutar_juego

ejecutar_juego: src/*.c juego.c
	$(CC) $(CFLAGS) src/*.c juego.c -o juego
	valgrind $(VALGRIND_FLAGS) ./juego ejemplo/pokemones.txt
```


## TP

### Estructura
La estructura del tp contiene:

* cantidad_pokemon: La cantidad de pokemones que tiene almacenado.
* obstaculos_j1: Contiene la pista de obstaculos del jugador 1.
* obstaculos_j2: Contiene la pista de obstaculos del jugador 2.
* pokemon_j1: El pokemon del jugador 1.
* pokemon_j2: El pokemon del jugador 2.

### tp_crear
En tp_crear recibe un nombre del archivo luego inicializo el tp pidiendo memoria en caso de que no tenga un nombre del archivo o falle pidiendo memoria devuelvo NULL.

Luego llamo a la función que va a leer el archivo para guardar los datos del pokémon en el árbol binario de búsqueda (abb). El comparador del abb compará los nombres de los pokemones, el que voy a ingresar y con el que está en el árbol.

Para guardar al pokémon, voy a leer esa línea de texto y hago un split que me separá el nombre y sus atributos y en una función a parte pido memoria para almacenarlo en una estructura. El nombre del pokémon va a pasar por una función de copiar el nombre y además se guardará con la primera letra en mayúscula y el resto en minúscula. Luego de esto, guardo el pokémon en el árbol.

Para finalizar está función, guardo el tamaño del abb en cantidad_pokémon y creo una ***Lista*** para los obstáculos de jugador 1 y 2.

### tp_cantidad_pokemon
Devuelvo la cantidad de pokémones que hay almacenados en el abb.

Complejidad O(1): Solo devuelvo el valor;

### tp_buscar_pokemon
Recibe el tp y un nombre de un pokémon.

Creo la estructura del pokemon con el nombre recibido pero con sus atributos nulos, esto se debe a que el árbol está guardado una estructura del pokemon y el comparador recibe una estructura, por eso cree la estructura con solo el nombre. 

Luego de hacer la busqueda libero la estructura que hice para buscar al pokémon. Si no se encontro la estructura del pokemon devuelvo NULL. Si se encontró devuelvo la estructura del pokémon pedido.

Complejidad O(log n): Esto se debe a que estoy usando el abb para buscar al pokémon;
Complejidad O(n): En caso de que el abb se haya convertido en una lista de pokémon por guardarlos alfabeticamente.


### tp_nombres_disponibles
Recibe el tp.

Para realizar esta parte me cree una estructura que va a tener el string llamado ***nombres_disponibles***, la ***cantidad*** de pokémones, ***actual*** que sería un contador hasta que llegue a la cantidad de pokemones, esto sirve para poner las ***","***. Luego la estructura de los pokemones del jugador 1 y 2 para saltear esos nombres.

En tp_nombres_disponibles preparo los datos necesarios y llamo a abb_con_cada_elemento para crear la lista de nombres. Para eso voy a usar INORDEN para que ordene alfabeticamente, la función agregar_listado y el auxiliar va a ser la estructura que cree.
Al final, devolverá el string con los nombres disponibles.

La función recibe la estructura de pokemones y la estructura que cree para el auxiliar.

Si lo datos del pokemon del jugador 1 o 2 son iguales al pokemon que estoy actualmente, devuelvo true para saltearlo.

Pido más memoria para agregar el nombre del pokémon al string. Luego si el actual es menor a la cantidad, agregó la ***","*** para separar los nombres.

Complejidad O(n): Esto se debe a que recorro todos los elementos del árbol para devolver el string de nombres.

### tp_seleccionar_pokemon
Recibe el tp, un jugador y el nombre del pokémon.

Hago lo mismo que hice en ***tp_buscar_pokemon*** para buscar al pokémon. Una vez encontrado, veo si este le pertenece al jugador 1 o 2. Si el pokemon no se encontro o el pokemon es el mismo que tiene el jugador contrario devuelvo false, y sin asignar el pokémon al jugador.
Si pasa le asigno el pokémon al jugador que lo pidió y devuelvo true.

Complejidad O(log n): Esto se debe a que estoy usando el abb para buscar al pokémon;
Complejidad O(n): En caso de que el abb se haya convertido en una lista de pokémon por guardarlos alfabeticamente.

### tp_pokemon_seleccionado
Recibe el tp y un jugador.

Devuelve al jugador que lo pidio, la estructura del pokémon que seleccionó anteriormente.

Complejidad O(1): Como tengo el pokémon guardado en la estructura del tp, este lo recibe de inmediato.

## tp_agregar_obstaculo
Recibe el tp, un jugador, un obstaculo y una posición.

Para este caso, cree una estructura con el enum del ***obstaculo***, su ***identificador*** y el ***tiempo*** de dicho obstáculo.

Primero creo al obstaculo llamando a la función que se encargará de pedir memoria y guardar sus datos dependiendo del obstaculo. Luego veo que jugador es al que le voy a agregar el obstáculo e inserto en la lista de obstaculos de dicho jugador en la posición dada.
Luego devuelvo el tamaño de la lista de obstaculos.

Complejidad O(n): Como estoy usando una lista para guardar los obstaculos, voy a recorrer la lista para guardar el obstaculo en la posición recibida.

## tp_quitar_obstaculo
Recibe el tp, un jugador y una posición.

Veo que jugador es al que voy a quitar el obstáculo y voy a usar lista_quitar_de_posicion para que quite ese obstáculo. Este me devuelve el obstáculo y lo libero porque había pedido memoria para guardarlo. Una vez quitado, devuelve el tamaño de la lista de obstáculos actualizado.

Complejidad O(n): Como estoy usando una lista para quitar los obstaculos, voy a recorrer la lista para sacar el obstaculo en la posición recibida.

## tp_obstaculos_pista
Recibe el tp y un jugador.

Veo que jugador es al que voy devolverle el string de su pista de obstáculos.
En una función a parte, pido memoria para el string de obstáculos y va a recorrer la lista con un iterador externo.

Mientras el contador i sea menor al tamaño de la lista agrego los identificadores al string.
Si i es igual al tamaño agrego el 0 al final del string para decir que hay termina el string.
Luego libero el iterador externo y devuelvo el string de los obstáculos.

Complejidad O(n): Recorro la lista.

## tp_limpiar_pista
Recibe el tp y un jugador.

Veo que jugador es al que voy a limpiar la pista. Para ello, libero la memoria de los obstaculos y la lista. Luego vuelvo a crear una lista para el jugador.

Complejidad O(n): Recorro y libero los elementos de la lista.


## tp_calulcar_tiempo_pista
Recibe el tp y un jugador.

Veo que jugador es al que voy devolverle el string del tiempo de su pista de obstáculos.
Mientras el contador i sea menor al tamaño de la lista agrego los identificadores al string.
Si i es igual al tamaño agrego el 0 al final del string para decir que hay termina el string.
Si es distinto agrego la ',' para separar el tiempo de cada obstáculo.
Luego libero el iterador externo y devuelvo el string del tiempo de los obstáculos.

Complejidad O(n): Recorro la lista.

## tp_destruir
Recibe el tp.

Libero toda la memoria pedida a lo largo del TDA. Libero el abb junto con la información de los pokemones. También libero los obstaculos de los jugadores. Y por último libero el tp.

Complejidad O(n): Recorro el abb y las listas.

## Menu

## Estructura
* Tiene el tp que va a ser recibido.
* La partida es un booleano para que se siga ejecutando el juego hasta que sea falso.
* La carrera iniciada es un booleano para que el jugador no pueda seleccionar un pokémon al iniciar la carrera.
* La dificultad es un numero entre el 0 al 3 de un enum de dificultad. Con esto se va a modificar los intentos y la pista del jugador 2.
* Pokémon del jugador 1 y 2 contiene los pokémon de los jugadores. Esto es para mostrar sus estadisticas.
* El Tamaño de pista para el jugador 1 y 2 es para antes de iniciar la carrera. Si es menor a 3 este no iniciará la carrera.


## iniciar_juego
Recibe el tp.

Si no existe el tp devuelvo NULL. Este primero imprime el logo del juego. Le pide al jugador que seleccione la dificultad. Luego asigna un pokémon para el jugador 2, los intentos y la pista, estos dos últimos dependen de la dificultad que el jugador seleccionó. Devuelve el menú.

## menu_ejecutar
Recibe el menú.

Si no existe el menu devuelve y no hace nada. Mientras la partida sea true va a seguir ejecutandose. Le pide al jugador que ingrese alguno de los comandos que se muestran en pantalla. Si el comando es el indicado, se ejecuta esa acción.
Cuando la partida sea false, este terminará de ejecutarse.

## destruir_menu
Recibe el menú.

Destruye el menú.
Complejidad O(1): Solo destruye el menú.


## Cómo jugar
Al iniciar el juego, este pedirá la dificultad: FÁCIL, NORMAL, DIFÍCIL e IMPOSIBLE. Se tendrá que pedir al usuario que ingrese un número del 1 al 4, que representan la dificultad. Dependiendo la dificultad se asignará una cantidad de intentos. Luego se mostrará la dificultad que se ingreso.

<div align="center">
<img width="70%" src="img/captura 0.png">
</div>
	
***Si estos intentos se acaban es fin del juego al instante.***

Luego aparecerá el menú. Este tendrá varias opciones.
Si quieres volver a consultar el menú, ingresa ***'?'***.

<div align="center">
<img width="70%" src="img/captura 1.png">
</div>

***P, R y L*** son opciones para la pista. 
* ***P*** es para agregar un obstáculo a la pista. Se pedirá que se ingrese un atributo ***F, D o I*** y luego una posición empezando del 0.Para salir, ingrese ***S*** al momento de ingresar un atributo.

<div align="center">
<img width="70%" src="img/captura 2.png">
</div>

* ***R***: es para quitar un obstáculo de la pista. Solo se pedirá que se ingrese una posición válida empezando desde el 0. Si se desea salir solo ingrese -1.

<div align="center">
<img width="70%" src="img/captura 3.png">
</div>

* ***L***: Limpia la pista. Quita todos los obstáculos de la lista.

***M y S*** son opciones con relación al pokémon del jugador.

* ***M***: Muestra los datos del pokémon. Esto incluye su nombre, sus atributos, la pista de obstáculos y el tiempo que le toma recorrerlo.

<div align="center">
<img width="70%" src="img/captura 4.png">
</div>


* ***S***: Selecciona un pokémon. Aparecerá una lista con los pokemones disponibles. Es necesario ingresar el nombre completo. Ejemplo: Ekans para probar. 

<div align="center">
<img width="70%" src="img/captura 5.png">
</div>


***No se podrá elegir un pokémon si: el rival tiene ese pokémon, si el pokémon está mal escrito o si la carrera ya había empezado.***

***C***: Es para comenzar la carrera. Este iniciará si el jugador tiene al menos 3 obstáculos disponibles, si no los tiene saldrá un mensaje.

Luego de correr la carrera, saldrá el resultado y decidirá al ganador con aquel jugador que haya recorrido la pista en menos tiempo.
Abajo de este, aparecerá el reintentar. Si se elige ***Sí*** se podrá volver al menú principal y cambiar la pista. Si se elige ***No*** se saldrá completamente del juego.

<div align="center">
<img width="70%" src="img/captura 6.png">
</div>

***Q***: Salir del juego.

***No le saque captura a algunas cosas que se muestran en pantalla ejemplo el título.***