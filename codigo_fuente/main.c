#include <stdio.h> // libreria para poder usar la funcion printf.
#include <stdlib.h> // libreria para poder usar la funcion system.
#include "bs_common.h" // Incluye definiciones comunes
#include "bs_console_utils.h" // libreria para poder usar la funcion limpiar y cambio de color.
#include "bs_logic.h" // libreria para poder usar funciones de logica.
#include "bs_ui.h" // libreria para poder usar funciones de UI.
#include <string.h> // libreria para poder usar la funcion strcspn.

void partida(); // Prototipo de la funcion partida.
int main() {
	pantalla_bienvenida(); // Pantalla de bienvenida.
	limpiar_pantalla(); // Limpiar la pantalla después de la bienvenida.
	menu_principal(); // Menu principal.
}