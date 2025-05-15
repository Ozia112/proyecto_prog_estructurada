#include <stdio.h>
#include "bs_logic.h"
#include "bs_console_utils.h" // libreria para poder usar la funcion limpiar y cambio de color.
#include "bs_ui.h" // libreria para poder usar funciones de UI.

void inicializar_barco(struct ship *barco, int size) {
    barco-> size = size;
    barco->orientation = 'U'; // No definido
    barco->direction = 'U'; // No definido

    // Inicializar coordenadas a -1 para indicar que no está colocado.
    barco->startShip[0] = -1;
    barco->startShip[1] = -1;
    barco->endShip[0] = -1;
    barco->endShip[1] = -1;
}

// Inicializar jugadores.
void inicializar_jugador(struct player *player) {

    // Asignar el nombre al jugador.
    solicitar_nombre(player->name, sizeof(player->name));

    // Inicializar estado de jugador.
    player->placed_ships = 0;
    player->sunked_enemy_ships = 0;
    player->sunked_ships = 0;

    // Inicializar barcos.
    inicializar_flota(player);
}

// Inicializa la flota de un jugador.
void inicializar_flota(struct player *player) {
    // Initialize ships with different sizes
    inicializar_barco(&player->ships[0], 5); // 5 cells
    inicializar_barco(&player->ships[1], 4); // 4 cells
    inicializar_barco(&player->ships[2], 3); // 3 cells
    inicializar_barco(&player->ships[3], 3); // 3 cells
    inicializar_barco(&player->ships[4], 2); // 2 cells
}