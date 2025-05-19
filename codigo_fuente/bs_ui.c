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
	
	printf("Presione cualquier \"enter\" para continuar");

	getchar();
	limpiar_pantalla(); // Limpiar la pantalla después de mostrar el logo.
}

void menu_principal() {
    char opc = ' ';

	// Menu de opciones inicial.
	while(opc != 'c' && opc != 'C'){
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
	};
}

void menu_por_turno(struct player *player_i, struct player *enemy_i, struct cartas *cartas) {
    srand(time(NULL));
    char opc = ' ';
    do {
        // Menu de opciones por turno.
    printf("Elija la opcion que desea realizar:\n");
    printf("[A]: Sacar carta\n");
    printf("[B]: Reporte de flota\n");
    printf("[C]: Reporte de barcos enemigos\n");

    scanf(" %c", &opc);
    opc = toupper(opc); // Convertir a mayúscula para evitar problemas de comparación.
    switch(opc) {
        case 'A':
            sacar_carta(player_i, enemy_i, cartas);
            opc = 'Z'; // Cambiar la opcion para salir del menu.
            break;
        case 'B':
            imprimirReporteBarcos(player_i, enemy_i, cartas);
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
}

void solicitar_nombre(char *nombre, int max_length) {
    printf("Introduce el nombre del jugador (maximo %d caracteres): ", max_length - 1);
    fgets(nombre, max_length, stdin);
    nombre[strcspn(nombre, "\n")] = '\0'; // Eliminar el salto de línea al final del nombre
}

void partida(){
    struct player player1, player2;
    struct cartas cartas[NUM_CARTAS];
    int alternancia_turno = 1; // Variable de alternancia de turnos.
    int i, j;

    inicializar_cartas(cartas);

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

    do {
        struct player *jugador_en_turno;
        if(alternancia_turno == 1) {
            if(player1.turno == 1) {
                jugador_en_turno = &player1;
                printf("Turno de"); color_txt(INFO_COLOR); printf(" %s\n", player1.name); color_txt(DEFAULT_COLOR);
                imprimirTableroGuerra(&player2, &player1);
                menu_por_turno(&player1, &player2, cartas);
            } else {
                jugador_en_turno = &player2;
                printf("Turno de"); color_txt(INFO_COLOR); printf(" %s\n", player2.name); color_txt(DEFAULT_COLOR);
                imprimirTableroGuerra(&player1, &player2);
                menu_por_turno(&player2, &player1, cartas);
            }
            alternancia_turno = 2; // Cambiar turno
        } else {
            if(player2.turno == 1) {
                jugador_en_turno = &player2;
                printf("Turno de"); color_txt(INFO_COLOR); printf(" %s\n", player2.name); color_txt(DEFAULT_COLOR);
                imprimirTableroGuerra(&player1, &player2);
                menu_por_turno(&player2, &player1, cartas);
            } else {
                jugador_en_turno = &player1;
                printf("Turno de"); color_txt(INFO_COLOR); printf(" %s\n", player1.name); color_txt(DEFAULT_COLOR);
                imprimirTableroGuerra(&player2, &player1);
                menu_por_turno(&player1, &player2, cartas);
            }
            alternancia_turno = 1; // Cambiar turno
        }

        // Verificar si algún barco ha sido hundido y luego desactivar salvo
        for(int s = 0; s < NUM_SHIPS; s++) {
            if(!jugador_en_turno->ships[s].vivo && jugador_en_turno->salvo) {
                desactivar_salvo(jugador_en_turno);
                break;
            }
        }
        // Verificar si el jugador ha ganado
        if(player1.enemy_hit_parts >= VICTORYCONDITION) {
            printf("%s ha ganado!\n", player1.name);
            break;
        } else if(player2.enemy_hit_parts >= VICTORYCONDITION) {
            printf("%s ha ganado!\n", player2.name);
            break;
        }
    }while(player1.enemy_hit_parts < VICTORYCONDITION && player2.enemy_hit_parts < VICTORYCONDITION);
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
}

void capturar_fila_columna(struct cartas *cartas, struct player *player_i, struct player *enemy_i) {
    char columna_c;
    int columna, fila;

    // Capturar fila o columna dependiendo de la carta
    if (cartas->id == 4 || cartas->id == 7) {
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
    } else if (cartas->id == 5 || cartas->id == 8) {
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

    switch (cartas->id) {
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
        for (j = 0; j < 10; j++) {
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

void imprimirReporteBarcos(struct player *player_i, struct player *enemy_i, struct cartas *cartas) {
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
        printf("Bote %02d%*s", i + 1, ancho_col - 6, ""); // "Bote 01" ocupa 8 caracteres, el resto es espacio
    }
    printf("\n");

    // Dibujo de proa (/'\)
    for (i = 0; i < NUM_SHIPS; i++) {
        int estado = player_i->ships[i].status[0][2];
        printf("%*s", ancho_col / 2 - 1, ""); // Centrar proa
        estado == SHIP_STER ? color_txt(SHIP_COLOR) : color_txt(ERROR_COLOR);
        printf("/'\\");
        color_txt(DEFAULT_COLOR);
        printf("%*s", ancho_col - (ancho_col / 2 + 2), ""); // Relleno a la derecha
    }
    printf("\n");

    // Dibujo de casillas de cada barco, por filas (máximo tamaño de barco)
    for (k = 1; k < dimension_maxima; k++) {
        for (i = 0; i < NUM_SHIPS; i++) {
            if (k < player_i->ships[i].size) {
                int estado = player_i->ships[i].status[k][2];
                printf("%*s", ancho_col / 2 - 1, "");
                estado == SHIP_BODY ? color_txt(SHIP_COLOR) : color_txt(ERROR_COLOR);
                estado == SHIP_BODY ? printf("[_]") : printf("[X]");
                color_txt(DEFAULT_COLOR);
                printf("%*s", ancho_col - (ancho_col / 2 + 2), "");
            } else {
                printf("%*s", ancho_col, ""); // Espacio vacío para barcos más cortos
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
        menu_por_turno(player_i, enemy_i, cartas);
    } else {
        color_txt(ERROR_COLOR);
        printf("¡Tecla invalida!\n");
        color_txt(DEFAULT_COLOR);
    }
}

void ponerBarcos(struct ship *ship_i, struct player *player_i) {
    int filaInicio, filaFin, columnaInicio, columnaFin;
    char columnaInicio_c, columnaFin_c;
    int i, j;
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
        if(procesar_coordenadas(ship_i, filaInicio, filaFin, columnaInicio, columnaFin)) {
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

void solicitar_barco(struct player *player_i) {
    int i, barco_seleccionado;
    
    printf("Barcos disponibles:\n");
    for (i = 0; i < NUM_SHIPS; i++) {
        for (int j = 0; j < player_i->ships[i].size; j++) {
            if (player_i->ships[i].status[j][2] == SHIP_BODY_D || player_i->ships[i].status[j][2] == SHIP_STER_D) {
            break; // Si el barco ya fue alcanzado, no lo muestro
            }
            printf("Barco %d: %d celdas\n", i + 1, player_i->ships[i].size);   
        }
    }
    
    do {
        printf("Seleccione el barco que desea mover (1-%d): ", NUM_SHIPS);
        scanf("%d", &barco_seleccionado);
        barco_seleccionado--; // Convertir a base 0
        if (barco_seleccionado < 0 || barco_seleccionado >= NUM_SHIPS) {
            color_txt(ERROR_COLOR);
            printf("Barco invalido. Intente de nuevo.\n");
            color_txt(DEFAULT_COLOR);
        }
    } while (barco_seleccionado < 0 || barco_seleccionado >= NUM_SHIPS || player_i->ships[barco_seleccionado].size == 0); // Validar rango y tamaño del barco

    // Llamar a la función de mover barco
    mover_barco_adelante(player_i, barco_seleccionado);
}

void reglas() {
	printf("Las reglas para jugar al iconico juego \"Batalla Naval\" rezan lo siguiente:\n");
	printf("1. Cada jugador contara con una flota de barcos, la cual ordenara en una distribucion que considere conveniente para ocultarla de su rival\n");
	printf("2. El juego es por turnos. En cada turno se le proporcionará a cada jugador la posibilidad de usar una carta con diversos efectos sobre el tablero.\n");
    printf("3. Las cartas disponibles son:\n");
    printf("   - Disparo: Dispara a una coordenada del tablero enemigo.\n");
    printf("   - Bombardeo de fila: Bombardea una fila del tablero enemigo.\n");
    printf("   - Bombardeo de columna: Bombardea una columna del tablero enemigo.\n");
    printf("   - Revelar: Revela el estado de los barcos enemigos.\n");
    printf("   - Chequeo de fila: Revela el estado de una fila del tablero enemigo.\n");
    printf("   - Chequeo de columna: Revela el estado de una columna del tablero enemigo.\n");
    printf("   - Salvo: Permite disparar a una coordenada del tablero enemigo sin que el enemigo pueda defenderse.\n");
    printf("   - Torre de ventaja: Permite disparar a una coordenada del tablero enemigo y revela el estado de la fila y columna del barco.\n");
    printf("   - Revelar casilla aleatoria: Permite revelar una casilla aleatoria en la que haya un barco enemigo.\n");
    printf("4. El objetivo del juego es hundir todos los barcos del enemigo antes de que el enemigo hunda los tuyos.\n");
    printf("5. Un barco se considera hundido cuando todas sus partes han sido alcanzadas.\n");
	printf("Presione enter cuando haya terminado de leer las reglas\n");
	
	limpiar_buffer_entrada(); // Limpiar el buffer de entrada
	getchar(); // Esperar a que el usuario presione enter
	limpiar_pantalla();
}

void enter_continuar() {
    printf("Presione enter para ");  color_txt(INFO_COLOR); printf("continuar.\n"); color_txt(DEFAULT_COLOR);
    getchar(); // Pausa antes de continuar.
}
