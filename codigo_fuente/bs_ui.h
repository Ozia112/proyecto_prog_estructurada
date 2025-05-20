#ifndef BS_UI_H
#define BS_UI_H

#include "bs_common.h" // Incluye definiciones comunes


// Function prototypes

void pantalla_bienvenida();

void menu_principal();

void menu_por_turno(struct player *player_i, struct player *enemy_i);

void solicitar_nombre(struct player *player);

void partida();

void capturar_coordenada(struct player *player_i, struct player *enemy_i);

void capturar_fila_columna(int carta_id, struct player *player_i, struct player *enemy_i);

void imprimirTablero(struct player *player_i);

void imprimirTableroGuerra(struct player *enemy_i, struct player *player_i);

void imprimirReporteBarcos(struct player *player_i, struct player *enemy_i);

void ponerBarcos(struct ship *ship_i, struct player *player_i);

void colocar_barcos_jugador(struct player *player_i);

void solicitar_barco(struct player *player_i, struct player *enemy_i);

void reglas();

void mostrar_turno_y_tablero(struct player *player_i, struct player *enemy_i);

void mostrar_info_carta(struct cartas *carta);

void enter_continuar();

#endif // BS_UI_H