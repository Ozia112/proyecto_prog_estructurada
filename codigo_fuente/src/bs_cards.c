#include "bs_cards.h" // libreria para poder usar funciones de efectos de cartas.

void disparar(struct player *player, struct player *enemy) {
    bool disparo_exitoso = false; // Variable para verificar si el disparo fue exitoso

    for (int idx_ship = 0; idx_ship < NUM_SHIPS; idx_ship++) { // Recorre todos los barcos enemigos
        for (int s_part = 0; s_part < enemy->ships[idx_ship].size; s_part++) { // Recorre todas las partes del barco
            if (posicion_barco(enemy, idx_ship, s_part, 
                                player->last_input_fila, 
                                player->last_input_columna)) {
                disparo_exitoso = true;

                // Guarda la última coordenada de disparo exitosa
                player->last_successful_shot_fila = player->last_input_fila;
                player->last_successful_shot_columna = player->last_input_columna;

                if (player->buff) {
                    // Modifica todo el barco a dañado(hundido)
                    mostrar_ultimo_disparo_exitoso(player);
                    hundir_barco_buff(player, idx_ship, enemy);

                } else {
                    // Modifica el estado de la parte del barco a dañada
                    enemy->ships[idx_ship].status[s_part][CC_STATUS] += 2;
                    mostrar_ultimo_disparo_exitoso(player);
                    pausa_consola(1.3);
                    player->enemy_hit_parts++;
                    player->aciertos_por_turno++;
                    hundido(player, enemy); // Verifica si el barco está hundido
                }
                break; // Salir del bucle si se encuentra una parte del barco
            }
        }
        
    }
    if (!disparo_exitoso) {
            color_txt(ERROR_COLOR);
            printf("Disparo fallido"); color_txt(DEFAULT_COLOR);
            printf(" en %c,%d! Disparaste al", 
                    player->last_input_fila + 'A',
                    player->last_input_columna + 1);
            color_txt(WATER_COLOR); printf(" agua.\n"); color_txt(DEFAULT_COLOR);
    }
}

void bombardea_fila(struct player *player, struct player *enemy) {
    // Recorre todos los barcos enemigos y daña las partes en la fila dada
    for (int idx_ship = 0; idx_ship < NUM_SHIPS; idx_ship++) {
        for (int s_part = 0; s_part < enemy->ships[idx_ship].size; s_part++) {
            if (enemy->ships[idx_ship].status[s_part][CC_FILA] == player->last_input_fila) {
                if (casilla_saludable(enemy, idx_ship, s_part)) {
                    if (player->buff) {
                        printf("Disparo exitoso en %c,%d!\n", player->last_input_fila + 'A', enemy->ships[idx_ship].status[s_part][CC_COLUMNA] + 1);
                        hundir_barco_buff(player, idx_ship, enemy);
                        //printf("Haz hundido el barco!\n");
                        hundido(enemy, player); // Verifica si el barco está hundido
                        pausa_consola(1.3);
                        break; // Salir del bucle si se hunde el barco
                    } else {
                    enemy->ships[idx_ship].status[s_part][CC_STATUS] += 2; // Modifica el estado de la parte del barco a dañada
                    player->enemy_hit_parts++; // Incrementa el contador de partes dañadas del enemigo
                    player->aciertos_por_turno++; // Incrementa el contador de aciertos por turno
                    printf("Disparo exitoso en %c,%d\n", player->last_input_fila + 'A', enemy->ships[idx_ship].status[s_part][CC_COLUMNA] + 1);
                    hundido(enemy, player); // Verifica si el barco está hundido
                    pausa_consola(1.3);
                    }
                    player->last_successful_shot_fila = player->last_input_fila; // Guarda la última fila disparada
                }
            }
        }
    }
}

void bombardea_columna(struct player *player, struct player *enemy) {
    // Recorre todos los barcos enemigos y daña las partes en la columna dada
    for (int idx_ship = 0; idx_ship < NUM_SHIPS; idx_ship++) {
        for (int s_part = 0; s_part < enemy->ships[idx_ship].size; s_part++) {
            if (enemy->ships[idx_ship].status[s_part][CC_COLUMNA] == player->last_input_columna) {
                if (casilla_saludable(enemy, idx_ship, s_part)) {
                    if (player->buff) {
                        printf("Disparo exitoso en %c,%d!\n", enemy->ships[idx_ship].status[s_part][CC_FILA] + 'A', player->last_input_columna + 1);
                        hundir_barco_buff(player, idx_ship, enemy);
                        hundido(enemy, player); // Verifica si el barco está hundido
                        break; // Salir del bucle si se hunde el barco
                    } else {
                        enemy->ships[idx_ship].status[s_part][CC_STATUS] += 2; // Modifica el estado de la parte del barco a dañada
                        player->enemy_hit_parts++; // Incrementa el contador de partes dañadas del enemigo
                        player->aciertos_por_turno++; // Incrementa el contador de aciertos por turno
                        printf("Disparo exitoso en %c,%d\n", enemy->ships[idx_ship].status[s_part][CC_FILA] + 'A', player->last_input_columna + 1);
                        hundido(enemy, player); // Verifica si el barco está hundido
                    }
                    player->last_successful_shot_columna = player->last_input_columna; // Guarda la última columna disparada
                }
            }
        }
    }
}

