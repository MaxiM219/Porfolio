<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA HASH

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

### ¿Qué es un diccionario?
Un diccionario es una estructura de datos que se usa para almacenar un par de claves y valor.

La clave es necesaria para encontrar al elemento al que está asociada dicha clave. Además la clave es única, no se puede modificar.

El valor está asociado a la clave y este puede tener guardado cualquier cosa. Además el elemento que almaceno puede ser modificado.

### 3 formas diferentes de implementar un diccionario
En este caso hay 3 formas diferentes de implementar un diccionario, pero hay más. En este caso los 3 que elegí son:

1 - Tabla de Hash
- Para guardar/ver/quitar se puede hacer directamente en la tabla de hash. No es necesario tener una estructura auxiliar.
- Hay que definir algunos métodos para saber el estado de la tabla. Si está vacía, borrada o ocupada.

2 - Listas Enlazadas
- Para guardar/ver/quitar se puede hacer en la tabla de hash y una estructura auxiliar. En este caso la lista enlazada. Esto quiere decir que puedo guardar el par clave valor dentro de esta estructura.
- Si una clave dio la misma posición que otra, este se va a guardar al siguiente de la otra clave.
- Al guardar/ver/quitar va a recorrer la lista hasta encontrar el par que estoy buscando. La complejidad sería O(n) si mi lista llegará a tener varios elementos.

<div align="center">
<img width="70%" src="img/Hash lista.png">
</div>

3 - Árboles
- Para guardar/ver/quitar se puede hacer en la tabla de hash y una estructura auxiliar. En este caso un árbol, en especifico un árbol binario de búsqueda. Esto quiere decir que puedo guardar el par clave valor dentro de esta estructura, además de usar un comparador para revisar las claves.
- Si una clave dio la misma posición que otra, este se va a guardar como un hijo de esa clave.
- Al ver/quitar va a recorrer el ABB hasta encontrar el par que estoy buscando. La complejidad sería O(log(n)) ya que no necesito recorrer todo el árbol para buscar el elemento.

<div align="center">
<img width="70%" src="img/Hash ABB.png">
</div>


### ¿Qué es una función de hash y qué características debe tener?
Una función de hash es cualquier función que pueda usarse para asignar datos de tamaños arbitrarios a valores de tamaño fijo.

Las características de una función de hash son las siguientes:
Tiene que ser **Determinista**, de **Rango Definido**, tiene que ser **Eficiente**, **Uniforme**, de **Resistencia a la primera preimagen**, de **Resistente a colisiones** y de **Efecto avalancha**.

### ¿Qué es una tabla de Hash?
Una **tabla de hash** es una estructura de datos usada para insertar, ver, quitar los valores.
A partir de una clave voy a usar una función de hash que hará el trabajo de dar una posición dentro de la tabla. Con esta posición va a encontrar el lugar donde se va a insertar/buscar/quitar el valor dentro de la tabla.

<div align="center">
<img width="70%" src="img/Ejemplo de hash.png">
</div>

###  Los diferentes métodos de resolución de colisiones vistos (encadenamiento, probing, etc)
Para guardar/buscar en la tabla de hash va a haber casos en los cuales la función de hash nos puede devolver una misma posición. Ese misma posición nos puede causar un problema al querer guardar algo en nuestra tabla. Se lo conoce como colisión y en la diferentes implementaciones hay que evitar que no modifique el valor en esa posición que no le pertenece.

**Rehash**: En caso de que la tabla de hash se haya llenado, es necesario crear una nueva tabla de hash con más capacidad.
Al hacer esto, se tiene que volver a insertar todos los pares de clave, valor no borrados a la nueva tabla.

**Hash abierto**:
En hash abierto la tabla de hash usa una estructura auxiliar para guardar las claves con sus respectivos valores.
Puede tener una tabla de hash apuntando a una lista, un árbol, etc. Y guardar sus pares allí.

**Caso de Encadenamiento: Colisión**:
En este caso si tenemos una tabla de hash con una estructura de lista. Los pares clave valor se van a insertar a la lista.

Pero al tener varios elementos en una lista voy a tener que iterar la lista hasta encontrar ese elemento. Y la complejidad de recorrer la lista es O(n). Esto puede llegar a tardar por lo que la solución sería hacer un rehash.
Esto reubicaría los pares clave,valor en distintas posiciones de la nueva tabla.



<div align="center">
<img width="70%" src="img/Hash lista.png">
</div>


**Hash Cerrado**
En hash cerrado guardamos los pares claves, valor en la tabla de hash, podemos usar un dato adicional para saber si fue borrado o no.
Es necesario saber que un par clave, valor fue borrado, esto se debe en caso de que haya guardado varios elementos con la misma posición y se haya reubicado más adelante.
Ejemplo:

<div align="center">
<img width="70%" src="img/Hash cerrado borrado.png">
</div>

**Colisión**:
En caso de que haya una colisión en un hash cerrado, es necesario tener un metodo para manejar estos casos y este sería el **Probing**. Hay 3 casos de probing vistos.

**Probing lineal**: Busca al siguiente espacio libre de inmediato. O sea que recorro uno por uno hasta encontrar un espacio vacío para insertar el par.

**Probing cuadrático**: (intentos fallidos)^2 para intentar insertar.

**Hash doble**: Aplica una segunda función de hash a la clave cuando hay colisión.

