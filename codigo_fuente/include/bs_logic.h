#ifndef BS_LOGIC_H
#define BS_LOGIC_H

#include "master.h" // Libreria con todas las cabeceras del proyecto.

// Prototipos de funciones

bool procesar_coordenadas(struct player *player, int index, int filaInicio, int filaFin, int columnaInicio, int columnaFin);

void colocar_casilla_inicial_en_tablero(struct player *player, int index, int filaIn, int columnaIn);

void colocar_barco_en_tablero(struct player *player, int index, int filaInicio, int filaFin, int columnaInicio, int columnaFin);

void decidir_primer_turno(struct player *player1, struct player *player2);

int obtener_id_aleatoria(struct player *player);

int calcular_peso_total(struct player *player);

bool validar_movimiento(struct player *player_i, struct ship *ship_i);



#endif // BS_LOGIC_H