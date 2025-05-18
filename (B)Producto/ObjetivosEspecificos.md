## Objetivo general y específicos del sistema 
### Objetivo general
Desarrollar una aplicación de consola en lenguaje C que permita a dos jugadores competir en una partida estratégica del juego “Batalla Naval”, incorporando nuevas mecánicas como el uso de cartas de poder, movimiento dinámico de unidades, detección automática de condiciones de victoria y una estructura modular clara y funcional, como ejercicio integrador de los conocimientos adquiridos en el curso de Programación Estructurada.

### Objetivos específicos

| ID   | Objetivo específico                                                                                                                                                                                                                      |
|------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| ``OE1``  | Diseñar e implementar estructuras de datos que representen con claridad a los barcos, los tableros de juego, el sistema de cartas de poder y los jugadores.                                                                             |
| ``OE2``  | Programar una lógica de turnos automatizada, que controle de manera eficiente el flujo de juego, permitiendo alternancia, validación de acciones y retroalimentación visual al jugador.                                                 |
| ``OE3``  | Incorporar un sistema de movimiento de unidades, que permita a los jugadores modificar la posición de sus barcos durante la partida como una estrategia adicional.                                                                       |
| ``OE4``  | Desarrollar una mecánica de cartas de poder, con efectos variables que afecten al desarrollo del juego y se gestionen de forma estructurada y justa.                                                                                    |
| ``OE5``  | Gestionar las condiciones de victoria o derrota, detectando de manera automática el estado final del juego y mostrando mensajes adecuados al jugador.                                                                                   |
| ``OE6``  | Aplicar buenas prácticas de codificación, utilizando funciones bien definidas, separación por módulos, uso correcto de punteros, matrices y estructuras.                                                                                |
| ``OE7``  | Fomentar el trabajo colaborativo y documentado, mediante bitácoras, control de versiones con GitHub, y registro de avances individuales y grupales.                                                                                    |
| ``OE8``  | Lograr que la interfaz de texto sea clara, accesible y funcional, facilitando al usuario la interacción con el juego y comprendiendo el estado de la partida en todo momento.                                                           |

---

### Lista de requerimientos funcionales

| CLAVE_RF     | NOMBRE                    | DESCRIPCIÓN                                                                                                         |
|-----------|---------------------------|--------------------------------------------------------------------------------------------------------------------|
| ``BS-F01``| **Registro de jugadores** | El sistema permitirá registrar a dos jugadores solicitando un nombre identificador para cada uno.                  |
| ``BS-F02``   | **Menú Principal**        | El sistema mostrará un menú principal con las opciones: iniciar partida, leer instrucciones y salir del juego.      |
| ``BS-F03``    | **Sistema de cartas**     | El sistema asignará de forma aleatoria una carta de poder a cada jugador al inicio de su turno.                    |
| ``BS-F04``    | **Sistema de ataque**  | El sistema permitirá manipular los datos de la matriz de los jugadores para que el programa lo identifique como un disparo. |
| ``BS-F05``    | **Movimiento de barcos**  | El sistema permitirá mover un barco de posición solo si la carta activa del turno lo permite.                      |
| ``BS-F06``    | **Reporte de estado**     | El sistema gestionará el estado de cada barco, incluyendo impactos, hundimientos y eliminación del tablero.        |
| ``BS-F07``    | **Condiciones de victoria** | El sistema evaluará condiciones de victoria, finalizando la partida cuando un jugador pierda toda su flota.        |
| ``BS-F08``    | **Fin de juego**          | El sistema mostrará mensajes de fin de juego e invitará al jugador a salir o reiniciar la partida.                 |

---
### Lista de requerimientos no funcionales
| CLAVE_RNF   | **NOMBRE**                        | DESCRIPCIÓN                                                                                   |
|:-----------:|:----------------------------------|:----------------------------------------------------------------------------------------------|
| ``BS-NF02`` | **Interfaz textual clara**        | La interfaz de consola es legible, con menús y mensajes comprensibles para el usuario.         |
| ``BS-NF03`` | **Tiempo de respuesta óptimo**    | El tiempo de respuesta entre acciones es inmediato (<2 segundos) gracias a la ejecución local. |
| ``BS-NF04`` | **Modularidad**                   | El sistema está dividido en archivos independientes por función (UI, lógica, utilidades, etc). |
| ``BS-NF05`` | **Estructuras y punteros**        | Uso intensivo de estructuras, matrices y punteros para la gestión de barcos y tableros.        |
| ``BS-NF07`` | **Separación lógica-visual**      | La lógica del juego y la visualización están separadas para facilitar el mantenimiento.        |
| ``BS-NF09`` | **Retroalimentación inmediata**   | El usuario recibe mensajes claros e inmediatos ante entradas erróneas o inválidas.             |
| ``BS-NF10`` | **Portabilidad Windows**          | El sistema es portable y compatible con cualquier equipo Windows con consola estándar.         |
| ``BS-NF11`` | **Bajo consumo de recursos**      | El programa no requiere recursos elevados, permitiendo su uso en equipos de bajas prestaciones.|
 
 