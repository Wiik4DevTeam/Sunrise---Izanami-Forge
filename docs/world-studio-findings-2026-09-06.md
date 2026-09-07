# External Geometry Editor Findings

## Decision

Use an external geometry workbench, backed by Alkahest's dedicated
[prebl-0.5 branch](https://github.com/cohaereo/alkahest/tree/prebl-0.5), rather
than recreate Tiger Engine. Its [pre-Beyond-Light release](https://github.com/cohaereo/alkahest/releases/tag/v0.5-prebl)
is explicitly aimed at this generation of game data. A viewer/renderer does not
replace Destiny's gameplay, networking, streaming, or collision runtime.

The local executable version is `86657.20.08.23.1800.d2_rc`. The external package
manager is explicitly configured for `GameVersion::Destiny2Shadowkeep`.

This pass built a usable external static-instance editing foundation. It does
not implement native package writeback, polygon editing, or collision cooking.
Sunrise's current DLL, Tower launch path, and installed packages were untouched.
Neither Destiny nor an interactive viewer session was launched for verification.
The package/GPU audits ran headlessly.

## Concrete Baseplate Identification

The installed Pandora map was loaded through the real package parser and rendered
with the native static-mesh renderer, not reconstructed from a UI placeholder.

| Field | Confirmed value |
| --- | --- |
| Bubble/map parent | `8150E00A` |
| Static mesh | `815B0FF8` |
| Owning data table | `8150E018` |
| Placement resource offset | `0xC8` |
| Preheader | `8150E017` |
| Static-instance table | `8150E016` |
| Instance group | `185` (zero-based) |
| Transform indices | `593`, `594` (zero-based) |
| Transform 594 position | `(-2.5, -2.5, -1.0029749)` |
| Transform 593 position | `(-7.4818163, -2.5, -1.0029749)` |
| Rendered appearance | Grid-textured rectangular floor block |
| Collision association | Not identified by this pass |

Complete key of the rendered instance:

```text
t8150E018/rC8/wFFFFFFFFFFFFFFFF/p8150E017/i8150E016/g185/n594/m815B0FF8
```

The current game-side builder instead names `8150E15B` and parent `8150E15A` as
its baseplate source. In the audited installation that table resolves to six
instances of `815B82EB`, with large offsets and scales. Its visual identity is
**not confirmed**: the isolated source-color preview was blank and failed its
pixel test. Do not relabel it as sky/mountains based only on those transforms.

The confirmed grid block above is a different mesh in a different table. This
is evidence that the current baseplate-source assumption needs to be revisited,
not authorization to redirect or rewrite packages without further validation.
`8150E018` contains **595 instances**, so preserving/copying that entire table
would also preserve lots of unrelated scenery. Target individual group/transform
records, not the whole aggregate.

`815B0FF8` is a **static mesh descriptor**, not a demonstrated entity-factory tag.
Do not pass it directly to Sunrise's entity spawn hook and call that supported.

## Implemented

- Pinned, separately built Alkahest checkout and repeatable PowerShell wrapper.
- Source identity attached to individual static instances during native loading.
- Source inspector and per-instance names.
- Searchable static geometry list with direct selection and camera framing.
- Static project save/open/restore: translation, quaternion, independent axis
  scales, visibility, and names. Saved projects remain outside build output.
- Map/activity/source-fingerprint preflight and all-record batch validation.
- Same-directory temporary-file replacement; failed validation preserves a prior save.
- Correct per-instance hiding in the batched render path and individual pick path.
- Real-package offscreen render/transform/visibility regression checks.

Original Alkahest provides the camera, textured geometry, selection, inspector,
outliner, and transform gizmos. This work builds on that implementation; it does
not claim those upstream features as new Forge code.

## Measured Verification

Windows x64 release build succeeded; six focused project tests passed:
transform/name/visibility persistence, invalid-batch atomicity, mismatched-source
rejection, ambiguous identity and invalid-number rejection, native quaternion
roundtrip without normalization drift, and file replacement/reopen behavior.

| Audit | Static instances | Fingerprinted records | Scale-changed pixels | Hide-changed pixels | Restore-different pixels |
| --- | ---: | ---: | ---: | ---: | ---: |
| Pandora `8150E00A` | 695 | 196 | 43,181 | 52,654 | 0 |
| Pandora `8150E06B` | 919 | 179 | 4,351 | 4,371 | 0 |

The default audit uses the closest static instance to the origin, unless a mesh
is explicitly requested. Preview images are 960 x 640, isolated, source-color
renders. These establish real rendered geometry, visible Y-axis resizing and
hiding, and exact restoration. They do **not** test Destiny physics or native
game package loading, nor a human-operated editor session.

The first map's instance counts by source table were:

| Table | Instances |
| --- | ---: |
| `8150E018` | 595 |
| `8150E14E` | 94 |
| `8150E15B` | 6 |

The second audit rendered mesh `8156F2E3`, table `8150E098`, group 48, transform
503. Its semantic object name has not been established.

Logs are in `build/external/world-studio-{build,tests,audit,second-map}.log`.
Audits and PNGs are in `%LOCALAPPDATA%/IzanamiForge/WorldStudio/Projects`.
The patch also passed `git apply --check` on a clean checkout of the pinned
upstream revision. Windows PowerShell 5.1 status/setup were checked separately.

## High-Priority Research

1. **Native static-instance writeback.** Translate the exact external identity
   into checked native records. Re-read/fingerprint the package at write time,
   preserve untouched records, and roundtrip the result through an independent
   parser before any deployment. The current outer table placement edit is not
   equivalent to editing every inner mesh instance.
2. **Collision ownership.** Locate collision corresponding to `815B0FF8` and its
   instances. Establish whether it lives in a separate collision collection,
   a combined shape, or another owner. Moving/hiding a render mesh does not move
   or remove collision. Do not repeat the phantom-collision assumption.
3. **Blank-map subset.** Preserve the actual grid-block instances, verified sky,
   and required spawn/streaming/activity infrastructure. Do not keep the 595-item
   aggregate or delete all entities indiscriminately. Prove collision before tiling.
4. **Non-uniform scaling in Destiny.** External X/Y/Z scaling is demonstrated.
   The existing pre-BL loader interprets native instance scale as uniform from
   `scale.x`. Native non-uniform support is not established; baking vertex data
   would also require normals, bounds, and collision updates.
5. **Vertex/topology authoring.** A renderer/editor foundation is not a geometry
   compiler. Validate mesh buffer/technique contracts and collision cooking
   before promising Blender-style topology edits or wholly new mesh packages.
6. **Unsupported resource families.** The loader warns about multiple classes
   in Pandora. Lights, decals, emitters, decorators, gameplay objects, sky-only
   draws, and collision are not all covered by the new static project format.
7. **Viewer hardening.** This is an experimental old upstream branch, with
   compiler warnings including unsafe initialization patterns outside this
   patch. One uninitialized D3D11 map structure on the exercised readback path
   was corrected. A broader upstream safety audit is still required.
8. **Editor integration.** Decide whether Forge keeps Alkahest as a separate
   application with a checked recipe bridge or embeds a rendering frontend.
   Reusing the parser/renderer is preferable to rebuilding all Tiger systems.

## Documentation Status

These findings are recorded in this repository. The shared Google Doc's trusted
read failed during its file-backed transfer in this pass; no unverified write
was made to that document. Its older baseplate-source labels may therefore still
be present and must not override the measured IDs above.
