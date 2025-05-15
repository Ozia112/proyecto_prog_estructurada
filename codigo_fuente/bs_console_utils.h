#ifndef BS_CONSOLE_UTILS_H
#define BS_CONSOLE_UTILS_H

#include <stdio.h>

/* Códigos ANSI básicos */
#define RESET_COLOR      "\x1b[0m"
#define ANSI_NEGRO       "\x1b[30m"
#define ANSI_ROJO        "\x1b[31m"
#define ANSI_VERDE       "\x1b[32m"
#define ANSI_AMARILLO    "\x1b[33m"
#define ANSI_AZUL        "\x1b[34m"
#define ANSI_MAGENTA     "\x1b[35m"
#define ANSI_CYAN        "\x1b[36m"
#define ANSI_BLANCO      "\x1b[37m"

/* Opciones de estilo */
#define ANSI_NEGRITA     "\x1b[1m"

/* Colores específicos para el juego */
#define WATER_COLOR      ANSI_AZUL
#define ERROR_COLOR      ANSI_ROJO
#define INFO_COLOR       ANSI_AMARILLO
#define SHIP_COLOR       ANSI_CYAN
#define DEFAULT_COLOR    RESET_COLOR
#define SUCCCESS_COLOR   ANSI_VERDE

/* Función inline para cambiar color */
static inline void cambiar_color_txt(const char *ansi_code) {
    fputs(ansi_code, stdout);
}

/* Función inline para limpiar pantalla */
static inline void limpiar_pantalla(void) {
    fputs("\x1b[2J\x1b[H", stdout);  // Borra y mueve cursor al inicio
}

#endif /* BS_CONSOLE_UTILS_H */
