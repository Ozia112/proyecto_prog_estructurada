# 🛠️ **Changelog Técnico - 22w25a**

## Registro de cambios realizados

Durante la semana 22 de 2025, el proyecto Batalla Naval experimentó importantes mejoras en su estructura, documentación y robustez del código. Se implementaron diagramas de flujo para visualizar la lógica principal, se reorganizó la estructura del repositorio y se refactorizaron módulos clave para facilitar el mantenimiento. Además, se corrigieron bugs críticos y se mejoró la experiencia de usuario en consola, consolidando una base de código más limpia y profesional.

## Cambios realizados

### `ef9363c` (28-may-2025 02:00)  

**Bug fixes and refactor of the Battleship codebase**

#### **1. Documentación y Diagramas**

- **Nuevo diagrama de flujo** en Mermaid para visualizar la lógica principal del juego.

  ```mermaid
  flowchart TD
      A[Start - main.c] --> B["Initialize Game - partida()"]
      B --> C[Initialize Players]
      C --> D[Place Ships - colocar_barcos_jugador]
      D --> E[Randomly Select First Turn]
      E --> F[Main Game Loop]
      F --> G{Player Turn}
      G --> H[Display Turn Menu - menu_por_turno]
      H --> I{Menu Options}
      I -->|A: Draw Card| J[sacar_carta Function]
      I -->|B: Fleet Report| K[Show Player Fleet Report]
      I -->|C: Enemy Fleet Report| L[Show Enemy Fleet Report]
      K --> H
      L --> H
      J --> M[Get Random Card ID]
      M --> N[Display Board]
      N --> O[Show Card Info]
      O --> P{Card Type?}
      P -->|Card 0| Q0[Single Shot or Salvo]
      P -->|Card 1| Q1[Double Shot]
      P -->|Card 2| Q2[Triple Shot]
      P -->|Card 3| Q3[4-Block Ship Special Attack]
      P -->|Card 4| Q4[5-Block Ship Special Attack]
      P -->|Card 5| Q5[Reveal Enemy Position]
      P -->|Card 6| Q6[Row Radar Attack]
      P -->|Card 7| Q7[Column Radar Attack]
      P -->|Card 8| Q8[Activate Salvo Mode]
      P -->|Card 9| Q9[Tower Accumulation]
      P -->|Card 10| Q10[Single Shot + Draw Another Card]
      P -->|Card 11| Q11[Move Ship Position]
      Q10 --> J
      Q0 --> R[End Turn]
      Q1 --> R
      Q2 --> R
      Q3 --> R
      Q4 --> R
      Q5 --> R
      Q6 --> R
      Q7 --> R
      Q8 --> R
      Q9 --> R
      Q11 --> R
      R --> S{Victory Condition Met?}
      S -->|No| T[Switch Active Player]
      T --> G
      S -->|Yes| U[Display Winner]
      U --> V[End Game]
  ```

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
  - Archivos de ZinjaI, ejecutables y objetos antiguos fueron removidos para mantener el repositorio limpio.
- **Reestructuración del código fuente**:
  - Se eliminaron archivos y funciones duplicadas o innecesarias.
  - Se mejoró la inicialización de la consola para soportar caracteres especiales.

#### **3. Corrección de Bugs**

- **Impresión de caracteres ASCII**:
  - Se corrigieron errores en la función de impresión de la tabla ASCII y en la configuración de la consola.
- **Robustez en la UI**:
  - Mejoras en la función de impresión de la tabla ASCII y en la gestión de entradas del usuario.

---

### `4bae246` (31-may-2025 02:57)  

**Add changelog and update repository structure**

- **Documentación y estructura**:
  - Se añadió un changelog detallado.
  - Se reorganizó la estructura del repositorio, moviendo documentación y archivos de cambios a carpetas específicas.
  - Se eliminó el archivo de flujo antiguo `flow_chart.md` para centralizar la documentación.

---

### `8c5083e` (31-may-2025 01:13)  

**Refactor game logic and UI for improved player interactions**

- **Refactorización de lógica y UI**:
  - Se añadieron nuevas validaciones para el solapamiento inicial de barcos:

    ```c
    bool validar_solapamiento_inicial(struct player *player, int index, int filaInicio, int columnaInicio);
    ```

  - Se mejoró la robustez de la lógica de colocación de barcos y la interacción con el usuario.
- **Mejoras en la robustez**:
  - Ajuste de prototipos de funciones para mantener consistencia en los parámetros.
  - Mejor validación de entradas y retroalimentación al usuario.

---

## Resumen Ejecutivo

- **Documentación y visualización**: Se añadieron diagramas de flujo y changelogs para facilitar el seguimiento de cambios y la comprensión del proyecto.
- **Refactorización y modularidad**: El código fue reorganizado en módulos más claros y robustos, facilitando el mantenimiento y la escalabilidad.
- **Automatización**: Se mejoraron los scripts y tareas de desarrollo para una experiencia más fluida.
- **Corrección de bugs y robustez**: Se corrigieron errores críticos y se mejoró la validación de entradas, haciendo el sistema más confiable.
- **Mejoras visuales**: Se actualizaron y centralizaron los recursos de documentación y diagramas para una mejor experiencia de usuario y desarrollador.

---

> **El proyecto Batalla Naval, al cierre de la semana 22 de 2025, cuenta con una base de código más limpia, modular y profesional, con una experiencia de usuario y desarrollador significativamente mejorada.**
