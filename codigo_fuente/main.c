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
			printf("Gracias por haber usado el programa :)\n");
			break;
		default:
			puts("Tecla invalida!");
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
	int matriz_enemigo_j1[BOARD_SIZE][BOARD_SIZE] = {0} // Matriz que se le mostrará al jugador 1 (perteneciente al jugador 2)
    int matriz_enemigo_j2[BOARD_SIZE][BOARD_SIZE] = {0} // Matriz que se le mostrará al jugador 2 (perteneciente al jugador 1)
	int i, j;
	int flag = 1;

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
    
    // Colocar barcos para el jugador 1.
	for(i = 0; i < NUM_SHIPS; i++) {
		if(i != 0) Sleep(1000);
        limpiar_pantalla(); // Limpiar la pantalla antes de colocar barcos.
        printf("Colocando barcos de"); cambiar_color_txt(INFO_COLOR); printf(" %s\n", player1.name); cambiar_color_txt(DEFAULT_COLOR);
        imprimirTablero(matriz_jug1);
        printf("Coloca tu barco de"); cambiar_color_txt(INFO_COLOR); printf(" %d ",player1.ships[i].size); cambiar_color_txt(DEFAULT_COLOR); printf("celdas.\n");
        printf("Barco"); cambiar_color_txt(INFO_COLOR); printf(" %d ",i + 1); cambiar_color_txt(DEFAULT_COLOR); printf("de"); cambiar_color_txt(INFO_COLOR); printf(" %d\n",NUM_SHIPS); cambiar_color_txt(DEFAULT_COLOR);
        ponerBarcos(matriz_jug1, &player1.ships[i], &player1); // Registrar los barcos del jugador 1.
        cambiar_color_txt(SUCCCESS_COLOR);
        printf("Barco colocado exitosamente en");
        cambiar_color_txt(INFO_COLOR); printf(" (%d, %c)\n", player1.ships->startShip[i] + 1, player1.ships->startShip[i] + 'A');
        cambiar_color_txt(DEFAULT_COLOR);
    }

	// Mensaje intermedio entre la colocación de barcos, para evitar revelar información al otro jugador.
	Sleep(2000); // Sleep para mostrar el tablero resultante del primer jugador. 
	limpiar_pantalla();
	printf("Voltea a otro lado"); cambiar_color_txt(INFO_COLOR); printf(" %s", player1.name); cambiar_color_txt(DEFAULT_COLOR); printf(", es hora de que"); cambiar_color_txt(INFO_COLOR); printf(" %s", player2.name); cambiar_color_txt(DEFAULT_COLOR); printf(" ponga sus barcos!\n");
	printf("Presione "); cambiar_color_txt(INFO_COLOR); printf("\"enter\""); cambiar_color_txt(DEFAULT_COLOR); printf(" para continuar");
	while(getchar() != '\n'); // Limpiar el buffer para evitar comportamientos inesperados.
	getchar();

	// Colocar los barcos del segundo jugador. 
	for(i = 0; i < NUM_SHIPS; i++) {
		if(i != 0) Sleep(1000);
        limpiar_pantalla(); // Limpiar la pantalla antes de colocar barcos.
        printf("Colocando barcos de"); cambiar_color_txt(INFO_COLOR); printf(" %s\n", player2.name); cambiar_color_txt(DEFAULT_COLOR);
        imprimirTablero(matriz_jug2);
        printf("Coloca tu barco de"); cambiar_color_txt(INFO_COLOR); printf(" %d ",player2.ships[i].size); cambiar_color_txt(DEFAULT_COLOR); printf("celdas.\n");
        printf("Barco"); cambiar_color_txt(INFO_COLOR); printf(" %d ",i + 1); cambiar_color_txt(DEFAULT_COLOR); printf("de"); cambiar_color_txt(INFO_COLOR); printf(" %d\n",NUM_SHIPS); cambiar_color_txt(DEFAULT_COLOR);
        ponerBarcos(matriz_jug2, &player2.ships[i], &player2); // Registrar los barcos del jugador 2.
        cambiar_color_txt(SUCCCESS_COLOR);
        printf("Barco colocado exitosamente en");
        cambiar_color_txt(INFO_COLOR); printf(" (%d, %c)\n", player2.ships->startShip[i] + 1, player2.ships->startShip[i] + 'A');
        cambiar_color_txt(DEFAULT_COLOR);
    }

	printf("Listos para comenzar?\n")
	printf("La partida iniciará tan pronto como presionen"); cambiar_color_txt(INFO_COLOR); printf("\"enter\"!"); cambiar_color_txt(DEFAULT_COLOR);
	
	// Ciclo para asignar los valores correspondientes a las matrices de enemigo.
	for(i = 0; i < BOARD_SIZE; i++){
		for(j = 0; j < BOARD_SIZE; j++){
			matriz_enemigo_j1[i][j] = matriz_jug2[1][j];
			matriz_enemigo_j2[i][j] = matriz_jug1[i][j];
		}
	}

	// ciclop para recorrer para la acción por turnos de los jugadores.
	/* while(flag){
		printf("Turno de"); cambiar_color_txt(INFO_COLOR); printf(" %s", player1.name); cambiar_color_txt(DEFAULT_COLOR);
		imprimirTablero(matriz_enemigo_j1);
		printf("Qué deseas hacer?\n");
		printf("a. Disparar\nb. Usar carta");
		char opc = ' ';
		while(opc != 'c' && opc != 'C'){
			scanf("%c", &opc);
			switch(opc){
				case 'a': case 'A':
				dispararBarco();
				break;
				case 'b': case 'B':
				// usarCarta(); // Función para usar carta.
				break;
				default:
				printf("Caracter inválido.\n");
				break;
			}
			break;
		} */
	}

	
	getchar(); // Pausa antes de continuar.
}