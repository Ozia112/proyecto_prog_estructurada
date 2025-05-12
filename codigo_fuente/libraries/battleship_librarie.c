#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "battleship_librarie.h"

// Definicion de constantes para el juego.
#define WATER 0
#define SHIP 1
#define BOARD_SIZE 10
#define MAX_NAME_LENGTH 20

// Definicion de colores para la consola.
#define WaterColor 3
#define ShipColor 4
#define DefaultColor 7

void limpiar(){
	system("cls");
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    /*Lista colores: 
        Negro:           0
        Azul:            1
        Verde:           2
        Aqua:            3
        Rojo:            4
        Purpura:         5
        Amarillo:        6
        Gris Claro:      7
        Gris Oscuro:     8
        Blanco:         15
    */
}

// imprimir tablero con el formato apropiado.
void imprimirTablero(int matriz[BOARD_SIZE][BOARD_SIZE]) {

    // Obtener el ancho de la consola
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int consolaAncho = 80; //Por defecto si no es posible
    if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        consolaAncho = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    // Calculando relleno para centrar
    int anchoTablero = BOARD_SIZE * 2 + 4; // Dos caracteres por columna + 4 para las filas de nuemros y espaciado
    int relleno = (consolaAncho - anchoTablero) / 2;

    // Imprimir tablero con el rellno
    printf("%*s", relleno,""); // Imprime relleno con espacios para centrar
    printf("   ");
    for (char caracter = 'A'; caracter <= 'J'; caracter++) {
        printf("%c ", caracter);
    }
    printf("\n");

    for (int i = 0; i < 10; i++) {
        printf("%*s", relleno,""); // Imprime relleno con espacios para centrar
        printf("%.2d ", i + 1);
        for (int j = 0; j < 10; j++) {
            if (matriz[i][j] == 0) {
                setColor(WaterColor);
                printf("%c ", '~');
                setColor(7);
            } else if (matriz[i][j] == 1) {
                setColor(ShipColor);
                printf("%c ", 158); // Carácter "×" para barco
                setColor(DefaultColor);
            } else {
                setColor(DefaultColor); // Gris claro para cualquier otro valor
                printf("? ");
            }
        }
        printf("\n");
        setColor(DefaultColor); // Restaurar color al final de cada línea
    }
}

// funcion para poner barcos.
void ponerBarcos(int matriz[BOARD_SIZE][BOARD_SIZE]) {
    int filaInicio, filaFin;
    char columnaInicio, columnaFin;

    while (1) {
        // Se le pide al usuario que ingrese las coordenadas iniciales y finales del barco.
        puts("Coordenadas iniciales del barco (numero de fila y letra de columna, separadas por un espacio).");
        if (scanf(" %d %c", &filaInicio, &columnaInicio) != 2) {
            printf("Entrada invalida. Asegurese de ingresar un numero seguido de una letra. Intente de nuevo.\n");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }

        puts("Coordenadas finales del barco (mismo formato).");
        if (scanf(" %d %c", &filaFin, &columnaFin) != 2) {
            printf("Entrada invalida. Asegurese de ingresar un numero seguido de una letra. Intente de nuevo.\n");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }

        // Transformar la letra de columna a mayúscula si no lo es.
        columnaInicio = toupper(columnaInicio);
        columnaFin = toupper(columnaFin);

        // se resta 1 a las filas para que el usuario pueda ingresar la fila de la matriz como si fuera un tablero de batalla naval (de 1 a 10).
        filaInicio--;
        filaFin--;
        int colInicio = columnaInicio - 'A';
        int colFin = columnaFin - 'A';

        // Validar que las coordenadas estén dentro del rango permitido.
        if (filaInicio < 0 || filaInicio >= BOARD_SIZE || filaFin < 0 || filaFin >= BOARD_SIZE ||
            colInicio < 0 || colInicio >= BOARD_SIZE || colFin < 0 || colFin >= BOARD_SIZE) {
            printf("Coordenadas invalidas. Asegurese de que las filas esten entre 1 y 10, y las columnas entre A y J. Intente de nuevo.\n");
            continue;
        }

        // Validar que las coordenadas formen un barco válido (horizontal o vertical).
        if (filaInicio != filaFin && colInicio != colFin) {
            printf("Coordenadas invalidas. Los barcos deben ser colocados horizontal o verticalmente. Intente de nuevo.\n");
            continue;
        }

        // Validar que no haya solapamiento con otros barcos.
        int solapamiento = 0;
        for (int i = filaInicio; i <= filaFin; i++) {
            for (int j = colInicio; j <= colFin; j++) {
                if (matriz[i][j] == 1) {
                    solapamiento = 1;
                    break;
                }
            }
            if (solapamiento) break;
        }

        if (solapamiento) {
            printf("Coordenadas invalidas. El barco se solapa con otro existente. Intente de nuevo.\n");
            continue;
        }

        // Si todas las validaciones pasan, colocar el barco.
        for (int i = filaInicio; i <= filaFin; i++) {
            for (int j = colInicio; j <= colFin; j++) {
                matriz[i][j] = 1; // se asigna el valor 1 a la matriz para representar el barco.
            }
        }

        break; // Salir del bucle si todo es válido.
    }
}


// funcion para iniciar la partida. Esta funcion sera como un "main secundario" para ejecutar todas las subrutinas necesarias para llevar a cabo una partida.
void partida(){
	limpiar(); // se limpia el menu de opciones inicial despues de haber entrado en la funcion partida, para que no estorbe.
	
	// Variables para almacenar los nombres de los jugadores.
	char NombreJugador1[MAX_NAME_LENGTH], NombreJugador2[MAX_NAME_LENGTH];
	
	// Las siguientes lineas solicitan y capturan los nombres de los jugadores.
	printf("Para iniciar la partida, comienza por poner los nombres de los jugadores (de maximo 20 caracteres).\n");
	getchar(); // Limpiar el buffer de entrada si hay caracteres sobrantes.
    
    printf("Jugador 1: ");
	fgets(NombreJugador1, sizeof(NombreJugador1), stdin);
    // Elimina el salto de línea al final del nombre.
    NombreJugador1[strcspn(NombreJugador1, "\n")] = '\0';

	printf("Jugador 2: ");
	fgets(NombreJugador2, sizeof(NombreJugador2), stdin);
    // Elimina el salto de línea al final del nombre.
	NombreJugador2[strcspn(NombreJugador2, "\n")] = '\0';

	int MatrizJug1[BOARD_SIZE][BOARD_SIZE] = {0}; // Matriz para el jugador 1.
    int MatrizJug2[BOARD_SIZE][BOARD_SIZE] = {0}; // Matriz para el jugador 2.
	
	imprimirTablero(MatrizJug1);
    ponerBarcos(MatrizJug1);
	imprimirTablero(MatrizJug1);
	
	getchar(); // Pausa antes de continuar.
}

// funcion para imprimir las reglas.
void reglas(){
	printf("Las reglas para jugar al iconico juego \"Batalla Naval\" rezan lo siguiente:\n");
	printf("1. Cada jugador contara con una flota de barcos, la cual ordenara en una distribucion que considere conveniente para ocultarla de su rival\n");
	printf("2. El juego es por turnos, y en cada turno un jugador puede escoger...\n");
	printf("Presione enter cuando haya terminado de leer las reglas\n");
	
	while (getchar() != '\n'); // Limpiar el buffer de entrada si hay caracteres sobrantes.
	
	getchar();
	
	limpiar();
}
