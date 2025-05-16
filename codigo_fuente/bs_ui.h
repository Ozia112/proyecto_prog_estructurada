#ifndef BS_UI_H
#define BS_UI_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "bs_common.h" // Incluye definiciones comunes

// Caracteres para las partes del barco.
#define ship_tip 207 // Caracter "¤" para punta de barco 
#define ship_body 254 // Carácter "■" para cuerpo de barco

// Function prototypes

void pantalla_bienvenida();
void menu_principal();
void partida();
void solicitar_nombre(char *nombre, int max_length);
void imprimirTablero(int matriz[BOARD_SIZE][BOARD_SIZE]);
void ponerBarcos(int matriz[BOARD_SIZE][BOARD_SIZE], struct ship *ship_i, struct player *player_i);
void colocar_barcos_jugador(struct player *player_i, int matriz[BOARD_SIZE][BOARD_SIZE]);
void reglas();
void enter_continuar();
#endif // BS_UI_H