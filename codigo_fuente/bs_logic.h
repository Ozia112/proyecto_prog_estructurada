#ifndef BS_LOGIC_H
#define BS_LOGIC_H

#include <stdio.h> // Incluye definiciones de entrada/salida estándar
#include <stdlib.h> // Incluye definiciones de funciones estándar
#include <math.h> // Incluye definiciones matemáticas
#include <stdbool.h> // Incluye definiciones de tipo booleano estándar
#include "bs_common.h" // Incluye definiciones comunes
#include "bs_console_utils.h" // libreria para poder usar la funcion limpiar y cambio de color.
#include "bs_ui.h" // libreria para poder usar funciones de UI.

// Function prototypes
void inicializar_barco(struct ship *barco, int size);

// Inicializar jugadores.
void inicializar_jugador(struct player *player);

// Inicializa la flota de un jugador.
void inicializar_flota(struct player *player);

// Funciones de validacion de colocacion de barcos
bool validar_coordenadas_en_rango(int fila, int columna);

bool validar_orientacion(int filaInicio, int filaFin, int columnaInicio, int columnaFin);

bool validar_dimension(int filaInicio, int filaFin, int columnaInicio, int columnaFin, int dimension_reuqerida);

bool validar_solapamiento(int matriz[BOARD_SIZE][BOARD_SIZE], int filaInicio, int filaFin, 
                          int columnaInicio, int columnaFin, struct ship *ship_i);

void colocar_barco_en_tablero(int matriz[BOARD_SIZE][BOARD_SIZE], struct ship *ship_i, int filaInicio, 
                              int filaFin, int columnaInicio, int columnaFin);

bool procesar_coordenadas(int matriz[BOARD_SIZE][BOARD_SIZE], struct ship *ship_i, 
                          int filaInicio, int filaFin, int columnaInicio, int columnaFin);

int decidir_primer_turno(const struct player *p1, const struct player *p2);

void limpiar_buffer_entrada();

void modificar_disparo(int matriz_enemigo[BOARD_SIZE][BOARD_SIZE], matriz_mostrada[BOARD_SIZE][BOARD_SIZE], int fila, int columna);

void liberar_status(struct ship *barco);

void liberar_flota(struct player *player);
#endif // BS_LOGIC_H