# Requisito Funcional 01: Registro de Jugadores

## Introducción

El registro de jugadores constituye un pilar fundamental en la arquitectura del sistema de Batalla Naval. Este proceso se implementa mediante una estructura de datos central, denominada `struct player`, que encapsula de manera eficiente toda la información relevante de cada participante. Dicha estructura es gestionada de forma global a lo largo de la ejecución del juego, permitiendo el acceso y la modificación controlada de los datos del jugador en las distintas fases de la partida.

La correcta gestión de la identidad y el estado de cada jugador es esencial para garantizar la integridad de la lógica del juego y la trazabilidad de las acciones realizadas. Además, la estructura está diseñada para facilitar la persistencia de datos, permitiendo almacenar la información en archivos de texto que pueden ser interpretados por el sistema para reanudar partidas previamente iniciadas.

A partir de la diferenciación clara entre los dos jugadores, el sistema puede asignar y gestionar de manera independiente los recursos y la memoria asociados a cada uno. Este enfoque no solo optimiza el rendimiento y la escalabilidad del sistema, sino que también sienta las bases para futuras extensiones, como la integración de nuevas mecánicas o la implementación de funcionalidades avanzadas de guardado y recuperación de partidas.

## Descripción de la estructura

La estructura de datos `player` es el núcleo para la gestión de la información de cada participante en el sistema de Batalla Naval. Este apartado detalla cada uno de los campos que la componen, explicando su propósito, alcance y la manera en que contribuyen al control y trazabilidad de la partida. La correcta definición y uso de estos elementos es fundamental para asegurar la integridad de los datos, la eficiencia en el acceso a la información y la escalabilidad del sistema ante futuras ampliaciones funcionales.  
</br>

- **Identidad y Turno:**  

  ```c
    char name[MAX_NAME_LENGTH];
  ```  

  El campo `name` almacena el nombre del jugador con un máximo de 20 caracteres utilizando la constante `MAX_NAME_LENGTH` que contiene el valor 21 (para incluir carácter nulo).  
  </br>

  ```c
    int placed_ships;
  ```  

  El campo `placed_ships` almacena la cantidad de barcos colocados por el jugador. Este campo se utiliza al principio del juego. Más detallado en [`RF03-ColocacionBarcos.md`](/(C)Documentacion/RequerimientosFuncionales/RF03-ColocacionBarcos.md).  
  </br>

  ```c
    int turno;
  ```  

  El campo `turno` almacena el turno del jugador; 1 es el que inicia la partida y 2 quien continúa. Estos valores se asignan de manera aleatoria.  
  </br>

- **Gestión de Cartas:**  
  El apartado de gestión de cartas es explicado en [`RF05-SistemaCartas.md`]  
  </br>

- **Gestión de Barcos:**  
  El arreglo `ships` contiene la información de cada barco, incluyendo su posición, estado y orientación. Los campos `enemy_hit_parts` y `sunked_ships` permiten llevar un registro del progreso del jugador respecto a la flota enemiga.
  
  ```c
    struct ship ships[NUM_SHIPS];
  ```  

  El `struct` anidado ship almacena toda la información de los barcos del jugador:  
  - ID (`int id;`).
  - Nombre (`char name[MAX_NAME_LENGTH]`).
  - Tamaño (`int size;`).
  - Dirección (`char direction;`).
  - Estado (`int **status;`).
  - Vivo (`bool vivo;`).  

  El tamaño del arreglo NUM_SHIPS equivale a 5, el tamaño establecido en las especificaciones del juego.  
  </br>

  ```c
    int enemy_hit_parts;
  ```  

  El campo `enemy_hit_parts` almacena la cantidad de casillas enemigas alcanzadas por el jugador. Cuando el jugador llega a 17 casillas alcanzadas gana automáticamente.  
  </br>

  ```c
    int sunked_ships;
  ```  

  El campo `sunked_ships` almacena la cantidad de barcos hundidos (El número de barcos enemigos con estado `bool vivo false;`).
  </br>

