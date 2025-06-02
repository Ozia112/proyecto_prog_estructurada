# Obtiene el hash (específico)
$hash = git log -1 --format="%h"
# Fecha y hora del commit en formato dd-MM-yy-HH-mm (24 hrs)
$date     = (git show -s --format=%cd --date=format:"%y-%m-%d-%H-%M" $hash).Trim()
$baseName = "$date-$hash"

# Directorios de destino
$repoDiffDir = ".\(D)Proceso\Historial de cambios\Diffs\RepoDiffs"
$codeDiffDir = ".\(D)Proceso\Historial de cambios\Diffs\CodeDiffs"

if (-not (Test-Path $repoDiffDir)) {
    New-Item -ItemType Directory -Path $repoDiffDir -Force | Out-Null
}
if (-not (Test-Path $codeDiffDir)) {
    New-Item -ItemType Directory -Path $codeDiffDir -Force | Out-Null
}

# 1) Cambios fuera de codigo_fuente y excluyendo Historial de cambios/Diffs
$outsideFile = Join-Path $repoDiffDir "cambiosRepo-$baseName.diff"
git show $hash -- . `
    ':(exclude)codigo_fuente/**' `
    ':(exclude)(D)Proceso/Historial de cambios/**' `
    > $outsideFile
if ((Get-Content $outsideFile).Length -eq 0) {
    "No se modificaron elementos fuera de codigo_fuente/ y (D)Proceso/Historial de cambios/" | Set-Content $outsideFile
}
Write-Host "Generado: $outsideFile"

# 2) Solo cambios en la carpeta codigo_fuente
$insideFile = Join-Path $codeDiffDir "cambios-$baseName.diff"
git show $hash -- codigo_fuente/ ':(exclude)**/*.md' > $insideFile
if ((Get-Content $insideFile).Length -eq 0) {
    "No se modificaron archivos del codigo_fuente del proyecto" | Set-Content $insideFile
}
Write-Host "Generado: $insideFile"