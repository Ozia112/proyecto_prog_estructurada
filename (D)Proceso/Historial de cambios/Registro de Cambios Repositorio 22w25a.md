# 📁 **Changelog de Repositorio - 22w25a**

## Resumen introductorio

Durante la semana 22 de 2025, el repositorio del proyecto Batalla Naval fue sometido a una profunda reorganización y limpieza. Se realizaron cambios significativos en la estructura de carpetas, se renombraron y reubicaron archivos clave, y se mejoró la documentación para facilitar la trazabilidad y el acceso a los recursos del proyecto. Además, se corrigieron rutas en el README y se crearon nuevos formatos para el registro de cambios, consolidando así una base de trabajo más ordenada y profesional.

---

## Cambios por commit

---

### `ef9363c` (28-may-2025 02:00)

**Bug fixes and refactor of the Battleship codebase**

- **Creación de recursos de documentación:**
  - Se añadió el archivo `Propuesta 1 casos de uso.png` como recurso gráfico para la documentación de casos de uso.
- **Mejoras en la estructura de documentación interna:**
  - Se agregaron diagramas de flujo y archivos de configuración para Visual Studio Code, facilitando la comprensión y el desarrollo colaborativo.

---

### `da6cc1e` (28-may-2025 02:32)

**Refactor game and UI logic for improved clarity and functionality**

- **No hubo cambios estructurales en el repositorio, solo en el código fuente.**

---

### `4bae246` (31-may-2025 02:57)

**Add changelog and update repository structure**

- **Reubicación y renombramiento de archivos y carpetas:**
  - Se movió el archivo `Propuesta 1 casos de uso.png` a la carpeta `(C)Documentacion/`.
  - Se creó el archivo `(C)Documentacion/flow_chart.md` con un diagrama Mermaid para documentar el flujo principal del sistema.
  - Archivos administrativos y de QA fueron reubicados:
    - `AdministracionParticipativa.md` → `(D)Proceso/Proceso Administrativo/AdministracionParticipativa.md`
    - `CHANGELOG.md` → `(D)Proceso/Proceso Administrativo/CHANGELOG.md`
    - `ChangelogTutorial.md` → `(D)Proceso/Proceso Administrativo/ChangelogTutorial.md`
    - `PlanDeAccion18-05.md` → `(D)Proceso/QA/PlanDeAccion18-05.md`
    - `Rerpote de posibles bgus.md` → `(D)Proceso/QA/Rerpote de posibles bgus.md`
- **Consolidación de historial de cambios:**
  - Se renombraron y movieron todos los archivos de diffs y changelogs de la carpeta `(D)Proceso/historial_cambios/` a `(D)Proceso/Historial de cambios/`.
  - Ejemplo de cambio:

    ```diff
    rename from (D)Proceso/historial_cambios/Diffs/cambios-8c5083e.diff
    rename to (D)Proceso/Historial de cambios/Diffs/cambios-8c5083e.diff
    ```

- **Actualización de rutas en el README:**
  - Se corrigieron todas las referencias a carpetas y archivos renombrados para reflejar la nueva estructura.
  - Ejemplo:

    ```diff
    - [`historial_cambios/`](/(D)Proceso/historial_cambios/): Registro de cambios y versiones del proyecto.
    + [`historial_cambios/`](/(D)Proceso/Historial%20de%20cambios/) Registro de cambios y versiones del proyecto.
    ```

  - Se actualizaron las rutas de la carpeta `Diffs` y los changelogs para mantener la coherencia.

---

### `c12adb7`, `c67c5db`, `baa4fb2` (31-may-2025, agrupados)

**HotFix README y ajustes menores de estructura**

- **Correcciones rápidas y mejoras en la documentación:**
  - Se actualizaron y corrigieron entradas en el [README.md](http://_vscodecontentref_/0) para reflejar la nueva estructura de carpetas y archivos.
  - Se añadieron referencias a nuevos formatos de changelog:

    ```diff
    +  - [`Registro de Cambios del Repositorio 22w25a.md`](/(D)Proceso/Historial%20de%20cambios/Registro%20de%20Cambios%20del%20Repositorio%2022w25a.md)
    ```

- **Mejoras en la presentación del índice del proyecto:**
  - Se reorganizó la sección de índice para que los usuarios puedan navegar fácilmente entre documentación, producto, proceso y código fuente.

---

## Resumen de cambios

- **Reestructuración y renombramiento:**  
  Se consolidaron y renombraron carpetas y archivos clave para mejorar la organización y trazabilidad del repositorio.
- **Actualización de rutas y referencias:**  
  El [README.md](http://_vscodecontentref_/1) y otros documentos fueron actualizados para reflejar la nueva estructura, evitando enlaces rotos y facilitando la navegación.
- **Creación de nuevos formatos:**  
  Se añadieron nuevos changelogs y formatos de registro para documentar los cambios tanto en el código como en la estructura del repositorio.
- **Centralización de historial de cambios:**  
  Todos los archivos de diffs y changelogs relevantes fueron centralizados en la carpeta `(D)Proceso/Historial de cambios/`.

---

> **Con estos cambios, el repositorio del proyecto Batalla Naval es ahora más claro, ordenado y fácil de mantener, permitiendo una mejor trazabilidad y colaboración entre los miembros del equipo.**
