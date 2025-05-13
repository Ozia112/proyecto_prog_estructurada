#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> 
#include <stdbool.h>
#include "battleship_librarie.h"


// Definicion de constantes para el juego.
#define WATER 0
#define SHIP_STER 1
#define SHIP_BODY 2 
#define BOARD_SIZE 10
#define NUM_SHIPS 5

// Caracteres para las partes del barco.
#define ship_tip 207 // Caracter "�" para punta de barco 
#define ship_body 254 // Caracter "�" para cuerpo de barco

// Definicion de colores para la consola.
#define WaterColor 3
#define ShipColor 6
#define DefaultColor 7
#define ErrorColor 12
#define SuccessColor 10
#define InfoColor 6

void limpiar(){
	system("cls");
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    /*Lista colores: 
        Negro:           0
        Azul:            1
        Verde:           2
        Aqua:            3
        Rojo:            4
        Purpura:         5
        Amarillo:        6
        Gris Claro:      7
        Gris Oscuro:     8
        Azul Claro:      9
        Verde Claro:    10
        Aqua Claro:     11
        Rojo Claro:     12
        Fucsia:         13
        Amarillo Claro: 14
        Blanco:         15
    */
}

void solicitar_nombre(char *nombre, int max_length) {
    printf("Introduce el nombre del jugador (maximo %d caracteres): ", max_length - 1);
    fgets(nombre, max_length, stdin);
    nombre[strcspn(nombre, "\n")] = '\0'; // Eliminar el salto de línea al final del nombre
}

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

// imprimir tablero con el formato apropiado.
void imprimirTablero(int matriz[BOARD_SIZE][BOARD_SIZE]) {

    // Obtener el ancho de la consola
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int consolaAncho = 80; //Por defecto si no es posible
    if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        consolaAncho = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    // Calculando relleno para centrar
    int anchoTablero = BOARD_SIZE * 2 + 4; // Dos caracteres por columna + 4 para las filas de nuemros y espaciado
    int relleno = (consolaAncho - anchoTablero) / 2;



    // Imprimir tablero con el relleno
    printf("%*s", relleno,""); // Imprime relleno con espacios para centrar
    printf("   ");
    for (char caracter = 'A'; caracter <= 'J'; caracter++) {
        printf("%c ", caracter);
    }
    printf("\n");

    for (int i = 0; i < 10; i++) {
        printf("%*s", relleno,""); // Imprime relleno con espacios para centrar
        printf("%.2d ", i + 1);
        for (int j = 0; j < 10; j++) {
            if (matriz[i][j] == 0) {
                setColor(WaterColor);
                printf("%c ", '~');
                setColor(7);
            } else if (matriz[i][j] == 1) {
                setColor(ShipColor);
                printf("%c ", SHIP_BODY); // Carácter "×" para barco
                setColor(DefaultColor);
            } else if (matriz[i][j] == 2) {
                setColor(ShipColor);
                printf("%c ", SHIP_STER); // Carácter "¤" para barco
                setColor(DefaultColor);
            } else {
                setColor(DefaultColor); // Gris claro para cualquier otro valor
                printf("? ");
            }
        }
        printf("\n");
        setColor(DefaultColor); // Restaurar color al final de cada línea
    }
}

