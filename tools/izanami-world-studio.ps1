[CmdletBinding()]
param(
    [ValidateSet('Setup', 'Build', 'Test', 'Audit', 'Launch', 'Status')]
    [string]$Action = 'Status',
    [string]$PackageRoot,
    [ValidatePattern('^(0x)?[0-9a-fA-F]{8}$')]
    [string]$MapTag = '8150E00A',
    [ValidatePattern('^(0x)?[0-9a-fA-F]{8}$')]
    [string]$PreviewMesh,
    [string]$ProjectPath
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$repo = Split-Path $PSScriptRoot -Parent
$source = Join-Path $repo 'build/external/alkahest-prebl'
$support = Join-Path $PSScriptRoot 'world-studio'
$patch = Join-Path $support 'alkahest-prebl.patch'
$pin = '7455ab2db8ac0ef77789b27ab630850d7d810227'
$exe = Join-Path $source 'target/release/alkahest-prebl.exe'
$stamp = Join-Path $source '.forge-build.json'
$managed = Join-Path $source '.forge-overlays.json'
$dataRoot = Join-Path $env:LOCALAPPDATA 'IzanamiForge/WorldStudio'
$projects = Join-Path $dataRoot 'Projects'
$overlays = @{
    'forge_project.rs' = 'crates/alkahest/src/forge_project.rs'
    'forge_preview.rs' = 'crates/alkahest/src/forge_preview.rs'
    'forge_menu.rs' = 'crates/alkahest/src/gui/menu/forge.rs'
}
if (-not $PackageRoot) {
    $PackageRoot = Join-Path (Split-Path $repo -Parent) 'Destiny2-Sunrise/packages'
}
$PackageRoot = [IO.Path]::GetFullPath($PackageRoot)

function Get-InputFingerprint {
    $parts = @($pin, (Get-FileHash -LiteralPath $patch -Algorithm SHA256).Hash)
    foreach ($name in ($overlays.Keys | Sort-Object)) {
        $parts += (Get-FileHash -LiteralPath (Join-Path $support "overlay/$name") -Algorithm SHA256).Hash
    }
    $sha = [Security.Cryptography.SHA256]::Create()
    try {
        [BitConverter]::ToString($sha.ComputeHash([Text.Encoding]::UTF8.GetBytes(($parts -join '|')))).Replace('-', '')
    } finally { $sha.Dispose() }
}

function Initialize-Source {
    if (-not (Test-Path -LiteralPath $source)) {
        New-Item -ItemType Directory -Path (Split-Path $source -Parent) -Force | Out-Null
        & git clone --no-checkout --branch prebl-0.5 https://github.com/cohaereo/alkahest.git $source
        if ($LASTEXITCODE -ne 0) { throw 'Alkahest clone failed.' }
        & git -C $source checkout --detach $pin
        if ($LASTEXITCODE -ne 0) { throw 'Pinned Alkahest checkout failed.' }
    }
    $head = (& git -C $source rev-parse HEAD | Out-String).Trim()
    if ($LASTEXITCODE -ne 0 -or $head -ne $pin) {
        throw "Unexpected checkout at $source. Expected $pin. Nothing was reset."
    }
    $savedPreference = $ErrorActionPreference
    try {
        # A failed reverse check is expected on a fresh checkout, including Windows PowerShell 5.1.
        $ErrorActionPreference = 'Continue'
        & git -C $source apply --reverse --check $patch 2>$null
        $alreadyApplied = $LASTEXITCODE -eq 0
    } finally { $ErrorActionPreference = $savedPreference }
    if (-not $alreadyApplied) {
        & git -C $source apply --check $patch
        if ($LASTEXITCODE -ne 0) { throw 'Forge patch conflicts with local edits. No reset or overwrite attempted.' }
        & git -C $source apply $patch
        if ($LASTEXITCODE -ne 0) { throw 'Forge patch failed.' }
    }
    $previous = @{}
    if (Test-Path -LiteralPath $managed) {
        $state = Get-Content -LiteralPath $managed -Raw | ConvertFrom-Json
        foreach ($property in $state.PSObject.Properties) { $previous[$property.Name] = $property.Value }
    }
    $next = @{}
    foreach ($name in $overlays.Keys) {
        $from = Join-Path $support "overlay/$name"
        $to = Join-Path $source $overlays[$name]
        $hash = (Get-FileHash -LiteralPath $from -Algorithm SHA256).Hash
        if (Test-Path -LiteralPath $to) {
            $current = (Get-FileHash -LiteralPath $to -Algorithm SHA256).Hash
            if ($current -ne $hash -and (-not $previous.ContainsKey($name) -or $previous[$name] -ne $current)) {
                throw "Local changes in $to; refusing to overwrite them."
            }
        }
        Copy-Item -LiteralPath $from -Destination $to -Force
        $next[$name] = $hash
    }
    $next | ConvertTo-Json | Set-Content -LiteralPath $managed -Encoding UTF8
}

function Assert-ViewerClosed {
    $running = Get-Process -Name 'alkahest-prebl' -ErrorAction SilentlyContinue
    if ($running) { throw 'Close the external Alkahest viewer before rebuilding. Destiny can stay open.' }
}

function Install-LocalRuntime {
    $oodle = Join-Path (Split-Path $PackageRoot -Parent) 'bin/x64/oo2core_3_win64.dll'
    if (-not (Test-Path -LiteralPath $oodle)) {
        throw "Required runtime not found: $oodle. Use your matching local Shadowkeep installation."
    }
    Copy-Item -LiteralPath $oodle -Destination (Join-Path (Split-Path $exe -Parent) 'oo2core_3_win64.dll') -Force
}

function Assert-CurrentBuild {
    if (-not (Test-Path -LiteralPath $exe) -or -not (Test-Path -LiteralPath $stamp)) {
        throw 'Build World Studio first: .\tools\izanami-world-studio.ps1 -Action Build'
    }
    $built = Get-Content -LiteralPath $stamp -Raw | ConvertFrom-Json
    if ($built.inputs -ne (Get-InputFingerprint) -or $built.executable -ne (Get-FileHash -LiteralPath $exe -Algorithm SHA256).Hash) {
        throw 'World Studio build is stale or changed. Run -Action Build before launching.'
    }
    if (-not (Test-Path -LiteralPath $PackageRoot -PathType Container)) { throw "Missing packages: $PackageRoot" }
}

function Convert-TagForAlkahest([string]$NativeTag) {
    $value = [Convert]::ToUInt32(($NativeTag -replace '^0x', ''), 16)
    $bytes = [BitConverter]::GetBytes($value)
    ($bytes | ForEach-Object { $_.ToString('X2') }) -join ''
}

switch ($Action) {
    'Status' {
        [pscustomobject]@{ Executable=$exe; Built=(Test-Path -LiteralPath $stamp); Upstream=$pin;
            Packages=$PackageRoot; Projects=$projects; Scope='External static geometry; no Destiny writeback' }
    }
    'Setup' { Assert-ViewerClosed; Initialize-Source }
    { $_ -in 'Build', 'Test' } {
        Assert-ViewerClosed
        Initialize-Source
        $cargo = (Get-Command cargo -ErrorAction Stop).Source
        Push-Location $source
        try {
            if ($Action -eq 'Test') {
                & $cargo test --locked --release -p alkahest --bin alkahest-prebl forge_project::tests
            } else {
                & $cargo build --locked --release -p alkahest
            }
            if ($LASTEXITCODE -ne 0) { throw "World Studio $Action failed." }
        } finally { Pop-Location }
        if ($Action -eq 'Build') {
            Install-LocalRuntime
            @{ inputs=(Get-InputFingerprint); executable=(Get-FileHash -LiteralPath $exe -Algorithm SHA256).Hash;
                upstream=$pin; builtUtc=[DateTime]::UtcNow.ToString('o') } |
                ConvertTo-Json | Set-Content -LiteralPath $stamp -Encoding UTF8
            Write-Host "Built external editor: $exe"
        }
    }
    { $_ -in 'Audit', 'Launch' } {
        Assert-CurrentBuild
        New-Item -ItemType Directory -Path $projects -Force | Out-Null
        $viewerArgs = @($PackageRoot, '--map', (Convert-TagForAlkahest $MapTag))
        if ($Action -eq 'Audit') {
            if (-not $ProjectPath) { $ProjectPath = Join-Path $projects "$($MapTag -replace '^0x', '').audit.forge.json" }
            $ProjectPath = [IO.Path]::GetFullPath($ProjectPath)
            $viewerArgs += @('--forge-audit', $ProjectPath)
            if ($PreviewMesh) { $viewerArgs += @('--forge-preview-mesh', (Convert-TagForAlkahest $PreviewMesh)) }
            Push-Location $dataRoot
            try {
                & $exe @viewerArgs
                if ($LASTEXITCODE -ne 0) { throw 'External package/render audit failed. No game packages were changed.' }
            } finally { Pop-Location }
        } else {
            # This is the interactive editor requested by the user, not a background helper.
            $quoted = ($viewerArgs | ForEach-Object { '"' + $_ + '"' }) -join ' '
            Start-Process -FilePath $exe -ArgumentList $quoted -WorkingDirectory $dataRoot -WindowStyle Normal
        }
    }
}
