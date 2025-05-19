## Documentación de la Biblioteca [`bs_console_utils.h`]

La biblioteca [`bs_console_utils.h`] proporciona utilidades para la manipulación de la consola en Windows, enfocadas en la limpieza de pantalla y el manejo de colores de texto, facilitando la creación de interfaces de usuario más amigables y visualmente atractivas para el juego Batalla Naval.

---

## Funciones

### `limpiar_pantalla()`
```c
static inline void limpiar_pantalla(){
    system("cls");
}
```
**Descripción:**  
Limpia la pantalla de la consola utilizando el comando `cls` de Windows. Es una función inline para minimizar la sobrecarga de llamada y se utiliza frecuentemente para refrescar la interfaz entre menús o turnos.

---

### `color_txt(int color)`
```c
static inline void color_txt(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
```
**Descripción:**  
Cambia el color del texto en la consola. Utiliza la función de la API de Windows `SetConsoleTextAttribute` para modificar el color de salida de texto según el valor entero recibido. Permite resaltar mensajes de error, información, éxito, etc.

---

## Macros de Colores

La biblioteca define una serie de macros para facilitar el uso de colores en la consola. Estos valores corresponden a los códigos de color estándar de la consola de Windows.

- `NEGRO` (0)
- `AZUL` (1)
- `VERDE` (2)
- `AQUA` (3)
- `ROJO` (4)
- `PURPUR` (5)
- `AMARILLO` (6)
- `GRIS_CLARO` (7)
- `GRIS_OSCURO` (8)
- `AZUL_CLARO` (9)
- `VERDE_CLARO` (10)
- `AQUA_CLARO` (11)
- `ROJO_CLARO` (12)
- `FUCSIA` (13)
- `AMARILLO_C` (14)
- `BLANCO` (15)

### Colores específicos para el juego

- `WATER_COLOR` (`AZUL_CLARO`): Color para representar el agua en el tablero.
- `ERROR_COLOR` (`ROJO`): Color para mensajes de error.
- `INFO_COLOR` (`AMARILLO`): Color para mensajes informativos.
- `SHIP_COLOR` (`BLANCO`): Color para representar los barcos.
- `DEFAULT_COLOR` (`GRIS_CLARO`): Color por defecto para el texto.
- `SUCCCESS_COLOR` (`VERDE`): Color para mensajes de éxito.

---

## Uso típico

- **Limpieza de pantalla:**  
  Se llama a `limpiar_pantalla()` para borrar la consola antes de mostrar un nuevo menú o tablero.
- **Coloreado de texto:**  
  Se utiliza `color_txt(COLOR)` antes de imprimir mensajes para resaltar información relevante, errores o estados del juego.

---

> Notas
>
>- Estas utilidades están diseñadas específicamente para sistemas Windows, ya que dependen de la API de consola de este sistema operativo.
>
>- El uso de colores mejora la experiencia del usuario, facilitando la identificación de diferentes tipos de mensajes y estados en el juego.
   
---

[`bs_console_utils.h`]: ../../codigo_fuente/bs_console_utils.h