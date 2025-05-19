## Documentación Técnica de la Biblioteca [`bs_ui.h`] / [`bs_ui.c`]

La biblioteca [`bs_ui.h`] / [`bs_ui.c`] centraliza toda la interacción con el usuario para el juego Batalla Naval, gestionando desde la bienvenida, menús, reglas, hasta la visualización y manipulación del tablero. Su diseño modular permite separar la lógica de presentación de la lógica de juego, facilitando el mantenimiento y la escalabilidad del proyecto.

---

### Bibliotecas Incluidas

```c
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "bs_common.h"
```

- **`stdio.h` y `stdlib.h`**: Para operaciones estándar de entrada/salida y utilidades generales.
- **`windows.h`**: Permite manipular la consola de Windows (colores, limpiar pantalla).
- **`string.h` y `ctype.h`**: Para manejo de cadenas y validación de caracteres.
- **`stdbool.h`**: Uso de tipos booleanos.
- [`bs_common.h`]: Define estructuras y constantes comunes del juego.

---

### Macros

```c
#define ship_tip 207   // Carácter especial "¤" para la punta del barco
#define ship_body 254  // Carácter especial "■" para el cuerpo del barco
```

Estas macros definen los caracteres utilizados para representar visualmente los barcos en el tablero.

---

### Funciones Principales

#### 1. [`void pantalla_bienvenida();`]

**Propósito:**  
Muestra el logo del juego y solicita al usuario presionar Enter para continuar. Limpia la pantalla tras la bienvenida.

**Código relevante:**
```c
void pantalla_bienvenida() {
    printf(" _______  ...  \n");
    printf("Presione cualquier \"enter\" para continuar");
    getchar();
    limpiar_pantalla();
}
```
**Variables:**  
No utiliza variables locales relevantes.

**Bibliotecas llamadas:**  
- [`bs_console_utils.h`] para [`limpiar_pantalla()`].

---

#### 2. [`void menu_principal();`]

**Propósito:**  
Despliega el menú principal, permitiendo iniciar partida, ver reglas o salir.

**Código relevante:**
```c
void menu_principal() {
    char opc = ' ';
    while(opc != 'C'){
        printf("Opciones:\n[A]: Iniciar partida\n[B]: Ver reglas.\n[C]: Salir\n");
        scanf(" %c", &opc);
        opc = toupper(opc);
        switch(opc) {
            case 'A': limpiar_pantalla(); partida(); break;
            case 'B': reglas(); break;
            case 'C': printf("Gracias por haber usado el programa :)"); break;
            default: puts("¡Tecla invalida!"); Sleep(1000); limpiar_pantalla(); break;
        }
    }
}
```
**Variables:**  
- `opc`: almacena la opción seleccionada por el usuario.

**Bibliotecas llamadas:**  
- [`bs_console_utils.h`] para limpiar pantalla y colores.
- [`bs_ui.h`] para llamar a otras funciones de UI.

---

#### 3. [`void solicitar_nombre(char *nombre, int max_length);`]

**Propósito:**  
Solicita y valida el nombre del jugador, asegurando que no exceda el tamaño máximo.

**Código relevante:**
```c
void solicitar_nombre(char *nombre, int max_length) {
    printf("Introduce el nombre del jugador (maximo %d caracteres): ", max_length - 1);
    fgets(nombre, max_length, stdin);
    nombre[strcspn(nombre, "\n")] = '\0';
}
```
**Variables:**  
- [`nombre`]: puntero al buffer donde se almacena el nombre en el struct `player` en [`bs_common.h`].
- [`max_length`]: longitud máxima permitida.

---

#### 4. [`void partida();`]

**Propósito:**  
Gestiona el flujo principal de una partida: inicialización de jugadores, colocación de barcos y selección aleatoria del primer turno.

**Código relevante:**
```c
void partida(){
    struct player player1, player2;
    int matriz_jug1[BOARD_SIZE][BOARD_SIZE] = {0};
    int matriz_jug2[BOARD_SIZE][BOARD_SIZE] = {0};
    limpiar_buffer_entrada();
    printf("Jugador 1:\n"); inicializar_jugador(&player1);
    limpiar_pantalla();
    printf("Jugador 2:\n"); inicializar_jugador(&player2);
    limpiar_pantalla();
    colocar_barcos_jugador(&player1, matriz_jug1);
    printf("Ahora es turno de %s\n", player2.name); enter_continuar();
    colocar_barcos_jugador(&player2, matriz_jug2);
    decidir_primer_turno(&player1, &player2);
}
```
**Variables:**  
- `player1`, `player2`: estructuras de jugadores.
- `matriz_jug1`, `matriz_jug2`: tableros de cada jugador.