- **Buffers Temporales:**  
  Estos campos almacenan información relevante para la interacción del usuario, como la última coordenada ingresada, el último disparo exitoso y el ID de la última carta utilizada.
  
  ```c
    int last_input_fila;
  ```  

  El campo `last_input_fila` almacena la última coordenada correspondiente a la fila del tablero enemigo con índice base 0.  
  </br>

  ```c
    int last_input_columna;
  ```  

  El campo `last_input_columna` almacena la última coordenada correspondiente a la columna del tablero enemigo con índice base 0.  
  </br>

  ```c
    int last_successful_shot_fila;
  ```  

  El campo `last_successful_shot_fila` almacena la última coordenada correspondiente a la fila del tablero enemigo con índice base 0 solo si esta fue un disparo exitoso.  
  </br>

  ```c
    int last_successful_shot_columna;
  ```  

  El campo `last_successful_shot_columna` almacena la última coordenada correspondiente a la fila del tablero enemigo con índice base 0 solo si esta fue un disparo exitoso.  
  </br>

  ```c
    int last_card_id;
  ```  

  El campo `last_card_id` almacena la última carta obtenida por el jugador durante su turno en la partida. Sirve para gestionar los flujos de lógica dependiendo de cada carta.  
  </br>

  ```c
    int aciertos_por_turno;
  ```  

  El campo `aciertos_por_turno` almacena la cantidad de casillas enemigas alcanzadas por turno. Al final de cada turno se reinicia.  
  </br>

## Inicialización

```c
void inicializar_jugador(struct player *player);
```  

La función `inicializar_jugador` tiene como objetivo establecer los valores iniciales de todos los campos de la estructura `player` al comienzo de cada partida. Esta inicialización garantiza que los datos del jugador se encuentren en un estado consistente y libre de errores, utilizando valores predeterminados como 0 o -1 según corresponda al uso de cada campo en la lógica del juego.  

La estructura del jugador integra tanto la información de los barcos como la de las cartas. Debido a la complejidad de estos arreglos, su inicialización se delega a funciones especializadas, las cuales son invocadas dentro de la función principal de inicialización del jugador. A continuación, se detallan las inicializaciones directas de los campos principales:

- El nombre del jugador:  

  ```c
    player->name[0] = '\0';
  ```  

  Se inicializa el primer carácter del arreglo de nombre con el carácter nulo (`'\0'`). Esto asegura que el espacio de memoria destinado al nombre del jugador esté vacío antes de solicitar la entrada del usuario, evitando posibles lecturas de basura en memoria.  
  </br>

- Cantidad de barcos puestos (para colocarlos al inicio de la partida):  

  ```c
    player->placed_ships = 0;
  ```  

  Se asigna el valor cero al campo `placed_ships`, lo que permite iniciar el proceso de colocación de barcos sin inconsistencias y facilita el control del flujo durante la fase de preparación.  
  </br>

- Número de turno:  

  ```c
    player->turno = 0;
  ```  
  
  Se establece en 0 para evitar errores en las operaciones.  
  </br>

- Casillas enemigas alcanzadas:  

  ```c
    player->enemy_hit_parts = 0;
  ```  
  
  Se establece en 0 para evitar errores en las operaciones.  
  </br>

- Barcos hundidos:  
  
  ```c
    player->sunked_ships = 0;
  ```  

  Se establece en 0 para evitar errores en las operaciones.  
  </br>

- Cantidad de cartas (Torre de ventaja) acumuladas:  
  
  ```c
    player->torres_acumuladas = 0;
  ```  
  
  Se establece en 0 para evitar errores en las operaciones.  
  </br>

- Cartas de chequeo fila/columna:  
  
  ```c
    for (int i = 0; i < BOARD_SIZE; i++) {
        player->chequeo_fila[i] = false;
        player->chequeo_columna[i] = false;
        player->contador_fila[i] = 0;
        player->contador_columna[i] = 0;
    }
  ```  

  Se establece en false por defecto todas las filas y columnas (Nadie ha activado alguna carta aún).  
  Los contadores de casillas enemigas encontradas se establecen en 0 para evitar comportamientos de memoria inesperados.  
  </br>

- Última fila/columna chequeada:  
  
  ```c
    player->ultima_fila_chequeada = -1;
    player->ultima_columna_chequeada = -1;
  ```  

  Estos campos se establecen como -1 para evitar errores en la interpretación de los campos. Ya que son leídos para localizarlos en una matriz con base 0.  
  </br>

