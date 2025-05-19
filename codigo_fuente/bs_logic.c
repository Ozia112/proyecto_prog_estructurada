#include "bs_logic.h" // libreria para poder usar funciones de logica.
#include "bs_console_utils.h" // libreria para poder usar la funcion limpiar y cambio de color.
#include "bs_ui.h" // libreria para poder usar funciones de UI.
#include "bs_efectos_cartas.h" // libreria para poder usar funciones de efectos de cartas.
#include <time.h> // libreria para poder usar la funcion time.
#include <stdio.h> // libreria para poder usar la funcion printf.
#include <stdlib.h> // libreria para poder usar la funcion system.
#include <string.h> // libreria para poder usar la funcion strcspn.

void inicializar_barco(struct ship *barco, int size) {
    barco-> size = size;
    barco->orientation = 'U'; // No definido
    barco->direction = 'U'; // No definido
    barco->vivo = true; // Barco está vivo al inicio

    // Reservar memoria para el estado del barco.
    barco->status = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        barco->status[i] = (int *)malloc(3 * sizeof(int)); // 3 columnas para x, y y estado
        barco->status[i][0] = -1; // Inicializar coordenadas x a -1
        barco->status[i][1] = -1; // Inicializar coordenadas y a -1
        barco->status[i][2] = 0; // Inicializar estado a 0 (agua)
    }
}

void hundido(struct player *player_i) {
    for (int i = 0; i < NUM_SHIPS; i++) {
        bool todas_alcanzadas = true;
        for (int j = 0; j < player_i->ships[i].size; j++) {
            if (player_i->ships[i].status[j][2] != 3 && player_i->ships[i].status[j][2] != 4) {
                todas_alcanzadas = false; // Si alguna parte no está dañada, no se hunde
                break;
            }
        }
        player_i->ships[i].vivo = !todas_alcanzadas ? true : false;
    }
}

void inicializar_jugador(struct player *player) {

    // Asignar el nombre al jugador.
    solicitar_nombre(player->name, sizeof(player->name));

    // Inicializar estado de jugador.
    player->placed_ships = 0;
    player->enemy_hit_parts = 0;
    player->sunked_ships = 0;
    player->enemy_hit_parts = 0;
    player->torres_acumuladas = 0;
    
    // chequeo_fila y chequeo_columna inicializados a false.
    for (int i = 0; i < BOARD_SIZE; i++) {
        player->chequeo_fila[i] = false;
        player->chequeo_columna[i] = false;
    }

    // Inicializar barcos.
    inicializar_flota(player);
}

void inicializar_flota(struct player *player) {
    // Inicializar barcos con diferentes
    inicializar_barco(&player->ships[0], 5); // 5 cells
    inicializar_barco(&player->ships[1], 4); // 4 cells
    inicializar_barco(&player->ships[2], 3); // 3 cells
    inicializar_barco(&player->ships[3], 3); // 3 cells
    inicializar_barco(&player->ships[4], 2); // 2 cells
}

