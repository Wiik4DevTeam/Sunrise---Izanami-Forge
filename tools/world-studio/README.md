# Izanami World Studio: External Geometry Workbench

An Alkahest-based external viewer/editor for Sunrise's pre-Beyond-Light packages.
This is an extension of Alkahest, not a new Tiger Engine implementation.

## Scope

- Renders actual package meshes through Alkahest's Direct3D 11 renderer.
- Uses its free camera, outliner, inspector, selection, and transform gizmos.
- Adds **Forge Project** save/open/restore commands for source-backed static instances.
- Saves position, quaternion, separate X/Y/Z scale, instance visibility, and names.
- Adds exact source identities to the inspector and saved JSON.
- Rejects changed source records, duplicate identities, wrong maps/activities,
  malformed transforms, and unsupported project versions before applying a batch.
- Fixes hidden children remaining visible in Alkahest's batched static rendering.

**These edits affect the external renderer, not the running game.** Project JSON
is not a Destiny package. Vertex/topology editing, creating collision, moving
native collision, dynamic actors, lights, sky edits, and game writeback are not
persisted by this first project format. No package promoter or game hook is called.

## Build and Run

Requires Windows x64, Rust stable/MSVC, Visual Studio C++ build tools, Git, and
your local Shadowkeep package installation and its Oodle runtime. The build uses
the committed Cargo lockfile. First-time setup downloads open-source dependencies.

From the Sunrise repository:

```powershell
.\tools\izanami-world-studio.ps1 -Action Build
.\tools\izanami-world-studio.ps1 -Action Launch
```

Launch does not rebuild. It opens the external editor on Pandora's VFX map.
Destiny does not need to be running and is never opened or closed by this script.
Viewer configuration is separate from an existing Alkahest installation. Discord
presence is off by default; the underlying executable has an explicit opt-in flag.
Close the external viewer before rebuilding it; Destiny itself may stay open.

```powershell
.\tools\izanami-world-studio.ps1 -Action Launch -MapTag 8150E06B
.\tools\izanami-world-studio.ps1 -Action Test
.\tools\izanami-world-studio.ps1 -Action Audit
.\tools\izanami-world-studio.ps1 -Action Status
```

`-PackageRoot` selects a different compatible package directory. This is not a
current-retail-Destiny viewer: its schemas target pre-Beyond-Light/Shadowkeep.

## First Edit

1. Load the default Pandora map. The existing Alkahest Activity Browser can select
   other installed maps; not every resource class is supported by this branch.
2. Open **Forge Project > Static geometry**, search `815B0FF8`, and double-click
   either result to select and frame the actual grid floor. Other meshes can be
   selected in this list, the outliner, or the viewport. The native inspector's
   **Forge Source** section exposes package-record IDs and an editable name.
3. Use the transform inspector or gizmo to move, rotate, or scale that instance.
   Use the eye control to hide it. Collection hiding is also saved for its children.
4. Choose **Forge Project > Save static project** and select a `.json` filename.
5. After reopening the same map/activity, choose **Open static project**. The
   entire static snapshot is validated before any changes are applied.

The default audit output lives in
`%LOCALAPPDATA%\IzanamiForge\WorldStudio\Projects`, outside the build directory.
Choose that folder for authored projects too, or any persistent folder you prefer.
An audit filename ends in `.audit.forge.json`; do not use that filename for your
authored work because rerunning the audit intentionally replaces its own output.

The project stores static-instance edits only. Changes to other Alkahest objects
are not included. It does not automatically switch maps when opening a project.
Restore resets static poses/visibility, retaining custom names.

## Verification and Provenance

`Audit` opens packages read-only, loads actual map geometry on a headless D3D11
device, writes a fingerprinted project, and tests edits and restoration. It also
renders the nearest static instance in isolation: original, Y-scaled, hidden,
and restored PNGs. It requires changed pixels for scale/hide and an exact pixel
match after restoration. No Destiny session or screen automation is involved.

Optional `-PreviewMesh 815B0FF8` selects a native static mesh for that render.
Some sky/translucent/special-only models are not suitable for the source-color
verification pass; a blank preview is a failed audit, not evidence of no geometry.

All IDs in Forge Source, project JSON, and `-MapTag`/`-PreviewMesh` use **native
32-bit hexadecimal**. Original Alkahest UI/CLI hashes are byte-swapped. The
PowerShell wrapper performs the conversion; do not swap its input yourself.

Provenance includes map/activity, data-table tag, resource offset, world ID,
preheader tag, static-instance table, group ordinal, transform ordinal, and mesh
tag. No transient ECS handle is persisted. Repeated ambiguous source identities
cause a failure instead of selecting a record by position or load order.

SHA-256 fingerprints cover the loaded map/activity records, static data tables,
preheaders, instance tables, and mesh descriptors. They are not a transitive
checksum of every texture, shader, vertex buffer, or collision dependency.

## Reproducible Extension

- Upstream: <https://github.com/cohaereo/alkahest/tree/prebl-0.5>
- Pinned commit: `7455ab2db8ac0ef77789b27ab630850d7d810227`
- `alkahest-prebl.patch`: minimal changes to upstream renderer/UI/loader and lockfile.
- `overlay/`: Forge-owned project, menu, and offscreen verification modules.
- Checkout: `build/external/alkahest-prebl`, intentionally outside Sunrise's DLL.
- `Setup` refuses conflicting local edits and never resets the checkout.
- `Launch` rejects a stale build when the tracked patch/overlays or executable changed.

Alkahest is by cohaereo and its contributors and is licensed under GPL-3.0.
The upstream attribution/license remain in the checkout and application. These
extension sources use GPL-3.0-or-later. Proprietary game packages and the local
Oodle DLL are not included in this extension or fetched from third parties.

See `docs/world-studio-findings-2026-09-06.md` for measured results and the next
research boundary: a narrowly validated game writer and independent collision.