- Estados de mejora del jugador:  
  
  ```c
    player->salvo = false;
    player->buff = false;
  ```  

  Se establecen por defecto en false antes de iniciar la partida.  
  </br>

- Últimos inputs ingresados por el jugador:  
  
  ```c
    player->last_input_fila = -1;
    player->last_input_columna = -1;
    player->last_successful_shot_fila = -1;
    player->last_successful_shot_columna = -1;
    player->last_card_id = -1;
    player->aciertos_por_turno = 0;
  ```  

  Se establecen en -1 ya que almacenan coordenadas con base 0 en la matriz del jugador contrario.  
  </br>
  El campo `aciertos_por_turno` se establece en 0 ya que solo es un contador de aciertos dentro del turno. Se restablece al final de cada turno.  
  </br>

Las inicializaciones de las estructuras anidadas dentro de la estructura principal del jugador son:

- Inicialización de flota:
  
  ```c
    void inicializar_flota(struct player *player) {
        // Inicializar barcos del jugador
        for (int idx_ship = 0; idx_ship < NUM_SHIPS; idx_ship++) {
            player->ships[idx_ship].id = idx_ship; // Asignar ID del barco
            switch (idx_ship) {
              case idx_ship:
                strcpy(player->ships[idx_ship].name, "Nombre del barco");
                inicializar_barco(&player->ships[idx_ship], dimension_del_barco);
                break;
            }
        }
    }
  ```  

  Se le asigna a cada barco una ID almacenada en:  

  - ```c
      player->ships[index].id = index // Variable index va de 0 a 4
    ```  

  A cada barco se le establece un nombre dependiendo de su ID y se almacena en:  

  - ```c
      player->ships[index_ships].name // Variable index va de 0 a 4
    ```  

    A cada barco se le establece un tamaño dependiendo de su id. Los tamaños son:

    | Barco        | ID | Tamaño (casillas) |
    |--------------|----|:----------------:|
    | Portaaviones | 0  |        5         |
    | Acorazado    | 1  |        4         |
    | Crucero      | 2  |        3         |
    | Destructor   | 3  |        3         |
    | Fragata      | 4  |        2         |
  
- Inicialización de barcos:  

  ```c
    void inicializar_barco(struct ship *barco, int size)
  ```  

  En esta función se establece y almacena a cada barco las siguientes propiedades:  
  - Tamaño del barco:  

    ```c
      barco-> size = size;
    ```  

    Se establece el tamaño pasado por el parámetro `int size`.  
    </br>

  - Dirección del barco:
  
    ```c
      barco->direction = 'U';
    ```  

    Se establece en 'U' para indicar `undefined`.  
    </br>

  - Estado del barco (Vivo/Muerto):  

    ```c
      barco->vivo = true;
    ```  

    Se establece en `true`; todos los barcos se suponen vivos al iniciar partida.  
    </br>

  - Matriz `status`:  

    Coordenadas:  

    - ```c
        // CC_FILA = x || CC_COLUMNA = y
        barco->status[casilla][CC_FILA] = -1;
        barco->status[casilla][CC_COLUMNA] = -1;
      ```  

      Se establece a -1 para evitar errores en los índices de la matriz con base 0.  
      </br>

    Estado de cada casilla:

    - ```c
        barco->status[s_part][CC_STATUS] = 0;
      ```  

      Se establece en 0 (Agua) para indicar que aún no ha sido colocado en el tablero.  
    </br>

    El tamaño de la matriz en filas dependerá del tamaño del barco dado por `int size`, así se podrá asignar a cada casilla una coordenada `(x,y)` y un estado `(saludable/dañado)`.  
    </br>

    Se reserva la memoria con el tamaño del barco dada por `int size`:  

    - ```c
        barco->status = (int **)malloc(size * sizeof(int *));
      ```  

    </br>
      Se establece el tamaño de la matriz de manera dinámica dependiendo del tamaño del barco:  

    - ```c
        for (int s_part = 0; s_part < size; s_part++) {
            barco->status[s_part] = (int *)malloc(3 * sizeof(int));
        }
      ```  

    </br>

- Inicialización de Cartas:
  - La inicialización de las cartas es explicada en la documentación del requerimiento funcional [`RF05-SistemaCartas.md`]

---

## Criterios de Aceptación

