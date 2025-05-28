#ifndef BS_GAME_H
#define BS_GAME_H

#include "master.h" // Libreria con todas las cabeceras del proyecto.

void partida();

void menu_por_turno(struct player *player, struct player *enemy);

void sacar_carta(struct player *player, struct player *enemy);

#endif // BS_GAME_H