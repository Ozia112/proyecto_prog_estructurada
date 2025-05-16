#include <stdio.h>
#include "bs_logic.h"
#include "bs_console_utils.h" // libreria para poder usar la funcion limpiar y cambio de color.
#include "bs_ui.h" // libreria para poder usar funciones de UI.

void inicializar_barco(struct ship *barco, int size) {
    barco-> size = size;
    barco->orientation = 'U'; // No definido
    barco->direction = 'U'; // No definido

    // Inicializar coordenadas a -1 para indicar que no está colocado.
    barco->startShip[0] = -1;
    barco->startShip[1] = -1;
    barco->endShip[0] = -1;
    barco->endShip[1] = -1;
}

// Inicializar jugadores.
void inicializar_jugador(struct player *player) {

    // Asignar el nombre al jugador.
    solicitar_nombre(player->name, sizeof(player->name));

    // Inicializar estado de jugador.
    player->placed_ships = 0;
    player->sunked_enemy_ships = 0;
    player->sunked_ships = 0;

    // Inicializar barcos.
    inicializar_flota(player);
}

// Inicializa la flota de un jugador.
void inicializar_flota(struct player *player) {
    // Initialize ships with different sizes
    inicializar_barco(&player->ships[0], 5); // 5 cells
    inicializar_barco(&player->ships[1], 4); // 4 cells
    inicializar_barco(&player->ships[2], 3); // 3 cells
    inicializar_barco(&player->ships[3], 3); // 3 cells
    inicializar_barco(&player->ships[4], 2); // 2 cells
}

bool validar_coordenadas_en_rango(int fila, int columna) {
    return (fila >= 0 && fila < BOARD_SIZE && columna >= 0 && columna < BOARD_SIZE);
}

bool validar_orientacion(int filaInicio, int filaFin, int columnaInicio, int columnaFin) {
    return (filaInicio == filaFin || columnaInicio == columnaFin);
}

bool validar_dimension(int filaInicio, int filaFin, int columnaInicio, int columnaFin, int dimension_reuqerida) {
    int dimension_actual;

    if (filaInicio == filaFin) {
        dimension_actual = abs(columnaFin - columnaInicio) + 1;
    } else if(columnaInicio == columnaFin) {
        dimension_actual = abs(filaFin - filaInicio) + 1;
    } else {
        return false; // No es una línea recta
    }
    
    return (dimension_actual == dimension_reuqerida);
    
}

bool validar_solapamiento(int matriz[BOARD_SIZE][BOARD_SIZE], int filaInicio, int filaFin, 
                          int columnaInicio, int columnaFin, struct ship *ship_i) {
    int i;

    // Determinar la orientación y dirección del barco
    if (filaInicio == filaFin) {
        ship_i->orientation = 'H'; // Horizontal
        if (columnaInicio <= columnaFin) {
            ship_i->direction = 'E'; // Este
            for (i = columnaInicio; i <= columnaFin; i++) {
                if (matriz[filaInicio][i] != 0) {
                    return false; // Hay solapamiento
                }
            }
        } else {
            ship_i->direction = 'O'; // Oeste
            for (i = columnaFin; i <= columnaInicio; i++) {
                if (matriz[filaInicio][i] != 0) {
                    return false; // Hay solapamiento
                }
            }
        }
    } else if (columnaInicio == columnaFin) {
        ship_i->orientation = 'V'; // Vertical
        if (filaInicio <= filaFin) {
            ship_i->direction = 'S'; // Sur
            for (i = filaInicio; i <= filaFin; i++) {
                if (matriz[i][columnaInicio] != 0) {
                    return false; // Hay solapamiento
                }
            }
        } else {
            ship_i->direction = 'N'; // Norte
            for (i = filaFin; i <= filaInicio; i++) {
                if (matriz[i][columnaInicio] != 0) {
                    return false; // Hay solapamiento
                }
            }
        }
    }
    return true; // No hay solapamiento
}