- El sistema solicita y almacena correctamente el nombre de cada jugador, validando que no exceda el límite de caracteres definido por `MAX_NAME_LENGTH`.
- Al iniciar una nueva partida, ambos jugadores cuentan con sus estructuras `player` correctamente inicializadas (todos los campos en valores predeterminados).
- Los campos de la estructura `player` reflejan el estado inicial esperado: sin barcos colocados, sin cartas, sin aciertos ni disparos previos, y con los buffers temporales en valores nulos o -1 según corresponda.
- La función `inicializar_jugador` es invocada para cada jugador antes de cualquier otra acción del juego.
- El sistema diferencia correctamente entre los dos jugadores y asigna los recursos de manera independiente.
- No se permite iniciar la partida si alguno de los jugadores no ha sido registrado correctamente.
- La información de los jugadores puede ser almacenada y recuperada para reanudar partidas (si aplica persistencia).

---

## Escenarios de Uso

### Escenario 1: Registro exitoso de ambos jugadores

**Precondición:** El sistema está en el menú principal y se selecciona "Iniciar partida".  
**Flujo:**

1. El sistema solicita el nombre del Jugador 1.
2. El usuario ingresa un nombre válido (≤ 20 caracteres).
3. El sistema solicita el nombre del Jugador 2.
4. El usuario ingresa un nombre válido (≤ 20 caracteres).
5. El sistema inicializa ambas estructuras `player` y muestra el siguiente paso del juego.
**Postcondición:** Ambos jugadores están registrados y listos para colocar barcos.

### Escenario 2: Nombre de jugador inválido

**Precondición:** El sistema solicita el nombre de un jugador.  
**Flujo:**

1. El usuario ingresa un nombre vacío o mayor a 20 caracteres.
2. El sistema muestra un mensaje de error y solicita nuevamente el nombre.
**Postcondición:** El registro solo avanza cuando se ingresa un nombre válido.

### Escenario 3: Inicialización de estructuras al reiniciar partida

**Precondición:** Se selecciona la opción de reiniciar partida tras finalizar un juego.  
**Flujo:**

1. El sistema vuelve a solicitar los nombres de ambos jugadores.
2. Se inicializan nuevamente las estructuras `player` para ambos.
**Postcondición:** El sistema garantiza que no quedan datos residuales de partidas anteriores.

### Escenario 4: Persistencia de datos (opcional, si aplica)

**Precondición:** El usuario desea reanudar una partida guardada.  
**Flujo:**

1. El sistema carga los datos de los jugadores desde un archivo.
2. Se reconstruyen las estructuras `player` con la información almacenada.
**Postcondición:** Los jugadores retoman la partida con su información previa.

