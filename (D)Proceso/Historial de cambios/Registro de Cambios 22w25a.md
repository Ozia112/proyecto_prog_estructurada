# 🚢 Batalla Naval - Registro de Cambios (Changelog) 🚢

¡Bienvenido al anuncio de actualización de **Batalla Naval**! Aquí encontrarás un resumen cronológico y estructurado de las mejoras, refactorizaciones y nuevas características implementadas en el proyecto. Solo se listan los cambios vigentes en la última versión, agrupados por fecha y commit. ¡Gracias por jugar y contribuir!

---

## 📅 28 de mayo de 2025

### Refactorización de la lógica del juego y la interfaz de usuario

- **Separación y mejora de la lógica de juego y UI** para mayor claridad y mantenibilidad.
- **Refactorización de la función `partida()`**:
  - Ahora muestra mensajes claros al finalizar el turno y al detectar la victoria.
  - Se mejoró el flujo de cambio de turno y la liberación de recursos.
- **Mejoras visuales**:
  - Mensajes de victoria con colores y agradecimientos al finalizar la partida.
  - Limpieza de pantalla y buffer de entrada en los momentos adecuados.
- **Actualización de la función `hundido()`**:
  - Mensaje más claro al desactivar el modo Salvo cuando un barco es hundido.
- **Chequeo de filas y columnas**:
  - Ahora muestra correctamente la cantidad de barcos en filas/columnas chequeadas.
  - Si una fila o columna está llena, muestra "F" (Full).
- **Eliminación de archivos y binarios obsoletos** para mantener el repositorio limpio.
- **Documentación**:
  - Se agregó un diagrama de flujo en formato Mermaid para visualizar el flujo principal del juego.

---

## 📅 31 de mayo de 2025

### Configuración de VS Code y limpieza de artefactos

- Se añade `.vscode/flow_chart.md` con diagrama de flujo en Mermaid.
- Se actualiza `launch.json` para ejecutar `battleship.exe` en terminal externa y ajustar cwd.
- Se redefine `tasks.json`:
  - Nueva tarea `limpiar` que elimina binarios y objetos (`*.exe`, `*.o`).
  - Tarea de compilación en `src/` con dependencias de limpieza y matcher de GCC.
- Se eliminan archivos obsoletos de `codigo_fuente/`:
  - Proyecto ZinjaI (`Battleship.zpr`), binarios y objetos en `Debug/`, fuentes duplicadas y ZIP.

### Modularización e inclusión de cabeceras

- **Reorganización del código fuente**:
  - Se crearon carpetas include y src para separar cabeceras y fuentes.
  - Se modularizó el código en archivos como `bs_board.c`, `bs_cards.c`, `bs_flow_card.c`, `bs_game.c`, `bs_logic.c`, `bs_player.c`, `bs_ship.c`, `bs_ui.c`.
  - Se creó el archivo maestro `master.h` para incluir todas las cabeceras relevantes.

- Se crea `include/master.h` como punto único de inclusión.
- Nueva jerarquía de módulos en `include/`:
  - bs_board.h · bs_cards.h · bs_flow_card.h · bs_game.h · bs_logic.h · bs_player.h · bs_ship.h · bs_utils.h
- En `src/`: implementaciones de cada módulo (p. ej. `bs_board.c`, `bs_cards.c`, `bs_flow_card.c`, `bs_game.c`, etc.).
- Ajustes en `bs_common.h`: renombrado de macros, ampliación de estructuras `player` y `ship`.

### Refinamiento de flujos y experiencia de usuario

- En `bs_flow_card.c`: consolidación de repetición de disparos en funciones estáticas `shot_flow` y `end_card_flow`; firmas de cartas unificadas.
- En `bs_game.c`: mensaje “Tu turno ha terminado”, agradecimiento tras victoria y retorno al menú principal.
- En `bs_ui.c`:
  - Corrección del orden de parámetros en `imprimirTableroGuerra`.
  - Uso de `barcos_en_fila` / `barcos_en_columna` para mostrar recuentos y marcar “F” cuando están completos.
  - Modularización de colocación de barcos con `flow_colocar_barcos` y `tablero_colocar_barcos`.
- En `bs_logic.c`: simplificación de `procesar_coordenadas` encadenando rangos, orientación, dimensión y solapamiento.

---

## 🚀 Próximas Features

- Pendiente a confirmar nuevas features...

---

¡Sigue atento a las próximas actualizaciones y no dudes en sugerir nuevas ideas!  
**Batalla Naval** sigue creciendo gracias a tu apoyo. 🚢✨
