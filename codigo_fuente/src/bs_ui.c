#include "bs_ui.h" // libreria para poder usar funciones de UI.

void pantalla_bienvenida() {
    // Logo para la pantalla de inicio.
	printf(" _______  _______  _______  _______  ___      ___      _______    __    _  _______  __   __  _______  ___     \n");
	printf("|  _    ||   _   ||       ||   _   ||   |    |   |    |   _   |  |  |  | ||   _   ||  | |  ||   _   ||   |    \n");
	printf("| |_|   ||  |_|  ||_     _||  |_|  ||   |    |   |    |  |_|  |  |   |_| ||  |_|  ||  |_|  ||  |_|  ||   |    \n");
	printf("|       ||       |  |   |  |       ||   |    |   |    |       |  |       ||       ||       ||       ||   |    \n");
	printf("|  _   | |       |  |   |  |       ||   |___ |   |___ |       |  |  _    ||       ||       ||       ||   |___ \n");
	printf("| |_|   ||   _   |  |   |  |   _   ||       ||       ||   _   |  | | |   ||   _   | |     | |   _   ||       | \n");
	printf("|_______||__| |__|  |___|  |__| |__||_______||_______||__| |__|  |_|  |__||__| |__|  |___|  |__| |__||_______| \n");

	printf("Presiona enter para"); color_txt(INFO_COLOR); printf(" continuar\n"); color_txt(DEFAULT_COLOR);
	getchar(); // Espera a que el usuario presione una tecla.
}

void menu_principal() {
    char opc;
    bool loop = true;

    limpiar_pantalla(); // Limpiar la pantalla antes de mostrar el menú.
	// Menu de opciones inicial.
	do{
		printf("Ingrese la opcion que desee realizar.\n");
		printf("Opciones:\n");
		printf("[A]: Iniciar partida\n");
        printf("[B]: Ver reglas.\n");
        printf("[C]: Salir\n");
		scanf(" %c", &opc);
        limpiar_buffer_entrada(); // Limpiar el buffer de entrada
        opc = toupper(opc); // Convertir a mayúscula para evitar problemas de comparación.
        if (opc == 'A' || opc == 'B' || opc == 'C') {
            limpiar_pantalla(); // Limpiar la pantalla antes de mostrar el menú.
        }
		switch(opc) {
		    // Caso en el que el usuario quiere iniciar partida.
            case 'A':
                partida();
                break;
            // caso en el que el usuario quiere leer las reglas.
            case 'B':
                reglas();
                break;
            // Caso en el que el usuario quiere salir del programa (se especifica con un "case" porque sino el programa imprime "tecla invalida" cuando se presiona la c).
            case 'C':
                printf("Gracias por haber usado el programa :)");
                loop = false;
                break;
            default:
                puts("¡Tecla invalida!");
                Sleep(1000); // funcion para tener demora en la ejecucion de la limpieza de la terminal.
                limpiar_pantalla(); // Limpiar la pantalla.
                break;
            }
	}while(loop); // Mientras loop sea verdadero, el menu se repetira.
}

