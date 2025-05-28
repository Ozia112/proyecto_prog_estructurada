#ifndef BS_PLAYER_H
#define BS_PLAYER_H

#include "master.h" // Incluye todas las cabeceras del proyecto

void inicializar_jugador(struct player *player); // Inicializa un jugador

void inicializar_cartas(struct player *player); // Inicializa las cartas del jugador

void reset_input(struct player *player_i); // Reinicia las coordenadas de entrada del jugador

void reset_sucessful_shot(struct player *player_i); // Reinicia el disparo exitoso del jugador

void reset_card_id(struct player *player_i); // Reinicia el ID de la carta del jugador

#endif