**Factor de carga**:
En caso de llenarse la tabla de hash, es necesario hacer un rehash cuando se cumpla la condición del factor de carga.Este se calcula mediante la cantidad de claves almacenadas (llamamos n) y la capacidad de la tabla (llamamos m). 

La cuenta es la siguiente: **α = n/m**. Para hacer el rehash, hay que definir de cuanto va a ser nuestro factor de carga. Por ejemplo si definimos α >= 0.75, esto quiere decir que cuando α sea mayor o igual a ese número, recién podremos hacer el rehash.

## Mi TDA Hash
Voy a explicar las funciones auxiliares que hice para lograr el TDA Hash.

### Funciones de Hash
## Crear
Creo el hash y le asigno la capacidad dada por el usuario, si la capacidad es menor que 3, por defecto la capacidad se asignará de 3.
Creo la tabla a partir de la capacidad y devuelve el hash creado.

<div align="center">
<img width="70%" src="img/Hash mi estructura.png">
</div>


## Insertar
Recibo por parametro una clave, un elemento y un anterior. Voy a obtener una posición dada por la función de hash usando la clave y la capacidad. 

**Guardar por primera vez**: Para guardar el par (clave, valor) me fijaré de que no haya colisionado con otro par dada por la posición. Si no colisionan guardo el par en una posición vacía.
Si no recorro la tabla hasta encontrar un lugar vacío.

**Guardar con clave repetida**: Para guardar el par (clave, valor) me fijaré de que no haya colisionado con otro par dada por la posición. Si no colisionan las claves serán iguales y lo que se reemplaza es el valor. Se guardará el nuevo valor y el que estaba antes se guardará en **anterior** si este no es NULL. 

## Quitar
Recibo por parametro una clave. Voy a obtener una posición dada por la función de hash usando la clave y la capacidad.

Para quitar voy a recorrer la tabla, si está ocupado y las claves son iguales, guardo mi valor en una variable para luego devolverla, el valor en esa posición lo dejo en NULL, su estado va a ser borrado, la cantidad disminuye y libero la clave. Si no encontró al elemento devuelvo NULL.

## Obtener
Está función me devuelve el valor de la clave.
Recibo por parametro una clave. Voy a obtener una posición dada por la función de hash usando la clave y la capacidad.

Para obtener el valor recorro la tabla mientras no sea vacío. Si está ocupado y las claves son iguales devuelvo el valor. Si no ocurre esto devuelvo NULL.

## Contiene
Está función me devuelve un booleano que revisará si mi clave está en la tabla de hash.
Recibo por parametro una clave. Voy a obtener una posición dada por la función de hash usando la clave y la capacidad.

Recorro la tabla mientras no sea vacío. Si está ocupado y las claves son iguales devuelvo el **true**. Si no ocurre esto devuelvo **false**.

## Cantidad
Me devuelve la cantidad de pares (claves, valor) **ocupados** en la tabla de hash.

## Destruir
Primero destruye las claves que están ocupadas en la tabla de hash, luego la tabla y al final la estructura del hash.

## Destruir todo
Primero destruye los elementos pedidos por memoria si el usuario le paso un destructor, luego destruye las claves que están ocupadas en la tabla de hash, la tabla y al final la estructura del hash.

## Hash con cada clave
Voy a recorrer la tabla y le aplicaré una función dada por el usuario a aquellos pares que esten ocupados, también recibo un auxiliar para usarla en la función. Si no recibo la función dada por el usuario este devuelve 0. Devuelve la cantidad de veces que se uso la función del usuario.

## Funciones Auxiliares

Al comienzo, elegí tener un enum de estados para la tabla: VACIO = 0, OCUPADO = 1, BORRADO = 2.
Esto me pareció un poco mejor a tener un booleano que solo tiene true o false. Ya que se me hace más fácil ver estos valores al recorrer la tabla.

### Funciones para Hash
Para mi función de Hash busque SDBMHash, le paso el string y su largo, y este me devuelve un número en unsigned int.

Para obtener la posición uso de la función de hash, este me va a dar un número. Al hacer el resto del número con la capacidad este me va a dar la posición en la que va a estar almacenado el par clave, valor.

### Funciones de redimensión
Factor de carga: Cuando mi tabla de hash tenga un 75% o más de pares ocupados y borrados, voy a hacer una redimensión. 
La cuenta es Resultado = (cantidad de ocupado + cantidad de borrados) / capacidad.
*La cantidad de borrados es importante porque aún siguen estando ocupando un espacio dentro de la tabla*.

Para hacer una redimensión, lo que voy a pedir es una nueva capacidad y un nuevo hash.
El nuevo hash será para pasar la tabla, la nueva capacidad, la cantidad, luego este será liberado.

Para la nueva capacidad voy a multiplicar la capacidad por 2 y luego llamo a una función para que busque un número primo. 

*¿Para qué quiero que la capacidad sea un número primo?*
Al tener un número primo, la función de hash va a ser más eficiente ya que voy a tener menos colisiones a la hora de asignar las posiciones.

Volviendo, al tener un nuevo hash, voy a iterar la tabla de hash anterior para insertar los pares ocupados en la nueva tabla. Al finalizar la iteración hago los cambios necesarios y libero la tabla vieja y el nuevo hash. La nueva tabla será ahora la que está.

