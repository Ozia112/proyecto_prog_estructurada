#include "bs_ui.h" // libreria para poder usar funciones de UI.
#include "bs_console_utils.h" // libreria para poder usar la funcion limpiar y cambio de color.
#include "bs_logic.h" // libreria para poder usar funciones de logica.
#include "bs_efectos_cartas.h" // libreria para poder usar funciones de efectos de cartas.
#include <windows.h> // libreria para poder usar la funcion Sleep.
#include <string.h> // libreria para poder usar la funcion strcspn.
#include <ctype.h> // libreria para poder usar la funcion toupper.
#include <time.h> // libreria para poder usar la funcion time.
#include <stdio.h> // libreria para funciones de entrada/salida como stdin.

void pantalla_bienvenida() {
    // Logo para la pantalla de inicio.
	printf(" _______  _______  _______  _______  ___      ___      _______    __    _  _______  __   __  _______  ___     \n");
	printf("|  _    ||   _   ||       ||   _   ||   |    |   |    |   _   |  |  |  | ||   _   ||  | |  ||   _   ||   |    \n");
	printf("| |_|   ||  |_|  ||_     _||  |_|  ||   |    |   |    |  |_|  |  |   |_| ||  |_|  ||  |_|  ||  |_|  ||   |    \n");
	printf("|       ||       |  |   |  |       ||   |    |   |    |       |  |       ||       ||       ||       ||   |    \n");
	printf("|  _   | |       |  |   |  |       ||   |___ |   |___ |       |  |  _    ||       ||       ||       ||   |___ \n");
	printf("| |_|   ||   _   |  |   |  |   _   ||       ||       ||   _   |  | | |   ||   _   | |     | |   _   ||       | \n");
	printf("|_______||__| |__|  |___|  |__| |__||_______||_______||__| |__|  |_|  |__||__| |__|  |___|  |__| |__||_______| \n");
	
	enter_continuar(); // Pausa antes de continuar.
	limpiar_pantalla(); // Limpiar la pantalla después de mostrar el logo.
}

void menu_principal() {
    char opc = ' ';

	// Menu de opciones inicial.
	do{
		printf("Presione la tecla correspondiente a su opcion.\n");
		printf("Opciones:\n");
		printf("[A]: Iniciar partida\n");
        printf("[B]: Ver reglas.\n");
        printf("[C]: Salir\n");
		scanf(" %c", &opc);
        opc = toupper(opc); // Convertir a mayúscula para evitar problemas de comparación.
		switch(opc) {
		    // Caso en el que el usuario quiere iniciar partida.
            case 'A':
                limpiar_pantalla(); // Limpiar la pantalla antes de iniciar la partida.
                partida();
                break;
            // caso en el que el usuario quiere leer las reglas.
            case 'B':
                reglas();
                break;
            // Caso en el que el usuario quiere salir del programa (se especifica con un "case" porque sino el programa imprime "tecla inv�lida" cuando se presiona la c).
            case 'C':
                printf("Gracias por haber usado el programa :)");
                break;
            default:
                puts("¡Tecla invalida!");
                Sleep(1000); // funcion para tener demora en la ejecucion de la limpieza de la terminal.
                limpiar_pantalla(); // Limpiar la pantalla.
                break;
            }
	}while(opc != 'c' && opc != 'C');
}

void menu_por_turno(struct player *player_i, struct player *enemy_i) {
    srand(time(NULL));
    char opc = ' ';
    do {
        // Menu de opciones por turno.
    printf("Elija la opcion que desea realizar:\n");
    printf("[A]: Sacar carta\n");
    printf("[B]: Reporte de flota\n");
    printf("[C]: Reporte de barcos enemigos\n");

    scanf(" %c", &opc);
    limpiar_buffer_entrada(); // Limpiar el buffer de entrada antes de procesar la opción.
    opc = toupper(opc); // Convertir a mayúscula para evitar problemas de comparación.
    switch(opc) {
        case 'A':
            sacar_carta(player_i, enemy_i);
            opc = 'Z'; // Cambiar la opcion para salir del menu.
            break;
        case 'B':
            imprimirReporteBarcos(player_i, enemy_i);
            break;
        case 'C':
            // Logica reporte barcos enemigos
            break;
        default:
            color_txt(ERROR_COLOR);
            printf("¡Tecla invalida!\n");
            color_txt(DEFAULT_COLOR);
    }
    }while(opc != 'Z' && opc != 'z');
    limpiar_pantalla(); // Limpiar la pantalla después de salir del menú.
}

