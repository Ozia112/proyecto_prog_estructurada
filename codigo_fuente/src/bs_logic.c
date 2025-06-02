#include "bs_logic.h"

bool procesar_coordenadas(struct player *player, int index, int filaIn, int filaFin, int columnaIn, int columnaFin) {
    if (!validar_cc_rango(filaFin, columnaFin)) return false;
    if (!validar_orientacion(player, index, filaIn, filaFin, columnaIn, columnaFin)) return false;
    if (!validar_dimension(player, index, filaIn, filaFin, columnaIn, columnaFin)) return false;
    if (!validar_solapamiento(player, index, filaIn, filaFin, columnaIn, columnaFin)) return false;
    return true;
}

void colocar_casilla_inicial_en_tablero(struct player *player, int index, int filaIn, int columnaIn) {
    player->ships[index].status[0][CC_FILA] = filaIn;
    player->ships[index].status[0][CC_COLUMNA] = columnaIn;
    player->ships[index].status[0][CC_STATUS] = SHIP_STER; // Marca la proa del barco
}

void colocar_barco_en_tablero(struct player *player, int index, int filaInicio, int filaFin, int columnaInicio, int columnaFin) {
    int i, idx = 0;

    // Solo almacena la información en ship_i->status
    switch (player->ships[index].direction) {
        case 'E':
            for (i = columnaInicio; i <= columnaFin; i++, idx++) {
                player->ships[index].status[idx][CC_FILA] = filaInicio;
                player->ships[index].status[idx][CC_COLUMNA] = i;
                player->ships[index].status[idx][CC_STATUS] = (idx == 0) ? SHIP_STER : SHIP_BODY;
            }
            break;
        case 'O':
            for (i = columnaInicio; i >= columnaFin; i--, idx++) {
                player->ships[index].status[idx][CC_FILA] = filaInicio;
                player->ships[index].status[idx][CC_COLUMNA] = i;
                player->ships[index].status[idx][CC_STATUS] = (idx == 0) ? SHIP_STER : SHIP_BODY;
            }
            break;
        case 'S':
            for (i = filaInicio; i <= filaFin; i++, idx++) {
                player->ships[index].status[idx][CC_FILA] = i;
                player->ships[index].status[idx][CC_COLUMNA] = columnaInicio;
                player->ships[index].status[idx][CC_STATUS] = (idx == 0) ? SHIP_STER : SHIP_BODY;
            }
            break;
        case 'N':
            for (i = filaInicio; i >= filaFin; i--, idx++) {
                player->ships[index].status[idx][CC_FILA] = i;
                player->ships[index].status[idx][CC_COLUMNA] = columnaInicio;
                player->ships[index].status[idx][CC_STATUS] = (idx == 0) ? SHIP_STER : SHIP_BODY;
            }
            break;
    }
}

void decidir_primer_turno(struct player *player1, struct player *player2) {
    int primer_turno = (rand() % 2) + 1;
    printf("Decidiendo quien sera el primer jugador de forma aleatoria...\n");
    Sleep(1000);

    if (primer_turno == 1) {
        player1->turno = 1;
        player2->turno = 2;
        color_txt(INFO_COLOR); printf("%s ", player1->name); color_txt(DEFAULT_COLOR); printf("ha sido elegido para comenzar la partida\n");
        color_txt(INFO_COLOR); printf("%s ", player2->name); color_txt(DEFAULT_COLOR); printf("sera el segundo en jugar\n");
    } else {
        player2->turno = 1;
        player1->turno = 2;
        color_txt(INFO_COLOR); printf("%s ", player2->name); color_txt(DEFAULT_COLOR); printf("ha sido elegido para comenzar la partida\n");
        color_txt(INFO_COLOR); printf("%s ", player1->name); color_txt(DEFAULT_COLOR); printf("sera el segundo en jugar\n");
    }
}

int obtener_id_aleatoria(struct player *player) {
    // Recalcular probabilidades antes de sacar una carta
    player->peso_total = calcular_peso_total(player);
    if(player->peso_total <= 0) {
        return -1; // No hay cartas disponibles
    }
    
    // Numero aleatorio entre 0 y peso_total
    int numero_rand = rand() % player->peso_total;
    
    int acumulado = 0;
    for (int i = 0; i < NUM_CARTAS; i++) {
        acumulado += player->cartas[i].peso;
        if (numero_rand < acumulado) {
            return i;
        }
    }
    return -1; // No se encontró una carta válida
}

int calcular_peso_total(struct player *player) {
    int peso_total = 0;
    for (int i = 0; i < NUM_CARTAS; i++) {
        peso_total += player->cartas[i].peso;
    }
    return peso_total;
}

bool validar_movimiento(struct player *player_i, struct ship *ship_i) {
    int dx = 0, dy = 0;
    int nx, ny;
    int s, k;
    switch(ship_i->direction) {
        case 'E': dy =  1; break;
        case 'O': dy = -1; break;
        case 'N': dx =  1; break;
        case 'S': dx = -1; break;
        default: return false;
    }
    nx = ship_i->status[0][CC_FILA] + dx;
    ny = ship_i->status[0][CC_COLUMNA] + dy;

    // Validar rango en la matriz
    if(nx < 0 || ny < 0 || nx >= BOARD_SIZE || ny >= BOARD_SIZE) {
        return false;
    }

    // Validar solapamiento con otro barco
    for(s = 0; s < NUM_SHIPS; s++){
        for(k = 0; k < player_i->ships[s].size; k++) {
            if(player_i->ships[s].status[k][CC_FILA] == nx && player_i->ships[s].status[k][CC_COLUMNA] == ny) {
                return false;
            }
        }
    }

    // Validar salud del barco
    for(int p = 0; p < ship_i->size; p++) {
        if(ship_i->status[p][CC_STATUS] == SHIP_BODY_D || ship_i->status[p][CC_STATUS] == SHIP_STER_D) {
            return false;
        }
    }
    return true;
}