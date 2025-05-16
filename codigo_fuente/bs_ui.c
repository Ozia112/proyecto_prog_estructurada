#include "bs_ui.h" // libreria para poder usar la funcion limpiar y cambio de color.
#include "bs_console_utils.h"



void solicitar_nombre(char *nombre, int max_length) {
    printf("Introduce el nombre del jugador (maximo %d caracteres): ", max_length - 1);
    fgets(nombre, max_length, stdin);
    nombre[strcspn(nombre, "\n")] = '\0'; // Eliminar el salto de línea al final del nombre
}

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
            int temp = matriz[i][j];
            switch (temp) {
                case 0:
                    cambiar_color_txt(WATER_COLOR);
                    printf("%c ", '~');
                    cambiar_color_txt(DEFAULT_COLOR);
                    break;
                case 1:
                    cambiar_color_txt(SHIP_COLOR);
                    printf("%c ", '1'); // Carácter "×" para barco
                    cambiar_color_txt(DEFAULT_COLOR);
                    break;
                case 2:
                    cambiar_color_txt(SHIP_COLOR);
                    printf("%c ", '2'); // Carácter "¤" para barco
                    cambiar_color_txt(DEFAULT_COLOR);
                    break;
                default:
                    cambiar_color_txt(DEFAULT_COLOR); // Gris claro para cualquier otro valor
                    printf("? ");
                    break;
            }
        }
        printf("\n");
    }
}

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
            cambiar_color_txt(ERROR_COLOR);
            printf("Entrada invalida. Asegurese de ingresar un numero seguido de una letra. Intente de nuevo.\n");
            cambiar_color_txt(DEFAULT_COLOR);
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }

        puts("Coordenadas finales del barco (mismo formato).");
        if (scanf(" %d %c", &filaFin, &columnaFin_c) != 2) {
            cambiar_color_txt(ERROR_COLOR);
            printf("Entrada invalida. Asegurese de ingresar un numero seguido de una letra. Intente de nuevo.\n");
            cambiar_color_txt(DEFAULT_COLOR);
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
            cambiar_color_txt(ERROR_COLOR);
            printf("Columna invalida. Asegurese de ingresar una letra entre A y J. Intente de nuevo.\n");
            cambiar_color_txt(DEFAULT_COLOR);
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }
        
        // Convertir la letra de columna a un número (A=0, B=1, ..., J=9)
        if (columnaFin_c >= 'A' && columnaFin_c <= 'J') {
            columnaFin = columnaFin_c - 'A';
        } else {
            cambiar_color_txt(ERROR_COLOR);
            printf("Columna invalida. Asegurese de ingresar una letra entre A y J. Intente de nuevo.\n");
            cambiar_color_txt(DEFAULT_COLOR);
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
            cambiar_color_txt(ERROR_COLOR);
            printf("Coordenadas no validas. El barco debe ser horizontal o vertical.\n");
            cambiar_color_txt(DEFAULT_COLOR);
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }

        // Validar que las coordenadas de inicio y fin sean diferentes.
        if (size_valid != ship_i->size) {
            cambiar_color_txt(ERROR_COLOR);
            if (size_valid == 1) {
                printf("Error: un barco debe ocupar al menos dos casillas.\n");
            } else {
                printf("Error: ese barco debe tener exactamente %d casillas.\n", ship_i->size);
            }
            cambiar_color_txt(DEFAULT_COLOR);
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
            cambiar_color_txt(ERROR_COLOR);
            printf("Coordenadas no validas. Asegurese de que el barco sea horizontal o vertical. Intente de nuevo.\n");
            cambiar_color_txt(DEFAULT_COLOR);
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }

        if (solapamiento) {
            cambiar_color_txt(ERROR_COLOR);
            printf("Ya hay un barco en esa posicion. Intente de nuevo.\n");
            cambiar_color_txt(DEFAULT_COLOR);
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }
        
        // Validar que el barco sea del tamaño correcto para el barco actual
        if (size_valid != ship_i->size) {
            cambiar_color_txt(ERROR_COLOR);
            printf("El barco debe tener exactamente %d celdas de longitud.\n", ship_i->size);
            cambiar_color_txt(DEFAULT_COLOR);
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
    limpiar_pantalla(); // Limpiar la pantalla después de colocar el barco.
}

void reglas(){
	printf("Las reglas para jugar al iconico juego \"Batalla Naval\" rezan lo siguiente:\n");
	printf("1. Cada jugador contara con una flota de barcos, la cual ordenara en una distribucion que considere conveniente para ocultarla de su rival\n");
	printf("2. El juego es por turnos, y en cada turno un jugador puede escoger...\n");
	printf("Presione enter cuando haya terminado de leer las reglas\n");
	
	while (getchar() != '\n'); // Limpiar el buffer de entrada si hay caracteres sobrantes.
	getchar();
	
	limpiar_pantalla();
}