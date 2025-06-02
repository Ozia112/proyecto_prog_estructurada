#ifndef BS_CONSOLE_UTILS_H
#define BS_CONSOLE_UTILS_H

#include "master.h" // Incluye todas las cabeceras del proyecto
#include <windows.h> // Libreria para usar funciones de consola en Windows
#include <stdio.h>    // Para usar getchar() y EOF

/* Códigos ANSI básicos */
#define NEGRO           0
#define AZUL            1
#define VERDE           2
#define AQUA            3
#define ROJO            4
#define PURPUR          5
#define AMARILLO        6
#define GRIS_CLARO      7
#define GRIS_OSCURO     8
#define AZUL_CLARO      9
#define VERDE_CLARO    10
#define AQUA_CLARO     11
#define ROJO_CLARO     12
#define FUCSIA         13
#define AMARILLO_C     14
#define BLANCO         15

/* Colores específicos para el juego */
#define WATER_COLOR      AZUL_CLARO
#define ERROR_COLOR      ROJO
#define INFO_COLOR       AMARILLO
#define SHIP_COLOR       BLANCO
#define DEFAULT_COLOR    GRIS_CLARO
#define SUCCESS_COLOR    VERDE
#define INV_COLOR        NEGRO

static inline void configurar_consola_CP(int page) {

    system("chcp page > nul"); // Cambia la codificación de la consola a page para evitar problemas con caracteres especiales.
    SetConsoleCP(page);
    SetConsoleOutputCP(page);
}

static inline void limpiar_pantalla(){
	system("cls");
}

static inline void color_txt(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

static inline void limpiar_buffer_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static inline void pausa_consola(float segundos) {
    Sleep(segundos * 1000);
}

static inline void enter_continuar() {
    printf("Presione enter para ");  color_txt(INFO_COLOR); printf("continuar.\n"); color_txt(DEFAULT_COLOR);
    while (getchar() != '\n'); // Esperar a que el usuario presione enter.
    limpiar_pantalla(); // Limpiar la pantalla después de mostrar el mensaje.
}

#endif