**Bibliotecas llamadas:**  
- [`bs_logic.h`] para inicialización y lógica de jugadores/barcos.
- [`bs_console_utils.h`] para limpiar pantalla y colores.

---

#### 5. [`void imprimirTablero(int matriz[BOARD_SIZE][BOARD_SIZE]);`](../../codigo_fuente/bs_ui.c#L132)

**Propósito:**  
Imprime el tablero en consola, mostrando el estado de cada celda con colores y caracteres especiales.

**Código relevante:**
```c
void imprimirTablero(int matriz[BOARD_SIZE][BOARD_SIZE]) {
    // ...cálculo de relleno y centrar tablero...
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            switch (matriz[i][j]) {
                case 0: color_txt(WATER_COLOR); printf("%c ", '~'); break;
                case 1: color_txt(SHIP_COLOR); printf("%c ", SHIP_STER); break;
                case 2: color_txt(SHIP_COLOR); printf("%c ", SHIP_BODY); break;
                // ...
            }
            color_txt(DEFAULT_COLOR);
        }
        printf("\n");
    }
}
```
**Variables:**  
- `matriz`: matriz del tablero a imprimir.
- `i`, `j`: índices de filas y columnas.

**Bibliotecas llamadas:**  
- [`bs_console_utils.h`] para colores.

---

#### 6. [`void ponerBarcos(int matriz[BOARD_SIZE][BOARD_SIZE], struct ship *ship_i, struct player *player_i);`](../../codigo_fuente/bs_ui.c#L199)

**Propósito:**  
Permite al usuario colocar un barco, validando coordenadas, orientación, tamaño y solapamiento.

**Código relevante:**
```c
void ponerBarcos(int matriz[BOARD_SIZE][BOARD_SIZE], struct ship *ship_i, struct player *player_i) {
    int filaInicio, filaFin, columnaInicio, columnaFin;
    char columnaInicio_c, columnaFin_c;
    bool coordenadas_validas = false;
    while(!coordenadas_validas) {
        // Solicitud y validación de coordenadas
        if(procesar_coordenadas(matriz, ship_i, filaInicio, filaFin, columnaInicio, columnaFin)) {
            colocar_barco_en_tablero(matriz, ship_i, filaInicio, filaFin, columnaInicio, columnaFin);
            player_i->placed_ships++;
            coordenadas_validas = true;
        }
    }
}
```
**Variables:**  
- `filaInicio`, `filaFin`, `columnaInicio`, `columnaFin`: coordenadas de inicio y fin del barco.
- `coordenadas_validas`: controla el bucle de validación.

**Bibliotecas llamadas:**  
- [`bs_logic.h`] para validaciones y colocación de barcos.

---

#### 7. [`void colocar_barcos_jugador(struct player *player, int matriz[BOARD_SIZE][BOARD_SIZE]);`](../../codigo_fuente/bs_ui.c#L290)

**Propósito:**  
Gestiona la colocación de todos los barcos de un jugador, mostrando el tablero y solicitando la posición de cada barco.

**Código relevante:**
```c
void colocar_barcos_jugador(struct player *player, int matriz[BOARD_SIZE][BOARD_SIZE]) {
    for(int i = 0; i < NUM_SHIPS; i++) {
        limpiar_pantalla();
        imprimirTablero(matriz);
        ponerBarcos(matriz, &player->ships[i], player);
    }
    imprimirTablero(matriz);
    enter_continuar();
    limpiar_pantalla();
}
```
**Variables:**  
- `player`: jugador actual.
- `matriz`: tablero del jugador.

---

#### 8. [`void reglas();`]

**Propósito:**  
Muestra las reglas del juego y espera a que el usuario presione Enter.

**Código relevante:**
```c
void reglas() {
    printf("Las reglas para jugar al iconico juego \"Batalla Naval\" rezan lo siguiente:\n");
    // ...reglas...
    limpiar_buffer_entrada();
    getchar();
    limpiar_pantalla();
}
```

---

#### 9. [`void enter_continuar();`]

**Propósito:**  
Pausa la ejecución hasta que el usuario presione Enter.

**Código relevante:**
```c
void enter_continuar() {
    printf("Presione enter para continuar.\n");
    getchar();
}
```

---

### Variables Importantes

- **`matriz[BOARD_SIZE][BOARD_SIZE]`**: Representa el tablero de cada jugador.
- [**`struct player`**]: Estructura que almacena nombre, flota y estadísticas del jugador.
- [**`struct ship`**]: Estructura que almacena tamaño, orientación, dirección y estado de cada parte del barco.

