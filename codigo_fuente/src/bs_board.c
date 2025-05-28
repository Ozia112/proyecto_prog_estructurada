#include "bs_board.h"

// Administrar colocacion y movimiento de barcos

bool validar_cc_rango(int cc_fila, int cc_columna) {
    if (cc_fila >= 0 && cc_fila < BOARD_SIZE && 
        cc_columna >= 0 && cc_columna < BOARD_SIZE) {
        return true; // Coordenadas válidas
    }
    if (cc_fila < 0 || cc_fila >= BOARD_SIZE) {
        color_txt(ERROR_COLOR);
        printf("Coordenada fuera de rango(Fila).");

    } else if (cc_columna < 0 || cc_columna >= BOARD_SIZE) {
        color_txt(ERROR_COLOR);
        printf("Coordenada fuera de rango(Columna).");
    }
    color_txt(INFO_COLOR); printf(" CodeError: 1\n");
    color_txt(DEFAULT_COLOR);
    return false;
}

bool validar_orientacion(struct player *player, int index, int filaInicio, int filaFin, int columnaInicio, int columnaFin) {
    if (!(filaInicio == filaFin || columnaInicio == columnaFin)) {
        color_txt(ERROR_COLOR);
        printf("Orientacion no permitida, el barco debe ser horizontal o vertical."); color_txt(INFO_COLOR); printf(" CodeError: 2\n");
        color_txt(DEFAULT_COLOR);
        return false;
    } else { // Si la orientación es válida, asignar la dirección.
        if (filaInicio == filaFin) {
            player->ships[index].direction = (columnaInicio < columnaFin) ? 'E' : 'O';
        } else if (columnaInicio == columnaFin) {
            player->ships[index].direction = (filaInicio < filaFin) ? 'S' : 'N';
        } else {
            player->ships[index].direction = 'U'; // No debería ocurrir si las validaciones son correctas
        }
        return true; // Orientación válida
    }
}

bool validar_dimension( struct player *player, int index, int filaInicio, int filaFin, int columnaInicio, int columnaFin) {
    int dimension_actual;

    if (player->ships[index].direction == 'E' || player->ships[index].direction == 'O') {
        dimension_actual = abs(columnaFin - columnaInicio) + 1;
    } else {
        dimension_actual = abs(filaFin - filaInicio) + 1;
    }
    if (dimension_actual != player->ships[index].size) {
        color_txt(ERROR_COLOR);
        printf("Las coordenadas no son validas. El barco debe tener"); color_txt(INFO_COLOR); printf(" %d", player->ships[index].size);
        color_txt(ERROR_COLOR); printf(" celdas de longitud.", player->ships[index].size); color_txt(INFO_COLOR); printf(" CodeError: 3\n");
        color_txt(DEFAULT_COLOR);
        return false;
    }
    return true; // Dimensión válida
}

bool validar_solapamiento(struct player *player, int index, int filaInicio, int filaFin, int columnaInicio, int columnaFin) {
    int i, x, y, idx_ship, s_part;

    // Recorre todas las posiciones que ocuparía el nuevo barco
    if (player->ships[index].direction == 'E' || player->ships[index].direction == 'O') {
        // Horizontal
        for (i = columnaInicio; (player->ships[index].direction == 'E') ? (i <= columnaFin) : (i >= columnaFin); (player->ships[index].direction == 'E') ? i++ : i--) {
            x = filaInicio;
            y = i;
            // Compara contra todos los barcos ya colocados
            for (idx_ship = 0; idx_ship < player->placed_ships; idx_ship++) {
                for (s_part = 0; s_part < player->ships[idx_ship].size; s_part++) {
                    // Solo compara si la casilla ya fue asignada (no -1)
                    if ((posicion_barco(player, idx_ship, s_part, x, y)) && x != -1 && y != -1) {
                        color_txt(ERROR_COLOR);
                        printf("Solapamiento detectado en"); color_txt(INFO_COLOR); printf(" %d,%d", x, y); 
                        color_txt(DEFAULT_COLOR); printf(" con el barco %d", idx_ship + 1);
                        color_txt(INFO_COLOR); printf(" CodeError: 4\n"); color_txt(DEFAULT_COLOR);
                        return false; // Hay solapamiento
                    }
                }
            }
        }
    } 
    // Vertical
    else {    
        for (i = filaInicio; (player->ships[index].direction == 'S') ? (i <= filaFin) : (i >= filaFin); (player->ships[index].direction == 'S') ? i++ : i--) {
            x = i;
            y = columnaInicio;
            for (s_part = 0; s_part < player->ships[idx_ship].size; s_part++) {
                // Solo compara si la casilla ya fue asignada (no -1)
                if ((posicion_barco(player, idx_ship, s_part, x, y)) && x != -1 && y != -1) {
                    color_txt(ERROR_COLOR);
                    printf("Solapamiento detectado en"); color_txt(INFO_COLOR); printf(" %d,%d", x, y);
                    color_txt(DEFAULT_COLOR); printf(" con el barco %d", idx_ship + 1);
                    color_txt(INFO_COLOR); printf(" CodeError: 4\n"); color_txt(DEFAULT_COLOR);
                    return false; // Hay solapamiento
                }
            }
        }
    }
    return true; // No hay solapamiento
}

// Administrar ataques a barcos

