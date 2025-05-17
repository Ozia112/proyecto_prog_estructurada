## Documentación Detallada: [`bs_common.h`]

La biblioteca [`bs_common.h`] centraliza todas las definiciones, macros y estructuras de datos fundamentales para el funcionamiento del juego Batalla Naval. Su objetivo es garantizar la coherencia y facilitar el mantenimiento del código, permitiendo que todos los módulos accedan a las mismas definiciones y estructuras.

---

### Macros y Definiciones

- **BOARD_SIZE**
  - `#define BOARD_SIZE 10`
  - Define el tamaño del tablero de juego (10x10). Permite modificar el tamaño del tablero de manera centralizada si se requiere.

- **MAX_NAME_LENGTH**
  - `#define MAX_NAME_LENGTH 21`
  - Especifica la longitud máxima permitida para el nombre de un jugador (20 caracteres + 1 para el carácter nulo).

- **NUM_SHIPS**
  - `#define NUM_SHIPS 5`
  - Indica la cantidad de barcos que cada jugador tendrá en su flota.

- **WATER, SHIP_STER, SHIP_BODY**
  - `#define WATER 0`
  - `#define SHIP_STER 1`
  - `#define SHIP_BODY 2`
  - Representan los valores numéricos que se almacenan en la matriz del tablero para identificar agua, la punta del barco y el cuerpo del barco respectivamente.

---

### Estructuras de Datos

#### struct ship

```c
struct ship
{
    int size;
    char orientation; // 'H' horizontal, 'V' vertical, 'U' indefinido
    char direction;   // 'E' este, 'O' oeste, 'N' norte, 'S' sur, 'U' indefinido
    int **status;     // status[size][3]: [fila][0]=x, [fila][1]=y, [fila][2]=estado
};
```

- **size**: Tamaño del barco (número de celdas que ocupa).
- **orientation**: Orientación del barco ('H' para horizontal, 'V' para vertical, 'U' si aún no está definido).
- **direction**: Dirección del barco ('E', 'O', 'N', 'S', 'U').
- **status**: Matriz dinámica que almacena, para cada segmento del barco, su posición en el tablero y su estado:
  - `[i][0]`: Fila (x)
  - `[i][1]`: Columna (y)
  - `[i][2]`: Estado (1=punta, 2=cuerpo, 3=punta dañada, 4=cuerpo dañado)

#### struct player

```c
struct player
{
    char name[MAX_NAME_LENGTH];
    struct ship ships[NUM_SHIPS];
    int placed_ships;
    int sunked_enemy_ships;
    int sunked_ships;
};
```

- **name**: Nombre del jugador.
- **ships**: Arreglo de barcos que conforman la flota del jugador.
- **placed_ships**: Contador de barcos colocados en el tablero.
- **sunked_enemy_ships**: Contador de barcos enemigos hundidos por este jugador.
- **sunked_ships**: Contador de barcos propios hundidos.

#### struct cartas

```c
struct cartas
{
    int id;
    char nombre[20];
    char descripcion[100];
};
```

- **id**: Identificador único de la carta.
- **nombre**: Nombre de la carta.
- **descripcion**: Descripción de los efectos o reglas de la carta.

---

### Resumen de Funcionamiento

- Las macros permiten modificar parámetros globales del juego de forma sencilla.
- Las estructuras modelan los elementos clave del juego: barcos, jugadores y cartas.
- El uso de punteros y arreglos en las estructuras permite gestionar dinámicamente el estado de cada barco y la flota de cada jugador, facilitando la implementación de la lógica del juego y la interacción entre módulos.

---

> **Nota:** Esta biblioteca no contiene funciones, solo definiciones y estructuras. Todas las operaciones sobre estos datos se realizan en los módulos de lógica y UI, que incluyen este archivo para acceder a las definiciones comunes.

[`bs_common.h`]: ../../codigo_fuente/bs_common.h