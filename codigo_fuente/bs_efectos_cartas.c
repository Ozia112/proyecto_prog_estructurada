#include "bs_console_utils.h" // libreria para poder usar la funcion limpiar y cambio de color.
#include "bs_efectos_cartas.h" // libreria para poder usar funciones de efectos de cartas.
#include "bs_ui.h" // libreria para poder usar funciones de UI.
#include "bs_logic.h" // libreria para poder usar funciones de logica.
#include <windows.h> // libreria para poder usar la funcion Sleep.
#include <stdio.h> // libreria para poder usar la funcion printf.

void disparar(struct player *player_i, struct player *enemy_i, int fila, int columna) {
    for (int i = 0; i < NUM_SHIPS; i++) {
        for (int j = 0; j < enemy_i->ships[i].size; j++) {
            if (player_i->buff) {
                for (int k = 0; k < enemy_i->ships[i].size; k++) {
                    // Solo daña si no está ya dañado
                    if (enemy_i->ships[i].status[k][2] == 1 || enemy_i->ships[i].status[k][2] == 2) {
                        // 3 = SHIP_STER, 4 = SHIP_BODY
                        if (enemy_i->ships[i].status[k][3] == 1) {
                            enemy_i->ships[i].status[k][2] = 3;
                        } else if (enemy_i->ships[i].status[k][3] == 2) {
                            enemy_i->ships[i].status[k][2] = 4;
                        }
                        player_i->enemy_hit_parts++;
                    }
                }
            } else {
                if (enemy_i->ships[i].status[j][0] == fila && enemy_i->ships[i].status[j][1] == columna) {
                    // Modifica el estado de la parte del barco a dañada (sin validaciones)
                    enemy_i->ships[i].status[j][2] += 2;
                    player_i->enemy_hit_parts++;
                }
            }
            
        }
    }
}

void bombardea_fila(struct player *player_i, struct player *enemy_i, int fila) {
    // Verifica si el jugador tiene su barco de 4 casillas a flote
    bool barco_cuatro_aflote = true;
    int casillas_buenas = 4;
    for (int i = 0; i < player_i->ships[1].size; i++) {
        if (player_i->ships[1].status[i][2] == 3 || player_i->ships[1].status[i][2] == 4) { // 3 o 4 = no dañado
            casillas_buenas--;
        }
        if (casillas_buenas == 0) {
            barco_cuatro_aflote = false; // Barco de 4 casillas no está a flote
            break;
        }
    }

    if (barco_cuatro_aflote) {
        // Recorre todos los barcos enemigos y daña las partes en la fila dada
        for (int s = 0; s < NUM_SHIPS; s++) {
            for (int p = 0; p < enemy_i->ships[s].size; p++) {
                if (player_i->buff) {
                    // Si hay buff, si alguna parte del barco está en la fila, hunde todo el barco
                    if (enemy_i->ships[s].status[p][0] == fila && (enemy_i->ships[s].status[p][2] == 1 || enemy_i->ships[s].status[p][2] == 2)) {
                        for (int k = 0; k < enemy_i->ships[s].size; k++) {
                            if (enemy_i->ships[s].status[k][2] == 1 || enemy_i->ships[s].status[k][2] == 2) {
                                // 3 = SHIP_STER, 4 = SHIP_BODY
                                if (enemy_i->ships[s].status[k][3] == 1) {
                                    enemy_i->ships[s].status[k][2] = 3;
                                } else if (enemy_i->ships[s].status[k][3] == 2) {
                                    enemy_i->ships[s].status[k][2] = 4;
                                }
                                player_i->enemy_hit_parts++;
                            }
                        }
                        break; // Ya hundió el barco, no es necesario seguir revisando sus partes
                    }
                } else {
                    if (enemy_i->ships[s].status[p][0] == fila && enemy_i->ships[s].status[p][2] == 1) {
                        enemy_i->ships[s].status[p][2] += 2;
                        player_i->enemy_hit_parts++;
                    } else if (enemy_i->ships[s].status[p][0] == fila && enemy_i->ships[s].status[p][2] == 2) {
                        enemy_i->ships[s].status[p][2] += 2;
                        player_i->enemy_hit_parts++;
                    }
                }
            }
        }
    } else {
        printf("Al parecer tu barco de 4 casillas no está a flote, por lo que no puedes bombardear la fila.\n");
        printf("Puedes disparar una vez");
        capturar_coordenada(player_i, enemy_i);
    }
}

