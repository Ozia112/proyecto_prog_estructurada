# Registro de Cambios del Repositorio

Este documento recoge exclusivamente las modificaciones a la estructura y configuración del repositorio, sin incluir cambios en el código fuente de la aplicación.

---

## [8c5083e] – 2025-05-01  

**Ámbito:** Inicialización y documentación básica  

- Se añadió un archivo .gitignore para descartar binarios, dependencias y archivos temporales.  
- Se incorporó el README.md con descripción general del proyecto y pautas de uso.  
- Se incluyó la licencia de uso (`LICENSE`, MIT).  
- Se creó `CONTRIBUTING.md` definiendo el flujo de contribución y estándares de commits.

---

## [da6cc1e] – 2025-05-15  

**Ámbito:** Integración continua y badging  

- Se habilitó GitHub Actions mediante `.github/workflows/ci.yml`:
  - Compilación automática y ejecución de pruebas unitarias en cada push.  
  - Notificaciones de estado en pull requests.  
- Se añadió badge de estado de CI en README.md.  
- Se añadió archivo `CODEOWNERS` para asignación automática de revisores en rutas clave.

---

## [ef9363c] – 2025-05-30  

**Ámbito:** Plantillas y gobernanza de issues/PR  

- Se incorporaron plantillas en `.github/ISSUE_TEMPLATE/` y `.github/PULL_REQUEST_TEMPLATE.md` para estandarizar informes de errores, solicitudes de funcionalidad y revisiones de código.  
- Se actualizó `CONTRIBUTING.md` con directrices detalladas para el uso de las plantillas y el etiquetado de issues.  
- Se configuraron reglas de branch protection y revisión obligatoria antes de merge.  

---

> Todos los cambios anteriores están disponibles para revisión en los diffs:  
>
> - `cambiosRepo-8c5083e.diff`  
> - `cambiosRepo-da6cc1e.diff`  
> - `cambiosRepo-ef9363c.diff`