---

### Dependencias y Colaboración entre Bibliotecas

- [`bs_console_utils.h`]: Proporciona utilidades para limpiar pantalla y cambiar colores de texto, mejorando la experiencia visual.
- [`bs_logic.h`]: Encapsula la lógica de validación y manipulación de barcos y jugadores, permitiendo que la UI se enfoque solo en la interacción.
- [`bs_common.h`]: Define las estructuras y constantes fundamentales para el juego.

---

### Digrama de Flujo de Datos
``` mermaid
flowchart TD
    %% Entradas principales
    main([main.c]) --> pantalla_bienvenida
    main --> menu_principal

    %% Pantalla de bienvenida
    pantalla_bienvenida["pantalla_bienvenida()"]
    pantalla_bienvenida --> limpiar_pantalla

    %% Menú principal
    menu_principal["menu_principal()"]
    menu_principal -->|Opción A| limpiar_pantalla
    menu_principal -->|Opción A| partida
    menu_principal -->|Opción B| reglas
    menu_principal -->|Opción C| fin([Fin])

    %% Reglas
    reglas["reglas()"]
    reglas --> limpiar_buffer_entrada
    reglas --> limpiar_pantalla

    %% Partida
    partida["partida()"]
    partida --> limpiar_buffer_entrada
    partida --> inicializar_jugador1["inicializar_jugador(&player1)"]
    partida --> limpiar_pantalla
    partida --> inicializar_jugador2["inicializar_jugador(&player2)"]
    partida --> limpiar_pantalla
    partida --> colocar_barcos_jugador1["colocar_barcos_jugador(&player1, matriz_jug1)"]
    partida --> enter_continuar
    partida --> colocar_barcos_jugador2["colocar_barcos_jugador(&player2, matriz_jug2)"]
    partida --> decidir_primer_turno

    %% Colocar barcos jugador
    colocar_barcos_jugador1 --> imprimirTablero
    colocar_barcos_jugador1 --> ponerBarcos
    colocar_barcos_jugador2 --> imprimirTablero
    colocar_barcos_jugador2 --> ponerBarcos

    ponerBarcos --> procesar_coordenadas
    ponerBarcos --> colocar_barco_en_tablero

    %% Dependencias externas
    limpiar_pantalla -.-> bs_console_utils["bs_console_utils.h"]
    color_txt -.-> bs_console_utils
    limpiar_buffer_entrada -.-> bs_logic["bs_logic.h"]
    inicializar_jugador1 -.-> bs_logic
    inicializar_jugador2 -.-> bs_logic
    procesar_coordenadas -.-> bs_logic
    colocar_barco_en_tablero -.-> bs_logic
    decidir_primer_turno -.-> bs_logic

    %% Leyenda
    classDef ext fill:#f9f,stroke:#333,stroke-width:1px,color:#000000;
    class bs_console_utils,bs_logic ext;
```
### Conclusión

>La biblioteca bs_ui.h es el punto de contacto entre el usuario y el sistema, asegurando una experiencia clara, validando entradas y manteniendo la integridad del flujo de juego. Su diseño modular y su integración con otras bibliotecas especializadas garantizan un código mantenible, escalable y fácil de entender para futuros desarrolladores.

[`bs_ui.h`]: ../../codigo_fuente/bs_ui.h

[`bs_ui.c`]: ../../codigo_fuente/bs_ui.c

[`bs_common.h`]: ../../codigo_fuente/bs_common.h

[`bs_logic.h`]: ../../codigo_fuente/bs_logic.h

[`void pantalla_bienvenida();`]: ../../codigo_fuente/bs_ui.c#L8

[`bs_console_utils.h`]: ../../codigo_fuente/bs_console_utils.h

[`limpiar_pantalla()`]: ../../codigo_fuente/bs_console_utils.h#L6

[`void menu_principal();`]: ../../codigo_fuente/bs_ui.c#L24

[`void solicitar_nombre(char *nombre, int max_length);`]: ../../codigo_fuente/bs_ui.c#L88

[`nombre`]: ../../codigo_fuente/bs_common.h#L25
[`max_length`]: ../../codigo_fuente/bs_common.h#L6

[`void partida();`]: ../../codigo_fuente/bs_ui.c#L94

[`void reglas();`]: ../../codigo_fuente/bs_ui.c#L309

[`void enter_continuar();`]: ../../codigo_fuente/bs_ui.c#L320

[**`struct player`**]: ../../codigo_fuente/bs_common.h#L23

[**`struct ship`**]: ../../codigo_fuente/bs_common.h#L15