// funcion para poner barcos.
void ponerBarcos(int matriz[BOARD_SIZE][BOARD_SIZE], struct ship *ship_i, struct player *player_i) {
    
    int filaInicio, filaFin, columnaInicio, columnaFin;
    char columnaInicio_c, columnaFin_c;
    int i, j, solapamiento = 0;
    int size_valid = ship_i->size; // Tamaño del barco a colocar.
    bool ccs_colocadas = false; // Variable para controlar el bucle de entrada de coordenadas.

    while(!ccs_colocadas) {
        // Se le pide al usuario que ingrese las coordenadas iniciales y finales del barco.
        puts("Coordenada inicial del barco (fila 1-10 y columna A-J, separadas por un espacio): ");
        if (scanf(" %d %c", &filaInicio, &columnaInicio_c) != 2) {
            setColor(ErrorColor);
            printf("Entrada invalida. Asegurese de ingresar un numero seguido de una letra. Intente de nuevo.\n");
            setColor(DefaultColor);
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }

        puts("Coordenadas finales del barco (mismo formato).");
        if (scanf(" %d %c", &filaFin, &columnaFin_c) != 2) {
            setColor(ErrorColor);
            printf("Entrada invalida. Asegurese de ingresar un numero seguido de una letra. Intente de nuevo.\n");
            setColor(DefaultColor);
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }

        // Ajustar indices de fila
        filaInicio--; filaFin--;
        
        // Transformar la letra de columna a mayúscula si no lo es.
        // Transformar la letra de columna a mayúscula si no lo es.
        columnaInicio_c = toupper(columnaInicio_c);
        columnaFin_c = toupper(columnaFin_c);
        
        // Convertir la letra de columna a un número (A=0, B=1, ..., J=9)
        if (columnaInicio_c >= 'A' && columnaInicio_c <= 'J') {
            columnaInicio = columnaInicio_c - 'A';
        } else {
            setColor(ErrorColor);
            printf("Columna invalida. Asegurese de ingresar una letra entre A y J. Intente de nuevo.\n");
            setColor(DefaultColor);
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }
        
        // Convertir la letra de columna a un número (A=0, B=1, ..., J=9)
        if (columnaFin_c >= 'A' && columnaFin_c <= 'J') {
            columnaFin = columnaFin_c - 'A';
        } else {
            setColor(ErrorColor);
            printf("Columna invalida. Asegurese de ingresar una letra entre A y J. Intente de nuevo.\n");
            setColor(DefaultColor);
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }

        //Validaciones

        // Validar que el barco sea del tamaño correcto.
        if (filaInicio == filaFin) {
            size_valid = abs(columnaFin - columnaInicio) + 1;
        } else if (columnaInicio == columnaFin) {
            size_valid = abs(filaFin - filaInicio) + 1;
        } else {
            setColor(ErrorColor);
            printf("Coordenadas no validas. El barco debe ser horizontal o vertical.\n");
            setColor(DefaultColor);
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }

        // Validar que las coordenadas de inicio y fin sean diferentes.
        if (size_valid != ship_i->size) {
            setColor(ErrorColor);
            if (size_valid == 1) {
                printf("Error: un barco debe ocupar al menos dos casillas.\n");
            } else {
                printf("Error: ese barco debe tener exactamente %d casillas.\n", ship_i->size);
            }
            setColor(DefaultColor);
            while (getchar() != '\n'); // limpio buffer
            continue;  // vuelvo a pedir coordenadas
        }

        // Validar que las coordenadas estén dentro del rango permitido.
        if (filaInicio < 0 || filaInicio >= BOARD_SIZE || filaFin < 0 || filaFin >= BOARD_SIZE ||
            columnaInicio < 0 || columnaInicio >= BOARD_SIZE || columnaFin < 0 || columnaFin >= BOARD_SIZE) {
            printf("Coordenadas fuera de rango. Asegurese de establecerlas entre 1 y 10 para filas y A-J para columnas. Intente de nuevo.\n");
            continue;
        }

        // Validar que no haya solapamiento con otros barcos y asignacion de orientacion y direccion.
        if(filaInicio == filaFin) {
            ship_i->orientation = 'H'; // Horizontal
            if (columnaInicio < columnaFin) {
                ship_i->direction = 'E'; // Este
                for (i = columnaInicio; i <= columnaFin; i++) {
                    if(matriz[filaInicio][i] != 0) {
                        solapamiento = 1;
                        break;
                    }
                }
            }else if(columnaFin < columnaInicio) {
                ship_i->direction = 'W'; // Oeste
                for (i = columnaFin; i <= columnaInicio; i++) {
                    if(matriz[filaInicio][i] != 0) {
                        solapamiento = 1;
                        break;
                    }
                }
            }
        }else if(columnaInicio == columnaFin) {
            ship_i->orientation = 'V'; // Vertical
            if (filaInicio < filaFin) {
                ship_i->direction = 'S'; // Sur
                for (i = filaInicio; i <= filaFin; i++) {
                    if(matriz[i][columnaInicio] != 0) {
                        solapamiento = 1;
                        break;
                    }
                }
            }else if(filaFin < filaInicio) {
                ship_i->direction = 'N'; // Norte
                for (i = filaFin; i <= filaInicio; i++) {
                    if(matriz[i][columnaInicio] != 0) {
                        solapamiento = 1;
                        break;
                    }
                }
            }
        }else { // Si no es horizontal ni vertical
            setColor(ErrorColor);
            printf("Coordenadas no validas. Asegurese de que el barco sea horizontal o vertical. Intente de nuevo.\n");
            setColor(DefaultColor);
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }

        if (solapamiento) {
            setColor(ErrorColor);
            printf("Ya hay un barco en esa posicion. Intente de nuevo.\n");
            setColor(DefaultColor);
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }
        
        // Validar que el barco sea del tamaño correcto para el barco actual
        if (size_valid != ship_i->size) {
            setColor(ErrorColor);
            printf("El barco debe tener exactamente %d celdas de longitud.\n", ship_i->size);
            setColor(DefaultColor);
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }

        // Guardar las coordenadas de inicio y fin del barco.
        ship_i->startShip[0] = filaInicio;
        ship_i->startShip[1] = columnaInicio;
        ship_i->endShip[0] = filaFin;
        ship_i->endShip[1] = columnaFin;
        
        // Si todas las validaciones pasan, colocar el barco.
        if (ship_i->orientation == 'H') {
            if(ship_i->direction == 'E') {
                for(i = columnaInicio; i <= columnaFin; i++) {
                    if(i == columnaInicio) {
                        matriz[filaInicio][i] = SHIP_STER; // se asigna el valor 1 para la popa del barco.
                    } else {
                        matriz[filaInicio][i] = SHIP_BODY; // se asigna el valor 2 para el cuerpo del barco.
                    }
                }
            } else if(ship_i->direction == 'W') {
                for(i = columnaInicio; i >= columnaFin; i--) {
                    if(i == columnaInicio) {
                        matriz[filaInicio][i] = SHIP_STER; // se asigna el valor 1 para la popa del barco.
                    } else {
                        matriz[filaInicio][i] = SHIP_BODY; // se asigna el valor 2 para el cuerpo del barco.
                    }
                }
            }
        } else if (ship_i->orientation == 'V') {
            if(ship_i->direction == 'S') {
                for(i = filaInicio; i <= filaFin; i++) {
                    if(i == filaInicio) {
                        matriz[i][columnaInicio] = SHIP_STER; // se asigna el valor 1 para la popa del barco.
                    } else {
                        matriz[i][columnaInicio] = SHIP_BODY; // se asigna el valor 2 para el cuerpo del barco.
                    }
                }
            } else if(ship_i->direction == 'N') {
                for(i = filaInicio; i >= filaFin; i--) {
                    if(i == filaInicio) {
                        matriz[i][columnaInicio] = SHIP_STER; // se asigna el valor 1 para la popa del barco.
                    } else {
                        matriz[i][columnaInicio] = SHIP_BODY; // se asigna el valor 2 para el cuerpo del barco.
                    }
                }
            }
        }
        // Incrementar el contador de barcos colocados.
        player_i->placed_ships++;
        ccs_colocadas = true; // Salir del bucle si todo es válido.
    }
    limpiar(); // Limpiar la pantalla después de colocar el barco.
}