void reglas() {
    char opc;
    do {
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

        printf("[Z]: Regresar al"); color_txt(INFO_COLOR); printf(" menu.\n");
        color_txt(DEFAULT_COLOR);

        scanf(" %c", &opc);
        limpiar_buffer_entrada();
        opc = toupper(opc);
    } while (opc != 'Z');
    
    menu_principal();
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

void colocar_barcos_jugador(struct player *player) {
    printf("Colocando barcos para"); color_txt(INFO_COLOR); printf(" %s\n", player->name); color_txt(DEFAULT_COLOR);
    for(int idx_ship = 0; idx_ship < NUM_SHIPS; idx_ship++) {
        limpiar_pantalla();
        printf("Colocando barcos de"); color_txt(INFO_COLOR); printf(" %s\n", player->name); color_txt(DEFAULT_COLOR);
        imprimirTablero(player);
        printf("Coloca tu %s", player->ships[idx_ship].name); color_txt(INFO_COLOR); printf(" (%d ",player->ships[idx_ship].size); color_txt(DEFAULT_COLOR);
        printf("celdas).\nBarco"); color_txt(INFO_COLOR); printf(" %d ",idx_ship + 1); color_txt(DEFAULT_COLOR);
        printf("de"); color_txt(INFO_COLOR); printf(" %d\n",NUM_SHIPS); color_txt(DEFAULT_COLOR);
        ponerBarcos(player, idx_ship);
    }
    printf("Colocando barcos de"); color_txt(INFO_COLOR); printf(" %s\n", player->name); color_txt(DEFAULT_COLOR);
    imprimirTablero(player);
    printf("Barcos colocados correctamente. \n");
    Sleep(1000);
    limpiar_buffer_entrada();
    enter_continuar();
    limpiar_pantalla();
}

void imprimirTablero(struct player *player) {
    int anchoTablero, relleno, consolaAncho;
    int i, j, idx_ship, s_part, estado;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    
    // Obtener ancho de consola
    consolaAncho = 80; //Por defecto si no es posible
    if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        consolaAncho = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    // Calculando relleno para centrar
    anchoTablero = BOARD_SIZE * 2 + 3; // Cada columna ocupa 3 caracteres (" 1 ")
    relleno = (consolaAncho - anchoTablero) / 2;

    color_txt(INFO_COLOR);
        printf("%*s Tablero de Flota\n", relleno, "");
    color_txt(DEFAULT_COLOR);
    // Encabezado de columnas (1 2 3 ... 10)
    printf("%*s", relleno,""); // Imprime relleno con espacios para centrar
    printf("  ");
    for (int num = 1; num <= BOARD_SIZE; num++) {
        num < BOARD_SIZE ? printf("%2d", num) : printf(" F");
    }
    printf("\n");

    // Dibujar cada fila
    for (i = 0; i < BOARD_SIZE; i++) {
        // Encabezado de filas (A B C ... J)
        printf("%*s%c  ", relleno,"", 'A' +i);

        // Recorrer cada columna
        for (j = 0; j < BOARD_SIZE; j++) {
            estado = WATER; // Por defecto el estado es agua
            
            // Recorrer cada barco
            for (idx_ship = 0; idx_ship < NUM_SHIPS && estado == WATER; idx_ship++) {
                
                // Recorrer cada parte del barco
                for (s_part = 0; s_part < player->ships[idx_ship].size; s_part++) {

                    // Comprobar si la parte del barco coincide con la posición actual(i, j).
                    if (posicion_barco(player, idx_ship, s_part, i, j)) {

                        // Si coincide, asignar el estado correspondiente
                        estado = player->ships[idx_ship].status[s_part][2];
                        break; // Salir del bucle s_part
                    }
                }
            }

            // Imprimir el resultado según el estado
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

void ponerBarcos(struct player *player, int index) {
    int filaInicio, filaFin, columnaInicio, columnaFin;
    char filaInicio_c, filaFin_c;
    bool validacion = false;

    do {
        // Se le pide al usuario que ingrese las coordenadas iniciales y finales del barco.
        puts("Coordenada inicial del barco (Fila: letras de A a la J; Columna: numero del 1 al 10): ");
        printf("Ejemplo:"); color_txt(INFO_COLOR); printf("A 1"); color_txt(DEFAULT_COLOR);
        printf("\n> ");

        if (scanf(" %c %d", &filaInicio_c, &columnaInicio) != 2) {
            limpiar_buffer_entrada(); // Limpiar el buffer de entrada
            color_txt(ERROR_COLOR);
            printf("Formato de entrada invalido.");
            color_txt(INFO_COLOR); printf("CodeError: 0\n"); color_txt(DEFAULT_COLOR);
        } else validacion = true;
        
        columnaInicio--; // Ajustar columna a base 0

        filaInicio_c = toupper(filaInicio_c); // Convertir a mayúscula para evitar problemas de comparación
        filaInicio = filaInicio_c - 'A'; // Convertir letra a índice (A=0, B=1, ..., J=9)
        if (validar_cc_rango(filaInicio, columnaInicio)) validacion = true; // Validar rango de coordenadas
        
        if (!validacion) color_txt(ERROR_COLOR); printf("Intente de nuevo.\n"); color_txt(DEFAULT_COLOR);
    } while(!validacion);
    
    validacion = false; // Reiniciar la validacion para la siguiente entrada

    do {
        puts("Coordenada final del barco (Fila: letras de A a la J; Columna: numero del 1 al 10): ");
        printf("Ejemplo:"); color_txt(INFO_COLOR); printf("A 1"); color_txt(DEFAULT_COLOR);
        printf("\n> ");

        if (scanf(" %c %d", &filaFin_c, &columnaFin) != 2) {
            limpiar_buffer_entrada(); // Limpiar el buffer de entrada
            color_txt(ERROR_COLOR);
            printf("Formato de entrada invalido.");
            color_txt(INFO_COLOR); printf("CodeError: 0\n"); color_txt(DEFAULT_COLOR);
        } else validacion = true;

        columnaFin--; // Ajustar columna a base 0

        filaFin_c = toupper(filaFin_c); // Convertir a mayúscula para evitar problemas de comparación
        filaFin = filaFin_c - 'A'; // Convertir letra a índice (A=0, B=1, ..., J=9)
        if (validar_cc_rango(filaFin, columnaFin)) validacion = true; // Validar rango de coordenadas

        // Validar barco una vez validadas las coordenadas iniciales y finales.
        if (procesar_coordenadas(player, index, filaInicio, filaFin, columnaInicio, columnaFin)) validacion = true; // Validaciones en conjunto

        if (!validacion) color_txt(ERROR_COLOR); printf("Intente de nuevo.\n"); color_txt(DEFAULT_COLOR);
    } while(!validacion);
    
    // Si las coordenadas son validas, colocar el barco en el tablero.
    colocar_barco_en_tablero(player, index, filaInicio, filaFin, columnaInicio, columnaFin);
    
    color_txt(SUCCESS_COLOR);
    printf("Barco colocado exitosamente de");
    color_txt(INFO_COLOR);
    printf(" (%c, %d) ", filaInicio_c, columnaInicio + 1);
    color_txt(DEFAULT_COLOR); printf("a");
    color_txt(INFO_COLOR); printf(" (%c, %d)\n", filaFin_c, columnaFin + 1); color_txt(DEFAULT_COLOR);
    Sleep(1000); // Pausa para mostrar el mensaje de éxito.
    limpiar_pantalla(); // Limpiar la pantalla después de colocar el barco.
}

void mostrar_turno_y_tablero_G(struct player *player, struct player *enemy) {
    int espacios = 5; // Espacios para centrar el texto

    printf("Turno de");

    color_txt(INFO_COLOR);
    printf(" %s %*s", player->name, espacios, "");
    color_txt(DEFAULT_COLOR);

    printf(" | Modo salvo: ");

    player->salvo ? color_txt(SUCCESS_COLOR) : color_txt(ERROR_COLOR);
    printf("%s ", player->salvo ? "Activo" : "Inactivo");
    color_txt(DEFAULT_COLOR);
    if (player->buff) {
        printf("| Torre de ventaja: ");
        
        color_txt(SUCCESS_COLOR);
            printf("Activada ");
        color_txt(DEFAULT_COLOR);
    } else {
        printf(" | Torres acumuladas: ");

        color_txt(INFO_COLOR);
            printf("%d\n\n", player->torres_acumuladas);
        color_txt(DEFAULT_COLOR);
    }

    imprimirTableroGuerra(enemy, player); // Imprimir el tablero del enemigo.
}

void imprimirTableroGuerra(struct player *enemy, struct player *player) {
    int anchoTablero, relleno, consolaAncho;
    int i, j, idx_ship, s_part, print_status;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // Obtener ancho de consola
    consolaAncho = 80; //Por defecto si no es posible
    if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        consolaAncho = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    // Calculando relleno para centrar
    anchoTablero = BOARD_SIZE * 3 + 3; // Cada columna ocupa 3 caracteres (" 1 ")
    relleno = (consolaAncho - anchoTablero) / 2;

    color_txt(INFO_COLOR);
        printf("%*s Tablero de Guerra\n", relleno, ""); 
    color_txt(DEFAULT_COLOR);
    // Encabezado de columnas (1 2 3 ... 10)
    printf("%*s", relleno,""); // Imprime relleno con espacios para centrar
    printf("  ");
    for (int num = 1; num <= BOARD_SIZE; num++) {
        num < BOARD_SIZE ? printf("%2d", num) : printf(" F");
    }
    printf("\n");

    // Dibujar cada fila
    for (i = 0; i < BOARD_SIZE; i++) {

        // Encabezado de filas (A B C ... J)
        printf("%*s%c  ", relleno,"", 'A' + i);

        // Recorrer cada columna
        for (j = 0; j < BOARD_SIZE; j++) {
            print_status = WATER; // Por defecto el estado es agua
            for (idx_ship = 0; idx_ship < NUM_SHIPS && print_status == WATER; idx_ship++) {
                for (s_part = 0; s_part < enemy->ships[idx_ship].size; s_part++) {

                    // Comprobar si la parte del barco coincide con la posición actual(i, j).
                    if (posicion_barco(enemy, idx_ship, s_part, i, j)) {

                        // Si coincide, asignar el estado correspondiente
                        if (enemy->ships[idx_ship].status[s_part][CC_STATUS] == SHIP_BODY_D) {
                            print_status = SHIP_BODY_D;
                        } else if (enemy->ships[idx_ship].status[s_part][CC_STATUS] == SHIP_STER_D) {
                            print_status = SHIP_STER_D;
                        }
                        break; // Salir del bucle s_part
                    }
                }
            }
            switch (print_status) {
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
        if (player->chequeo_fila[i]) {
            barcos_en_fila(player, enemy);
            color_txt(SUCCESS_COLOR);
            if (player->contador_fila[i] > BOARD_SIZE - 1) {
                printf(" %d", player->contador_fila[i]);
            } else {
                printf("F "); // F = Full
            }
            color_txt(DEFAULT_COLOR);
        }
        printf("\n");
    }

    // Mostrar chequeo de columna (una sola línea debajo del tablero)
    printf("%*s   ", relleno, "");
        for (j = 0; j < BOARD_SIZE; j++) {
            if (player->chequeo_columna[j]) {
                barcos_en_columna(player, enemy);
                color_txt(SUCCESS_COLOR);
                if (player->contador_columna[j] > BOARD_SIZE - 1) {
                    printf("%d ", player->contador_columna[j]);    
                } else {
                    printf(" F "); // F = Full
                }
                color_txt(DEFAULT_COLOR);
            } else {
                printf("  "); // Espacio vacío si no hay chequeo
            }
        }
    printf("\n");
}

void imprimirReporteBarcosEnemigos(struct player *player, struct player *enemy) {
    
    mostrar_turno_y_tablero_G(player, enemy);
    printf("\n");
    printf("Reporte de barcos enemigos:\n");
    printf("Barcos enemigos hundidos: ");
    color_txt(INFO_COLOR);
        printf("%d\n", player->sunked_ships);
    color_txt(DEFAULT_COLOR);

    printf("Partes de barcos enemigos hundidos: ");
    color_txt(INFO_COLOR);
        printf("%d\n", player->enemy_hit_parts);
    color_txt(DEFAULT_COLOR);

    printf("Modo salvo enemigo activado: ");
    enemy->salvo ? color_txt(INFO_COLOR) : color_txt(SUCCESS_COLOR);
        printf("%s\n", enemy->salvo ? "Si" : "No");
    color_txt(DEFAULT_COLOR);

    printf("Torre de ventaja enemigo activada: ");
    enemy->torres_acumuladas == 4 ? color_txt(INFO_COLOR) : color_txt(SUCCESS_COLOR);
        printf("%s\n", enemy->torres_acumuladas == 4 ? "Si" : "No");
    color_txt(DEFAULT_COLOR);
    printf("\n");

    printf("[z]: Regresar al menu.\n");
    char opc;
    bool loop = true;
    do {
        scanf(" %c", &opc);
        limpiar_buffer_entrada(); // Limpiar el buffer de entrada
        opc = toupper(opc);
        if (opc == 'Z') {
            loop = false;
        } else {
            color_txt(ERROR_COLOR);
            printf("¡Tecla invalida!\n");
            color_txt(DEFAULT_COLOR);
        }
    } while (loop);
}

void imprimirReporteBarcos(struct player *player, struct player *enemy) {
    int i, k;
    int dimension_maxima = 0;
    int ancho_col = 12; // Ancho fijo para cada barco

    mostrar_turno_y_tablero(player);
    printf("\n");
    printf("Reporte de barcos:\n");

    // Encontrar el tamaño máximo de los barcos
    for (i = 0; i < NUM_SHIPS; i++) {
        if (player->ships[i].size > dimension_maxima) {
            dimension_maxima = player->ships[i].size;
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
        int estado = player->ships[i].status[0][2];
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
            if (k < player->ships[i].size) {
                int estado = player->ships[i].status[k][2];
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
    bool loop = true;
    do {
        scanf(" %c", &opc);
        limpiar_buffer_entrada(); // Limpiar el buffer de entrada
        opc = toupper(opc);
        if (opc == 'Z') {
            loop = false;
        } else {
            color_txt(ERROR_COLOR);
            printf("¡Tecla invalida!\n");
        color_txt(DEFAULT_COLOR);
    }
    } while (loop);
}

void mostrar_turno_y_tablero(struct player *player) {
    int espacios = 10; // Espacios para centrar el texto

    printf("Turno de");

    color_txt(INFO_COLOR);
    printf(" %s %*s", player->name, espacios, "");
    color_txt(DEFAULT_COLOR);

    printf(" | Modo salvo: ");

    player->salvo ? color_txt(SUCCESS_COLOR) : color_txt(ERROR_COLOR);
    printf("%s ", player->salvo ? "Activado" : "Desactivado");
    color_txt(DEFAULT_COLOR);
    if (player->buff) {
        printf("| Torre de ventaja: ");
        
        color_txt(SUCCESS_COLOR);
            printf("Activada ");
        color_txt(DEFAULT_COLOR);
    } else {
        printf(" | Torres acumuladas: ");

        color_txt(INFO_COLOR);
            printf("%d\n\n", player->torres_acumuladas);
        color_txt(DEFAULT_COLOR);
    }
    imprimirTablero(player); // Imprimir el tablero del jugador.
}

void mostrar_info_carta(struct cartas *carta) {
    printf("Te ha salido la carta:"); color_txt(INFO_COLOR); printf(" %s\n", carta->nombre); color_txt(DEFAULT_COLOR);
}

void capturar_coordenada(struct player *player, struct player *enemy) {
    char fila_c;
    int columna;
    bool validacion = false;
    char linea[32]; // Buffer para la entrada del usuario
    char *nl; // Puntero para el salto de línea
    do {
        puts("Ingrese las coordenadas (Fila: letras de A a la J; Columna: numeros del 1 al 10): ");
        printf("Ejemplo: "); color_txt(INFO_COLOR); printf("A 1\n"); color_txt(DEFAULT_COLOR);
        printf("> ");

        if(!fgets(linea, sizeof(linea), stdin)) {
            limpiar_buffer_entrada(); // Limpiar el buffer de entrada
            color_txt(ERROR_COLOR);
            printf("Error de entrada."); color_txt(INFO_COLOR); printf(" CodeError: Null.\n");
            color_txt(DEFAULT_COLOR);
            continue; // Repetir el ciclo si la entrada es invalida
        }

        nl = strchr(linea, '\n');
        if(nl) *nl = '\0'; // Eliminar el salto de línea al final de la entrada

        // Intentar leer las coordenadas en el formato "A 1" o "A1"
        if (sscanf(linea, " %c %d", &fila_c, &columna) != 2
          && sscanf(linea, " %c%d", &fila_c, &columna) != 2) {
            color_txt(ERROR_COLOR);
            printf("Formato invalido.");
            color_txt(INFO_COLOR); printf("CodeError: 0\n");
            color_txt(DEFAULT_COLOR);
            continue; // Repetir el ciclo si la entrada es invalida
        }
        
        fila_c = toupper(fila_c); // Convertir a mayúscula para evitar problemas de comparación
        player->last_input_fila = fila_c - 'A';
        player->last_input_columna = columna - 1; // Ajustar columna a base 0

        // Rango de coordenadas
        if (!validar_ataque_cc_rango(player)) {
            continue;
        } 
        if (!validar_estado_casilla(player, enemy)) {
            continue;
        }
        validacion = true; // Si todas las validaciones pasan, se marca como valido

        if (!validacion) {
            color_txt(ERROR_COLOR);
            printf("Intente de nuevo.\n");
            color_txt(DEFAULT_COLOR); 
        }
    } while (!validacion);

    printf("Coordenadas ingresadas: %c, %d\n", 
            player->last_input_fila + 'A', 
            player->last_input_columna + 1);

    disparar(player, enemy);
}

void mostrar_ultimo_disparo_exitoso(struct player *player) {
    if (player->last_successful_shot_columna != -1 && player->last_successful_shot_fila != -1) {
        color_txt(SUCCESS_COLOR);
        printf("Disparo exitoso en: %c,%d\n", player->last_successful_shot_fila + 'A', player->last_successful_shot_columna + 1);
        color_txt(DEFAULT_COLOR);
    } else {
        printf("No se ha realizado ningun disparo exitoso.\n");
    }
}

void capturar_fila_columna(struct player *player, struct player *enemy) {
    char fila_c;
    int columna;
    bool validacion = false;

    if (player->last_card_id == 3 || player->last_card_id == 6) {
        // Bombardeo/Chequeo de fila: letra
        do {
            printf("Ingrese la fila que desee %s (A-%c): ",(player->last_card_id==3) ? "bombardear" : "revisar",'A' + BOARD_SIZE - 1);

            if (scanf(" %c", &fila_c) == 0) {
                limpiar_buffer_entrada(); // Limpiar el buffer de entrada
                color_txt(ERROR_COLOR);
                printf("Error de formato,"); color_txt(INFO_COLOR); printf("CodeError: NULL\n");
                color_txt(DEFAULT_COLOR);
            } else validacion = true;
            fila_c = toupper(fila_c); // Convertir a mayúscula para evitar problemas de comparación
            player->last_input_fila = fila_c - 'A'; // Convertir letra a índice (A=0, B=1, ..., J=9)

            if (validar_ataque_cc_rango(player)) validacion = true; // Validar rango de coordenadas

        } while (!validacion);
    } else if (player->last_card_id == 4 || player->last_card_id == 7) {
        // Bombardeo/Chequeo de columna: número
        do {
            printf("Ingrese la columna que desee %s (1-%d): ",(player->last_card_id==4) ? "bombardear" : "revisar",BOARD_SIZE);
            if(scanf(" %d", &columna) == 0) {
                limpiar_buffer_entrada(); // Limpiar el buffer de entrada
                color_txt(ERROR_COLOR);
                printf("Error de formato,"); color_txt(INFO_COLOR); printf("CodeError: NULL\n");
                color_txt(DEFAULT_COLOR);
            } else validacion = true;
            player->last_input_columna = columna - 1; // Ajustar columna a base 0

            if (validar_ataque_cc_rango(player)) validacion = true; // Validar rango de coordenadas

        } while (!validacion);
    }

    switch (player->last_card_id) {
        case 3: 
            bombardea_fila(player, enemy);
            break;
        case 4: 
            bombardea_columna(player, enemy);
            break;
        case 6:
            chequeo_fila(player, enemy);
            player->ultima_fila_chequeada = player->last_input_fila;
            break;
        case 7:
            chequeo_columna(player, enemy);
            player->ultima_columna_chequeada = player->last_input_columna;
            break;
    }
}

void mostrar_bomb_cheq_exitoso(struct player *player_i) {
        
switch (player_i->last_card_id) {
    case 3:
        if (player_i->last_successful_shot_fila != -1) {
            printf("Bombardeo exitoso en la fila: %c\n", player_i->last_successful_shot_fila + 'A');
            printf("Casillas enemigas destruidos: %d\n", player_i->aciertos_por_turno);
        } else printf("No se ha realizado ningun bombardeo exitoso.\n");
        break;
    case 4:
        if (player_i->last_successful_shot_columna != -1) {
            printf("Bombardeo exitoso en la columna: %d\n", player_i->last_successful_shot_columna + 1);
            printf("Casillas enemigas destruidos: %d\n", player_i->aciertos_por_turno);
        } else printf("No se ha realizado ningun bombardeo exitoso.\n");
        break;
    case 6:
        printf("Chequeo exitoso en la fila: %c\n", player_i->ultima_fila_chequeada + 'A');
        printf("Casillas enemigas encontradas: %d\n", player_i->contador_fila[player_i->ultima_fila_chequeada]);
        break;
    case 7:
        printf("Chequeo exitoso en la columna: %d\n", player_i->ultima_columna_chequeada + 1);
        printf("Casillas enemigas encontradas: %d\n", player_i->contador_columna[player_i->ultima_columna_chequeada]);
        break;
    }
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


