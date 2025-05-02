# Propuesta de proyecto: Juego de Dados con Ranking
## Introducción
La implementación de un juego de dados con múltiples jugadores ofrece una manera divertida y didáctica de aplicar los conceptos centrales del curso de programación en C. Esta propuesta busca desarrollar un sistema interactivo que simule partidas entre jugadores, registre resultados y mantenga un ranking competitivo, todo dentro de una interfaz por consola.

## Características Propuestas
Inspirado en los juegos clásicos de dados, este proyecto se centrará en una experiencia sencilla pero sólida en cuanto a lógica de programación:

- ``Simulación de Tiradas``: Se utilizará la generación de números aleatorios para emular las tiradas de dados, lo que introduce el concepto de azar controlado en el juego.

- ``Puntaje por Rondas``: En cada ronda, los jugadores lanzan dados y se les asignan puntos según reglas definidas (por ejemplo: suma de dados, dobles, bonificaciones).

- ``Registro de Jugadores``: Se permitirán partidas con múltiples jugadores, cada uno con su nombre y puntaje almacenado en una estructura dinámica.

- ``Sistema de Ranking``: Al finalizar la partida, los puntajes se guardarán en un archivo. El juego podrá mostrar un ranking ordenado de los mejores jugadores.

- ``Expansión de Reglas (Opcional)``: Se podrán añadir reglas especiales como penalizaciones, turnos perdidos, o bonificaciones por tiradas especiales.

## Aplicaciones de Conocimientos del Curso
Este proyecto abarca múltiples temas clave del curso:

- ``Uso de Structs``: Representación de jugadores con atributos como nombre y puntaje.

- ``Punteros y Arreglos Dinámicos``: Gestión dinámica de múltiples jugadores mediante memoria asignada en tiempo de ejecución.

- ``Generación Aleatoria``: Uso de funciones estándar para simular dados (``rand()``), aplicando correctamente ``srand()`` para resultados variados.

- ``Manejo de Archivos``: Escritura y lectura de puntajes en archivos para mantener persistencia de datos entre partidas.

- ``Ordenamiento y Comparaciones``: Implementación de funciones para ordenar y mostrar rankings según puntajes.

## Conclusión
Este juego de dados representa un proyecto motivador, accesible y útil para afianzar conceptos como structs, punteros, archivos y lógica condicional. Además, fomenta la creatividad al permitir la creación de reglas personalizadas. Su enfoque competitivo, unido a una estructura de código modular, lo convierte en una herramienta ideal para consolidar habilidades de programación en C y disfrutar el proceso de aprendizaje en equipo.

Documento redactado por: ``TM-02``


# Project Proposal: Dice Game with Score Ranking
## Introduction
Implementing a dice game with multiple players offers a fun and educational way to apply core C programming concepts. This project aims to develop an interactive system that simulates rounds between players, records results, and maintains a competitive ranking board—all through a console-based interface.

## Proposed Features
Inspired by classic dice games, this project will focus on a simple yet solid logic-driven experience:

- ``Dice Roll Simulation``: Random number generation will be used to simulate dice rolls, introducing the concept of controlled randomness.

- ``Round-Based Scoring``: In each round, players roll dice and earn points according to predefined rules (e.g., sum of dice, doubles, bonuses).

- ``Player Registration``: The game will support multiple players, each with a name and score stored in a dynamic structure.

- ``Ranking System``: After the game, scores will be saved to a file. The game will display a sorted ranking of top players.

- ``Rule Expansion (Optional)``: Special rules may be added, such as penalties, skipped turns, or bonuses for special rolls.

## Course Knowledge Applications
This project covers several key topics from the course:

- ``Use of Structs``: Representing players with attributes such as name and score.

- ``Pointers and Dynamic Arrays``: Managing multiple players using memory allocated at runtime.

- ``Random Number Generation``: Using standard functions to simulate dice (``rand()``), with proper use of ``srand()`` for varied results.

- ``File Handling``: Writing and reading scores to/from files for persistent data between sessions.

- ``Sorting and Comparisons``: Implementing functions to sort and display the leaderboard by score.

## Conclusion
This dice game is a motivating, accessible, and practical project to reinforce concepts such as structs, pointers, files, and conditional logic. It also encourages creativity by allowing the creation of custom rules. Its competitive nature and modular structure make it an ideal tool for consolidating C programming skills while enjoying the learning process as a team.

Written by: ``TM-02``