// funcion para iniciar la partida. Esta funcion sera como un "main secundario" para ejecutar todas las subrutinas necesarias para llevar a cabo una partida.
void partida(){
    struct player player1, player2;
    int matriz_jug1[BOARD_SIZE][BOARD_SIZE] = {0}; // Matriz para el jugador 1.
    int matriz_jug2[BOARD_SIZE][BOARD_SIZE] = {0}; // Matriz para el jugador 2.
    int i, j;

    getchar(); // Limpiar el buffer de entrada antes de solicitar coordenadas
	limpiar(); // se limpia el menu de opciones inicial despues de haber entrado en la funcion partida, para que no estorbe.
	printf("Jugador 1:\n");
	inicializar_jugador(&player1);
    
    limpiar(); // Limpiar la pantalla después de inicializar jugadores.
    printf("Jugador 2:\n");
    inicializar_jugador(&player2);
    
    limpiar(); // Limpiar la pantalla después de inicializar jugadores.
    printf("Jugadores:\n");
    printf("Jugador 1:"); setColor(InfoColor); printf(" %s\n",player1.name); setColor(DefaultColor);
    printf("Jugador 2:"); setColor(InfoColor); printf(" %s\n",player2.name); setColor(DefaultColor);
    printf("Presione enter para ");  setColor(InfoColor); printf(" continuar.\n"); setColor(DefaultColor);
    getchar(); // Pausa antes de continuar.
    limpiar(); // Limpiar la pantalla después de mostrar los nombres de los jugadores.
    
    printf("Colocando barcos para %s\n", player1.name);
    // Colocar barcos para el jugador 1.
	for(i = 0; i < NUM_SHIPS; i++) {
        limpiar(); // Limpiar la pantalla antes de colocar barcos.
        printf("Colocando barcos de"); setColor(InfoColor); printf(" %s\n", player1.name); setColor(DefaultColor);
        imprimirTablero(matriz_jug1);
        printf("Coloca tu barco de"); setColor(InfoColor); printf(" %d ",player1.ships[i].size); setColor(DefaultColor); printf("celdas.\n");
        printf("Barco"); setColor(InfoColor); printf(" %d ",i + 1); setColor(DefaultColor); printf("de"); setColor(InfoColor); printf(" %d\n",NUM_SHIPS); setColor(DefaultColor);
        ponerBarcos(matriz_jug1, &player1.ships[i], &player1); // Registrar los barcos del jugador 1.
        setColor(SuccessColor);
        printf("Barco colocado exitosamente en");
        setColor(InfoColor); printf(" (%d, %c)\n", player1.ships->startShip[0] + 1, player1.ships->startShip[1] + 'A');
        setColor(DefaultColor);
    }
	
    

	imprimirTablero(matriz_jug1);
	
	getchar(); // Pausa antes de continuar.
}

// funcion para imprimir las reglas.
void reglas(){
	printf("Las reglas para jugar al iconico juego \"Batalla Naval\" rezan lo siguiente:\n");
	printf("1. Cada jugador contara con una flota de barcos, la cual ordenara en una distribucion que considere conveniente para ocultarla de su rival\n");
	printf("2. El juego es por turnos, y en cada turno un jugador puede escoger...\n");
	printf("Presione enter cuando haya terminado de leer las reglas\n");
	
	while (getchar() != '\n'); // Limpiar el buffer de entrada si hay caracteres sobrantes.
	getchar();
	
	limpiar();
}
