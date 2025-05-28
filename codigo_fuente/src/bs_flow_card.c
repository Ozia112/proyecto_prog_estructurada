#include "bs_flow_card.h"

void funcion_carta_0(struct player *player, struct player *enemy) {
    int disparos = player->salvo ? (NUM_SHIPS - enemy->sunked_ships) : 1;
    for (int i = 0; i < disparos; i++) {
        if (i == 0) {
            printf("Dispara una vez.\n");
        } else if (i < disparos - 1) {
            mostrar_turno_y_tablero_G(player, enemy);
            printf("Dispara de nuevo.\n");
        } else {
            mostrar_turno_y_tablero_G(player, enemy);
            printf("Dispara una vez mas.\n");
        }
        pausa_consola(1.3);
        capturar_coordenada(player, enemy);
        enter_continuar();
        mostrar_turno_y_tablero_G(player, enemy); // Mostrar el tablero después de disparar.
        printf("Tablero de guerra actualizado:\n");
        mostrar_ultimo_disparo_exitoso(player); // Mostrar el último disparo exitoso.
        pausa_consola(1);
        if(player->salvo) {
            enter_continuar();
        } else break; // Si no es modo Salvo, salir del bucle después de un disparo.
    }
    enter_continuar();
}

void funcion_carta_1(struct player *player, struct player *enemy) {
    // Primer disparo
    for(int i = 1; i <= 2; i++) {
        if (i == 1) {
            printf("Dispara una vez.\n");
        } else {
            mostrar_turno_y_tablero_G(player, enemy);
            printf("Dispara de nuevo.\n");
        }
        pausa_consola(1.3);
        capturar_coordenada(player, enemy);
        enter_continuar();
        mostrar_turno_y_tablero_G(player, enemy);
        printf("Tablero de guerra actualizado:\n");
        mostrar_ultimo_disparo_exitoso(player);
        pausa_consola(1);
        enter_continuar();
    }
}

void funcion_carta_2(struct player *player, struct player *enemy) {
    for(int i = 1; i <= 3; i++) {
        if (i == 1) {
            printf("Dispara una vez.\n");
        } else if (i == 2) {
            mostrar_turno_y_tablero_G(player, enemy);
            printf("Dispara de nuevo.\n");
        } else {
            mostrar_turno_y_tablero_G(player, enemy);
            printf("Dispara una vez mas.\n");
        }
        pausa_consola(1.3);
        capturar_coordenada(player, enemy);
        enter_continuar();
        mostrar_turno_y_tablero_G(player, enemy);
        printf("Tablero de guerra actualizado:\n");
        mostrar_ultimo_disparo_exitoso(player);
        pausa_consola(1);
        enter_continuar();
    }
}

void funcion_carta_3(struct player *player, struct player *enemy) {
    if (player->ships[1].vivo) {
        printf("Su barco de %d casillas logro activar su habilidad especial.\n", player->ships[1].size);
        capturar_fila_columna(player, enemy);
    } else {
        printf("No hemos podido activar la carta. El barco de %d casillas no esta a flote.\n", player->ships[1].size);
        printf("Solo pudimos activar la carta de 1 disparo.\n");
        capturar_coordenada(player, enemy);

    }
    enter_continuar();
    mostrar_turno_y_tablero_G(player, enemy);
    printf("Tablero de guerra actualizado:\n");
    mostrar_bomb_cheq_exitoso(player);
    pausa_consola(1);
    enter_continuar();
}

void funcion_carta_4(struct player *player, struct player *enemy) {
    if (player->ships[0].vivo) {
        printf("Su barco de %d casillas logro activar su habilidad especial.\n", player->ships[0].size);
        capturar_fila_columna(player, enemy);
    } else {
        printf("No hemos podido activar la carta. El barco de %d casillas no esta a flote.\n", player->ships[0].size);
        printf("Solo pudimos activar la carta de 1 disparo.\n");
        capturar_coordenada(player, enemy);
    }

    limpiar_buffer_entrada(); // Limpiar el buffer de entrada para evitar problemas con la entrada del usuario.
    enter_continuar();
    mostrar_turno_y_tablero_G(player, enemy);
    printf("Tablero de guerra actualizado:\n");
    mostrar_bomb_cheq_exitoso(player);
    pausa_consola(1);
    enter_continuar();
}

void funcion_carta_5(struct player *player, struct player *enemy) {
    printf("Inteligencia a decifrado con exito la ubicacion de una casilla enemiga.\n");
    revela(enemy, player);
    enter_continuar();
}

void funcion_carta_6(struct player *player, struct player *enemy) {
    printf("Hemos logrado activar el radar de filas.\n");
    capturar_fila_columna(player, enemy);
    limpiar_buffer_entrada(); // Limpiar el buffer de entrada para evitar problemas con la entrada del usuario.
    enter_continuar();
    mostrar_turno_y_tablero_G(player, enemy);
    printf("Tablero de guerra actualizado:\n");
    mostrar_bomb_cheq_exitoso(player);
    pausa_consola(1);
    enter_continuar();
}

void funcion_carta_7(struct player *player, struct player *enemy) {
    printf("Hemos logrado activar el radar de columnas.\n");
    capturar_fila_columna(player, enemy);
    limpiar_buffer_entrada(); // Limpiar el buffer de entrada para evitar problemas con la entrada del usuario.
    enter_continuar();
    mostrar_turno_y_tablero_G(player, enemy);
    printf("Tablero de guerra actualizado:\n");
    mostrar_bomb_cheq_exitoso(player);
    pausa_consola(1);
    enter_continuar();
}

void funcion_carta_8(struct player *player) {
    activar_salvo(player);
    printf("\nModo Salvo activado\n");
    printf("Durante este turno NO disparas. En tu proximo turno, podras disparar multiples veces.\n");
    pausa_consola(1.3);
    enter_continuar();
}

void funcion_carta_9(struct player *player, struct player *enemy) {
    if(player->torres_acumuladas < MAX_ID_9) {
            player->torres_acumuladas++;
            printf("Has acumulado una torre de ventaja. Acumula 4 para hundir instantaneamente los barcos enemigos.\n");
            // Reducir el peso de la carta Torre de ventaja
            if (player->cartas[9].peso > 0) player->cartas[9].peso--;
    } else torre_ventaja(player);
    printf("En este turno no disparas.\n");
    enter_continuar();
}

void funcion_carta_10(struct player *player, struct player *enemy) {
    printf("Puedes disparar una vez, luego podras agarrar otra carta.\n");
    pausa_consola(1.3);
    capturar_coordenada(player, enemy);
    enter_continuar();
    mostrar_turno_y_tablero_G(player, enemy);
    printf("Tablero de guerra actualizado:\n");
    mostrar_ultimo_disparo_exitoso(player);
    pausa_consola(1);
    printf("Presiona enter para sacar otra carta.\n");
    
    sacar_carta(player, enemy);
}

void funcion_carta_11(struct player *player, struct player *enemy) {
    printf("Puedes mover un barco hacia adelante");
    pausa_consola(1.3);
    solicitar_barco(player, enemy);
    limpiar_buffer_entrada(); // Limpiar el buffer de entrada para evitar problemas con la entrada del usuario.
    enter_continuar();
    mostrar_turno_y_tablero(player);
    printf("Posicion de barco actualizada:\n");
    enter_continuar();
}