# Script para sobrescribir el CHANGELOG.md con el formato solicitado

$changelog = "(D)Proceso\CHANGELOG.md"
Set-Content $changelog ""

git log --pretty=format:"%H|%ad|%an|%s" --date=format:"%d-%m-%Y" | ForEach-Object {
    $fields = $_ -split "\|"
    $hash = $fields[0].Substring(0,7)
    $date = $fields[1]
    $author = $fields[2]
    $msg = $fields[3]

    # Detectar tipo de cambio
    $files = git show --name-only --pretty="" $hash
    $isCode = $false
    $isDoc = $false
    foreach ($file in $files) {
        if ($file -like "codigo_fuente/*") { $isCode = $true }
        if ($file -like "(B)Producto/*" -or $file -like "*.md") { $isDoc = $true }
    }
    if ($isCode -and $isDoc) { $type = "R/C" }
    elseif ($isCode) { $type = "C" }
    else { $type = "R" }

    # Etiquetas personalizadas para autores
    if ($author -eq "Isaac Alejandro Ortiz Zaldivar") {
        $authorTag = "``TM-01``"
    } elseif ($author -eq "LicNico") {
        $authorTag = "``TM-02``"
    } else {
        $authorTag = "[$author]"
    }

    Add-Content $changelog "- **$hash date: $date** _type: **$type**_ | $msg $authorTag"
}