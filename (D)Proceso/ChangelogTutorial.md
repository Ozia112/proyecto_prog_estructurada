# 📑 ChangelogTutorial

## Uso del Script de Generación Automática de CHANGELOG

Este tutorial describe el procedimiento paso a paso para ejecutar correctamente el script de generación automática de changelog en un entorno Windows, asegurando el cumplimiento de las políticas de seguridad y las mejores prácticas corporativas.

---

## 🛠️ Requisitos Previos

- Tener instalado **Git** y **PowerShell**.
- Contar con permisos de administrador en el equipo.
- Ubicar el script `generate-changelog.ps1` en la raíz de su repositorio.

---

## 1️⃣ Abrir PowerShell como Administrador

1. Presione `Windows + S` y escriba `PowerShell`.
2. Haga clic derecho sobre **Windows PowerShell** y seleccione **Ejecutar como administrador**.
3. Se abrirá una ventana en la ruta predeterminada:  
   ```
   C:\Windows\System32
   ```

---

## 2️⃣ Navegar a la Carpeta del Repositorio

Utilice el comando `cd` para llegar a la carpeta donde se encuentra su repositorio.  
Por ejemplo, si su repositorio está en:

```
C:\Users\HP\Documents\GitHub\Repositorio
```

Ejecute:

```powershell
cd C:\Users\HP\Documents\GitHub\Repositorio
```

---

## 3️⃣ Deshabilitar la Política de Seguridad de Scripts (si es necesario)

Por defecto, Windows restringe la ejecución de scripts. Para permitir la ejecución de su script, ejecute:

```powershell
Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy RemoteSigned
```

- Si se solicita confirmación, escriba `S` y presione Enter.
- **Nota:** Esto solo afecta al usuario actual y es reversible.

---

## 4️⃣ Ejecutar el Script de Generación de Changelog

Con la terminal ubicada en la carpeta del repositorio, ejecute:

```powershell
.\generate-changelog.ps1
```

El script analizará el historial de commits y sobrescribirá el archivo `CHANGELOG.md` con el formato corporativo requerido.

---

## 5️⃣ (Opcional) Restaurar la Política de Seguridad

Si desea restablecer la política de seguridad después de ejecutar el script, utilice:

```powershell
Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy Restricted
```

---

## 📝 Notas Finales

- Asegúrese de tener todos los cambios guardados y el repositorio actualizado antes de ejecutar el script.
- El changelog generado es fundamental para la trazabilidad y auditoría de cambios en proyectos corporativos.
- Si tiene dudas, consulte con el área de soporte técnico o desarrollo.

---
Documento escrito por: ``TM-01``