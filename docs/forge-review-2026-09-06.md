# Forge Review: September 6, 2026

## Scope and evidence

Reviewed the local launch protocol, native spawn/transform bridge, Explorer ownership,
group persistence, package builder, relevant logs, shared research document, and current
upstream changes. Base checkout: `e86bfaf2` on `izanami-forge`; upstream fetched through
`ae465b0f`. Pre-existing worktree edits were retained. This was a targeted integration,
not a merge of all upstream changes or an exhaustive audit of every game subsystem.

Evidence labels below are literal: **code-confirmed**, **offline-tested**, **user-reported**,
or **unverified in-game**. The latest saved failure logs predate the recent upstream
integration; they cannot validate this build. Destiny was not launched for this review.

The shared Google Doc's front-page date, review status, research priorities and historical
summary label were updated and read back. A larger insert was rejected by the provider;
the compact front-page update succeeded. This file contains the full review. No historical
research sections or the linked asset-type addendum were deleted.

## Implemented fixes

### Launch protocol

1. **Receiving host port:** connect responses now advertise the receiving host's UDP port,
   with the existing advertised port only as a fallback when no receiving port is available.
   Previously every host could respond with the primary port, conflicting with the native
   client's channel identity. Adapted from upstream `f9a62072`,
   [PR 103](https://github.com/stanuwu/Sunrise/pull/103).
   Source: `Sunrise/src/server/gameplay/peer/peer_out_of_band.cpp`, `local_address`.

2. **Loading versus arrival:** loading presentation uses instantiated-region readiness;
   the player-spawn gate separately waits for the client's world-arrival report. Reusing
   the arrival gate for both could hold loading indefinitely or mishandle the fade/spawn
   ordering. Adapted from upstream `8a34b7f6`, also PR 103.
   Sources: `activity_roster_snapshot.cpp`, `activity_roster_push.cpp`, `internal.h` in
   `Sunrise/src/server/bap/encrypted/push/activity/`.

3. **Map-generator auth body:** the empty type-37 body is 1,750 bits, not 998. Two fixed
   arrays contain 32 and 64 bytes, not one byte each. The old encoding was 752 bits short,
   potentially misaligning the rest of a roster message. Adapted from upstream `8f96fbb7`,
   [PR 105](https://github.com/stanuwu/Sunrise/pull/105).
   Source: `Sunrise/src/middleware/bap/activity_message/activity_sensor_auth_bodies.cpp`.
   The regression test independently walks the schema and checks a nonzero following-field
   sentinel, rather than merely comparing the writer with its own size constant.

These are concrete protocol corrections, not proof that every destination now launches.
No Tower destination selector was rewritten. The protocol code is shared, so both Tower
control and Pandora still need runtime regression tests.

### Native object editing

- Pending transforms now coalesce by the **full native handle**. The old append plus
  swap-removal behavior could execute A1, A3, A2 for one object, leaving a stale transform.
  New edits replace the pending value for that object rather than accumulating old drag frames.
- The queue no longer silently discards an accepted request to admit another one. Group
  transforms preflight and enqueue as one batch; an invalid member or capacity failure
  rejects the batch before changing the editor model. Capacity is 1,024 distinct handles.
  Queue acceptance is atomic; execution in Destiny is not transactional and can still fail
  later if a handle expires. That distinction remains important.
- Properties and transform undo/redo do not commit their state when queue admission fails.
- Spawn observations are copied under one lock, preventing mixed fields from different
  observations. An expired request produces an explicit timeout, including when the
  player-update hook is not servicing spawns. Absolute world-position requests no longer
  require a camera pose unless camera-dependent placement or rotation was requested.
- Explorer refresh no longer guesses authored-to-live ownership from matching tags/types
  and nearby positions, or automatically replays saved edits onto those guesses. Separate
  live-handle rows remain editable when their transforms are known. Package-placement
  rows remain staging-only until exact runtime ownership is established.

Sources: `Sunrise/src/client/hooks/spawn/activation_queue.h`, `spawn_runtime.cpp/.h`, and
`Sunrise/src/izanami/editor/ui/forge_shell.cpp`.

### Persistence

- Fate map recipes now preserve virtual groups, nested hierarchy, names, pivots, and child
  transforms. Replay recreates virtual groups without trying to spawn them as native assets.
- New saves use format version 2; existing version-1 recipes still load. Old DLLs cannot
  read version-2 saves, so retain a copy of important old recipes before rolling back builds.
- Writes stage beside the save and replace it only after a completed write. A denied
  replacement leaves the previous valid save intact.
- Parent validation uses indexed, iterative cycle detection. The full 8,192-node nested
  hierarchy is tested without recursive stack depth or repeated whole-scene scans.

Sources: `Sunrise/src/izanami/fate/map_recipe.cpp/.h` and the shell's `quick_save`/`quick_load`.
This saves Forge scene instructions, not a newly authored Destiny package or stock-map edits.

## Verification

- Full `steam_api64` Release DLL build: successful.
- Three standalone CTest executables: passed, with assertions enabled in Release.
- Packet tests: type-37 schema, following-field alignment, undersized output buffer.
- Queue tests: newest transform wins, generation-bearing handle identity, full-queue batch
  rejection without partial replacement, erase/reuse behavior.
- Recipe tests: nested groups, names and transforms, version-1 compatibility, cycles,
  missing parents, duplicate IDs, invalid scale, truncated input, failed replacement preserving
  the old save, and the 8,192-node hierarchy limit.
- `git diff --check`: passed.
- No in-game launch, collision, deletion, group replay, or rendered UI validation was performed.

The verified DLL was deployed to `B:\!!izanami\Destiny2-Sunrise\bin\x64\steam_api64.dll`
with Destiny closed. SHA-256:
`4FB9A7FE81DA45CAE17C7F6AA51872CF0D86F30D5656C7C5BCEFCF661D69A1C5`.
The previous DLL is preserved at
`build/deployment-backups/steam_api64-before-review-20260906-211058.dll`.
No package files were promoted, and no game launch was performed.

Run the regression suite from the repository in PowerShell:

```powershell
& 'C:\Program Files\CMake\bin\cmake.exe' -S tools/tests -B build/forge-tests -A x64
& 'C:\Program Files\CMake\bin\cmake.exe' --build build/forge-tests --config Release -- /m
& 'C:\Program Files\CMake\bin\ctest.exe' --test-dir build/forge-tests -C Release --output-on-failure
```

## High-priority research topics

| Priority | Finding and certainty | Next proof needed |
| --- | --- | --- |
| 1 | **Code-confirmed:** current Pandora blank draft preserves direct Havok, entity-model, visibility, unknown infrastructure, and protected entity records. Visual suppression is not collision removal. | Trace the known working baseplate's exact render and collision owners; test one isolated render/collision pair before tiling. Preserve spawn/system records explicitly. |
| 1 | **User-reported:** native Pandora entry and its original platform collision worked in earlier runs. **Unverified:** repeatability on this integration. | Fresh-process Tower control, then unmodified native Pandora direct launch; capture host port, region-ready, world-state, spawn-gate and roster widths. Do not mix edited-package testing into the first control. |
| 1 | **Code-confirmed:** asset tag and proximity do not establish which occurrence owns a runtime object. Static aggregate pieces need not be individual entity datums. | Record exact resource/placement provenance during native creation or load, including generation. Join Explorer rows only from that provenance; otherwise expose them as unbound. |
| 1 | **Code-confirmed:** native transform calls accept quaternion, XYZ position and a single uniform scale, not three independent scales. | Identify a supported render-instance matrix or authored mesh-scale path and its collision/bounds update. Do not label group spacing changes as per-object anisotropic scaling. |
| 2 | **Code-confirmed:** current Delete quarantines objects by moving them down and shrinking them. It is not native destruction. | Trace lifecycle-safe removal, world ownership, physics removal and roster retirement together. Test transient and persistent entities separately. |
| 2 | **Code-confirmed:** queued transforms are not native acknowledgements. Spawn completions use sequence/tag correlation, not unique request IDs. | Add per-request IDs and world generations; collect success/failure acknowledgements on the owning update thread, then reconcile UI/history. Bound native work per frame. |
| 2 | **Code-confirmed:** the package builder edits installed package namespaces and physical owner patches; it does not prove creation of arbitrary new map namespaces. | Validate graph/reference integrity, collision data and loader acceptance for a minimal staged map. Only then attempt a new package namespace. |
| 2 | **Code-confirmed:** the gizmo builds a projection from camera pose and a configurable FOV, not a verified final render view-projection matrix. | Capture the final render camera, projection and viewport from the same frame. Verify first/third person, FOV changes, distance and clipping before expanding gizmo behavior. |
| 3 | **Code-confirmed:** combined-asset filenames normalize names; different punctuation can resolve to the same filename. | Use stable asset IDs with separate display names and explicit overwrite behavior; migrate existing files without renaming user metadata silently. |

The relevant builder logic is `stage_pandora_map_root` in
`Sunrise/src/izanami/runtime/custom_package_builder.cpp` (the preserved-class branch near
`kTowerDirectHavokResourceClass`). The current behavior cannot honestly be called a clean,
custom, collision-correct world. Reusing the native Pandora activity is a useful loading
foundation; it does not require pretending its stock contents are custom content.

## Other upstream leads

- [PR 98](https://github.com/stanuwu/Sunrise/pull/98) explores following the player's host
  and multiple spawner-rule references. Potentially useful for server-owned object spawning,
  but it was still under review and drew maintainer concerns. Not imported wholesale.
- Upstream `10aa578a` changes entity roster reuse/retirement. Review it alongside native
  deletion, with stale-handle and host-transition tests; it is not a ready-made delete API.
- [PR 53](https://github.com/stanuwu/Sunrise/pull/53) / upstream `fca0e86f` adds runtime
  boot-flow texture overrides. Useful for branded presentation, not proof of a native
  Destiny editor screen, asset thumbnail renderer, or viewport engine.
- [SunriseMissions](https://github.com/stanuwu/SunriseMissions) provides experimental mission
  examples. Treat them as API usage evidence, not validated end-to-end map templates.

## Recommended next session

1. Deploy this DLL with Destiny closed, verify its hash against the loaded location, and
   start one fresh process. Do not promote a new package draft for the control run.
2. Test Tower Carrier Control and unmodified Pandora direct entry separately. Record the
   exact world option and whether gameplay, inventory and movement complete loading.
3. In a working world, spawn a known collision-bearing asset; rapidly transform it, group
   several objects, save/replay, and test a rejected edit on an expired member.
4. Resume blank-map work only after launch control is repeatable. Isolate the platform's
   collision ownership before removing or duplicating any additional map records.

Do not enable speculative physics deletion, nonuniform scale, or arbitrary package mutation
just to expose a working-looking button. Those require the native evidence listed above.