void inicializar_cartas(struct cartas *cartas) {
    // Inicializar cartas con sus IDs, nombres, probabilidades y descripciones
    for (int i = 0; i < NUM_CARTAS; i++) {
        cartas[i].id = i + 1;

        switch (i + 1) {
            case 1:
                strcpy(cartas[i].nombre, "Dispara 1 tiro");
                strcpy(cartas[i].descripcion, "Inserta coordenadas donde desees disparar.");
                cartas[i].probabilidad = 26.92;
                break;
            case 2:
                strcpy(cartas[i].nombre, "Dispara 2 tiros");
                strcpy(cartas[i].descripcion, "Inserta coordenadas donde desees disparar. Hazlo de nuevo.");
                cartas[i].probabilidad = 19.23;
                break;
            case 3:
                strcpy(cartas[i].nombre, "Dispara 3 tiros");
                strcpy(cartas[i].descripcion, "Inserta coordenadas donde desees disparar. Hazlo dos veces mas.");
                cartas[i].probabilidad = 7.69;
                break;
            case 4:
                strcpy(cartas[i].nombre, "Bombardea una fila");
                strcpy(cartas[i].descripcion, "Si tienes tu buque de 4 casillas a flote, elige un numero y bombardea esa fila entera.");
                cartas[i].probabilidad = 3.85;
                break;
            case 5:
                strcpy(cartas[i].nombre, "Bombardea una columna");
                strcpy(cartas[i].descripcion, "Si tienes tu buque de 5 casillas a flote, elige una letra y bombardea esa columna entera.");
                cartas[i].probabilidad = 3.85;
                break;
            case 6:
                strcpy(cartas[i].nombre, "Revela");
                strcpy(cartas[i].descripcion, "Tu equipo de inteligencia logro descifrar la ubicacion de una parte de un barco, subraya para revelar.");
                cartas[i].probabilidad = 3.85;
                break;
            case 7:
                strcpy(cartas[i].nombre, "Chequeo fila");
                strcpy(cartas[i].descripcion, "Tu equipo logro activar el sonar. Elige un numero y podras ver el numero de coordenadas en esa fila.");
                cartas[i].probabilidad = 3.85;
                break;
            case 8:
                strcpy(cartas[i].nombre, "Chequeo columna");
                strcpy(cartas[i].descripcion, "Tu equipo logro activar el sonar. Elige una letra y podras ver el numero de coordenadas en esa columna.");
                cartas[i].probabilidad = 3.85;
                break;
            case 9:
                strcpy(cartas[i].nombre, "Salvo");
                strcpy(cartas[i].descripcion, "Esta carta activa el modo Salvo. Dispara los mismos tiros que tengas en flota.");
                cartas[i].probabilidad = 3.85;
                break;
            case 10:
                strcpy(cartas[i].nombre, "Torre de ventaja");
                strcpy(cartas[i].descripcion, "Acumula 4 tarjetas como esta para hundir instantaneamente los barcos.");
                cartas[i].probabilidad = 15.38;
                break;
            case 11:
                strcpy(cartas[i].nombre, "Tira y toma");
                strcpy(cartas[i].descripcion, "Inserta coordenadas donde desees disparar y vuelve a generar una carta.");
                cartas[i].probabilidad = 3.85;
                break;
            case 12:
                strcpy(cartas[i].nombre, "Mover hacia adelante");
                strcpy(cartas[i].descripcion, "Tu equipo logro obtener materiales para arreglar un motor momentaneamente.");
                cartas[i].probabilidad = 3.85;
                break;
        }
    }
}

