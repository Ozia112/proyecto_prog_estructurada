#ifndef BS_COMMON_H
#define BS_COMMON_H

// Definiciones comunes compartidas en todo el proyecto
#define BOARD_SIZE 10
#define MAX_NAME_LENGTH 21
#define NUM_SHIPS 5

// Valores numericos para interpretar el tablero
#define WATER 0
#define SHIP_STER 1
#define SHIP_BODY 2

// Common structure definitions
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

struct cartas
{
    int id;
    char nombre[20];
    char descripcion[100];
};

#endif // BS_COMMON_H