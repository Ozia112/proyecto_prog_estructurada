#ifndef BS_COMMON_H
#define BS_COMMON_H

#include <stdbool.h> // Incluye definiciones de tipo booleano estándar

// Definiciones comunes compartidas en todo el proyecto
#define BOARD_SIZE 10
#define MAX_NAME_LENGTH 21
#define NUM_SHIPS 5
#define VICTORYCONDITION 17 // Número de partes de barco que se deben hundir para ganar
#define MAX_ID_9 4
#define NUM_CARTAS 12
#define CC_STATUS 2 // Columna de estado en la matriz de barcos
#define CC_FILA 0 // Columna de fila en la matriz de barcos
#define CC_COLUMNA 1 // Columna de columna en la matriz de barcos
#define TOTAL_SHIP_PARTS VICTORYCONDITION // Número total de partes de barco
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
    int id; // ID del barco
    char name[20]; // Nombre del barco
    int size; // alojar la dimension del barco
    char direction; // 'E' for east, 'W' for west, 'N' for north, 'S' for south, 'U' for undefined
    int **status; // status[size][3]: [fila][0]=x, [fila][1]=y, [fila][2]=estado (1=punta, 2=cuerpo, 3=punta dañada, 4=cuerpo dañado)
    bool vivo;
};

struct cartas
{
    int id;
    char nombre[40];
    char descripcion[150];
    int peso;
};

struct player
{
    // Variables de innicializacion
    char name[MAX_NAME_LENGTH];
    int placed_ships;
    int turno; // Turno del jugador

    // Variables para barcos
    struct ship ships[NUM_SHIPS]; // Array of ships for the player
    int enemy_hit_parts; // Numero de partes de barco enemigo alcanzadas
    int sunked_ships; // Numero de barcos enemigos hundidos
    
    // Variables para cartas
    struct cartas cartas[NUM_CARTAS]; // Array de cartas
    int peso_total; // Peso total de las cartas
    int torres_acumuladas; // Numero de torres acumuladas
    bool chequeo_fila[BOARD_SIZE]; // Variable para guardar la fila seleccionada por el jugador
    int contador_fila[BOARD_SIZE]; // Contador para el chequeo de fila
    int ultima_fila_chequeada; // Almacena la última fila chequeada
    bool chequeo_columna[BOARD_SIZE]; // Variable para guardar la columna seleccionada por el jugador
    int contador_columna[BOARD_SIZE]; // Contador para el chequeo de columna
    int ultima_columna_chequeada; // Almacena la última columna chequeada
    bool salvo;
    bool buff;

    // Variables de tipo buffer
    int last_input_fila; // Almacena la última coordenada de disparo
    int last_input_columna; // Almacena la última coordenada de disparo
    int last_successful_shot_fila; // Almacena la última coordenada de disparo exitosa
    char last_successful_shot_columna; // Almacena la última coordenada de disparo exitosa
    int last_card_id; // Almacena el ID de la última carta utilizada
    int aciertos_por_turno; // Almacena el número de aciertos por turno
};


#endif // BS_COMMON_H