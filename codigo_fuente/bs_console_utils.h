#ifndef BS_CONSOLE_UTILS_H
#define BS_CONSOLE_UTILS_H

#include <windows.h>

static inline void limpiar_pantalla(){
	system("cls");
}

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
#define SUCCCESS_COLOR   VERDE

static inline void color_txt(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

#endif