#include "bs_player.h" // Incluye definiciones de jugador

void inicializar_jugador(struct player *player) {

    // Asignar el nombre al jugador, validando que no sea vacío y no exceda 20 caracteres.
    player->name[0] = '\0'; // Inicializar el nombre como cadena vacía
    solicitar_nombre(player);

    // Inicializar estado de jugador.
    player->placed_ships = 0;
    player->turno = -1; // Turno inicial del jugador
    
    // Variables para barcos.
    inicializar_flota(player);
    player->enemy_hit_parts = 0;
    player->sunked_ships = 0;
    
    // Variables para cartas.
    inicializar_cartas(player); // Asignar informacion y pesos
    player->torres_acumuladas = 0;
    for (int i = 0; i < BOARD_SIZE; i++) { // chequeo_fila y chequeo_columna inicializados a false.
        player->chequeo_fila[i] = false;
        player->chequeo_columna[i] = false;
        player->contador_fila[i] = 0;
        player->contador_columna[i] = 0;
    }
    player->ultima_fila_chequeada = -1; // Inicializar fila chequeada a -1
    player->ultima_columna_chequeada = -1; // Inicializar columna chequeada a -1
    player->salvo = false;
    player->buff = false;
    
    // Variables de tipo buffer.
    player->last_input_fila = -1;
    player->last_input_columna = -1;
    player->last_successful_shot_fila = -1;
    player->last_successful_shot_columna = -1;
    player->last_card_id = -1;
    player->aciertos_por_turno = 0; // Inicializar aciertos por turno a 0
}

void inicializar_cartas(struct player *player) {
    // Inicializar cartas con sus IDs, nombres, probabilidades y descripciones
    player->peso_total = 0; // Inicializar peso total a 0
    for (int i = 0; i < NUM_CARTAS; i++) {
        player->cartas[i].id = i; // Asignar ID a la carta base 0
        switch (i) {
            case 0:
                strcpy(player->cartas[i].nombre, "Dispara 1 tiro");
                strcpy(player->cartas[i].descripcion, "Inserta coordenadas donde desees disparar.");
                player->cartas[i].peso = 7;
                break;
            case 1:
                strcpy(player->cartas[i].nombre, "Dispara 2 tiros");
                strcpy(player->cartas[i].descripcion, "Inserta coordenadas donde desees disparar. Hazlo de nuevo.");
                player->cartas[i].peso = 5;
                break;
            case 2:
                strcpy(player->cartas[i].nombre, "Dispara 3 tiros");
                strcpy(player->cartas[i].descripcion, "Inserta coordenadas donde desees disparar. Hazlo dos veces mas.");
                player->cartas[i].peso = 2;
                break;
            case 3:
                strcpy(player->cartas[i].nombre, "Bombardea una fila");
                strcpy(player->cartas[i].descripcion, "Si tienes tu buque de 4 casillas a flote, elige un numero y bombardea esa fila entera.");
                player->cartas[i].peso = 1;
                break;
            case 4:
                strcpy(player->cartas[i].nombre, "Bombardea una columna");
                strcpy(player->cartas[i].descripcion, "Si tienes tu buque de 5 casillas a flote, elige una letra y bombardea esa columna entera.");
                player->cartas[i].peso = 1;
                break;
            case 5:
                strcpy(player->cartas[i].nombre, "Revela");
                strcpy(player->cartas[i].descripcion, "Tu equipo de inteligencia logro descifrar la ubicacion de una parte de un barco.");
                player->cartas[i].peso = 1;
                break;
            case 6:
                strcpy(player->cartas[i].nombre, "Chequeo fila");
                strcpy(player->cartas[i].descripcion, "Tu equipo logro activar el sonar. Elige un numero y podras ver el numero de coordenadas en esa fila.");
                player->cartas[i].peso = 1;
                break;
            case 7:
                strcpy(player->cartas[i].nombre, "Chequeo columna");
                strcpy(player->cartas[i].descripcion, "Tu equipo logro activar el sonar. Elige una letra y podras ver el numero de coordenadas en esa columna.");
                player->cartas[i].peso = 1;
                break;
            case 8:
                strcpy(player->cartas[i].nombre, "Salvo");
                strcpy(player->cartas[i].descripcion, "Esta carta activa el modo Salvo. Dispara los mismos tiros que tengas en flota.");
                player->cartas[i].peso = 1;
                break;
            case 9:
                strcpy(player->cartas[i].nombre, "Torre de ventaja");
                strcpy(player->cartas[i].descripcion, "Acumula 4 tarjetas como esta para hundir instantaneamente los barcos.");
                player->cartas[i].peso = 4;
                break;
            case 10:
                strcpy(player->cartas[i].nombre, "Tira y toma");
                strcpy(player->cartas[i].descripcion, "Inserta coordenadas donde desees disparar y vuelve a generar una carta.");
                player->cartas[i].peso = 1;
                break;
            case 11:
                strcpy(player->cartas[i].nombre, "Mover hacia adelante");
                strcpy(player->cartas[i].descripcion, "Tu equipo logro obtener materiales para arreglar un motor momentaneamente.");
                player->cartas[i].peso = 1;
                break;
        }
        player->peso_total += player->cartas[i].peso;
    }
}

void reset_input(struct player *player_i) {
    player_i->last_input_fila = -1;
    player_i->last_input_columna = -1;
}

void reset_sucessful_shot(struct player *player_i) {
    player_i->last_successful_shot_fila = -1;
    player_i->last_successful_shot_columna = -1;
}

void reset_card_id(struct player *player_i) {
    player_i->last_card_id = -1;
}