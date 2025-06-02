# Obtiene el hash (específico)
$hash = git log -1 --format="%h"
# Fecha y hora del commit en formato dd-MM-yy-HH-mm (24 hrs)
$date     = (git show -s --format=%cd --date=format:"%y-%m-%d-%H-%M" $hash).Trim()
$baseName = "$date-$hash"

# Directorio de destino
$diffDir = "(D)Proceso\Historial de cambios\Diffs"
if (-not (Test-Path $diffDir)) {
    New-Item -ItemType Directory -Path $diffDir -Force | Out-Null
}

# 1) Cambios fuera de codigo_fuente y excluyendo Historial de cambios/Diffs
$outsideFile = Join-Path $diffDir "cambiosRepo-$baseName.diff"
git show $hash -- . `
    ':(exclude)codigo_fuente/**' `
    ':(exclude)Historial de cambios/**' `
  > $outsideFile
Write-Host "Generado: $outsideFile"

# 2) Solo cambios en la carpeta codigo_fuente
$insideFile = Join-Path $diffDir "cambios-$baseName.diff"
git show $hash -- codigo_fuente/ > $insideFile
Write-Host "Generado: $insideFile"