```mermaid
flowchart TD
  %% Escenario 4: Persistencia de datos (opcional)
  subgraph Escenario_4["Escenario 4: Persistencia de datos"]
    style Escenario_4 fill:#1F1F1F,stroke:#606060,stroke-width:2px, color:#FFFFFF
    A4["Inicio: Seleccionar Reanudar partida"]
    B4[Cargar datos de jugadores desde archivo]
    C4[Reconstruir estructuras player]
    D4[Fin: Retomar partida con información previa]
    style A4 fill:#FF60BF,stroke:#333,stroke-width:2px, color:#000000
    style B4 fill:#BBF7D0,stroke:#333,stroke-width:2px, color:#000000
    style C4 fill:#FEF08A,stroke:#333,stroke-width:2px, color:#000000
    style D4 fill:#A5B4FC,stroke:#333,stroke-width:2px, color:#000000
    A4 --> B4 --> C4 --> D4
  end

  %% Escenario 3: Inicialización de estructuras al reiniciar partida
  subgraph Escenario_3["Escenario 3: Inicialización al reiniciar partida"]
    style Escenario_3 fill:#1F1F1F,stroke:#606060,stroke-width:2px, color:#FFFFFF
    A3["Inicio: Seleccionar Reiniciar partida"]
    B3[Solicitar nombres de ambos jugadores]
    C3[Inicializar estructuras player]
    D3[Fin: Sin datos residuales]
    style A3 fill:#FF60BF,stroke:#333,stroke-width:2px, color:#000000
    style B3 fill:#BBF7D0,stroke:#333,stroke-width:2px, color:#000000
    style C3 fill:#FEF08A,stroke:#333,stroke-width:2px, color:#000000
    style D3 fill:#A5B4FC,stroke:#333,stroke-width:2px, color:#000000
    A3 --> B3 --> C3 --> D3
  end

  %% Escenario 2: Nombre de jugador inválido
  subgraph Escenario_2["Escenario 2: Nombre de jugador inválido"]
    style Escenario_2 fill:#1F1F1F,stroke:#606060,stroke-width:2px, color:#FFFFFF
    A2[Inicio: Solicitar nombre de jugador]
    B2[Ingresar nombre inválido]
    C2[Mostrar mensaje de error]
    D2[Solicitar nuevamente el nombre]
    E2[Ingresar nombre válido]
    F2[Continuar con el registro]
    style A2 fill:#FF60BF,stroke:#333,stroke-width:2px, color:#000000
    style B2 fill:#BBF7D0,stroke:#333,stroke-width:2px, color:#000000
    style C2 fill:#FEF08A,stroke:#333,stroke-width:2px, color:#000000
    style D2 fill:#A5B4FC,stroke:#333,stroke-width:2px, color:#000000
    style E2 fill:#FCA5A5,stroke:#333,stroke-width:2px, color:#000000
    style F2 fill:#FCD34D,stroke:#333,stroke-width:2px, color:#000000
    A2 --> B2 --> C2 --> D2
    D2 -->|Nombre válido| E2 --> F2
    D2 -->|Nombre inválido| B2
  end 
  
  %% Escenario 1: Registro exitoso de ambos jugadores
  subgraph Escenario_1["Escenario 1: Registro exitoso de ambos jugadores"]
    style Escenario_1 fill:#1F1F1F,stroke:#606060,stroke-width:2px, color:#FFFFFF
    A1[Inicio: Menú principal]
    B1["Seleccionar Iniciar partida"]
    C1[Solicitar nombre Jugador 1]
    D1[Ingresar nombre válido]
    E1[Solicitar nombre Jugador 2]
    F1[Ingresar nombre válido]
    G1[Inicializar estructuras player]
    H1[Mostrar siguiente paso del juego]
    I1[Fin: Jugadores listos para colocar barcos]
    style A1 fill:#FF60BF,stroke:#333,stroke-width:2px, color:#000000
    style B1 fill:#BBF7D0,stroke:#333,stroke-width:2px, color:#000000
    style C1 fill:#FEF08A,stroke:#333,stroke-width:2px, color:#000000
    style D1 fill:#A5B4FC,stroke:#333,stroke-width:2px, color:#000000
    style E1 fill:#FCA5A5,stroke:#333,stroke-width:2px, color:#000000
    style F1 fill:#FCD34D,stroke:#333,stroke-width:2px, color:#000000
    style G1 fill:#F87171,stroke:#333,stroke-width:2px, color:#000000
    style H1 fill:#FFC2AD,stroke:#333,stroke-width:2px, color:#000000
    style I1 fill:#A5FFF4,stroke:#333,stroke-width:2px, color:#000000
    A1 --> B1 --> C1 --> D1 --> E1 --> F1 --> G1 --> H1 --> I1
  end
```

---

## Conclusión

La implementación del registro de jugadores en Batalla Naval constituye un componente esencial que garantiza la integridad, trazabilidad y eficiencia en la gestión de la información de cada participante. La definición detallada de la estructura `player` y su proceso de inicialización aseguran que todos los datos relevantes se encuentren correctamente organizados y listos para su uso desde el inicio de la partida. Los criterios de aceptación y los escenarios de uso descritos validan que el sistema responde de manera robusta ante situaciones comunes y excepcionales, como el registro de nombres inválidos, la reinicialización de partidas y la persistencia de datos. Los diagramas de flujo refuerzan la claridad de los procesos involucrados, facilitando la comprensión y el mantenimiento del sistema. Este enfoque estructurado y modular no solo optimiza la experiencia del usuario, sino que también sienta bases sólidas para futuras ampliaciones, asegurando la escalabilidad y la confiabilidad del sistema a largo plazo.

---
[`RF05-SistemaCartas.md`]: /(C)Documentacion/RequerimientosFuncionales/RF05-SistemaCartas.md
