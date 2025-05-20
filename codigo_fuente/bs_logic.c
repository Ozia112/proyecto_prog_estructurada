#include "bs_common.h" // libreria para poder usar definiciones comunes.
#include "bs_logic.h" // libreria para poder usar funciones de logica.
#include "bs_console_utils.h" // libreria para poder usar la funcion limpiar y cambio de color.
#include "bs_ui.h" // libreria para poder usar funciones de UI.
#include "bs_efectos_cartas.h" // libreria para poder usar funciones de efectos de cartas.
#include <time.h> // libreria para poder usar la funcion time.
#include <stdio.h> // libreria para poder usar la funcion printf.
#include <stdlib.h> // libreria para poder usar la funcion system.
#include <string.h> // libreria para poder usar la funcion strcspn.
#include <windows.h> // libreria para poder usar la funcion Sleep.s

void inicializar_barco(struct ship *barco, int size) {
    barco-> size = size;
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

void hundido(struct player *enemy_i, struct player *player_i) {
    for (int i = 0; i < NUM_SHIPS; i++) {
        if (enemy_i->ships[i].vivo) {
            bool hundido = true;
            for (int j = 0; j < enemy_i->ships[i].size; j++) {
                if (enemy_i->ships[i].status[j][2] != 3 && enemy_i->ships[i].status[j][2] != 4) {
                    hundido = false; // Si alguna parte no está dañada, no se hunde
                    break;
                }
            }
            if (hundido) {
                enemy_i->ships[i].vivo = false; // Barco hundido
                enemy_i->sunked_ships++;
                printf("El barco %d ha sido hundido.\n", i + 1);
                // Desactivar salvo si estaba activo
                if (enemy_i->salvo) {
                    enemy_i->salvo = false;
                    printf("El barco %d ha sido hundido, el modo Salvo se desactiva.\n", i + 1);
                }
            }
        }
    }
}

void inicializar_jugador(struct player *player) {

    // Asignar el nombre al jugador, validando que no sea vacío y no exceda 20 caracteres.
    solicitar_nombre(player);

    // Inicializar estado de jugador.
    player->placed_ships = 0;
    player->enemy_hit_parts = 0;
    player->sunked_ships = 0;
    player->enemy_hit_parts = 0;
    player->torres_acumuladas = 0;
    player->salvo = false;
    player->buff = false;
    
    // chequeo_fila y chequeo_columna inicializados a false.
    for (int i = 0; i < BOARD_SIZE; i++) {
        player->chequeo_fila[i] = false;
        player->chequeo_columna[i] = false;
    }

    // Inicializar barcos.
    inicializar_flota(player);
    inicializar_cartas(player);
}

void inicializar_flota(struct player *player) {
    // Inicializar barcos con diferentes
    inicializar_barco(&player->ships[0], 5); // 5 cells
    inicializar_barco(&player->ships[1], 4); // 4 cells
    inicializar_barco(&player->ships[2], 3); // 3 cells
    inicializar_barco(&player->ships[3], 3); // 3 cells
    inicializar_barco(&player->ships[4], 2); // 2 cells
}

void inicializar_cartas(struct player *player) {
    // Inicializar cartas con sus IDs, nombres, probabilidades y descripciones
    for (int i = 0; i < NUM_CARTAS; i++) {
        player->cartas[i].id = i + 1;

        switch (i + 1) {
            case 1:
                strcpy(player->cartas[i].nombre, "Dispara 1 tiro");
                strcpy(player->cartas[i].descripcion, "Inserta coordenadas donde desees disparar.");
                player->cartas[i].peso = 7;
                break;
            case 2:
                strcpy(player->cartas[i].nombre, "Dispara 2 tiros");
                strcpy(player->cartas[i].descripcion, "Inserta coordenadas donde desees disparar. Hazlo de nuevo.");
                player->cartas[i].peso = 5;
                break;
            case 3:
                strcpy(player->cartas[i].nombre, "Dispara 3 tiros");
                strcpy(player->cartas[i].descripcion, "Inserta coordenadas donde desees disparar. Hazlo dos veces mas.");
                player->cartas[i].peso = 2;
                break;
            case 4:
                strcpy(player->cartas[i].nombre, "Bombardea una fila");
                strcpy(player->cartas[i].descripcion, "Si tienes tu buque de 4 casillas a flote, elige un numero y bombardea esa fila entera.");
                player->cartas[i].peso = 1;
                break;
            case 5:
                strcpy(player->cartas[i].nombre, "Bombardea una columna");
                strcpy(player->cartas[i].descripcion, "Si tienes tu buque de 5 casillas a flote, elige una letra y bombardea esa columna entera.");
                player->cartas[i].peso = 1;
                break;
            case 6:
                strcpy(player->cartas[i].nombre, "Revela");
                strcpy(player->cartas[i].descripcion, "Tu equipo de inteligencia logro descifrar la ubicacion de una parte de un barco.");
                player->cartas[i].peso = 1;
                break;
            case 7:
                strcpy(player->cartas[i].nombre, "Chequeo fila");
                strcpy(player->cartas[i].descripcion, "Tu equipo logro activar el sonar. Elige un numero y podras ver el numero de coordenadas en esa fila.");
                player->cartas[i].peso = 1;
                break;
            case 8:
                strcpy(player->cartas[i].nombre, "Chequeo columna");
                strcpy(player->cartas[i].descripcion, "Tu equipo logro activar el sonar. Elige una letra y podras ver el numero de coordenadas en esa columna.");
                player->cartas[i].peso = 1;
                break;
            case 9:
                strcpy(player->cartas[i].nombre, "Salvo");
                strcpy(player->cartas[i].descripcion, "Esta carta activa el modo Salvo. Dispara los mismos tiros que tengas en flota.");
                player->cartas[i].peso = 1;
                break;
            case 10:
                strcpy(player->cartas[i].nombre, "Torre de ventaja");
                strcpy(player->cartas[i].descripcion, "Acumula 4 tarjetas como esta para hundir instantaneamente los barcos.");
                player->cartas[i].peso = 4;
                break;
            case 11:
                strcpy(player->cartas[i].nombre, "Tira y toma");
                strcpy(player->cartas[i].descripcion, "Inserta coordenadas donde desees disparar y vuelve a generar una carta.");
                player->cartas[i].peso = 1;
                break;
            case 12:
                strcpy(player->cartas[i].nombre, "Mover hacia adelante");
                strcpy(player->cartas[i].descripcion, "Tu equipo logro obtener materiales para arreglar un motor momentaneamente.");
                player->cartas[i].peso = 1;
                break;
        }
    }
}

void calcular_probabilidades(struct player *player) {
    int suma_pesos = 0;
    for (int i = 0; i < NUM_CARTAS; i++) {
        suma_pesos += player->cartas[i].peso;
    }

    for (int i = 0; i < NUM_CARTAS; i++) {
        player->cartas[i].probabilidad = (float)player->cartas[i].peso / suma_pesos * 100.0; // Convertir a porcentaje
    }
}

void ajustar_probabilidades(struct player *player_1, struct player *player_2) {
    if (player_1->torres_acumuladas >= 4 || player_2->torres_acumuladas >= 4) {
        float total_redistribuir = player_1->cartas[9].probabilidad;  // Probabilidad de Torre de ventaja
        player_1->cartas[9].peso = 0;  // Establecer peso de Torre de ventaja a 0

        calcular_probabilidades(player_1);  // Recalcular probabilidades
        calcular_probabilidades(player_2);  // Recalcular probabilidades

        // Redistribuir la probabilidad entre las demás cartas proporcionalmente
        float factor = 1.0 + (total_redistribuir / (100.0 - total_redistribuir));
        for (int i = 0; i < NUM_CARTAS; i++) {
            if (i != 9) {  // No ajustar la probabilidad de Torre de ventaja
                player_1->cartas[i].probabilidad *= factor;
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
        return false; // No es una línea recta
    }
    
    return (dimension_actual == dimension_reuqerida);
    
}

bool validar_solapamiento(struct ship *ships, int num_ships_colocados, int filaInicio, int filaFin, int columnaInicio, int columnaFin, int size) {
    int i, x, y;

    // Recorre todas las posiciones que ocuparía el nuevo barco
    if (filaInicio == filaFin) {
        // Horizontal
        for (i = columnaInicio; (columnaInicio <= columnaFin) ? (i <= columnaFin) : (i >= columnaFin); (columnaInicio <= columnaFin) ? i++ : i--) {
            x = filaInicio;
            y = i;
            // Compara contra todos los barcos ya colocados
            for (int s = 0; s < num_ships_colocados; s++) {
                for (int j = 0; j < ships[s].size; j++) {
                    // Solo compara si la casilla ya fue asignada (no -1)
                    if (ships[s].status[j][0] == x && ships[s].status[j][1] == y && x != -1 && y != -1) {
                        return false; // Hay solapamiento
                    }
                }
            }
        }
    } else if (columnaInicio == columnaFin) {
        // Vertical
        for (i = filaInicio; (filaInicio <= filaFin) ? (i <= filaFin) : (i >= filaFin); (filaInicio <= filaFin) ? i++ : i--) {
            x = i;
            y = columnaInicio;
            for (int s = 0; s < num_ships_colocados; s++) {
                for (int j = 0; j < ships[s].size; j++) {
                    if (ships[s].status[j][0] == x && ships[s].status[j][1] == y && x != -1 && y != -1) {
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
                if (player_i->ships[i].status[j][2] == SHIP_BODY_D || player_i->ships[i].status[j][2] == SHIP_STER_D) {
                    color_txt(ERROR_COLOR);
                    printf("Ya disparaste en"); color_txt(DEFAULT_COLOR); printf(" %d,%c!\n", fila + 1, columna + 'A');
                    return false; // Ya disparado
                }
                return true; // Casilla válida para disparar
            }
        }
    }
    color_txt(ERROR_COLOR);
    printf("Disparo fallido"); color_txt(DEFAULT_COLOR); printf(" en %d,%c! Disparaste al", fila + 1, columna + 'A'); color_txt(WATER_COLOR); printf(" agua.\n");
    color_txt(DEFAULT_COLOR);
    return false; // La casilla no es parte de un barco (agua)
}

void colocar_barco_en_tablero(struct ship *ship_i, int filaInicio, int filaFin, int columnaInicio, int columnaFin) {
    int i, idx = 0;

    // Solo almacena la información en ship_i->status
    switch (ship_i->direction) {
        case 'E':
            for (i = columnaInicio; i <= columnaFin; i++, idx++) {
                ship_i->status[idx][0] = filaInicio;
                ship_i->status[idx][1] = i;
                ship_i->status[idx][2] = (idx == 0) ? SHIP_STER : SHIP_BODY;
            }
            break;
        case 'O':
            for (i = columnaInicio; i >= columnaFin; i--, idx++) {
                ship_i->status[idx][0] = filaInicio;
                ship_i->status[idx][1] = i;
                ship_i->status[idx][2] = (idx == 0) ? SHIP_STER : SHIP_BODY;
            }
            break;
        case 'S':
            for (i = filaInicio; i <= filaFin; i++, idx++) {
                ship_i->status[idx][0] = i;
                ship_i->status[idx][1] = columnaInicio;
                ship_i->status[idx][2] = (idx == 0) ? SHIP_STER : SHIP_BODY;
            }
            break;
        case 'N':
            for (i = filaInicio; i >= filaFin; i--, idx++) {
                ship_i->status[idx][0] = i;
                ship_i->status[idx][1] = columnaInicio;
                ship_i->status[idx][2] = (idx == 0) ? SHIP_STER : SHIP_BODY;
            }
            break;
    }
}


bool procesar_coordenadas(struct ship *ship_i, int filaInicio, int filaFin, int columnaInicio, int columnaFin, struct player *player_i) {
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
    if(!validar_solapamiento(player_i->ships, player_i->placed_ships, filaInicio, filaFin, columnaInicio, columnaFin, ship_i->size)) {
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

void decidir_primer_turno(struct player *p1, struct player *p2) {
    int primer_turno = (rand() % 2) + 1;
    printf("Decidiendo quien sera el primer jugador de forma aleatoria...\n");
    Sleep(1000);

    if (primer_turno == 1) {
        p1->turno = 1;
        p2->turno = 2;
        color_txt(INFO_COLOR); printf("%s ", p1->name); color_txt(DEFAULT_COLOR); printf("ha sido elegido para comenzar la partida\n");
        color_txt(INFO_COLOR); printf("%s ", p2->name); color_txt(DEFAULT_COLOR); printf("sera el segundo en jugar\n");
    } else {
        p1->turno = 2;
        p2->turno = 1;
        color_txt(INFO_COLOR); printf("%s ", p2->name); color_txt(DEFAULT_COLOR); printf("ha sido elegido para comenzar la partida\n");
        color_txt(INFO_COLOR); printf("%s ", p1->name); color_txt(DEFAULT_COLOR); printf("sera el segundo en jugar\n");
    }
    Sleep(1000);
    enter_continuar();
    limpiar_pantalla();
}

int obtener_id_aleatoria(struct player *player_i) {
    // Recalcular probabilidades antes de sacar una carta
    calcular_probabilidades(player_i);

    float numero_rand = (float)(rand() % 10000) / 100.0f; // Número aleatorio entre 0 y 100
    float acumulado = 0.0f;

    for (int i = 0; i < NUM_CARTAS; i++) {
        acumulado += player_i->cartas[i].probabilidad;
        if (numero_rand < acumulado) {
            return i;
        }
    }
    // Si no cayó en ningún rango, devuelve la última carta
    return NUM_CARTAS - 1;
}

void sacar_carta(struct player *player_i, struct player *enemy_i) {
    int carta_id = obtener_id_aleatoria(player_i);

    limpiar_pantalla();
    mostrar_turno_y_tablero(player_i, enemy_i);
    mostrar_info_carta(&player_i->cartas[carta_id]);
    switch (carta_id) {
    case 0:
        funcion_carta_1(player_i, enemy_i, carta_id);
        break;
    case 1:
        funcion_carta_2(player_i, enemy_i, carta_id);
        break;
    case 2:
        funcion_carta_3(player_i, enemy_i, carta_id);
    case 3: case 4: case 6: case 7:
        capturar_fila_columna(carta_id, player_i, enemy_i);
        if (carta_id == 6) {
            printf("La fila ha sido revelada.\n");
        } else if (carta_id == 7) {
            printf("La columna ha sido revelada.\n");
        }
        mostrar_turno_y_tablero(player_i, enemy_i);
        break;
    case 5:
        revela(enemy_i, player_i);
        break;
    case 8:
        activar_salvo(player_i);
        printf("\n¡Modo Salvo activado!\n");
        printf("Durante este turno NO disparas. En tu próximo turno, podrás disparar múltiples veces.\n");
        printf("Presiona enter para terminar el turno.\n");
        enter_continuar();
        limpiar_pantalla();
        break;
    case 9:
        if(player_i->torres_acumuladas < MAX_ID_10) {
            player_i->torres_acumuladas++;
            printf("Has acumulado una torre de ventaja. Acumula 4 para hundir instantaneamente los barcos enemigos.\n");
            // Reducir el peso de la carta Torre de ventaja
            if (player_i->cartas[9].peso > 0) player_i->cartas[9].peso--;
            ajustar_probabilidades(player_i, enemy_i);

        } else {
            torre_ventaja(player_i);
        }
        break;
    case 10:
        tira_toma(player_i, enemy_i);
        break;
    case 11:
        solicitar_barco(player_i, enemy_i);
        break;
    }

    if (carta_id != 9 && carta_id != 11) {
        enter_continuar();
        limpiar_pantalla();
    }
}

void funcion_carta_1(struct player *player_i, struct player *enemy_i, int carta_id) {
    int disparos = player_i->salvo ? (NUM_SHIPS - enemy_i->sunked_ships) : 1;
    for (int i = 0; i < disparos; i++) {
        if (i == 0) {
            printf("Dispara una vez.\n");
        } else {
            printf("Dispara de nuevo.\n");
        }
        Sleep(1000);
        mostrar_turno_y_tablero(player_i, enemy_i);
        capturar_coordenada(player_i, enemy_i);
        limpiar_pantalla();
    }
    enter_continuar();
    limpiar_pantalla();
}

void funcion_carta_2(struct player *player_i, struct player *enemy_i, int carta_id) {
    printf("Dispara una vez.\n");
    Sleep(1000);
    mostrar_turno_y_tablero(player_i, enemy_i);
    mostrar_info_carta(&player_i->cartas[carta_id]);
    capturar_coordenada(player_i, enemy_i);
    Sleep(1000);
    limpiar_pantalla();
    printf("Dispara de nuevo.\n");
    Sleep(1000);
    mostrar_turno_y_tablero(player_i, enemy_i);
    capturar_coordenada(player_i, enemy_i);
}

void funcion_carta_3(struct player *player_i, struct player *enemy_i, int carta_id) {
    for (int i = 0; i < 3; i++) {
        if (i == 0) {
            printf("Dispara una vez.\n");
        } else if (i == 1) {
            printf("Dispara de nuevo.\n");
        } else if (i == 2) {
            printf("Dispara una vez mas.\n");
        }
        Sleep(1000);
        mostrar_turno_y_tablero(player_i, enemy_i);
        capturar_coordenada(player_i, enemy_i);
        limpiar_pantalla();
    }
    enter_continuar();
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