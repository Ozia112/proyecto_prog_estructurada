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
#define NUM_SHIPS 5

// Caracteres para las partes del barco.
#define ship_tip 207 // Caracter "¤" para punta de barco 
#define ship_body 254 // Carácter "■" para cuerpo de barco

// Definicion de colores para la consola.
#define WaterColor 3
#define ShipColor 4
#define DefaultColor 7
#define ErrorColor 12
#define SuccessColor 10
#define InfoColor 6

struct ship
{
    int size;
    int startShip[2];
    int endShip[2];
    int *ship_status; // Pointer for dynamic allocation of status array
    char orientation; // 'H' for horizontal, 'V' for vertical, 'U' for undefined
    char direction; // 'E' for east, 'W' for west, 'N' for north, 'S' for south, 'U' for undefined
};

struct player
{
    char name[MAX_NAME_LENGTH];
    struct ship ships[NUM_SHIPS]; // Array of ships for the player
    int placed_ships;
    int sunked_enemy_ships;
    int sunked_ships;

};
struct player player1;

// Inicializa un barco individual.
void inicializar_barco(struct ship *s, int lenght) {
    s->size = lenght;
    s->startShip[0] = -1;
    s->startShip[1] = -1;
    s->endShip[0] = -1;
    s->endShip[1] = -1;
    s->ship_status = (int *)malloc(lenght * sizeof(int)); // Allocate memory for ship status
    if (s->ship_status == NULL) {
        fprintf(stderr, "Error allocating memory for ship status\n");
        exit(1);
    }
    for (int i = 0; i < lenght; i++) {
        s->ship_status[i] = 0; // Initialize ship status to 0 (not hit)
    }
};

// Inicializa la flota de un jugador.
void inicializar_flota(struct player *p) {
    // Initialize ships with different sizes
    inicializar_barco(&p->ships[0], 5); // 5 cells
    inicializar_barco(&p->ships[1], 4); // 4 cells
    inicializar_barco(&p->ships[2], 3); // 3 cells
    inicializar_barco(&p->ships[3], 3); // 3 cells
    inicializar_barco(&p->ships[4], 2); // 2 cells

    p->placed_ships = 0;
    p->sunked_enemy_ships = 0;
    p->sunked_ships = 0;
}




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
        Azul Claro:      9
        Verde Claro:    10
        Aqua Claro:     11
        Rojo Claro:     12
        Fucsia:         13
        Amarillo Claro: 14
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



    // Imprimir tablero con el relleno
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
void ponerBarcos(int matriz[BOARD_SIZE][BOARD_SIZE], struct ship *s) {
    
    int filaInicio, filaFin;
    char columnaInicio, columnaFin;

    

    while (1) {
        // Se le pide al usuario que ingrese las coordenadas iniciales y finales del barco.
        puts("Coordenada inicial del barco (fila 1-10 y columna A-J, separadas por un espacio): ");
        if (scanf(" %d %c", &filaInicio, &columnaInicio) != 2) {
            setColor(ErrorColor);
            printf("Entrada invalida. Asegurese de ingresar un numero seguido de una letra. Intente de nuevo.\n");
            setColor(DefaultColor);
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            return;
        }

        puts("Coordenadas finales del barco (mismo formato).");
        if (scanf(" %d %c", &filaFin, &columnaFin) != 2) {
            setColor(ErrorColor);
            printf("Entrada invalida. Asegurese de ingresar un numero seguido de una letra. Intente de nuevo.\n");
            setColor(DefaultColor);
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            return;
        }

        // Ajustar indices
        filaInicio--; filaFin--;
        
        // Transformar la letra de columna a mayúscula si no lo es.
        int colCharInicio = toupper(columnaInicio) - 'A';
        int colCharFin = toupper(columnaFin) - 'A';
        
        //Validaciones:
        // Validar que las coordenadas estén dentro del rango permitido.
        if (filaInicio < 0 || filaInicio >= BOARD_SIZE || filaFin < 0 || filaFin >= BOARD_SIZE ||
            colCharInicio < 0 || colCharInicio >= BOARD_SIZE || colCharFin < 0 || colCharFin >= BOARD_SIZE) {
            printf("Coordenadas fuera de rango. Asegurese de establecerlas entre 1 y 10 para filas y A-J para columnas. Intente de nuevo.\n");
            return;
        }

        // Validar que no haya solapamiento con otros barcos.
        int solapamiento = 0;
        for (int i = filaInicio; i <= filaFin; i++) {
            for (int j = colCharInicio; j <= colCharFin; j++) {
                if (matriz[i][j] != 0) {
                    solapamiento = 1;
                    continue;
                }
            }
            if (solapamiento) continue;
        }
        
        if (solapamiento) {
            printf("Ya hay un barco en esa posicion. Intente de nuevo.\n");
            break;
        }

        // Determinar orientación del barco.
        if (filaInicio == filaFin) {
            // Horizontal
            s->orientation = 'H';
            s->direction = (colCharInicio < colCharFin) ? 'E' : 'W'; // Determinar dirección
        } else if (colCharInicio == colCharFin) {
            // Vertical
            s->orientation = 'V';
            s->direction = (filaInicio < filaFin) ? 'S' : 'N'; // Determinar dirección
        } else {
            printf("Coordenadas invalidas. El barco debe ser horizontal o vertical. Intente de nuevo.\n");
            return;
        }
        
        // Si todas las validaciones pasan, colocar el barco.
        for (int i = filaInicio; i <= filaFin; i++) {
            for (int j = colCharInicio; j <= colCharFin; j++) {
                matriz[i][j] = 1; // se asigna el valor 1 a la matriz para representar el barco.
            }
        }

        // Guardar las coordenadas de inicio y fin del barco.
        s->startShip[0] = filaInicio;
        s->startShip[1] = colCharInicio;
        s->endShip[0] = filaFin;
        s->endShip[1] = colCharFin;

        // Colocar en la matriz: punta en la primera celda, cuerpo en las siguientes.
        int dr = (filaFin > filaInicio) ? 1 : (filaFin < filaInicio) ? -1 : 0;
        int dc = (colCharFin > colCharInicio) ? 1 : (colCharFin < colCharInicio) ? -1 : 0;
        int r = filaInicio, c = colCharInicio;

        for(int i = 0; i < s->size; i++) {
            matriz[r][c]= (i == 0 ? ship_tip : ship_body); // Punta o cuerpo del barco
            r += dr;
            c += dc;
        }

        break; // Salir del bucle si todo es válido.
    }
    limpiar(); // Limpiar la pantalla después de colocar el barco.
    printf("Barco colocado exitosamente en");
    setColor(InfoColor); printf(" (%d, %c)\n", filaInicio + 1, columnaInicio); setColor(DefaultColor);
}


// funcion para iniciar la partida. Esta funcion sera como un "main secundario" para ejecutar todas las subrutinas necesarias para llevar a cabo una partida.
void partida(){
    struct player player1, player2;
    inicializar_flota(&player1);
    inicializar_flota(&player2);

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
    ponerBarcos(MatrizJug1, &player1.ships[0]); // Pass the first ship of player1 as an example
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