void ajustar_probabilidades(struct cartas *cartas, struct player *player_1, struct player *player_2) {
    if (player_1->torres_acumuladas >= 4 || player_2->torres_acumuladas >= 4) {
        float total_redistribuir = cartas[9].probabilidad;  // Probabilidad de Torre de ventaja
        cartas[9].probabilidad = 0.0;  // Establecer probabilidad de Torre de ventaja a 0
        
        // Redistribuir la probabilidad entre las demás cartas proporcionalmente
        float factor = 1.0 + (total_redistribuir / (100.0 - total_redistribuir));
        for (int i = 0; i < NUM_CARTAS; i++) {
            if (i != 9) {  // No ajustar la probabilidad de Torre de ventaja
                cartas[i].probabilidad *= factor;
            }
        }
    }
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

bool validar_solapamiento(struct ship *ship_i, int filaInicio, int filaFin, int columnaInicio, int columnaFin) {
    int i, x, y;

    // Determinar la orientación y dirección del barco
    if (filaInicio == filaFin) {
        ship_i->orientation = 'H'; // Horizontal
        if (columnaInicio <= columnaFin) {
            ship_i->direction = 'E'; // Este
            for (i = columnaInicio; i <= columnaFin; i++) {
                x = filaInicio;
                y = i;
                // Verificar si alguna parte del barco ya ocupa esta coordenada
                for (int j = 0; j < ship_i->size; j++) {
                    if (ship_i->status[j][0] == x && ship_i->status[j][1] == y) {
                        return false; // Hay solapamiento
                    }
                }
            }
        } else {
            ship_i->direction = 'O'; // Oeste
            for (i = columnaInicio; i >= columnaFin; i--) {
                x = filaInicio;
                y = i;
                for (int j = 0; j < ship_i->size; j++) {
                    if (ship_i->status[j][0] == x && ship_i->status[j][1] == y) {
                        return false; // Hay solapamiento
                    }
                }
            }
        }
    } else if (columnaInicio == columnaFin) {
        ship_i->orientation = 'V'; // Vertical
        if (filaInicio <= filaFin) {
            ship_i->direction = 'S'; // Sur
            for (i = filaInicio; i <= filaFin; i++) {
                x = i;
                y = columnaInicio;
                for (int j = 0; j < ship_i->size; j++) {
                    if (ship_i->status[j][0] == x && ship_i->status[j][1] == y) {
                        return false; // Hay solapamiento
                    }
                }
            }
        } else {
            ship_i->direction = 'N'; // Norte
            for (i = filaInicio; i >= filaFin; i--) {
                x = i;
                y = columnaInicio;
                for (int j = 0; j < ship_i->size; j++) {
                    if (ship_i->status[j][0] == x && ship_i->status[j][1] == y) {
                        return false; // Hay solapamiento
                    }
                }
            }
        }
    }
    return true; // No hay solapamiento
}

bool validar_estado_casilla(struct player *player_i, int fila, int columna) {
    for (int i = 0; i < NUM_SHIPS; i++) {
        for (int j = 0; j < player_i->ships[i].size; j++) {
            if (player_i->ships[i].status[j][0] == fila && player_i->ships[i].status[j][1] == columna) {
                if (player_i->ships[i].status[j][2] == SHIP_BODY + 2 || player_i->ships[i].status[j][2] == SHIP_STER + 2) {
                    return false; // Ya disparado
                }
            return true; // Casilla válida para disparar
            }
        }
    }
    printf("Disparo fallido en %d,%c!\n", fila + 1, columna + 'A');
    return false; // La casilla no es parte de un barco
}

void colocar_barco_en_tablero(struct ship *ship_i, int filaInicio, int filaFin, int columnaInicio, int columnaFin) {
    int i, idx = 0;

    // Solo almacena la información en ship_i->status
    if (ship_i->orientation == 'H') {
        if (ship_i->direction == 'E') {
            for (i = columnaInicio; i <= columnaFin; i++, idx++) {
                ship_i->status[idx][0] = filaInicio;
                ship_i->status[idx][1] = i;
                ship_i->status[idx][2] = (idx == 0) ? SHIP_STER : SHIP_BODY;
            }
        } else if (ship_i->direction == 'O') {
            for (i = columnaInicio; i >= columnaFin; i--, idx++) {
                ship_i->status[idx][0] = filaInicio;
                ship_i->status[idx][1] = i;
                ship_i->status[idx][2] = (idx == 0) ? SHIP_STER : SHIP_BODY;
            }
        }
    } else if (ship_i->orientation == 'V') {
        if (ship_i->direction == 'S') {
            for (i = filaInicio; i <= filaFin; i++, idx++) {
                ship_i->status[idx][0] = i;
                ship_i->status[idx][1] = columnaInicio;
                ship_i->status[idx][2] = (idx == 0) ? SHIP_STER : SHIP_BODY;
            }
        } else if (ship_i->direction == 'N') {
            for (i = filaInicio; i >= filaFin; i--, idx++) {
                ship_i->status[idx][0] = i;
                ship_i->status[idx][1] = columnaInicio;
                ship_i->status[idx][2] = (idx == 0) ? SHIP_STER : SHIP_BODY;
            }
        }
    }
}

bool procesar_coordenadas(struct ship *ship_i, int filaInicio, int filaFin, int columnaInicio, int columnaFin) {
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
    if(!validar_solapamiento(ship_i, filaInicio, filaFin, columnaInicio, columnaFin)) {
        color_txt(ERROR_COLOR);
        printf("Las coordenadas no son validas. Hay solapamiento con otro barco.\n");
        color_txt(DEFAULT_COLOR);
        return false;
    }    
    return true;
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
    nx = ship_i->status[0][0] + dx;
    ny = ship_i->status[0][1] + dy;

    // Validar rango en la matriz
    if(nx < 0 || ny < 0 || nx >= BOARD_SIZE || ny >= BOARD_SIZE) {
        return false;
    }

    // Validar solapamiento con otro barco
    for(s = 0; s < NUM_SHIPS; s++){
        for(k = 0; k < player_i->ships[s].size; k++) {
            if(player_i->ships[s].status[k][0] == nx && player_i->ships[s].status[k][1] == ny) {
                return false;
            }
        }
    }

    return true;
}

void decidir_primer_turno(struct player *p1, struct player *p2) {
    int primer_turno = (rand() % 2) + 1;
    printf("Decidiendo quien sera el primer jugador de forma aleatoria...\n");
    Sleep(1000);

    p1->turno = primer_turno;
    if (p1->turno == 1) {
        color_txt(INFO_COLOR); printf("%s ",p1->name); color_txt(DEFAULT_COLOR); printf(" ha sido elegido para comenzar la partida\n");
        p2->turno = 2;
    } else {
        color_txt(INFO_COLOR); printf("%s ",p2->name); color_txt(DEFAULT_COLOR); printf(" ha sido elegido para comenzar la partida\n");
        p2->turno = 1;
    }
    enter_continuar();
    limpiar_pantalla();
}

int obtener_id_aleatoria(struct cartas *cartas) {
    float numero_rand = (float)(rand() % 10000) / 100.0f; // Número aleatorio entre 0 y 100
    float acumulado = 0.0f;
    
    for (int i = 0; i < NUM_CARTAS; i++) {
        acumulado += cartas[i].probabilidad;
        if (numero_rand <= acumulado) {
            return cartas[i].id;
        }
    }
    
    return 0; // Valor por defecto si algo sale mal
}

void sacar_carta(struct player *player_i, struct player *enemy_i, struct cartas *cartas) {
    int carta_id = obtener_id_aleatoria(cartas);
    
    // Buscar y mostrar la información de la carta
    for (int i = 0; i < NUM_CARTAS; i++) {
        if (cartas[i].id == carta_id) {
            printf("\n¡Has sacado la carta: %s!\n", cartas[i].nombre);
            printf("Descripción: %s\n\n", cartas[i].descripcion);
            break;
        }
    }

    switch (carta_id) {
    case 1:
        if(player_i->salvo) {
            printf("Tienes el modo Salvo activado, puedes disparar %d veces.\n", NUM_SHIPS - enemy_i->sunked_ships);
            for (int i = 0; i < NUM_SHIPS - enemy_i->sunked_ships; i++) {
                imprimirTableroGuerra(enemy_i, player_i);
                capturar_coordenada(player_i, enemy_i);
                Sleep(1000);
                limpiar_pantalla();
                printf("Dispara de nuevo.\n");
                if (i < NUM_SHIPS - enemy_i->sunked_ships - 1) {
                    printf("Dispara una vez mas.\n");
                    imprimirTableroGuerra(enemy_i, player_i);
                    capturar_coordenada(player_i, enemy_i);
                    Sleep(1000);
                    limpiar_pantalla();
                }
            }
        } else {
            printf("Dispara una vez.\n");
            capturar_coordenada(player_i, enemy_i);
        }
        break;
    case 2:
        capturar_coordenada(player_i, enemy_i);
        Sleep(1000);
        limpiar_pantalla();
        printf("Dispara de nuevo.\n");
        imprimirTableroGuerra(enemy_i, player_i);
        capturar_coordenada(player_i, enemy_i);
        break;
    case 3:
        capturar_coordenada(player_i, enemy_i);
        Sleep(1000);
        limpiar_pantalla();
        printf("Dispara de nuevo.\n");
        imprimirTableroGuerra(enemy_i, player_i);
        capturar_coordenada(player_i, enemy_i);
        Sleep(1000);
        limpiar_pantalla();
        printf("Dispara una ultima vez.\n");
        imprimirTableroGuerra(enemy_i, player_i);
        capturar_coordenada(player_i, enemy_i);
        break;
    case 4:
        capturar_fila_columna(cartas, player_i, enemy_i);
        break;
    case 5:
        capturar_fila_columna(cartas, player_i, enemy_i);
        break;
    case 6:
        revela(player_i, enemy_i);
        break;
    case 7:
        capturar_fila_columna(cartas, player_i, enemy_i);
        break;
    case 8:
        capturar_fila_columna(cartas, player_i, enemy_i);
        break;
    case 9:
        activar_salvo(player_i);
        break;
    case 10:
        if(player_i->torres_acumuladas < MAX_ID_10) {
            player_i->torres_acumuladas++;
            printf("Has acumulado una torre de ventaja. Acumula 4 para hundir instantaneamente los barcos enemigos.\n");
            ajustar_probabilidades(cartas, player_i, enemy_i);
        } else {
            torre_ventaja(player_i);
        }
        break;
    case 11:
        tira_toma(player_i, enemy_i, cartas);
        break;
    case 12:
        solicitar_barco(player_i);
        break;
    }
}

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