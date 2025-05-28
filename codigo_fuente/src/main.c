#include "master.h" // Incluye todas las cabeceras necesarias para el proyecto

int main() {
	srand((unsigned int)time(NULL)); // Inicializa la semilla para números aleatorios.
	pantalla_bienvenida(); // Pantalla de bienvenida.
	menu_principal(); // Menu principal.
	
	return 0; // Fin del programa.
}