void solicitar_nombre(struct player *player) {
    do {
        printf("Introduce el nombre del jugador (max 20 caracteres): ");
        if (fgets(player->name, sizeof(player->name), stdin) == NULL) {
            color_txt(ERROR_COLOR);
            printf("Error de entrada. Intenta de nuevo.\n");
            color_txt(DEFAULT_COLOR);
            continue;
        }

        // Si no hay salto de línea, limpiar el buffer y repetir
        if (strchr(player->name, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // Limpiar buffer completamente
            color_txt(ERROR_COLOR);
            printf("El nombre no puede tener mas de 20 caracteres. Intenta de nuevo.\n");
            color_txt(DEFAULT_COLOR);
            continue;
        }

        // Eliminar salto de línea
        player->name[strcspn(player->name, "\n")] = '\0';

        // Validar longitud
        size_t len = strlen(player->name);
        if (len == 0) {
            color_txt(ERROR_COLOR);
            printf("El nombre no puede estar vacio. Intenta de nuevo.\n");
            color_txt(DEFAULT_COLOR);
            continue;
        }
        if (len > 20) {
            color_txt(ERROR_COLOR);
            printf("El nombre no puede tener mas de 20 caracteres. Intenta de nuevo.\n");
            color_txt(DEFAULT_COLOR);
            continue;
        }

        // Si pasa todas las validaciones, salir del ciclo
        break;
    } while (1);
}

void partida() {
    struct player player1, player2;
    struct cartas cartas[NUM_CARTAS];
    int alternancia_turno = 1; // Variable de alternancia de turnos.
    int i, j;

    limpiar_buffer_entrada(); // Limpiar el buffer de entrada antes de solicitar el nombre.
    printf("Jugador 1:\n");
    inicializar_jugador(&player1);
    limpiar_pantalla(); // Limpiar pantalla despues del primer jugador.
    printf("Jugador 2:\n");
    inicializar_jugador(&player2);
    limpiar_pantalla(); // Limpiar la pantalla después de inicializar jugadores.
    
    printf("Jugadores:\n");
    printf("Jugador 1:"); color_txt(INFO_COLOR); printf(" %s\n",player1.name); color_txt(DEFAULT_COLOR);
    printf("Jugador 2:"); color_txt(INFO_COLOR); printf(" %s\n",player2.name); color_txt(DEFAULT_COLOR);
    printf("Presione enter para ");  color_txt(INFO_COLOR); printf(" continuar.\n"); color_txt(DEFAULT_COLOR);
    getchar(); // Pausa antes de continuar.
    limpiar_pantalla(); // Limpiar la pantalla después de mostrar los nombres de los jugadores.
    
    // Colocar barcos para el jugador 1.
    colocar_barcos_jugador(&player1); // Colocar barcos para el jugador 1.

    // Colocar barcos para el jugador 2.
    printf("Ahora es turno de"); color_txt(INFO_COLOR); printf(" %s\n", player2.name); color_txt(DEFAULT_COLOR);
    enter_continuar(); // Pausa antes de continuar.

    colocar_barcos_jugador(&player2);

    // Elegir aleatoriamente quién inicia
    decidir_primer_turno(&player1, &player2);

    struct player *jugador_actual, *jugador_enemigo;
    if(player1.turno == 1) {
        jugador_actual = &player1;
        jugador_enemigo = &player2;
    } else {
        jugador_actual = &player2;
        jugador_enemigo = &player1;
    }

    do {
        printf("Turno de"); color_txt(INFO_COLOR); printf(" %s\n", jugador_actual->name); color_txt(DEFAULT_COLOR);
        imprimirTableroGuerra(jugador_enemigo, jugador_actual);
        menu_por_turno(jugador_actual, jugador_enemigo);
    
        // Mensaje de cambio de turno
        printf("Ahora es turno de %s\n", jugador_enemigo->name);
        enter_continuar();
        limpiar_pantalla(); // Limpiar la pantalla después de mostrar el turno.

        // Alternar punteros (esto es lo que realmente cambia el turno)
        struct player *temp = jugador_actual;
        jugador_actual = jugador_enemigo;
        jugador_enemigo = temp;
    
    } while(jugador_actual->enemy_hit_parts < VICTORYCONDITION && jugador_enemigo->enemy_hit_parts < VICTORYCONDITION);

    // Mensaje de victoria
    if(jugador_actual->enemy_hit_parts >= VICTORYCONDITION) {
            printf("%s ha ganado!\n", jugador_actual->name);
        } else if(jugador_enemigo->enemy_hit_parts >= VICTORYCONDITION) {
            printf("%s ha ganado!\n", jugador_enemigo->name);
        }
    liberar_flota(&player1); // Liberar memoria de la flota del jugador 1.
	liberar_flota(&player2); // Liberar memoria de la flota del jugador 2.

}

void capturar_coordenada(struct player *player_i, struct player *enemy_i) {
    int fila, columna;
    char columna_c;
    bool coordenadas_validas = false;

    while (!coordenadas_validas) {
        printf("Ingrese las coordenadas (ejemplo: 1 A): ");
        if (scanf(" %d %c", &fila, &columna_c) != 2) {
            color_txt(ERROR_COLOR);
            printf("Entrada invalida. Asegurese de ingresar un numero seguido de una letra. Intente de nuevo.\n");
            color_txt(DEFAULT_COLOR);
            limpiar_buffer_entrada();
            continue;
        }

        fila--; // Convertir a base 0
        columna_c = toupper(columna_c);

        if (columna_c >= 'A' && columna_c <= 'J') {
            columna = columna_c - 'A';
        } else {
            color_txt(ERROR_COLOR);
            printf("Columna invalida. Asegurese de ingresar una letra entre A y J. Intente de nuevo.\n");
            color_txt(DEFAULT_COLOR);
            limpiar_buffer_entrada();
            continue;
        }

        if (!validar_coordenadas_en_rango(fila, columna)) {
            color_txt(ERROR_COLOR);
            printf("Coordenadas fuera de rango. Intente de nuevo.\n");
            color_txt(DEFAULT_COLOR);
            limpiar_buffer_entrada();
            continue;
        }

        // Validar estado de la casilla antes de disparar
        if (!validar_estado_casilla(enemy_i, fila, columna)) {
            color_txt(ERROR_COLOR);
            printf("Ya has disparado a esa casilla. Elige otra.\n");
            color_txt(DEFAULT_COLOR);
            limpiar_buffer_entrada();
            continue;
        }

        coordenadas_validas = true;
    }
    // Llama a la función de disparo con fila y columna
    disparar(player_i, enemy_i, fila, columna);
    Sleep(1000); // Pausa de 1 segundo para mostrar el resultado del disparo.
    limpiar_pantalla(); // Limpiar la pantalla después de disparar.
}

void capturar_fila_columna(int carta_id, struct player *player_i, struct player *enemy_i) {
    char columna_c;
    int columna, fila;

    // Capturar fila o columna dependiendo de la carta
    if (carta_id == 4 || carta_id == 7) {
        // Capturar fila
        do {
            printf("Ingrese la fila a capturar (1-%d): ", BOARD_SIZE);
            if (scanf("%d", &fila) != 1) {
                color_txt(ERROR_COLOR);
                printf("Entrada invalida. Debe ser un numero.\n");
                color_txt(DEFAULT_COLOR);
                limpiar_buffer_entrada();
                fila = -1;
                continue;
            }
            if (fila < 1 || fila > BOARD_SIZE) {
                color_txt(ERROR_COLOR);
                printf("Fila invalida. Debe estar entre 1 y %d.\n", BOARD_SIZE);
                color_txt(DEFAULT_COLOR);
            }
        } while (fila < 1 || fila > BOARD_SIZE);
    } else if (carta_id == 5 || carta_id == 8) {
        // Capturar columna
        do {
            printf("Ingrese la columna a capturar (A-J): ");
            if (scanf(" %c", &columna_c) != 1) {
                color_txt(ERROR_COLOR);
                printf("Entrada invalida. Debe ser una letra.\n");
                color_txt(DEFAULT_COLOR);
                limpiar_buffer_entrada();
                columna = -1;
                continue;
            }
            columna_c = toupper(columna_c);
            columna = columna_c - 'A';
            if (columna < 0 || columna > 9) {
                color_txt(ERROR_COLOR);
                printf("Columna invalida. Debe estar entre A y J.\n");
                color_txt(DEFAULT_COLOR);
            }
        } while (columna < 0 || columna > 9);
    }

    switch (carta_id) {
        case 4:
            // Bombardea fila
            bombardea_fila(player_i, enemy_i, fila);
            break;
        case 5:
            // Bombardea columna
            bombardea_columna(player_i, enemy_i, columna);
            break;
        case 7:
            // Chequeo fila
            chequeo_fila(player_i, enemy_i, fila);
            break;
        case 8:
            // Chequeo columna
            chequeo_columna(player_i, enemy_i, columna);
            break;
        default:
            break;
    }
    imprimirTableroGuerra(enemy_i, player_i); // Imprimir el tablero del enemigo después de la acción.
}

void imprimirTablero(struct player *player_i) {
    int anchoTablero, relleno, consolaAncho;
    char caracter;
    int i, j, s, k, estado;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    
    // Obtener ancho de consola
    consolaAncho = 80; //Por defecto si no es posible
    if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        consolaAncho = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    // Calculando relleno para centrar
    anchoTablero = BOARD_SIZE * 2 + 4; // Dos caracteres por columna + 4 para las filas de nuemros y espaciado
    relleno = (consolaAncho - anchoTablero) / 2;

    // Encabezado de columnas (A B C D E F G H I J)
    printf("%*s", relleno,""); // Imprime relleno con espacios para centrar
    printf("   ");
    for (caracter = 'A'; caracter <= 'J'; caracter++) {
        printf("%c ", caracter);
    }
    printf("\n");

    // Dibujar cada fila
    for (i = 0; i < BOARD_SIZE; i++) {
        printf("%*s%.2d ", relleno,"", i + 1); // // Encabezado de filas(1 2 3 4 5 6 7 8 9 10) con relleno para centrar
        for (j = 0; j < BOARD_SIZE; j++) {
            estado = WATER; // Por defecto el estado es agua
            for (s = 0; s < NUM_SHIPS && estado == WATER; s++) {
                for (k = 0; k < player_i->ships[s].size; k++) {
                    if (player_i->ships[s].status[k][0] == i && player_i->ships[s].status[k][1] == j) //Buscando coincidencias en las coordenadas guardadas por los barcos y la matriz impresa
                    {
                        estado = player_i->ships[s].status[k][2];
                        break;
                    }
                    
                }
            }
            switch (estado) {
                case SHIP_STER:
                    color_txt(SHIP_COLOR);
                    printf("%c ", STER_PRINT);
                    color_txt(DEFAULT_COLOR);
                    break;
                case SHIP_BODY:
                    color_txt(SHIP_COLOR);
                    printf("%c ", BODY_PRINT);
                    color_txt(DEFAULT_COLOR);
                    break;
                case SHIP_STER_D:
                    color_txt(ERROR_COLOR);
                    printf("%c ", STER_PRINT);
                    color_txt(DEFAULT_COLOR);
                    break;
                case SHIP_BODY_D:
                    color_txt(ERROR_COLOR);
                    printf("%c ", BODY_PRINT);
                    color_txt(DEFAULT_COLOR);
                    break;
                default:
                    color_txt(WATER_COLOR);
                    printf("%c ", WATER_PRINT);
                    color_txt(DEFAULT_COLOR);
                    break;
            }
        }
        printf("\n");
    }
}

void imprimirTableroGuerra(struct player *enemy_i, struct player *player_i) {
    int anchoTablero, relleno, consolaAncho;
    char caracter;
    int i, j, s, k, estado;
    bool hay_chequeo_columna = false;
    int chequeo_fila[BOARD_SIZE] = {0};
    int chequeo_columna[BOARD_SIZE] = {0};
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // Inicializar chequeo_fila y chequeo_columna y contadores
    for (i = 0; i < BOARD_SIZE; i++) {
        // Chequeo de fila: contar solo si está activado
        if (player_i->chequeo_fila[i]) {
            for (j = 0; j < BOARD_SIZE; j++) {
                for (s = 0; s < NUM_SHIPS; s++) {
                    for (k = 0; k < enemy_i->ships[s].size; k++) {
                        if (enemy_i->ships[s].status[k][0] == i && enemy_i->ships[s].status[k][1] == j && (enemy_i->ships[s].status[k][2] == SHIP_BODY || enemy_i->ships[s].status[k][2] == SHIP_STER)) {
                            chequeo_fila[i]++;
                        }
                    }
                }
            }
        }
        // Chequeo de columna: contar solo si está activado
        if (player_i->chequeo_columna[i]) {
            for (j = 0; j < BOARD_SIZE; j++) {
                for (s = 0; s < NUM_SHIPS; s++) {
                    for (k = 0; k < enemy_i->ships[s].size; k++) {
                        if (enemy_i->ships[s].status[k][1] == i && enemy_i->ships[s].status[k][0] == j && (enemy_i->ships[s].status[k][2] == SHIP_BODY || enemy_i->ships[s].status[k][2] == SHIP_STER)) {
                            chequeo_columna[i]++;
                        }
                    }
               }
           }
       }
    }

    // Obtener ancho de consola
    consolaAncho = 80; //Por defecto si no es posible
    if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        consolaAncho = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    // Calculando relleno para centrar
    anchoTablero = BOARD_SIZE * 2 + 4; // Dos caracteres por columna + 4 para las filas de nuemros y espaciado
    relleno = (consolaAncho - anchoTablero) / 2;

    // Encabezado de columnas (A B C D E F G H I J)
    printf("%*s", relleno,""); // Imprime relleno con espacios para centrar
    printf("   ");
    for (caracter = 'A'; caracter <= 'J'; caracter++) {
        printf("%c ", caracter);
    }
    printf("\n");

    // Dibujar cada fila
    for (i = 0; i < BOARD_SIZE; i++) {
        printf("%*s%.2d ", relleno,"", i + 1); // Encabezado de filas
        for (j = 0; j < BOARD_SIZE; j++) {
            estado = WATER; // Por defecto el estado es agua
            for (s = 0; s < NUM_SHIPS && estado == WATER; s++) {
                for (k = 0; k < enemy_i->ships[s].size; k++) {
                    if (enemy_i->ships[s].status[k][0] == i && enemy_i->ships[s].status[k][1] == j) {
                        // Solo mostrar si está dañado (status == SHIP_BODY+2 o SHIP_STER+2)
                        if (enemy_i->ships[s].status[k][2] == SHIP_BODY_D) {
                            estado = SHIP_BODY_D;
                        } else if (enemy_i->ships[s].status[k][2] == SHIP_STER_D) {
                            estado = SHIP_STER_D;
                        }
                        break;
                    }
                }
            }
            switch (estado) {
                case SHIP_STER_D:
                    color_txt(ERROR_COLOR);
                    printf("%c ", STER_PRINT);
                    color_txt(DEFAULT_COLOR);
                    break;
                case SHIP_BODY_D:
                    color_txt(ERROR_COLOR);
                    printf("%c ", BODY_PRINT);
                    color_txt(DEFAULT_COLOR);
                    break;
                default:
                    color_txt(WATER_COLOR);
                    printf("%c ", WATER_PRINT);
                    color_txt(DEFAULT_COLOR);
                    break;
            }
        }
        // Mostrar chequeo de fila al final de la fila solo si está activado
        if (player_i->chequeo_fila[i]) {
            color_txt(SUCCESS_COLOR);
            printf(" %d", chequeo_fila[i]);
            color_txt(DEFAULT_COLOR);
        }
        printf("\n");
    }

    // Mostrar chequeo de columna (una sola línea debajo del tablero)
    for (i = 0; i < BOARD_SIZE; i++) {
        if (player_i->chequeo_columna[i]) {
            hay_chequeo_columna = true;
            break;
        }
    }
    if (hay_chequeo_columna) {
        printf("%*s   ", relleno, "");
        for (j = 0; j < BOARD_SIZE; j++) {
            if (player_i->chequeo_columna[j]) {
                color_txt(SUCCESS_COLOR);
                printf("%d ", chequeo_columna[j]);
                color_txt(DEFAULT_COLOR);
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void imprimirReporteBarcos(struct player *player_i, struct player *enemy_i) {
    int i, k;
    int dimension_maxima = 0;
    int ancho_col = 12; // Ancho fijo para cada barco

    limpiar_pantalla();
    printf("Turno de"); color_txt(INFO_COLOR); printf(" %s\n", player_i->name); color_txt(DEFAULT_COLOR);
    imprimirTableroGuerra(enemy_i, player_i);
    printf("\n");
    printf("Reporte de barcos:\n");

    // Encontrar el tamaño máximo de los barcos
    for (i = 0; i < NUM_SHIPS; i++) {
        if (player_i->ships[i].size > dimension_maxima) {
            dimension_maxima = player_i->ships[i].size;
        }
    }

    // Encabezado
    for (i = 0; i < NUM_SHIPS; i++) {
        printf("%*sBote %02d", ancho_col / 2 - 4, "", i + 1);
        printf("%*s", ancho_col - (ancho_col / 2 + 4), "");
    }
    printf("\n");

    // Dibujo de proa (/'\)
    for (i = 0; i < NUM_SHIPS; i++) {
        int estado = player_i->ships[i].status[0][2];
        if (i == 0) printf("%*s", ancho_col - 8, "");
        estado == SHIP_STER ? color_txt(SHIP_COLOR) : color_txt(ERROR_COLOR);
        printf("/'\\");
        color_txt(DEFAULT_COLOR);
        printf("%*s", ancho_col - 4, "");
    }
    printf("\n");

    // Cuerpo del barco
    for (k = 1; k < dimension_maxima; k++) {
        for (i = 0; i < NUM_SHIPS; i++) {
            if (k < player_i->ships[i].size) {
                int estado = player_i->ships[i].status[k][2];
                if (i == 0) printf("%*s", ancho_col - 8, "");
                if (estado == SHIP_BODY) {
                    color_txt(SHIP_COLOR);
                    printf("[_]");
                } else {
                    color_txt(ERROR_COLOR);
                    printf("[X]");
                }
                color_txt(DEFAULT_COLOR);
                printf("%*s", ancho_col - 4, "");
            } else {
                printf("%*s", ancho_col, "");
            }
        }
    printf("\n");
    }

    printf("[Z]: Regresar al menu.\n");
    char opc;
    scanf(" %c", &opc);
    opc = toupper(opc);
    if (opc == 'Z') {
        limpiar_pantalla();
        printf("Turno de"); color_txt(INFO_COLOR); printf(" %s\n", player_i->name); color_txt(DEFAULT_COLOR);
        imprimirTableroGuerra(enemy_i, player_i);
        printf("\n");
        menu_por_turno(player_i, enemy_i);
    } else {
        color_txt(ERROR_COLOR);
        printf("¡Tecla invalida!\n");
        color_txt(DEFAULT_COLOR);
    }
}

void ponerBarcos(struct ship *ship_i, struct player *player_i) {
    int filaInicio, filaFin, columnaInicio, columnaFin;
    char columnaInicio_c, columnaFin_c;
    int i;
    bool coordenadas_validas = false;

    while(!coordenadas_validas) {
        
        // Se le pide al usuario que ingrese las coordenadas iniciales y finales del barco.
        puts("Coordenada inicial del barco (fila 1-10 y columna A-J, separadas por un espacio): ");
        if (scanf(" %d %c", &filaInicio, &columnaInicio_c) != 2) {
            color_txt(ERROR_COLOR);
            printf("Entrada invalida. Asegurese de ingresar un numero seguido de una letra. Intente de nuevo.\n");
            color_txt(DEFAULT_COLOR);
            limpiar_buffer_entrada(); // Limpiar el buffer de entrada
            continue;
        }

        puts("Coordenadas finales del barco (mismo formato).");
        if (scanf(" %d %c", &filaFin, &columnaFin_c) != 2) {
            color_txt(ERROR_COLOR);
            printf("Entrada invalida. Asegurese de ingresar un numero seguido de una letra. Intente de nuevo.\n");
            color_txt(DEFAULT_COLOR);
            limpiar_buffer_entrada(); // Limpiar el buffer de entrada
            continue;
        }

        // Ajustar indices de fila(convertir a base 0)
        filaInicio--; filaFin--;
        
        // Transformar la letra de columna a mayúscula si no lo es.
        columnaInicio_c = toupper(columnaInicio_c);
        columnaFin_c = toupper(columnaFin_c);
        
        // Convertir la letra de columna a un número (A=0, B=1, ..., J=9)
        if (columnaInicio_c >= 'A' && columnaInicio_c <= 'J') {
            columnaInicio = columnaInicio_c - 'A';
        } else {
            color_txt(ERROR_COLOR);
            printf("Columna invalida. Asegurese de ingresar una letra entre A y J. Intente de nuevo.\n");
            color_txt(DEFAULT_COLOR);
            limpiar_buffer_entrada(); // Limpiar el buffer de entrada
            continue;
        }
        
        if (columnaFin_c >= 'A' && columnaFin_c <= 'J') {
            columnaFin = columnaFin_c - 'A';
        } else {
            color_txt(ERROR_COLOR);
            printf("Columna invalida. Asegurese de ingresar una letra entre A y J. Intente de nuevo.\n");
            color_txt(DEFAULT_COLOR);
            limpiar_buffer_entrada(); // Limpiar el buffer de entrada
            continue;
        }

        //Validaciones

        // Validar que las coordenadas esten dentro del rango permitido.
        if(!validar_coordenadas_en_rango(filaInicio, columnaInicio) || 
           !validar_coordenadas_en_rango(filaFin, columnaFin)) {
            color_txt(ERROR_COLOR);
            printf("Coordenadas fuera de rango. Asegurese de establecerlas entre 1 y 10 para filas y A-J para columnas. Intente de nuevo.\n");
            color_txt(DEFAULT_COLOR);
            limpiar_buffer_entrada(); // Limpiar el buffer de entrada
            continue;
        }

        // Procesar y validar las coordenadas del barco.
        if(procesar_coordenadas(ship_i, filaInicio, filaFin, columnaInicio, columnaFin, player_i)) {
            // Asignar direccion del barco.
            if (filaInicio == filaFin) {
                ship_i->direction = (columnaInicio < columnaFin) ? 'E' : 'O';
            } else if (columnaInicio == columnaFin) {
                ship_i->direction = (filaInicio < filaFin) ? 'S' : 'N';
            } else {
                ship_i->direction = 'U'; // No debería ocurrir si las validaciones son correctas
            }
            // Si las coordenadas son validas, colocar el barco en el tablero.
            colocar_barco_en_tablero(ship_i, filaInicio, filaFin, columnaInicio, columnaFin);
        
            // Incrementar el contador de barcos colocados.
            player_i->placed_ships++;
            coordenadas_validas = true; // Salir del bucle si todo es válido.
        } else {
            limpiar_buffer_entrada(); // Limpiar el buffer de entrada
        }
    if(coordenadas_validas) {
        color_txt(SUCCESS_COLOR);
        printf("Barco colocado exitosamente en");
        color_txt(INFO_COLOR); 
        printf(" (%d, %c)\n", filaInicio + 1, columnaInicio + 'A');
        color_txt(DEFAULT_COLOR);
        Sleep(1000); // Pausa para mostrar el mensaje de éxito.
        limpiar_pantalla(); // Limpiar la pantalla después de colocar el barco.
    }
    
    }
}

void colocar_barcos_jugador(struct player *player) {
    printf("Colocando barcos para"); color_txt(INFO_COLOR); printf(" %s\n", player->name); color_txt(DEFAULT_COLOR);
    for(int i = 0; i < NUM_SHIPS; i++) {
        limpiar_pantalla();
        printf("Colocando barcos de"); color_txt(INFO_COLOR); printf(" %s\n", player->name); color_txt(DEFAULT_COLOR);
        imprimirTablero(player);
        printf("Coloca tu barco de"); color_txt(INFO_COLOR); printf(" %d ",player->ships[i].size); color_txt(DEFAULT_COLOR);
        printf("celdas.\nBarco"); color_txt(INFO_COLOR); printf(" %d ",i + 1); color_txt(DEFAULT_COLOR);
        printf("de"); color_txt(INFO_COLOR); printf(" %d\n",NUM_SHIPS); color_txt(DEFAULT_COLOR);
        ponerBarcos(&player->ships[i], player);
    }
    imprimirTablero(player);
    printf("Barcos colocados correctamente. \n");
    Sleep(1000);
    limpiar_buffer_entrada();
    enter_continuar();
    limpiar_pantalla();
}

void solicitar_barco(struct player *player_i, struct player *enemy_i) {
    int i, barco_seleccionado;
    char opc;
    do {
        limpiar_pantalla();
        printf("Turno de"); color_txt(INFO_COLOR); printf(" %s\n", player_i->name); color_txt(DEFAULT_COLOR);
        imprimirTablero(player_i);    
        printf("Seleccione el barco que desea mover:\n");
        for (i = 0; i < NUM_SHIPS; i++) {
            if (validar_movimiento(player_i, &player_i->ships[i])) {
                // Mostrar solo barcos que se pueden mover
                printf("Barco %d: %d celdas\n", i + 1, player_i->ships[i].size);
            }
        }
        printf("[z]: No mover ningun barco.\n");
        scanf(" %c", &opc);
        opc = toupper(opc);
        switch (opc) {
            case 'Z':
                printf("No se movera ningun barco. Recibes una carta de"); color_txt(INFO_COLOR); printf(" disparo.\n");
                color_txt(DEFAULT_COLOR);
                capturar_coordenada(player_i, enemy_i);
                return;
            case '1': case '2': case '3': case '4': case '5':
                barco_seleccionado = opc - '1'; // Convertir a base 0
                if (validar_movimiento(player_i, &player_i->ships[barco_seleccionado])) {       
                    mover_barco_adelante(player_i, barco_seleccionado);
                    return;
                } else {
                        color_txt(ERROR_COLOR);
                    printf("No puedes mover ese barco.\n");
                    color_txt(DEFAULT_COLOR);
                    Sleep(2000); // Pausa para mostrar el mensaje de error.
                    break; // Salir del bucle si el barco no se puede mover
                }
                break;
            default:
                color_txt(ERROR_COLOR);
                printf("Opcion invalida. Intente de nuevo.\n");
                color_txt(DEFAULT_COLOR);
                Sleep(2000);
            }
        } while (1);
}

void reglas() {
    char opc;
    do {
        limpiar_pantalla();
        color_txt(INFO_COLOR);
        printf("=== REGLAS DEL JUEGO \"BATALLA NAVAL\" ===\n\n");
        color_txt(DEFAULT_COLOR);

        color_txt(SUCCESS_COLOR);
        printf("1. Cada jugador contara con una flota de barcos,\n");
        color_txt(DEFAULT_COLOR);
        printf("   la cual ordenara en una distribucion que considere conveniente para ocultarla de su rival.\n\n");

        color_txt(SUCCESS_COLOR);
        printf("2. El juego es por turnos.\n");
        color_txt(DEFAULT_COLOR);
        printf("   En cada turno se le proporcionara a cada jugador la posibilidad de usar una ");
        color_txt(INFO_COLOR); printf("carta"); color_txt(DEFAULT_COLOR);
        printf(" con diversos efectos sobre el tablero.\n\n");

        color_txt(SUCCESS_COLOR);
        printf("3. Las cartas disponibles son:\n");
        color_txt(DEFAULT_COLOR);
        printf("   ");
        color_txt(INFO_COLOR); printf("- Disparo: "); color_txt(DEFAULT_COLOR);
        printf("Dispara a una coordenada del tablero enemigo.\n   ");
        color_txt(INFO_COLOR); printf("- Bombardeo de fila: "); color_txt(DEFAULT_COLOR);
        printf("Bombardea una fila del tablero enemigo.\n   ");
        color_txt(INFO_COLOR); printf("- Bombardeo de columna: "); color_txt(DEFAULT_COLOR);
        printf("Bombardea una columna del tablero enemigo.\n   ");
        color_txt(INFO_COLOR); printf("- Revelar: "); color_txt(DEFAULT_COLOR);
        printf("Revela el estado de los barcos enemigos.\n   ");
        color_txt(INFO_COLOR); printf("- Chequeo de fila: "); color_txt(DEFAULT_COLOR);
        printf("Revela el estado de una fila del tablero enemigo.\n   ");
        color_txt(INFO_COLOR); printf("- Chequeo de columna: "); color_txt(DEFAULT_COLOR);
        printf("Revela el estado de una columna del tablero enemigo.\n   ");
        color_txt(INFO_COLOR); printf("- Salvo: "); color_txt(DEFAULT_COLOR);
        printf("Permite disparar a una coordenada del tablero enemigo sin que el enemigo pueda defenderse.\n   ");
        color_txt(INFO_COLOR); printf("- Torre de ventaja: "); color_txt(DEFAULT_COLOR);
        printf("Permite disparar a una coordenada y revela el estado de la fila y columna del barco.\n   ");
        color_txt(INFO_COLOR); printf("- Revelar casilla aleatoria: "); color_txt(DEFAULT_COLOR);
        printf("Permite revelar una casilla aleatoria en la que haya un barco enemigo.\n\n");

        color_txt(SUCCESS_COLOR);
        printf("4. El objetivo del juego es ");
        color_txt(INFO_COLOR); printf("hundir todos los barcos del enemigo"); color_txt(DEFAULT_COLOR);
        printf(" antes de que el enemigo hunda los tuyos.\n\n");

        color_txt(SUCCESS_COLOR);
        printf("5. Un barco se considera hundido cuando ");
        color_txt(INFO_COLOR); printf("todas sus partes han sido alcanzadas."); color_txt(DEFAULT_COLOR);
        printf("\n\n");

        color_txt(ERROR_COLOR);
        printf(" PROHIBIDO\n");
        color_txt(DEFAULT_COLOR);
        printf("   ");
        color_txt(ERROR_COLOR); printf("- No puedes colocar barcos fuera del tablero.\n"); color_txt(DEFAULT_COLOR);
        printf("   ");
        color_txt(ERROR_COLOR); printf("- No puedes sobreponer barcos.\n"); color_txt(DEFAULT_COLOR);
        printf("   ");
        color_txt(ERROR_COLOR); printf("- No puedes disparar dos veces a la misma casilla.\n"); color_txt(DEFAULT_COLOR);
        printf("   ");
        color_txt(ERROR_COLOR); printf("- No puedes mover barcos una vez colocados.\n\n"); color_txt(DEFAULT_COLOR);

        color_txt(INFO_COLOR);
        printf("Consejos:\n");
        color_txt(DEFAULT_COLOR);
        printf("   - Piensa estrategicamente la ubicacion de tus barcos.\n");
        printf("   - Aprovecha las cartas especiales para obtener ventaja.\n");
        printf("   - Recuerda que la informacion revelada por cartas es temporal.\n\n");

        color_txt(SUCCESS_COLOR);
        printf("[Z]: Regresar al menu.\n");
        color_txt(DEFAULT_COLOR);

        scanf(" %c", &opc);
        opc = toupper(opc);
        limpiar_buffer_entrada();
    } while (opc != 'Z');
    limpiar_pantalla();
    menu_principal();
}

void mostrar_turno_y_tablero(struct player *player_i, struct player *enemy_i) {
    limpiar_pantalla(); // Limpiar la pantalla antes de mostrar el turno y tablero.
    printf("Turno de"); color_txt(INFO_COLOR); printf(" %s\n", player_i->name); color_txt(DEFAULT_COLOR);
    imprimirTableroGuerra(enemy_i, player_i); // Imprimir el tablero del enemigo.
}

void mostrar_info_carta(struct cartas *carta) {
    printf("Te ha salido la carta:"); color_txt(INFO_COLOR); printf(" %s\n", carta->nombre); color_txt(DEFAULT_COLOR);
    printf("Descripcion: %s\n", carta->descripcion);
}

void enter_continuar() {
    printf("Presione enter para ");  color_txt(INFO_COLOR); printf("continuar.\n"); color_txt(DEFAULT_COLOR);
    getchar(); // Pausa antes de continuar.
}
