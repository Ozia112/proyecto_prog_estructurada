#include "master.h" // Incluye todas las cabeceras necesarias para el proyecto

void impresion_ascii();

int main() {
	configurar_consola_CP(850); // Configura la consola para usar CP1252.
    srand((unsigned int)time(NULL)); // Inicializa la semilla para números aleatorios.
    limpiar_pantalla(); // Limpia la pantalla al inicio del programa.
    
	//impresion_ascii(); // Imprime la tabla de caracteres ASCII.
	pantalla_bienvenida(); // Pantalla de bienvenida.
	menu_principal(); // Menu principal.
	
	return 0; // Fin del programa.
}

void impresion_ascii() {
	printf("Caracter\tValor\n");
    for (int i = 0; i <= 255; i++) {
        // Lista de caracteres no definidos en CP1252
        if (i == 127 || i == 129 || i == 141 || i == 143 || i == 144 || i == 157)
            printf(" (ND)\t\t%d\n", i);
        else if (i >= 32 && i <= 255)
            printf("   %c\t\t%d\n", i, i);
        else
            printf("  ( )\t\t%d\n", i);
    }

	enter_continuar(); // Espera a que el usuario presione ENTER para continuar.
}