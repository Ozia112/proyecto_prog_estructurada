#ifndef BS_LOGIC_H
#define BS_LOGIC_H

#include "bs_common.h" // Incluye definiciones comunes
#include "bs_console_utils.h" // libreria para poder usar la funcion limpiar y cambio de color.

// Function prototypes
void inicializar_barco(struct ship *barco, int size);

// Inicializar jugadores.
void inicializar_jugador(struct player *player);

// Inicializa la flota de un jugador.
void inicializar_flota(struct player *player);

#endif // BS_LOGIC_H