#ifndef BATTLESHIP_LIBRARIE_H
#define BATTLESHIP_LIBRARIE_H

#define BOARD_SIZE 10
#define MAX_NAME_LENGTH 21
#define NUM_SHIPS 5

struct ship
{
    int size;
    int startShip[2];
    int endShip[2];
    char orientation; // 'H' for horizontal, 'V' for vertical, 'U' for undefined
    char direction; // 'E' for east, 'W' for west, 'N' for north, 'S' for south, 'U' for undefined
};

struct player
{
    char name[MAX_NAME_LENGTH];
    struct ship ships[NUM_SHIPS]; // Array of ships for the player
    int placed_ships;
    int sunked_enemy_ships;
    int sunked_ships;

};

void limpiar();
void setColor(int color);
void solicitar_nombre(char *nombre, int max_length);
void inicializar_barco(struct ship *barco, int size);
void inicializar_jugador(struct player *player);
void inicializar_flota(struct player *player);
void imprimirTablero(int matriz[BOARD_SIZE][BOARD_SIZE]);
void ponerBarcos(int matriz[BOARD_SIZE][BOARD_SIZE], struct ship *ship_i, struct player *player_i);
void reglas();
void partida();
#endif
