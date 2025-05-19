#ifndef BS_COMMON_H
#define BS_COMMON_H

#include <stdbool.h> // Incluye definiciones de tipo booleano estándar

// Definiciones comunes compartidas en todo el proyecto
#define BOARD_SIZE 10
#define MAX_NAME_LENGTH 21
#define NUM_SHIPS 5
#define VICTORYCONDITION 17 // Número de partes de barco que se deben hundir para ganar
#define MAX_ID_10 4
#define NUM_CARTAS 12
#define CC_STATUS 2 // Columna de estado en la matriz de barcos
#define CC_FILA 0 // Columna de fila en la matriz de barcos
#define CC_COLUMNA 1 // Columna de columna en la matriz de barcos

// Valores numericos para interpretar el tablero
#define WATER 0
#define SHIP_STER 1
#define SHIP_BODY 2
#define SHIP_STER_D 3
#define SHIP_BODY_D 4

// Valores para interpretar los numeros como caracteres

#define STER_PRINT 49 // '1'
#define BODY_PRINT 50 // '2'
#define WATER_PRINT '~' 

// Common structure definitions
struct ship
{
    int size; // alojar la dimension del barco
    char direction; // 'E' for east, 'W' for west, 'N' for north, 'S' for south, 'U' for undefined
    int **status; // status[size][3]: [fila][0]=x, [fila][1]=y, [fila][2]=estado (1=punta, 2=cuerpo, 3=punta dañada, 4=cuerpo dañado)
    bool vivo;
};

struct player
{
    char name[MAX_NAME_LENGTH];
    int turno; // Turno del jugador
    struct ship ships[NUM_SHIPS]; // Array of ships for the player
    int placed_ships; 
    int enemy_hit_parts; // Numero de partes de barco enemigo alcanzadas
    int sunked_ships; // Numero de barcos enemigos hundidos
    int torres_acumuladas; // Numero de torres acumuladas
    bool chequeo_fila[BOARD_SIZE]; // Variable para guardar la fila seleccionada por el jugador
    bool chequeo_columna[BOARD_SIZE]; // Variable para guardar la columna seleccionada por el jugador
    bool salvo;
    bool buff;
};

struct cartas
{
    int id;
    char nombre[20];
    float probabilidad;
    char descripcion[100];
};

#endif // BS_COMMON_H