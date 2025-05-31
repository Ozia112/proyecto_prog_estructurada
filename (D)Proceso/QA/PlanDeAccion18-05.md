Con base en los archivos fuente y documentación adjunta, el **avance del proyecto** se puede estimar así:

---

## **1. Estructuras y Definiciones**
- **Estructuras de datos:** Completas y bien diseñadas (`struct ship`, `struct player`, `struct cartas`).
- **Constantes y macros:** Definidas para el tablero, barcos y cartas.
- **Avance:** **100%**

---

## **2. Lógica del Juego**
- **Inicialización de jugadores, barcos y cartas:** Implementada.
- **Colocación de barcos:** Implementada con validaciones.
- **Turnos y alternancia:** Implementados.
- **Sistema de cartas:** Implementado, con efectos básicos.
- **Ataques y efectos:** Implementados (disparo, bombardeo, chequeo, mover barco).
- **Condiciones de victoria:** Parcial (falta mostrar mensaje de fin y reinicio).
- **Avance:** **85%**

---

## **3. Interfaz de Usuario (Consola)**
- **Menú principal y bienvenida:** Implementados.
- **Menú por turno:** Implementado.
- **Impresión de tableros y reportes:** Implementados.
- **Mensajes y retroalimentación:** Presentes, aunque pueden mejorarse.
- **Avance:** **90%**

---

## **4. Modularidad y Organización**
- **Separación en archivos:** Correcta (UI, lógica, efectos, utilidades).
- **Uso de cabeceras:** Correcto.
- **Avance:** **100%**

---

## **5. Pruebas, Depuración y Detalles Finales**
- **Liberación de memoria:** Implementada.
- **Pruebas de juego completo:** No evidentes.
- **Mensajes de victoria/derrota y reinicio:** Faltan.
- **Documentación en código:** Puede mejorarse.
- **Avance:** **40%**

---

## **Porcentaje global estimado**
**Avance total:**  
**~85%**

---

# **Plan de acción para terminar el proyecto**

### **1. Terminar lógica de fin de juego**
- [ ] Detectar y mostrar mensajes claros de victoria/derrota.
- [ ] Ofrecer opción de reiniciar o salir tras el fin de la partida.

### **2. Mejorar retroalimentación y validaciones**
- [ ] Revisar y mejorar mensajes de error y éxito.
- [ ] Validar todos los posibles errores de entrada del usuario.

### **3. Pruebas y depuración**
- [ ] Jugar partidas completas para detectar bugs.
- [ ] Corregir errores de lógica o visualización.

### **4. Documentación y limpieza**
- [ ] Comentar funciones y estructuras clave.
- [ ] Agregar instrucciones de uso en README o en el menú.

### **5. (Opcional) Mejoras visuales**
- [ ] Mejorar la visualización del tablero y reportes.
- [ ] Añadir colores o símbolos para mayor claridad.

---

## **Siguiente paso inmediato**
**Implementar la detección y mensaje de fin de juego** en el ciclo principal (`partida`), y permitir reinicio o salida.

---

Claro, aquí tienes una lista de los cambios que deberías realizar en la documentación de cada biblioteca, basados en el código actual de tu proyecto:

---

### **bs_common.h**

**Cambios sugeridos en la documentación:**
- **Agregar/Actualizar campos en las estructuras:**
  - En `struct ship`, agregar el campo `bool vivo;`.
  - En `struct player`, agregar los campos:
    - `int turno;`
    - `int enemy_hit_parts;`
    - `int torres_acumuladas;`
    - `bool chequeo_fila[BOARD_SIZE];`
    - `bool chequeo_columna[BOARD_SIZE];`
    - `bool salvo;`
    - `bool buff;`
- **Actualizar la definición de la estructura `cartas`:**
  - Incluir el campo `float probabilidad;`.
- **Actualizar/Agregar defines:**
  - `VICTORYCONDITION`, `MAX_ID_10`, `NUM_CARTAS`.
  - `STER_PRINT`, `BODY_PRINT`, `WATER_PRINT`.
- **Aclarar los valores de estado en `status` (ahora 1=punta, 2=cuerpo, 3=punta dañada, 4=cuerpo dañado).**

---

### **bs_console_utils.h**

**Cambios sugeridos en la documentación:**
- **Agregar/Corregir nombres de macros:**
  - `SUCCESS_COLOR` (no `SUCCCESS_COLOR`).
- **Aclarar que los colores están definidos como macros y que la función `color_txt` es inline.**
- **Aclarar que la función `limpiar_pantalla` es inline.**
- **Actualizar la lista de colores si hay algún cambio.**

---

### **bs_logic.h / bs_logic.c**

**Cambios sugeridos en la documentación:**
- **Actualizar prototipos y descripciones de funciones:**
  - `hundido(struct player *player_i);` (verifica si un barco está hundido).
  - `inicializar_cartas`, `ajustar_probabilidades`, `obtener_id_aleatoria`, `sacar_carta`, etc.
- **Actualizar la lógica de validación de solapamiento:**  
  Ahora se valida sobre la estructura del barco, no sobre una matriz.
- **Actualizar la función `decidir_primer_turno`:**
  - Ahora asigna el campo `turno` en la estructura `player`.
- **Agregar/Actualizar funciones relacionadas con cartas y efectos especiales.**
- **Actualizar la lógica de memoria y validaciones según los nuevos campos de las estructuras.**
- **Aclarar el uso de los nuevos campos en las estructuras (`salvo`, `buff`, etc.).**

---

### **bs_ui.h / bs_ui.c**

**Cambios sugeridos en la documentación:**
- **Actualizar prototipos de funciones:**
  - `imprimirTablero` ahora recibe `struct player *` en vez de una matriz.
  - `imprimirTableroGuerra` y otras funciones también usan estructuras.
- **Agregar/Actualizar funciones:**
  - `menu_por_turno`, `capturar_coordenada`, `capturar_fila_columna`, `solicitar_barco`, etc.
- **Actualizar la lógica de impresión de tableros y reportes para reflejar el uso de las nuevas estructuras y campos.**
- **Aclarar el flujo de la función `partida` y el uso de cartas.**
- **Actualizar la documentación sobre la interacción con cartas y efectos especiales.**

---

### **bs_efectos_cartas.h / bs_efectos_cartas.c**

**Cambios sugeridos en la documentación:**
- **Agregar la descripción de todas las funciones de efectos de cartas:**
  - `disparar`, `bombardea_fila`, `bombardea_columna`, `revela`, `chequeo_fila`, `chequeo_columna`, `activar_salvo`, `desactivar_salvo`, `torre_ventaja`, `tira_toma`, `mover_barco_adelante`.
- **Aclarar el uso de los nuevos campos en las estructuras (`buff`, `salvo`, etc.).**
- **Explicar cómo interactúan estas funciones con la lógica de juego y la UI.**

---

**Resumen general:**  
La documentación debe reflejar los nuevos campos en las estructuras, los cambios en los prototipos de funciones, la lógica de cartas y efectos especiales, y el uso de estructuras en vez de matrices simples para la mayoría de las operaciones. Además, se deben actualizar los ejemplos y diagramas de flujo si es necesario.