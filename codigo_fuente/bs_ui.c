#include "bs_ui.h" // libreria para poder usar la funcion limpiar y cambio de color.
#include "bs_console_utils.h"
#include "bs_logic.h" // libreria para poder usar la funcion limpiar y cambio de color.
#include <string.h>
#include <ctype.h>
#include <windows.h> // Para Sleep

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

void menu_por_turno() {
    char opc = ' ';
    do {
        // Menu de opciones por turno.
    printf("elija la opcion que desea realizar:\n");
    printf("[A]: Sacar carta\n");
    printf("[B]: Reporte de flota\n");
    printf("[C]: Reporte de barcos enemigos\n");

    scanf(" %c", &opc);
    opc = toupper(opc); // Convertir a mayúscula para evitar problemas de comparación.
    switch(opc) {
        case 'A':
            // Lógica para sacar carta
            break;
        case 'B':
            // Lógica para reporte de flota
            break;
        case 'C':
            // Lógica para reporte de barcos enemigos
            break;
        default:
            color_txt(ERROR_COLOR);
            printf("¡Tecla invalida!\n");
            color_txt(DEFAULT_COLOR);
    }
    }while(opc != 'C' && opc != 'c');
}

void solicitar_nombre(char *nombre, int max_length) {
    printf("Introduce el nombre del jugador (maximo %d caracteres): ", max_length - 1);
    fgets(nombre, max_length, stdin);
    nombre[strcspn(nombre, "\n")] = '\0'; // Eliminar el salto de línea al final del nombre
}

void partida(){
    struct player player1, player2;
    int primer_turno;
    int matriz_jug1[BOARD_SIZE][BOARD_SIZE] = {0}; // Matriz para el jugador 1.
    int matriz_jug2[BOARD_SIZE][BOARD_SIZE] = {0}; // Matriz para el jugador 2.
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
    colocar_barcos_jugador(&player1, matriz_jug1); // Colocar barcos para el jugador 1.

    // Colocar barcos para el jugador 2.
    printf("Ahora es turno de"); color_txt(INFO_COLOR); printf(" %s\n", player2.name); color_txt(DEFAULT_COLOR);
    enter_continuar(); // Pausa antes de continuar.
	
    colocar_barcos_jugador(&player2, matriz_jug2);
    
    // Elegir aleatoriamente quién inicia
    primer_turno = decidir_primer_turno(&player1, &player2);

    // Aquí puedes llamar a la función de turnos, pasando el jugador que inicia
    // turno(primer_jugador == 0 ? &player1 : &player2, primer_jugador == 0 ? &player2 : &player1, matriz_jug1, matriz_jug2);
}

void imprimirTablero(int matriz[BOARD_SIZE][BOARD_SIZE]) {
    int anchoTablero, relleno, consolaAncho;
    char caracter;
    int i, j, temp;

    // Obtener el ancho de la consola
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    consolaAncho = 80; //Por defecto si no es posible
    if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        consolaAncho = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    // Calculando relleno para centrar
    anchoTablero = BOARD_SIZE * 2 + 4; // Dos caracteres por columna + 4 para las filas de nuemros y espaciado
    relleno = (consolaAncho - anchoTablero) / 2;



    // Imprimir tablero con el relleno
    printf("%*s", relleno,""); // Imprime relleno con espacios para centrar
    printf("   ");
    for (caracter = 'A'; caracter <= 'J'; caracter++) {
        printf("%c ", caracter);
    }
    printf("\n");

    for (i = 0; i < 10; i++) {
        printf("%*s", relleno,""); // Imprime relleno con espacios para centrar
        printf("%.2d ", i + 1);
        for (j = 0; j < 10; j++) {
            temp = matriz[i][j];
            switch (temp) {
                case 0:
                    color_txt(WATER_COLOR);
                    printf("%c ", '~');
                    color_txt(DEFAULT_COLOR);
                    break;
                case 1:
                    color_txt(SHIP_COLOR);
                    printf("%c ", SHIP_STER); // Carácter "×" para barco
                    color_txt(DEFAULT_COLOR);
                    break;
                case 2:
                    color_txt(SHIP_COLOR);
                    printf("%c ", SHIP_BODY); // Carácter "¤" para barco
                    color_txt(DEFAULT_COLOR);
                    break;
                case 3:
                    color_txt(ERROR_COLOR);
                    printf("%c ", SHIP_STER);
                    color_txt(DEFAULT_COLOR);
                    break;
                case 4:
                    color_txt(ERROR_COLOR);
                    printf("%c ", SHIP_BODY);
                    color_txt(DEFAULT_COLOR);
                    break;
                default:
                    color_txt(DEFAULT_COLOR); // Gris claro para cualquier otro valor
                    printf("? ");
                    break;
            }
        }
        printf("\n");
    }
}

