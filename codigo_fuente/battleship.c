#include <stdio.h> // libreria para poder usar la funcion printf.
#include <stdlib.h> // libreria para poder usar la funcion system.
#include "battleship_librarie.h"    // libreria que contiene las funciones para el juego.
#include <string.h> // libreria para poder usar la funcion strcspn.
#include <windows.h> // libreria para poder usar la funcion sleep.
	
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
	limpiar();
	
	
	
	
	char opc = ' ';
	// Este ciclo llamara a las funciones que serviran para iniciar y ejecutar la partida.
	while(opc != 'c' && opc != 'C'){
		printf("Presione la tecla correspondiente a su opcion.\n");
		printf("Opciones:\n");
		printf("A. Iniciar partida\nB. Ver reglas.\nC. Salir\n");
		scanf(" %c", &opc);
		switch(opc){
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
			Sleep(1000); // funcion para tener demora en la ejecucion de la limpieza de la terminal.
			limpiar();
			break;
		}
	};
    return 0;
}