void colocar_barco_en_tablero(int matriz[BOARD_SIZE][BOARD_SIZE], struct ship *ship_i) {
    int i;

    if (ship_i->orientation == 'H') {
        if (ship_i->direction == 'E') {
            for (i = ship_i->startShip[1]; i <= ship_i->endShip[1]; i++) {
                if (i == ship_i->startShip[1]) {
                    matriz[ship_i->startShip[0]][i] = SHIP_STER; // se asigna el valor 1 para la popa del barco.
                } else {
                    matriz[ship_i->startShip[0]][i] = SHIP_BODY; // se asigna el valor 2 para el cuerpo del barco.
                }
            }
        } else if (ship_i->direction == 'O') {
            for (i = ship_i->startShip[1]; i >= ship_i->endShip[1]; i--) {
                if (i == ship_i->startShip[1]) {
                    matriz[ship_i->startShip[0]][i] = SHIP_STER; // se asigna el valor 1 para la popa del barco.
                } else {
                    matriz[ship_i->startShip[0]][i] = SHIP_BODY; // se asigna el valor 2 para el cuerpo del barco.
                }
            }
        }
    } else if (ship_i->orientation == 'V') {
        if (ship_i->direction == 'S') {
            for (i = ship_i->startShip[0]; i <= ship_i->endShip[0]; i++) {
                if (i == ship_i->startShip[0]) {
                    matriz[i][ship_i->startShip[1]] = SHIP_STER; // se asigna el valor 1 para la popa del barco.
                } else {
                    matriz[i][ship_i->startShip[1]] = SHIP_BODY; // se asigna el valor 2 para el cuerpo del barco.
                }
            }
        } else if (ship_i->direction == 'N') {
            for (i = ship_i->startShip[0]; i >= ship_i->endShip[0]; i--) {
                if (i == ship_i->startShip[0]) {
                    matriz[i][ship_i->startShip[1]] = SHIP_STER; // se asigna el valor 1 para la popa del barco.
                } else {
                    matriz[i][ship_i->startShip[1]] = SHIP_BODY; // se asigna el valor 2 para el cuerpo del barco.
                }
            }
        }
    }
}

bool procesar_coordenadas(int matriz[BOARD_SIZE][BOARD_SIZE], struct ship *ship_i, 
                          int filaInicio, int filaFin, int columnaInicio, int columnaFin) {
    // Validar orientación (horizontal o vertical)
    if(!validar_orientacion(filaInicio, filaFin, columnaInicio, columnaFin)) {
        cambiar_color_txt(ERROR_COLOR);
        printf("Las coordenadas no son válidas. El barco debe ser horizontal o vertical.\n");
        cambiar_color_txt(DEFAULT_COLOR);
        return false;
    }

    // Validar que la dimensión del barco sea correcta
    if(!validar_dimension(filaInicio, filaFin, columnaInicio, columnaFin, ship_i->size)) {
        cambiar_color_txt(ERROR_COLOR);
        printf("Las coordenadas no son válidas. El barco debe tener exactamente %d celdas de longitud.\n", ship_i->size);
        cambiar_color_txt(DEFAULT_COLOR);
        return false;
    }

    // Validar que no haya solapamiento con otros barcos
    if(!validar_solapamiento(matriz, filaInicio, filaFin, columnaInicio, columnaFin, ship_i)) {
        cambiar_color_txt(ERROR_COLOR);
        printf("Las coordenadas no son válidas. Hay solapamiento con otro barco.\n");
        cambiar_color_txt(DEFAULT_COLOR);
        return false;
    }

    // Si todas las validaciones pasan, colocar el barco

    // Guardar las coordenadas de inicio y fin del barco.
    ship_i->startShip[0] = filaInicio;
    ship_i->startShip[1] = columnaInicio;
    ship_i->endShip[0] = filaFin;
    ship_i->endShip[1] = columnaFin;
    
    return true;
}

// Función para limpiar el buffer de entrada
void limpiar_buffer_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}