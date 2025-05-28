#ifndef BS_UI_H
#define BS_UI_H

#include "master.h" // Libreria con todas las cabeceras del proyecto.

// Function prototypes

void pantalla_bienvenida();

void menu_principal();

void reglas();

void solicitar_nombre(struct player *player);

void colocar_barcos_jugador(struct player *player);

void imprimirTablero(struct player *player);

void ponerBarcos(struct player *player, int index);

void mostrar_turno_y_tablero_G(struct player *player, struct player *enemy);

void imprimirTableroGuerra(struct player *enemy, struct player *player);

void imprimirReporteBarcosEnemigos(struct player *player, struct player *enemy);

void imprimirReporteBarcos(struct player *player, struct player *enemy);

void mostrar_turno_y_tablero(struct player *player);

void mostrar_info_carta(struct cartas *carta);

void capturar_coordenada(struct player *player, struct player *enemy);

void mostrar_ultimo_disparo_exitoso(struct player *player_i);

void mostrar_bomb_cheq_exitoso(struct player *player_i);



void capturar_fila_columna(struct player *player_i, struct player *enemy_i);

void solicitar_barco(struct player *player_i, struct player *enemy_i);

#endif // BS_UI_H