void ponerBarcos(int matriz[BOARD_SIZE][BOARD_SIZE], struct ship *ship_i, struct player *player_i) {
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
        if(procesar_coordenadas(matriz, ship_i, filaInicio, filaFin, columnaInicio, columnaFin)) {
            // Si las coordenadas son validas, colocar el barco en el tablero.
            colocar_barco_en_tablero(matriz, ship_i, filaInicio, filaFin, columnaInicio, columnaFin);
        
            // Incrementar el contador de barcos colocados.
            player_i->placed_ships++;
            coordenadas_validas = true; // Salir del bucle si todo es válido.
        } else {
            limpiar_buffer_entrada(); // Limpiar el buffer de entrada
        }
    if(coordenadas_validas) {
        color_txt(SUCCCESS_COLOR);
        printf("Barco colocado exitosamente en");
        color_txt(INFO_COLOR); 
        printf(" (%d, %c)\n", filaInicio + 1, columnaInicio + 'A');
        color_txt(DEFAULT_COLOR);
        Sleep(1000); // Pausa para mostrar el mensaje de éxito.
        limpiar_pantalla(); // Limpiar la pantalla después de colocar el barco.
    }
    
    }
}

void colocar_barcos_jugador(struct player *player, int matriz[BOARD_SIZE][BOARD_SIZE]) {
    printf("Colocando barcos para"); color_txt(INFO_COLOR); printf(" %s\n", player->name); color_txt(DEFAULT_COLOR);
    for(int i = 0; i < NUM_SHIPS; i++) {
        limpiar_pantalla();
        printf("Colocando barcos de"); color_txt(INFO_COLOR); printf(" %s\n", player->name); color_txt(DEFAULT_COLOR);
        imprimirTablero(matriz);
        printf("Coloca tu barco de"); color_txt(INFO_COLOR); printf(" %d ",player->ships[i].size); color_txt(DEFAULT_COLOR);
        printf("celdas.\nBarco"); color_txt(INFO_COLOR); printf(" %d ",i + 1); color_txt(DEFAULT_COLOR);
        printf("de"); color_txt(INFO_COLOR); printf(" %d\n",NUM_SHIPS); color_txt(DEFAULT_COLOR);
        ponerBarcos(matriz, &player->ships[i], player);
    }
    imprimirTablero(matriz);
    printf("Barcos colocados correctamente. \n");
    Sleep(1000);
    limpiar_buffer_entrada();
    enter_continuar();
    limpiar_pantalla();
}

void reglas() {
	printf("Las reglas para jugar al iconico juego \"Batalla Naval\" rezan lo siguiente:\n");
	printf("1. Cada jugador contara con una flota de barcos, la cual ordenara en una distribucion que considere conveniente para ocultarla de su rival\n");
	printf("2. El juego es por turnos, y en cada turno un jugador puede escoger...\n");
	printf("Presione enter cuando haya terminado de leer las reglas\n");
	
	limpiar_buffer_entrada(); // Limpiar el buffer de entrada
	getchar(); // Esperar a que el usuario presione enter
	limpiar_pantalla();
}

void enter_continuar() {
    printf("Presione enter para ");  color_txt(INFO_COLOR); printf(" continuar.\n"); color_txt(DEFAULT_COLOR);
    getchar(); // Pausa antes de continuar.
}