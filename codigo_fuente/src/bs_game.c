#include "bs_game.h"

void partida() {
    struct player player1, player2;

    printf("Jugador 1:\n");
    inicializar_jugador(&player1);
    limpiar_pantalla(); // Limpiar pantalla despues del primer jugador.
    printf("Jugador 2:\n");
    inicializar_jugador(&player2);
    limpiar_pantalla(); // Limpiar la pantalla después de inicializar jugadores.
    
    printf("Jugadores:\n");
    printf("Jugador 1:"); color_txt(INFO_COLOR); printf(" %s\n",player1.name); color_txt(DEFAULT_COLOR);
    printf("Jugador 2:"); color_txt(INFO_COLOR); printf(" %s\n",player2.name); color_txt(DEFAULT_COLOR);
    enter_continuar(); // Pausa antes de continuar.
    
    // Colocar barcos para el jugador 1.
    flow_colocar_barcos(&player1); // Colocar barcos para el jugador 1.

    // Colocar barcos para el jugador 2.
    printf("Ahora es turno de"); color_txt(INFO_COLOR); printf(" %s\n", player2.name); color_txt(DEFAULT_COLOR);
    enter_continuar(); // Pausa antes de continuar.

    flow_colocar_barcos(&player2);

    // Elegir aleatoriamente quién inicia
    decidir_primer_turno(&player1, &player2);
    Sleep(1000);
    enter_continuar();

    struct player *jugador_actual, *jugador_enemigo;
    if(player1.turno == 1) {
        jugador_actual = &player1;
        jugador_enemigo = &player2;
    } else {
        jugador_actual = &player2;
        jugador_enemigo = &player1;
    }

    // Bucle principal del juego
    do {

        menu_por_turno(jugador_actual, jugador_enemigo);
    
        
        // Despues de acabar el turno, se muestra mensaje de que el turno ha terminado.
        printf("Tu turno ha terminado.\n");
        enter_continuar(); // Pausa antes de continuar.
        
        // Si el jugador actual ya ha ganado, saltar al final del ciclo.
        if (jugador_actual->enemy_hit_parts >= VICTORYCONDITION) {

        } 
        
        // Mensaje de cambio de turno
        printf("Ahora es turno de %s\n", jugador_enemigo->name);
        enter_continuar();


        // Alternar punteros (esto es lo que realmente cambia el turno)
        struct player *temp = jugador_actual;
        jugador_actual = jugador_enemigo;
        jugador_enemigo = temp;
        jugador_actual->aciertos_por_turno = 0; // Reiniciar aciertos por turno
        jugador_actual->last_successful_shot_columna = -1; // Reiniciar disparo exitoso
        jugador_actual->last_successful_shot_fila = -1; // Reiniciar disparo exitoso
        jugador_actual->last_card_id = -1; // Reiniciar ID de carta
    } while(jugador_actual->enemy_hit_parts < VICTORYCONDITION && jugador_enemigo->enemy_hit_parts < VICTORYCONDITION);

    // Mensaje de victoria
    color_txt(INFO_COLOR);
    if (player1.enemy_hit_parts >= VICTORYCONDITION) {
        printf("¡%s ", player1.name); 
    } else if (player2.enemy_hit_parts >= VICTORYCONDITION) {
        printf("¡%s ", player2.name);
    }
    color_txt(SUCCESS_COLOR);
        printf("ha ganado la partida!\n");
    color_txt(DEFAULT_COLOR);

    liberar_flota(&player1); // Liberar memoria de la flota del jugador 1.
	liberar_flota(&player2); // Liberar memoria de la flota del jugador 2.

    printf("Gracias por jugar a Batalla Naval.\n");
    printf("Presione enter para regresar al menu principal.\n");
    limpiar_buffer_entrada(); // Limpiar el buffer de entrada antes de esperar la tecla.
    limpiar_pantalla(); // Limpiar la pantalla al finalizar la partida.
}

void menu_por_turno(struct player *player, struct player *enemy) {
    char opc = ' ';
    bool loop = true;
    do {
    mostrar_turno_y_tablero_G(player, enemy);
    printf("\n");
        // Menu de opciones por turno.
    printf("Elija la opcion que desea realizar:\n");
    printf("[A]: Reporte de barcos enemigos\n");
    printf("[B]: Reporte de flota\n");
    printf("[C]: Sacar carta\n");

    scanf(" %c", &opc);
    limpiar_buffer_entrada(); // Limpiar el buffer de entrada antes de procesar la opción.
    opc = toupper(opc); // Convertir a mayúscula para evitar problemas de comparación.
        switch(opc) {
            case 'A':
                limpiar_pantalla(); //limpiar pantalla al salir del menu.
                imprimirReporteBarcosEnemigos(player, enemy);
                break;
            case 'B':
                limpiar_pantalla(); //limpiar pantalla al salir del menu.
                imprimirReporteBarcos(player, enemy);
                break;
            case 'C':
                limpiar_pantalla(); //limpiar pantalla al salir del menu.
                sacar_carta(player, enemy);
                loop = false;
                break;
            default:
                color_txt(ERROR_COLOR);
                printf("¡Tecla invalida!\n");
                color_txt(DEFAULT_COLOR);
        }
        limpiar_pantalla(); // Limpiar la pantalla después de cada opción.
    }while(loop);
}

void sacar_carta(struct player *player, struct player *enemy) {
    int carta_id = obtener_id_aleatoria(player);
    player->last_card_id = carta_id; // Guardar el ID de la carta utilizada

    mostrar_turno_y_tablero_G(player, enemy); // Mostrar el tablero de guerra si la carta no es la 11
    
    mostrar_info_carta(&player->cartas[carta_id]);

    switch (carta_id) {
    case 0:
        funcion_carta_0(player, enemy); // Carta 0: Dispara 1 tiro
        break;
    case 1:
        funcion_carta_1(player, enemy); // Carta 1: Dispara 2 tiros
        break;
    case 2:
        funcion_carta_2(player, enemy); // Carta 2: Dispara 3 tiros
        break;
    case 3:
        funcion_carta_3(player, enemy); // Carta 3: Bombardeo en fila
        break;
    case 4: 
        funcion_carta_4(player, enemy); // Carta 4: Bombardeo en columna
        break;
    case 5:
        funcion_carta_5(player, enemy); // Carta 5: Revela una celda enemiga
        break;
    case 6: 
        funcion_carta_6(player, enemy); // Carta 6: Revela una fila enemiga
        break;
    case 7:
        funcion_carta_7(player, enemy); // Carta 7: Revela una columna enemiga
        break;
    case 8:
        funcion_carta_8(player, enemy); // Carta 8: Activa el modo salvo
        break;
    case 9:
        funcion_carta_9(player, enemy); // Carta 9: Activa la torre de ventaja al acumular 4 torres
        break;
    case 10:
        funcion_carta_10(player, enemy); // Carta 10: Dipara 1 tiro y toma otra carta
        break;
    }
}