#include <stdio.h>
#include "bs_logic.h"
#include "bs_console_utils.h" // libreria para poder usar la funcion limpiar y cambio de color.
#include "bs_ui.h" // libreria para poder usar funciones de UI.

void inicializar_barco(struct ship *barco, int size) {
    barco-> size = size;
    barco->orientation = 'U'; // No definido
    barco->direction = 'U'; // No definido

    // Reservar memoria para el estado del barco.
    barco->status = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        barco->status[i] = (int *)malloc(3 * sizeof(int)); // 3 columnas para x, y y estado
        barco->status[i][0] = -1; // Inicializar coordenadas x a -1
        barco->status[i][1] = -1; // Inicializar coordenadas y a -1
        barco->status[i][2] = 0; // Inicializar estado a 0 (agua)
    }
}

// Inicializar jugadores.
void inicializar_jugador(struct player *player) {

    // Asignar el nombre al jugador.
    solicitar_nombre(player->name, sizeof(player->name));

    // Inicializar estado de jugador.
    player->placed_ships = 0;
    player->enemy_hit_parts = 0;
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

void colocar_barco_en_tablero(int matriz[BOARD_SIZE][BOARD_SIZE], struct ship *ship_i, int filaInicio, 
                              int filaFin, int columnaInicio, int columnaFin) {
    int i, idx = 0;

    // Guardar las coordenadas de inicio y fin del barco.
    if (ship_i->orientation == 'H') {
        if (ship_i->direction == 'E') {
            for (i = columnaInicio; i <= columnaFin; i++, idx ++) {
                if (idx == 0) {
                    matriz[filaInicio][i] = SHIP_STER; // se asigna el valor 1 para la popa del barco.
                } else {
                    matriz[filaInicio][i] = SHIP_BODY; // se asigna el valor 2 para el cuerpo del barco.
                }
                ship_i->status[idx][0] = filaInicio; // Guardar coordenadas x
                ship_i->status[idx][1] = i; // Guardar coordenadas y
                if (idx == 0) {
                    ship_i->status[idx][2] = SHIP_STER; // Estado de la punta del barco
                } else {
                    ship_i->status[idx][2] = SHIP_BODY; // Estado del cuerpo del barco
                }
            }
        } else if (ship_i->direction == 'O') {
            for (i = columnaInicio; i >= columnaFin; i--, idx++) {
                if (idx == 0) {
                    matriz[filaInicio][i] = SHIP_STER; // se asigna el valor 1 para la popa del barco.
                } else {
                    matriz[filaInicio][i] = SHIP_BODY; // se asigna el valor 2 para el cuerpo del barco.
                }
                ship_i->status[idx][0] = filaInicio; // Guardar coordenadas x
                ship_i->status[idx][1] = i; // Guardar coordenadas y
                if (idx == 0) {
                    ship_i->status[idx][2] = SHIP_STER; // Estado de la punta del barco
                } else {
                    ship_i->status[idx][2] = SHIP_BODY; // Estado del cuerpo del barco
                }  
            }
        }
    } else if (ship_i->orientation == 'V') {
        if (ship_i->direction == 'S') {
            for (i = filaInicio; i <= filaFin; i++, idx++) {
                if (idx == 0) {
                    matriz[i][columnaInicio] = SHIP_STER; // se asigna el valor 1 para la popa del barco.
                } else {
                    matriz[i][columnaInicio] = SHIP_BODY; // se asigna el valor 2 para el cuerpo del barco.
                }
                ship_i->status[idx][0] = i; // Guardar coordenadas x
                ship_i->status[idx][1] = columnaInicio; // Guardar coordenadas y
                if (idx == 0) {
                    ship_i->status[idx][2] = SHIP_STER; // Estado de la punta del barco
                } else {
                    ship_i->status[idx][2] = SHIP_BODY; // Estado del cuerpo del barco
                }
            }
        } else if (ship_i->direction == 'N') {
            for (i = filaInicio; i >= filaFin; i--, idx++) {
                if (idx == 0) {
                    matriz[i][columnaInicio] = SHIP_STER; // se asigna el valor 1 para la popa del barco.
                } else {
                    matriz[i][columnaInicio] = SHIP_BODY; // se asigna el valor 2 para el cuerpo del barco.
                }
                ship_i->status[idx][0] = i; // Guardar coordenadas x
                ship_i->status[idx][1] = columnaInicio; // Guardar coordenadas y
                if (idx == 0) {
                    ship_i->status[idx][2] = SHIP_STER; // Estado de la punta del barco
                } else {
                    ship_i->status[idx][2] = SHIP_BODY; // Estado del cuerpo del barco
                }
            }
        }
    }

}

bool procesar_coordenadas(int matriz[BOARD_SIZE][BOARD_SIZE], struct ship *ship_i, 
                          int filaInicio, int filaFin, int columnaInicio, int columnaFin) {
    // Validar orientación (horizontal o vertical)
    if(!validar_orientacion(filaInicio, filaFin, columnaInicio, columnaFin)) {
        color_txt(ERROR_COLOR);
        printf("Las coordenadas no son validas. El barco debe ser horizontal o vertical.\n");
        color_txt(DEFAULT_COLOR);
        return false;
    }

    // Validar que la dimensión del barco sea correcta
    if(!validar_dimension(filaInicio, filaFin, columnaInicio, columnaFin, ship_i->size)) {
        color_txt(ERROR_COLOR);
        printf("Las coordenadas no son validas. El barco debe tener exactamente %d celdas de longitud.\n", ship_i->size);
        color_txt(DEFAULT_COLOR);
        return false;
    }

    // Validar que no haya solapamiento con otros barcos
    if(!validar_solapamiento(matriz, filaInicio, filaFin, columnaInicio, columnaFin, ship_i)) {
        color_txt(ERROR_COLOR);
        printf("Las coordenadas no son validas. Hay solapamiento con otro barco.\n");
        color_txt(DEFAULT_COLOR);
        return false;
    }    
    return true;
}

int decidir_primer_turno(const struct player *p1, const struct player *p2) {
    int primer_turno = (rand() % 2) + 1;
    limpiar_pantalla(); 
    printf("El numero aleatorio para decidir quien inicia es:"); color_txt(INFO_COLOR); printf(" %d\n", primer_turno); color_txt(DEFAULT_COLOR);
    Sleep(1000);
    if (primer_turno == 1) {
        color_txt(INFO_COLOR); printf("¡%s ",p1->name); color_txt(DEFAULT_COLOR); printf(" ha sido elegido para comenzar la partida!\n");
    } else {
        color_txt(INFO_COLOR); printf("¡%s ",p2->name); color_txt(DEFAULT_COLOR); printf(" ha sido elegido para comenzar la partida!\n");
    }
    enter_continuar();
    getchar();
    return primer_turno;
}

// Función para limpiar el buffer de entrada
void limpiar_buffer_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void liberar_status(struct ship *barco) {
    for (int i = 0; i < barco->size; i++) {
        free(barco->status[i]);
    }
    free(barco->status);
    barco->status = NULL; // Evitar puntero colgante
}

void liberar_flota(struct player *player) {
    for (int i = 0; i < NUM_SHIPS; i++) {
        liberar_status(&player->ships[i]);
    }
}

void modificar_disparo(int matriz_enemigo[BOARD_SIZE][BOARD_SIZE], matriz_mostrada[BOARD_SIZE][BOARD_SIZE], int fila, int columna) {
    if (matriz_enemigo[fila][columna] == SHIP_STER) {
        matriz_mostrada[fila][columna] = 3; // Punta dañada
        printf("El disparo dirigido a (%d, %d) ha dañado la punta de un barco enemigo!\n", fila + 1, columna + 1);
    } else if (matriz_enemigo[fila][columna] == SHIP_BODY) {
        matriz_mostrada[fila][columna] = 4; // Cuerpo dañado
        printf("El disparo dirigido a (%d, %d) ha dañado un barco enemigo!\n", fila + 1, columna + 1);
    } else if (matriz_enemigo[fila][columna] == 0) {
        printf("El disparo dirigido a (%d, %d) ha caído en el agua!\n", fila + 1, columna + 1);
    } else {
        printf("El barco en las coordenadas (%d, %d) ya ha sido dañado antes. Dispara a un lugar diferente!\n", fila + 1, columna + 1);
        capturar_disparo(matriz_enemigo, matriz_mostrada); // Volver a capturar disparo si la casilla ya fue disparada
    }
    enter_continuar();
}