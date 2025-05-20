#ifndef BS_EFECTOS_CARTAS_H
#define BS_EFECTOS_CARTAS_H

#include "bs_common.h" // Incluye definiciones comunes
#include <stdbool.h> // Incluye definiciones de tipo booleano estándar

void disparar(struct player *player_i, struct player *enemy_i, int fila, int columna);

bool barco_cuatro_aflote(struct player *player_i);

void bombardea_fila(struct player *player_i, struct player *enemy_i, int fila);

bool barco_cinco_aflote(struct player *player_i);

void bombardea_columna(struct player *player_i, struct player *enemy_i, int columna);

void revela(struct player *enemy_i, struct player *player_i);

void chequeo_fila(struct player *player_i, struct player *enemy_i, int fila);

void chequeo_columna(struct player *player_i, struct player *enemy_i, int columna);

void activar_salvo(struct player *player_i);

void desactivar_salvo(struct player *player_i);

void torre_ventaja(struct player *player_i);

void tira_toma(struct player *player_i, struct player *enemy_i);

void mover_barco_adelante(struct player *player_i, int id_barco);

#endif // BS_EFECTOS_CARTAS_H