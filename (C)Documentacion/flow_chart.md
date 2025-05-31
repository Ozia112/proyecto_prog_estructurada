``` mermaid
flowchart TD
Pantalla_bienvenida --Limpiar pantalla()--> menu_principal 
menu_principal ---->partida(["partida()"])
menu_principal --limpiar_pantalla()-->Reglas(["reglas()"])
menu_principal--limpiar_pantalla()-->Mensaje_salida([Saliendo del programa])

%% Reglas
Reglas-->Mostrar_reglas--> Opc{"Press z to return main"}
Opc --Any other than z--> Reglas
Opc --Pressing z-->menu_principal

%% Partida
partida --limpiar_pantalla()-->mpt(["menu_por_turno()"])


%% Menu por turno
mpt ---->carta(["sacar_carta()"])
mpt -->rptB(["mostrar_reporte_barcos"])
mpt -->rptBE(["mostrar_reporte_barcos_enemigos"])

%% reporte barcos
rptB -->OpcB{"Press z to return main"}
OpcB --Any other than z--> rptB
OpcB --Pressing z-->mpt

%% Reporte barcos enemigos
rptBE -->OpcBE{"Press z to return main"}
OpcBE --Any other than z--> rptBE
OpcBE --Pressing z-->mpt
```
