#ifndef BS_LOGIC_H
#define BS_LOGIC_H

#include <stdbool.h> // Incluye definiciones de tipo booleano estándar
#include "bs_common.h" // Incluye definiciones comunes

// Function prototypes
void inicializar_barco(struct ship *barco, int size);

void hundido(struct player *player_i); // Verifica si un barco está hundido.

void inicializar_jugador(struct player *player); // Inicializar jugadores.

void inicializar_flota(struct player *player); // Inicializa la flota de un jugador.

void inicializar_cartas(struct cartas *cartas); // Inicializa las cartas de un jugador.

void ajustar_probabilidades(struct cartas *cartas, struct player *player_1, struct player *player_2); // Ajusta las probabilidades de las cartas.

bool validar_coordenadas_en_rango(int fila, int columna); // Funciones de validacion de colocacion de barcos

bool validar_orientacion(int filaInicio, int filaFin, int columnaInicio, int columnaFin);

bool validar_dimension(int filaInicio, int filaFin, int columnaInicio, int columnaFin, int dimension_reuqerida);

bool validar_solapamiento(struct ship *ship_i, int filaInicio, int filaFin, int columnaInicio, int columnaFin);

bool validar_estado_casilla(struct player *player_i, int fila, int columna);

void colocar_barco_en_tablero(struct ship *ship_i, int filaInicio, int filaFin, int columnaInicio, int columnaFin);

bool procesar_coordenadas(struct ship *ship_i, int filaInicio, int filaFin, int columnaInicio, int columnaFin);

bool validar_movimiento(struct player *player_i, struct ship *ship_i);

void decidir_primer_turno(struct player *p1, struct player *p2);

int obtener_id_aleatoria(struct cartas *cartas); // Función para obtener un ID de carta aleatorio

void sacar_carta(struct player *player_i, struct player *enemy_i, struct cartas *cartas); // Función para sacar una carta

void limpiar_buffer_entrada(); // Función para limpiar el buffer de entrada

void liberar_status(struct ship *barco);

void liberar_flota(struct player *player);
#endif // BS_LOGIC_H