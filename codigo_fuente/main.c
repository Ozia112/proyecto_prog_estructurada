#include <stdio.h> // libreria para poder usar la funcion printf.
#include <stdlib.h> // libreria para poder usar la funcion system.
#include "bs_common.h" // Incluye definiciones comunes
#include "bs_console_utils.h" // libreria para poder usar la funcion limpiar y cambio de color.
#include "bs_logic.h" // libreria para poder usar funciones de logica.
#include "bs_ui.h" // libreria para poder usar funciones de UI.
#include <string.h> // libreria para poder usar la funcion strcspn.

void partida(); // Prototipo de la funcion partida.
int main() {
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
	limpiar_pantalla();
	
	char opc = ' ';
	// Este ciclo llamara a las funciones que serviran para iniciar y ejecutar la partida.
	while(opc != 'c' && opc != 'C'){
		printf("Presione la tecla correspondiente a su opcion.\n");
		printf("Opciones:\n");
		printf("A. Iniciar partida\nB. Ver reglas.\nC. Salir\n");
		scanf(" %c", &opc);

		switch(opc) {
		// Caso en el que el usuario quiere iniciar partida.
		case 'a': case 'A':
			partida();
			break;
		// caso en el que el usuario quiere leer las reglas.
		case 'b': case 'B':
			reglas();
			break;
		// Caso en el que el usuario quiere salir del programa (se especifica con un "case" porque sino el programa imprime "tecla inv�lida" cuando se presiona la c).
		case 'c': case 'C':
			printf("Gracias por haber usado el programa :)");
			break;
		default:
			puts("¡Tecla invalida!");
			//Sleep(1000); // funcion para tener demora en la ejecucion de la limpieza de la terminal.
			limpiar_pantalla(); // Limpiar la pantalla.
			break;
		}
	};
    return 0;
}

void partida(){
    struct player player1, player2;
    int matriz_jug1[BOARD_SIZE][BOARD_SIZE] = {0}; // Matriz para el jugador 1.
    int matriz_jug2[BOARD_SIZE][BOARD_SIZE] = {0}; // Matriz para el jugador 2.
    int i, j;

    getchar(); // Limpiar el buffer de entrada antes de solicitar coordenadas
	limpiar_pantalla(); // se limpia el menu de opciones inicial despues de haber entrado en la funcion partida, para que no estorbe.
	printf("Jugador 1:\n");
	inicializar_jugador(&player1);
    
    limpiar_pantalla(); // Limpiar la pantalla después de inicializar jugadores.
    printf("Jugador 2:\n");
    inicializar_jugador(&player2);
    
    limpiar_pantalla(); // Limpiar la pantalla después de inicializar jugadores.
    printf("Jugadores:\n");
    printf("Jugador 1:"); cambiar_color_txt(INFO_COLOR); printf(" %s\n",player1.name); cambiar_color_txt(DEFAULT_COLOR);
    printf("Jugador 2:"); cambiar_color_txt(INFO_COLOR); printf(" %s\n",player2.name); cambiar_color_txt(DEFAULT_COLOR);
    printf("Presione enter para ");  cambiar_color_txt(INFO_COLOR); printf(" continuar.\n"); cambiar_color_txt(DEFAULT_COLOR);
    getchar(); // Pausa antes de continuar.
    limpiar_pantalla(); // Limpiar la pantalla después de mostrar los nombres de los jugadores.
    
    printf("Colocando barcos para %s\n", player1.name);
    // Colocar barcos para el jugador 1.
	for(i = 0; i < NUM_SHIPS; i++) {
        limpiar_pantalla(); // Limpiar la pantalla antes de colocar barcos.
        printf("Colocando barcos de"); cambiar_color_txt(INFO_COLOR); printf(" %s\n", player1.name); cambiar_color_txt(DEFAULT_COLOR);
        imprimirTablero(matriz_jug1);
        printf("Coloca tu barco de"); cambiar_color_txt(INFO_COLOR); printf(" %d ",player1.ships[i].size); cambiar_color_txt(DEFAULT_COLOR); printf("celdas.\n");
        printf("Barco"); cambiar_color_txt(INFO_COLOR); printf(" %d ",i + 1); cambiar_color_txt(DEFAULT_COLOR); printf("de"); cambiar_color_txt(INFO_COLOR); printf(" %d\n",NUM_SHIPS); cambiar_color_txt(DEFAULT_COLOR);
        ponerBarcos(matriz_jug1, &player1.ships[i], &player1); // Registrar los barcos del jugador 1.
        cambiar_color_txt(SUCCCESS_COLOR);
        printf("Barco colocado exitosamente en");
        cambiar_color_txt(INFO_COLOR); printf(" (%d, %c)\n", player1.ships->startShip[0] + 1, player1.ships->startShip[1] + 'A');
        cambiar_color_txt(DEFAULT_COLOR);
    }
	
    imprimirTablero(matriz_jug1);
	
	getchar(); // Pausa antes de continuar.
}