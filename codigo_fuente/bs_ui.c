#include "bs_ui.h" // libreria para poder usar la funcion limpiar y cambio de color.
#include "bs_console_utils.h"
#include "bs_logic.h" // libreria para poder usar la funcion limpiar y cambio de color.
#include <string.h>


void solicitar_nombre(char *nombre, int max_length) {
    printf("Introduce el nombre del jugador (maximo %d caracteres): ", max_length - 1);
    fgets(nombre, max_length, stdin);
    nombre[strcspn(nombre, "\n")] = '\0'; // Eliminar el salto de línea al final del nombre
}

void imprimirTablero(int matriz[BOARD_SIZE][BOARD_SIZE]) {
    int anchoTablero, relleno, consolaAncho;
    char caracter;
    int i, j;

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
            int temp = matriz[i][j];
            switch (temp) {
                case 0:
                    cambiar_color_txt(WATER_COLOR);
                    printf("%c ", '~');
                    cambiar_color_txt(DEFAULT_COLOR);
                    break;
                case 1:
                    cambiar_color_txt(SHIP_COLOR);
                    printf("%c ", SHIP_BODY); // Carácter "×" para barco
                    cambiar_color_txt(DEFAULT_COLOR);
                    break;
                case 2:
                    cambiar_color_txt(SHIP_COLOR);
                    printf("%c ", SHIP_STER); // Carácter "¤" para barco
                    cambiar_color_txt(DEFAULT_COLOR);
                    break;
                default:
                    cambiar_color_txt(DEFAULT_COLOR); // Gris claro para cualquier otro valor
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
            cambiar_color_txt(ERROR_COLOR);
            printf("Entrada invalida. Asegurese de ingresar un numero seguido de una letra. Intente de nuevo.\n");
            cambiar_color_txt(DEFAULT_COLOR);
            limpiar_buffer_entrada(); // Limpiar el buffer de entrada
            continue;
        }

        puts("Coordenadas finales del barco (mismo formato).");
        if (scanf(" %d %c", &filaFin, &columnaFin_c) != 2) {
            cambiar_color_txt(ERROR_COLOR);
            printf("Entrada invalida. Asegurese de ingresar un numero seguido de una letra. Intente de nuevo.\n");
            cambiar_color_txt(DEFAULT_COLOR);
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
            cambiar_color_txt(ERROR_COLOR);
            printf("Columna invalida. Asegurese de ingresar una letra entre A y J. Intente de nuevo.\n");
            cambiar_color_txt(DEFAULT_COLOR);
            limpiar_buffer_entrada(); // Limpiar el buffer de entrada
            continue;
        }
        
        if (columnaFin_c >= 'A' && columnaFin_c <= 'J') {
            columnaFin = columnaFin_c - 'A';
        } else {
            cambiar_color_txt(ERROR_COLOR);
            printf("Columna invalida. Asegurese de ingresar una letra entre A y J. Intente de nuevo.\n");
            cambiar_color_txt(DEFAULT_COLOR);
            limpiar_buffer_entrada(); // Limpiar el buffer de entrada
            continue;
        }

        //Validaciones

        // Validar que las coordenadas esten dentro del rango permitido.
        if(!validar_coordenadas_en_rango(filaInicio, columnaInicio) || 
           !validar_coordenadas_en_rango(filaFin, columnaFin)) {
            cambiar_color_txt(ERROR_COLOR);
            printf("Coordenadas fuera de rango. Asegurese de establecerlas entre 1 y 10 para filas y A-J para columnas. Intente de nuevo.\n");
            cambiar_color_txt(DEFAULT_COLOR);
            limpiar_buffer_entrada(); // Limpiar el buffer de entrada
            continue;
        }

        // Procesar y validar las coordenadas del barco.
        if(procesar_coordenadas(matriz, ship_i, filaInicio, filaFin, columnaInicio, columnaFin)) {
            // Si las coordenadas son validas, colocar el barco en el tablero.
            colocar_barco_en_tablero(matriz, ship_i);
        
            // Incrementar el contador de barcos colocados.
            player_i->placed_ships++;
            coordenadas_validas = true; // Salir del bucle si todo es válido.
        } else {
            limpiar_buffer_entrada(); // Limpiar el buffer de entrada
        }

    limpiar_pantalla(); // Limpiar la pantalla después de colocar el barco.
    }
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