void bombardea_columna(struct player *player_i, struct player *enemy_i, int columna) {
    // Verifica si el jugador tiene su barco de 5 casillas a flote
    bool barco_cinco_aflote = true;
    int casillas_buenas = 5;
    for (int i = 0; i < player_i->ships[0].size; i++) {
        if (player_i->ships[0].status[i][2] == 3 || player_i->ships[0].status[i][2] == 4) { // 3 o 4 = no dañado
            casillas_buenas--;
        }
        if (casillas_buenas == 0) {
            barco_cinco_aflote = false; // Barco de 5 casillas no está a flote
            break;
        }
    }

    if (barco_cinco_aflote) {
        // Recorre todos los barcos enemigos y daña las partes en la columna dada
        for (int s = 0; s < NUM_SHIPS; s++) {
            for (int p = 0; p < enemy_i->ships[s].size; p++) {
                if (player_i->buff) {
                    // Si hay buff, si alguna parte del barco está en la columna, hunde todo el barco
                    if (enemy_i->ships[s].status[p][1] == columna && (enemy_i->ships[s].status[p][2] == 1 || enemy_i->ships[s].status[p][2] == 2)) {
                        for (int k = 0; k < enemy_i->ships[s].size; k++) {
                            if (enemy_i->ships[s].status[k][2] == 1 || enemy_i->ships[s].status[k][2] == 2) {
                                // 3 = SHIP_STER, 4 = SHIP_BODY
                                if (enemy_i->ships[s].status[k][3] == 1) {
                                    enemy_i->ships[s].status[k][2] = 3;
                                } else if (enemy_i->ships[s].status[k][3] == 2) {
                                    enemy_i->ships[s].status[k][2] = 4;
                                }
                                player_i->enemy_hit_parts++;
                            }
                        }
                        break; // Ya hundió el barco, no es necesario seguir revisando sus partes
                    }
                } else {
                    if (enemy_i->ships[s].status[p][1] == columna && enemy_i->ships[s].status[p][2] == 1) {
                        enemy_i->ships[s].status[p][2] += 2;
                        player_i->enemy_hit_parts++;
                    } else if (enemy_i->ships[s].status[p][1] == columna && enemy_i->ships[s].status[p][2] == 2) {
                        enemy_i->ships[s].status[p][2] += 2;
                        player_i->enemy_hit_parts++;
                    }
                }
            }
        }
    } else {
        printf("Al parecer tu barco de 5 casillas no está a flote, por lo que no puedes bombardear la columna.\n");
        printf("Puedes disparar una vez");
        capturar_coordenada(player_i, enemy_i);
    }
}

void revela(struct player *player_i, struct player *enemy_i) {
}

void chequeo_fila(struct player *player_i, struct player *enemy_i, int fila) {
    player_i->chequeo_fila[fila] = true;
}

void chequeo_columna(struct player *player_i, struct player *enemy_i, int columna) {
    player_i->chequeo_columna[columna] = true;
}

void activar_salvo(struct player *player_i) {
    player_i->salvo = true;
}

void desactivar_salvo(struct player *player_i) {
    player_i->salvo = false;
}

void torre_ventaja(struct player *player_i) {
    player_i->buff = true;
}

void tira_toma(struct player *player_i, struct player *enemy_i, struct cartas *cartas) {
    imprimirTableroGuerra(enemy_i, player_i);
    capturar_coordenada(enemy_i, player_i);
    Sleep(1000);
    limpiar_pantalla();
    printf("Toma otra carta.\n");
    sacar_carta(player_i, enemy_i, cartas);
}

void mover_barco_adelante(struct player *player_i, int id_barco) {
    struct ship *ship_i = &player_i->ships[id_barco];
    int i;
    if (ship_i->direction == 'E' && validar_movimiento(player_i, ship_i)) {
        // Mover barco hacia el este
        for(i = 0; i < ship_i->size - 1; i ++) {
            ship_i->status[i][1] ++;
        }
    // Mover barco hacia el oeste
    } else if (ship_i->direction == 'O' && validar_movimiento(player_i, ship_i)) {
        for(i = 0; i < ship_i->size - 1; i++) {
            ship_i->status[i][1] --;
        }
    // Mover barco hacia el sur
    } else if (ship_i->direction == 'S' && validar_movimiento(player_i, ship_i)) {
        for(i = 0; i < ship_i->size - 1; i++) {
            ship_i->status[i][0] ++;
        }
    // Mover barco hacia el norte
    } else if (ship_i->direction == 'N' && validar_movimiento(player_i, ship_i)) {
        for(i = 0; i < ship_i->size - 1; i++) {
            ship_i->status[i][0] --;
        }
    }
}

void revelar_casilla_barco(struct player *enemy_i) {
    // 1. Guardar todas las partes de barco no dañadas
    int posibles[NUM_SHIPS * 5][2]; // Máximo 5 partes por barco
    int total = 0;
    int s, p;

    for (s = 0; s < NUM_SHIPS; s++) {
        struct ship *barco = &enemy_i->ships[s];
        for (p = 0; p < barco->size; p++) {
            // Si la parte no está dañada (1 = punta, 2 = cuerpo)
            if (barco->status[p][2] == 1 || barco->status[p][2] == 2) {
                posibles[total][0] = barco->status[p][0]; // fila
                posibles[total][1] = barco->status[p][1]; // columna
                total++;
            }
        }
    }

    // 2. Elegir una coordenada aleatoria
    srand((unsigned int)time(NULL));
    int idx = rand() % total;
    int fila = posibles[idx][0];
    int columna = posibles[idx][1];

    // 3. Mostrar la coordenada revelada
    printf("Para revelar un barco enemigo, seleccione con el cursor el siguiente texto:\n");
    color_txt(INFO_COLOR);
    printf("---> ");
    color_txt(INV_COLOR);
    printf("(%d,%c)\n", fila + 1, columna + 'A');
    color_txt(INFO_COLOR);
    printf(" <---\n");
    color_txt(DEFAULT_COLOR);

    // Aquí debe estar la función de disparo.
}