bool validar_ataque_cc_rango(struct player *player) {
    int f = player->last_input_fila;
    int c = player->last_input_columna;

    // Cartas que solo requieren validar fila
    if (player->last_card_id == 3 || player->last_card_id == 6) {
        if (f < 0 || f >= BOARD_SIZE) {
            color_txt(ERROR_COLOR);
            printf("Fila fuera del tablero de juego.");
            color_txt(INFO_COLOR); printf(" CodeError: 1\n");
            color_txt(DEFAULT_COLOR);
        }
        return (f >= 0 && f < BOARD_SIZE); // Solo fila es válida
    }
    if (player->last_card_id == 4 || player->last_card_id == 7) {
        if (c < 0 || c >= BOARD_SIZE) {
            color_txt(ERROR_COLOR);
            printf("Columna fuera del tablero de juego.");
            color_txt(INFO_COLOR); printf(" CodeError: 1\n");
            color_txt(DEFAULT_COLOR);
        }
        return (c >= 0 && c < BOARD_SIZE); // Solo columna es válida
    }
    // Cartas que requieren validar fila y columna
    return validar_cc_rango(f, c);
}

int barcos_en_fila(struct player *player, struct player *enemy) {
    int contador = 0;
    
    // bf = barrido de fila
    for (int bf = 0; bf < BOARD_SIZE; bf++) {
        for (int idx_ship = 0; idx_ship < NUM_SHIPS; idx_ship++) {
            for (int s_part = 0; s_part < enemy->ships[idx_ship].size; s_part++) {
                // Comprobar si la parte del barco coincide con la fila y no está dañado
                if (enemy->ships[idx_ship].status[s_part][CC_FILA] == player->last_input_fila && casilla_saludable(enemy, idx_ship, s_part)) {
                    contador++;
                }
            }
        }
    }
    return contador;
}

int barcos_en_columna(struct player *player, struct player *enemy) {
    int contador = 0;

    // bc = barrido de columna
    for (int bc = 0; bc < BOARD_SIZE; bc++) {
        for (int idx_ship = 0; idx_ship < NUM_SHIPS; idx_ship++) {
            for (int s_part = 0; s_part < enemy->ships[idx_ship].size; s_part++) {
                // Comprobar si la parte del barco coincide con la columna y no está dañado
                if (enemy->ships[idx_ship].status[s_part][CC_COLUMNA] == player->last_input_columna && (casilla_saludable(enemy, idx_ship, s_part))) {
                    contador++;
                }
            }
        }
    }
    return contador;
}

bool validar_estado_casilla(struct player *player, struct player *enemy) {
    // ¿Hay barco en la coordenada?
    for (int idx_ship = 0; idx_ship < NUM_SHIPS; idx_ship++) {
        for (int s_part = 0; s_part < enemy->ships[idx_ship].size; s_part++) {
            if (posicion_barco_enemy(player, idx_ship, s_part, enemy)) {
                if (!casilla_saludable(enemy, idx_ship, s_part)) { // Si la casilla esta dañada
                    color_txt(ERROR_COLOR);
                        printf("Casilla ya disparada previamente");
                    color_txt(INFO_COLOR);
                        printf(" CodeError: 5\n");
                    color_txt(DEFAULT_COLOR);
                    return false; // Ya disparado
                }
                return true; // Casilla válida para disparar
            }
        }
    }
    return true; // No habia barco → puede disparar (agua)
}

bool validar_entrada(char *input, int carta_id) {
    char *endptr;
    long num;
    char *salto_linea;
    char c;

    // SOLO fila (letra)
    if (carta_id == 3 || carta_id == 6) {
        salto_linea = strchr(input, '\n');
        if (!salto_linea) {
            color_txt(ERROR_COLOR); printf("Debe ingresar una letra.");
            color_txt(INFO_COLOR); printf(" CodeError: 0\n");
            color_txt(DEFAULT_COLOR);
            return false;
        }
        *salto_linea = '\0';
        if (strlen(input) != 1 || !isalpha((unsigned char)input[0])) {
            color_txt(ERROR_COLOR); printf("Formato de entrada invalido.");
            color_txt(INFO_COLOR); printf(" CodeError: 1\n");
            color_txt(DEFAULT_COLOR);
            return false;
        }
        c = toupper((unsigned char)input[0]);
        if (c < 'A' || c > 'A' + BOARD_SIZE - 1) {
            color_txt(ERROR_COLOR); printf("Fila fuera del tablero de juego.");
            color_txt(INFO_COLOR); printf(" CodeError: 2\n");
            color_txt(DEFAULT_COLOR);
            return false;
        }
        return true;
    }
    // SOLO columna (número)
    else if (carta_id == 4 || carta_id == 7) {
        if (strchr(input, '\n') == NULL) {
            color_txt(ERROR_COLOR); printf("Debe ingresar un numero.");
            color_txt(INFO_COLOR); printf(" CodeError: 0\n");
            color_txt(DEFAULT_COLOR);
            return false;
        }
        input[strcspn(input, "\n")] = '\0';
        errno = 0;
        num = strtol(input, &endptr, 10);
        if (errno == ERANGE || *endptr != '\0') {
            color_txt(ERROR_COLOR); printf("Formato de entrada invalido.");
            color_txt(INFO_COLOR); printf(" CodeError: 1\n");
            color_txt(DEFAULT_COLOR);
            return false;
        }
        if (num < 1 || num > BOARD_SIZE) {
            color_txt(ERROR_COLOR); printf("Columna fuera del tablero de juego.");
            color_txt(INFO_COLOR); printf(" CodeError: 3\n");
            color_txt(DEFAULT_COLOR);
            return false;
        }
        return true;
    }
    return false;
}
