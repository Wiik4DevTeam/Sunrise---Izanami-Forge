[CmdletBinding()]
param(
    [ValidateSet('Status', 'Promote', 'Restore')]
    [string]$Action = 'Status',

    [string]$GameDirectory = (Join-Path $PSScriptRoot '..\..\Destiny2-Sunrise')
)

$ErrorActionPreference = 'Stop'

function Resolve-ContainedPath {
    param(
        [Parameter(Mandatory)]
        [string]$Root,

        [Parameter(Mandatory)]
        [string]$Path
    )

    $rootPath = [System.IO.Path]::GetFullPath($Root).TrimEnd('\') + '\'
    $fullPath = [System.IO.Path]::GetFullPath($Path)
    if (-not $fullPath.StartsWith($rootPath, [System.StringComparison]::OrdinalIgnoreCase)) {
        throw "Refusing path outside package directory: $fullPath"
    }
    return $fullPath
}

function Assert-DestinyClosed {
    if (Get-Process -Name destiny2 -ErrorAction SilentlyContinue) {
        throw 'Destiny 2 must be completely closed before package promotion or restore.'
    }
}

function Commit-StagedFile {
    param(
        [Parameter(Mandatory)]
        [string]$PackageRoot,

        [Parameter(Mandatory)]
        [string]$StagePath,

        [Parameter(Mandatory)]
        [string]$Suffix
    )

    $targetPath = $StagePath.Substring(0, $StagePath.Length - $Suffix.Length)
    $targetPath = Resolve-ContainedPath -Root $PackageRoot -Path $targetPath
    $backupPath = Resolve-ContainedPath -Root $PackageRoot -Path ($targetPath + '.izanami-backup')
    $temporaryPath =
        Resolve-ContainedPath -Root $PackageRoot -Path ($targetPath + '.izanami-promote-temp')

    if ((Test-Path -LiteralPath $targetPath) -and -not (Test-Path -LiteralPath $backupPath)) {
        Copy-Item -LiteralPath $targetPath -Destination $backupPath
    }
    Copy-Item -LiteralPath $StagePath -Destination $temporaryPath -Force
    if (Test-Path -LiteralPath $targetPath) {
        [System.IO.File]::Copy($temporaryPath, $targetPath, $true)
        Remove-Item -LiteralPath $temporaryPath
    } else {
        Move-Item -LiteralPath $temporaryPath -Destination $targetPath
    }

    if ($Suffix -eq '.izanami-stage') {
        $markerPath =
            Resolve-ContainedPath -Root $PackageRoot -Path ($targetPath + '.izanami-active')
        [System.IO.File]::WriteAllText($markerPath, 'Izanami authored package edit')
    }
    return $targetPath
}

$resolvedGame = (Resolve-Path -LiteralPath $GameDirectory).Path
$packageRoot = (Resolve-Path -LiteralPath (Join-Path $resolvedGame 'packages')).Path
$mainStages =
    @(Get-ChildItem -LiteralPath $packageRoot -File -Filter 'w64_pandora_0687_*.pkg.izanami-stage')
$ownerStages =
    @(Get-ChildItem -LiteralPath $packageRoot -File -Filter 'w64_pandora_0687_*.pkg.izanami-owner-stage')
$activeMarkers =
    @(Get-ChildItem -LiteralPath $packageRoot -File -Filter 'w64_pandora_0687_*.pkg.izanami-active')
$backups =
    @(Get-ChildItem -LiteralPath $packageRoot -File -Filter 'w64_pandora_0687_*.pkg.izanami-backup')

if ($Action -eq 'Status') {
    [pscustomobject]@{
        PackageDirectory = $packageRoot
        MainStages = $mainStages.Count
        OwnerStages = $ownerStages.Count
        ActiveMarkers = $activeMarkers.Count
        Backups = $backups.Count
    }
    return
}

Assert-DestinyClosed

if ($Action -eq 'Promote') {
    if ($mainStages.Count -eq 0) {
        throw 'No staged Izanami package patch was found.'
    }
    $promoted = @()
    foreach ($stage in $ownerStages) {
        $promoted += Commit-StagedFile -PackageRoot $packageRoot -StagePath $stage.FullName `
            -Suffix '.izanami-owner-stage'
    }
    foreach ($stage in $mainStages) {
        $promoted += Commit-StagedFile -PackageRoot $packageRoot -StagePath $stage.FullName `
            -Suffix '.izanami-stage'
    }
    "Promoted $($promoted.Count) staged file(s)."
    $promoted
    return
}

foreach ($marker in $activeMarkers) {
    $targetPath = $marker.FullName.Substring(0, $marker.FullName.Length - '.izanami-active'.Length)
    $targetPath = Resolve-ContainedPath -Root $packageRoot -Path $targetPath
    $backupPath = Resolve-ContainedPath -Root $packageRoot -Path ($targetPath + '.izanami-backup')
    if (Test-Path -LiteralPath $backupPath) {
        Copy-Item -LiteralPath $backupPath -Destination $targetPath -Force
    } elseif (Test-Path -LiteralPath $targetPath) {
        Remove-Item -LiteralPath $targetPath
    }
    Remove-Item -LiteralPath $marker.FullName
}
foreach ($backup in $backups) {
    $targetPath = $backup.FullName.Substring(0, $backup.FullName.Length - '.izanami-backup'.Length)
    $targetPath = Resolve-ContainedPath -Root $packageRoot -Path $targetPath
    Copy-Item -LiteralPath $backup.FullName -Destination $targetPath -Force
}
"Restored package targets from $($backups.Count) backup(s) and removed active Izanami patches."
