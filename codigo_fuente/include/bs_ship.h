#ifndef BS_SHIP_H
#define BS_SHIP_H

#include "master.h" // Incluye todas las cabeceras del proyecto

void inicializar_flota(struct player *player); // Inicializa la flota de barcos del jugador

void inicializar_barco(struct ship *barco, int size); // Inicializa un barco con un tamaño específico

bool posicion_barco(struct player *player, int index, int s_part, int fila, int columna); // Verifica si una parte del barco está en la posición (x, y)

bool posicion_barco_enemy(struct player *player, int index, int s_part, struct player *enemy);

bool casilla_saludable(struct player *enemy, int index, int s_part); // Verifica si una parte del barco está saludable

void hundir_barco_buff(struct player *player, int index, struct player *enemy); // Hundir un barco enemigo con el buff activado

void hundido(struct player *player, struct player *enemy); // Verifica si un barco enemigo ha sido hundido

void liberar_status(struct ship *barco); // Libera la memoria del estado de un barco

void liberar_flota(struct player *player); // Libera la memoria de la flota de barcos del jugador

#endif