void revela(struct player *player, struct player *enemy) {
    // 1. Guardar todas las partes de barco no dañadas
    int posibles[TOTAL_SHIP_PARTS - player->enemy_hit_parts][CC_STATUS]; // Máximo 5 partes por barco
    int total = 0;
    int s, p;

    for (s = 0; s < NUM_SHIPS; s++) {
        struct ship *barco = &enemy->ships[s];
        for (p = 0; p < barco->size; p++) {
            // Si la parte no está dañada (1 = punta, 2 = cuerpo)
            if (barco->status[p][CC_STATUS] == SHIP_STER || barco->status[p][CC_STATUS] == SHIP_BODY) {
                posibles[total][0] = barco->status[p][CC_FILA]; // fila
                posibles[total][1] = barco->status[p][CC_COLUMNA]; // columna
                total++;
            }
        }
    }
    // 2. Elegir una coordenada aleatoria
    int idx = rand() % total;
    int fila = posibles[idx][0];
    int columna = posibles[idx][1];


    printf("Presione enter para revelar...\n");
    color_txt(INFO_COLOR);
    printf("---> ");
    color_txt(ERROR_COLOR);
    printf("(%c,%d)", fila + 'A', columna + 1);
    color_txt(INFO_COLOR);
    printf(" <---\n");
    color_txt(DEFAULT_COLOR);
    pausa_consola(1);
    
    printf("Presione enter para disparar...\n");
    getchar();
    for (s = 0; s < NUM_SHIPS; s++) {
        for (p = 0; p < enemy->ships[s].size; p++) {
            if (posicion_barco(enemy, s, p, fila, columna)) {
                // Modifica el estado de la parte del barco a dañada (sin validaciones)
                enemy->ships[s].status[p][CC_STATUS] += 2;
                break;
            }
        }
    }
    limpiar_pantalla();
    mostrar_turno_y_tablero_G(player, enemy);
    printf("Disparo exitoso en %c,%d!\n", fila + 'A', columna + 1);
    player->enemy_hit_parts++;
    hundido(enemy, player); // Verifica si el barco está hundido
}

void chequeo_fila(struct player *player, struct player *enemy) {
    player->chequeo_fila[player->last_input_fila] = true;
    player->contador_fila[player->last_input_fila] = barcos_en_fila(player, enemy);
}

void chequeo_columna(struct player *player, struct player *enemy) {
    player->chequeo_columna[player->last_input_columna] = true;
    player->contador_columna[player->last_input_columna] = barcos_en_columna(player, enemy);
}

void activar_salvo(struct player *player) {
    player->salvo = true;
}

void desactivar_salvo(struct player *player) {
    player->salvo = false;
}

void torre_ventaja(struct player *player) {
    player->buff = true;
}

void mover_barco_adelante(struct player *player, int id_barco) {
    struct ship *ship_i = &player->ships[id_barco];
    int prev_pos[ship_i->size][2];
    int i;

    // Guardar la posición anterior del barco
    for (i = 0; i < ship_i->size; i++) {
        prev_pos[i][0] = ship_i->status[i][0];
        prev_pos[i][1] = ship_i->status[i][1];
    }

    if (ship_i->direction == 'E') {
        ship_i->status[0][1] ++;
    // Mover barco hacia el oeste
    } else if (ship_i->direction == 'O') {
        ship_i->status[0][1] --;
    // Mover barco hacia el sur
    } else if (ship_i->direction == 'S') {
        ship_i->status[0][0] ++;
    // Mover barco hacia el norte
    } else if (ship_i->direction == 'N') {
        ship_i->status[0][0] --;
    } else {
        return; // No se puede mover el barco
    }

    // Mover el resto del barco
    for (i = 1; i < ship_i->size; i++) {
        ship_i->status[i][0] = prev_pos[i - 1][0];
        ship_i->status[i][1] = prev_pos[i - 1][1];
    }
}