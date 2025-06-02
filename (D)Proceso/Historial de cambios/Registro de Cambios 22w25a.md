# 🛠️ **Changelog Técnico - 22w25a**

## Registro de cambios realizados

Durante la semana 22 de 2025, el proyecto Batalla Naval experimentó importantes mejoras en su estructura, documentación y robustez del código. Se reorganizó la estructura del repositorio, se refactorizaron módulos clave para facilitar el mantenimiento y se corrigieron bugs críticos, consolidando una base de código más limpia y profesional.

## Cambios realizados

---

### `ef9363c` (28-may-2025 02:00)  

**Bug fixes y refactorización integral del código base de Batalla Naval**

#### **1. Documentación y Automatización**

- **Actualización de archivos de configuración de VSCode**:
  - `launch.json` y `tasks.json` fueron adaptados para soportar el nuevo ejecutable y automatizar la limpieza y compilación.
  - Ejemplo de tarea de limpieza:

    ```json
    {
      "label": "limpiar",
      "type": "shell",
      "command": "cmd.exe",
      "args": [
        "/d", "/c", 
        "pushd \"${workspaceFolder}\" && del /f /q *.exe && del /f /q *.o && pushd src && del /f /q *.o && popd && popd"
      ],
      "problemMatcher": []
    }
    ```

#### **2. Refactorización y Limpieza**

- **Eliminación de archivos obsoletos y binarios**:
  - Se eliminaron archivos de ZinjaI, ejecutables y objetos antiguos para mantener el repositorio limpio.
- **Reestructuración del código fuente**:
  - Se eliminaron archivos y funciones duplicadas o innecesarias.
  - Se mejoró la inicialización de la consola para soportar caracteres especiales.
  - Se reorganizó la estructura del proyecto, separando headers y fuentes en carpetas `include/` y `src/`.
  - Se agregaron nuevos headers modulares como `bs_board.h`, `bs_cards.h`, `bs_ship.h`, `bs_player.h`, `bs_flow_card.h`, y un header maestro `master.h` para centralizar dependencias.

#### **3. Modularización y Nuevos Archivos**

- **Separación de responsabilidades**:
  - Se crearon archivos fuente y headers para cada módulo funcional: lógica de juego, gestión de barcos, cartas, tablero, jugador y utilidades de consola.
  - Ejemplo de nuevo header modular:

    ```c
    // filepath: codigo_fuente/include/bs_board.h
    #ifndef BS_BOARD_H
    #define BS_BOARD_H

    #include "master.h"
    // Funciones para validación y gestión de tablero
    bool validar_cc_rango(int cc_fila, int cc_columna);
    ...
    #endif
    ```

- **Renombramiento y migración de archivos**:
  - `bs_common.h` y `bs_console_utils.h` fueron renombrados y migrados a `include/bs_common.h` y `include/bs_utils.h` respectivamente, con mejoras en la definición de estructuras y utilidades.

#### **4. Corrección de Bugs y Robustez**

- **Eliminación de redundancias y mejora de validaciones**:
  - Se corrigieron errores en la función de impresión de la tabla ASCII y en la configuración de la consola.
  - Se mejoró la gestión de entradas del usuario y la validación de coordenadas.
  - Se centralizó la lógica de validación y ataque en funciones específicas para cada módulo.

---

### `8c5083e` (31-may-2025 01:13)  

**Refactorización de lógica de juego y UI para mejorar la interacción del jugador**

- **Validaciones avanzadas para solapamiento de barcos**:
  - Se añadió la función para validar el solapamiento inicial de barcos, evitando errores en la colocación:

    ```c
    bool validar_solapamiento(struct player *player, int index, int filaInicio, int filaFin, int columnaInicio, int columnaFin);
    ```

- **Mejoras en la robustez de la lógica de colocación**:
  - Ajuste de prototipos de funciones para mantener consistencia en los parámetros.
  - Validación de entradas más estricta y retroalimentación clara al usuario para evitar estados inconsistentes.

---

## Resumen Ejecutivo

- **Documentación y visualización**: Se actualizaron los archivos de configuración y documentación técnica, facilitando el seguimiento y comprensión del proyecto.
- **Refactorización y modularidad**: El código fue reorganizado en módulos más claros y robustos, eliminando redundancias y mejorando la mantenibilidad.
- **Automatización**: Se optimizaron los scripts y tareas de desarrollo, permitiendo una experiencia de desarrollo más eficiente y profesional.
- **Corrección de bugs y robustez**: Se corrigieron errores críticos en la impresión y validación de entradas, incrementando la confiabilidad del sistema.
- **Mejoras visuales**: Se centralizaron recursos de documentación y diagramas, mejorando la experiencia tanto para usuarios como para desarrolladores.

---

> **El proyecto Batalla Naval, al cierre de la semana 22 de 2025, cuenta con una base de código más limpia, modular y profesional, con una experiencia de usuario y desarrollador significativamente mejorada.**
