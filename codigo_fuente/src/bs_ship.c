
#include "bs_ship.h" // Incluye definiciones de barcos

void inicializar_flota(struct player *player) {
    // Inicializar barcos del jugador
    for (int idx_ship = 0; idx_ship < NUM_SHIPS; idx_ship++) {
        player->ships[idx_ship].id = idx_ship; // Asignar ID del barco
        switch (idx_ship) {
            case 0:
                strcpy(player->ships[idx_ship].name, "Portaaviones");
                inicializar_barco(&player->ships[idx_ship], 5); // Inicializar barco de 5 partes
                break;
            case 1:
                strcpy(player->ships[idx_ship].name, "Acorazado");
                inicializar_barco(&player->ships[idx_ship], 4); // Inicializar barco de 4 partes
                break;
            case 2:
                strcpy(player->ships[idx_ship].name, "Crucero");
                inicializar_barco(&player->ships[idx_ship], 3); // Inicializar barco de 3 partes
                break;
            case 3:
                strcpy(player->ships[idx_ship].name, "Destructor");
                inicializar_barco(&player->ships[idx_ship], 3); // Inicializar barco de 3 partes
                break;
            case 4:
                strcpy(player->ships[idx_ship].name, "Fragata");
                inicializar_barco(&player->ships[idx_ship], 2); // Inicializar barco de 2 partes
                break;
        }
    }
}

void inicializar_barco(struct ship *barco, int size) {
    barco-> size = size;
    barco->direction = 'U'; // No definido
    barco->vivo = true; // Barco está vivo al inicio

    // Reservar memoria para el estado del barco.
    barco->status = (int **)malloc(size * sizeof(int *));
    for (int s_part = 0; s_part < size; s_part++) {
        barco->status[s_part] = (int *)malloc(3 * sizeof(int)); // 3 columnas para x, y y estado
        barco->status[s_part][CC_FILA] = -1; // Inicializar coordenadas x a -1
        barco->status[s_part][CC_COLUMNA] = -1; // Inicializar coordenadas y a -1
        barco->status[s_part][CC_STATUS] = 0; // Inicializar estado a 0 (agua)
    }
}

bool posicion_barco(struct player *player, int index, int s_part, int fila, int columna) {
    // Verifica si la parte del barco esta en la posicion (x, y)
    return player->ships[index].status[s_part][0] == fila
        && player->ships[index].status[s_part][1] == columna;
}

bool posicion_barco_enemy(struct player *player, int index, int s_part, struct player *enemy) {
    return enemy->ships[index].status[s_part][CC_FILA] == player->last_input_fila
        && enemy->ships[index].status[s_part][CC_COLUMNA] == player->last_input_columna;
}

bool casilla_saludable(struct player *enemy, int index, int s_part) {
    return enemy->ships[index].status[s_part][CC_STATUS] == SHIP_STER || enemy->ships[index].status[s_part][CC_STATUS] == SHIP_BODY;
}

void hundir_barco_buff(struct player *player, int index, struct player *enemy) {
    for (int s_part = 0; s_part < enemy->ships[index].size; s_part++) {
        if (casilla_saludable(enemy, index, s_part)) {
            enemy->ships[index].status[s_part][CC_STATUS] += 2; // Cambiar estado a dañado
            player->enemy_hit_parts++; // Incrementar partes alcanzadas
            player->aciertos_por_turno++; // Incrementar aciertos por turno
        }
    }
    hundido(player, enemy); // Verifica si el barco está hundido
}

void hundido(struct player *player, struct player *enemy) {
    for (int i = 0; i < NUM_SHIPS; i++) {
        if (enemy->ships[i].vivo) {
            bool hundido = true;
            for (int j = 0; j < enemy->ships[i].size; j++) {
                if (enemy->ships[i].status[j][2] != 3 && enemy->ships[i].status[j][2] != 4) {
                    hundido = false; // Si alguna parte no está dañada, no se hunde
                    break;
                }
            }
            if (hundido) {
                enemy->ships[i].vivo = false; // Barco hundido
                player->sunked_ships++;
                printf("El barco %d ha sido hundido.\n", i + 1);
                // Desactivar salvo si estaba activo
                if (enemy->salvo) {
                    enemy->salvo = false;
                    printf("El modo Salvo enemigo se "); color_txt(INFO_COLOR); printf("desactiva.\n");
                }
            }
        }
    }
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