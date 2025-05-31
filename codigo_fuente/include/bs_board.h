#ifndef BS_BOARD_H
#define BS_BOARD_H

#include "master.h"

// administrar colocacion y movimiento de barcos

bool validar_cc_rango(int cc_fila, int cc_columna);

bool validar_solapamiento_inicial(struct player *player, int index, int filaInicio, int columnaInicio);

bool validar_orientacion(struct player *player, int index, int filaInicio, int filaFin, int columnaInicio, int columnaFin);

bool validar_dimension(struct player *player, int index, int filaInicio, int filaFin, int columnaInicio, int columnaFin);

bool validar_solapamiento(struct player *player, int index, int filaInicio, int filaFin, int columnaInicio, int columnaFin);

// Administrar ataques a barcos

bool validar_ataque_cc_rango(struct player *player);

int barcos_en_fila(struct player *player, struct player *enemy);

int barcos_en_columna(struct player *player, struct player *enemy);

bool validar_estado_casilla(struct player *player, struct player *enemy);

bool validar_entrada(char *input, int carta_id);


#endif