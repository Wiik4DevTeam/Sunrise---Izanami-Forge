# Izanami_Forge_Master_Research_Developer_Onboarding

- Document ID: 1bK5K4ym9Sgp43FvvU1KY1v4I78q_YhAzJMLEAHFRtb4
- Revision ID: AIroW34JGwMSz5Wx6WqEHN5CL2H1x6yn3phmUJJj4MWTYZSNSftcqmZWLD5imGGCgRjaELthis9CR0DUJ6exMYMYbQjFG5gSPf-QhbxEHko
- Selected tab: t.0
- Protected controls: 0
- Opaque controls: 0
- Authoritative dropdowns: 0

Protected-control annotations are preservation instructions. Do not insert their displayed placeholder text to recreate a native control.

## Tab 1 (t.0)

[P00001 | 1:29 | NORMAL_TEXT]
PROJECT SUNRISE / DESTINY 2

[P00002 | 29:43 | NORMAL_TEXT]
IZANAMI FORGE

[P00003 | 43:99 | NORMAL_TEXT]
Current Research, Implementation, and Developer Handoff

[P00004 | 99:124 | NORMAL_TEXT]
Updated: August 21, 2026

[P00005 | 124:173 | NORMAL_TEXT]
Repository: B:\!!izanami\Sunrise---Izanami-Forge

[P00006 | 173:379 | NORMAL_TEXT]
Branch / HEAD: izanami-forge / 830a9a58eb7855d111a1d3eab606b45c0df38fc8. Local worktree verified dirty with thirteen tracked files modified plus one new native-binding header; preserve it as authoritative.

[P00007 | 379:482 | NORMAL_TEXT]
Primary focus: Explicit Forge-native placement bindings, then a minimal package-backed baseplate world

[P00008 | 482:565 | NORMAL_TEXT]
Evidence rule: VERIFIED means observed in source, logs, memory, or an in-game test

[P00009 | 565:566 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00010 | 566:1948 | NORMAL_TEXT]
CURRENT BOTTOM LINE. Tower Carrier Control and canonical Tower package mutation are FIELD-PROVEN, but the current Blank Baseplate is still an edited Tower carrier, not a new custom map package. Field tests have now ruled out all known placement-level Havok candidates as the source of the observed phantom structural collision: six visibility/world-bundle wrappers, fourteen base direct-Havok wrappers, sixteen activity direct-Havok wrappers, sixteen entity-model outer transforms, and the nullable interpretation of fifteen model-linked Havok references. The isolated group-13/static-13/mesh-0x815B621C staircase/floor remains visual-only and has no matched collision. A complete row census found that all 1,563 Tower-base map rows carry an entity owner at +0x00; 1,336 also carry component data at +0x78, while 227 are standalone entity rows. The deployed next control suppresses exactly 210 source-classified standalone scenery actors and preserves the eight System and nine Interactive standalone nodes plus every component-backed row and the clean 65-row collision baseline. The immediate test is now intentionally about scenery ownership, not collision. Collision research moves below placement wrappers into component, slice, and native world-physics ownership, while a true custom package identity and a deliberately paired visible-and-collidable baseplate remain unproven.

[P00011 | 1948:2010 | HEADING_1]
[REFERENCE ADDENDUM: Exact Package and Resource Function Index](https://docs.google.com/document/d/12FgHazzSWWLR6KupHNZfZ7KjYF1thNSdwCtjBvRsb54/edit)

[P00012 | 2010:2032 | HEADING_1]
1. Scope and Priority

[P00013 | 2032:2293 | NORMAL_TEXT]
This document is the source of truth for resuming Izanami Forge work. It intentionally removes the broad long-term editor-platform roadmap, speculative multiplayer/Fate design, and stale pull-request archaeology that do not help solve the current runtime gate.

[P00014 | 2293:2366 | NORMAL_TEXT]
One runtime breakthrough is now proven; the remaining release gates are:

[P00015 | 2366:2491 | NORMAL_TEXT]
1.  Field-test the explicit Forge-bound Tower patch: restore the known aggregate and move one smaller independent placement.

[P00016 | 2491:2625 | NORMAL_TEXT]
2.  Reduce the proven carrier to a safe baseplate, spawn, and sky, then progress toward a genuinely new package/destination identity.

[P00017 | 2625:3015 | NORMAL_TEXT]
PARALLEL DESIGN TRACK. Research native spawning, rotation, scale, destruction, Destiny menu integration, and the Forge UI while package-backed placement ownership is implemented. The target remains two coordinated surfaces: compact Destiny-style in-game controls and a separate UE/Roblox-style editor. Fate, multiplayer, cinematics, and unrelated platform work remain outside this handoff.

[P00018 | 3015:3017 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00019 | 3017:3040 | HEADING_1]
2. Ground-Truth Status

[P00020 | 3043:3048 | NORMAL_TEXT | TABLE row=0 col=0]
Area

[P00021 | 3049:3056 | NORMAL_TEXT | TABLE row=0 col=1]
Status

[P00022 | 3057:3074 | NORMAL_TEXT | TABLE row=0 col=2]
What is true now

[P00023 | 3076:3101 | NORMAL_TEXT | TABLE row=1 col=0]
Forge UI and scene model

[P00024 | 3102:3110 | NORMAL_TEXT | TABLE row=1 col=1]
PARTIAL

[P00025 | 3111:3253 | NORMAL_TEXT | TABLE row=1 col=2]
The hierarchy, viewport, inspector, commands, undo/redo, and serialization-facing scene model exist. Most edits change Forge-owned data only.

[P00026 | 3255:3279 | NORMAL_TEXT | TABLE row=2 col=0]
In-game object mutation

[P00027 | 3280:3297 | NORMAL_TEXT | TABLE row=2 col=1]
PROVEN - PACKAGE

[P00028 | 3298:3524 | NORMAL_TEXT | TABLE row=2 col=2]
A canonical Tower patch moved a native placement aggregate +64 units on X. A new deployed build now wires Forge scene transforms to source-validated package placement records; its selective patch result is pending field test.

[P00029 | 3526:3550 | NORMAL_TEXT | TABLE row=3 col=0]
Direct activity request

[P00030 | 3551:3566 | NORMAL_TEXT | TABLE row=3 col=1]
PROVEN - TOWER

[P00031 | 3567:3703 | NORMAL_TEXT | TABLE row=3 col=2]
The Forge path can arm the carrier and request the activity transition without another Director click; Tower Carrier Control is proven.

[P00032 | 3705:3731 | NORMAL_TEXT | TABLE row=4 col=0]
Forced destination bridge

[P00033 | 3732:3739 | NORMAL_TEXT | TABLE row=4 col=1]
PROVEN

[P00034 | 3740:3886 | NORMAL_TEXT | TABLE row=4 col=2]
A manually launched valid destination was redirected to the Tower and loaded there. The server-side selection rewrite can affect a valid carrier.

[P00035 | 3888:3903 | NORMAL_TEXT | TABLE row=5 col=0]
vfx_shade_test

[P00036 | 3904:3920 | NORMAL_TEXT | TABLE row=5 col=1]
STOCK TEST ONLY

[P00037 | 3921:4073 | NORMAL_TEXT | TABLE row=5 col=2]
It is installed Destiny content. It loaded in an earlier experiment and showed a baseplate plus unrelated test scenery, with Waiting for Other Players.

[P00038 | 4075:4091 | NORMAL_TEXT | TABLE row=6 col=0]
Blank Baseplate

[P00039 | 4092:4109 | NORMAL_TEXT | TABLE row=6 col=1]
PROVEN - CARRIER

[P00040 | 4110:4250 | NORMAL_TEXT | TABLE row=6 col=2]
The current pipeline writes and loads a canonical Tower next-patch whose native transform changes are visible in game. It is not blank yet.

[P00041 | 4252:4286 | NORMAL_TEXT | TABLE row=7 col=0]
Existing package-chain activation

[P00042 | 4287:4304 | NORMAL_TEXT | TABLE row=7 col=1]
PARTIAL - PROVEN

[P00043 | 4305:4449 | NORMAL_TEXT | TABLE row=7 col=2]
Destiny discovered and loaded a canonical extra patch in the existing Tower chain. A wholly new package/destination identity is not yet proven.

[P00044 | 4451:4473 | NORMAL_TEXT | TABLE row=8 col=0]
Current direct launch

[P00045 | 4474:4489 | NORMAL_TEXT | TABLE row=8 col=1]
PROVEN - TOWER

[P00046 | 4490:4617 | NORMAL_TEXT | TABLE row=8 col=2]
Tower Carrier Control has launched directly into a stable Tower world. Other carrier/package combinations remain experimental.

[P00047 | 4619:4636 | NORMAL_TEXT | TABLE row=9 col=0]
Player broadcast

[P00048 | 4637:4657 | NORMAL_TEXT | TABLE row=9 col=1]
NON-BLOCKING SIGNAL

[P00049 | 4658:4765 | NORMAL_TEXT | TABLE row=9 col=2]
It can repeat during a stable activity:in_world run. Track it as a separate replication/entity-slot issue.

[P00050 | 4767:4790 | NORMAL_TEXT | TABLE row=10 col=0]
Native Destiny UI node

[P00051 | 4791:4807 | NORMAL_TEXT | TABLE row=10 col=1]
NOT IMPLEMENTED

[P00052 | 4808:4941 | NORMAL_TEXT | TABLE row=10 col=2]
Forge remains inside the Sunrise overlay. Adding a native Destinations node is not needed to prove the runtime path and is deferred.

[P00053 | 4943:4963 | NORMAL_TEXT | TABLE row=11 col=0]
Editor workspace UI

[P00054 | 4964:4991 | NORMAL_TEXT | TABLE row=11 col=1]
IMPLEMENTED - TEST PENDING

[P00055 | 4992:5252 | NORMAL_TEXT | TABLE row=11 col=2]
Explicit native table/entry/parent/source-transform bindings and package-staged transform editing are implemented in the deployed build. The selective Tower patch is awaiting its first in-game generation and test; the separate full editor remains future work.

[P00056 | 5253:5254 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00057 | 5254:5283 | HEADING_1]
3. What Has Been Implemented

[P00058 | 5283:5322 | HEADING_2]
3.1 Forge application and editor shell

[P00059 | 5322:5400 | NORMAL_TEXT]
•  Forge templates and workspaces under Sunrise/src/izanami/editor/workspace.

[P00060 | 5400:5513 | NORMAL_TEXT]
•  Standalone Forge panel, hierarchy, 2D viewport, inspector, placement controls, undo/redo, and scene commands.

[P00061 | 5513:5668 | NORMAL_TEXT]
•  Forge-owned IDs, transforms, component registry, event bus, service registry, scene document, catalog records, and early Fate lexer/parser scaffolding.

[P00062 | 5668:5808 | NORMAL_TEXT]
•  Movement/editor-mode helpers can hide Sunrise UI and enable released fly/noclip settings, but this is not a complete native editor mode.

[P00063 | 5808:5833 | HEADING_2]
3.2 Direct launch bridge

[P00064 | 5833:5974 | NORMAL_TEXT]
•  director_handoff.cpp resolves Destiny's boot-flow manager, state request, live private session, and session-goal publisher by signatures.

[P00065 | 5974:6091 | NORMAL_TEXT]
•  A queued game-thread poll publishes target 38 / mode 2, then requests setup:activity_session_creation (state 30).

[P00066 | 6091:6183 | NORMAL_TEXT]
•  The Forge overlay closes before the transition, so no second Director click is intended.

[P00067 | 6183:6403 | NORMAL_TEXT]
•  The carrier lifecycle is now in-game validated for Tower. The detour installs during activation but remains dormant until an explicit Forge launch arms it, preventing startup from entering an unintended launch state.

[P00068 | 6403:6447 | HEADING_2]
3.3 Server-side selection and activity path

[P00069 | 6447:6554 | NORMAL_TEXT]
•  Activity manager service 6 parses the client's opaque descriptor and can preserve its carrier identity.

[P00070 | 6554:6677 | NORMAL_TEXT]
•  Forced destination logic can insert or replace the 40-byte biased package-name field while preserving opaque tail bits.

[P00071 | 6677:6831 | NORMAL_TEXT]
•  Activity global state, roster, membership, host advertisement, entity-slot grants, and keepalive paths have additional diagnostics and targeted fixes.

[P00072 | 6831:7013 | NORMAL_TEXT]
•  Tower is the proven direct carrier. Forced vfx and other package substitutions remain experimental and are no longer the primary path for validating package-authored map changes.

[P00073 | 7013:7048 | HEADING_2]
3.4 Package-backed Tower authoring

[P00074 | 7048:7184 | NORMAL_TEXT]
•  carrier_probe.cpp walks installed scenario, slice, map, placement, registry, and resource references without modifying package data.

[P00075 | 7184:7357 | NORMAL_TEXT]
•  custom_package_builder.cpp now stages a canonical next-patch in the existing Tower package chain, rewrites a bounded static-resource transform, and validates the result.

[P00076 | 7357:7541 | NORMAL_TEXT]
•  The builder preserves the source block codec. Tower's 8C07 stream maps to Oodle 2.3 LZH compressor 0; using a newly authored 8C06 Kraken stream caused native decompression failure.

[P00077 | 7541:7711 | NORMAL_TEXT]
•  Encryption metadata, GCM tag, embedded SHA-1, patch ID, block offsets/sizes, package size, and source/target identity are revalidated before the artifact is accepted.

[P00078 | 7711:7816 | NORMAL_TEXT]
•  OodleRuntime now exposes compress_with_codec(); the existing compress() API remains a Kraken wrapper.

[P00079 | 7816:8103 | NORMAL_TEXT]
•  The hard-coded first-table +64 X mutation has been removed. The deployed builder now consumes explicit Forge-bound placements, validates table/entry/parent/full source transform, restores the known aggregate to X = 0, and stages one smaller independent +64 X probe for field testing.

[P00080 | 8103:8132 | HEADING_1]
4. Verified In-Game Findings

[P00081 | 8132:8209 | NORMAL_TEXT]
•  Tower Carrier Control launched directly and reached a stable Tower world.

[P00082 | 8209:8309 | NORMAL_TEXT]
•  Destiny's native loader discovered and loaded a canonical Tower next-patch generated by Izanami.

[P00083 | 8309:8393 | NORMAL_TEXT]
•  A no-op source-codec-preserving patch loaded with no native decompression error.

[P00084 | 8393:8513 | NORMAL_TEXT]
•  A real package-authored transform changed table 0x80ED22FB, entry 0, parent 0x80ED22FA from (0, 0, 0) to (64, 0, 0).

[P00085 | 8513:8645 | NORMAL_TEXT]
•  The user visually confirmed that a large part of the Tower moved. This is the first proven native world mutation in the project.

[P00086 | 8645:8704 | NORMAL_TEXT]
•  The successful transform run reached activity:in_world.

[P00087 | 8704:8852 | NORMAL_TEXT]
•  player_broadcast messages continued during successful gameplay, so they are a separate diagnostic issue rather than a standalone launch verdict.

[P00088 | 8852:8958 | NORMAL_TEXT]
•  vfx_shade_test and Bonfire Bash remain stock content and must not be described as custom Forge worlds.

[P00089 | 8958:8991 | HEADING_1]
5. Package Breakthrough Timeline

[P00090 | 8991:9063 | NORMAL_TEXT]
1.  A canonical no-op Tower patch 7 was accepted and loaded by Destiny.

[P00091 | 9063:9115 | NORMAL_TEXT]
2.  A raw encrypted rewrite deadlocked during load.

[P00092 | 9115:9231 | NORMAL_TEXT]
3.  A freshly authored Kraken stream (8C06) reached the native loader but failed decompression and closed the game.

[P00093 | 9231:9339 | NORMAL_TEXT]
4.  The installed Tower source stream was identified as 8C07, mapped locally to Oodle 2.3 LZH compressor 0.

[P00094 | 9339:9452 | NORMAL_TEXT]
5.  The builder was changed to preserve the source compressor. A byte-identical LZH rewrite loaded successfully.

[P00095 | 9452:9540 | NORMAL_TEXT]
6.  Patch 8 changed one native static-resource transform block and loaded successfully.

[P00096 | 9540:9622 | NORMAL_TEXT]
7.  The resulting Tower geometry visibly moved by the authored +64 X translation.

[P00097 | 9622:9784 | NORMAL_TEXT]
8.  The run reached activity:in_world. Repeated player_broadcast logs continued, proving that message is not sufficient by itself to classify a launch as failed.

[P00098 | 9784:9785 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00099 | 9785:9816 | HEADING_1]
6. Known-Good Package Contract

[P00100 | 9816:9858 | NORMAL_TEXT]
Source world root: map:city_tower_d2:root

[P00101 | 9858:9890 | NORMAL_TEXT]
Package: w64_city_tower_d2_0369

[P00102 | 9890:9909 | NORMAL_TEXT]
Package ID: 0x0369

[P00103 | 9909:9936 | NORMAL_TEXT]
Current canonical patch: 8

[P00104 | 9936:10017 | NORMAL_TEXT]
Native placement identity: table 0x80ED22FB, entry 0, expected parent 0x80ED22FA

[P00105 | 10017:10073 | NORMAL_TEXT]
Authored translation: (64, 0, 0), from source (0, 0, 0)

[P00106 | 10073:10136 | NORMAL_TEXT]
Source compression stream: 8C07 / Oodle 2.3 LZH / compressor 0

[P00107 | 10136:10259 | NORMAL_TEXT]
Current builder scope: one Tower static-resource table, deliberately bounded while the record contract is being validated.

[P00108 | 10259:10260 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00109 | 10260:10614 | NORMAL_TEXT]
The package builder now reads the source block, detects its compressor, recompresses with that same codec, encrypts, updates the GCM tag and SHA-1, writes a canonical next patch, and validates package metadata plus block ranges before use. OodleRuntime exposes compress_with_codec(); the existing compress() remains the Kraken wrapper for compatibility.

[P00110 | 10614:10615 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00111 | 10615:10650 | HEADING_1]
7. Corrected Launch Interpretation

[P00112 | 10650:10824 | NORMAL_TEXT]
Direct Tower launch is no longer the primary blocker. Tower Carrier Control has entered a stable Tower world, and the package-backed transform run reached activity:in_world.

[P00113 | 10824:10825 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00114 | 10825:11076 | NORMAL_TEXT]
player_broadcast remains useful diagnostic evidence, but it also appears during successful gameplay. It must be tracked as a separate replication/entity-slot issue. Do not reject an otherwise stable package/world load solely because this log repeats.

[P00115 | 11076:11077 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00116 | 11077:11328 | NORMAL_TEXT]
The early local-carrier hook is installed during activation but remains dormant until Forge explicitly arms it. This avoids booting Destiny already in a launch transition. The exact launch bridge remains experimental outside the proven Tower carrier.

[P00117 | 11328:11329 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00118 | 11329:11359 | HEADING_1]
8. Remaining Custom-World Gap

[P00119 | 11359:11541 | NORMAL_TEXT]
The breakthrough proves extension and mutation of an existing installed package chain. It does not yet prove a completely new Destiny destination identity or a scenery-free package.

[P00120 | 11541:11542 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00121 | 11542:11871 | NORMAL_TEXT]
The present patch moves one large Tower aggregate because the first bounded static table owns a broad parent resource. The next practical milestone is selective native placement ownership: catalog the map tables, bind one Forge object to one stable table/entry/parent identity, and author that object's transform into the patch.

[P00122 | 11871:11872 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00123 | 11872:11933 | NORMAL_TEXT]
A minimal baseplate carrier should be reached incrementally:

[P00124 | 11933:11999 | NORMAL_TEXT]
1.  Catalog native placements and choose small, isolated records.

[P00125 | 11999:12055 | NORMAL_TEXT]
2.  Prove exact per-record translation from Forge data.

[P00126 | 12055:12093 | NORMAL_TEXT]
3.  Add rotation and supported scale.

[P00127 | 12093:12191 | NORMAL_TEXT]
4.  Remove or redirect unwanted scenery while preserving spawn, collision, and world environment.

[P00128 | 12191:12259 | NORMAL_TEXT]
5.  Only then attempt a genuinely new package/destination identity.

[P00129 | 12259:12260 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00130 | 12260:12295 | HEADING_1]
9. Failed or Superseded Approaches

[P00131 | 12295:12385 | NORMAL_TEXT]
•  Opening Destinations without a native carrier: superseded by the direct Tower carrier.

[P00132 | 12385:12507 | NORMAL_TEXT]
•  Server-only package-name rewrite: useful with a valid carrier, insufficient to create client world identity by itself.

[P00133 | 12507:12633 | NORMAL_TEXT]
•  Forcing server activity index/readiness/entity masks: did not create a world and risks hiding the actual missing contract.

[P00134 | 12633:12740 | NORMAL_TEXT]
•  Teleporting outside stock maps: caused kill-volume or spawn-correction deaths and is not map authoring.

[P00135 | 12740:12829 | NORMAL_TEXT]
•  Treating Bonfire Bash or vfx_shade_test as custom: incorrect; both are stock content.

[P00136 | 12829:12866 | NORMAL_TEXT]
•  Raw rewritten blocks: deadlocked.

[P00137 | 12866:12935 | NORMAL_TEXT]
•  New Kraken-compressed Tower streams: native decompression failed.

[P00138 | 12935:13044 | NORMAL_TEXT]
•  Treating player_broadcast spam as the launch verdict: disproven by the successful in-world transform run.

[P00139 | 13044:13045 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00140 | 13045:13070 | HEADING_1]
10. Immediate Work Queue

[P00141 | 13070:13453 | NORMAL_TEXT]
PRIMARY: prove one true Shadowkeep StaticInstanceBinding without group projection. Extend the read-only 0x8080966D placement/culling catalog until one group/model/transform has fail-closed source provenance, evidence-proven bounds indexing, and independently attested collection bounds; then move exactly one 0x808071A3 Position XYZ while preserving every vector/group row and size.

[P00142 | 13453:13454 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00143 | 13454:13760 | NORMAL_TEXT]
1.  Introduce a typed package-placement binding. Preserve the proven map table/entry/parent tuple as MapNodeAggregateBinding, and add a deeper StaticInstanceBinding that records the resolved static-instance collection, group, model, transform index, bounds index, source transform, and source fingerprint.

[P00144 | 13760:13816 | NORMAL_TEXT]
2.  Seed the proven Tower placement in Blank Baseplate.

[P00145 | 13816:13917 | NORMAL_TEXT]
3.  Route the object's absolute transform through baseplate_composition into custom_package_builder.

[P00146 | 13917:14218 | NORMAL_TEXT]
4.  Validate binding identity and reject stale/duplicate records using separate structural-identity, immutable baseline-preimage, and evolving expected-canonical-preimage fingerprints. Do not let a successful Izanami build self-invalidate the binding, and do not silently adopt unknown package drift.

[P00147 | 14218:15703 | NORMAL_TEXT]
5.  Version-lock the first isolated static-instance parser to the installed Shadowkeep layout before field mutation. Resolve current Tower statics through the Shadowkeep map-row bridge first: SMapDataTable/SMapDataTableEntry 0x808099D6/0x808099D8 -> DataResource resource_type 0x808071B3 -> raw-attested 0x80806EF4 parent -> 0x8080966D static-instances payload; do not use the Post-BL component chain as the primary Tower parser. For data class 0x8080966D, use the Shadowkeep/pre-Beyond-Light layout family and 0x808071A3 / 0x30 instance transform, but raw-attest the installed header/tail layout instead of treating one public tool's declared size as authoritative: historical pre-BL Alkahest declares 0x98 for the same class while current Charm declares 0xA0. The Shadowkeep culling RESOURCE association is high-confidence but must be raw-byte-attested before mutation: public Charm exposes ModelOcclusionBounds at +0x18 through a cross-strategy fallback, while field-inspected VFX data independently reaches SOcclusionBounds 0x80809671. What remains unresolved is the per-transform bounds INDEXING rule; do not import the Post-BL +0x20 transform_to_bounds_index mapping. Recover that indexing read-only before any transform+AABB write. Before exposing a writable candidate, also validate the Shadowkeep 0x80807190 group ranges as the transform/static membership graph and require the selected transform to have exactly one group-range owner; do not assume one row per static model.

[P00148 | 15703:15812 | NORMAL_TEXT]
6.  Add a placement-catalog diagnostic to locate candidate baseplate, scenery, collision, and spawn records.

[P00149 | 15812:15895 | NORMAL_TEXT]
7.  Keep runtime spawning research separate from package-authored placement edits.

[P00150 | 15895:16179 | NORMAL_TEXT]
8.  After the data path is trustworthy, redesign Forge as two coordinated surfaces: compact Destiny-style in-game controls and a separate UE/Roblox-style workspace with viewport, Explorer, Toolbox, Properties, transform tools, undo/redo, loading/error states, and play/test controls.

[P00151 | 16179:16202 | HEADING_1]
11. Acceptance Signals

[P00152 | 16205:16216 | NORMAL_TEXT | TABLE row=0 col=0]
Checkpoint

[P00153 | 16217:16232 | NORMAL_TEXT | TABLE row=0 col=1]
Success signal

[P00154 | 16233:16248 | NORMAL_TEXT | TABLE row=0 col=2]
Failure signal

[P00155 | 16250:16264 | NORMAL_TEXT | TABLE row=1 col=0]
Local carrier

[P00156 | 16265:16405 | NORMAL_TEXT | TABLE row=1 col=1]
A logged substitution or explicit rebuild occurs before the activity transition; local selection no longer shows 0x0000 placeholder hashes.

[P00157 | 16406:16465 | NORMAL_TEXT | TABLE row=1 col=2]
No local_carrier/rebuild log, or selection remains 0x0000.

[P00158 | 16467:16483 | NORMAL_TEXT | TABLE row=2 col=0]
Prologue loader

[P00159 | 16484:16556 | NORMAL_TEXT | TABLE row=2 col=1]
setup:prologue_intro_loading task ENUM(0) completes and state advances.

[P00160 | 16557:16597 | NORMAL_TEXT | TABLE row=2 col=2]
Task ENUM(0) remains open indefinitely.

[P00161 | 16599:16610 | NORMAL_TEXT | TABLE row=3 col=0]
World bind

[P00162 | 16611:16660 | NORMAL_TEXT | TABLE row=3 col=1]
ActivityClient bind receipt changes from 0 to 1.

[P00163 | 16661:16680 | NORMAL_TEXT | TABLE row=3 col=2]
Receipt remains 0.

[P00164 | 16682:16695 | NORMAL_TEXT | TABLE row=4 col=0]
Entity slots

[P00165 | 16696:16762 | NORMAL_TEXT | TABLE row=4 col=1]
Pending grant drops from 7,936 and view slots become allocatable.

[P00166 | 16763:16795 | NORMAL_TEXT | TABLE row=4 col=2]
Pending remains 7,936, dirty 0.

[P00167 | 16797:16819 | NORMAL_TEXT | TABLE row=5 col=0]
Broadcast diagnostics

[P00168 | 16820:16901 | NORMAL_TEXT | TABLE row=5 col=1]
A stable world reaches activity:in_world; broadcast spam is recorded separately.

[P00169 | 16902:16967 | NORMAL_TEXT | TABLE row=5 col=2]
Broadcast diagnostics output is used as the sole launch verdict.

[P00170 | 16969:16975 | NORMAL_TEXT | TABLE row=6 col=0]
World

[P00171 | 16976:17048 | NORMAL_TEXT | TABLE row=6 col=1]
Guardian reaches a stable in-world state with inventory and UI loading.

[P00172 | 17049:17100 | NORMAL_TEXT | TABLE row=6 col=2]
Orbit stall, black menus, freeze, or error return.

[P00173 | 17102:17127 | NORMAL_TEXT | TABLE row=7 col=0]
Package-backed transform

[P00174 | 17128:17234 | NORMAL_TEXT | TABLE row=7 col=1]
PROVEN: the native loader opens the generated patch and the loaded world reflects the selected transform.

[P00175 | 17235:17309 | NORMAL_TEXT | TABLE row=7 col=2]
Authored transform is absent, or native package open/decompression fails.

[P00176 | 17311:17332 | NORMAL_TEXT | TABLE row=8 col=0]
Forge native binding

[P00177 | 17333:17447 | NORMAL_TEXT | TABLE row=8 col=1]
A Forge object targets a stable table/entry/parent identity and package generation writes its absolute transform.

[P00178 | 17448:17541 | NORMAL_TEXT | TABLE row=8 col=2]
The editor changes only Forge-owned scene data, or the binding resolves the wrong aggregate.

[P00179 | 17543:17553 | NORMAL_TEXT | TABLE row=9 col=0]
Editor UX

[P00180 | 17554:17687 | NORMAL_TEXT | TABLE row=9 col=1]
A reviewed two-surface component/state specification covers Destiny-style in-game controls and a separate UE/Roblox-style workspace.

[P00181 | 17688:17775 | NORMAL_TEXT | TABLE row=9 col=2]
The proposal is another debug panel or omits loading/error/runtime-unavailable states.

[P00182 | 17776:17777 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00183 | 17777:17792 | HEADING_1]
12. Source Map

[P00184 | 17795:17800 | NORMAL_TEXT | TABLE row=0 col=0]
Path

[P00185 | 17801:17831 | NORMAL_TEXT | TABLE row=0 col=1]
Responsibility / current note

[P00186 | 17833:17888 | NORMAL_TEXT | TABLE row=1 col=0]
Sunrise/src/client/hooks/director/director_handoff.cpp

[P00187 | 17889:17987 | NORMAL_TEXT | TABLE row=1 col=1]
Direct goal/state request; carrier hook installs dormant and arms only for explicit Forge launch.

[P00188 | 17989:18046 | NORMAL_TEXT | TABLE row=2 col=0]
Sunrise/src/client/hooks/bootflow/join_request_ready.cpp

[P00189 | 18047:18116 | NORMAL_TEXT | TABLE row=2 col=1]
Native readiness observation; invasive term-report call is disabled.

[P00190 | 18118:18186 | NORMAL_TEXT | TABLE row=3 col=0]
Sunrise/src/client/hooks/retail_log/retail_log_enqueue_observer.cpp

[P00191 | 18187:18246 | NORMAL_TEXT | TABLE row=3 col=1]
Passive selection and player_broadcast stack/code capture.

[P00192 | 18248:18311 | NORMAL_TEXT | TABLE row=4 col=0]
Sunrise/src/client/hooks/membership_probe/membership_probe.cpp

[P00193 | 18312:18393 | NORMAL_TEXT | TABLE row=4 col=1]
ActivityClient status, bind receipt, pending grant, and membership observations.

[P00194 | 18395:18482 | NORMAL_TEXT | TABLE row=5 col=0]
Sunrise/src/server/bap/encrypted/activity_host_manager/activity_host_manager_route.cpp

[P00195 | 18483:18547 | NORMAL_TEXT | TABLE row=5 col=1]
Service-6 selection capture and forced-destination application.

[P00196 | 18549:18615 | NORMAL_TEXT | TABLE row=6 col=0]
Sunrise/src/state/activity/forced/activity_forced_destination.cpp

[P00197 | 18616:18687 | NORMAL_TEXT | TABLE row=6 col=1]
Package-name insertion/rename while preserving opaque descriptor bits.

[P00198 | 18689:18767 | NORMAL_TEXT | TABLE row=7 col=0]
Sunrise/src/server/bap/encrypted/push/activity/activity_global_state_push.cpp

[P00199 | 18768:18816 | NORMAL_TEXT | TABLE row=7 col=1]
Global-state descriptor replay and diagnostics.

[P00200 | 18818:18873 | NORMAL_TEXT | TABLE row=8 col=0]
Sunrise/src/izanami/runtime/custom_package_builder.cpp

[P00201 | 18874:18979 | NORMAL_TEXT | TABLE row=8 col=1]
Tower next-patch generation, source-codec preservation, transform rewrite, and package/block validation.

[P00202 | 18981:19027 | NORMAL_TEXT | TABLE row=9 col=0]
Sunrise/src/izanami/runtime/carrier_probe.cpp

[P00203 | 19028:19078 | NORMAL_TEXT | TABLE row=9 col=1]
Read-only scenario/map/resource graph inspection.

[P00204 | 19080:19134 | NORMAL_TEXT | TABLE row=10 col=0]
Sunrise/src/izanami/runtime/baseplate_composition.cpp

[P00205 | 19135:19213 | NORMAL_TEXT | TABLE row=10 col=1]
Arms the Tower-backed baseplate composition and canonical next-patch staging.

[P00206 | 19215:19273 | NORMAL_TEXT | TABLE row=11 col=0]
Sunrise/src/izanami/editor/workspace/editor_workspace.cpp

[P00207 | 19274:19355 | NORMAL_TEXT | TABLE row=11 col=1]
Template behavior and next owner of explicit native table/entry/parent bindings.

[P00208 | 19357:19397 | NORMAL_TEXT | TABLE row=12 col=0]
Sunrise/resources/default_settings.json

[P00209 | 19398:19477 | NORMAL_TEXT | TABLE row=12 col=1]
Fallback Tower destination uses activity index 20; entity slot reserve is 256.

[P00210 | 19478:19479 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00211 | 19479:19505 | HEADING_1]
13. Working Tree Snapshot

[P00212 | 19505:19560 | NORMAL_TEXT]
Local repository: B:\!!izanami\Sunrise---Izanami-Forge

[P00213 | 19560:19632 | NORMAL_TEXT]
Branch / HEAD: izanami-forge / 830a9a58eb7855d111a1d3eab606b45c0df38fc8

[P00214 | 19632:19654 | NORMAL_TEXT]
HEAD subject: commit!

[P00215 | 19654:19793 | NORMAL_TEXT]
State at this handoff: ten tracked files are modified. Treat the dirty worktree as authoritative; do not reset or discard unrelated edits.

[P00216 | 19793:19794 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00217 | 19794:19810 | NORMAL_TEXT]
Modified files:

[P00218 | 19810:19868 | NORMAL_TEXT]
•  Sunrise/src/client/hooks/director/director_handoff.cpp

[P00219 | 19868:19924 | NORMAL_TEXT]
•  Sunrise/src/client/hooks/director/director_handoff.h

[P00220 | 19924:19988 | NORMAL_TEXT]
•  Sunrise/src/client/hooks/package_trust/package_trust_bypacpp

[P00221 | 19988:20039 | NORMAL_TEXT]
•  Sunrise/src/izanami/editor/ui/izanami_panel.cpp

[P00222 | 20039:20100 | NORMAL_TEXT]
•  Sunrise/src/izanami/editor/workspace/editor_workspace.cpp

[P00223 | 20100:20157 | NORMAL_TEXT]
•  Sunrise/src/izanami/runtime/baseplate_composition.cpp

[P00224 | 20157:20215 | NORMAL_TEXT]
•  Sunrise/src/izanami/runtime/custom_package_builder.cpp

[P00225 | 20215:20271 | NORMAL_TEXT]
•  Sunrise/src/izanami/runtime/custom_package_builder.h

[P00226 | 20271:20333 | NORMAL_TEXT]
•  Sunrise/src/middleware/compression/oodle/oodle_runtime.cpp

[P00227 | 20333:20387 | NORMAL_TEXT]
•  Sunrise/src/middleware/compression/oodle/runtime.h

[P00228 | 20387:20388 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00229 | 20388:20416 | HEADING_1]
14. Build, Deploy, and Test

[P00230 | 20416:20438 | HEADING_2]
14.1 Build and deploy

[P00231 | 20438:20576 | NORMAL_TEXT]
Destiny must be fully closed before replacing steam_api64.dll or canonical package files. The current Release DLL and deployed DLL match.

[P00232 | 20576:20577 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00233 | 20577:20619 | NORMAL_TEXT]
cd 'B:\!!izanami\Sunrise---Izanami-Forge'

[P00234 | 20619:20723 | NORMAL_TEXT]
& 'C:\Program Files\CMake\bin\cmake.exe' --build build --config Release --target steam_api64 --parallel

[P00235 | 20723:20860 | NORMAL_TEXT]
Copy-Item -LiteralPath '.\build\x64\Release\steam_api64.dll' -Destination 'B:\!!izanami\Destiny2-Sunrise\bin\x64\steam_api64.dll' -Force

[P00236 | 20860:20998 | NORMAL_TEXT]
Get-FileHash -Algorithm SHA256 -LiteralPath '.\build\x64\Release\steam_api64.dll','B:\!!izanami\Destiny2-Sunrise\bin\x64\steam_api64.dll'

[P00237 | 20998:20999 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00238 | 20999:21028 | NORMAL_TEXT]
Latest deployed DLL SHA-256:

[P00239 | 21028:21093 | NORMAL_TEXT]
31F1A6600394563976EB36B22C916DEDEB23E5AE33E1BE309052A08CABB94FEE

[P00240 | 21093:21094 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00241 | 21094:21139 | HEADING_2]
14.2 Minimal package-transform test protocol

[P00242 | 21139:21219 | NORMAL_TEXT]
1.  Archive the previous sunrise.log and preserve the current known-good patch.

[P00243 | 21219:21294 | NORMAL_TEXT]
2.  Confirm Destiny is closed, then build, deploy, and compare DLL hashes.

[P00244 | 21294:21716 | NORMAL_TEXT]
3.  Generate and validate the required noncanonical Izanami stage artifacts first. Keep them outside canonical package discovery during validation; only after every owner/latest route, block range, authentication digest, patch identity, and source codec passes — and Destiny is closed — promote each accepted artifact to its unique canonical <stem>.pkg path. Section 17.43 documents the public Sunrise discovery boundary.

[P00245 | 21716:21797 | NORMAL_TEXT]
4.  Launch Destiny, enter Tower Carrier Control, and wait for activity:in_world.

[P00246 | 21797:21902 | NORMAL_TEXT]
5.  Judge geometry from a stable viewpoint. player_broadcast spam alone is not a launch failure verdict.

[P00247 | 21902:21972 | NORMAL_TEXT]
6.  Close Destiny before changing or replacing the DLL/package again.

[P00248 | 21972:21973 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00249 | 21973:22011 | HEADING_1]
15. Evidence and Known-Good Artifacts

[P00250 | 22011:22086 | NORMAL_TEXT]
Runtime logs are under B:\!!izanami\Destiny2-Sunrise\bin\x64\Sunrise\logs.

[P00251 | 22086:22087 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00252 | 22087:22120 | NORMAL_TEXT]
Known-good source-codec rewrite:

[P00253 | 22120:22215 | NORMAL_TEXT]
B:\!!izanami\Destiny2-Sunrise\packages\w64_city_tower_d2_0369_7.pkg.izanami-passed-lzh-rewrite

[P00254 | 22215:22289 | NORMAL_TEXT]
SHA-256: 795A96CDC57F545C7F56ED86BD4DC1B957681F8569533BDF0A7665914083CE77

[P00255 | 22289:22290 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00256 | 22290:22326 | NORMAL_TEXT]
Confirmed native-transform package:

[P00257 | 22326:22394 | NORMAL_TEXT]
B:\!!izanami\Destiny2-Sunrise\packages\w64_city_tower_d2_0369_8.pkg

[P00258 | 22394:22471 | NORMAL_TEXT]
Preserved copy: w64_city_tower_d2_0369_8.pkg.izanami-passed-native-transform

[P00259 | 22471:22545 | NORMAL_TEXT]
SHA-256: 520D4707D998F423B05A936D1642D722A20F636F7E8116DF430CD90ECA99994B

[P00260 | 22545:22565 | NORMAL_TEXT]
Size: 299,008 bytes

[P00261 | 22565:22758 | NORMAL_TEXT]
Validation: package 0x0369, patch 8, 7,308 entries, 584 blocks, one patch-8 block. Block 19 is at file offset 249,856, compressed size 47,938, flags 0x3; its range and embedded SHA-1 validate.

[P00262 | 22758:22759 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00263 | 22759:22785 | NORMAL_TEXT]
Observed native mutation:

[P00264 | 22785:23037 | NORMAL_TEXT]
Map table 0x80ED22FB, entry 0, parent resource 0x80ED22FA changed translation from (0, 0, 0) to (64, 0, 0). The user confirmed that a large Tower scenery aggregate visibly moved in game. The run reached activity:in_world with no decompression failure.

[P00265 | 23037:23038 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00266 | 23038:23074 | HEADING_1]
16. Handoff Rules and Next Decision

[P00267 | 23074:23089 | NORMAL_TEXT]
VERIFIED FACTS

[P00268 | 23089:23161 | NORMAL_TEXT]
•  Tower Carrier Control can launch directly into a stable Tower world.

[P00269 | 23161:23253 | NORMAL_TEXT]
•  Destiny discovers and loads a canonical extra patch in the existing Tower package chain.

[P00270 | 23253:23305 | NORMAL_TEXT]
•  A byte-identical source-codec LZH rewrite loads.

[P00271 | 23305:23370 | NORMAL_TEXT]
•  A package-authored translation changes native world geometry.

[P00272 | 23370:23464 | NORMAL_TEXT]
•  player_broadcast can continue during successful gameplay and must be diagnosed separately.

[P00273 | 23464:23465 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00274 | 23465:23482 | NORMAL_TEXT]
DO NOT CLAIM YET

[P00275 | 23482:23535 | NORMAL_TEXT]
•  A new standalone destination or package identity.

[P00276 | 23535:23573 | NORMAL_TEXT]
•  A blank baseplate/sky/spawn world.

[P00277 | 23573:23639 | NORMAL_TEXT]
•  Forge-driven per-object spawn, move, rotate, scale, or delete.

[P00278 | 23639:23678 | NORMAL_TEXT]
•  A native Destiny Destinations node.

[P00279 | 23678:23705 | NORMAL_TEXT]
•  A production editor UI.

[P00280 | 23705:23706 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00281 | 23706:23733 | NORMAL_TEXT]
IMPLEMENTED - TEST PENDING

[P00282 | 23733:23855 | NORMAL_TEXT]
1.  Add an explicit native map binding to ForgeObject: table tag, entry index, expected parent tag, and source transform.

[P00283 | 23855:23972 | NORMAL_TEXT]
2.  Seed the proven Tower binding (table 0x80ED22FB, entry 0, parent 0x80ED22FA) into the Blank Baseplate workspace.

[P00284 | 23972:24114 | NORMAL_TEXT]
3.  Make package generation consume the selected Forge object's absolute transform instead of applying a hard-coded first-match +64 X offset.

[P00285 | 24114:24202 | NORMAL_TEXT]
4.  Reject stale or duplicate bindings and validate the expected parent before writing.

[P00286 | 24202:24308 | NORMAL_TEXT]
5.  Catalog all Tower static placements and choose a smaller, visually isolated target for the next test.

[P00287 | 24308:24408 | NORMAL_TEXT]
6.  Use selective placement removal/rebinding to approach a safe baseplate, sky, and spawn carrier.

[P00288 | 24408:24525 | NORMAL_TEXT]
7.  Continue new destination/package identity research only after the selective existing-chain pipeline is reliable.

[P00289 | 24525:24728 | NORMAL_TEXT]
8.  Then connect rotation, scale, native spawning/destruction, and the two-surface Forge UI: restrained Destiny-style in-game controls plus a separate Explorer/Toolbox/Properties editor beside the game.

[P00290 | 24728:24729 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00291 | 24729:24730 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00292 | 24730:24731 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00293 | 24731:24796 | NORMAL_TEXT]
16. Source-Derived Static-Instance Binding Contract — 2026-08-19

[P00294 | 24796:24797 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00295 | 24797:25129 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED reverse engineering from current Alkahest/Charm schemas and render code. It does not supersede Codex/user field-tested results above. The field-tested baseline remains: Tower patch 8 moved table 0x80ED22FB / entry 0 / parent 0x80ED22FA by +64 X and reached activity:in_world.

[P00296 | 25129:25130 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00297 | 25130:25218 | NORMAL_TEXT]
16.1 The proven map-node edit is an aggregate binding, not yet an individual Forge prop

[P00298 | 25218:25867 | NORMAL_TEXT]
Current external schemas agree that a map node table is class 0x80809883 and each 0x90-byte map node is class 0x80809885. The node begins with quaternion rotation, then a Vec4 translation whose XYZ is position and whose W is interpreted by Alkahest as uniform scale; it carries a WideHash entity/pattern reference at +0x28, world_id at +0x70, and map-specific component data at +0x78. This matches the current Izanami package breakthrough at the outer map-node layer, but a map node can own a broad pattern/aggregate. That explains why moving the first bounded Tower record moved a large portion of scenery instead of behaving like one editor prop.

[P00299 | 25867:25868 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00300 | 25868:25952 | NORMAL_TEXT]
16.2 Post-BL/WQ component-chain reference — not the current Shadowkeep Tower parser

[P00301 | 25952:26330 | NORMAL_TEXT]
VERSION-SCOPED REFERENCE. The chain below is a later Post-BL/WQ component model. For the installed Shadowkeep Tower chain, use the direct SMapDataTable/SMapDataTableEntry -> 0x808071B3 DataResource -> 0x80806EF4 parent -> 0x8080966D static-instances bridge recovered in Section 17.32; do not require the 0x80806CC8/0x80806CC9 component path to catalog current Tower placements.

[P00302 | 26330:26355 | NORMAL_TEXT]
SMapNodeEntry 0x80809885

[P00303 | 26355:26388 | NORMAL_TEXT]
  -> SPattern / entity reference

[P00304 | 26388:26449 | NORMAL_TEXT]
  -> component type 0x80806CC8 (static-instances collection)

[P00305 | 26449:26499 | NORMAL_TEXT]
  -> map-specific component data class 0x80806CC9

[P00306 | 26499:26570 | NORMAL_TEXT]
  -> wrapper/resource tag (observed Alkahest wrapper class 0x80806A0D)

[P00307 | 26570:26607 | NORMAL_TEXT]
  -> SStaticMeshInstances 0x808093AD

[P00308 | 26607:26638 | NORMAL_TEXT]
  -> instance group 0x80806D28

[P00309 | 26638:26700 | NORMAL_TEXT]
  -> one or more SStaticInstanceTransform 0x80806D40 records.

[P00310 | 26700:26701 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00311 | 26701:27440 | NORMAL_TEXT]
SStaticMeshInstances is 0xC0 bytes in the current schema. It contains an occlusion-bounds tag at +0x18, an optional transform-to-bounds-index vector at +0x20, the instance-transform vector at +0x40, a static-mesh TagHash vector, an instance-group vector, and collection-level bounds. Each instance group is eight bytes: instance_count, instance_start, static_index, and an unknown u16. The group defines a contiguous range of transforms and static_index selects the mesh/model used by the group. Each individual transform is 0x40 bytes and contains quaternion rotation, Vec3 translation, and one scalar uniform scale. Charm independently describes the same current transform class and notes that only the first/global scale value is used.

[P00312 | 27440:27441 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00313 | 27441:27483 | NORMAL_TEXT]
16.3 Recommended persistent Forge binding

[P00314 | 27483:27662 | NORMAL_TEXT]
Do not overload ForgeUUID with package identity. ForgeUUID remains the stable editor identity. Add a serializable PackagePlacementBinding variant for package-authored placements:

[P00315 | 27662:27663 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00316 | 27663:27687 | NORMAL_TEXT]
MapNodeAggregateBinding

[P00317 | 27687:27705 | NORMAL_TEXT]
  mapNodeTableTag

[P00318 | 27705:27717 | NORMAL_TEXT]
  nodeIndex

[P00319 | 27717:27747 | NORMAL_TEXT]
  expectedPatternOrEntityHash

[P00320 | 27747:27775 | NORMAL_TEXT]
  expectedParent/provenance

[P00321 | 27775:27793 | NORMAL_TEXT]
  sourceTransform

[P00322 | 27793:27813 | NORMAL_TEXT]
  sourceFingerprint

[P00323 | 27813:27814 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00324 | 27814:27836 | NORMAL_TEXT]
StaticInstanceBinding

[P00325 | 27836:27854 | NORMAL_TEXT]
  mapNodeTableTag

[P00326 | 27854:27866 | NORMAL_TEXT]
  nodeIndex

[P00327 | 27866:27896 | NORMAL_TEXT]
  expectedPatternOrEntityHash

[P00328 | 27896:27917 | NORMAL_TEXT]
  staticInstancesTag

[P00329 | 27917:27938 | NORMAL_TEXT]
  instanceGroupIndex

[P00330 | 27938:27960 | NORMAL_TEXT]
  expectedStaticIndex

[P00331 | 27960:27984 | NORMAL_TEXT]
  expectedStaticMeshTag

[P00332 | 27984:28001 | NORMAL_TEXT]
  transformIndex

[P00333 | 28001:28015 | NORMAL_TEXT]
  boundsIndex

[P00334 | 28015:28033 | NORMAL_TEXT]
  sourceTransform

[P00335 | 28033:28048 | NORMAL_TEXT]
  sourceBounds

[P00336 | 28048:28068 | NORMAL_TEXT]
  sourceFingerprint

[P00337 | 28068:28069 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00338 | 28069:28693 | NORMAL_TEXT]
Resolution must fail closed if any expected identity, index range, parent chain, structural fingerprint, or accepted mutable preimage differs. Do not collapse immutable identity and mutable authored bytes into one sourceFingerprint: keep a stable structural/source-baseline fingerprint plus an explicitly evolving expected-canonical-preimage fingerprint so a verified Izanami-authored postimage can be recognized without accepting unrelated drift. A package binding is persistent/serializable; a future native RuntimeObjectBinding is separate and ephemeral. Never serialize a raw live Destiny handle into the .iforge scene.

[P00339 | 28693:28694 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00340 | 28694:28788 | NORMAL_TEXT]
16.4 Post-BL culling/bounds model — reference only; current Shadowkeep correction is in 17.16

[P00341 | 28788:29274 | NORMAL_TEXT]
Alkahest's current static renderer proves that static-instance visibility is not driven by the transform vector alone. For each group it resolves a per-transform occlusion bound: when transform_to_bounds_index is empty, the transform index is used directly; otherwise the mapping vector selects the bound. Group visibility is derived from those bounds, and the entire collection is first rejected against the top-level SStaticMeshInstances bounds before per-group/per-instance testing.

[P00342 | 29274:29275 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00343 | 29275:29874 | NORMAL_TEXT]
HYPOTHESIS / IMPLEMENTATION CONSEQUENCE. If Izanami moves one static transform but leaves the corresponding occlusion bound and collection bounds at the old position, Destiny may cull the moved geometry incorrectly. Therefore the first per-instance package mutation should change one transform and its associated culling bounds together. Translation-only is the safest first proof: shift the selected instance translation and its matching AABB by the exact same delta, then recompute or conservatively expand the collection bounds. Do not resize vectors or alter instance-group counts in this test.

[P00344 | 29874:29875 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00345 | 29875:31001 | NORMAL_TEXT]
For rotation/scale after translation is proven, do not assume the raw occlusion AABB is a mesh-local box that Destiny or the renderer will transform with the instance. Current Alkahest uploads the instance SRT to GPU constants but consumes the resolved occlusion AABBs directly for visibility and derives group bounds by union; it does not apply the instance matrix to those AABBs at cull time. The safer rotation/scale candidate is therefore geometry-derived: compute source render AABB G0 from decoded mesh geometry + ModelTransform + source instance SRT, measure conservative per-side padding between G0 and the raw source bound B0 when B0 contains G0, compute target render AABB G1 under the proposed target SRT, then reapply that preserved padding to form B1. An eight-corner transform of B0 is a conservative fallback/diagnostic, not the preferred authored-bound model. Rebuild or conservatively expand collection bounds from the resulting per-instance bounds. Start with finite positive uniform scale only. Quaternion direction/handedness remains SOURCE-DERIVED/Unresolved until a separate Izanami rotation field test.

[P00346 | 31001:31002 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00347 | 31002:31036 | NORMAL_TEXT]
16.5 Placement-catalog diagnostic

[P00348 | 31036:31164 | NORMAL_TEXT]
The next read-only catalog should enumerate every static collection reachable from each map node and emit one row per instance:

[P00349 | 31164:31395 | NORMAL_TEXT]
map table tag; node index; pattern/entity hash; world_id provenance; static-instances tag; group index; static mesh tag; transform index; bounds index; position; quaternion; uniform scale; group instance count; source fingerprint.

[P00350 | 31395:31396 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00351 | 31396:31664 | NORMAL_TEXT]
Rank first-test candidates by isolation. Prefer group instance_count == 1, otherwise the smallest groups with compact, non-overlapping bounds and a distinctive mesh tag. This is a better candidate-selection rule than continuing to patch the first table/entry blindly.

[P00352 | 31664:31665 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00353 | 31665:31712 | NORMAL_TEXT]
16.6 Collision is a separate acceptance signal

[P00354 | 31712:32331 | NORMAL_TEXT]
Charm's map-resource schemas show Havok volumes can live in separate map DataResource classes and are transformed by the outer map-node transform when exported. This is evidence that visual static-instance placement and collision resources may not share the same editable record. The first individual-static field test must therefore check both rendering and collision at the old/new location. If the visual moves but collision remains, classify StaticInstanceBinding as render-static only and do not expose it as a gameplay-solid editable prop until the corresponding collision resource/instance binding is recovered.

[P00355 | 32331:32332 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00356 | 32332:32640 | NORMAL_TEXT]
Do not use deletion as the first static-instance experiment. Shrinking transform arrays, changing group counts, or deleting model references changes multiple native assumptions at once. First prove one transform + culling-bounds mutation, then rotation/scale, then separately recover safe removal semantics.

[P00357 | 32640:32641 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00358 | 32641:32692 | NORMAL_TEXT]
16.7 UI/runtime contract resulting from this split

[P00359 | 32692:33242 | NORMAL_TEXT]
Package-backed objects may be selectable/editable in the external Forge workspace, but their status must clearly read Package-backed / Requires Build & Reload until a valid live runtime binding exists. Gizmo actions may update Forge-owned scene data immediately and mark the compiled package dirty; they must not claim a live Destiny object moved until the native/runtime backend reports a proven valid handle. Undo/redo should operate on Forge scene state; the package compiler then regenerates derived package output from that authoritative state.

[P00360 | 33242:33243 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00361 | 33243:33654 | NORMAL_TEXT]
Sources used for this source-derived section: cohaereo/alkahest current map/static/pattern/render schemas and MontagueM/Charm current static-map/Havok schemas, inspected 2026-08-19. Key class IDs cross-check consistently across both tools: map table 0x80809883, map entry 0x80809885, static instances 0x808093AD, instance transform 0x80806D40, instance group 0x80806D28, occlusion bounds 0x808093B1/0x808093B3.

[P00362 | 33654:33655 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00363 | 33655:34309 | NORMAL_TEXT]
2026-08-19 — Research update: reconciled the newest Codex/user field-tested breakthrough (direct Tower carrier and package-backed +64 X native world mutation) before continuing source research. Promoted the map-node record to an explicit MapNodeAggregateBinding and recovered a deeper per-static instance chain through 0x80806CC8/0x80806CC9 -> 0x808093AD -> group/model/transform. Added the culling-bounds dependency, a read-only placement-catalog schema, a translation-only first individual-instance experiment, and a separate collision acceptance signal. No repository files, DLLs, packages, or running Destiny process were changed by this research pa

[P00364 | 34309:34310 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00365 | 34310:34311 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00366 | 34311:34349 | HEADING_1]
17. Current Selective Placement Build

[P00367 | 34349:34434 | NORMAL_TEXT]
PATCH 9 REJECTED BY NATIVE SLOT ROUTING; SELECTIVE PATCH 8 INSTALLED; RETEST PENDING

[P00368 | 34434:34435 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00369 | 34435:34769 | NORMAL_TEXT]
The broad first-table mutation has been replaced by an explicit Forge-to-package edit path. Patch 9 was structurally valid but failed native patch-slot routing in game. The same two validated edits are now installed in the last proven native slot, patch 8, and the builder is capped there; the corrected field result remains pending.

[P00370 | 34769:34770 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00371 | 34770:34798 | NORMAL_TEXT]
Implementation now present:

[P00372 | 34798:34935 | NORMAL_TEXT]
•  ForgeObject carries an optional NativeMapBinding with map table tag, entry index, expected parent tag, and complete source transform.

[P00373 | 34935:35186 | NORMAL_TEXT]
•  Blank Baseplate no longer seeds fake local anchor/marker/door objects. Its first Build action catalogs readable Tower static-resource placements and creates two package-backed scene objects: Tower Aggregate Restore and Small Tower Placement Probe.

[P00374 | 35186:35341 | NORMAL_TEXT]
•  The known aggregate binding remains table 0x80ED22FB, entry 0, parent 0x80ED22FA. Its authored target is X = 0, restoring the patch-8 +64 X experiment.

[P00375 | 35341:35534 | NORMAL_TEXT]
•  The smaller probe must use a different parent. Candidates are ranked by smaller static-resource payload, then proximity; the selected probe receives +64 X for a visually obvious field test.

[P00376 | 35534:35738 | NORMAL_TEXT]
•  Package generation consumes the Forge objects' absolute transforms. It accepts at most 32 explicit edits and rejects invalid, duplicate, non-Tower, stale-source, wrong-class, or wrong-parent bindings.

[P00377 | 35738:36011 | NORMAL_TEXT]
•  Each write validates the full source translation, quaternion, and uniform scale before writing the complete target transform. Modified blocks retain the source Oodle codec and must pass the existing decrypt/decompress round trip before a .izanami-stage file is emitted.

[P00378 | 36011:36264 | NORMAL_TEXT]
•  Package-backed objects are labeled package in the Forge hierarchy/inspector. Their table, entry, and parent identity is visible; transform editing is enabled, while the runtime adapter records staged-on-build instead of claiming a live object moved.

[P00379 | 36264:36265 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00380 | 36265:36613 | NORMAL_TEXT]
Scope warning: this milestone binds a smaller outer map placement/static-resource record. It does not yet prove the deeper per-instance SStaticMeshInstances transform-and-bounds chain described in section 16, and it must not be called individual-prop editing until the field result identifies the moved geometry and its collision/culling behavior.

[P00381 | 36613:36614 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00382 | 36614:36630 | NORMAL_TEXT]
Deployed build:

[P00383 | 36630:36680 | NORMAL_TEXT]
Release target: build/x64/Release/steam_api64.dll

[P00384 | 36680:36744 | NORMAL_TEXT]
Installed target: B:\!!izanami\Destiny2-Sunrise\steam_api64.dll

[P00385 | 36744:36818 | NORMAL_TEXT]
SHA-256: 4E5ED4AB49CFEF00F0D69C91CE8B62848AC2B7AD438576328E983B535E5F3EC7

[P00386 | 36818:36819 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00387 | 36819:36840 | NORMAL_TEXT]
Next field sequence:

[P00388 | 36840:36879 | NORMAL_TEXT]
1.  Start Destiny and remain in orbit.

[P00389 | 36879:36968 | NORMAL_TEXT]
2.  Open Izanami Forge, select Blank Baseplate, and use Open Editor or the build action.

[P00390 | 36968:37164 | NORMAL_TEXT]
3.  Trigger Build Tower Baseplate Patch once. Confirm the hierarchy contains Tower Aggregate Restore and Small Tower Placement Probe and that the status reports two source-validated edits staged.

[P00391 | 37164:37323 | NORMAL_TEXT]
4.  Close Destiny completely. Inspect the structured candidate/mutation logs and the new w64_city_tower_d2_0369_9.pkg.izanami-stage artifact before promotion.

[P00392 | 37323:37472 | NORMAL_TEXT]
5.  Promote the staged file only after its package identity, patch number, modified-block count, codec, hashes, and two explicit mutations validate.

[P00393 | 37472:37698 | NORMAL_TEXT]
6.  Relaunch and use Tower Carrier Control. Verify the previously shifted large aggregate returned to stock and identify exactly which smaller object moved. Also test visual culling and collision at the old and new positions.

[P00394 | 37698:37699 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00395 | 37699:37885 | NORMAL_TEXT]
Do not claim yet: the patch-7 carrier layout loaded in Destiny, aggregate restored in game, smaller placement moved in game, individual static-instance editing, or a blank custom world.

[P00396 | 37885:37886 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00397 | 37886:37887 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00398 | 37887:37915 | HEADING_2]
17.1 Patch 9 Build Evidence

[P00399 | 37915:37978 | NORMAL_TEXT]
PATCH 9 BUILD VALIDATED; NATIVE SLOT-ROUTING FIELD TEST FAILED

[P00400 | 37978:37979 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00401 | 37979:38199 | NORMAL_TEXT]
The live catalog completed successfully against map:city_tower_d2:root. It traversed 813 graph nodes and 161 map tables, of which 136 were local Tower tables. Thirteen readable static-resource placements were cataloged.

[P00402 | 38199:38200 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00403 | 38200:38228 | NORMAL_TEXT]
Selected smaller placement:

[P00404 | 38228:38246 | NORMAL_TEXT]
Table: 0x80ED2B6F

[P00405 | 38246:38255 | NORMAL_TEXT]
Entry: 0

[P00406 | 38255:38274 | NORMAL_TEXT]
Parent: 0x80ED2B6E

[P00407 | 38274:38295 | NORMAL_TEXT]
Data tag: 0x80ED2B6D

[P00408 | 38295:38364 | NORMAL_TEXT]
Static-resource payload: 656 bytes, the smallest cataloged candidate

[P00409 | 38364:38440 | NORMAL_TEXT]
Source transform: position (0, 0, 0), quaternion unchanged, uniform scale 1

[P00410 | 38440:38519 | NORMAL_TEXT]
Authored transform: position (64, 0, 0), quaternion unchanged, uniform scale 1

[P00411 | 38519:38520 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00412 | 38520:38548 | NORMAL_TEXT]
Explicit mutations emitted:

[P00413 | 38548:38641 | NORMAL_TEXT]
•  Restored table 0x80ED22FB, entry 0, parent 0x80ED22FA from (64, 0, 0, 1) to (0, 0, 0, 1).

[P00414 | 38641:38731 | NORMAL_TEXT]
•  Moved table 0x80ED2B6F, entry 0, parent 0x80ED2B6E from (0, 0, 0, 1) to (64, 0, 0, 1).

[P00415 | 38731:38732 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00416 | 38732:38752 | NORMAL_TEXT]
Generated artifact:

[P00417 | 38752:38877 | NORMAL_TEXT]
Failed artifact archive: B:\!!izanami\Destiny2-Sunrise\packages\w64_city_tower_d2_0369_9.pkg.izanami-failed-native-slot-wrap

[P00418 | 38877:38951 | NORMAL_TEXT]
SHA-256: B818E4CECC0B333F3C6E897455260ACD193C18425FFDCD144D2895326FF6584E

[P00419 | 38951:39005 | NORMAL_TEXT]
Package identity: version 38, package 0x0369, patch 9

[P00420 | 39005:39056 | NORMAL_TEXT]
File size: 475,136 bytes; header file size matches

[P00421 | 39056:39135 | NORMAL_TEXT]
Tables: 7,308 entries and 584 blocks; entry table is byte-identical to patch 8

[P00422 | 39135:39165 | NORMAL_TEXT]
Changed block rows: exactly 2

[P00423 | 39165:39305 | NORMAL_TEXT]
•  Block 19: offset 299,008; stored size 47,935; flags 0x3; patch 9; embedded SHA-1 valid; source/authored Oodle prefix 8C07; compressor 0.

[P00424 | 39305:39447 | NORMAL_TEXT]
•  Block 164: offset 348,160; stored size 125,322; flags 0x3; patch 9; embedded SHA-1 valid; source/authored Oodle prefix 8C07; compressor 0.

[P00425 | 39447:39664 | NORMAL_TEXT]
Both block bodies are aligned, in range, and passed the builder's decrypt/decompress round-trip validation. The staged and canonical files have identical SHA-256 values. Destiny was closed before canonical promotion.

[P00426 | 39664:39665 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00427 | 39665:39904 | NORMAL_TEXT]
Historical result: this patch 9 artifact did not load. Native verification routed its block-164 request through package slot 3 and failed before activity:in_world. Section 17.2 records the patch-8 recovery and current retest instructions.

[P00428 | 39904:39905 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00429 | 39905:40091 | NORMAL_TEXT]
Do not claim yet: the patch-7 carrier layout loaded in Destiny, aggregate restored in game, smaller placement moved in game, individual static-instance editing, or a blank custom world.

[P00430 | 40091:40092 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00431 | 40092:40093 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00432 | 40093:40145 | HEADING_2]
17.2 Native Patch-Slot Failure and Patch 8 Recovery

[P00433 | 40145:40233 | NORMAL_TEXT]
PATCH 9 FIELD FAILURE VERIFIED; DIRECT-BODY PATCH 8 ALSO FAILED; CARRIER RETEST PENDING

[P00434 | 40233:40234 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00435 | 40234:40260 | NORMAL_TEXT]
Observed patch 9 failure:

[P00436 | 40260:40350 | NORMAL_TEXT]
•  Destiny accepted the broader Tower trust category but did not reach activity:in_world.

[P00437 | 40350:40485 | NORMAL_TEXT]
•  Native asynchronous verification repeatedly failed for w64_city_tower_d2_0369_3.pkg at offset 348,160 while loading tag 0x80ED2B60.

[P00438 | 40485:40757 | NORMAL_TEXT]
•  The requested failed record was patch 9 block 164, whose authored body lived at the same offset. The native diagnostic resolving patch ID 9 through package slot 3 is direct evidence that incrementing beyond the proven patch-8 ceiling is not safe in this package chain.

[P00439 | 40757:40936 | NORMAL_TEXT]
•  The process remained responsive, but the resource load had already failed with riddle failure and the transition could not recover. Destiny was closed before package recovery.

[P00440 | 40936:40937 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00441 | 40937:40957 | NORMAL_TEXT]
Recovery performed:

[P00442 | 40957:41091 | NORMAL_TEXT]
•  Canonical patch 9 was removed from the active chain and preserved as w64_city_tower_d2_0369_9.pkg.izanami-failed-native-slot-wrap.

[P00443 | 41091:41258 | NORMAL_TEXT]
•  The already validated selective artifact was converted to patch slot 8 by changing only the header patch ID and the patch IDs in block rows 19 and 164 from 9 to 8.

[P00444 | 41258:41403 | NORMAL_TEXT]
•  The encrypted bodies, GCM tags, embedded SHA-1 values, Oodle streams, offsets, sizes, and two authored placement transforms remain unchanged.

[P00445 | 41403:41538 | NORMAL_TEXT]
•  The previously successful aggregate-only patch 8 remains preserved as w64_city_tower_d2_0369_8.pkg.izanami-passed-native-transform.

[P00446 | 41538:41539 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00447 | 41539:41596 | NORMAL_TEXT]
Superseded direct-body package (failed in Section 17.3):

[P00448 | 41596:41683 | NORMAL_TEXT]
Canonical package: B:\!!izanami\Destiny2-Sunrise\packages\w64_city_tower_d2_0369_8.pkg

[P00449 | 41683:41757 | NORMAL_TEXT]
SHA-256: FB5114D2416061C186FA6F23FBA47D1B139B2854127EF7C219F53F3E331A88D5

[P00450 | 41757:41811 | NORMAL_TEXT]
Package identity: version 38, package 0x0369, patch 8

[P00451 | 41811:41862 | NORMAL_TEXT]
File size: 475,136 bytes; header file size matches

[P00452 | 41862:41911 | NORMAL_TEXT]
Patch-8 block rows: exactly 2, blocks 19 and 164

[P00453 | 41911:42028 | NORMAL_TEXT]
Both bodies remain aligned, in range, flags 0x3, and have valid embedded SHA-1 values. No canonical patch 9 remains.

[P00454 | 42028:42029 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00455 | 42029:42057 | NORMAL_TEXT]
Durable builder correction:

[P00456 | 42057:42112 | NORMAL_TEXT]
•  Tower output is capped at native-safe patch slot 8.

[P00457 | 42112:42199 | NORMAL_TEXT]
•  A source chain above slot 8 is rejected instead of generating another unsafe patch.

[P00458 | 42199:42403 | NORMAL_TEXT]
•  When canonical patch 8 already exists, later Forge builds stage another patch 8 derived from that complete canonical file. This supports iterative replacement without advancing the native patch index.

[P00459 | 42403:42504 | NORMAL_TEXT]
•  Corrected deployed DLL SHA-256: 2CF9E81F577E3879F5FB7181C3E237BCE19D64BA911C269AE01A2BA8F0709348.

[P00460 | 42504:42505 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00461 | 42505:42794 | NORMAL_TEXT]
Next action: relaunch Destiny and use Tower Carrier Control -> Launch In Destiny without rebuilding. Verify that selective patch 8 loads, the large aggregate returns to stock, and the smaller table 0x80ED2B6F placement moves by +64 X. Check visual culling and collision at both locations.

[P00462 | 42794:42795 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00463 | 42795:42981 | NORMAL_TEXT]
Do not claim yet: the patch-7 carrier layout loaded in Destiny, aggregate restored in game, smaller placement moved in game, individual static-instance editing, or a blank custom world.

[P00464 | 42981:43034 | HEADING_2]
17.3 Direct Patch 8 Failure and Patch 7 Body Carrier

[P00465 | 43034:43116 | NORMAL_TEXT]
DIRECT-BODY PATCH 8 AND UNCLAIMED PATCH 7 CARRIER FAILED; DUAL-ROW RETEST PENDING

[P00466 | 43116:43117 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00467 | 43117:43160 | NORMAL_TEXT]
Field result that corrected the diagnosis:

[P00468 | 43160:43283 | NORMAL_TEXT]
- The selective direct-body patch 8 reached Tower initial-slice loading, then failed at t=63,594 before activity:in_world.

[P00469 | 43283:43421 | NORMAL_TEXT]
- Native verification again reported w64_city_tower_d2_0369_3.pkg at offset 348,160 while loading tag 0x80ED2B60 (entry 2912, block 164).

[P00470 | 43421:43651 | NORMAL_TEXT]
- The active public block row contained the new offset and patch ID 8, but the native request retained block 164's original patch-3 ownership. This disproves the earlier conclusion that the failure was only patch-9 slot wrapping.

[P00471 | 43651:43882 | NORMAL_TEXT]
- Package AES-GCM nonce construction depends on package ID 0x0369, not patch ID. The generated body, GCM tag, stored SHA-1, and Oodle round trip were locally valid; changing only the patch number was not the cryptographic failure.

[P00472 | 43882:43976 | NORMAL_TEXT]
- Destiny remained responsive but could not recover from the resource failure and was closed.

[P00473 | 43976:43977 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00474 | 43977:44007 | NORMAL_TEXT]
Installed carrier experiment:

[P00475 | 44007:44168 | NORMAL_TEXT]
- Patch 8 remains the latest metadata layer. SHA-256: 4CFB1A893247C3057181F1E99D474761354DA0BF248A45A1E9ADB8ECB5FDB0B1; size 475,136 bytes; header size matches.

[P00476 | 44168:44269 | NORMAL_TEXT]
- Block 19 remains in patch 8 at offset 299,008, size 47,935, flags 0x3, with matching stored SHA-1.

[P00477 | 44269:44447 | NORMAL_TEXT]
- Block 164's patch-8 metadata now points to patch 7 at offset 249,856, size 125,322, flags 0x3. The carrier body is in range and its stored SHA-1 exactly matches the block row.

[P00478 | 44447:44631 | NORMAL_TEXT]
- Patch 7 was extended without overlapping its existing block data. SHA-256: EC5652A3C7C1847C8DE408E55E3C46AA6A056B84E3522FE4393A56231ACB5AA3; size 376,832 bytes; header size matches.

[P00479 | 44631:44779 | NORMAL_TEXT]
- Pre-carrier patch 7 and failed direct-body patch 8 are preserved as .izanami-pre-carrier-routing and .izanami-failed-direct-body-routing backups.

[P00480 | 44779:44780 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00481 | 44780:44808 | NORMAL_TEXT]
Durable builder correction:

[P00482 | 44808:44857 | NORMAL_TEXT]
- Tower metadata remains capped at patch slot 8.

[P00483 | 44857:44988 | NORMAL_TEXT]
- Newly authored Tower block bodies are staged in the field-proven patch 7 carrier, while patch 8 receives the updated block rows.

[P00484 | 44988:45172 | NORMAL_TEXT]
- The builder emits separate .izanami-stage and .izanami-carrier-stage artifacts and validates package identity, file size, encryption, compression, and stored digests before staging.

[P00485 | 45172:45272 | NORMAL_TEXT]
- Corrected deployed DLL SHA-256: 34808D9328A0FA0CE9CBD9D61304B069E001FB63E3F6C01DC36BD54AD9185B22.

[P00486 | 45272:45273 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00487 | 45273:45568 | NORMAL_TEXT]
Next field action: start Destiny, select Tower Carrier Control, and use Launch In Destiny without rebuilding. Confirm whether Tower loads, whether any verification error now names patch 7, whether the large aggregate is restored, and whether the small table 0x80ED2B6F placement moved by +64 X.

[P00488 | 45568:45569 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00489 | 45569:45795 | NORMAL_TEXT]
Do not claim yet: the patch-7 carrier layout loaded in Destiny, the aggregate restored, the smaller placement moved, collision followed the placement, individual static editing works generally, or a blank custom world exists.

[P00490 | 45795:45796 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00491 | 45796:45797 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00492 | 45797:45880 | NORMAL_TEXT]
17.4 Source-Derived Block Ownership Model and Safer Candidate Ranking — 2026-08-19

[P00493 | 45880:45881 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00494 | 45881:46222 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from current public Tiger package readers and is reconciled against the FIELD-TESTED failures in Sections 17.1-17.3. It does not supersede the pending patch-7 carrier field test; it changes how that result should be interpreted and how the next placement candidate should be selected.

[P00495 | 46222:46223 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00496 | 46223:47093 | NORMAL_TEXT]
SOURCE-DERIVED. v4nguard/tiger-pkg’s shared Destiny 2 package reader models every block row as {offset, size, patch_id, flags, hash, gcm_tag}. Its get_block_raw() implementation uses block.patch_id as a physical-owner selector: when the block’s patch_id equals the currently opened package header patch, it reads the body from the current file; otherwise it opens <package-family>_<block.patch_id>.pkg and reads the body at that block row’s offset. MontagueM/Charm independently implements the same ownership model: file reads open GetPackageHandle(blockEntry.PatchId), GetRequiredPatches() is derived from every referenced block’s PatchId, and the patch handle path is constructed from that PatchId. Both independent readers therefore treat the block-row PatchId as the physical package file that owns the stored block body, not merely a descriptive generation number.

[P00497 | 47093:47094 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00498 | 47094:47931 | NORMAL_TEXT]
FIELD-TESTED CONTRADICTION / STRONG HYPOTHESIS. Izanami’s block-164 experiments did not follow that simple edited-row model in Destiny’s native runtime. Patch 9 and direct-body patch 8 both installed a latest block row whose authored body lived at offset 348,160 and whose row PatchId had been changed, yet native verification repeatedly opened w64_city_tower_d2_0369_3.pkg for tag 0x80ED2B60 / entry 2912 / block 164 while retaining the new authored offset. The strongest current hypothesis is that Destiny maintains an authoritative registered/merged block-owner route for block 164 that remains patch 3 and is not replaced merely by changing the latest public block row’s PatchId. This may be a registrar-owned merged table, cached ownership map, or another per-entry/per-block route; the exact native structure is not yet recovered.

[P00499 | 47931:47932 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00500 | 47932:48560 | NORMAL_TEXT]
PREDICTION FOR THE CURRENT PATCH-7 CARRIER TEST. The test remains high-value because it distinguishes two models. If the patch-7 carrier reaches activity:in_world and the selective mutations appear, then Destiny accepted the redirected owner despite the earlier patch-3 observations; record that as a field-specific routing success while keeping the owner mechanism unresolved. If native verification still names w64_city_tower_d2_0369_3.pkg, especially at the new carrier offset, stop cycling candidate carrier patch numbers. That result would strongly confirm that block 164’s native owner is independently pinned to patch 3.

[P00501 | 48560:48561 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00502 | 48561:49246 | NORMAL_TEXT]
SAFER NEXT STRATEGY IF PATCH 7 STILL ROUTES TO PATCH 3. Prefer a new selective placement candidate whose complete source entry/block span already lives on a FIELD-PROVEN writable/loadable route, ideally the same route that backed the successful aggregate mutation, before modifying an original stock owner file. The first candidate-selection key should become routing safety, not smallest payload. Prefer: (1) entry fully contained in one block, (2) block owner/path already proven by an Izanami-loaded mutation, (3) no cross-block or cross-owner span, then (4) isolated static group / instance_count == 1, compact culling bounds, distinctive mesh, and finally payload size/proximity.

[P00503 | 49246:49247 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00504 | 49247:49989 | NORMAL_TEXT]
HIGHER-RISK FALLBACK EXPERIMENT. If no useful isolated candidate exists on a proven route, test an owner-preserving block-164 carrier only with Destiny closed and exact backup/restore tooling: keep block 164’s owner PatchId at its native-proven value 3, append the source-codec-preserving modified body to the physical patch-3 file at a non-overlapping aligned offset, update only the latest metadata needed to point block 164 to that offset while preserving owner 3, then validate package identity, bounds, GCM/SHA-1, codec round trip, and byte-for-byte restoration capability before launch. This is intentionally secondary because it mutates a stock owner package and carries more recovery risk than selecting a route-compatible placement.

[P00505 | 49989:49990 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00506 | 49990:50613 | NORMAL_TEXT]
PLACEMENT CATALOG CORRECTION. Every candidate row should now include package-route provenance in addition to table/node/static-instance provenance: source tag/entry, starting block, number of covered blocks, and for each covered block {block index, original owner PatchId, source offset, stored size, flags, codec identity}. Derive a route classification such as FieldProven, UnprovenSingleOwner, or CrossOwner and rank candidates by that before visual isolation. A multi-block entry is not automatically unsafe, but every covered block must have a coherent owner route and all modified blocks must be staged consistently.

[P00507 | 50613:50614 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00508 | 50614:51073 | NORMAL_TEXT]
BINDING CORRECTION. PackagePlacementBinding / StaticInstanceBinding should add a sourceBlockRouteFingerprint over the covered block indices, original owner PatchIds, source offsets/sizes/flags, and codec identity. Resolution/build must fail closed if this fingerprint changes. This keeps ForgeUUID stable while preventing a scene object from silently writing through a different package-chain route after stock package updates or a changed canonical carrier.

[P00509 | 51073:51074 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00510 | 51074:51829 | NORMAL_TEXT]
2026-08-19 — SOURCE-DERIVED research update: independent tiger-pkg and Charm readers agree that a block row’s PatchId selects the physical patch file containing that block body. Reconciling that with Izanami’s FIELD-TESTED block-164 failures strongly suggests Destiny retains a separate native owner route that remained patch 3 even when the latest row was changed to 8 or 9. The current patch-7 carrier test remains useful as a discriminator, but if the verifier still opens patch 3 the next safe move is route-aware candidate selection rather than more carrier-number cycling. Added source-block routing provenance/fingerprinting and route-first placement ranking; no repository, DLL, package, or running Destiny process was changed by this research pa

[P00511 | 51829:51830 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00512 | 51830:51831 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00513 | 51831:51950 | NORMAL_TEXT]
17.5 Post-BL/WQ Per-Instance Mutation Safety Reference — 2026-08-19 (superseded for current Shadowkeep bytes by 17.16)

[P00514 | 51950:51951 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00515 | 51951:52220 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from current Alkahest/Charm schemas and renderer code and is reconciled against the FIELD-TESTED Tower package-routing results above. It does not claim that an individual static instance has moved in Destiny yet.

[P00516 | 52220:52221 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00517 | 52221:53251 | NORMAL_TEXT]
TWO-RESOURCE MUTATION BOUNDARY. An individual static translation is not necessarily a one-tag edit. SStaticMeshInstances 0x808093AD stores the transform vector and collection-level bounds, but its per-instance occlusion data is referenced through a separate SOcclusionBounds 0x808093B1 TagHash at +0x18. Therefore the first correct StaticInstanceBinding mutation can require two independently routed package resources: (A) the SStaticMeshInstances tag containing the selected SStaticInstanceTransform and collection bounds, and (B) the separate SOcclusionBounds tag containing the mapped SObjectOcclusionBounds AABB. Given the block-164 owner-routing failures, candidate safety must validate both physical package routes before authoring. Extend StaticInstanceBinding with staticInstancesRouteFingerprint and occlusionBoundsRouteFingerprint, or a single mutableResourceSet fingerprint that covers both. Prefer candidates where every mutable resource is FieldProven, single-owner, and single-block before considering payload size.

[P00518 | 53251:53252 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00519 | 53252:53823 | NORMAL_TEXT]
UNIQUE BOUND OWNERSHIP. Alkahest's renderer proves that transform index and bounds index are not always one-to-one. If transform_to_bounds_index is empty, boundsIndex = transformIndex. Otherwise the u32 mapping at +0x20 selects the bound used by that transform. Multiple transforms may therefore reference one bounds record. The first field candidate must require boundsRefCount == 1. If a mapped bounds record is shared by siblings, skip it for the first proof; moving that AABB would alter culling for multiple instances and would no longer be a one-object experiment.

[P00520 | 53823:53824 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00521 | 53824:54828 | NORMAL_TEXT]
MINIMAL TRANSLATION-ONLY BYTE CONTRACT. SStaticInstanceTransform is 0x40 bytes: quaternion first, then Vec3 translation, scalar uniform scale, followed by AO/unknown fields. For the first individual test, modify translation XYZ only. Preserve quaternion, scale, vertex-AO offset, and every unknown tail byte exactly. SObjectOcclusionBounds 0x808093B3 is 0x30 bytes: the first 0x20 bytes are min/max Vec4 and the final 0x10 bytes are unknown/hash fields. Shift only min.xyz and max.xyz by the same translation delta, preserve both Vec4 W components and all final unknown bytes. For the SStaticMeshInstances collection AABB, use a conservative expansion instead of recomputing/shrinking the whole collection on the first test: newMinXYZ = min(oldCollectionMinXYZ, movedBoundMinXYZ), newMaxXYZ = max(oldCollectionMaxXYZ, movedBoundMaxXYZ), preserving the collection-bound W components. Do not change vector counts, relative pointers, group counts, static-model references, AO identifiers, or array lengths.

[P00522 | 54828:54829 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00523 | 54829:56017 | NORMAL_TEXT]
CANDIDATE FILTER ORDER. Rank by mutation safety before visual convenience: (1) all required mutable resources have coherent FieldProven/single-owner routes; (2) each edited resource is wholly contained in one validated block for the first proof; (3) group range is valid: instance_start + instance_count <= transforms.count; (4) static_index < statics.count; (5) mapped bounds index is in range and boundsRefCount == 1; (6) prefer instance_count == 1; (7) for the first inner-translation proof, prefer an outer LINEAR transform that is identity (rotation identity and Translation.W/uniform scale == 1); nonzero outer translation is acceptable because it cancels from the translation delta; (8) prefer static meshes without the current Alkahest vertex-animation indicator (mesh-group unk6 == 2) and with simpler/fewer special meshes; then rank compact/non-overlapping bounds, distinctive geometry, payload size, and proximity. The aggregate-only patch-8 success establishes block 19 as a FIELD-PROVEN mutation route. Search first for candidates whose complete mutable resource set remains on block 19 or another already field-proven route before revisiting the problematic block-164 path.

[P00524 | 56017:56018 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00525 | 56018:56861 | NORMAL_TEXT]
COORDINATE-SPACE CAVEAT. Do not yet serialize an SStaticInstanceTransform as an assumed absolute world transform. Alkahest's pattern loader accepts an outer map-node Transform, but its StaticRenderObject submission does not apply that ECS Transform to the static-instances renderer. That tool therefore cannot prove Destiny's native composition order between SMapNodeEntry and SStaticInstanceTransform. The field-tested aggregate move proves that Destiny applies the outer map-node transform, but the inner transform may be local to that node/pattern. Preserve both sourceOuterMapNodeTransform and sourceStaticLocalTransform in the binding, and prefer an identity outer node for the first individual translation. Absolute Forge-world editing should graduate only after a non-identity outer-node composition test or equivalent native evidence.

[P00526 | 56861:56862 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00527 | 56862:57448 | NORMAL_TEXT]
IMPLEMENTATION PARSER NOTE. Charm's DynamicArray<T> schema is a 0x10-byte header with count at +0x0 and a relative 64-bit pointer field beginning at +0x8 under its pointer semantics. Do not hand-wave these vectors with unchecked raw offsets. Add or reuse one validated Tiger dynamic-vector reader that checks signed count, pointer arithmetic overflow, target range, element-size multiplication, and full array containment before exposing transforms, statics, groups, bounds mapping, or bounds records to the placement catalog. A malformed or stale pointer must fail the binding closed.

[P00528 | 57448:57449 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00529 | 57449:58111 | NORMAL_TEXT]
NEXT FIELD EXPERIMENT AFTER ROUTE CATALOGING. Choose one identity-outer-transform, instance_count==1 candidate with unique bounds ownership and a fully field-proven mutable resource route. Apply one translation delta only using the transform + mapped AABB + conservative collection-bound contract above. Leave all other bytes and vector sizes unchanged. In game, independently verify visual movement, culling from multiple viewpoints, and collision at both old and new positions. If visual geometry moves but collision does not, classify the binding as RenderStaticOnly and keep gameplay-solid editing disabled until its collision resource binding is recovered.

[P00530 | 58111:58112 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00531 | 58112:58942 | NORMAL_TEXT]
2026-08-19 — SOURCE-DERIVED research update: refined the individual-static milestone into a two-resource transaction. SStaticMeshInstances owns transforms and collection bounds while per-instance AABBs live in a separately routed SOcclusionBounds tag, so a safe candidate must validate both package routes. Added unique-bound ownership (boundsRefCount == 1), an exact translation-only byte-preservation contract, conservative collection-bound expansion, route-first/static-safety ranking, a coordinate-space caveat requiring outer/local transform provenance, and a validated DynamicArray parser requirement. The successful aggregate's block 19 should be treated as the first FieldProven route to search for a per-instance candidate. No repository files, DLLs, packages, or running Destiny process were changed by this research pa

[P00532 | 58942:58943 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00533 | 58943:59040 | NORMAL_TEXT]
17.6 Post-BL/WQ Static AO and Shared-Resource Reference — 2026-08-19 (version-scoped; see 17.16)

[P00534 | 59040:59041 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00535 | 59041:59365 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from current Alkahest, tiger-pkg, and the connected remote Izanami branch. It adds safety/diagnostic requirements for the first individual-static proof; it does not supersede Codex/user FIELD-TESTED results or claim that a per-instance transform has moved in Destiny.

[P00536 | 59365:59366 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00537 | 59366:60175 | NORMAL_TEXT]
BAKED STATIC-AO IS A THIRD DEPENDENCY, BUT READ-ONLY FOR THE FIRST TEST. SStaticMeshInstances carries a collection-level vertex_ao_identifier, while every SStaticInstanceTransform carries vertex_ao_offset. The map/pattern component graph can separately provide SStaticAmbientOcclusionComponent 0x80806A40 -> SStaticAmbientOcclusion 0x80806D19. In Alkahest, the AO resource has three buffers with identifier->base-offset mappings; static rendering resolves the collection identifier, combines the matching base with each transform's vertex_ao_offset, and writes (vertex_ao_offset + base) >> 2. If no matching AO mapping exists, the renderer uses an all-ones fallback. This means a translated static can remain tied to baked AO authored for its stock placement even when transform and culling data are correct.

[P00538 | 60175:60176 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00539 | 60176:60878 | NORMAL_TEXT]
FIRST-TEST CONSEQUENCE. Do not alter vertex_ao_identifier, vertex_ao_offset, AO mappings, or AO buffers in the translation-only experiment. Preserving them keeps AO outside the changed-native-assumption set. A visually moved and correctly culled object with stale-looking baked lighting/AO is still a successful transform proof; record that condition separately instead of treating it as transform failure. Extend the read-only placement catalog with vertexAoIdentifier, vertexAoOffset, aoMappingPresent, aoBufferIndex, and aoBaseOffset when resolvable. StaticInstanceBinding should initially expose a lighting capability/state such as BakedAOUnchanged rather than promising lighting follows the edit.

[P00540 | 60878:60879 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00541 | 60879:61555 | NORMAL_TEXT]
SHARED OCCLUSION-TAG SAFETY. boundsRefCount == 1 only proves that one bounds record is not shared by sibling transforms inside the same collection. SOcclusionBounds itself is a separate TagHash and can, in principle, be referenced by more than one SStaticMeshInstances collection. For the first field proof, build a reverse-reference map over every reachable static collection and prefer/require occlusionBoundsTagInboundCollectionCount == 1 in addition to boundsRefCount == 1. This is an Izanami safety rule, not a recovered Destiny requirement. Later, shared bounds resources can graduate if the exact edited bounds index is proven disjoint across every inbound collection.

[P00542 | 61555:61556 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00543 | 61556:62180 | NORMAL_TEXT]
MUTABLE-RESOURCE CLOSURE FOR ONE STATIC INSTANCE. Treat the first candidate as a closure, not a single tag: mutable = {SStaticMeshInstances transform/collection AABB, referenced SOcclusionBounds mapped AABB}; read-only dependencies = {selected static mesh/model, static AO mapping/buffer metadata, outer map-node/pattern provenance}. Every mutable tag must pass source identity, pointer/range validation, package-route validation, and a source fingerprint before build. The read-only dependencies belong in the provenance/fingerprint enough to detect a stale binding but must not be rewritten in the first translation test.

[P00544 | 62180:62181 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00545 | 62181:63028 | NORMAL_TEXT]
REMOTE-BRANCH BUILDER CONSTRAINT. The connected izanami-forge branch at 830a9a58... is older than the dirty local field-test work, but it still exposes an implementation constraint worth preserving unless Codex's local source has already superseded it: custom_package_builder::mutable_entry() rejects entries that cross a 0x40000 package-block boundary and returns a span from only the starting decoded block. Sunrise's general read_tag() path, by contrast, already walks sequential block rows until the complete entry size is reconstructed. Therefore the placement catalog should emit singleBlockBuilderMutable explicitly and the first candidate should remain single-block. Do not describe a cross-block candidate as writable until the dirty local builder has a deliberate multi-block mutation path that stages and validates every covered block.

[P00546 | 63028:63029 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00547 | 63029:63663 | NORMAL_TEXT]
LONGER-TERM MULTI-BLOCK DESIGN. When needed, model an EntryBlockSpan list using the same placement semantics as read_tag(): starting block, starting offset, total size, then successive block rows until the entry is complete. Each span element should retain block index, declared PatchId, source offset, stored size, flags/codec, and bytes contributed to the logical entry. A writer should mutate a logical entry buffer, project changed byte ranges back into every affected decoded block, and stage/revalidate all affected block bodies atomically. This should be a later capability, not part of the first individual-static experiment.

[P00548 | 63663:63664 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00549 | 63664:64497 | NORMAL_TEXT]
DECLARED ROUTE VS NATIVE-OBSERVED ROUTE. Public tiger-pkg and Sunrise readers select the latest package tables and then use each block row's PatchId to choose the physical package body. The FIELD-TESTED block-164 behavior shows Destiny can disagree with that declared route. Add two separate catalog concepts: DeclaredBlockRoute (latest-table PatchId/offset/size/flags) and NativeRouteObservation (physical patch/file and offset actually observed in native verification/open diagnostics). Never infer NativeRouteObservation from generated metadata. A candidate is FieldProvenRoute only when the native-observed route, or an equivalent successful in-world mutation on that exact block route, supports it. This keeps block 19 high-priority and block 164 explicitly conflicted rather than allowing a rewritten row to make it look safe.

[P00550 | 64497:64498 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00551 | 64498:64963 | NORMAL_TEXT]
STATIC-MESH PREVIEW/PIVOT NOTE. SStaticMeshData separately carries mesh_offset and mesh_scale before per-instance placement is applied. Preserve these fields and surface them in the catalog as read-only mesh-local provenance. They may explain why a transform pivot does not coincide with the visible object's geometric center. Do not compensate for mesh_offset/mesh_scale by rewriting the instance transform until the first placement result is visually identified.

[P00552 | 64963:64964 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00553 | 64964:65565 | NORMAL_TEXT]
UNRESOLVED SECONDARY VISIBILITY CONTRACT. The same map component graph can carry SUmbraTomeComponent 0x80806CF1, and the recovered SUmbraTomes 0x80806E6B structure includes an object_bindings TagHash. Public Alkahest currently exposes the field but does not resolve its semantics into per-static editing. Do not mutate Umbra data in the first proof. If transform + mapped AABB + collection-bounds are correct yet Destiny still exhibits unexplained disappearance/visibility behavior, promote Umbra object bindings as a separate visibility investigation instead of changing more culling fields blindly.

[P00554 | 65565:65566 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00555 | 65566:66231 | NORMAL_TEXT]
UPDATED FIRST-CANDIDATE GATE. Before authoring one translation, require: coherent/field-proven routes for both mutable tags; single-block builder mutability for both; valid group/static/transform/bounds indexes; boundsRefCount == 1; preferably occlusionBoundsTagInboundCollectionCount == 1; instance_count == 1; preferably identity outer map-node transform; no known vertex-animation indicator; and AO metadata successfully inventoried but left unchanged. Then mutate only translation XYZ + mapped bounds XYZ + conservative collection-bounds expansion. Independently score geometry movement, multi-view culling, collision old/new, and baked-lighting/AO appearance.

[P00556 | 66231:66232 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00557 | 66232:67014 | NORMAL_TEXT]
2026-08-19 — SOURCE-DERIVED research update: added the static baked-AO dependency (collection vertexAoIdentifier + per-transform vertexAoOffset + separate AO mapping/buffer resource) and explicitly kept AO read-only for the first translation proof. Tightened unique-resource safety by adding occlusion-bounds-tag inbound-reference counting, separated declared package routing from native-observed routing, and documented that the connected remote builder is currently single-block-mutation-only while Sunrise's general reader already supports multi-block entries. Added a future EntryBlockSpan writer design and an Umbra object-bindings watchpoint for unexplained visibility failures. No repository files, DLLs, packages, or running Destiny process were changed by this research pa

[P00558 | 67014:67070 | HEADING_2]
17.7 Field Confirmation and Dual-Row Carrier Correction

[P00559 | 67070:67155 | NORMAL_TEXT]
UNCLAIMED PATCH 7 CARRIER FAILED; PATCH 7 AND PATCH 8 ROWS NOW AGREE; RETEST PENDING

[P00560 | 67155:67156 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00561 | 67156:67170 | NORMAL_TEXT]
Field result:

[P00562 | 67170:67290 | NORMAL_TEXT]
- The first patch-7 carrier launch reached Tower initial-slice loading but failed at t=67,594 before activity:in_world.

[P00563 | 67290:67437 | NORMAL_TEXT]
- Native verification opened w64_city_tower_d2_0369_3.pkg at the new carrier offset 249,856 while loading tag 0x80ED2B60 / entry 2912 / block 164.

[P00564 | 67437:67639 | NORMAL_TEXT]
- This is the exact discriminator predicted in Section 17.4: changing patch 8's latest row to owner 7 was insufficient because patch 7's own block-164 row still declared its inherited owner as patch 3.

[P00565 | 67639:67702 | NORMAL_TEXT]
- Destiny was closed after the unrecoverable resource failure.

[P00566 | 67702:67703 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00567 | 67703:67734 | NORMAL_TEXT]
Dual-row correction installed:

[P00568 | 67734:67944 | NORMAL_TEXT]
- Patch 7 and patch 8 now contain byte-identical block-164 rows at table offset 0x2B000. Both rows point to patch 7, body offset 249,856, stored size 125,322, flags 0x3, with the same GCM tag and stored SHA-1.

[P00569 | 67944:68088 | NORMAL_TEXT]
- The authenticated body is physically present within patch 7 and is fully in range. Patch 7 header size equals its 376,832-byte physical size.

[P00570 | 68088:68180 | NORMAL_TEXT]
- Active patch 7 SHA-256: 77F42AD7F9E7EF26FCE43E2371B0BA3C6190EDA694ED52C6E65B5084CA2A4DEB.

[P00571 | 68180:68279 | NORMAL_TEXT]
- Active patch 8 SHA-256 remains 4CFB1A893247C3057181F1E99D474761354DA0BF248A45A1E9ADB8ECB5FDB0B1.

[P00572 | 68279:68389 | NORMAL_TEXT]
- The failed unclaimed carrier is preserved as w64_city_tower_d2_0369_7.pkg.izanami-failed-unclaimed-carrier.

[P00573 | 68389:68390 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00574 | 68390:68410 | NORMAL_TEXT]
Builder correction:

[P00575 | 68410:68605 | NORMAL_TEXT]
- Carrier authoring now writes each new block record into both the latest patch-8 metadata table and patch 7's own block table after independently validating both table layouts and block counts.

[P00576 | 68605:68751 | NORMAL_TEXT]
- The patch-7 carrier file receives the aligned authenticated body and updated header size; both files remain staged separately before promotion.

[P00577 | 68751:68880 | NORMAL_TEXT]
- Release build succeeded and the deployed DLL matches SHA-256 B73D7A69FCA91B35724BE97500A5B48DFE1FB1491BB72E2C2FA838E979EC6E43.

[P00578 | 68880:68881 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00579 | 68881:69118 | NORMAL_TEXT]
Next field action: launch Destiny fresh, select Tower Carrier Control, and use Launch In Destiny without rebuilding. The decisive evidence is whether block 164 now opens from patch 7 and whether the transition reaches activity:in_world.

[P00580 | 69118:69119 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00581 | 69119:69323 | NORMAL_TEXT]
Do not claim yet: the dual-row carrier loaded, either placement mutation appeared in game, collision or culling followed the edit, general individual-static editing works, or a blank custom world exists.

[P00582 | 69323:69389 | HEADING_2]
17.8 Dual-row field result and owner-preserving package-3 carrier

[P00583 | 69389:69390 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00584 | 69390:69404 | NORMAL_TEXT]
Field result:

[P00585 | 69404:69617 | NORMAL_TEXT]
- The dual-row patch-7/patch-8 carrier still failed. The native loader opened w64_city_tower_d2_0369_3.pkg at offset 249,856 for block 164 and raised the same 0x80ED2B60 resource failure before activity:in_world.

[P00586 | 69617:69863 | NORMAL_TEXT]
- This is the fourth route observation showing that public block-row patchId changes can change the offset while the native physical owner remains package 3. Treat package 3 as pinned ownership for block 164 until contrary field evidence exists.

[P00587 | 69863:70155 | NORMAL_TEXT]
- The failed dual-row files are preserved as w64_city_tower_d2_0369_7.pkg.izanami-failed-dual-row-carrier and w64_city_tower_d2_0369_8.pkg.izanami-failed-dual-row-carrier. Patch 7 was restored to the passed LZH image, SHA-256 795A96CDC57F545C7F56ED86BD4DC1B957681F8569533BDF0A7665914083CE77.

[P00588 | 70155:70156 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00589 | 70156:70195 | NORMAL_TEXT]
Owner-preserving test image installed:

[P00590 | 70195:70413 | NORMAL_TEXT]
- Before mutation, stock package 3 was copied byte-for-byte to w64_city_tower_d2_0369_3.pkg.izanami-stock-backup-before-block164-owner-carrier, SHA-256 7440911A9090057324B9B489C6EDB6BD381569514B2B24EB7D93E095671035B2.

[P00591 | 70413:70637 | NORMAL_TEXT]
- The authenticated block-164 body is now physically appended to package 3 at aligned offset 65,085,440. Stored size is 125,322, owner patch is 3, flags are 0x3, and stored SHA-1 is F7B660EE2819F60DDBD7D73FBAFFF81B66B40FF4.

[P00592 | 70637:70837 | NORMAL_TEXT]
- Package 3 and patch 8 contain byte-identical block-164 records. Package 3 header size equals its 65,212,416-byte physical size; the body is fully in range and its computed SHA-1 matches the record.

[P00593 | 70837:71109 | NORMAL_TEXT]
- Patch 8 retains the independently validated block-19 body in patch 8 at offset 299,008. Its active SHA-256 is EC60EE2B0311A3019EA082905553062C77B60BB952956214DFFC6FCAB44F5CC8. Active package-3 SHA-256 is 5EB17677923BAADAF217F906E2D8BCE013B7433682E5F6208982496470ACDA8E.

[P00594 | 71109:71110 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00595 | 71110:71134 | NORMAL_TEXT]
Builder and deployment:

[P00596 | 71134:71381 | NORMAL_TEXT]
- custom_package_builder.cpp now routes only the field-observed pinned block 164 through package 3. Other changed blocks remain in patch 8. The updated record is written into both package 3 and patch 8, and both output headers are size-validated.

[P00597 | 71381:71520 | NORMAL_TEXT]
- Release compilation succeeded. The deployed steam_api64.dll SHA-256 is D8E97077D8493451D6265075DD497A49E01309CB4159B35BF04B10441060283C.

[P00598 | 71520:71521 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00599 | 71521:71836 | NORMAL_TEXT]
Next field action: launch Destiny without rebuilding, select Tower Carrier Control, and use Launch In Destiny. The decisive evidence is whether the transition reaches activity:in_world without a package-3 verification failure. If it fails, preserve the first package/offset/error tuple before changing any package.

[P00600 | 71836:71837 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00601 | 71837:72046 | NORMAL_TEXT]
Do not claim yet: the owner-preserving carrier loads, either placement mutation appears in game, collision or culling follows the edit, general individual-static editing works, or a blank custom world exists.

[P00602 | 72046:72089 | HEADING_2]
17.9 Owner-preserving carrier field result

[P00603 | 72089:72090 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00604 | 72090:72158 | NORMAL_TEXT]
VERIFIED: PACKAGE-3 OWNER-PRESERVING ROUTE REACHED THE NATIVE WORLD

[P00605 | 72158:72159 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00606 | 72159:72279 | NORMAL_TEXT]
- Tower Carrier Control requested the private carrier activity normally and reached activity:initial_slice_set_loading.

[P00607 | 72279:72464 | NORMAL_TEXT]
- The five-second prologue-filler timeout still appeared, but loading recovered: initial slice instantiation completed, physics_join completed, and activity:in_world began at t=80,328.

[P00608 | 72464:72616 | NORMAL_TEXT]
- No data-verification failure, 0x80ED2B60 resource assertion, package-3 offset error, freeze, or process exit occurred during the observed transition.

[P00609 | 72616:72878 | NORMAL_TEXT]
- This is the first field proof that the edited block-164 body is accepted when it remains physically owned by package 3. The previous patch-7 and patch-8 ownership claims were structurally inconsistent with the native loader even when their public rows agreed.

[P00610 | 72878:72879 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00611 | 72879:73190 | NORMAL_TEXT]
Current interpretation: for this Tower resource, the latest public block row supplies the new offset and authentication data, but the native physical-owner decision remains pinned to package 3. The durable builder must therefore preserve owner 3 for block 164 unless a later route fingerprint proves otherwise.

[P00612 | 73190:73191 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00613 | 73191:73367 | NORMAL_TEXT]
Visual result is pending user observation. Do not yet claim that the moved geometry remains visible, collision follows the transform, or the route generalizes to other blocks.

[P00614 | 73367:73368 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00615 | 73368:73388 | NORMAL_TEXT]
Visual observation:

[P00616 | 73388:73627 | NORMAL_TEXT]
- The user confirmed that the previously displaced large Tower area is no longer displaced. This matches the intentional aggregate-restore edit for table 0x80ED22FB, entry 0: its authored translation returned from (64, 0, 0) to (0, 0, 0).

[P00617 | 73627:73874 | NORMAL_TEXT]
- Do not classify this as a lost mutation. The remaining visual target is the separate small placement at table 0x80ED2B6F, entry 0, parent 0x80ED2B6E, authored from (0, 0, 0) to (64, 0, 0). Its identity, culling, and collision remain unverified.

[P00618 | 73874:73914 | HEADING_2]
17.10 Observable block-164 probe staged

[P00619 | 73914:73915 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00620 | 73915:73936 | NORMAL_TEXT]
Prior visual result:

[P00621 | 73936:74173 | NORMAL_TEXT]
- The user confirmed the intentionally restored large aggregate is back in its stock position and reported no other obvious displacement. This validates aggregate restoration but does not visually identify the small block-164 placement.

[P00622 | 74173:74174 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00623 | 74174:74198 | NORMAL_TEXT]
Observable probe build:

[P00624 | 74198:74354 | NORMAL_TEXT]
- The same placement was retained to avoid changing the route under test: table 0x80ED2B6F, entry 0, parent 0x80ED2B6E, entity 0x80C70CC0, data 0x80ED2B6D.

[P00625 | 74354:74517 | NORMAL_TEXT]
- Its authored transform changed from position (64, 0, 0), scale 1 to position (128, 0, 0), scale 6. The Forge hierarchy now labels it Tower Probe [0x80ED2B6F:0].

[P00626 | 74517:74591 | NORMAL_TEXT]
- The aggregate table 0x80ED22FB remained at position (0, 0, 0), scale 1.

[P00627 | 74591:74592 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00628 | 74592:74626 | NORMAL_TEXT]
Package validation and promotion:

[P00629 | 74626:74783 | NORMAL_TEXT]
- The runtime builder produced a package-3 owner stage of 65,339,392 bytes and patch-8 stage of 524,288 bytes. Both header sizes match their physical files.

[P00630 | 74783:75020 | NORMAL_TEXT]
- Package 3 and patch 8 contain byte-identical block-164 rows: owner 3, offset 65,212,416, stored size 125,326, flags 0x3, stored SHA-1 87BF56AFCD122FB08C809D0CF41EF7BFEEEDB005. The body is fully in range and its computed SHA-1 matches.

[P00631 | 75020:75106 | NORMAL_TEXT]
- Block 19 remains owned by patch 8 at offset 475,136, stored size 47,935, flags 0x3.

[P00632 | 75106:75324 | NORMAL_TEXT]
- The previously successful owner-preserving image was archived as w64_city_tower_d2_0369_3.pkg.izanami-passed-owner-preserving-world-entry and w64_city_tower_d2_0369_8.pkg.izanami-passed-owner-preserving-world-entry.

[P00633 | 75324:75549 | NORMAL_TEXT]
- Destiny was closed before promotion. Active package-3 SHA-256 is 61282BC7D1B7ADCD96B88C173FF8B7667DE00328088953786623FB6C9E591701; active patch-8 SHA-256 is 873F9E1CBF4BB47359964A167F4F487C0BDE4AE19FA22D24752C655E22D2D491.

[P00634 | 75549:75550 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00635 | 75550:75782 | NORMAL_TEXT]
Next field action: launch Destiny without rebuilding, use Tower Carrier Control, and inspect for an unmistakably enlarged/displaced placement. Record world entry separately from visual identification and collision/culling behavior.

[P00636 | 75782:75826 | HEADING_2]
17.11 Skybox placement field identification

[P00637 | 75826:75827 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00638 | 75827:75891 | NORMAL_TEXT]
VERIFIED: THE SELECTIVE BLOCK-164 PLACEMENT IS THE TOWER SKYBOX

[P00639 | 75891:75892 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00640 | 75892:76157 | NORMAL_TEXT]
- The user visually confirmed that the authored 6x scale and translation affected the skybox. The supplied screenshot shows the environment enlarged and offset, including displaced celestial/debris features, while foreground Tower geometry remains normally placed.

[P00641 | 76157:76301 | NORMAL_TEXT]
- Native identity: table 0x80ED2B6F, entry 0, parent 0x80ED2B6E, entity 0x80C70CC0, data 0x80ED2B6D. The table and data both live in block 164.

[P00642 | 76301:76443 | NORMAL_TEXT]
- Public entry metadata identifies table class 0x808099D6, parent class 0x80806EF4, and data class 0x8080966D. The data payload is 656 bytes.

[P00643 | 76443:76630 | NORMAL_TEXT]
- Destiny accepted translation from X=64 to X=128 and uniform scale from 1 to 6 through the owner-preserving package-3 route, then reached activity:in_world without verification failure.

[P00644 | 76630:76631 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00645 | 76631:76649 | NORMAL_TEXT]
What this proves:

[P00646 | 76649:76767 | NORMAL_TEXT]
- Forge-authored translation and uniform scale both affect an independently addressable native map placement in game.

[P00647 | 76767:77031 | NORMAL_TEXT]
- The Tower skybox can be retained and normalized independently from the large foreground scenery aggregate. This is directly useful for the blank-world plan: preserve one skybox at its source transform while selectively removing or relocating scenery placements.

[P00648 | 77031:77212 | NORMAL_TEXT]
- Payload size and shared class IDs do not distinguish sky/environment from ordinary geometry; candidate naming must be grounded in field observation or deeper dependency analysis.

[P00649 | 77212:77213 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00650 | 77213:77553 | NORMAL_TEXT]
Next implementation rule: restore this skybox to its source position and scale before the next package. Replace the hard-coded single-owner exception with per-block owner preservation so additional scenery candidates can be transformed without repeating patch-slot failures. Collision is not an applicable signal for this skybox placement.

[P00651 | 77553:77610 | HEADING_2]
17.12 Generalized owner routing and next map-layer probe

[P00652 | 77610:77611 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00653 | 77611:77627 | NORMAL_TEXT]
Implementation:

[P00654 | 77627:78009 | NORMAL_TEXT]
- The Tower builder no longer hard-codes block 164 or package 3. For every changed block, it now reads the current block-row patchId as the physical owner, loads each distinct non-latest owner file once, appends the authenticated body to that owner, mirrors the updated row into both owner and latest tables, updates every header size, and writes one owner stage per changed owner.

[P00655 | 78009:78211 | NORMAL_TEXT]
- This is required for continued map decomposition: the cataloged candidate blocks currently span physical owners 3, 4, and 5, while the field-proven aggregate block 19 remains owned by latest patch 8.

[P00656 | 78211:78212 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00657 | 78212:78232 | NORMAL_TEXT]
Workspace contract:

[P00658 | 78232:78315 | NORMAL_TEXT]
- Tower Aggregate Restore remains table 0x80ED22FB at position (0, 0, 0), scale 1.

[P00659 | 78315:78421 | NORMAL_TEXT]
- Tower Skybox Restore is now explicit: table 0x80ED2B6F is authored back to position (0, 0, 0), scale 1.

[P00660 | 78421:78711 | NORMAL_TEXT]
- The next probe excludes both field-identified layers and selects table 0x80ED25D9, entry 0, parent 0x80ED25D7, entity 0x80C70CC0, data 0x80ED25D6. Its table and 1,472-byte data payload live in block 126, whose installed owner is package 3. The intended probe is +64 X at 6x source scale.

[P00661 | 78711:78712 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00662 | 78712:78736 | NORMAL_TEXT]
Build and preservation:

[P00663 | 78736:78878 | NORMAL_TEXT]
- Release compilation succeeded and the deployed steam_api64.dll SHA-256 is 035CBEAEA1D6C3813465A2945E46E965A5CFC77C3D2B55C4B427A515F10E0486.

[P00664 | 78878:79069 | NORMAL_TEXT]
- The field-proven enlarged/offset skybox image was archived as w64_city_tower_d2_0369_3.pkg.izanami-passed-skybox-transform and w64_city_tower_d2_0369_8.pkg.izanami-passed-skybox-transform.

[P00665 | 79069:79175 | NORMAL_TEXT]
- Destiny was closed before DLL deployment. No next-candidate package has been generated or promoted yet.

[P00666 | 79175:79176 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00667 | 79176:79421 | NORMAL_TEXT]
Next action: launch without rebuilding, open Blank Baseplate, and run Build Tower Baseplate Patch exactly once. Do not launch Tower Carrier Control until all generated owner stages and the latest stage have been validated and promoted together.

[P00668 | 79421:79453 | HEADING_2]
17.13 Blank-world carrier draft

[P00669 | 79453:79469 | NORMAL_TEXT]
Implementation:

[P00670 | 79469:79685 | NORMAL_TEXT]
- The Blank Baseplate build no longer creates a single visual probe. It now catalogs every Tower static-map placement reachable from map:city_tower_d2:root and binds each placement as an explicit Forge scene object.

[P00671 | 79685:79803 | NORMAL_TEXT]
- The field-identified Tower skybox (table 0x80ED2B6F, parent 0x80ED2B6E) is restored to position (0, 0, 0), scale 1.

[P00672 | 79803:80098 | NORMAL_TEXT]
- The proven large Tower aggregate (table 0x80ED22FB, parent 0x80ED22FA) is source-validated and then redirected to the six-instance VFX test baseplate parent 0x8150E15A. The original VFX table uses the same entity tag, 0x80C70CC0, and the same static-map resource class as the Tower aggregate.

[P00673 | 80098:80308 | NORMAL_TEXT]
- Every other discovered Tower static-map placement is translated by the quarantine vector (32768, -32768, 8192), keeping those layers outside ordinary scenery range while retaining reversible source bindings.

[P00674 | 80308:80328 | NORMAL_TEXT]
Builder guardrails:

[P00675 | 80328:80614 | NORMAL_TEXT]
- Resource substitution is allowlisted only for the known Tower aggregate and the known baseplate parent. The builder verifies the original table, entry, parent, and transform before writing, then resolves the replacement parent as class 0x80806EF4 and its payload as class 0x8080966D.

[P00676 | 80614:80816 | NORMAL_TEXT]
- The generalized physical-owner router remains in use, so changed table blocks spanning owners 3, 4, 5, and latest patch 8 are staged back into their native owner files rather than falsely reassigned.

[P00677 | 80816:81127 | NORMAL_TEXT]
- QuickTag identifies the installed Shadowkeep-era payload classes as s_static_mesh_instances (0x8080966D) and s_static_instance_transform (0x808071A3). Alkahest's current static-geometry definitions corroborate the underlying static-instance transform and group model, although class IDs vary by game version.

[P00678 | 81127:81140 | NORMAL_TEXT]
Build state:

[P00679 | 81140:81311 | NORMAL_TEXT]
- Release compilation succeeded. Destiny was closed before deployment. Deployed steam_api64.dll SHA-256: BB76E3A490BD671B53C626097C7463D2EEA3751E9342A5C8D4408261D0E18738.

[P00680 | 81311:81453 | NORMAL_TEXT]
- No blank-world package has been generated, validated, promoted, or loaded yet. The implementation is ready for its first runtime staging pa

[P00681 | 81453:81497 | NORMAL_TEXT]
Known limitations for the first field test:

[P00682 | 81497:81717 | NORMAL_TEXT]
- This pass removes or replaces discovered static-map placements only. Terrain, physics/collision resources, decals, lights, activity scripting, gameplay volumes, and spawn placement are not yet classified or rewritten.

[P00683 | 81717:82078 | NORMAL_TEXT]
- Cross-package loading of the baseplate parent from package 0x0687, the baseplate's alignment with the Tower spawn, and whether usable collision appears under the player are all unverified. A freeze or orbit return would most strongly implicate dependency residency; a successful load with missing or offset geometry would implicate transform/spawn alignment.

[P00684 | 82078:82091 | NORMAL_TEXT]
Next action:

[P00685 | 82091:82358 | NORMAL_TEXT]
- Launch Destiny without rebuilding, open Blank Baseplate, and run Build Blank World Draft exactly once. Close Destiny after staging so every newly written owner stage and patch-8 stage can be validated and promoted together before Tower Carrier Control is launched.

[P00686 | 82358:82359 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00687 | 82359:82360 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00688 | 82360:82435 | NORMAL_TEXT]
17.14 Source-Derived Cross-Package Baseplate Routing Contract — 2026-08-19

[P00689 | 82435:82436 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00690 | 82436:82802 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from current tiger-pkg/QuickTag package and traversal code and is reconciled against the FIELD-TESTED owner-routing results in Sections 17.8-17.11. It does not claim that the 0x0687 VFX baseplate parent is resident or loadable inside the Tower activity; Section 17.13's blank-world draft remains TEST PENDING.

[P00691 | 82802:82803 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00692 | 82803:83360 | NORMAL_TEXT]
EXACT CROSS-PACKAGE IDENTITY. Tiger's 32-bit TagHash encoding is 0x80800000 + (packageId << 13) + entryIndex. Under that recovered encoding, the replacement baseplate parent 0x8150E15A decodes to package 0x0687, entry 346. The Tower aggregate source parent 0x80ED22FA decodes to package 0x0369, entry 762, while its table 0x80ED22FB is package 0x0369, entry 763. Therefore the current blank-world substitution is not an intra-Tower alias: it intentionally changes the static-map parent from the Tower package family to a different installed package family.

[P00693 | 83360:83361 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00694 | 83361:84083 | NORMAL_TEXT]
STRUCTURAL VALIDITY VS NATIVE RESIDENCY. Public tiger-pkg models TagHash package identity as first-class: PackageManager::read_tag() selects the package by tag.pkg_id() and then reads tag.entry_index(); get_entry() performs the same package/entry split. QuickTag's recursive tag traversal likewise passes referenced TagHashes through the global PackageManager rather than requiring referenced tags to remain in the starting package. This is strong source evidence that cross-package TagHash references are structurally representable in Tiger data/tooling. It is NOT proof that Destiny's native Tower world loader will register or keep package 0x0687 and every required dependency resident during this activity transition.

[P00695 | 84083:84084 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00696 | 84084:84794 | NORMAL_TEXT]
TWO-AXIS ROUTING MODEL. The block-164 field work proves that two different ownership concepts must remain separate in Izanami bindings and diagnostics. Axis A is Resource/Tag Route: {tagHash, packageFamilyId, entryIndex, entryClass/reference}. Axis B is Physical Block Route: {packageFamilyId, blockIndex, physicalOwnerPatchId, offset, storedSize, flags, codec/authentication fingerprint}. The skybox example is package family 0x0369 with a block physically pinned to patch 3. The new baseplate parent introduces an independent package-family transition to 0x0687. Never use the word owner for both without qualification. PackagePlacementBinding should fingerprint both axes and fail closed if either changes.

[P00697 | 84794:84795 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00698 | 84795:85255 | NORMAL_TEXT]
REPLACEMENT-PARENT VALIDATION CORRECTION. Class equality alone is necessary but insufficient for a cross-package substitution. Continue validating the expected replacement parent/payload classes, but also bind the exact replacement TagHash 0x8150E15A, decoded package 0x0687 / entry 346, its entry metadata, and a dependency-closure fingerprint. A different same-class static-map parent must not silently satisfy the binding after an installed-package update.

[P00699 | 85255:85256 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00700 | 85256:86114 | NORMAL_TEXT]
READ-ONLY CrossPackageDependencyClosure PREFLIGHT. Before treating a blank-world failure as another package-body routing problem, add or reuse a non-mutating dependency walk rooted at 0x8150E15A. Use a visited set and bounded depth, follow only validated outgoing TagHash references, and emit for each reachable tag: tagHash, packageId, entryIndex, entry reference/class when known, source offset/reference provenance, and package/block route provenance when available. Partition the result by package family and record at minimum rootPackage=0x0687, totalTags, packageCount, foreignPackageCount, unresolvedTagCount, and a stable normalized closure fingerprint. Run the same diagnostic on source Tower parent 0x80ED22FA so the build log can compare the known-resident source closure against the replacement closure without copying or rewriting either graph.

[P00701 | 86114:86115 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00702 | 86115:86607 | NORMAL_TEXT]
DO NOT CLONE THE 0x0687 GRAPH YET. TagHash identity itself encodes package family plus entry index, and public package readers resolve it through that identity. Relocating the baseplate parent into package 0x0369 would therefore be a substantially larger experiment: every transitive internal TagHash that must move would need a newly allocated Tower entry identity and all inbound/internal references would need coherent remapping. Do not combine that with the first blank-world field test.

[P00703 | 86607:86608 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00704 | 86608:87414 | NORMAL_TEXT]
FIELD INTERPRETATION FOR THE 17.13 DRAFT. If the Tower transition reaches activity:in_world with the replacement visible, record cross-package static-map-parent use from 0x0687 as FIELD-PROVEN and keep the closure diagnostic as provenance. If loading fails and the first resource/package tuple names 0x8150E15A, package 0x0687, or one of the closure's foreign dependencies, classify the next problem as CrossPackageResidency/DependencyClosure before changing compression, block owner routing, or the already-proven Tower carrier. Preserve the exact first tag/package/offset/error tuple. If failure occurs before the replacement root or any dependency is requested, investigate the source Tower mutation/quarantine set instead; do not infer a 0x0687 residency failure without a matching native observation.

[P00705 | 87414:87415 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00706 | 87415:87931 | NORMAL_TEXT]
SAFER FALLBACK ORDER IF CROSS-PACKAGE RESIDENCY FAILS. First search the placement catalog/dependency graph for a simple baseplate-like s_static_mesh_instances resource already reachable from the Tower-resident package closure and test that as an intra-resident replacement. Only if no suitable resident resource exists should Izanami investigate narrowly making the 0x0687 dependency closure resident/registered for the Tower activity. Full dependency cloning/remapping into Tower remains the highest-risk fallback.

[P00707 | 87931:87932 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00708 | 87932:88401 | NORMAL_TEXT]
IMPLEMENTATION NOTE ON ENTRY METADATA. tiger-pkg's unified UEntryHeader keeps reference as a raw u32 alongside type/subtype and block location metadata; do not assume every UEntryHeader.reference value is itself a TagHash merely because some package structures contain TagHash references. Dependency closure should be driven by validated outgoing TagHash scans/schema-known fields, not by blindly interpreting every 32-bit reference/class value as a resource identity.

[P00709 | 88401:88402 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00710 | 88402:89311 | NORMAL_TEXT]
2026-08-19 — SOURCE-DERIVED research update: decoded the VFX replacement parent 0x8150E15A as package 0x0687 / entry 346 and the Tower aggregate parent 0x80ED22FA as package 0x0369 / entry 762, proving that the current blank-world draft is deliberately exercising a cross-package-family static-map substitution. Public Tiger tooling treats packageId+entryIndex as first-class TagHash identity and can resolve cross-package references on demand, but native Tower residency remains unproven. Added a two-axis routing contract separating Resource/Tag Route from Physical Block Route, exact replacement-parent fingerprinting, a read-only CrossPackageDependencyClosure preflight, and a failure decision tree that prevents a 0x0687 residency error from being misdiagnosed as another codec/patch-owner regression. No repository files, DLLs, package files, or running Destiny process were changed by this research pa

[P00711 | 89311:89362 | HEADING_2]
17.15 Blank-world package validation and promotion

[P00712 | 89362:89386 | NORMAL_TEXT]
Runtime staging result:

[P00713 | 89386:89545 | NORMAL_TEXT]
- Build Blank World Draft completed successfully. The live package walk found 13 Tower static placements and the builder logged 13 source-validated mutations.

[P00714 | 89545:89865 | NORMAL_TEXT]
- Table 0x80ED22FB changed from source parent 0x80ED22FA to replacement parent 0x8150E15A at identity transform. Table 0x80ED2B6F restored the skybox from position (128, 0, 0), scale 6 to position (0, 0, 0), scale 1. The remaining 11 static placements moved to (32768, -32768, 8192) relative to their source transforms.

[P00715 | 89865:89892 | NORMAL_TEXT]
Physical-owner validation:

[P00716 | 89892:90151 | NORMAL_TEXT]
- Thirteen changed blocks were encoded with their original Oodle codec and authenticated. Owner 3 carries blocks 126, 130, 155, 164, 236, and 274; owner 4 carries block 286; owner 5 carries blocks 394, 411, 428, 439, and 583; latest patch 8 carries block 19.

[P00717 | 90151:90332 | NORMAL_TEXT]
- Package headers for stages 3, 4, 5, and 8 report version 38, package 0x0369, their correct patch IDs, in-range tables, and file-size fields exactly equal to physical file length.

[P00718 | 90332:90554 | NORMAL_TEXT]
- For every changed block, the latest patch-8 row is byte-identical to the physical owner's row, offset plus stored size remains inside the owner file, and SHA-1 of the stored body exactly matches the row's opaque digest.

[P00719 | 90554:90565 | NORMAL_TEXT]
Promotion:

[P00720 | 90565:90722 | NORMAL_TEXT]
- Destiny was closed before installation. The previous active packages 3, 4, 5, and 8 were copied to matching .izanami-pre-blank-world-draft rollback files.

[P00721 | 90722:90870 | NORMAL_TEXT]
- Only the newly validated owner stages 3, 4, and 5 plus patch-8 stage were promoted. Older patch-7 and patch-9 research stages were not installed.

[P00722 | 90870:91205 | NORMAL_TEXT]
- Active SHA-256 values: package 3 = 7445A1BE850B411B85CA1A81907423A762C8881794911E0CC460503E6DAF8B09; package 4 = 4CEADF9B52A099D28EC96474EBE9FBD81B7DC4097B9ED767ED108E033CAAD854; package 5 = 4349925B7533244C33AA409760F270826600425F02A90B5685D035F4DEEEC1AE; patch 8 = 5F14C4891010A30446BA905A1ED14F0361A4BEDEC75EEEA2E6F1AC8F078FEC4E.

[P00723 | 91205:91219 | NORMAL_TEXT]
Field status:

[P00724 | 91219:91471 | NORMAL_TEXT]
- The package set is structurally validated and installed but has not yet been loaded by Destiny. Cross-package residency, visible baseplate placement, spawn alignment, collision, and the completeness of static-layer removal remain field-test pending.

[P00725 | 91471:91484 | NORMAL_TEXT]
Next action:

[P00726 | 91484:91819 | NORMAL_TEXT]
- Launch Destiny without rebuilding or running Build Blank World Draft again. From orbit, use Tower Carrier Control once. Record whether the transition reaches activity:in_world, freezes, returns to orbit, or exits, then inspect whether the baseplate, normalized skybox, and quarantined scenery produce the intended blank composition.

[P00727 | 91819:91820 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00728 | 91820:91905 | NORMAL_TEXT]
17.16 Source-Derived Shadowkeep-Specific Per-Instance Layout Correction — 2026-08-19

[P00729 | 91905:91906 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00730 | 91906:92300 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from the current public Charm and QuickTag repositories and corrects a version-mismatch in Sections 16, 17.5, and 17.6. It does not supersede any Codex/user FIELD-TESTED result. The currently installed blank-world package set in Section 17.15 remains field-test pending and should not be rebuilt merely because of this parser correction.

[P00731 | 92300:92301 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00732 | 92301:93034 | NORMAL_TEXT]
MAJOR VERSION-LOCK CORRECTION. The field-tested Tower static-map payload class is 0x8080966D. QuickTag's Destiny 2 Shadowkeep class table identifies 0x8080966D as s_static_mesh_instances, 0x808071A3 as s_static_instance_transform, 0x80807190 as s_static_mesh_instance_group, and 0x808071A7 as s_static_mesh. Charm independently gives its DESTINY2_SHADOWKEEP_2601 schema for the same 0x8080966D payload as SStaticMapData with serialized size 0xA0. Therefore the byte-level parser for Izanami's current Tower files must be Shadowkeep-specific. The newer Alkahest 0x808093AD / 0x80806D40 layout remains useful conceptual evidence for later game versions but must not be applied byte-for-byte to this installed Shadowkeep package chain.

[P00733 | 93034:93035 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00734 | 93035:93877 | NORMAL_TEXT]
SHADOWKEEP STATIC-MAP LAYOUT. Charm's versioned schema places the instance-transform DynamicArray at +0x40 and the static-mesh-reference DynamicArray at +0x58, followed by the instance-count/group mapping used by Charm to pair meshes with contiguous transform ranges. Charm's exporter resolves each group as Statics[c.StaticIndex].Static and Instances.Skip(c.InstanceOffset).Take(c.InstanceCount). The group schema is 0x80807190 / 0x8 bytes and contains InstanceCount, InstanceOffset, StaticIndex, and one unknown u16. This gives Izanami a direct read-only candidate path without first relying on the newer Alkahest component layout: validate a 0x8080966D data tag, enumerate group records, validate InstanceOffset + InstanceCount against the instance array, validate StaticIndex against the static array, then rank InstanceCount == 1 first.

[P00735 | 93877:93878 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00736 | 93878:94666 | NORMAL_TEXT]
SHADOWKEEP TRANSFORM CONTRACT. Charm's DESTINY2_SHADOWKEEP_2601 SStaticMeshInstanceTransform is class 0x808071A3 and serialized size 0x30. It contains a Vector4 rotation, Vector3 position, and Vector3 scale; Charm comments that only scale X is used as the global scale. This differs materially from the newer 0x80806D40 / 0x40 transform used in prior source-derived notes, which contains a scalar scale plus AO/unknown tail fields. For the first Shadowkeep individual-object proof, preserve all 0x30 source bytes except Position XYZ. Preserve the rotation, every scale component, padding/unknown bytes, array sizes, group records, and static references. Rotation and scale remain separate later experiments even though outer-placement uniform scale is already FIELD-PROVEN on the skybox.

[P00737 | 94666:94667 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00738 | 94667:95793 | NORMAL_TEXT]
CULLING RESOURCE LINK — HIGH-CONFIDENCE, NOT YET RAW-BYTE-ATTESTED FOR TOWER. Charm's SStaticMapData declares ModelOcclusionBounds at +0x18 only with a DESTINY1_RISE_OF_IRON SchemaField annotation. Charm's SchemaDeserializer has a generic fallback that returns a lone SchemaField attribute for every strategy, so Charm will interpret that D1-annotated field at +0x18 in Shadowkeep too; this is tool behavior, not an independent Shadowkeep-specific field annotation. When interpreted that way it resolves to Shadowkeep SOcclusionBounds 0x80809671, whose payload contains a DynamicArray of SMeshInstanceOcclusionBounds 0x80809673. The FIELD-INSPECTED VFX chain in Section 17.17 independently found a 0x80809671 bounds dependency, which makes +0x18 a strong candidate but still leaves the Tower byte offset to attest directly. Before any culling write, raw-read payload 0x80ED22F9 at +0x18, require the value to resolve to a valid tag whose entry class is 0x80809671, and fingerprint that exact relation. PER-TRANSFORM BOUNDS INDEXING remains unresolved; do not import the later Post-BL +0x20 transform_to_bounds_index contract.

[P00739 | 95793:95794 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00740 | 95794:97199 | NORMAL_TEXT]
SHADOWKEEP CULLING INDEXING GATE. The bounds class no longer needs rediscovery, but the Tower-specific +0x18 resource link still requires raw-byte attestation before use. SOURCE-DERIVED CORRECTION: do not parse Charm's field currently named Unk50 as a Shadowkeep u32 mapping vector. Charm defines DynamicArray<T> as a 0x10-byte serialized header; with Instances fixed at +0x40, a sequential Unk50 DynamicArray would occupy +0x50..+0x5F, but Shadowkeep Statics is explicitly fixed at +0x58. Those declarations overlap, so the Unk50 type/offset is not internally coherent for this layout and cannot be used as a write contract. Before a first individual transform+AABB mutation, record Instances.Count, SOcclusionBounds.InstanceBounds.Count, group range, selected transform index, and raw bytes from the unmodeled +0x20..+0x3F and +0x50..+0x57 header regions. If InstanceBounds.Count == Instances.Count, evaluate direct transformIndex -> boundsIndex first. Any alternative map must be recovered from raw bytes and pass non-overlap, count/pointer/range, and geometric-coherence validation before use. The two Vector4 fields at +0x80/+0x90 are now high-confidence collection-AABB candidates by exact later-version tail-layout parity, but remain non-writable until the RawTailAabbAttestation in Section 17.26 passes on installed Tower bytes. If no mapping is proven, keep per-instance culling writes disabled.

[P00741 | 97199:97200 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00742 | 97200:97932 | NORMAL_TEXT]
VERSIONED BINDING DESIGN. Add a layout discriminator to PackagePlacementBinding / StaticInstanceBinding instead of assuming one universal Tiger static layout. A Shadowkeep binding should retain at minimum: layoutId = D2Shadowkeep_StaticMapData_0x8080966D_v0xA0; dataTag; outer map/table/node provenance; group index; source InstanceCount/InstanceOffset/StaticIndex; resolved transform index; resolved static mesh tag; the complete source 0x30 transform bytes; source resource/block-route fingerprints; and any culling relationship only after that relationship has its own validated fingerprint. Resolution fails closed on class, serialized-layout, array range, static index, source transform, route, or culling-provenance mismatch.

[P00743 | 97932:97933 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00744 | 97933:98874 | NORMAL_TEXT]
DYNAMIC-ARRAY / TIGER-VECTOR PARSER REQUIREMENT — EVIDENCE CORRECTION. The 64-bit Tiger vector header is 0x10 bytes, but pre-BL-era tiger-parse used u64 Size/Offset; signed i64 Size/Offset were introduced in May 2025 to support backwards seeking. For a header beginning at H, the parser reads count at H, reads the relative offset at H+8, resolves envelope = (H+8)+offset, verifies the duplicated count at the envelope, and reads elements from envelope+0x10. If count is zero, it returns empty without following the target. Izanami should fingerprint the raw header/layout version, use checked count*elementSize and pointer arithmetic, require envelope/data containment in the reconstructed logical entry, validate the duplicate count and known element-type marker when applicable, and fail closed on absurd counts or malformed ranges. Signed-negative rejection is a current-parser safety rule, not a historical Shadowkeep on-disk semantic.

[P00745 | 98874:98875 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00746 | 98875:100108 | NORMAL_TEXT]
DEPENDENCY-CLOSURE CONFIDENCE CORRECTION. QuickTag's scanner is extremely useful, but its ordinary file-hash graph is partly heuristic: outside ranges deliberately marked block_tags, it scans each 4-byte-aligned value and records it as a file hash when it is a syntactically valid package-file TagHash present in the package manager's valid-file set. It retains the exact byte offset for every hit. Therefore CrossPackageDependencyClosure must distinguish at least three edge classes: SchemaKnownEdge (a typed/recovered TagHash field), HeuristicValidHashEdge (QuickTag-style validated aligned scan hit with source byte offset), and RuntimeObservedEdge (Destiny actually requested/opened the referenced resource). HeuristicValidHashEdge is discovery evidence only. For schema-known numeric/metadata array ranges such as Shadowkeep transforms, groups, and occlusion-bound records, Section 17.45 now requires a SchemaAwareReferenceMask that suppresses aligned hash hits inside those ranges entirely; outside masked ranges, heuristic hits still must not by themselves make a foreign package 'required', trigger dependency cloning/remapping, or fail a build. Residency decisions should prioritize schema-known and runtime-observed edges.

[P00747 | 100108:100109 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00748 | 100109:100825 | NORMAL_TEXT]
REVISED NEXT IMPLEMENTATION AFTER THE CURRENT BLANK-WORLD FIELD TEST. Do not rewrite the already installed Section 17.15 package set. After that field result is captured, the next individual-static implementation should first add a read-only Shadowkeep placement parser for 0x8080966D / 0x808071A3 / 0x80807190 and emit candidate rows with package/block-owner provenance. Rank one-group/one-instance candidates on FIELD-PROVEN routes. Separately recover their Shadowkeep culling relationship. Only then create one writable StaticInstanceBinding and change Position XYZ alone. This keeps the experiment to one native placement assumption and prevents a Post-BL culling schema from contaminating the Shadowkeep proof.

[P00749 | 100825:100826 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00750 | 100826:101204 | NORMAL_TEXT]
Sources: MontagueM/Charm StaticMapData.cs and SchemaTypes.cs at commit 50d36ee1f9ecadad7522504c20b1f3f9c97e30af; v4nguard/quicktag classes.rs and scanner/src/lib.rs at commit bdad2e92442439bb0f71c67aca608b7ca0a8c74c; cohaereo/alkahest statics.rs at commit b140945588717ce75218ff48e15674a6655431d7, used only to identify the later-version layout that must now be version-scoped.

[P00751 | 101204:101205 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00752 | 101205:102161 | NORMAL_TEXT]
2026-08-19 — SOURCE-DERIVED research update: found and corrected a critical game-version mismatch in the individual-static plan. The current Tower payload 0x8080966D is explicitly the Shadowkeep static-instances layout in QuickTag/Charm, while the prior 0x808093AD + 0x80806D40 transform/bounds contract is a newer Post-BL/WQ layout. The Shadowkeep transform is 0x808071A3 / 0x30 with Vector4 rotation, Vector3 position, and Vector3 scale, and Charm maps group InstanceOffset/InstanceCount/StaticIndex directly into its instance/static arrays. Demoted the newer +0x18 occlusion-tag/+0x20 transform-to-bounds mapping from the current-build contract, added a Shadowkeep culling-recovery prerequisite, versioned binding/layout fingerprints, and confidence-typed dependency edges so QuickTag heuristic hash hits cannot be mistaken for mandatory native residency. No repository files, DLLs, packages, or running Destiny process were changed by this research pa

[P00753 | 102161:102162 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00754 | 102162:102228 | HEADING_2]
17.17 Blank-world field result and baseplate alignment correction

[P00755 | 102228:102242 | NORMAL_TEXT]
Field result:

[P00756 | 102242:102446 | NORMAL_TEXT]
- Tower Carrier Control completed the native transition into city_tower_social_d2. The client reached activity:in_world at t=162594 after successful world change, initial-slice loading, and physics_join.

[P00757 | 102446:102688 | NORMAL_TEXT]
- No package verification failure, cross-package residency assertion, freeze, orbit return, or process exit occurred. This field-proves that replacement parent 0x8150E15A from package 0x0687 is loadable through the Tower carrier package set.

[P00758 | 102688:102910 | NORMAL_TEXT]
- The user observed that most large Tower architecture was gone. A few objects and effects remained, the Tower skybox remained, and the Guardian could still collide with invisible Tower geometry. No baseplate was visible.

[P00759 | 102910:102926 | NORMAL_TEXT]
Interpretation:

[P00760 | 102926:103102 | NORMAL_TEXT]
- The 13 static-placement edits affected live Destiny geometry as intended. The surviving objects are owned by map-resource layers outside the cataloged static-map placements.

[P00761 | 103102:103269 | NORMAL_TEXT]
- Tower collision is independently authored from the quarantined render placements. Moving static render tables does not remove the corresponding Havok/physics world.

[P00762 | 103269:103414 | NORMAL_TEXT]
- Cross-package loadability is now field-proven, but the original identity-transform graft was spatially invalid rather than dependency-invalid.

[P00763 | 103414:103434 | NORMAL_TEXT]
Package inspection:

[P00764 | 103434:103727 | NORMAL_TEXT]
- The replacement chain is parent 0x8150E15A (class 0x80806EF4) to payload 0x8150E159 (class 0x8080966D), with schema-known references to bounds 0x8150E158 (class 0x80809671) and static mesh 0x815B82EB (class 0x808071A7). Every immediate dependency is readable from the installed package set.

[P00765 | 103727:103956 | NORMAL_TEXT]
- The Shadowkeep payload contains six 0x30-byte instance transforms. Their positions span X=-5092.993..2454.747, Y=-2274.877..2253.844, and Z=444.586..615.889. The nearest instance remains more than 2200 world units from origin.

[P00766 | 103956:104238 | NORMAL_TEXT]
- By comparison, the Tower aggregate payload contains 1057 transforms spanning approximately X=-116.8..0, Y=0..89.4, and Z=0..30. Tower content is authored around world origin. This explains why the cross-package group loaded without producing a visible platform near the Guardian.

[P00767 | 104238:104265 | NORMAL_TEXT]
Implementation correction:

[P00768 | 104265:104544 | NORMAL_TEXT]
- The blank-world composition now applies outer translation (-2454.747, 2274.877, -444.586) to the replacement placement. This cancels the first VFX platform instance center and places that platform at Tower world origin while preserving its package-authored rotation and scale.

[P00769 | 104544:104708 | NORMAL_TEXT]
- This source change has not yet been rebuilt, staged, validated, or promoted. The currently running field-test package remains the prior identity-transform image.

[P00770 | 104708:104972 | NORMAL_TEXT]
- The next package pass should test visible platform alignment first. Invisible collision removal remains a separate resource-classification task and must target the Tower physics/Havok layer rather than inferring collision from static render placement ownership.

[P00771 | 104972:104973 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00772 | 104973:105017 | HEADING_2]
17.18 Aligned blank-world build preparation

[P00773 | 105017:105039 | NORMAL_TEXT]
Build and deployment:

[P00774 | 105039:105246 | NORMAL_TEXT]
- Release compilation succeeded after applying the baseplate-origin correction. The deployed steam_api64.dll is 8,727,040 bytes with SHA-256 A7ADBD5DE0B709D991BB755080769B2E611687ABF20556F71EFDE9D8B5953CE4.

[P00775 | 105246:105350 | NORMAL_TEXT]
- Destiny was closed before DLL deployment and remains closed. The game was not launched automatically.

[P00776 | 105350:105384 | NORMAL_TEXT]
Package preservation and restore:

[P00777 | 105384:105547 | NORMAL_TEXT]
- The field-proven package set that removed most Tower static scenery was archived for patches 3, 4, 5, and 8 with suffix .izanami-passed-static-quarantine-field.

[P00778 | 105547:105703 | NORMAL_TEXT]
- The pre-blank-world source set was restored before the next staging run so transforms are authored once rather than compounding prior quarantine offsets.

[P00779 | 105703:106040 | NORMAL_TEXT]
- Restored SHA-256 values: package 3 = 61282BC7D1B7ADCD96B88C173FF8B7667DE00328088953786623FB6C9E591701; package 4 = 2872E0FCED0517B19B62AF2B046C826F0E480895AA13F2EE040B64F42853BD01; package 5 = 0536B910EC4179AFEEEEAB35280C6C17864C37CA3D1CB118B79EB3BBD84FE508; patch 8 = 873F9E1CBF4BB47359964A167F4F487C0BDE4AE19FA22D24752C655E22D2D491.

[P00780 | 106040:106053 | NORMAL_TEXT]
Next action:

[P00781 | 106053:106364 | NORMAL_TEXT]
- Launch Destiny directly without rebuilding. In orbit, open Izanami Forge, select Blank Baseplate, and press Build Blank World Draft exactly once. Do not launch Tower Carrier Control yet. Close Destiny after staging so the newly generated owner stages and patch-8 stage can be validated and promoted together.

[P00782 | 106364:106423 | HEADING_2]
17.19 Aligned blank-world staging validation and promotion

[P00783 | 106423:106435 | NORMAL_TEXT]
Validation:

[P00784 | 106435:106637 | NORMAL_TEXT]
- Blank Baseplate staging completed successfully for city_tower_social_d2 package 0x0369. The generated set contains physical owner stages for patches 3, 4, and 5 plus the logical latest patch-8 stage.

[P00785 | 106637:106971 | NORMAL_TEXT]
- The replacement aggregate 0x80ED22FB entry 0 now uses outer translation (-2454.747, 2274.877, -444.586), cancelling the first Shadowkeep VFX platform instance center and aligning it to Tower world origin. The skybox remains at identity and the other 11 cataloged Tower static placements remain quarantined at (32768, -32768, 8192).

[P00786 | 106971:107178 | NORMAL_TEXT]
- Header validation passed for all four staged files: version 38, package 0x0369, correct stored patch id, exact header/file-size agreement, nonzero entry and block counts, and in-bounds entry/block tables.

[P00787 | 107178:107459 | NORMAL_TEXT]
- All 13 changed block records passed cross-file validation. Latest-patch rows are byte-identical to their physical-owner rows; owner ids remain 3, 4, 5, or 8 as appropriate; flags remain 0x3; all stored bodies are in bounds; and recomputed SHA-1 values match every record digest.

[P00788 | 107459:107470 | NORMAL_TEXT]
Promotion:

[P00789 | 107470:107595 | NORMAL_TEXT]
- Only patches 3, 4, 5, and 8 were promoted. Stale patch-7 and patch-9 experimental stages were deliberately left untouched.

[P00790 | 107595:107924 | NORMAL_TEXT]
- Active SHA-256 values: patch 3 = 7445A1BE850B411B85CA1A81907423A762C8881794911E0CC460503E6DAF8B09; patch 4 = 4CEADF9B52A099D28EC96474EBE9FBD81B7DC4097B9ED767ED108E033CAAD854; patch 5 = 4349925B7533244C33AA409760F270826600425F02A90B5685D035F4DEEEC1AE; patch 8 = E71313AAF130ABD8C1E66414668DC6493990867CF1AE03320F2D46A176A2573E.

[P00791 | 107924:108085 | NORMAL_TEXT]
- Each promoted active file exactly matches its validated stage. The immediately previous active files are preserved with suffix .izanami-pre-aligned-baseplate.

[P00792 | 108085:108183 | NORMAL_TEXT]
- Destiny remained closed throughout validation and promotion. No automatic game launch occurred.

[P00793 | 108183:108200 | NORMAL_TEXT]
Next field test:

[P00794 | 108200:108654 | NORMAL_TEXT]
- Launch Destiny directly without rebuilding or pressing Build Blank World Draft again. From orbit, launch the Blank Baseplate/Tower Carrier Control path once. Check whether a visible platform is now centered near the Guardian, whether the Guardian can stand and move on it, and which residual visible objects or invisible collision surfaces remain. This test isolates spatial alignment; Tower collision removal remains a separate physics-resource task.

[P00795 | 108654:108655 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00796 | 108655:108721 | HEADING_2]
17.20 Foreign-parent field result and Tower-local baseplate pivot

[P00797 | 108721:108735 | NORMAL_TEXT]
Field result:

[P00798 | 108735:108997 | NORMAL_TEXT]
- The aligned aggregate row was verified on disk with parent 0x8150E15A and outer translation (-2454.747, 2274.877, -444.586), but no VFX platform rendered near the Guardian. Tower still reached activity:in_world with initial-slice and physics joins completing.

[P00799 | 108997:109163 | NORMAL_TEXT]
- Most ordinary Tower render scenery remained removed. Invisible collision remained, and the Guardian continued to collide with geometry that was no longer rendered.

[P00800 | 109163:109382 | NORMAL_TEXT]
- Mountains and city-light layers appeared far above the player. This is consistent with the previous (32768, -32768, 8192) quarantine translation affecting distant scenery or LOD placements rather than unloading them.

[P00801 | 109382:109394 | NORMAL_TEXT]
Conclusion:

[P00802 | 109394:109627 | NORMAL_TEXT]
- A cross-package tag reference can be valid on disk while its payload is not render-resident in the destination. Package header registration is not evidence that the destination's resource graph will stream a foreign static parent.

[P00803 | 109627:109837 | NORMAL_TEXT]
- Render placement and collision ownership are separate. Clearing static map-table visuals cannot be treated as a collision-removal mechanism; the Tower physics/Havok layer requires independent classification.

[P00804 | 109837:109865 | NORMAL_TEXT]
Tower-local implementation:

[P00805 | 109865:110067 | NORMAL_TEXT]
- The failed foreign-parent field set was archived for patches 3, 4, 5, and 8 with suffix .izanami-failed-foreign-parent-field. The source package baseline was restored before generating another draft.

[P00806 | 110067:110231 | NORMAL_TEXT]
- The restored aggregate row is table 0x80ED22FB entry 0, parent 0x80ED22FA, with identity outer transform. Parent 0x80ED22FA resolves to local payload 0x80ED22F9.

[P00807 | 110231:110526 | NORMAL_TEXT]
- Payload 0x80ED22F9 contains 1057 transforms, 260 static records, and 260 instance groups. The guarded floor candidate is group 218, transform 986, static index 218, resident mesh 0x80ED2C73. Its mesh bounds are approximately 50.96 by 50.96 by 0.60 world units before the authored 1.163 scale.

[P00808 | 110526:110800 | NORMAL_TEXT]
- The Sunrise build-data cache places the Tower courtyard arrival cluster around X=16.9..34.6, Y=63.4..66.1, Z=18.97..18.99. The new outer placement offset is (90.473, 35.386, 11.456), preserving the candidate's authored local transform while aligning it near that arrival.

[P00809 | 110800:111073 | NORMAL_TEXT]
- The package builder now fingerprints the exact payload size, array counts, group words, transform words, and mesh tag before writing. It changes the local group count to one and copies group 218 to the first group slot, retaining all local dependencies and culling data.

[P00810 | 111073:111271 | NORMAL_TEXT]
- The remaining discovered static placements keep their original translation and use uniform scale 0.0001. This replaces the large quarantine offset that displaced distant scenery above the player.

[P00811 | 111271:111293 | NORMAL_TEXT]
Build and deployment:

[P00812 | 111293:111453 | NORMAL_TEXT]
- Release compilation succeeded. The deployed steam_api64.dll is 8,728,064 bytes with SHA-256 6C41B53A92D04F57A3FF41401A451324BBA496185C4848861C7DCD199A318BB0.

[P00813 | 111453:111623 | NORMAL_TEXT]
- The DLL was deployed to both the game root and bin/x64 runtime paths with matching hashes. Destiny was closed before package restore and deployment and remains closed.

[P00814 | 111623:111644 | NORMAL_TEXT]
Next staging action:

[P00815 | 111644:111943 | NORMAL_TEXT]
- Launch Destiny directly without rebuilding. In orbit, open Izanami Forge, select Blank Baseplate, and press Build Blank World Draft exactly once. Do not launch Tower Carrier Control yet. Close Destiny after staging so the new owner-stage files and patch-8 stage can be validated before promotion.

[P00816 | 111943:111944 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00817 | 111944:111945 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00818 | 111945:111946 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00819 | 111946:112041 | NORMAL_TEXT]
17.21 Source-Derived Shadowkeep Culling Association and Group-Projection Contract — 2026-08-19

[P00820 | 112041:112042 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00821 | 112042:112343 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from MontagueM/Charm's current Shadowkeep schemas/deserializer and reconciled against the FIELD-TESTED/INSPECTED Tower and VFX package data already recorded above. It does not claim a per-instance transform or culling AABB has moved in Destiny.

[P00822 | 112343:112344 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00823 | 112344:113282 | NORMAL_TEXT]
SHADOWKEEP CULLING RESOURCE LINK — EVIDENCE-GRADED. Charm's SStaticMapData source has ModelOcclusionBounds at +0x18 annotated specifically for DESTINY1_RISE_OF_IRON, while SchemaDeserializer's single-attribute fallback causes that lone field annotation to be reused for every strategy. Therefore the public Charm parser will expose +0x18 in Shadowkeep, but that behavior alone is not a Shadowkeep-specific schema proof. Confidence remains high because the inspected VFX Shadowkeep payload independently reaches a 0x80809671 bounds resource and later static-map layouts retain the same broad concept. For Izanami, promote +0x18 from ToolBehaviorInferred to RawByteValidated only when the installed payload's raw u32 at +0x18 resolves to a valid tag whose entry class is 0x80809671 and whose payload validates as 0x80809673 bounds records. Store that attestation in the binding fingerprint rather than trusting Charm's fallback implicitly.

[P00824 | 113282:113283 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00825 | 113283:114467 | NORMAL_TEXT]
UNRESOLVED PIECE IS INDEXING, NOT RESOURCE OWNERSHIP. Shadowkeep still lacks a verified transform-to-bounds indexing field. SOURCE-DERIVED CORRECTION: Charm's Shadowkeep declarations do not support treating the field named Unk50 as a usable DynamicArray<u32> mapping. DynamicArray<T> is 0x10 bytes; a sequential header at +0x50 would overlap Shadowkeep's explicitly placed Statics header at +0x58. The later Alkahest 0x808093AD layout independently puts its real transform_to_bounds_index vector at +0x20 while +0x50 is a non-vector unknown, reinforcing that the Unk50 name is unsafe evidence. A culling diagnostician should record Instances.Count, InstanceBounds.Count, group InstanceOffset/InstanceCount, selected transform index, and raw header bytes at +0x20..+0x3F and +0x50..+0x57. Test direct transformIndex -> boundsIndex first when counts permit. Any alternative mapping must be recovered from those raw bytes and pass non-overlap, pointer/range, count, and geometric-coherence checks before it is parsed or written. Persist cullingMappingMode = Unknown | DirectIndex | RecoveredMap with the proven source fingerprint, and fail closed on Unknown for transform+AABB mutation.

[P00826 | 114467:114468 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00827 | 114468:115339 | NORMAL_TEXT]
GROUP-LIST PROJECTION IS STRUCTURALLY COHERENT SOURCE EVIDENCE. Charm's exporter selects each static solely from the instance-group row: model = Statics[StaticIndex], then the contiguous transform span Instances[InstanceOffset .. InstanceOffset+InstanceCount). Therefore the current Codex experiment that preserves the full Statics/Instances arrays, changes the exposed group list to one row, and copies source group 218 into that row is a coherent minimal 'group-list projection' under Charm's recovered model. It changes fewer native structures than physically deleting meshes or transforms. This remains SOURCE-DERIVED rather than native-field-proven because Destiny may retain hidden group-index-dependent metadata. The prepared field test should explicitly watch for missing geometry, viewpoint-dependent popping, or other evidence of hidden group/culling coupling.

[P00828 | 115339:115340 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00829 | 115340:115934 | NORMAL_TEXT]
CURRENT BUILD CONSEQUENCE. Do not rebuild the already prepared Section 17.20 package solely because of this research correction. Leaving the original transform array and broad bounds resources intact is safer than guessing a per-transform bounds rewrite during the group-projection test. After its field result, the highest-value implementation is a read-only Shadowkeep culling diagnostician for local payload 0x80ED22F9, especially group 218 / transform 986, followed by one true Position-XYZ-only StaticInstanceBinding once a bounds indexing mode passes structural and geometric validation.

[P00830 | 115934:115935 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00831 | 115935:116669 | NORMAL_TEXT]
2026-08-19 — SOURCE-DERIVED research update: clarified the Shadowkeep culling model using Charm's actual SchemaField strategy semantics. Charm exposes ModelOcclusionBounds at +0x18 -> SOcclusionBounds 0x80809671 under its cross-strategy fallback, but the installed Tower +0x18 relation still requires raw-byte attestation; after that, transform-to-bound indexing is the remaining culling association unknown. Added a fail-closed direct-index-vs-u32-map diagnostic and clarified that the currently prepared one-group/group-218 package is a structurally coherent group-list projection under Charm's exporter model, but not yet native-field-proven. No repository, DLL, package, or running Destiny process was changed by this research pa

[P00832 | 116669:116730 | HEADING_2]
17.21 Tower-local baseplate staging validation and promotion

[P00833 | 116730:116746 | NORMAL_TEXT]
Staging result:

[P00834 | 116746:116999 | NORMAL_TEXT]
- Blank Baseplate staging completed successfully for city_tower_social_d2 package 0x0369. The guarded tower_local_baseplate_payload step accepted group 218, and stage_tower_baseplate completed with 14 changed blocks across owner patches 3, 4, 5, and 8.

[P00835 | 116999:117334 | NORMAL_TEXT]
- Fresh staged SHA-256 values: patch 3 = 0835F6A26C21392DBC3F80BF2389AE6BE1B9109DE7B27FC86F87B1FD6E6D90C1; patch 4 = D8434CD9D908A3A07340F1811D0689C9DFC380DBA567D39353B82C1DC4BE98A9; patch 5 = 938AF8A079D184360BE5C889B4755CDD92673D6F1691723FA40366F87E69E911; patch 8 = A03E3AD8DEF7A47A3A08C78F2AD230AE01C9EBF3AA0EED4FE1F3944EC3C7AE94.

[P00836 | 117334:117346 | NORMAL_TEXT]
Validation:

[P00837 | 117346:117530 | NORMAL_TEXT]
- All four package headers passed: version 38, package 0x0369, expected stored patch id, exact header/file-size agreement, nonzero entry and block counts, and in-bounds public tables.

[P00838 | 117530:117799 | NORMAL_TEXT]
- Exactly 14 latest-patch block rows differ from the restored source. Every changed row is byte-identical to the corresponding physical-owner row, every body offset and length is in bounds, every row retains flags 0x3, and every stored body matches its recorded SHA-1.

[P00839 | 117799:118097 | NORMAL_TEXT]
- An independent tiger-pkg read of an isolated staged package directory successfully decrypted and decompressed the modified graph. Payload 0x80ED22F9 reports 1057 transforms, 260 statics, and one instance group. Group 0 now points to transform 986, static index 218, and resident mesh 0x80ED2C73.

[P00840 | 118097:118371 | NORMAL_TEXT]
- The active aggregate row retains local parent 0x80ED22FA and decodes to translation (90.473, 35.386, 11.456), rotation identity, and scale 1.0. This proves the staged image contains the intended Tower-local floor composition rather than the previous foreign-parent graft.

[P00841 | 118371:118382 | NORMAL_TEXT]
Promotion:

[P00842 | 118382:118554 | NORMAL_TEXT]
- Destiny was closed before validation and remained closed throughout promotion. Only patches 3, 4, 5, and 8 were promoted; patch-7 and patch-9 experiments were untouched.

[P00843 | 118554:118744 | NORMAL_TEXT]
- The prior active baseline is preserved with suffix .izanami-pre-tower-local-baseplate. Each active package now exactly matches its validated stage and has the staged SHA-256 listed above.

[P00844 | 118744:118761 | NORMAL_TEXT]
Next field test:

[P00845 | 118761:119244 | NORMAL_TEXT]
- Launch Destiny directly without rebuilding and do not press Build Blank World Draft again. From orbit, launch the Blank Baseplate/Tower Carrier Control path once. Check for a broad visible platform near the courtyard arrival, whether the Guardian can stand on the visible surface, whether displaced mountains or city lights remain overhead, and which invisible collision surfaces remain. Collision removal has not yet been implemented and remains a separate physics-resource task.

[P00846 | 119244:119245 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00847 | 119245:119246 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00848 | 119246:119346 | NORMAL_TEXT]
17.22 Source-Derived Shadowkeep Header-Layout Correction and Bounds-Mapping Diagnostic — 2026-08-19

[P00849 | 119346:119590 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from MontagueM/Charm's Shadowkeep schema/deserializer plus current Alkahest static-render code. It does not supersede the staged Tower-local package or any Codex/user FIELD-TESTED result.

[P00850 | 119590:119591 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00851 | 119591:120199 | NORMAL_TEXT]
CHARM SCHEMA SELF-CHECK. Charm fixes Shadowkeep Instances at +0x40 and Statics at +0x58. Its DynamicArray<T> type is serialized as a 0x10-byte header. Because the intervening field named Unk50 has no explicit offset, normal sequential layout would place that DynamicArray at +0x50 and consume through +0x5F, overlapping the explicit Statics header at +0x58. This is a concrete internal inconsistency in the public schema for Shadowkeep: the Unk50 declaration is stale, version-smudged, or otherwise incomplete. Izanami must not use Unk50.Count, Unk50[index], or a presumed +0x50 vector as culling authority.

[P00852 | 120199:120200 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00853 | 120200:120998 | NORMAL_TEXT]
LATER-VERSION CROSS-CHECK, NOT A BYTE CONTRACT. Alkahest's later 0x808093AD static-instances layout places the explicit transform_to_bounds_index vector at +0x20, transforms at +0x40, and a non-vector unk50 u64 at +0x50. A 2023 intermediate D2 Alkahest layout is stronger negative evidence for routine backporting: it already had an occlusion-bounds Tag at +0x18 and transforms at +0x40 while explicitly skipping/unmodeling +0x1C..+0x3F, and its static loader consumed transforms and bounds by the same group range. Therefore Shadowkeep +0x20..+0x3F must default to opaque/preserve-only. Capture it verbatim and inspect it as a mapping candidate only after DirectIndex evidence fails or the raw bytes independently satisfy the full Tiger-vector and mapping-semantics gates in Sections 17.34–17.36.

[P00854 | 120998:120999 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00855 | 120999:121785 | NORMAL_TEXT]
REVISED READ-ONLY CULLING DIAGNOSTIC. For payload 0x80ED22F9 and especially group 218 / transform 986 after the pending field result: (1) raw-read the +0x18 candidate, require it to resolve to a valid tag whose entry class is 0x80809671, then validate its 0x80809673 bounds records; (2) record transform count and bounds count; (3) if counts match, test direct transformIndex -> boundsIndex first; (4) dump raw +0x20..+0x3F and +0x50..+0x57 header bytes and only recognize an alternative vector/map if its count, pointer, element extent, and non-overlap all validate inside the logical entry; (5) build a reverse reference count for the selected bounds record; and (6) require geometric coherence before graduating the mapping. Unknown remains a hard stop for transform+AABB authoring.

[P00856 | 121785:121786 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00857 | 121786:122724 | NORMAL_TEXT]
GEOMETRIC COHERENCE CAN BE STRONGER THAN CENTER PROXIMITY. Charm's Shadowkeep StaticPart path decodes static-mesh vertices and applies SStaticMesh.ModelTransform as vertex.xyz = vertex.xyz * ModelTransform.w + ModelTransform.xyz before instance placement. A historical city_tower_d2_0369 extractor independently applies the Shadowkeep instance as quaternion rotation, then uniform Scale.x, then Position translation; translation is not multiplied by the instance scale. Current Charm still exposes the same Position/quaternion/Scale.x components. A diagnostician can therefore compute a predicted render AABB from the source mesh geometry under the source instance SRT and compare that predicted center/extents against each candidate occlusion bound. Use tolerant containment/overlap scoring rather than exact equality because authored occlusion bounds may be conservative. This check is read-only and does not imply collision ownership.

[P00858 | 122724:122725 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00859 | 122725:123315 | NORMAL_TEXT]
BINDING CONSEQUENCE. Replace any provisional U32Map provenance with RecoveredMap provenance containing the exact header offset, element count, pointer/range validation, source bytes/fingerprint, and evidence method. DirectIndex needs its own count-equality and geometric-coherence evidence. Neither mode should be serialized as authoritative merely because a parser can decode plausible integers. The currently staged one-group projection should not be rebuilt because of this correction; it preserves the original transform and culling arrays and remains the safest pending field control.

[P00860 | 123315:123316 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00861 | 123316:123974 | NORMAL_TEXT]
2026-08-19 — SOURCE-DERIVED research update: found a concrete self-overlap in Charm's public Shadowkeep SStaticMapData declarations that invalidates the prior Unk50-as-u32-bounds-map hypothesis. DynamicArray<T> is 0x10 bytes, so a sequential Unk50 header at +0x50 would overlap the explicit Shadowkeep Statics header at +0x58. Demoted Unk50 from the culling decision tree, promoted raw inspection of the unmodeled +0x20..+0x3F region, and defined a stricter geometric validation using decoded Shadowkeep mesh vertices plus ModelTransform and instance SRT. No repository files, DLLs, package files, or running Destiny process were changed by this research pa

[P00862 | 123974:123975 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00863 | 123975:124054 | HEADING_2]
17.23 Field-Tested Stair Candidate Result and Three-Layer Baseplate Correction

[P00864 | 124054:124490 | NORMAL_TEXT]
FIELD-TESTED RESULT. The one-group Tower-local package loaded successfully and reached activity:in_world. A substantial portion of scenery disappeared, proving that the installed package graph and group-list projection are active. Candidate group 218 / mesh 0x80ED2C73 rendered as a compound stair-and-floor assembly rather than a clean baseplate. Loose props remained, and invisible collision surfaces continued to block the Guardian.

[P00865 | 124490:124491 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00866 | 124491:124875 | NORMAL_TEXT]
MESH CLASSIFICATION. Corrected Shadowkeep mesh parsing identifies group 218 as a compound architectural asset: bounds extents are approximately (25.481, 25.481, 0.301), with 20,754 highest-detail indices and 6,918 triangles. This explains both the visible stairs and the attached floor sections. It is archived as a failed compound baseplate candidate, not treated as a usable plate.

[P00867 | 124875:124876 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00868 | 124876:125267 | NORMAL_TEXT]
NEXT SURFACE CANDIDATE. Group 13 / mesh 0x815B621C is the stronger resident candidate. Its bounds describe an approximately 14-by-14-unit, near-zero-thickness surface; it has 1,074 highest-detail indices and 358 triangles. The builder now isolates this group, copies transform 122, and rewrites the copied group instance count from 14 to 1 before aligning it to the courtyard test position.

[P00869 | 125267:125268 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00870 | 125268:125680 | NORMAL_TEXT]
ENTITY OWNERSHIP. A corrected map-graph walk found 265 valid null-resource entity placement rows in the reachable Tower graph, including several near the test area. These records are separate from static scenery placement tables and explain why cones, flags, and other props survived static suppression. The next diagnostic package preserves each entity translation and rotation but reduces its scale to 0.0001.

[P00871 | 125680:125681 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00872 | 125681:126328 | NORMAL_TEXT]
COLLISION OWNERSHIP — SUPERSEDED BY SECTION 17.58. The six reachable 0x80807246 rows resolve to 0x80807320 visibility/world bundles, not a universal collision layer. The earlier “27/0 Havok” discriminator was wrong for the installed Shadowkeep format: 26/7 is Havok, 27/0 is Criware video, and 24/0 is Umbra. Later package-wide validation found only two of the six Tower bundles have a structured path to Havok, and field suppression of all six did not remove phantom structural collision. The stronger next collision owners are the 14 base + 16 activity 0x8080929B direct-Havok rows and the 15 model-linked Havok rows described in Section 17.58.

[P00873 | 126328:126329 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00874 | 126329:126830 | NORMAL_TEXT]
IMPLEMENTATION AND DEPLOYMENT. The package builder now handles the surface, entity, and collision layers separately and reports entity/collision suppression counts. The previous stair package is archived with suffix .izanami-failed-compound-stair-baseplate-field, and clean .izanami-pre-tower-local-baseplate package baselines were restored before the next stage. Release DLL SHA-256 AA7121C115393F947F58A1163713E0DCD811465C3115B74C658E55F37DCE3164 is deployed identically to both game DLL locations.

[P00875 | 126830:126831 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00876 | 126831:127272 | NORMAL_TEXT]
CURRENT STATE. Code is built and deployed, but the new package has not yet been staged or promoted because that operation must run once inside Sunrise with package keys available. The next action is to launch Destiny without rebuilding, open Izanami Forge from orbit, select Blank Baseplate, and press Build Blank World Draft once. Then close Destiny so the generated owner-stage files can be validated and promoted before the field launch.

[P00877 | 127272:127273 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00878 | 127273:127614 | NORMAL_TEXT]
SUCCESS CRITERIA FOR THE NEXT PASS. The stair structure should be replaced by a simple flat surface; loose entity props should disappear; and phantom walls should disappear. Falling through the world is an acceptable diagnostic result for this pass and would isolate the remaining task to authoring or reusing one controlled collision plane

[P00879 | 127614:127615 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00880 | 127615:127698 | NORMAL_TEXT]
17.24 Source-Derived Collision-Placement Binding and Safe Havok Reuse — 2026-08-19

[P00881 | 127698:128016 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from MontagueM/Charm’s public Shadowkeep map/export schemas and is reconciled against the FIELD-INSPECTED six-row collision/Havok chains in Section 17.23. It does not claim that the pending six-row suppression package has been staged, promoted, or field-tested.

[P00882 | 128016:128017 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00883 | 128017:128851 | NORMAL_TEXT]
OUTER MAP ROW IS THE FIRST SAFE COLLISION PLACEMENT SEAM. Charm defines Shadowkeep SMapDataEntry as a 0x90-byte generic map row for statics, entities, and other resources with a world transform. Its Shadowkeep layout places Rotation at +0x10, Translation in the following Vec4, and DataResource at +0x78. DataResource is a ResourcePointer: the pointer resolves relative to the row payload and records the pointed resource’s class hash from the four bytes immediately preceding the target. This gives Izanami a narrow persistent collision provenance chain: map table/entry -> exact source row transform -> ResourcePointer class/target provenance -> terminal Havok file. The currently observed 0x80807246 -> 0x80807320 identities remain FIELD-INSPECTED unknown classes; public source does not justify inventing semantic names for them.

[P00884 | 128851:128852 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00885 | 128852:129832 | NORMAL_TEXT]
HAVOK GEOMETRY IS READABLE WITHOUT REWRITING HAVOK — FORMAT CORRECTED BY SECTION 17.58. In the installed Shadowkeep package format, terminal Havok files are type/subtype 26/7, not 27/0. Once a collision row's validated resource chain reaches a 26/7 Havok file, Charm's DestinyHavok bridge can expose shapes as vertices plus triangle indices, and the activity-map exporter supplies the owning SMapDataEntry transform. CollisionPlacementCatalog should therefore classify only rows whose terminal file is correctly identified as Havok 26/7. For each candidate record: map table tag; row index/class; source quaternion/translation/W scale; ResourcePointer class and target provenance; terminal Havok FileHash; physical block-route fingerprint; logical Havok SHA-256; shape count; per-shape vertex/index/triangle counts; local AABB; predicted source-world AABB; and a plane score based on horizontal area, vertical thickness, complexity, and overlap with the intended visible surface.

[P00886 | 129832:129833 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00887 | 129833:130490 | NORMAL_TEXT]
TRANSFORM-ORDER CAUTION. Charm’s standalone Havok OBJ helper computes exported vertices as (rotatedVertex + translation.xyz) * translation.w, while Charm’s ordinary map-entity exporter represents translation and scale as separate transform components. That disagreement makes the exact native multiplication order SOURCE-UNRESOLVED. Do not encode Charm’s OBJ formula as Destiny truth. The first authored collision experiment should keep Rotation and Translation.W byte-identical and change Translation XYZ only, preferably on a source row whose W is 1. Rotation and positive uniform scale become separate experiments only after translation is field-proven.

[P00888 | 130490:130491 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00889 | 130491:131414 | NORMAL_TEXT]
PERSISTENT BINDING DESIGN. Add CollisionPlacementBinding as a PackagePlacementBinding variant rather than attaching raw Havok bytes or a future runtime handle directly to ForgeUUID. Persist at minimum: layout/version id; map table tag; row index; complete source row transform; expected ResourcePointer class/chain fingerprint; terminal Havok FileHash; terminal logical-content fingerprint; source physical-route fingerprint; decoded shape/AABB fingerprint; and capability = CollisionAggregate | CollisionSurfaceCandidate | CollisionSurfaceProven. Resolution must fail closed if the row, chain, terminal file, logical bytes, or package route changes. A future RuntimeObjectBinding remains separate and ephemeral. One Forge object may ultimately carry coordinated but distinct RenderStaticBinding and CollisionPlacementBinding components; do not collapse render and collision ownership merely because they visually overlap.

[P00890 | 131414:131415 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00891 | 131415:132346 | NORMAL_TEXT]
SAFEST POST-SUPPRESSION FIELD EXPERIMENT. First capture the pending Section 17.23 result. If nulling the six rows removes the phantom Tower walls/floor, restore the source collision set and choose one read-only catalog candidate whose decoded Havok is broad, thin, simple, on a coherent route, and spatially compatible with group 13. Preserve the correctly identified terminal type-26/subtype-7 Havok bytes and every resource pointer; change only that row’s outer Translation XYZ to align the candidate collision AABB beneath the visible group-13 surface. Success is the Guardian standing on the moved visible surface while unrelated phantom walls remain absent. If a large collision complex returns with the candidate, classify it CollisionAggregate and choose a narrower candidate rather than editing Havok topology. Only after translation is proven should quaternion rotation, then positive uniform scale, be tested separately.

[P00892 | 132346:132347 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00893 | 132347:132758 | NORMAL_TEXT]
EDITOR/UI CONSEQUENCE. Package-backed Forge objects should expose render and collision readiness independently. A group-13 surface can report Render = Package-backed / Requires Build & Reload while Collision = Unbound, Candidate, or Proven. Gizmos may update Forge scene intent immediately, but neither surface should claim live collision motion until a built/reloaded package passes the field acceptance test.

[P00894 | 132758:132759 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00895 | 132759:133004 | NORMAL_TEXT]
Sources: MontagueM/Charm Tiger/Schema/Static/StaticMapData.cs, Tiger/SchemaTypes.cs, Tiger/Schema/Model/Havok/HavokMesh.cs, Tiger/Exporters/Exporter.cs, and Charm/ActivityMapEntityView.xaml.cs at commit 50d36ee1f9ecadad7522504c20b1f3f9c97e30af.

[P00896 | 133004:133005 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00897 | 133005:133913 | NORMAL_TEXT]
2026-08-19 — SOURCE-DERIVED research update: converted the newly identified Tower physics layer into an implementation-ready collision-binding plan without changing the pending field package. Public Charm source confirms that map-resource rows carry their own outer transform and typed ResourcePointer chain, and that correctly identified terminal type-26/subtype-7 Havok files can be decoded into shape vertices/triangles for read-only classification. Added a CollisionPlacementCatalog, fail-closed CollisionPlacementBinding, geometry/content fingerprints, render-vs-collision component separation, and a translation-only reuse experiment that moves an existing collision resource by its outer row while leaving Havok bytes untouched. Exact native W-scale/transform order remains deliberately unclaimed. No repository files, DLLs, package files, or running Destiny process were changed by this research pa.

[P00898 | 133913:133914 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00899 | 133914:133915 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00900 | 133915:134004 | NORMAL_TEXT]
17.25 Source-Derived Culling Attestation and Global Bounds-Correlation Gate — 2026-08-19

[P00901 | 134004:134475 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from current public Charm and Alkahest source and is reconciled against the FIELD-TESTED Tower-local group projection in Section 17.23. It corrects evidence grading around the Shadowkeep +0x18 culling field and defines a read-only way to resolve the remaining per-transform bounds-index question without guessing. It does not change or invalidate the currently pending group-13/entity/collision diagnostic package.

[P00902 | 134475:134476 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00903 | 134476:135519 | NORMAL_TEXT]
CHARM FALLBACK IS NOT SHADOWKEEP-SPECIFIC SCHEMA EVIDENCE. In current Charm source, SStaticMapData.ModelOcclusionBounds carries one SchemaField attribute, and that attribute is explicitly tagged DESTINY1_RISE_OF_IRON at offset +0x18. SchemaDeserializer::GetAttribute has a generic rule that if a field has only one strategy attribute, it returns that attribute for every active strategy. This explains why Charm exposes +0x18 while parsing Shadowkeep, but it also means the parser behavior itself cannot prove the Shadowkeep byte contract. The VFX payload's observed 0x80809671 dependency and the continuity of later layouts make +0x18 a strong hypothesis, not a write authority. Izanami should require a RawLayoutAttestation: data class == 0x8080966D, logical entry size/layout fingerprint matches the installed source, raw u32 at +0x18 resolves through TagHash/package metadata to entry class 0x80809671, and that resource validates as an array of 0x80809673 / 0x30 bounds records. Only then can cullingResourceMode become RawByteValidated.

[P00904 | 135519:135520 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00905 | 135520:136806 | NORMAL_TEXT]
GLOBAL BOUNDS CORRELATION CAN TEST DIRECT INDEXING BEFORE ANY WRITE. For each valid Shadowkeep group, map its contiguous InstanceOffset..InstanceOffset+InstanceCount range to Statics[StaticIndex]. Decode the selected mesh's source geometry, apply the mesh ModelTransform exactly as Charm does, then apply the source 0x808071A3 instance in the historically recovered Tower order—quaternion rotation, uniform Scale.x, then Position translation—to the eight mesh-AABB corners; the instance translation is not multiplied by Scale.x. This yields a predicted render AABB for each transform. Compare each predicted AABB against the decoded 0x80809673 bounds records using tolerant metrics: normalized center distance, extent ratio, containment/overlap, and the score margin between the direct-index candidate bounds[i] and the best competing bound. Run the test collection-wide, not only on one hand-picked transform. If Instances.Count == InstanceBounds.Count and bounds[i] is consistently the best geometric match for a large majority of well-formed transforms, DirectIndex becomes a strong source-data hypothesis; the selected candidate still needs its own unambiguous match and unique-reference check. Do not invent a fixed confidence threshold before seeing the Tower score distribution.

[P00906 | 136806:136807 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00907 | 136807:137678 | NORMAL_TEXT]
IF DIRECT INDEX FAILS, USE GEOMETRY TO DISCOVER THE MAP, NOT TO AUTHOR AROUND IT. Build a read-only best-match/permutation report between predicted transform AABBs and bounds records, preferably within compatible group/mesh neighborhoods first. Then inspect the unmodeled Shadowkeep header bytes, especially +0x20..+0x3F, for a validated vector whose values reproduce that recovered association. A plausible geometric assignment without a matching native encoding is diagnostic evidence only; it is not sufficient to write an AABB because Destiny's renderer may use an unrecovered mapping. Persist cullingMappingMode = Unknown | DirectIndex | RecoveredMap plus the evidence method, raw header fingerprint, transform/bounds counts, selected bounds index, reverse-reference count, and correlation metrics. Unknown remains a hard stop for the first transform+AABB mutation.

[P00908 | 137678:137679 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00909 | 137679:138738 | NORMAL_TEXT]
CULLING SPACE SHOULD BE MEASURED, WITH COLLECTION-LOCAL NOW THE SOURCE-DERIVED PRIMARY HYPOTHESIS. Same-era pre-BL Alkahest constructs the outer map-row Transform but the 0x808071B3 static-placement branch does not attach it to the static parent or children; children receive only inner 0x808071A3 transforms. Other branches do attach the row Transform, so this is placement-branch behavior rather than a missing parser field. Run raw-bounds correlation in CollectionLocal first and OuterComposed as a secondary cross-check. Persist cullingSpace = CollectionLocal | OuterComposed | Unknown and cullingSpaceEvidence. Do not promote CollectionLocal to native write authority until raw correlation and the isolated field mutation agree. For an inner translation under an outer identity linear transform, shift the raw per-instance AABB and collection bounds by the same inner delta; outer translation does not affect the delta. For non-identity outer rotation/scale, world-space authoring must remain disabled until the outer linear composition is field-proven.

[P00910 | 138738:138739 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00911 | 138739:139504 | NORMAL_TEXT]
PLACEMENT-CATALOG/BINDING ADDITIONS. Add a read-only LayoutAttestation block to candidate rows: layoutId, static data tag/class, logical-size/source digest, raw +0x18 value, resolved bounds tag/class, transformCount, boundsCount, cullingMappingMode, cullingSpace, correlation summary, selected bounds index, boundsRefCount, and physical-route fingerprints for both mutable resources. StaticInstanceBinding may serialize culling provenance only after the attestation and mapping pass; otherwise expose the object as RenderStaticCandidate / CullingUnresolved and keep writable per-instance placement disabled. This is consistent with fail-closed ForgeUUID -> PackagePlacementBinding semantics and keeps future RuntimeObjectBinding/raw handles separate and ephemeral.

[P00912 | 139504:139505 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00913 | 139505:140359 | NORMAL_TEXT]
SEPARATE THE CURRENT GROUP-13 BASEPLATE TEST FROM THE FIRST TRUE PER-INSTANCE PROOF. Section 17.23's current surface experiment intentionally copies group 13 and changes the copied group's InstanceCount from 14 to 1 as part of scenery decomposition. That is a useful baseplate-composition diagnostic, but it changes group metadata and therefore must not be cited as the acceptance test for the future one-assumption StaticInstanceBinding milestone. After the current package result is captured, the first true per-instance placement proof should start from an unprojected source layout, preserve all vector/group sizes and group records, change one 0x808071A3 Position XYZ only, update only its proven matching culling AABB plus conservatively required collection bounds, and independently score visual motion, multi-view culling, and collision old/new.

[P00914 | 140359:140360 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00915 | 140360:140804 | NORMAL_TEXT]
Sources: MontagueM/Charm Tiger/Schema/Static/StaticMapData.cs, Tiger/SchemaDeserializer.cs, Tiger/SchemaTypes.cs, and Tiger/Schema/Static/StaticPart.cs at current public main/commit lineage; cohaereo/alkahest crates/data/tfx/features/statics.rs used only as a later-version cross-check for explicit +0x18 occlusion, +0x20 transform-to-bounds mapping, and +0x40 transforms. No later-version byte offsets are imported into the Shadowkeep writer.

[P00916 | 140804:140805 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00917 | 140805:141640 | NORMAL_TEXT]
2026-08-19 — SOURCE-DERIVED research update: corrected the evidence grade of Shadowkeep ModelOcclusionBounds +0x18. Charm exposes it in Shadowkeep because its deserializer reuses a lone D1 SchemaField attribute across strategies, so Izanami must raw-byte-attest +0x18 -> class 0x80809671 before treating it as writable provenance. Added a collection-wide StaticBoundsCorrelation diagnostic using decoded mesh geometry + ModelTransform + source instance SRT, a direct-index vs recovered-map gate, culling-space classification, and LayoutAttestation fields for fail-closed StaticInstanceBinding. Also separated the pending group-13 projection test from the later true per-instance translation proof, which must preserve group/vector sizes. No repository files, DLLs, packages, or running Destiny process were changed by this research pa

[P00918 | 141640:141641 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00919 | 141641:141732 | NORMAL_TEXT]
17.26 Source-Derived Shadowkeep Tail Layout and Collection-Bounds Attestation — 2026-08-20

[P00920 | 141732:141733 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00921 | 141733:142156 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from public MontagueM/Charm commit 50d36ee1f9ecadad7522504c20b1f3f9c97e30af and cohaereo/alkahest commit b140945588717ce75218ff48e15674a6655431d7. It does not supersede the FIELD-TESTED Tower-local group projection in Section 17.23 and does not change the pending group-13/entity/collision package. No local Izanami source is inferred from these remote repositories.

[P00922 | 142156:142157 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00923 | 142157:143365 | NORMAL_TEXT]
EXACT CHARM TOOL-READ OFFSETS FOR THE SHADOWKEEP TAIL. Charm's SchemaDeserializer resets its running field offset whenever a field has an explicit SchemaField offset and otherwise advances by that field's serialized size. DynamicArray<T> is exactly 0x10 serialized bytes. In Shadowkeep SStaticMapData 0x8080966D / 0xA0, Statics is explicitly fixed at +0x58. The following InstanceCounts field has no explicit Shadowkeep offset, so Charm necessarily reads its 0x10-byte group-vector header at +0x68..+0x77. The next explicit field is at +0x78, then Vector4 fields are explicit/sequential at +0x80 and +0x90. This yields a non-overlapping tail contract +0x58 Statics -> +0x68 InstanceCounts/groups -> +0x78 opaque field/padding -> +0x80/+0x90 Vec4s even though the earlier Unk50 DynamicArray declaration remains internally inconsistent. Izanami can therefore raw-attest +0x68 as the Shadowkeep group-vector header instead of deriving group storage heuristically: require its count/pointer/extent to validate, reproduce the already observed 260-group topology, and reproduce known group-to-transform/static relationships such as group 218 -> transform 986 / static 218 before exposing it as binding provenance.

[P00924 | 143365:143366 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00925 | 143366:144616 | NORMAL_TEXT]
CROSS-VERSION TAIL PARITY STRONGLY IDENTIFIES A PREFERRED COLLECTION-BOUNDS CANDIDATE, BUT NOT EVERY UNKNOWN FIELD. Charm's Witch Queen offsets place Statics at +0x78, the implicit InstanceCounts vector at +0x88, Unk98 at +0x98, and two tail Vector4s at +0xA0/+0xB0. Alkahest independently lays out its later SStaticMeshInstances with statics at +0x78, instance_groups at +0x88, vertex_ao_identifier at +0x98, and AxisAlignedBBox bounds occupying +0xA0/+0xB0. Historical pre-BL Alkahest declares the Shadowkeep class size as 0x98 and does not model its tail, but a later Alkahest main-bak schema demonstrates that these declared sizes can be stale/incomplete: it also says 0x98 while modeling sequential fields and an Aabb extending beyond that extent, before current main corrects the same later structure to 0xC0. Therefore the size annotation alone should not demote Charm's explicit Shadowkeep +0x80/+0x90 Vec4 pair. Treat +0x80/+0x90 as the preferred/high-confidence collection-AABB candidate for raw attestation, never as automatic write authority. Charm's +0x78 TigerHash-like field remains opaque/read-only because the later analogous identifier differs in width/semantics, and +0x50..+0x57 remains the historically corroborated opaque slot.

[P00926 | 144616:144617 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00927 | 144617:145820 | NORMAL_TEXT]
RawTailAabbAttestation FOR TOWER 0x80ED22F9. Before making the collection bounds writable: (1) require data class 0x8080966D, expected logical-layout/source fingerprint, and valid +0x68 group-vector header; (2) test the explicit Charm Shadowkeep +0x80/+0x90 Vec4 pair first; if it fails structural or geometric validation, fall back to bounded candidate-window discovery in the remaining tail; require finite XYZ, componentwise min <= max, and no overlap with the validated group vector or opaque slots; (3) compute predicted source render AABBs from decoded static geometry, mesh ModelTransform, source group ranges, and source 0x808071A3 transforms; (4) compare the candidate tail AABB against the union of valid source render AABBs in both collection-local and outer-composed space as defined by Section 17.25, recording the space with coherent conservative coverage rather than assuming it; and (5) fingerprint the exact raw tail bytes, chosen corner offsets, logical entry digest, and physical route. Only then promote collectionBoundsMode = RawTailAABBValidated. If the values are non-finite, inverted, or geometrically incoherent, leave them opaque and keep per-instance culling writes disabled.

[P00928 | 145820:145821 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00929 | 145821:146631 | NORMAL_TEXT]
WRITE CONSEQUENCE AFTER THE SEPARATE PER-TRANSFORM BOUNDS MAP GRADUATES. The first true StaticInstanceBinding translation can then have three narrowly attested writable seams: one 0x808071A3 Position XYZ, the separately proven matching 0x80809673 per-instance AABB XYZ, and the raw-attested collection AABB at the discovered tail offsets. Preserve quaternion, all scale components, every vector/group size and pointer, both per-instance-bound Vec4 W lanes, both collection-bound Vec4 W lanes, and every unknown byte. For the first proof, never shrink collection bounds: newMin.xyz = min(oldMin.xyz, movedInstanceMin.xyz) and newMax.xyz = max(oldMax.xyz, movedInstanceMax.xyz). This removes collection-bound location as a major unknown while leaving transform-to-bounds indexing as a separate fail-closed gate.

[P00930 | 146631:146632 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00931 | 146632:147124 | NORMAL_TEXT]
PLACEMENT-CATALOG/BINDING ADDITIONS. Shadowkeep candidate rows should record groupVectorHeaderOffset = 0x68 with its raw header/source fingerprint; collectionBoundsOffsets = RawAttestedTailOffsets; collectionBoundsMode; source collection AABB; cullingSpace; and the existing transform/bounds mapping provenance. These are package-layout facts/provenance, not runtime handles. ForgeUUID remains stable editor identity; future RuntimeObjectBinding/native handles remain separate and ephemeral.

[P00932 | 147124:147125 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00933 | 147125:147899 | NORMAL_TEXT]
2026-08-20 — SOURCE-DERIVED research update: reconciled Charm's actual sequential-offset deserializer with its Shadowkeep static-map schema and recovered an exact tool-read location for the InstanceCounts/group vector at +0x68. Cross-checking Charm's Witch Queen tail against Alkahest shows exact statics/group/bounds offset parity and strongly upgrades Shadowkeep +0x80/+0x90 to collection-AABB attestation targets, while a TigerHash-vs-u64 type mismatch at the neighboring identifier field warns against importing later semantics wholesale. Added RawTailAabbAttestation and a conservative collection-bound expansion contract for the eventual one-instance translation. No repository files, DLLs, package files, or running Destiny process were changed by this research pass

[P00934 | 147899:147900 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00935 | 147900:148001 | NORMAL_TEXT]
17.27 Source-Derived Historical Tower Parser Anchors and Exact Instance Transform Order — 2026-08-20

[P00936 | 148001:148002 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00937 | 148002:148481 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from MontagueM/DestinyMapmining and MontagueM/D2Maps historical raw extractors plus current MontagueM/Charm source. The historical extractor explicitly targets city_tower_d2_0369, so it is unusually relevant to the same Tower package family used by Izanami. It does not supersede any FIELD-TESTED result, does not prove native culling indexing, and does not change the currently prepared group-13/entity/collision package.

[P00938 | 148481:148482 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00939 | 148482:149696 | NORMAL_TEXT]
HISTORICAL TOWER RAW-LAYOUT ANCHORS. The older city_tower_d2_0369 map extractor reads the static-map transform count directly from raw offset +0x40, assumes 0x30-byte transform records begin at logical offset +0xC0, reads the static/model count directly from +0x58, then places the model-hash array after the transform payload plus a 0x20-byte gap. It locates the group data by scanning for the little-endian class marker bytes 90 71 80 80 (class 0x80807190), skips the associated header, and parses 0x8-byte group/count records. This is independent historical evidence for the same Shadowkeep transform/statics/group topology now recovered in Charm. It is not a general writer contract: use these values as Tower-specific read-only sanity anchors and continue resolving vectors through validated relative pointers. For payload 0x80ED22F9, a HistoricalTowerLayoutAttestation should compare the pointer-derived transform start against +0xC0, verify transform element size 0x30, verify Statics.Count is read at +0x58, and corroborate the group vector with the 0x80807190 element marker/topology. Any disagreement should fail the binding closed and be investigated rather than patched around with hard-coded offsets.

[P00940 | 149696:149697 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00941 | 149697:150737 | NORMAL_TEXT]
Unk50 CONSEQUENCE. The historical Tower parser successfully treats +0x58 as the native static-count field and does not establish a separate 0x10-byte vector beginning at +0x50. Combined with Charm's known +0x50..+0x5F overlap against the explicit +0x58 Statics header, this upgrades the current safety decision: Charm's field named Unk50 must be classified as ToolSchemaOverlap / non-authoritative for Shadowkeep binding. Preserve +0x50..+0x57 as opaque raw provenance. Do not use Unk50.Count, its pointer interpretation, or its decoded elements as a transform-to-bounds map. The unmodeled +0x20..+0x3F region remains fallback-only mapping territory if collection-wide DirectIndex fails or its raw bytes independently satisfy a strict vector attestation. Intermediate D2 public tooling shows that the same broad +0x18/+0x40 layout can leave this gap opaque while still consuming bounds positionally, so vector-looking bytes there must not be inferred as a mapping without the full envelope, coverage, range, and semantic-correlation gates.

[P00942 | 150737:150738 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00943 | 150738:151592 | NORMAL_TEXT]
EXACT SOURCE-DERIVED INSTANCE TRANSFORM ORDER FOR GEOMETRIC CORRELATION. Current Charm decodes Shadowkeep static-mesh vertices and first applies SStaticMesh.ModelTransform as p_mesh = p_raw * ModelTransform.w + ModelTransform.xyz. The historical Tower extractor then applies each 0x808071A3 instance in three explicit stages: quaternion rotation, uniform scale from Scale.x, then Position translation. In formula form, p_instance = Position + Scale.x * R(quaternion) * p_mesh. Translation is therefore not multiplied by the instance scale in this historical Tower path. This gives StaticBoundsCorrelation a stronger source-derived prediction than an unordered 'instance SRT' description. Use that exact order for the collection-local correlation pass, while keeping it SOURCE-DERIVED until a native per-instance field test confirms the same composition.

[P00944 | 151592:151593 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00945 | 151593:152345 | NORMAL_TEXT]
OUTER-WORLD-SPACE LIMITATION IN PUBLIC TOOLING. Current Charm's static-map traversal loads SMapDataResource -> StaticMapParent -> StaticMap and exports the inner static instances without passing the owning SMapDataEntry outer transform into StaticMapData.LoadIntoExporterScene. FIELD-TESTED Izanami evidence, however, already proves that changing the outer Tower row moves the native aggregate. Therefore Charm-exported static coordinates must not be treated as authoritative native world coordinates for this chain. StaticBoundsCorrelation should continue to score both collection-local and separately outer-composed spaces, using the field-tested source outer placement as an explicit composition layer rather than assuming Charm already applied it.

[P00946 | 152345:152346 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00947 | 152346:152919 | NORMAL_TEXT]
PLACEMENT-CATALOG ADDITIONS. Add read-only historicalLayoutMatch, instancesResolvedOffset, expectedHistoricalInstancesOffset, transformElementSize, staticsCountOffset, groupElementClassMarker, and transformCompositionMode fields. A Shadowkeep candidate may report transformCompositionMode = HistoricalTower_RotateScaleTranslate only when the class/layout fingerprint and Tower raw anchors match; otherwise use Unknown and keep culling correlation/write enablement fail-closed. These are package provenance fields, not RuntimeObjectBinding state and not raw native handles.

[P00948 | 152919:152920 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00949 | 152920:153947 | NORMAL_TEXT]
2026-08-20 — SOURCE-DERIVED research update: found a historical raw city_tower_d2_0369 extractor that independently corroborates the Shadowkeep Tower static layout used by Izanami: transform count at +0x40, 0x30-byte transforms beginning at +0xC0 in the historical files, static count at +0x58, and 0x80807190 / 0x8 group records. This strengthens the decision to quarantine Charm's overlapping Unk50 field and provides Tower-specific parser-attestation anchors. More importantly, the historical code fixes the inner render transform order as mesh ModelTransform, then instance quaternion rotation, uniform Scale.x, then Position translation; translation is not scaled. Current Charm also omits the outer SMapDataEntry transform when exporting static resources, while Izanami field tests prove native Destiny applies that outer placement, so bounds correlation must keep collection-local and outer-composed spaces distinct. No repository files, DLLs, package files, or running Destiny process were changed by this research pa.

[P00950 | 153947:153948 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00951 | 153948:153949 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00952 | 153949:154053 | NORMAL_TEXT]
17.28 Source-Derived Shadowkeep Group-Range Semantics and Direct-Index Correlation Upgrade — 2026-08-20

[P00953 | 154053:154054 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00954 | 154054:154534 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from remote public GitHub only: MontagueM/D2Maps commit 79725baa74d25923177ed651ca5a74aadb8b196b, MontagueM/Charm commit 50d36ee1f9ecadad7522504c20b1f3f9c97e30af, and cohaereo/alkahest commit b140945588717ce75218ff48e15674a6655431d7. It does not infer unpublished local Izanami source and does not supersede FIELD-TESTED package results. It narrows the parser/binding contract for the pending true one-instance translation.

[P00955 | 154534:154535 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00956 | 154535:155351 | NORMAL_TEXT]
HISTORICAL SHADOWKEEP GROUP ROW SEMANTICS ARE NOW STRONGLY CORROBORATED. D2Maps parses the 8-byte rows located after the 0x80807190 marker as four u16 fields named Count, CumulativeCount, ModelRef, and Unk. Current Charm assigns the same Shadowkeep 0x80807190 / 0x08 row to InstanceCount, InstanceOffset, StaticIndex, and Unk06. Later Alkahest preserves the same semantic shape as instance_count, instance_start, static_index, unk6. Together these sources strongly support the writer-neutral interpretation: row[0] is the number of transforms in the group, row[1] is the first/global transform index for that range, and row[2] selects the static mesh/model. This independently fits the already-inspected Tower relationship group 218 -> transform 986 / static 218. The final u16 remains opaque and must be preserved.

[P00957 | 155351:155352 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00958 | 155352:155891 | NORMAL_TEXT]
IMPORTANT HISTORICAL-PARSER LIMITATION. D2Maps does not actually use CumulativeCount as an offset when exporting. It groups rows by ModelRef, sums Count for repeated ModelRef values, sorts by model index, then walks transforms with a locally accumulated last_index. That was sufficient for historical extraction, but it is lossy and must NOT be copied into Izanami's binding/writer. In particular, multiple 0x80807190 rows may legally target the same StaticIndex, so neither groupIndex == staticIndex nor one-row-per-model may be assumed.

[P00959 | 155891:155892 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00960 | 155892:156669 | NORMAL_TEXT]
NEW READ-ONLY GROUP RANGE ATTESTATION. For every 0x80807190 row, decode the four raw u16 fields and validate: InstanceOffset + InstanceCount does not overflow and is <= transforms.Count; StaticIndex < statics.Count; the raw 8-byte row is preserved in the provenance fingerprint; and the selected transform index is contained by the claimed half-open range [InstanceOffset, InstanceOffset + InstanceCount). Build a reverse transformOwnerGroups[] map rather than inferring ownership from row order. Record transformGroupRefCount for every transform and staticReuseGroupCount for every static model. For the first writable StaticInstanceBinding require transformGroupRefCount == 1. A model reused by other non-overlapping groups is allowed; an overlapping transform range is not.

[P00961 | 156669:156670 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00962 | 156670:157168 | NORMAL_TEXT]
COLLECTION TOPOLOGY DIAGNOSTIC. Sort all valid group ranges by InstanceOffset and classify their coverage as ExactPartition, PartitionWithGaps, Overlap, or Invalid. ExactPartition means the ranges cover [0, transforms.Count) exactly once with no gaps or overlaps. Do not silently repair or reorder rows in the writer. Even when the collection is not an exact partition, the catalog may remain read-only, but writable per-instance candidates inside overlapping or ambiguous ranges must fail closed.

[P00963 | 157168:157169 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00964 | 157169:157991 | NORMAL_TEXT]
DIRECT-INDEX CULLING CORRELATION GETS A SECOND, STRONGER TEST. If RawLayoutAttestation validates the Shadowkeep bounds resource, bounds.Count == transforms.Count, and the group topology is ExactPartition, test direct transformIndex -> boundsIndex not only per instance but per GROUP RANGE. For each 0x80807190 row, compute the union of predicted render AABBs for its authoritative transform range using the recovered Shadowkeep mesh->instance transform order, then compare it against the union of occlusion bounds carrying the same candidate indices. Score both collection-local and outer-composed spaces. Agreement across hundreds of group ranges is harder to fake than nearest-neighbor matching of individual repeated props and is therefore a materially stronger discriminator for DirectIndex versus an unknown mapping.

[P00965 | 157991:157992 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00966 | 157992:159587 | NORMAL_TEXT]
MAPPING EVIDENCE STATES — AUTHORITY CORRECTION. Keep GroupRangeUnresolved, DirectIndexPerInstanceOnly, and HighConfidenceDirectIndexCandidate as read-only diagnostic states, but do not treat HighConfidenceDirectIndexCandidate as persistent write authority. Two historical pre-Beyond-Light Alkahest static renderers inspected in the prebl-0.5 and prebl-old-0.1 branches do not consume SOcclusionBounds when rendering static instances, so there is currently no historical Shadowkeep renderer source that proves transformIndex == boundsIndex. Later Alkahest lineage provides useful analogy by pairing transform group ranges with same-range bounds when available, but that is later-version evidence only. Persist a separate boundsMappingEvidence state such as Unknown | LaterLineageAnalogy | LocalDirectIndexCorrelation | RawMappingStructureAttested | FieldProvenDirectIndex. For direct indexing, LocalDirectIndexCorrelation may select the explicitly labeled one-assumption field experiment, but it must not silently authorize arbitrary persistent scene writes; DirectIndex becomes binding authority only after that exact source/layout fingerprint is FIELD-PROVEN. A recovered raw mapping structure may be authoritative only while its exact bytes/ranges/fingerprint attest. The one-assumption test remains unchanged: preserve every vector/group size and row, change one 0x808071A3 Position XYZ, shift only the experimentally selected matching AABB by the same delta, conservatively expand the raw-attested collection AABB, and independently score visual position, multi-view culling, and collision.

[P00967 | 159587:159588 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00968 | 159588:160080 | NORMAL_TEXT]
PLACEMENT-CATALOG/BINDING ADDITIONS. Persist layoutId; groupClass = 0x80807190; groupIndex; rawGroupRow; instanceOffset; instanceCount; staticIndex; opaqueUnk06; transformGroupRefCount; staticReuseGroupCount; groupRangeTopologyDigest; cullingGroupCorrelationSummary; and the existing resource/physical-route fingerprints. The source fingerprint must cover both the selected 0x80807190 row and the selected 0x808071A3 transform so a stale scene cannot silently retarget after package changes.

[P00969 | 160080:160081 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00970 | 160081:160463 | NORMAL_TEXT]
IMPLEMENTATION ORDER. Extend the read-only Shadowkeep placement catalog with GroupRangeAttestation and reverse transform ownership first. Then run the existing global bounds correlation with the new group-range union score. Do not alter the pending group-13/entity/collision package because this finding only changes the acceptance gate for the later true per-instance translation.

[P00971 | 160463:160464 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00972 | 160464:161158 | NORMAL_TEXT]
2026-08-20 — SOURCE-DERIVED research update: historical D2Maps names the Shadowkeep 0x80807190 fields Count/CumulativeCount/ModelRef/Unk, independently corroborating Charm's InstanceCount/InstanceOffset/StaticIndex layout and Alkahest's later instance_count/instance_start/static_index semantics. Added fail-closed group-range ownership, overlap/partition diagnostics, and group-union culling correlation; the first writable static candidate now requires exactly one group owner and may promote direct bounds indexing only when both per-instance and authoritative group-range geometry agree. No repository files, DLLs, package files, or running Destiny process were changed by this research pa

[P00973 | 161158:161257 | NORMAL_TEXT]
17.29 Source-Derived Pre-Beyond-Light Alkahest Layout Correction and Bounds-Tail Gate — 2026-08-20

[P00974 | 161257:161597 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from remote public cohaereo/alkahest historical pre-Beyond-Light branches, especially prebl-old-0.1 and prebl-0.5. It does not infer unpublished local Izanami source, supersede FIELD-TESTED Tower results, or change the currently prepared group-13/entity/collision diagnostic package.

[P00975 | 161597:161598 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00976 | 161598:162215 | NORMAL_TEXT]
+0x50 OPAQUE SLOT IS NOW HISTORICALLY CORROBORATED. The 2023 prebl-old-0.1 parser models class 0x8080966D with transforms at +0x40, then exactly one u64-sized unk50 slot, followed by statics and 0x80807190 groups. The later prebl-0.5 data crate models the same location as [u32; 2]. Both independently describe exactly eight bytes at +0x50..+0x57 rather than a DynamicArray. This upgrades the current safety decision from merely noticing Charm's self-overlap to a positive pre-BL layout anchor: preserve +0x50..+0x57 byte-for-byte as Opaque50_57; its semantics remain unknown and it is not a transform-to-bounds map.

[P00977 | 162215:162216 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00978 | 162216:162796 | NORMAL_TEXT]
SHADOWKEEP OCCLUSION RECORD BYTE CONTRACT IS STRONGER. prebl-0.5 defines SOcclusionBounds 0x80809671 with a vector of SObjectOcclusionBounds 0x80809673 / 0x30. Each record consumes two Vec4 values for the AABB in its first 0x20 bytes and retains an opaque [u32;4] tail in its final 0x10 bytes. Once the transform-to-bounds association is independently proven, the first translation-only mutation should change only min.xyz/max.xyz by the selected delta, preserve both Vec4 W lanes, and preserve the final 16 bytes exactly. Add boundsRecordTailFingerprint to read-only provenance.

[P00979 | 162796:162797 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00980 | 162797:163473 | NORMAL_TEXT]
+0x18 GETS INDEPENDENT HISTORICAL SUPPORT, NOT WRITE AUTHORITY. In prebl-0.5 the same 0x8080966D static structure contains a commented occlusion_bounds field explicitly targeted at +0x18. That is independent historical developer evidence consistent with Charm's cross-strategy +0x18 interpretation and the FIELD-INSPECTED VFX 0x80809671 dependency. However, the field is commented out and the historical pre-BL renderer does not use it for per-instance culling, so this evidence strengthens the hypothesis without removing the RawLayoutAttestation gate. Installed Tower bytes must still prove +0x18 resolves to class 0x80809671 before Izanami treats it as binding provenance.

[P00981 | 163473:163474 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00982 | 163474:164423 | NORMAL_TEXT]
HEADER-SIZE DISAGREEMENT IS WEAKER EVIDENCE THAN EXPLICIT FIELD OFFSETS. prebl-0.5 declares SStaticMeshInstances 0x8080966D with schema size 0x98 and stops modeling the tail after the +0x68 group vector, while current Charm explicitly models the Shadowkeep form as 0xA0 with a field at +0x78 followed by Vec4 values at +0x80 and +0x90. Critically, Alkahest's own later main-bak lineage also declared the post-BL 0x808093AD structure as size 0x98 while simultaneously modeling sequential fields and an Aabb whose serialized extent runs beyond 0x98; current main corrects that later structure to 0xC0. Therefore a historical Alkahest size annotation is not strong enough by itself to refute Charm's explicit Shadowkeep tail offsets. Regrade +0x80/+0x90 as the preferred/high-confidence collection-AABB candidate, but not as write authority: installed Tower bytes must still pass raw geometric attestation before mutation. Keep +0x78 opaque/read-only.

[P00983 | 164423:164424 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00984 | 164424:165209 | NORMAL_TEXT]
REVISED RawTailAabbAttestation. Start with the explicit Charm Shadowkeep candidate min Vec4 at +0x80 and max Vec4 at +0x90. Require finite XYZ, componentwise min <= max, no overlap with the validated +0x68 group vector, and geometrically conservative coverage of the predicted source render-AABB union in either CollectionLocal or OuterComposed space. Fingerprint the exact raw +0x80/+0x90 bytes, logical-entry digest, and physical route. If this exact pair fails or remains ambiguous, only then fall back to bounded scanning of non-overlapping two-Vec4 windows in the unmodeled tail. Do not write any candidate until exactly one source-fingerprinted layout passes the geometric attestation; otherwise collectionBoundsMode remains Unknown and the transform+AABB writer stays disabled.

[P00985 | 165209:165210 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00986 | 165210:165895 | NORMAL_TEXT]
BINDING/CATALOG CORRECTION. Replace a hard-coded layoutId that treats v0xA0 as sufficient authority with a family-level discriminator plus raw source evidence: layoutFamily = D2PreBL_Shadowkeep_0x8080966D; declaredHeaderSizeEvidence = {Charm:0xA0, PreBLAlkahest:0x98}; observedSourceHeaderOrTailExtent; opaque50_57 raw bytes/fingerprint; tailLayoutMode = Unknown | PreBL_0x98Candidate | Charm_0xA0Candidate | RawAttested; and collectionBoundsOffsets only after RawAttested. Keep source logical-entry size/digest and physical-route fingerprints separate from schema-declared header size so a future package update fails closed instead of silently matching a tool-specific layout alias.

[P00987 | 165895:165896 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00988 | 165896:166477 | NORMAL_TEXT]
IMPLEMENTATION CONSEQUENCE. The next read-only Shadowkeep placement/culling catalog should incorporate these historical pre-BL anchors before the first true one-instance write. This finding does not justify rebuilding or modifying the current group-13/entity/collision diagnostic package because that package is a scenery-decomposition test, not the one-assumption StaticInstanceBinding acceptance test. The later true test still requires unchanged group/vector sizes, one Position-XYZ edit, a proven per-instance bounds association, and a raw-attested collection-bounds location.

[P00989 | 166477:166478 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00990 | 166478:166698 | NORMAL_TEXT]
Sources: cohaereo/alkahest prebl-old-0.1 src/statics.rs; cohaereo/alkahest prebl-0.5 crates/alkahest-data/src/statics.rs and occlusion.rs; current main static renderer retained only as a later-version culling reference.

[P00991 | 166698:166699 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00992 | 166699:167472 | NORMAL_TEXT]
2026-08-20 — SOURCE-DERIVED research update: historical pre-Beyond-Light Alkahest code independently resolves the Shadowkeep +0x50 ambiguity as an eight-byte opaque slot and gives an exact 0x80809673 bounds-record byte contract. A follow-up lineage check found that Alkahest itself later carried a stale 0x98 size annotation on a structure whose modeled fields extend beyond that boundary, so declared size alone cannot demote Charm's explicit Shadowkeep +0x80/+0x90 tail. Those offsets are now the preferred collection-AABB attestation candidate, still non-writable until installed Tower geometry validates them. The +0x18 occlusion link remains raw-attestation-only. No repository files, DLLs, package files, or running Destiny process were changed by this research pass

[P00993 | 167472:167473 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00994 | 167473:167565 | NORMAL_TEXT]
17.30 Source-Derived AO-Offset Continuity and Collection-Tail Evidence Regrade — 2026-08-20

[P00995 | 167565:167907 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from remote public GitHub only: cohaereo/alkahest historical pre-Beyond-Light and current lineages plus MontagueM/Charm. It does not infer unpublished local Izanami source, supersede any FIELD-TESTED result, or alter the currently prepared group-13/entity/collision diagnostic package.

[P00996 | 167907:167908 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00997 | 167908:168757 | NORMAL_TEXT]
TRANSFORM +0x28 IS A STRONG AO-CONTINUITY CANDIDATE, NOT A CULLING MAP. Historical pre-Beyond-Light Alkahest models Shadowkeep SStaticMeshInstanceTransform 0x808071A3 / 0x30 with opaque u32 fields at +0x28 and +0x2C. In the current later-version Alkahest transform, the corresponding +0x28 slot is explicitly vertex_ao_offset, and the ambient-occlusion implementation introduced at commit e66934d308f3040bf63a960cd0db4fb7db020a1b consumes that per-transform offset together with an AO base before indexing static AO data. This is strong semantic continuity but is not native Shadowkeep proof. Classify Shadowkeep +0x28 as AOOffsetContinuityCandidate until field/native evidence upgrades it. Preserve raw +0x28 and +0x2C byte-for-byte in the first translation experiment and exclude +0x28 from transform-to-bounds-map candidate discovery by default.

[P00998 | 168757:168758 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P00999 | 168758:169293 | NORMAL_TEXT]
COLLECTION +0x78 HAS WEAK AO-IDENTIFIER CONTINUITY ONLY. Charm's Shadowkeep static-map tail has an opaque/TigerHash-like field at +0x78 immediately before the +0x80/+0x90 Vec4 pair. Later Alkahest places vertex_ao_identifier immediately before its collection AABB. That positional continuity is useful provenance, but the recovered types/widths are not identical across versions. Keep Shadowkeep +0x78 opaque and read-only; the catalog may record AOIdentifierContinuityCandidate, but the first per-instance test must never rewrite it.

[P01000 | 169293:169294 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01001 | 169294:170031 | NORMAL_TEXT]
HEADER-SIZE EVIDENCE REGRADE. Historical preBL Alkahest declares Shadowkeep 0x8080966D as size 0x98, but that declaration is not sufficient to refute Charm's explicit +0x80/+0x90 tail. Alkahest's own later main-bak lineage likewise declared post-BL 0x808093AD as size 0x98 while modeling sequential fields and an Aabb whose serialized extent runs beyond that size; current main corrects the later class to 0xC0. Therefore +0x80/+0x90 remains the preferred/high-confidence Shadowkeep collection-AABB attestation candidate. It is still SOURCE-DERIVED and non-writable until installed Tower bytes pass RawTailAabbAttestation. If +0x80/+0x90 fails structural/geometric validation, then and only then use the bounded tail-discovery fallback.

[P01002 | 170031:170032 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01003 | 170032:170744 | NORMAL_TEXT]
CULLING SEARCH CONSEQUENCE. Keep DirectIndex as the first transform-to-bounds EXPERIMENT HYPOTHESIS when raw +0x18 attestation, equal transform/bounds counts, exact group topology, per-instance geometry correlation, and group-range union correlation support it; those source-data correlations choose the test but do not by themselves make DirectIndex persistent binding authority. If DirectIndex fails, inspect the unmodeled raw +0x20..+0x3F region for a validated mapping structure. Do not use +0x50..+0x57 (historically corroborated opaque bytes), transform +0x28 (AO continuity candidate), or collection +0x78 (weak AO-identifier continuity candidate) as bounds-index fields without contrary native evidence.

[P01004 | 170744:170745 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01005 | 170745:171279 | NORMAL_TEXT]
PLACEMENT-CATALOG / BINDING ADDITIONS. Add transformTail28Raw, transformTail2cRaw, aoOffsetEvidence = Unknown | ContinuityCandidate | NativeProven, collectionTail78Raw, aoIdentifierEvidence = Unknown | ContinuityCandidate | NativeProven, collectionBoundsCandidate = Unknown | Charm80_90Preferred | RawAttested, and exact raw/source-route fingerprints. These are package-layout provenance, not live runtime state. ForgeUUID remains the persistent editor identity; RuntimeObjectBinding/raw native handles remain separate and ephemeral.

[P01006 | 171279:171280 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01007 | 171280:171890 | NORMAL_TEXT]
FIRST TRUE TRANSLATION CONTRACT IS UNCHANGED. After the culling mapping and collection bounds independently graduate, change exactly one 0x808071A3 Position XYZ, shift only its proven matching 0x80809673 AABB min.xyz/max.xyz by the same delta, and conservatively expand the raw-attested collection AABB. Preserve quaternion, all scale components, every group/vector size and row, both bounds W lanes, AO candidate fields, and every opaque byte. Observe visual motion, multi-view culling, and collision independently; if rendering moves while collision does not, keep the binding classified render-static only.

[P01008 | 171890:171891 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01009 | 171891:172214 | NORMAL_TEXT]
Sources: cohaereo/alkahest prebl-0.5 and prebl-old-0.1 statics schemas; cohaereo/alkahest later main-bak/current static schemas and ambient-occlusion implementation lineage, including commit e66934d308f3040bf63a960cd0db4fb7db020a1b; MontagueM/Charm Shadowkeep StaticMapData schema. All are remote public source references.

[P01010 | 172214:172215 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01011 | 172215:173001 | NORMAL_TEXT]
2026-08-20 — SOURCE-DERIVED research update: corrected the weight assigned to historical Alkahest size metadata after finding the same lineage previously declared a later static-instances structure as 0x98 even though its modeled fields extended beyond that extent. Restored Charm's explicit Shadowkeep +0x80/+0x90 Vec4 pair as the preferred collection-AABB attestation target while keeping it non-writable until raw Tower geometry validates it. Also identified strong cross-generation continuity for transform +0x28 as the static vertex-AO offset, which removes that field from the default culling-map search and keeps AO/opaque tails unchanged in the first true translation proof. No repository files, DLLs, package files, or running Destiny process were changed by this research pa.

[P01012 | 173001:173002 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01013 | 173002:173003 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01014 | 173003:173109 | NORMAL_TEXT]
17.31 Source-Derived Historical Renderer Negative Evidence and Bounds-Mapping Authority Gate — 2026-08-20

[P01015 | 173109:173110 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01016 | 173110:173415 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from remote public cohaereo/alkahest historical pre-Beyond-Light and later renderer lineages. It does not infer unpublished local Izanami source, supersede FIELD-TESTED package results, or modify the pending group-13/entity/collision field package.

[P01017 | 173415:173416 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01018 | 173416:174206 | NORMAL_TEXT]
NO HISTORICAL SHADOWKEEP RENDERER CURRENTLY PROVES DIRECT BOUNDS INDEXING. The prebl-0.5 static renderer builds and draws static instances from transforms/models without reading SOcclusionBounds, and the older prebl-old-0.1 instanced renderer likewise constructs instance matrices directly from 0x808071A3 transforms without a culling-bounds association. The prebl-0.5 data schema's commented +0x18 occlusion_bounds field is therefore historical layout evidence only; it is not paired with renderer code that demonstrates transformIndex == boundsIndex. This is important negative evidence: DirectIndex remains a strong experiment candidate when installed Tower data correlates globally, but no historical pre-BL renderer source currently upgrades it to native/Shadowkeep mapping authority.

[P01019 | 174206:174207 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01020 | 174207:175197 | NORMAL_TEXT]
LATER-LINEAGE CORROBORATION IS USEFUL BUT VERSION-SCOPED. The 2023-12-23 Alkahest culling path established same-range transform/bounds coverage for the later SOcclusionBounds 0x808093B1 lineage, not Shadowkeep 0x80809671. Current Alkahest makes the later consumer model more exact: SStaticMeshInstances carries an optional transform_to_bounds_index Vec<u32>; StaticInstancesRenderer resolves each authoritative group transform range, uses transformIndex directly only when that vector is empty, otherwise requires mapping[transformIndex], then unions the resolved bounds into group_bounds before collection->group->individual visibility testing. Missing mapping entries or invalid bounds indices are errors, not per-element DirectIndex fallbacks. This is strong LaterLineageAnalogy for an optional direct-or-explicit-map model, but neither the later +0x20 byte offset nor its semantics become Shadowkeep write authority without raw Tower attestation and the Section 17.31 field-proof gate.

[P01021 | 175197:175198 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01022 | 175198:175931 | NORMAL_TEXT]
PER-GROUP COVERAGE GATE. Extend the read-only catalog with boundsCoverageMode = FullCollection | FullSelectedGroup | Partial | Missing plus selectedGroupBoundsRangeValid. For the first Shadowkeep DirectIndex experiment, require the selected authoritative 0x80807190 group range to be fully representable in the decoded bounds array and require the selected transform's candidate bounds index to be in range. Equal collection-wide transform/bounds counts remains the strongest condition for the collection-wide correlation proof, but the catalog should report group-local coverage explicitly rather than collapsing every mismatch into one generic failure. A Partial/Missing selected group is a hard stop for transform+AABB authoring.

[P01023 | 175931:175932 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01024 | 175932:176827 | NORMAL_TEXT]
MAPPING AUTHORITY MODEL. Separate experiment selection from persistent binding authority. Recommended evidence progression: Unknown -> source analogies (LaterLineageAnalogy and/or SameEraParallelArrayAnalogy) -> LocalDirectIndexCorrelation -> FieldProvenDirectIndex for the no-explicit-map case, or Unknown -> RawMappingStructureAttested for a recovered encoded map whose exact pointer/count/range/raw-byte fingerprint validates. LocalDirectIndexCorrelation may arm only the deliberately isolated one-instance field experiment described in Sections 17.25/17.28; it must not let the editor silently emit general DirectIndex writes. After a successful field test, persist FieldProvenDirectIndex together with the exact layout/data-tag/logical-entry/group-topology/bounds-resource/route fingerprints so a stock update or different collection fails closed instead of inheriting the result globally.

[P01025 | 176827:176828 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01026 | 176828:178066 | NORMAL_TEXT]
QUATERNION CONVENTION WARNING FOR THE POST-TRANSLATION ROTATION MILESTONE — REFINED BY SECTION 17.38. The historical prebl-old-0.1 Alkahest renderer applies .inverse() to the stored quaternion, but prebl-0.5's map loader passes the same-era 0x808071A3 quaternion directly into Transform and Transform::local_to_world() uses Mat4::from_scale_rotation_translation without inversion. The historical Tower extractor in Section 17.27 is also direct. Alkahest's own branch-to-branch disagreement therefore shows that renderer/exporter convention, transposition, or handedness can create an apparent direct-vs-inverse split without different package bytes. Preserve quaternion unchanged in the translation proof and keep rotationConvention = Unresolved for package authoring. For read-only bounds correlation, score both DirectStored and InverseStored modes and retain the mode/score margin as provenance; do not promote the better fit to rotation write authority. After translation succeeds, the first rotation experiment should use one isolated instance and a small unmistakable known angle while preserving scale/vector topology, then compare observed direction against both interpretations before serializing a native quaternion convention.

[P01027 | 178066:178067 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01028 | 178067:178737 | NORMAL_TEXT]
2026-08-20 — SOURCE-DERIVED research update: inspected two historical pre-Beyond-Light Alkahest static renderers and found that neither consumes SOcclusionBounds, so there is no historical Shadowkeep renderer proof for DirectIndex despite the strong +0x18/layout and geometric-correlation evidence already documented. Regraded HighConfidenceDirectIndexCandidate to an experiment-selection state, added explicit bounds-mapping authority/evidence states and per-group bounds coverage, and recorded a quaternion-convention discrepancy for the later rotation milestone. No repository files, DLLs, package files, or running Destiny process were changed by this research pass

[P01029 | 178737:178856 | NORMAL_TEXT]
17.32 Source-Derived Shadowkeep Map-Row → Static-Collection Bridge and Later-Lineage DirectIndex Timeline — 2026-08-20

[P01030 | 178856:178857 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01031 | 178857:179192 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from remote public cohaereo/alkahest history, especially the prebl-0.5 branch and the 2023-12-23/2025 later static-culling lineage. It does not infer unpublished local Izanami source, supersede FIELD-TESTED Tower results, or modify the pending group-13/entity/collision package.

[P01032 | 179192:179193 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01033 | 179193:180296 | NORMAL_TEXT]
SHADOWKEEP DIRECT MAP-ROW BRIDGE. The prebl-0.5 map loader gives a version-appropriate path that matches the classes already observed in the installed Tower package. It defines SMapDataTable 0x808099D6 with SMapDataTableEntry 0x808099D8. For rows whose DataResource.resource_type is 0x808071B3, the loader treats the resource as a placements/static-map path: it seeks to DataResource.offset + 0x10, reads a TagHash, resolves the 0x24-byte SUnk80806EF4 parent/wrapper, raw-attests the parent-relative +0x8 instances TagHash (Tag<T> is a raw TagHash on disk), resolves that child as SStaticMeshInstances 0x8080966D, then iterates the 0x80807190 instance groups, selects Statics[StaticIndex], and slices transforms over [InstanceOffset, InstanceOffset + InstanceCount). This directly matches Izanami’s field-inspected Tower identity family: map table class 0x808099D6 -> parent class 0x80806EF4 -> payload class 0x8080966D. Therefore the current Shadowkeep placement catalog should prefer this map-row bridge rather than requiring the later 0x80806CC8/0x80806CC9 pattern/component chain from Section 16.2.

[P01034 | 180296:180297 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01035 | 180297:181267 | NORMAL_TEXT]
RAW-ATTESTATION GATE. Treat 0x808071B3 placement semantics and the +0x10 TagHash read as SOURCE-DERIVED until the installed Tower bytes reproduce them. DataResource uses tiger-parse ResourcePointer semantics: at pointer-field address P read i64 displacement d; 0 and i64::MAX are invalid; resolved target = P+d; resource type/class is read at target-4. For every candidate persist: tableTag/tableClass/rowIndex; pointerFieldOffset; rawDisplacement; resolvedTargetOffset; typeWordOffset; raw/validated resource_type; raw TagHash read at resolvedTarget+0x10; resolved parent tag/class/serialized-layout fingerprint; staticInstancesTag/class; and logical plus physical block-route fingerprints. Reject the ShadowkeepMapRowStatic parser variant if resource_type is not 0x808071B3, the resolved parent class is not 0x80806EF4, or the child payload class is not 0x8080966D. Do not mutate any of these route/pointer fields during the first true per-instance translation proof.

[P01036 | 181267:181268 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01037 | 181268:181924 | NORMAL_TEXT]
IMPLEMENTATION CONSEQUENCE. Add an explicit path/layout discriminator such as ShadowkeepMapRowStatic = 0x808099D6/0x808099D8 -> DataResource 0x808071B3 -> 0x80806EF4 parent -> 0x8080966D static instances. Once raw-attested, enumerate the already recovered Shadowkeep vectors/groups from that payload: transforms 0x808071A3, statics, and 0x80807190 group ranges. This gives the read-only PlacementCatalog a direct root in the same classes Codex has already field-inspected, avoids unnecessary Post-BL pattern traversal, and lets PackagePlacementBinding fingerprint the whole table-row-resource-parent-payload chain before resolving a group/model/transform.

[P01038 | 181924:181925 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01039 | 181925:182763 | NORMAL_TEXT]
LATER-LINEAGE DIRECTINDEX TIMELINE. Alkahest’s 2023-12-23 “Single static dirty frustum culling” implementation already slices transforms and occlusion bounds with the identical authoritative group range [instance_start, instance_start + instance_count). The 2025 robustness fix preserves that exact relationship and merely falls back to no bounds/culling when the bounds slice cannot be obtained. Exact schema inspection at the 2023 commit shows that this renderer is using the later SOcclusionBounds class 0x808093B1, not Shadowkeep 0x80809671. This establishes a long-lived LaterLineageAnalogy for direct ordering/group-range coverage, but it still does not prove Shadowkeep transformIndex == boundsIndex or bypass the LocalDirectIndexCorrelation -> FieldProvenDirectIndex / RawMappingStructureAttested authority gate in Section 17.31.

[P01040 | 182763:182764 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01041 | 182764:183266 | NORMAL_TEXT]
PLACEMENT-CATALOG ADDITIONS. Add pathMode, dataResourceType, dataResourceTargetFingerprint, preheaderTagRaw, parentClass, parentLayoutFingerprint, staticInstancesTag, staticInstancesClass, and rowToStaticChainFingerprint. Keep these distinct from cullingMappingEvidence and from physical block routing. A candidate can have a fully attested Shadowkeep row-to-static chain while its transform-to-bounds index remains unresolved; that candidate stays read-only until the separate culling gate graduates.

[P01042 | 183266:183267 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01043 | 183267:183581 | NORMAL_TEXT]
Sources: cohaereo/alkahest prebl-0.5 crates/alkahest-data/src/map.rs and crates/alkahest-renderer/src/loaders/map.rs; cohaereo/alkahest 2023-12-23 commit 63cd3059ac806522ada2e003e640cd0346e66ba3 and 2025 robustness commit f6ffe808f6ad0082e099e50de7cb47c272b8527d. These are remote public-source observations only.

[P01044 | 183581:183582 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01045 | 183582:184190 | NORMAL_TEXT]
2026-08-20 — SOURCE-DERIVED research update: recovered a direct pre-Beyond-Light/Shadowkeep map-row bridge that matches the field-inspected Tower table/parent/payload classes, so the current Tower parser no longer needs the Post-BL pattern/component chain as its primary route. Also pinned same-range transform/bounds slicing in Alkahest to at least 2023-12-23 while confirming that implementation uses later occlusion class 0x808093B1 and therefore remains analogy rather than Shadowkeep write authority. No repository files, DLLs, package files, or running Destiny process were changed by this research pa

[P01046 | 184190:184191 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01047 | 184191:184293 | NORMAL_TEXT]
17.33 Source-Derived Same-Era Parallel Occlusion Arrays and Mapping False-Positive Guard — 2026-08-20

[P01048 | 184293:184566 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from remote public cohaereo/alkahest prebl-0.5 source only. It does not infer unpublished local Izanami source, supersede FIELD-TESTED Tower results, or alter the pending group-13/entity/collision diagnostic package.

[P01049 | 184566:184567 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01050 | 184567:185523 | NORMAL_TEXT]
SAME-ERA POSITIONAL OCCLUSION ORDERING IS NOW DIRECTLY OBSERVED IN OTHER SHADOWKEEP/PRE-BL MAP STRUCTURES. prebl-0.5 defines map structure 0x80806F95 with three parallel vectors: object records 0x80806F97, SObjectOcclusionBounds records, and u32 values. Each 0x80806F97 object contains a full transform matrix plus an embedded AABB that the source explicitly identifies as the same bounding box represented in the separate SObjectOcclusionBounds array. The corresponding pre-BL map loader iterates the three vectors together by array index and warns when object[i].bounds does not equal occlusionBounds[i].bb. A second same-era control exists in SLightCollection 0x8080713A: the loader likewise iterates light records, placement transforms, and referenced occlusion bounds in lockstep by index. This is materially stronger than a later-version-only analogy: positional placement/bounds alignment is an observed convention in multiple same-era map systems.

[P01051 | 185523:185524 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01052 | 185524:186385 | NORMAL_TEXT]
STATIC-INSTANCE IMPLICATION — STRONGER EXPERIMENT SELECTION, NOT WRITE AUTHORITY. These are different resource classes from SStaticMeshInstances 0x8080966D, and the historical pre-BL static renderer still does not consume 0x80809671 for static culling. Therefore this evidence does not prove Shadowkeep static transformIndex == boundsIndex. It does justify adding SameEraParallelArrayAnalogy alongside LaterLineageAnalogy when choosing DirectIndex as the first isolated experiment hypothesis. The existing Tower-specific gates remain mandatory: raw +0x18 bounds-resource attestation, transform/bounds count checks, authoritative 0x80807190 group topology, collection-wide per-instance correlation, group-range union correlation, and one consistent culling space. Only the isolated field test can promote that exact source fingerprint to FieldProvenDirectIndex.

[P01053 | 186385:186386 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01054 | 186386:187632 | NORMAL_TEXT]
IMPORTANT U32-MAPPING FALSE-POSITIVE GUARD. The same 0x80806F95 structure contains a parallel Vec<u32>, yet the inspected loader names it _unk28 and does not consume the values as an index map while still zipping the vector positionally with objects and bounds. Therefore discovering a structurally valid or same-length u32 vector in the unmodeled static header, including +0x20..+0x3F, is not enough to call it transform_to_bounds_index. Current later Alkahest supplies a specific consumer hypothesis to test if such a Shadowkeep vector raw-attests: empty means DirectIndex; nonempty means one bounds index lookup for every referenced transform, with no partial fallback. Upgrade RawMappingStructureAttested into RawVectorAttested plus MappingSemanticsCorrelated. A nonempty candidate must have sufficient transform coverage, all referenced values in range, coherent reverse references, and produce a materially better or uniquely explanatory per-instance/group-range geometry association than DirectIndex. All-zero, constant, partial-coverage, or merely identity-valued vectors remain auxiliary/unknown without stronger consumer or field evidence; an identity vector is semantically equivalent to DirectIndex and adds no independent authority.

[P01055 | 187632:187633 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01056 | 187633:188255 | NORMAL_TEXT]
PLACEMENT-CATALOG DIAGNOSTICS. For every raw u32 mapping candidate emit candidateHeaderOffset, count, resolved pointer/range, valueMin/valueMax, outOfRangeCount, uniqueValueCount, identityMatchRate, constant/allZero flags, reverse-reference histogram, directIndexCorrelationScore, mappedCorrelationScore, and mappedMinusDirectScore. Keep mappingCandidateSemantics = Unknown | AuxiliaryLikely | CorrelatedMap | FieldProven. The first true StaticInstanceBinding writer remains disabled unless it has FieldProvenDirectIndex or a structurally and semantically attested recovered map under the exact source/layout fingerprint.

[P01057 | 188255:188256 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01058 | 188256:188660 | NORMAL_TEXT]
COLLECTION-BOUNDS CORROBORATION ONLY. The same-era SLightCollection combines a collection-level AABB with per-light occlusion bounds, providing additional source-era support for the general model of a conservative collection envelope plus item-level culling bounds. This does not independently prove Shadowkeep static +0x80/+0x90; RawTailAabbAttestation remains required before those bytes are writable.

[P01059 | 188660:188661 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01060 | 188661:189541 | NORMAL_TEXT]
2026-08-20 — SOURCE-DERIVED research update: found direct pre-Beyond-Light map-loader evidence that multiple same-era resource families align placement records/transforms and occlusion bounds positionally by array index, materially strengthening DirectIndex as the first Shadowkeep static experiment hypothesis without promoting it to write authority. The same source also exposes a parallel u32 vector whose values are ignored by the consumer, establishing a concrete false-positive guard: a plausible u32 vector cannot become a bounds map from pointer/count validity alone and must pass semantic correlation against geometry and group topology. Added SameEraParallelArrayAnalogy, mapping-candidate diagnostics, and a structural-plus-semantic RawMappingStructureAttested gate. No repository files, DLLs, package files, or running Destiny process were changed by this research pa

[P01061 | 189541:189628 | NORMAL_TEXT]
17.34 Source-Derived Exact Tiger Vector and ResourcePointer Byte Contract — 2026-08-20

[P01062 | 189628:189629 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01063 | 189629:189980 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from remote public v4nguard/tiger-parse history plus cohaereo/alkahest prebl-0.5, which explicitly depends on tiger-parse 0.1.12 lineage. It does not infer unpublished local Izanami source, supersede FIELD-TESTED Tower results, or alter the pending group-13/entity/collision diagnostic package.

[P01064 | 189980:189981 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01065 | 189981:190910 | NORMAL_TEXT]
EXACT 64-BIT TIGER VECTOR CONTRACT. tiger-parse’s Vec<T> reader has kept the same envelope convention from its initial public 2024 implementation through current code. For a vector header beginning at logical offset H, the 64-bit form reads count at H, then a relative offset at H+8. The pointer base is the offset-field address, so envelope = (H + 8) + relativeOffset. If count == 0, the parser returns an empty vector without following the target. Otherwise the envelope begins with a duplicated count value; under type-checking builds the next word is used for element-type validation, and element payload always begins at envelope + 0x10. A historical tiger-parse unit test makes the base rule explicit: a header at H=0 with offset 0x18 resolves to envelope 0x20, not 0x18. This removes ambiguity from Izanami’s Shadowkeep vector parser for transforms (+0x40), statics (+0x58), groups (+0x68), and the decoded bounds vector.

[P01066 | 190910:190911 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01067 | 190911:191603 | NORMAL_TEXT]
SIGNEDNESS / VERSION CORRECTION. The vector byte width is stable, but parser signedness changed later. tiger-parse’s initial 2024 code used u64 Size/Offset on the 64-bit path. A 2025-05-24 change converted generic Size/Offset to i64 specifically to support backwards seeking. Therefore the canonical handoff must not describe the pre-BL/Shadowkeep vector count as inherently signed merely because current tiger-parse uses i64. Izanami should bind the raw 16-byte header and parser-layout version, reject absurd counts under either interpretation, use checked pointer arithmetic, and treat signed-negative rejection as a current-parser safety rule rather than historical Shadowkeep semantics.

[P01068 | 191603:191604 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01069 | 191604:192496 | NORMAL_TEXT]
FAIL-CLOSED read_tiger_vec64 CONTRACT. Persist headerOffset, rawHeader16, count, rawRelativeOffset, resolvedEnvelopeOffset, duplicatedCount, optional/attested elementTypeMarker, elementStart = envelope+0x10, elementSize, logicalEnd, and a source digest. Require H+0x10 in the reconstructed logical entry; checked count*elementSize; checked relative-address addition; envelope+0x10 and the final element byte in range; and duplicatedCount == count. For count == 0, preserve the raw header and return empty without requiring a valid target. Where an element class is independently known, such as 0x808071A3 transforms, 0x80807190 groups, or 0x80809673 bounds records, use an available envelope type marker only as an additional attestation; do not invent marker semantics for primitive/TagHash vectors. Any failure keeps the candidate read-only and prevents PackagePlacementBinding resolution.

[P01070 | 192496:192497 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01071 | 192497:193257 | NORMAL_TEXT]
EXACT ResourcePointer CONTRACT FOR MAP/COLLISION ROWS. tiger-parse’s ResourcePointer reader records the pointer-field address P before reading an i64 displacement d. d == 0 and d == i64::MAX are invalid. The resolved payload target is P + d, and the resource type/class word is read from target - 4. This makes the Shadowkeep map-row bridge in Section 17.32 more precise: for DataResource, persist pointerFieldOffset, rawDisplacement, resolvedTargetOffset, typeWordOffset = target-4, and resourceType; the prebl-0.5 map loader then seeks resolvedTarget + 0x10 and reads the TagHash used to resolve the 0x80806EF4 parent. The same pointer provenance should be used by CollisionPlacementCatalog in Section 17.24 rather than storing only a vague relative target.

[P01072 | 193257:193258 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01073 | 193258:193741 | NORMAL_TEXT]
TAGHASH DISTINCTION. Alkahest prebl Tag<T> reads a raw TagHash and resolves it through the package manager; that is a different on-disk primitive from ResourcePointer. Keep the candidate Shadowkeep +0x18 occlusion link classified as a raw 32-bit TagHash attestation: if installed 0x80ED22F9 +0x18 resolves to an entry class 0x80809671, store that exact raw tag and route fingerprint. Do not parse +0x18 as a ResourcePointer merely because nearby map-row DataResource fields use one.

[P01074 | 193741:193742 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01075 | 193742:194284 | NORMAL_TEXT]
IMPLEMENTATION CONSEQUENCE. The read-only placement catalog can now raw-attest the Shadowkeep row→resource→parent→collection bridge and every critical collection vector with exact pointer bases instead of heuristic offset following. This does not solve transform→bounds indexing by itself; DirectIndex/RecoveredMap authority remains governed by Sections 17.31–17.33. It does remove a parser ambiguity that could otherwise create false group counts, false vector extents, or stale bindings before the first true one-instance field experiment.

[P01076 | 194284:194285 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01077 | 194285:194498 | NORMAL_TEXT]
Sources: v4nguard/tiger-parse initial 2024 vector/pointer implementation and 2025-05-24 signed-offset change; cohaereo/alkahest prebl-0.5 Cargo.toml and map loader. All are remote public source observations only.

[P01078 | 194498:194499 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01079 | 194499:195096 | NORMAL_TEXT]
2026-08-20 — SOURCE-DERIVED research update: recovered the exact Tiger 64-bit vector envelope formula and the exact DataResource ResourcePointer target/type-word formula used by the pre-BL tooling lineage. Corrected the stale statement that Shadowkeep vector counts are inherently signed, added a fail-closed vector attestation contract including duplicated-count validation and zero-count behavior, and made the Section 17.32 row bridge / Section 17.24 collision pointer provenance byte-exact. No repository files, DLLs, package files, or running Destiny process were changed by this research pa

[P01080 | 195096:195097 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01081 | 195097:195202 | NORMAL_TEXT]
17.35 Source-Derived Optional Bounds-Map Semantics and Shadowkeep +0x20 Diagnostic Contract — 2026-08-20

[P01082 | 195202:195671 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from remote public cohaereo/alkahest current static schema/render code and the 2026-01-23 granular-static-culling lineage. It does not infer unpublished local Izanami source, supersede FIELD-TESTED Tower results, or turn the Post-BL +0x20 byte offset into a Shadowkeep contract. It narrows how Izanami should interpret any raw-attested mapping candidate if the installed Shadowkeep payload actually contains one.

[P01083 | 195671:196594 | NORMAL_TEXT]
EXACT LATER-LINEAGE OPTIONAL-MAP SEMANTICS. Current Alkahest SStaticMeshInstances 0x808093AD places transform_to_bounds_index at +0x20. StaticInstancesRenderer::load processes each authoritative instance-group range [instance_start, instance_start+instance_count), resolves that same transform range, then resolves one culling bound per transform as follows: if transform_to_bounds_index is empty, boundsIndex = transformIndex; otherwise boundsIndex = transform_to_bounds_index[transformIndex]. The renderer rejects an invalid transform range, missing mapping element, or out-of-range bounds index rather than partially falling back to DirectIndex. It unions the resolved per-instance bounds into group_bounds, and visibility proceeds collection bounds -> group bounds -> individual bounds. This is an exact later-lineage semantic model, not merely evidence that transforms and bounds happen to be stored in similar order.

[P01084 | 196594:197444 | NORMAL_TEXT]
SHADOWKEEP DIAGNOSTIC NARROWING. Keep the Shadowkeep byte-offset rule unchanged: do not assume 0x8080966D has the Post-BL vector at +0x20. However, when the read-only Tower parser inspects raw +0x20..+0x3F, the first explicit-map hypothesis should now be LaterLineageOptionalBoundsMap rather than an arbitrary u32 permutation. A candidate Tiger Vec<u32> must first pass the Section 17.34 vector contract and source fingerprinting. If its count is zero, treat that as semantically equivalent to the later DirectIndex branch. If nonzero, it must cover every transform index referenced by the authoritative 0x80807190 ranges being evaluated; for an ExactPartition collection the clean expected coverage is the full transforms.Count. Every referenced value must be < bounds.Count. Never use DirectIndex as a per-element fallback for a short/nonzero map.

[P01085 | 197444:198087 | NORMAL_TEXT]
IDENTITY / DEGENERATE MAP RULE. A nonempty identity vector is semantically equivalent to DirectIndex and does not create independent mapping authority. Constant, all-zero, out-of-range, or partial-coverage vectors remain AuxiliaryLikely/Unknown unless native consumer evidence proves otherwise. For a genuinely non-identity candidate, require the mapped geometry correlation and group-range union correlation to explain the decoded bounds materially better or more uniquely than DirectIndex before classifying it CorrelatedMap. This preserves the Section 17.33 false-positive guard while testing a much more specific recovered consumer model.

[P01086 | 198087:198844 | NORMAL_TEXT]
PLACEMENT-CATALOG / BINDING ADDITIONS. Add boundsMapMode = Unknown | DirectIndexCandidate | LaterLineageOptionalMapCandidate | RawMappingStructureAttested | FieldProvenDirectIndex; mappingVectorHeaderOffset; mappingVectorCount; mappingCoverageMaxTransform; mappingOutOfRangeCount; mappingIdentityRate; mappingReverseRefHistogram; directIndexCorrelationScore; mappedCorrelationScore; mappedMinusDirectScore; and mappingSourceFingerprint. Keep boundsMappingEvidence separate from map mode. A raw-attested nonempty vector may become write provenance only under the exact source/layout/tag/group-topology/bounds-resource fingerprint that validated it; an empty/identity case still requires the DirectIndex field-proof authority gate described in Section 17.31.

[P01087 | 198844:199665 | NORMAL_TEXT]
IMPLEMENTATION CONSEQUENCE — REVISED BY SECTION 17.36. The Shadowkeep culling diagnostician should use DirectIndex as the primary historical-continuity fast path after raw +0x18 bounds-resource attestation, group/bounds coverage validation, and the existing per-instance/group-union geometry correlation. Do not parse +0x20..+0x3F for a mapping vector as a default parallel step. Inspect that region only if DirectIndex evidence is contradictory/weak or the raw bytes independently attest a compelling Tiger Vec<u32>; any nonempty candidate must then obey the exact later optional-map semantics above and materially outperform DirectIndex before RawMappingStructureAttested is possible. Persistent write authority remains unchanged: DirectIndex still requires the isolated field proof under the exact source fingerprint.

[P01088 | 199665:200207 | NORMAL_TEXT]
EDITOR/TOOLING NOTE. Alkahest's 2024 individual-static move/rotate/scale feature updates its own ECS child transforms and renderer constant buffers; it is an editor/runtime-renderer architecture example only. It does not prove Destiny package write semantics, culling mutation, or collision ownership. Izanami should keep the same conceptual separation: editable Forge scene intent may change immediately, while PackagePlacementBinding remains source-attested and reports Requires Build/Reload until the package-backed field result succeeds.

[P01089 | 200207:200595 | NORMAL_TEXT]
Sources: cohaereo/alkahest current crates/data/tfx/features/statics.rs and crates/render/src/feature/static_geometry.rs at commit b140945588717ce75218ff48e15674a6655431d7; granular static instance culling commit fc7749695422fbd5acad27ec6d50bce1f306467c; individual-static editor transform commit 06a6f3e0dc05a4acca4795e55805210164aafcda. These are remote public source observations only.

[P01090 | 200595:201209 | NORMAL_TEXT]
2026-08-20 — SOURCE-DERIVED research update: recovered the exact later-lineage optional transform-to-bounds consumer contract: an empty mapping means direct transform index, while a nonempty mapping must supply the bounds index for every referenced transform and invalid/missing elements do not fall back individually. Narrowed the Shadowkeep +0x20 diagnostic to this explicit optional-map hypothesis, added coverage/identity/semantic-gain gates, and kept the Post-BL byte offset version-scoped. No unpublished local Izanami source, DLLs, package files, or running Destiny process were changed by this research pa

[P01091 | 201209:201306 | NORMAL_TEXT]
17.36 Source-Derived D2 Lightfall DirectIndex Continuity and +0x20 Backport Regrade — 2026-08-20

[P01092 | 201306:201669 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from remote public cohaereo/alkahest D2 Lightfall branch plus the current later D2 lineage. It does not infer unpublished local Izanami source, supersede any FIELD-TESTED Tower result, or prove native Shadowkeep culling behavior. It materially changes the priority of the read-only bounds-index diagnostic.

[P01093 | 201669:202492 | NORMAL_TEXT]
D2 LIGHTFALL DIRECT-INDEX CONTINUITY. The public Alkahest lightfall branch models its D2 static-instances collection with an occlusion-bounds resource, transforms, statics, and instance groups but no transform_to_bounds_index vector. More importantly, its map loader takes each authoritative group range [instance_start, instance_start + instance_count) and slices BOTH the transforms array and the occlusion-bounds array with that identical range before constructing the instanced renderer. If the requested group range exceeds the available bounds array, the loader substitutes infinite/no-cull bounds for that group rather than looking up a remapping structure. The renderer retains the supplied bounds in the same order as the transforms. This is direct D2-lineage consumer evidence, not merely a class-layout analogy.

[P01094 | 202492:203473 | NORMAL_TEXT]
TIMELINE / EVIDENCE REGRADE. The recovered pre-Beyond-Light/Shadowkeep static schema does not expose a verified mapping vector; the D2 Lightfall branch still consumes transforms and bounds positionally by the same group range. Public Alkahest commit 8c67a03bc57b0caf9d5287eb595d5701fc655603 on 2026-01-06 then added both the later +0x20 transform_to_bounds_index field and the consumer that implements empty=DirectIndex / nonempty=mapping[transformIndex] as part of the same static-frustum-culling change. That commit date is tool/reverse-engineering provenance only, not a claim about when Destiny's native format changed. The strongest source-derived interpretation remains that explicit remapping belongs to a later D2 tooling/layout lineage. This does NOT prove Shadowkeep native Destiny uses DirectIndex, but it makes DirectIndex the historically continuous primary experiment hypothesis and keeps +0x20 mapping-vector discovery as fallback rather than parallel/default work.

[P01095 | 203473:204682 | NORMAL_TEXT]
REVISED SHADOWKEEP DIAGNOSTIC ORDER. For installed Tower payload 0x80ED22F9: (1) raw-attest +0x18 as TagHash -> SOcclusionBounds 0x80809671 and validate the 0x80809673 / 0x30 bounds vector; (2) validate transforms, statics, 0x80807190 group topology, reverse transform ownership, selected-group bounds coverage, and collection bounds; (3) when bounds coverage/counts permit, run DirectIndex per-instance plus authoritative group-range union correlation in both culling-space hypotheses; (4) if those tests are coherent, classify boundsIndexModelEvidence = D2LightfallDirectIndexContinuity + SameEraParallelArrayAnalogy + LocalDirectIndexCorrelation and arm ONLY the isolated one-instance field experiment; (5) inspect raw +0x20..+0x3F for a Tiger Vec<u32> mapping only if DirectIndex correlation is contradictory/weak or the raw bytes independently form a compelling structurally valid vector. A nonempty recovered vector must then satisfy the exact later optional-map semantics and beat DirectIndex geometrically before it can become RawMappingStructureAttested. General editor writes still require FieldProvenDirectIndex or an independently attested recovered map under the exact source/layout fingerprint.

[P01096 | 204682:205093 | NORMAL_TEXT]
FALSE-POSITIVE / BYTE-PRESERVATION GUARD. Do not search the final 0x10 bytes of each Shadowkeep 0x80809673 bounds record for mapping metadata; public bounds consumers treat those bytes as opaque while mapping, where present in later D2 layouts, is collection-level. Preserve those bytes exactly. Likewise keep +0x50..+0x57, transform +0x28/+0x2C, and collection +0x78 read-only under the prior evidence grades.

[P01097 | 205093:205509 | NORMAL_TEXT]
PLACEMENT-CATALOG ADDITIONS. Add boundsIndexContinuityEvidence with flags/values for SameEraParallelArrayAnalogy, D2LightfallDirectIndexContinuity, LaterOptionalMapEvolution, LocalDirectIndexCorrelation, and FieldProvenDirectIndex; add boundsMapSearchPolicy = FallbackAfterDirectIndexFailure by default for Shadowkeep 0x8080966D. Keep these evidence labels separate from cullingMappingMode and from write authority.

[P01098 | 205509:205801 | NORMAL_TEXT]
Sources: cohaereo/alkahest lightfall branch crates/alkahest-data/src/statics.rs, src/mapload_temporary.rs, and src/render/static_instanced.rs; current main static schema/renderer retained only for the later optional-map evolution comparison. These are remote public-source observations only.

[P01099 | 205801:206581 | NORMAL_TEXT]
2026-08-20 — SOURCE-DERIVED research update: found direct D2 Lightfall consumer evidence that static instance transforms and occlusion bounds were still sliced by the identical authoritative group range without an explicit remapping vector; insufficient bounds disable culling for the group instead of invoking a map. Regraded DirectIndex as the primary historical-continuity Shadowkeep experiment hypothesis and moved +0x20 vector discovery to a fallback after DirectIndex correlation failure or independent raw-vector attestation. Persistent write authority is unchanged: the first one-instance field proof or an exact raw mapping structure is still required. No unpublished local Izanami source, DLLs, package files, or running Destiny process were changed by this research pa

[P01100 | 206581:206582 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01101 | 206582:206689 | NORMAL_TEXT]
17.37 Source-Derived Derived-Group-Bounds Contract and Padding-Preserving Rotation/Scale Plan — 2026-08-20

[P01102 | 206689:207120 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from remote public cohaereo/alkahest current static-render/culling code and AABB utilities. It does not infer unpublished local Izanami source, supersede any FIELD-TESTED Tower result, or modify the pending group-13/entity/collision package. It narrows the mutable-resource closure for the first true StaticInstanceBinding and corrects the later rotation/scale culling plan.

[P01103 | 207120:207121 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01104 | 207121:208124 | NORMAL_TEXT]
NO SERIALIZED GROUP-AABB WRITE SEAM IS REQUIRED BY THE LATER D2 CONSUMER. Current Alkahest resolves one occlusion AABB per static transform, then computes each group_bounds at load time as the union of those resolved per-instance boxes. The collection-level culling box is separately loaded from SStaticMeshInstances.bounds. AxisAlignedBBox::Sum is explicitly implemented as repeated AABB union. The package group row itself still carries only instance_count, instance_start, static_index, and an opaque u16; it does not carry a per-group AABB. Therefore Izanami should treat group bounds as DerivedGroupBounds provenance, not as a serialized mutable field. The first translation transaction does not need to search for or patch a third group-level bounds record: after the selected per-instance AABB is changed, a consumer following this model naturally re-derives the group envelope. The only separately persistent broad envelope remains the collection AABB already covered by RawTailAabbAttestation.

[P01105 | 208124:208125 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01106 | 208125:209190 | NORMAL_TEXT]
PER-INSTANCE OCCLUSION AABBs ARE CONSUMED AS PRE-RESOLVED CULLING-SPACE BOXES IN THE LATER D2 RENDERER. The same renderer stores instance transforms and culling bounds separately. Instance scale/rotation/translation is written into the GPU instance constant buffer, while collection, derived group, and individual visibility tests consume the AABBs directly; there is no culling-stage multiplication of each AABB by its SStaticInstanceTransform. This is strong later-lineage evidence that moving a transform alone cannot implicitly move its culling box. For a translation-only experiment in one proven culling space, the narrow candidate operation is exactly B1.min.xyz = B0.min.xyz + delta and B1.max.xyz = B0.max.xyz + delta, preserving both W lanes and the opaque 0x10-byte record tail. This remains an experiment hypothesis for Shadowkeep until the exact Tower fingerprint passes the DirectIndex/RecoveredMap gate and field test, but it strengthens the existing same-delta contract and explains why no additional group-AABB edit belongs in the mutable closure.

[P01107 | 209190:209191 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01108 | 209191:210483 | NORMAL_TEXT]
ROTATION/SCALE SHOULD PRESERVE AUTHORED CULLING MARGIN INSTEAD OF TREATING THE RAW AABB AS MESH-LOCAL. Once translation is FIELD-PROVEN, compute a predicted source render AABB G0 from decoded source mesh geometry, ModelTransform, and the source 0x808071A3 instance transform in the attested culling space. Compare it to the raw source occlusion bound B0. When B0 conservatively contains G0 within tolerance, derive directional authoring slack: padLow = G0.min - B0.min and padHigh = B0.max - G0.max, clamped only for tiny numerical error. For a proposed target rotation/positive uniform scale, compute target render AABB G1 from geometry under the target transform, then form the first culling candidate as B1.min = G1.min - padLow and B1.max = G1.max + padHigh. This preserves the source asset's authored culling margin instead of rotating an already axis-aligned, already-resolved box around an assumed pivot. If B0 does not contain G0 coherently, set rotationScaleBoundsMode = Unknown and keep rotation/scale writes disabled. Transforming the eight corners of B0 through a relative delta can remain a conservative diagnostic/fallback envelope, but it is no longer the preferred semantic model. For pure translation, this padding construction collapses to the same exact B0 + delta result.

[P01109 | 210483:210484 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01110 | 210484:211374 | NORMAL_TEXT]
MUTABLE-CLOSURE / CATALOG CONSEQUENCE. For the first true Shadowkeep translation proof, the culling-related writable closure remains {one 0x808071A3 Position XYZ, its independently proven 0x80809673 AABB XYZ, the independently raw-attested collection AABB when expansion is required}. There is no separate group-bounds package write under the recovered model. AO/opaque fields remain byte-identical and collision remains a separate CollisionPlacementBinding acceptance signal. Add read-only derivedGroupBounds, groupBoundsProvenance = DerivedUnion, sourcePredictedRenderAabb, sourceCullingPadLow/sourceCullingPadHigh, cullingPaddingValid, and rotationScaleBoundsMode = Unknown | PaddingPreservedGeometryAabbCandidate | FieldProven to PlacementCatalog/StaticInstanceBinding diagnostics. Do not serialize DerivedGroupBounds as native source bytes or include it in a source-block fingerprint.

[P01111 | 211374:211375 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01112 | 211375:211916 | NORMAL_TEXT]
IMPLEMENTATION ORDER. Keep DirectIndex correlation and raw collection-bounds attestation as the immediate read-only gate. Once one translation succeeds, use the padding-preserving geometry-derived AABB model for the first isolated rotation test, while rotationConvention remains Unresolved as documented in Section 17.31. Only after rotation direction and culling both pass should positive uniform scale use the same model. This keeps translation, quaternion convention, scale, and culling-envelope semantics as separate native assumptions.

[P01113 | 211916:211917 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01114 | 211917:212177 | NORMAL_TEXT]
Sources: cohaereo/alkahest current crates/render/src/feature/static_geometry.rs and crates/data/tfx/common.rs at commit b140945588717ce75218ff48e15674a6655431d7; 2025-12-14 robustness commit f6ffe808f6ad0082e099e50de7cb47c272b8527d. Remote public source only.

[P01115 | 212177:212178 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01116 | 212178:212920 | NORMAL_TEXT]
2026-08-20 — SOURCE-DERIVED research update: current Alkahest confirms that group bounds are runtime-derived unions of resolved per-instance AABBs while the collection bound is separately stored, so Izanami does not need or want a serialized group-AABB mutation seam. The renderer also consumes occlusion AABBs directly rather than transforming them by each instance SRT, strengthening exact same-delta AABB translation and correcting the post-translation rotation/scale plan: derive target bounds from target mesh geometry while preserving measured source culling padding instead of blindly rotating the old resolved AABB. No unpublished local Izanami source, DLLs, package files, or running Destiny process were changed by this research pa

[P01117 | 212920:212921 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01118 | 212921:213017 | NORMAL_TEXT]
17.38 Source-Derived Same-Era Mesh-Local Transform and Quaternion-Convention Split — 2026-08-20

[P01119 | 213017:213397 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from remote public cohaereo/alkahest prebl-0.5 source. It does not infer unpublished local Izanami source, supersede FIELD-TESTED Tower results, or modify the pending group-13/entity/collision diagnostic package. It refines the read-only geometry-correlation contract used before the first true StaticInstanceBinding write.

[P01120 | 213397:215846 | NORMAL_TEXT]
SAME-ERA MESH-LOCAL TRANSFORM IS PART OF THE STATIC RENDER PATH, AND ITS PRE-BL TOOL OFFSETS ARE NOW EXPLICIT. prebl-0.5 SStaticMesh 0x808071A7 exposes its opaque_meshes child Tag at +0x8 under the branch's sequential Tiger layout, then mesh_offset as Vec3 at +0x60 and mesh_scale as f32 at +0x6C. Its static renderer passes mesh_offset/mesh_scale into ScopeInstances for every instanced model. ScopeInstances constructs a mesh-local scale/offset matrix and composes it with each instance transform before writing the static instance constants. This independently corroborates the Charm ModelTransform evidence already used in Sections 17.22/17.27, but now from a same-era pre-Beyond-Light renderer with byte-addressable provenance. StaticBoundsCorrelation must raw-attest and fingerprint the selected mesh's +0x60..+0x6F bytes, resolve the +0x8 opaque-mesh-data child, and apply mesh_offset/mesh_scale before comparing predicted geometry against 0x80809673 occlusion bounds. Add opaqueMeshDataTag, meshOffset, meshScale, meshLocalTransformFingerprint, and anchorToGeometryOffset to PlacementCatalog provenance. An instance Position that does not coincide with the visible mesh center is not by itself a parser error.RENDER-COVERAGE REFINEMENT. StaticBoundsCorrelation must also record whether its predicted geometry is render-complete for the selected static. In same-era prebl-0.5, SStaticMesh carries both opaque_meshes and special_meshes; StaticModel::draw binds one shared instance scope and instance count, draws the highest-detail opaque groups, then draws highest-detail special meshes (transparent/decal/light-shaft/etc. stages) through the same instance transform. Therefore an opaque-only geometry AABB can be a useful lower bound but is not sufficient by itself to declare a transform↔occlusion-bound mismatch when special meshes exist. Add specialMeshCount, specialRenderStages, geometryCoverageMode={OpaqueOnly, OpaquePlusSpecial, SpecialPresentUnresolved}, and geometryCoverageComplete to PlacementCatalog provenance. For the first true one-instance field proof, prefer a static with specialMeshCount==0. If special meshes are present, either decode their position-bearing buffers into the predicted render union or keep DirectIndex correlation below HighConfidence until the missing render coverage is resolved. This is SOURCE-DERIVED tooling evidence, not a claim that native Destiny computes its authored AABB from those vertices.

[P01121 | 215846:215847 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01122 | 215847:215848 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01123 | 215848:216604 | NORMAL_TEXT]
SAME-ERA INSTANCE SRT PATH USES THE STORED QUATERNION DIRECTLY IN prebl-0.5. The prebl-0.5 map loader converts each Shadowkeep 0x808071A3 record into an editor Transform with translation = stored translation, rotation = stored quaternion, and uniform scale = Scale.x. Transform::local_to_world() then calls Mat4::from_scale_rotation_translation(scale, rotation, translation) without quaternion inversion. This conflicts with the older prebl-old-0.1 renderer noted in Section 17.31, which applied .inverse(). Alkahest's own branch-to-branch disagreement therefore makes the direct-vs-inverse issue a tool/convention-evolution problem rather than evidence that the package bytes themselves differ. Keep rotationConvention = Unresolved for package authoring.

[P01124 | 216604:217295 | NORMAL_TEXT]
READ-ONLY QUATERNION CORRELATION MODE. For StaticBoundsCorrelation, add quaternionCorrelationMode = DirectStored | InverseStored | Unknown and score both conventions while holding the same raw mesh geometry, mesh_offset/mesh_scale, Scale.x, Position, group range, culling-space hypothesis, and bounds resource fixed. prebl-0.5 makes DirectStored the preferred same-era tool hypothesis, while prebl-old-0.1 remains a historical alternate. Persist the score margin and selected diagnostic mode, but do not promote the better geometric fit into rotation write authority. Rotation remains a separate post-translation field experiment using one isolated instance and an unmistakable known angle.

[P01125 | 217295:218263 | NORMAL_TEXT]
IMPLEMENTATION CONSEQUENCE. The predicted source render AABB used by DirectIndex correlation should be derived from the actual static mesh after its mesh-local offset/scale, then evaluated under both quaternion-correlation modes and the source instance Scale.x/Position. Candidate ranking can use anchorToGeometryOffset and predicted world-space center to favor visually distinctive isolated instances and avoid mistaking a large mesh-local pivot offset for a bad transform. This finding does not change the current group-13/entity/collision diagnostic package and does not justify a rebuild. The first true per-instance proof remains unchanged: start from unprojected source topology, preserve every vector/group row and size, change one 0x808071A3 Position XYZ, shift only its evidence-proven 0x80809673 AABB by the same delta, conservatively expand independently attested collection bounds, and evaluate visual motion, multi-view culling, and collision separately.

[P01126 | 218263:218563 | NORMAL_TEXT]
Sources: cohaereo/alkahest prebl-0.5 crates/alkahest-data/src/statics.rs, crates/alkahest-renderer/src/loaders/map.rs, crates/alkahest-renderer/src/ecs/render/static_geometry.rs, crates/alkahest-renderer/src/ecs/transform.rs, and crates/alkahest-renderer/src/tfx/scope.rs. Remote public source only.

[P01127 | 218563:219356 | NORMAL_TEXT]
2026-08-20 — SOURCE-DERIVED research update: found independent same-era pre-Beyond-Light renderer evidence that SStaticMesh mesh_offset/mesh_scale participate directly in the static-instance render transform, making them mandatory provenance for bounds correlation rather than optional preview metadata. The same branch passes the stored 0x808071A3 quaternion directly into scale/rotation/translation matrix construction, while an older Alkahest branch used quaternion inverse. Regraded the quaternion discrepancy as a branch/tool convention split: DirectStored and InverseStored should both be scored read-only, while package rotation stays Unresolved until a field test. No unpublished local Izanami source, DLLs, package files, or running Destiny process were changed by this research pass

[P01128 | 219356:219357 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01129 | 219357:219468 | NORMAL_TEXT]
17.39 Source-Derived Exact Parent→Static-Collection Tag Edge and Shadowkeep Spawn-Placement Chain — 2026-08-20

[P01130 | 219468:219469 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01131 | 219469:219923 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from remote public cohaereo/alkahest prebl-0.5 source at branch head 7455ab2db8ac0ef77789b27ab630850d7d810227. It does not infer unpublished local Izanami source, supersede any FIELD-TESTED Tower result, or modify the pending group-13/entity/collision package. It makes one previously broad identity seam byte-exact and records a secondary same-era spawn-placement chain for the read-only catalog.

[P01132 | 219923:219924 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01133 | 219924:220874 | NORMAL_TEXT]
0x80806EF4 CHILD EDGE IS BYTE-EXACT IN THE PRE-BL TOOLING MODEL. prebl-0.5 defines SUnk80806EF4 as a 0x24-byte parent/wrapper containing an initial u64 at +0x0 followed immediately by instances: Tag<SStaticMeshInstances>. The same branch's Tag<T> reader consumes exactly one raw TagHash on disk and resolves that identity through the package manager; it is not a ResourcePointer. Therefore the source-derived child edge is parent-relative +0x8: raw TagHash at parent+0x8 -> SStaticMeshInstances 0x8080966D. Combined with the already recovered row ResourcePointer contract, the complete Shadowkeep static identity chain is now byte-exact in public tooling: SMapDataTable/SMapDataTableEntry -> DataResource ResourcePointer -> resolvedTarget+0x10 raw parent TagHash -> 0x80806EF4 parent -> parent+0x8 raw static-instances TagHash -> 0x8080966D payload. Installed Tower bytes must still raw-attest every tag/class before this becomes binding provenance.

[P01134 | 220874:220875 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01135 | 220875:221801 | NORMAL_TEXT]
MUTABLE-CLOSURE CONSEQUENCE. The first true StaticInstanceBinding translation should treat the map-row DataResource, the target+0x10 parent TagHash, the 0x80806EF4 wrapper, and its parent+0x8 child TagHash as READ-ONLY identity/provenance. Fingerprint the complete 0x24 parent wrapper plus the exact child tag. Add parentTagRaw, parentInstancesTagRaw, parentInstancesTagOffset = 0x8, parentRaw24Fingerprint, and rowToStaticChainFingerprint to the placement catalog/binding. Resolution fails closed if the wrapper or child TagHash changes. A translation-only per-instance proof therefore does not need to rewrite this routing seam; after the independent culling gate graduates, its mutable package closure remains the 0x8080966D transform/collection-bounds bytes plus the separately routed 0x80809671 per-instance bounds resource. This removes same-class-parent ambiguity without adding another native assumption to the write.

[P01136 | 221801:221802 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01137 | 221802:222753 | NORMAL_TEXT]
SAME-ERA SPAWN-PLACEMENT CHAIN IS NOW CONCRETE ENOUGH FOR A SECONDARY READ-ONLY CATALOG. The maintained prebl-0.5 map loader recognizes DataResource.resource_type 0x80809160 as a spawn-points path. It uses the same resolvedTarget+0x10 raw TagHash seam and resolves SSpawnPoints 0x80809162. The source schema defines SSpawnPoints as a file-size/header value followed by a Tiger vector of SSpawnPoint 0x80809164 records. Each SSpawnPoint is 0x30 bytes in the recovered layout: quaternion rotation at +0x0, Vec4 translation at +0x10, u32 unk20 at +0x20, and twelve probable padding/unknown bytes at +0x24. The loader materializes each spawn node from translation.xyz and the stored quaternion. Add a read-only SpawnPlacementCatalog row containing table/row identity, ResourcePointer provenance, raw spawn-header TagHash/class, vector-header attestation, spawn index, raw 0x30 fingerprint, rotation, translation.xyz, translation.w, and unk/padding bytes.

[P01138 | 222753:222754 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01139 | 222754:223469 | NORMAL_TEXT]
SPAWN WRITE GATE. A future first spawn-placement experiment should be translation-only: change SSpawnPoint.translation.xyz while preserving translation.w, quaternion, unk20, and all trailing bytes. Do not infer native world-space composition merely because the public loader creates the preview/editor node directly from the child spawn transform; the tool path shown does not establish whether native Destiny composes an outer SMapDataEntry transform. Keep spawnOuterComposition = Unknown until an installed-resource comparison or field test proves it. Spawn placement is secondary to the current static-instance/culling milestone and should not trigger a rebuild of the pending group-13/entity/collision package.

[P01140 | 223469:223470 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01141 | 223470:224067 | NORMAL_TEXT]
IMPLEMENTATION ORDER. Fold parent+0x8 raw attestation into the existing Shadowkeep PlacementCatalog first because it is a low-risk resolver/fingerprint improvement and directly strengthens ForgeUUID -> PackagePlacementBinding identity. Keep the primary work on raw +0x18 culling-resource attestation, DirectIndex correlation, collection-bounds attestation, and the unprojected one-instance translation proof. Add the spawn chain read-only in parallel when useful for blank-world arrival alignment; do not claim editable spawn placement until its own package-backed field acceptance signal exists.

[P01142 | 224067:224068 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01143 | 224068:224303 | NORMAL_TEXT]
Sources: cohaereo/alkahest prebl-0.5 crates/alkahest-data/src/map.rs, crates/alkahest-data/src/tag.rs, and crates/alkahest-renderer/src/loaders/map.rs at branch head 7455ab2db8ac0ef77789b27ab630850d7d810227. Remote public source only.

[P01144 | 224303:224304 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01145 | 224304:225058 | NORMAL_TEXT]
2026-08-20 — SOURCE-DERIVED research update: made the Shadowkeep map-row -> parent -> static-collection identity seam byte-exact in public pre-BL tooling: the 0x80806EF4 wrapper's static-instances TagHash sits at parent+0x8 and Tag<T> is a raw TagHash rather than another ResourcePointer. Added fail-closed parent-wrapper/child-tag fingerprints and kept the routing seam read-only for the first true per-instance translation. Also recovered a same-era spawn chain (DataResource 0x80809160 -> SSpawnPoints 0x80809162 -> SSpawnPoint 0x80809164 / 0x30) suitable for a read-only SpawnPlacementCatalog and a later XYZ-only spawn experiment. No unpublished local Izanami source, DLLs, package files, or running Destiny process were changed by this research pa

[P01146 | 225058:225059 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01147 | 225059:225175 | NORMAL_TEXT]
17.40 Source-Derived Exact Shadowkeep Mesh-Local Byte Contract and Culling-Map Tool-History Provenance — 2026-08-20

[P01148 | 225175:225176 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01149 | 225176:225627 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. This section is SOURCE-DERIVED from remote public cohaereo/alkahest prebl-0.5 source plus public Alkahest commit history. It does not infer unpublished local Izanami source, supersede FIELD-TESTED Tower results, or modify the pending group-13/entity/collision diagnostic package. It makes the selected-static-mesh side of StaticBoundsCorrelation byte-exact and sharpens the evidence grade of the later +0x20 bounds-map model.

[P01150 | 225627:225628 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01151 | 225628:226564 | NORMAL_TEXT]
BYTE-EXACT PRE-BL STATIC-MESH LOCAL TRANSFORM. In prebl-0.5, SStaticMesh 0x808071A7 is laid out sequentially with its opaque_meshes Tag<SStaticMeshData> at +0x8, then later mesh_offset as Vec3 at +0x60 and mesh_scale as f32 at +0x6C; the referenced opaque mesh-data class is 0x80807194. These offsets follow from the branch's concrete field order and Tiger serialized sizes, not from the newer Post-BL static layout. For a selected 0x80807190 group, PlacementCatalog should raw-attest Statics[StaticIndex] -> class 0x808071A7, raw-read/fingerprint the mesh's +0x8 child tag and +0x60..+0x6F local-transform bytes, resolve the child as 0x80807194, and require finite mesh_offset/mesh_scale before geometry correlation. Preserve these bytes read-only in the first per-instance translation. Add staticMeshLayoutMode = PreBL_808071A7, opaqueMeshDataTag, meshOffsetRaw, meshScaleRaw, and meshLocalTransformFingerprint to binding provenance.

[P01152 | 226564:226565 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01153 | 226565:227730 | NORMAL_TEXT]
SAME-ERA RENDER COMPOSITION IS NOW EXACT AT THE PUBLIC-TOOL LEVEL. prebl-0.5 ScopeInstances receives mesh_offset/mesh_scale separately from each instance Transform. Transform::local_to_world() builds scale/rotation/translation from the stored instance values; create_instances_scope transposes that affine matrix, ScopeInstances builds the correspondingly transposed mesh-local scale/offset matrix, and multiplies model_transform * instance_transform before writing the instance constants. In conventional column-vector form that transposed packing is equivalent to M_instance * M_mesh, where M_mesh applies mesh_scale then mesh_offset. Under the DirectStored quaternion diagnostic mode, the source-derived point formula is therefore p_render = Position + Scale.x * R(storedQuaternion) * (mesh_scale * p_raw + mesh_offset). This upgrades the mesh/instance composition used by StaticBoundsCorrelation from exporter-style inference to an exact same-era Alkahest renderer contract. It still does NOT make DirectStored a native Destiny quaternion write convention; the older branch inversion evidence remains, so rotation authoring stays Unresolved until field-tested.

[P01154 | 227730:227731 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01155 | 227731:228654 | NORMAL_TEXT]
PUBLIC TOOL-HISTORY PROVENANCE FOR THE OPTIONAL BOUNDS MAP. Alkahest commit 8c67a03bc57b0caf9d5287eb595d5701fc655603 on 2026-01-06 added the +0x20 transform_to_bounds_index Vec<u32> field and the renderer consumer that interprets empty = DirectIndex and nonempty = mapping[transformIndex] in the same static-frustum-culling change. This is useful chronology of Alkahest's reverse-engineering/tool implementation, NOT evidence that Destiny's game format introduced the field in 2026. Combined with pre-BL tooling lacking a static-bounds consumer and the D2 Lightfall branch still using positional same-range bounds, it strengthens the existing policy: for Shadowkeep 0x8080966D, run raw +0x18 attestation and DirectIndex correlation first; inspect +0x20..+0x3F only as fallback or when the bytes independently attest a valid Tiger vector. Do not import the later +0x20 offset into the Shadowkeep writer by chronology alone.

[P01156 | 228654:228655 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01157 | 228655:229395 | NORMAL_TEXT]
IMPLEMENTATION-ORIENTED CORRELATION PIPELINE. For each candidate: validate group range and single transform ownership -> resolve Statics[StaticIndex] -> attest 0x808071A7 mesh identity and +0x8 opaque-data child -> decode source geometry -> apply raw-attested +0x60/+0x6C mesh-local transform -> apply DirectStored and InverseStored instance hypotheses using the same Scale.x/Position -> compute predicted AABB -> compare against the raw-attested 0x80809671/0x80809673 bounds under CollectionLocal and OuterComposed culling-space hypotheses. Record the chosen diagnostic mode and score margins, but keep write authority separate. A malformed mesh-local seam is a hard parser/binding failure, not a reason to compensate the Forge transform.

[P01158 | 229395:229396 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01159 | 229396:230049 | NORMAL_TEXT]
FIRST WRITE CONTRACT REMAINS UNCHANGED. This finding does not add any mutable byte seam. The true acceptance test still starts from unprojected source topology, preserves every vector/group row and size plus all mesh-local bytes, changes exactly one 0x808071A3 Position XYZ, shifts only its evidence-selected 0x80809673 AABB XYZ by the same delta, conservatively expands independently raw-attested collection bounds, and scores render movement, multi-view culling, and collision independently. General Forge writes still require FieldProvenDirectIndex or an independently attested recovered map under the exact source/layout/resource/route fingerprint.

[P01160 | 230049:230050 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01161 | 230050:230744 | NORMAL_TEXT]
2026-08-20 — SOURCE-DERIVED research update: made the selected Shadowkeep static mesh's local transform byte-exact in the pre-BL tooling model (0x808071A7 opaque mesh-data tag at +0x8, mesh_offset +0x60, mesh_scale +0x6C) and traced the same-era renderer's transposed constant packing to the conventional composition M_instance * M_mesh. Also pinned Alkahest's explicit +0x20 transform-to-bounds map and its consumer to the same 2026-01-06 public tool commit, strengthening the evidence that this is a later tool/layout interpretation rather than Shadowkeep write authority. No unpublished local Izanami source, DLLs, package files, or running Destiny process were changed by this research pa.

[P01162 | 230744:230745 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01163 | 230745:230835 | HEADING_2]
17.24 Validated Flat-Surface, Entity-Quarantine, and Collision-Disconnect Field Candidate

[P01164 | 230835:231252 | NORMAL_TEXT]
STAGING RESULT. The in-game Build Blank World Draft pass completed successfully. The guarded plan traversed 813 nodes and 161 map tables, touched 34 local tables, applied 13 explicit static-placement edits, suppressed 227 Tower-local entity rows, disconnected 6 world-collision rows, and authored 32 changed package blocks. The local payload isolation accepted group 13 and completed without package or Oodle errors.

[P01165 | 231252:231253 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01166 | 231253:231682 | NORMAL_TEXT]
INDEPENDENT GRAPH VALIDATION. A separate tiger-pkg read of an isolated staged package set decrypted and decompressed the authored graph. Payload 0x80ED22F9 still contains 1,057 transforms and 260 statics, while exposed group 0 is exactly one instance starting at transform 122, static index 13, mesh 0x815B621C, flags 0x0007. The active aggregate row is identity rotation with translation (82.790, 42.272, 10.525) and scale 1.0.

[P01167 | 231682:231683 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01168 | 231683:232238 | NORMAL_TEXT]
ENTITY AND COLLISION VALIDATION. The live reachable graph reports all 227 Tower-local null-resource entity rows at scale 0.0001. All six identified collision tables (0x80ED2270, 0x80ED25AF, 0x80ED266E, 0x80ED29F4, 0x80ED2CC2, and 0x80ED3976) have null resource pointers and scale 0.0001. Resource class 0x80807246 is absent from the reachable resource-class report. The six disconnected collision rows are consequently counted among 271 null-resource entity-class rows by the diagnostic reader; this is expected reclassification, not an extra entity set.

[P01169 | 232238:232239 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01170 | 232239:232712 | NORMAL_TEXT]
BLOCK AND OWNER VALIDATION. Five package headers passed version, package id, patch id, stored-size, table-bound, and nonzero-count checks. The patch-8 entry table is unchanged from the clean baseline. Exactly 32 patch-8 block rows differ; owner distribution is patch 2: 4, patch 3: 14, patch 4: 2, patch 5: 11, patch 8: 1. Every changed latest row is byte-identical to its physical-owner row, uses flags 0x3, addresses an in-bounds body, and has a matching recorded SHA-1.

[P01171 | 232712:232713 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01172 | 232713:233278 | NORMAL_TEXT]
PROMOTED LIVE HASHES. Patch 2 = 40A0B3AE0AF251471C26E17179A932EAFA65F5583EC6F8E491BDD57387A3179D; patch 3 = 7CAE633EFC40D876BCDA18CF3303E755A63E9D5E47863A8772E2F4502B187F0A; patch 4 = 0AB15EB2924DBDF10EE949BA928F283779F0C058CE2254FBEAA22A9A93A63FBB; patch 5 = 1805BB5DE3E39765F5D71E6D190B1AE15B7F60247E7E18AF6AC52D89D04316D5; patch 8 = B6B43AD47B065F662542FDF93D6285B9F7B62A372705A5FDDD7A1E8634BC61D1. Every live file is now an independent single-link file, and a second tiger-pkg pass against the actual live package directory reproduced the staged graph exactly.

[P01173 | 233278:233279 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01174 | 233279:233789 | NORMAL_TEXT]
FILESYSTEM RECOVERY NOTE. The first isolated validation directory used hardlinks. Overwriting its package names caused the staged bytes to become active before the planned promotion. Destiny was closed, and no field launch occurred in that state. After all graph and block checks passed, the active names were replaced with independent copies and the linked paths were retained under explicit diagnostic suffixes. The validated candidate is archived under .izanami-pending-field-flat-surface-entity-collision.

[P01175 | 233789:233790 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01176 | 233790:234419 | NORMAL_TEXT]
ROLLBACK CAVEAT. Exact clean rollback copies remain for patches 3, 4, 5, and 8. The previous byte-identical patch-2 file (recorded SHA-256 554318600690535FF22757FC63F8485EBA7C27084106C2E5FCCC61594A579C7B) was part of the hardlink set and cannot be reproduced exactly from the later patch-8 owner metadata. Its original block bodies remain intact in the explicit .izanami-rollback-body-carrier-before-flat-surface-field copy, so restoring the clean patch-8 metadata remains an operational rollback. A byte-identical previous patch-2 file would require restoration from an external pristine installation or integrity verification.

[P01177 | 234419:234420 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01178 | 234420:234972 | NORMAL_TEXT]
NEXT FIELD TEST. Launch Destiny without rebuilding or pressing Build Blank World Draft again. From orbit, select Tower Carrier Control and press Launch In Destiny once. Check whether the stair assembly is replaced by a simple surface, whether loose props disappear, and whether phantom walls disappear. Falling through the world is an acceptable and expected diagnostic outcome because this pass deliberately disconnects all discovered world-collision resources; a controlled collision plane is the next implementation if that ownership test succeeds.

[P01179 | 234972:234973 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01180 | 234973:234974 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01181 | 234974:234975 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01182 | 234975:234976 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01183 | 234976:235072 | NORMAL_TEXT]
17.41 Source-Derived Typed Tiger Vector Envelope Attestation for Shadowkeep Bounds — 2026-08-20

[P01184 | 235072:235073 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01185 | 235073:235240 | NORMAL_TEXT]
Classification: SOURCE-DERIVED parser/layout evidence. This section does not upgrade transform→bounds indexing, package write authority, or any runtime-editing claim.

[P01186 | 235240:235241 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01187 | 235241:235258 | NORMAL_TEXT]
Why this matters

[P01188 | 235258:235769 | NORMAL_TEXT]
The first true StaticInstanceBinding currently depends on raw-attesting the Shadowkeep 0x8080966D +0x18 candidate occlusion tag before any one-instance AABB write. Public same-era parser code now gives a substantially stronger fail-closed test for the resource behind that tag: not just “the resolved entry class is 0x80809671,” but a typed Tiger vector envelope whose duplicate count, element-class marker, element start, record width, and logical extent can all be checked before geometry correlation begins.

[P01189 | 235769:235770 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01190 | 235770:235795 | NORMAL_TEXT]
Same-era parser evidence

[P01191 | 235795:236538 | NORMAL_TEXT]
Alkahest prebl-0.5 declares tiger-parse 0.1.12 with check_types, check_types_strict, and check_types_debug enabled. The public tiger-parse source at the immediately following 0.1.13 version bump uses the same vector implementation as the pre-bump 0.1.12 state because that bump changes only Cargo version metadata. For a nonempty Vec<T> header beginning at logical offset H, the parser reads Size at H, then resolves the envelope from the relative Offset field address: E = (H + 0x8) + relativeOffset. At E it requires a duplicate Size equal to the header count. With typed checking enabled, the next u32 at E+0x8 must match T::ID. Element payload begins at E+0x10 regardle A zero-count vector returns empty before dereferencing the envelope.

[P01192 | 236538:236539 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01193 | 236539:236577 | NORMAL_TEXT]
Exact Shadowkeep bounds-resource seam

[P01194 | 236577:237226 | NORMAL_TEXT]
prebl-0.5 defines SOcclusionBounds 0x80809671 as size 0x18 with file_size:u64 followed immediately by Vec<SObjectOcclusionBounds>. Therefore the bounds vector header is source-derived at resource +0x8..+0x17. SObjectOcclusionBounds is 0x80809673 / 0x30, so a typed envelope for this vector should carry the duplicated count at E+0x0, element-class marker 0x80809673 at E+0x8 under the same-era strict parser contract, and record data from E+0x10 in 0x30-byte strides. Each record’s first 0x20 bytes are the two Vec4 AABB corners; the complete +0x20..+0x2F tail remains opaque/write-preserved even though other tools partially label words within it.

[P01195 | 237226:237227 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01196 | 237227:237921 | NORMAL_TEXT]
The same typed-envelope validation can strengthen the collection parser itself: the 0x8080966D transforms vector at +0x40 should identify 0x808071A3 elements, and the instance-groups vector at +0x68 should identify 0x80807190 elements. The statics vector is a special case: pre-BL Alkahest models it as raw TagHash values and therefore does not type-check its envelope element word, but historical Charm's explicit Shadowkeep support defines the serialized 4-byte wrapper as SStaticMeshHash 0x8080967D. Treat 0x8080967D as the SOURCE-DERIVED expected marker candidate, record the raw envelope word, and require installed-data attestation before using that marker as write-authority provenance.

[P01197 | 237921:237922 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01198 | 237922:237978 | NORMAL_TEXT]
Implementation contract: TypedVectorEnvelopeAttestation

[P01199 | 237978:238671 | NORMAL_TEXT]
For every typed vector used by PackagePlacementBinding, persist and validate: headerOffset; rawCount; rawRelativeOffset; resolvedEnvelopeOffset; duplicateCount; rawElementTypeWord; expectedElementType when schema-backed; elementStart = envelope+0x10; elementSize; checked logical extent; and a fingerprint covering the raw header/envelope plus the referenced element bytes. All arithmetic must be overflow-checked and contained within the reconstructed logical entry. A duplicate-count mismatch, wrong typed element marker, impossible extent, or element-size disagreement is a parser/layout failure and must fail the candidate closed rather than triggering an alternate guessed element start.

[P01200 | 238671:238672 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01201 | 238672:239313 | NORMAL_TEXT]
For the Tower culling gate specifically, use the evidence progression CandidateTagAtStaticPlus18 → ResolvedClass0x80809671 → TypedBoundsVectorEnvelopeAttested → GeometryCorrelated → FieldProvenDirectIndex or RawMappingStructureAttested. TypedBoundsVectorEnvelopeAttested proves that Izanami has the expected Shadowkeep bounds resource shape; it does not prove which bounds index belongs to a transform. DirectIndex remains the highest-value first indexing hypothesis, with general package writes disabled until the exact source/layout/group/bounds/route fingerprint receives field proof or an explicit raw mapping is independently attested.

[P01202 | 239313:239314 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01203 | 239314:239363 | NORMAL_TEXT]
First true translation closure remains unchanged

[P01204 | 239363:240008 | NORMAL_TEXT]
Do not rebuild the currently promoted group-13/entity/collision diagnostic because of this finding. After that control is field-observed and a true unprojected candidate is selected, the first StaticInstanceBinding proof still preserves every vector header/envelope, count, group row, mesh identity, quaternion, scale, AO/opaque bytes, and resource route; it changes one 0x808071A3 Position XYZ, translates only its evidence-selected 0x80809673 AABB XYZ by the same delta, and conservatively expands only independently attested collection bounds when required. Visual movement, multi-view culling, and collision are separate acceptance signals.

[P01205 | 240008:240009 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01206 | 240009:240073 | NORMAL_TEXT]
Remote source provenance (not unpublished local Izanami source)

[P01207 | 240073:240178 | NORMAL_TEXT]
- cohaereo/alkahest prebl-0.5 Cargo.toml: https://github.com/cohaereo/alkahest/blob/prebl-0.5/Cargo.toml

[P01208 | 240178:240312 | NORMAL_TEXT]
- cohaereo/alkahest prebl-0.5 statics schema: https://github.com/cohaereo/alkahest/blob/prebl-0.5/crates/alkahest-data/src/statics.rs

[P01209 | 240312:240450 | NORMAL_TEXT]
- cohaereo/alkahest prebl-0.5 occlusion schema: https://github.com/cohaereo/alkahest/blob/prebl-0.5/crates/alkahest-data/src/occlusion.rs

[P01210 | 240450:240680 | NORMAL_TEXT]
- v4nguard/tiger-parse vector reader at the 0.1.13 bump commit, whose commit changes only version metadata from 0.1.12 to 0.1.13: https://github.com/v4nguard/tiger-parse/blob/ec2e27d0719db51f488033955c5a79860ebe9a6e/src/vector.rs

[P01211 | 240680:240681 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01212 | 240681:241112 | NORMAL_TEXT]
Dated update — 2026-08-20 (SOURCE-DERIVED): added typed-vector-envelope attestation as a prerequisite for Shadowkeep bounds-resource binding, upgraded the read-only placement catalog provenance to retain exact vector-envelope evidence, and corrected the top-level handoff to reflect that the group-13/entity/collision diagnostic packages are already staged, validated, and promoted and now await only the field launch/observation.

[P01213 | 241112:241113 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01214 | 241113:241199 | NORMAL_TEXT]
17.42 Source-Derived Intermediate D2 Opaque-Gap / DirectIndex Continuity — 2026-08-20

[P01215 | 241199:241200 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01216 | 241200:241379 | NORMAL_TEXT]
Classification: SOURCE-DERIVED from remote public cohaereo/alkahest only. This is later-D2 lineage evidence, not a Shadowkeep byte contract and not FIELD-TESTED Izanami behavior.

[P01217 | 241379:241380 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01218 | 241380:241894 | NORMAL_TEXT]
INTERMEDIATE D2 LAYOUT: +0x18 BOUNDS, +0x40 TRANSFORMS, OPAQUE MIDDLE GAP. In commit 63cd3059ac806522ada2e003e640cd0346e66ba3 (2023-12-23, “Single static dirty frustum culling”), SStaticMeshInstances seeks to +0x18 and reads an occlusion-bounds Tag, then from the post-Tag position seeks forward 0x24 before reading transforms. With a four-byte TagHash this places the transform-vector header at +0x40 while intentionally leaving +0x1C..+0x3F unmodeled. There is no transform_to_bounds_index field in that layout.

[P01219 | 241894:241895 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01220 | 241895:242275 | NORMAL_TEXT]
DIRECTINDEX CONSUMER IN THE SAME COMMIT. The static map loader takes each authoritative group range [instance_start, instance_start + instance_count) and slices both the transform array and occlusion-bounds array by that exact range before loading the model. Explicit per-transform mapping metadata is therefore not required for DirectIndex culling under this later-D2 structure.

[P01221 | 242275:242276 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01222 | 242276:242859 | NORMAL_TEXT]
SHADOWKEEP +0x20 POLICY REGRADE. This is negative evidence against routine mapping-vector discovery in 0x8080966D. Default headerGap20_3fMode = OpaquePreserved; fingerprint and preserve the raw bytes. Run raw +0x18 typed-bounds attestation, group topology/coverage, and collection-wide DirectIndex geometry/group-union correlation first. Only promote a vector candidate from the gap if DirectIndex fails or contradicts the data, OR if the raw bytes independently attest a complete Tiger vector and satisfy all mapping semantics. A plausible count/pointer pair alone is insufficient.

[P01223 | 242859:242860 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01224 | 242860:243292 | NORMAL_TEXT]
MAPPING CANDIDATE FAIL-CLOSED SEMANTICS. A nonempty candidate must cover the highest transform index referenced by authoritative group ranges, every value must be a valid bounds index, and mapped correlation must improve meaningfully over DirectIndex. Empty/identity mapping is semantically DirectIndex and does not create independent write authority. Constant, all-zero, partial, or range-invalid vectors remain non-authoritative.

[P01225 | 243292:243293 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01226 | 243293:243659 | NORMAL_TEXT]
PLACEMENT CATALOG PROVENANCE. Record headerGap20_3fRaw and its fingerprint; headerGap20_3fMode = OpaquePreserved | VectorCandidate | RawMappingStructureAttested; mappingDiscoveryTrigger = DirectIndexFailure | IndependentVectorAttestation; and intermediateD2OpaqueGapDirectIndexEvidence. No +0x20..+0x3F gap bytes enter the mutable closure for the first translation.

[P01227 | 243659:243660 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01228 | 243660:244098 | NORMAL_TEXT]
IMPLEMENTATION CONSEQUENCE. The read-only culling diagnostician becomes simpler and safer: attest +0x18 → 0x80809671 and its typed 0x80809673 vector, validate authoritative group ranges and bounds coverage, score DirectIndex immediately, and leave +0x20..+0x3F untouched unless a fallback trigger fires. This does not change the first-translation acceptance closure or the currently promoted group-13/entity/collision diagnostic package.

[P01229 | 244098:244099 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01230 | 244099:244125 | NORMAL_TEXT]
Remote source provenance:

[P01231 | 244125:244210 | NORMAL_TEXT]
https://github.com/cohaereo/alkahest/commit/63cd3059ac806522ada2e003e640cd0346e66ba3

[P01232 | 244210:244269 | NORMAL_TEXT]
src/statics.rs and src/mapload_temporary.rs at that commit

[P01233 | 244269:244383 | NORMAL_TEXT]
Later optional-map addition: https://github.com/cohaereo/alkahest/commit/8c67a03bc57b0caf9d5287eb595d5701fc655603

[P01234 | 244383:244384 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01235 | 244384:244769 | NORMAL_TEXT]
Dated update — 2026-08-20: SOURCE-DERIVED. Intermediate D2 Alkahest explicitly demonstrates +0x18 occlusion bounds + +0x40 transforms + an unmodeled middle gap while using same-range DirectIndex culling. Shadowkeep +0x20..+0x3F is therefore preserve-only by default and mapping discovery is fallback-only; field promotion still requires the existing exact-fingerprint acceptance gate.

[P01236 | 244769:244856 | NORMAL_TEXT]
17.43 Source-Derived Izanami Stage → Canonical Package Discovery Boundary — 2026-08-20

[P01237 | 244856:245185 | NORMAL_TEXT]
Classification: SOURCE-DERIVED from the remote public stanuwu/Sunrise tree at commit f26ef4e36adc922cbfac3b486c63cdccc13a37b6 (2026-08-19). This does not infer unpublished dirty Izanami source, does not change the currently promoted group-13/entity/collision field package, and does not prove a new package/destination identity.

[P01238 | 245185:245186 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01239 | 245186:245880 | NORMAL_TEXT]
STAGE-SUFFIX FILES ARE DELIBERATELY OUTSIDE THE PUBLIC CONTENT-MANIFEST INVENTORY. Sunrise's package-name parser accepts a package-directory leaf only when the lowercase filename ends exactly in .pkg and the stem has a recognized patchable package form. Files such as w64_..._8.pkg.izanami-stage, .izanami-carrier-stage, and passed/failed rollback suffixes are therefore classified unrecognized/excluded from the manifest inventory rather than registered as package rows. The directory scanner enumerates every leaf but skips unrecognized/excluded names, so these stage/backup artifacts also do not participate in the public directory fingerprint merely by existing beside the canonical files.

[P01240 | 245880:245881 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01241 | 245881:246578 | NORMAL_TEXT]
CONTENTCONFIG CANNOT ANNOUNCE AN .izanami-stage NAME AS-IS. The public ContentConfig row stores the canonical package filename stem, package id, and exact public build signature; the encoder explicitly documents that the client opens the row's package-name stem with a .pkg suffix. The scanner reconstructs the same canonical stem + .pkg path when validating a header. Therefore the supported discovery boundary is promotion to one canonical <stem>.pkg file, not trying to make Destiny/Sunrise open <stem>.pkg.izanami-stage directly. Do not add stage suffixes to ContentConfig or broaden the scanner solely to expose build artifacts: that would disagree with the client's stem-plus-.pkg contract.

[P01242 | 246578:246579 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01243 | 246579:247431 | NORMAL_TEXT]
TWO-PHASE BUILD/PROMOTION IS ARCHITECTURALLY CORRECT. The content-manifest runtime fingerprints only recognized canonical package candidates by name/stem, package id, filename-derived patch index, file size, and last-write time, then uses that fingerprint to decide whether a cached manifest is current. A newly generated or replaced noncanonical .izanami-stage file can therefore be built and validated without perturbing the public package catalog/cache. After Destiny is closed and every owner/latest stage passes Izanami validation, promotion/replacement of the canonical .pkg changes the recognized file inventory/fingerprint; on the next Sunrise initialization the canonical file is rescanned and its row can be emitted. Preserve byte equality between the accepted stage and promoted canonical file and verify the canonical hash after promotion.

[P01244 | 247431:247432 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01245 | 247432:248149 | NORMAL_TEXT]
MANIFEST IDENTITY IS NOT NATIVE BLOCK-ROUTE AUTHORITY. Header extraction derives patch ordering from the canonical filename and validates the package header's version 38, platform 2, public package id, and build signature. The public manifest Row itself contains name, packageId, and buildSignature but no separate physical-owner/block-route field. This is compatible with Izanami's FIELD-TESTED owner-routing result: ContentConfig registration of a canonical patch says which package filename is advertised, while physical block ownership still requires the independent native-observed/owner-preserving route fingerprint. Never promote a manifest-eligible file to FieldProvenRoute merely because Sunrise emitted it.

[P01246 | 248149:248150 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01247 | 248150:248997 | NORMAL_TEXT]
NEW-PACKAGE-IDENTITY CONSTRAINT. Sunrise's scanner allows multiple patch rows for one canonical package identity, but one public package id cannot safely describe two different identities; header extraction rejects mixed identities or duplicate patch indices within the same package-id group. It also accepts public package ids only in 0x0100..0x19FF, and the header validator requires the header publicPackageId to match the id encoded by the canonical filename. Therefore a future genuinely new package-name family cannot simply be advertised as a second identity sharing Tower package id 0x0369. A new identity needs a coherent distinct public package id/header/name tuple before native Destiny registration/loading is even tested. This is a Sunrise-manifest prerequisite, not proof that an arbitrary new id will be accepted by native Destiny.

[P01248 | 248997:248998 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01249 | 248998:249806 | NORMAL_TEXT]
IMPLEMENTATION / PROVENANCE CONTRACT. Treat generated files as an explicit lifecycle: StageUnregistered -> ValidatedStage -> CanonicalPromoted -> ManifestObserved. Add or log artifactRole, canonicalStem, parsedPackageId, parsedPatchIndex, manifestEligible, directoryFingerprintBefore/After, manifestRowBuildSignature, stageSha256, canonicalSha256, and promotionByteEquality. Fail closed if more than one canonical identity attempts to claim the same public package id, if the filename/header package ids disagree, or if the promoted canonical bytes do not exactly match the validated stage. Stage artifacts and rollback copies remain outside PackagePlacementBinding's native source identity; the binding should fingerprint the canonical resource/tag and physical block routes that Destiny actually consumes.

[P01250 | 249806:249807 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01251 | 249807:250449 | NORMAL_TEXT]
CURRENT FIELD CANDIDATE CONSEQUENCE. Do not rebuild, rename, or re-register the already promoted group-13/entity/collision diagnostic because of this finding. Its next operation remains the existing in-Sunrise field launch/observation. For future builds, keep the current safe workflow: author to noncanonical stage artifacts, validate completely, close Destiny, promote to the unique canonical .pkg paths, hash-verify, then relaunch. This source result specifically answers the generated-.pkg.izanami-stage discovery question: the stage is a pre-registration artifact by design; canonical promotion is the public Sunrise discovery boundary.

[P01252 | 250449:250450 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01253 | 250450:250869 | NORMAL_TEXT]
Remote source provenance: stanuwu/Sunrise public commit f26ef4e36adc922cbfac3b486c63cdccc13a37b6; content_manifest_package_name.cpp, content_manifest_directory_scan.cpp, content_manifest_header_extraction.cpp, content_manifest_package_header.cpp, state/content_manifest/definition.h, content_manifest_row_validation.cpp, middleware/content/manifest/content_manifest_encoder.cpp, and content_manifest_state_runtime.cpp.

[P01254 | 250869:250870 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01255 | 250870:251577 | NORMAL_TEXT]
Dated update — 2026-08-20 (SOURCE-DERIVED): proved from current public Sunrise source that .pkg.izanami-stage and other non-.pkg artifacts are intentionally skipped by the content-manifest inventory and cache fingerprint, while ContentConfig advertises a canonical stem that the client opens with .pkg appended. Formalized StageUnregistered -> CanonicalPromoted -> ManifestObserved, kept manifest registration separate from native physical block ownership, and identified a future new-package prerequisite: one public package id may not describe two different canonical package identities. No unpublished local Izanami source, DLL, package file, or running Destiny process was changed by this research pass

[P01256 | 251577:251578 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01257 | 251578:251683 | NORMAL_TEXT]
17.44 Source-Derived Shadowkeep Statics-Vector Marker Recovery and +0x18 Historical Regrade — 2026-08-20

[P01258 | 251683:251684 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01259 | 251684:252927 | NORMAL_TEXT]
SOURCE-DERIVED. A historical Charm change now closes one of the remaining parser-attestation gaps in the Shadowkeep static collection. Commit 149c541a2dfe52cc6b65d41da95f5e29e0a0e674 ("shadowkeep", 2023-08-05) is especially valuable because it is the commit that explicitly added the DESTINY2_SHADOWKEEP_2601 form of SStaticMapData. In that change, fields known to differ by generation were split deliberately: statics move to +0x58 for Shadowkeep versus +0x78 for Witch Queen; the tail hash moves to +0x78 versus +0x98; the likely collection-bound corner moves to +0x80 versus +0xA0; the static-list element class becomes 0x8080967D / 0x04 versus 0x808093BD / 0x04; the group row becomes 0x80807190 / 0x08 versus 0x80806D28 / 0x08; and the transform becomes 0x808071A3 / 0x30 versus 0x80806D40. Critically, ModelOcclusionBounds remained a shared SchemaField(+0x18) while those Shadowkeep-specific differences were being introduced. This upgrades +0x18 from merely a current-Charm deserializer-fallback clue to HistoricalShadowkeepSchemaEvidence. It still MUST be raw-attested against the installed Tower payload before any write, because that 2023 snapshot had not yet supplied the Shadowkeep-specific 0x80809671/0x80809673 bounds class IDs.

[P01260 | 252927:252928 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01261 | 252928:253670 | NORMAL_TEXT]
The statics-vector envelope now has a concrete marker candidate. That same Shadowkeep commit defines SStaticMeshHash as class 0x8080967D, serialized size 0x04, whose only payload is the StaticMesh tag. Pre-BL Alkahest instead declares the same logical list as Vec<TagHash>. These are not mutually exclusive descriptions of the bytes: tiger-parse's Vec<T> checks the envelope element-type word only when T exposes an ID, while its TagHash reader is a raw four-byte value with no declared type ID. Therefore an Alkahest Vec<TagHash> parse can consume the list while silently ignoring the envelope's element-class word. Historical Charm's 0x8080967D wrapper is consequently a strong SOURCE-DERIVED candidate for that otherwise-unchecked marker.

[P01262 | 253670:253671 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01263 | 253671:254614 | NORMAL_TEXT]
IMPLEMENTATION CONTRACT. For the Tower 0x8080966D statics vector at header +0x58, the read-only placement catalog should preserve the standard Tiger vector provenance (raw 0x10-byte header, resolved envelope, duplicated count, element start, extent) AND read the raw u32 at envelope+0x8 even though the Alkahest TagHash model does not validate it. Record staticElementMarkerMode = Unattested | ShadowkeepStaticHash_0x8080967D | Unexpected and expectedStaticElementMarker = 0x8080967D. Until installed bytes confirm the candidate, a mismatch is a non-writable/fail-closed binding result, not permission to rewrite the marker. Once raw-attested, the selected identity chain becomes exact: group.StaticIndex -> statics[StaticIndex] 4-byte wrapper -> raw StaticMesh TagHash -> resolved SStaticMesh 0x808071A7 -> child mesh data 0x80807194. Fingerprint both the vector envelope marker and the selected four-byte element in PackagePlacementBinding.

[P01264 | 254614:254615 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01265 | 254615:255141 | NORMAL_TEXT]
This also sharpens the difference among the four critical vectors. Transform 0x808071A3, group 0x80807190, and bounds 0x80809673 already have typed-element IDs in the strict parser model and can use their envelope marker as a direct structural gate. The statics list needs the historical-Charm marker candidate plus raw installed-data confirmation because the pre-BL Alkahest model intentionally erases that type at the Rust type level by using TagHash. Do not generalize 0x8080967D outside the Shadowkeep layout fingerprint.

[P01266 | 255141:255142 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01267 | 255142:255541 | NORMAL_TEXT]
The +0x18 occlusion rule is regraded but not loosened: raw Tower +0x18 must still resolve to a valid TagHash whose entry/resource class is 0x80809671, whose vector envelope attests 0x80809673 records, before DirectIndex correlation is armed. The historical Shadowkeep-support commit simply makes +0x18 the overwhelmingly preferred seam to test first; it does not make the relationship FIELD-TESTED.

[P01268 | 255541:255542 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01269 | 255542:256129 | NORMAL_TEXT]
The true one-instance acceptance mutation remains unchanged: preserve every vector/group count, pointer, marker, element ordering, static tag, quaternion, scale, AO/opaque data, and resource identity; change one 0x808071A3 Position XYZ; shift only its evidence-selected 0x80809673 AABB XYZ by the same delta; conservatively expand only independently attested collection bounds; then score visual movement, multi-view culling, and collision separately. The currently promoted group-13/entity/collision diagnostic package is not affected and should not be rebuilt for this parser finding.

[P01270 | 256129:256130 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01271 | 256130:256558 | NORMAL_TEXT]
UPDATE 2026-08-20 — SOURCE-DERIVED: Historical Charm Shadowkeep-enablement code identifies the four-byte static-list wrapper as 0x8080967D and deliberately retains ModelOcclusionBounds at +0x18 while changing other generation-specific offsets. This closes the statics-vector element-marker attestation gap and materially strengthens +0x18 as the first raw culling seam, without promoting either to FIELD-TESTED write authority.

[P01272 | 256558:256559 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01273 | 256559:256657 | NORMAL_TEXT]
17.45 Source-Derived Schema-Aware Reference Mask for Shadowkeep Static/Bounds Arrays — 2026-08-20

[P01274 | 256657:257660 | NORMAL_TEXT]
SOURCE-DERIVED. Current QuickTag scanning behavior exposes an important dependency-closure false-positive risk for the exact Shadowkeep resources Izanami is about to bind. QuickTag first blocks only array ranges whose detected element class is known to its class registry and marked block_tags; outside those blocked ranges it then scans every 4-byte-aligned u32, interprets it as a TagHash candidate, and records it when it is syntactically package-like and present in the valid-file set. That is intentionally useful heuristic discovery behavior, but it is not schema-aware dependency authority. The current Shadowkeep class registry inspected for this pass contains the core static classes 0x8080966D, 0x80807190, 0x808071A3, and 0x808071A7, while the Shadowkeep bounds classes 0x80809671/0x80809673 and the 0x8080967D statics wrapper are not registered there. Consequently the generic scanner cannot rely on those missing classes to protect their numeric payload ranges from aligned-hash discovery.

[P01275 | 257660:257661 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01276 | 257661:258641 | NORMAL_TEXT]
IMPLEMENTATION CONSEQUENCE: ADD SchemaAwareReferenceMask BEFORE BUILDING A BINDING/RESIDENCY CLOSURE. For a raw-attested Shadowkeep static collection, classify byte ranges by recovered semantics before any heuristic TagHash pa SchemaKnownEdge ranges are the exact raw +0x18 SOcclusionBounds TagHash, the 0x80806EF4 parent+0x8 static-instances TagHash, and each four-byte 0x8080967D statics-vector element that resolves to an SStaticMesh. Numeric/metadata non-reference ranges are every 0x808071A3 transform record, every 0x80807190 group record, and every 0x80809673 occlusion-bound record. Typed Tiger vector envelope class-marker words are structural metadata, not dependency edges. Any aligned value inside a masked non-reference range that happens to decode to an installed TagHash must be recorded only as SuppressedHeuristicHit for diagnostics and must never become a residency requirement, dependency-clone input, PackagePlacementBinding identity edge, or build rejection.

[P01277 | 258641:258642 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01278 | 258642:259479 | NORMAL_TEXT]
WHY THIS IS REQUIRED BEFORE THE FIRST TRUE TRANSLATION. The translation experiment deliberately changes floating-point Position XYZ and AABB min/max XYZ. Those numeric bit patterns can coincidentally gain or lose the shape of a valid installed TagHash after the edit. Without a schema-aware mask, a generic hash scan can therefore make the dependency closure appear to change merely because transform/culling floats changed, causing a false stale-binding failure, a bogus foreign-package residency dependency, or an attempted clone/remap of data that is not a reference at all. Add referenceMaskDigest, schemaKnownEdgeSetDigest, suppressedHeuristicHitCount, and maskedRangeFingerprint to read-only catalog/binding provenance so dependency identity remains stable across numeric edits except where an actual schema-known TagHash changes.

[P01279 | 259479:259480 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01280 | 259480:260995 | NORMAL_TEXT]
SHADOWKEEP 0x80809673 TAIL REFINEMENT — TYPE-AWARE. Current Charm models each 0x30-byte Shadowkeep occlusion record as two Vector4 corners followed by TigerHash Unk20 and TigerHash Unk24; the declared record size leaves +0x28..+0x2F unmodeled. Charm's own type system materially narrows what those names mean: TigerHash is the generic 32-bit hash base, while FileHash is the specialization that encodes package ID + entry index and is used for package-backed files/typed Tags. A generic TigerHash field is therefore not a resource edge merely because its numeric bits also form a syntactically valid FileHash. Charm supplies a concrete non-resource consumer for the same occlusion-record type: MetadataExporter uses a decal bound's Unk24.ToString() as the decal-box identifier while consuming Corner1/Corner2 as geometry; it does not resolve Unk24 through the package/file resourcer. This does not prove static-map Unk20/Unk24 can never have additional semantics, but it upgrades their default classification from vaguely 'hash-like' to GenericTigerIdentifier / NonTraversableUnlessConsumerProven. Izanami must preserve and fingerprint the complete +0x20..+0x2F tail, may expose +0x20/+0x24 raw identifiers diagnostically, but must not traverse them as package dependencies, use them as transform-to-bounds mapping metadata, or promote a package-shaped numeric coincidence into residency authority. A future native/static consumer can regrade an individual word only under the exact class/layout/usage fingerprint.

[P01281 | 260995:260996 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01282 | 260996:261569 | NORMAL_TEXT]
CROSS-PACKAGE CLOSURE POLICY. CrossPackageDependencyClosure should propagate SchemaKnownEdge plus RuntimeObservedEdge by default. HeuristicValidHashEdge remains discovery-only outside masked structures; inside a schema-known non-reference range it is suppressed entirely. This sharpens, rather than replaces, the existing confidence model in Sections 17.14/17.16: package residency, cloning/remapping, and persistent binding identity must be driven by typed/raw-attested reference seams, not coincidental 32-bit values inside transforms, group metadata, or culling floats.

[P01283 | 261569:261570 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01284 | 261570:262103 | NORMAL_TEXT]
FIRST-WRITE CONTRACT UNCHANGED. This finding adds no mutable byte seam. The first true unprojected StaticInstanceBinding still preserves every vector/group record and size, resource/tag identity, quaternion, scale, AO/opaque bytes, and all bounds-tail bytes; it changes one 0x808071A3 Position XYZ, shifts only its evidence-selected 0x80809673 AABB XYZ by the same delta, and conservatively expands only independently attested collection bounds. Visual movement, multi-view culling, and collision remain separate acceptance signals.

[P01285 | 262103:262104 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01286 | 262104:262436 | NORMAL_TEXT]
Remote source provenance: v4nguard/quicktag current scanner/classes at commit bdad2e92442439bb0f71c67aca608b7ca0a8c74c; MontagueM/Charm current StaticMapData.cs at commit 50d36ee1f9ecadad7522504c20b1f3f9c97e30af; cohaereo/alkahest current tfx/common.rs at commit b140945588717ce75218ff48e15674a6655431d7. Remote public source only.

[P01287 | 262436:262437 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01288 | 262437:263183 | NORMAL_TEXT]
UPDATE 2026-08-20 — SOURCE-DERIVED: added a schema-aware reference mask for Shadowkeep placement/culling resources after confirming QuickTag's aligned-u32 dependency scan can see coincidental TagHash-shaped values in unblocked numeric arrays. Typed transform/group/bounds ranges are now explicit non-reference ranges, statics elements and known parent/bounds TagHash fields remain typed edges, and the entire 0x80809673 trailing 0x10 bytes remain preserve-only/non-reference despite Charm naming two words TigerHash. This prevents numeric transform/AABB edits from spuriously changing dependency closure or residency requirements. No unpublished local Izanami source, DLL, package file, or running Destiny process was changed by this research pa

[P01289 | 263183:263185 | NORMAL_TEXT]
.

[P01290 | 263185:263186 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01291 | 263186:263187 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01292 | 263187:263188 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01293 | 263188:263293 | NORMAL_TEXT]
17.46 Source-Derived Generic TigerHash vs Resource FileHash Boundary for Culling Provenance — 2026-08-20

[P01294 | 263293:263635 | NORMAL_TEXT]
SOURCE-DERIVED. This section refines the dependency/reference authority model using remote public MontagueM/Charm source at commit 50d36ee1f9ecadad7522504c20b1f3f9c97e30af. It does not infer unpublished local Izanami source, supersede FIELD-TESTED Tower results, or change the currently promoted group-13/entity/collision diagnostic package.

[P01295 | 263635:263636 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01296 | 263636:264398 | NORMAL_TEXT]
TYPE-SYSTEM BOUNDARY. Charm defines TigerHash as a generic 32-bit hash type whose validity check only excludes 0 and 0xFFFFFFFF. FileHash derives from TigerHash but adds the Destiny package-file interpretation: PackageId and FileIndex are decoded from the same 32-bit value, and FileHash construction explicitly encodes package ID + entry index. Tag<T> is file-backed and is constructed from a FileHash/TigerFile identity before deserializing the typed payload. Therefore field declaration alone matters: a TigerHash is not automatically equivalent to a FileHash/TagHash dependency edge. Bit-pattern compatibility with the FileHash encoding is necessary for a real file identity but is not sufficient evidence that the producer/consumer intends file resolution.

[P01297 | 264398:264399 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01298 | 264399:265224 | NORMAL_TEXT]
CONCRETE OCCLUSION-TAIL CONSUMER. Charm's SMeshInstanceOcclusionBounds 0x80809673 / 0x30 declares Corner1, Corner2, TigerHash Unk20, and TigerHash Unk24. MetadataExporter consumes this same record type for decal projection bounds and uses boxCorners.Unk24.ToString() as the emitted decal-box identifier while Corner1/Corner2 provide the actual bound. That path does not dereference Unk24 through FileResourcer/PackageResourcer or construct a Tag from it. This is concrete evidence that at least one real consumer treats a tail TigerHash as semantic identity/metadata rather than package-backed resource ownership. It is not proof that every context gives Unk20/Unk24 identical semantics, so the correct static-map rule is non-traversable by default with consumer-specific regrading, not 'these words can never be resources.'

[P01299 | 265224:265225 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01300 | 265225:266066 | NORMAL_TEXT]
REFERENCE-SEMANTIC MODEL. Upgrade SchemaAwareReferenceMask from a binary reference/non-reference mask to a typed semantic classification. Recommended values are ResourceFileReference, GenericTigerIdentifier, StructuralTypeMarker, NumericData, and UnknownHeuristic. ResourceFileReference is reserved for schema/raw-attested seams whose consumer actually resolves a package file/tag, such as the 0x80806EF4 parent +0x8 child tag, 0x8080966D +0x18 occlusion tag after raw attestation, and each statics-vector element that resolves to SStaticMesh. GenericTigerIdentifier is preserved/fingerprinted but does not propagate CrossPackageDependencyClosure. StructuralTypeMarker covers Tiger vector envelope class words. NumericData covers transforms, group words, and AABB floats. UnknownHeuristic remains discovery-only outside schema-known ranges.

[P01301 | 266066:266067 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01302 | 266067:266866 | NORMAL_TEXT]
SHADOWKEEP 0x80809673 CONTRACT. For every bounds record, classify raw +0x20 and +0x24 as GenericTigerIdentifier / NonTraversableUnlessConsumerProven and +0x28..+0x2F as opaque Numeric/UnknownTail. Preserve all sixteen tail bytes exactly. Add boundsTail20HashRaw, boundsTail24HashRaw, boundsTailHashSemantic, and boundsTailFingerprint to read-only provenance. QuickTag-style aligned-u32 hits inside this tail remain SuppressedHeuristicHit even if the value decodes to an installed package/file identity. Do not add such hits to residency closure, clone/remap input, stale-binding identity, or the bounds-index search. If future native/static consumer evidence proves a tail word is dereferenced as a FileHash, reclassify that exact word only under the matching class/layout/resource-use fingerprint.

[P01303 | 266866:266867 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01304 | 266867:267582 | NORMAL_TEXT]
IMPLEMENTATION CONSEQUENCE. CrossPackageDependencyClosure should propagate ResourceFileReference and RuntimeObservedEdge by default, not every syntactically valid TigerHash. This prevents ordinary Position/AABB edits from manufacturing or deleting fake package dependencies while still retaining the raw identifiers needed for forensic comparison. The first true StaticInstanceBinding mutation remains unchanged: preserve every vector/group record and size plus the complete 0x80809673 tail; change one 0x808071A3 Position XYZ, shift only its evidence-selected AABB Corner XYZ by the same delta, and conservatively expand independently attested collection bounds. No new mutable seam is introduced by this finding.

[P01305 | 267582:267583 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01306 | 267583:267789 | NORMAL_TEXT]
Remote source provenance: MontagueM/Charm Tiger/TigerHash.cs, Tiger/Tag.cs, Tiger/Schema/Static/StaticMapData.cs, and Tiger/Exporters/MetadataExporter.cs at commit 50d36ee1f9ecadad7522504c20b1f3f9c97e30af.

[P01307 | 267789:267790 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01308 | 267790:268555 | NORMAL_TEXT]
UPDATE 2026-08-20 — SOURCE-DERIVED: Charm's type system distinguishes generic TigerHash identifiers from package-backed FileHash identities, and MetadataExporter concretely uses SMeshInstanceOcclusionBounds.Unk24 as a decal-bound identifier rather than resolving it as a package file. Refined the Shadowkeep culling-tail/reference model so +0x20/+0x24 are preserved GenericTigerIdentifier fields that do not enter dependency/residency traversal unless a consumer proves file-backed semantics. This makes the existing schema-aware reference mask type-aware and prevents valid-looking 32-bit hash coincidences from becoming false package dependencies. No unpublished local Izanami source, DLL, package file, or running Destiny process was changed by this research pa

[P01309 | 268555:268556 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01310 | 268556:268660 | NORMAL_TEXT]
17.47 Source-Derived Same-Era Static Placement-Layer Separation and Translation-Space Gate — 2026-08-20

[P01311 | 268660:269695 | NORMAL_TEXT]
SOURCE-DERIVED PRIMARY-SOURCE FINDING. The pre-Beyond-Light Alkahest prebl-0.5 map loader makes the Shadowkeep placement layering unusually explicit. For every SMapDataTableEntry it first constructs an outer Transform from the row translation XYZ, stored quaternion, and Translation.W as uniform scale. But in the 0x808071B3 static-placement branch, that outer Transform is not inserted on the generated static parent and is not composed into the children. The parent is spawned with metadata only; each child Static Instance receives only the corresponding inner 0x808071A3 translation/rotation/Scale.x transform. Other resource branches in the same function, such as lens flares, do insert the previously constructed outer row Transform, so the static omission is branch-specific rather than evidence that the row transform was unavailable. Primary source: cohaereo/alkahest, ref prebl-0.5, crates/alkahest-renderer/src/loaders/map.rs; the matching SMapDataTableEntry and SUnk80806EF4 schemas are in crates/alkahest-data/src/map.rs.

[P01312 | 269695:269696 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01313 | 269696:270371 | NORMAL_TEXT]
INTERPRETATION / EVIDENCE CLASS. This independently corroborates the existing Charm-exporter warning: public tooling is showing Shadowkeep static collections in collection-local coordinates and omitting the native outer placement stage. Izanami's FIELD-TESTED aggregate Tower translation proves native Destiny does apply the outer map-row placement to the collection. Together these support a two-layer model — outer map-row placement plus inner static-collection placement — but they do NOT by themselves field-prove the authored coordinate space of raw 0x80809673 culling AABBs. Therefore cullingSpace should remain an evidence-bearing value, not a hard-coded native fact.

[P01314 | 270371:270372 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01315 | 270372:271010 | NORMAL_TEXT]
CORRELATION ORDER. StaticBoundsCorrelation should now treat CollectionLocal as the SOURCE-DERIVED primary hypothesis and OuterComposed as a secondary cross-check/fallback. Compute predicted render AABBs from mesh-local geometry plus the inner 0x808071A3 transform first, correlate those against raw 0x80809673 bounds, and record both scores. A strong collection-local DirectIndex fit is expected under the same-era tool model rather than suspicious. OuterComposed should remain available to detect a contradictory payload or native-space clue, but it should no longer have equal prior weight merely because an outer row transform exists.

[P01316 | 271010:271011 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01317 | 271011:271635 | NORMAL_TEXT]
TRANSLATION-DELTA CONSEQUENCE. For a pure inner translation, outer translation cancels from the displacement. The safest first true StaticInstanceBinding test therefore does not require the entire outer transform to be identity; it requires the OUTER LINEAR PART to be identity for the delta being tested: rotation identity and uniform scale 1. A nonzero outer translation is acceptable. Under that gate, delta_world == delta_local, so the writer can change one 0x808071A3 Position XYZ by Δlocal and shift the evidence-selected raw AABB by the same Δlocal without introducing an additional coordinate-conversion assumption.

[P01318 | 271635:271636 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01319 | 271636:272250 | NORMAL_TEXT]
NON-IDENTITY OUTER PLACEMENTS. If an outer placement has rotation and/or scale, world-space authoring must remain fail-closed until the outer linear composition and quaternion convention are field-proven for that layout. The eventual compiler rule should be expressed abstractly as Δlocal = inverse(Louter) * Δworld, where Louter is the proven 3x3 linear part of the outer placement. Until then, such bindings may expose source/local transforms read-only or support explicitly local-space edits only; they must not silently compile a world-space gizmo delta directly into the inner Position field or culling AABB.

[P01320 | 272250:272251 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01321 | 272251:272779 | NORMAL_TEXT]
BINDING/CATALOG PROVENANCE. Add outerPlacementFingerprint, outerTranslation, outerRotationRaw, outerUniformScale, outerLinearIdentity, innerAuthoringSpace, cullingSpaceEvidence, and worldDeltaConversionMode. The outer row remains source-identity provenance for an inner StaticInstanceBinding and is not part of the first per-instance mutable closure. A stale or changed outer linear transform invalidates any field-proven local-to-world conversion fingerprint even if the inner collection tag and transform index are unchanged.

[P01322 | 272779:272780 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01323 | 272780:273389 | NORMAL_TEXT]
FIRST-PROOF GATE. Prefer a candidate with rotation identity and outer scale 1; do not reject it solely because outer translation is nonzero. Preserve every group/vector row and size, mesh-local data, outer row bytes, quaternion/scale/AO/opaque bytes, and resource identities. Change only one inner Position XYZ, its evidence-selected culling AABB XYZ, and conservative collection bounds as already specified. Score visual movement, multi-view culling, and collision independently. Success can upgrade the exact culling-space/mapping/layout/route fingerprint; it still does not establish live runtime editing.

[P01324 | 273389:273390 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01325 | 273390:273725 | NORMAL_TEXT]
UI CONSEQUENCE. The package-backed editor may show local transform intent immediately, but it must keep Requires Build/Reload. For bindings with unresolved non-identity outer linear transforms, world-space gizmo compilation should be disabled or explicitly local-only rather than pretending the package coordinate conversion is known.

[P01326 | 273725:273726 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01327 | 273726:274259 | NORMAL_TEXT]
2026-08-20 UPDATE — SOURCE-DERIVED: same-era preBL Alkahest independently shows the 0x808071B3 static branch discarding the outer row Transform while retaining only inner static transforms. CollectionLocal is now the preferred correlation hypothesis, and the first translation candidate gate is relaxed from full identity outer transform to identity outer linear transform (rotation identity, scale 1); nonzero outer translation is safe for a translation-delta proof. No package, DLL, or runtime mutation is implied by this finding.

[P01328 | 274259:274260 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01329 | 274260:274371 | NORMAL_TEXT]
17.48 Implementation-Derived Binding Preimage, Idempotent Rebuild, and Proof-Fingerprint Contract — 2026-08-20

[P01330 | 274371:275260 | NORMAL_TEXT]
IMPLEMENTATION-DERIVED / FIELD-RECONCILED. This section is not a new native-format claim. It reconciles the existing FIELD-TESTED package workflow with the persistent ForgeUUID -> PackagePlacementBinding design before the first true StaticInstanceBinding becomes writable. The field workflow has already needed clean-baseline restores to avoid compounded edits, while other iterations have derived a new patch-8 image from the currently active canonical file. The upcoming per-instance recipe will deliberately change Position XYZ, a per-instance culling AABB, and sometimes the conservative collection AABB. A single monolithic sourceFingerprint is therefore unsafe in both directions: if it covers all mutable bytes it self-invalidates immediately after a successful Forge build; if it is relaxed enough to accept those changed bytes it can accidentally accept unrelated external drift.

[P01331 | 275260:275261 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01332 | 275261:276679 | NORMAL_TEXT]
SEPARATE STRUCTURAL IDENTITY FROM MUTABLE PREIMAGE STATE. PackagePlacementBinding should carry at least four logically distinct digests. (1) StructuralIdentityFingerprint: stable routing/layout identity, including map-row/resource/parent/child tags and classes, Tiger vector headers/envelopes and typed markers, group row/topology, selected static/mesh identity, bounds-resource identity, culling mapping/space evidence, opaque read-only bytes that participate in layout attestation, and declared/native physical-route fingerprints. It deliberately excludes the mutable numeric XYZ fields that Forge is allowed to author. (2) BaselinePreimageFingerprint: the exact logical source bytes for every writable seam before Forge edits, retained immutably with the binding/source package-set identity. (3) ExpectedCanonicalPreimageFingerprint: the exact logical mutable bytes Izanami expects to find in the currently active canonical package set before an incremental build. Initially this equals the baseline; after a validated stage is promoted and canonical byte identity is verified, it may advance to the known Izanami-authored postimage. (4) AuthoredPostimageFingerprint: the exact logical mutable-resource bytes produced by the current compile and verified by re-reading the staged output. Stage generation alone must not advance ExpectedCanonicalPreimageFingerprint because a stage is not yet active canonical state.

[P01333 | 276679:276680 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01334 | 276680:277464 | NORMAL_TEXT]
FAIL-CLOSED PREIMAGE STATES. Before staging, classify the active logical resource set as BaselineMatched, LastKnownIzanamiPostimageMatched, or DriftedUnknown. BaselineMatched and LastKnownIzanamiPostimageMatched may compile under the corresponding explicit mode. DriftedUnknown is a hard stop: do not auto-rebase, do not overwrite the changed bytes, and do not infer that a same-class/same-index record is still safe. Surface NeedsRebindOrRebase with the mismatched resource/tag/block provenance. If a promoted test is rolled back, ExpectedCanonicalPreimageFingerprint must roll back with the canonical package set. If an installed Destiny/Sunrise update changes structural identity or route fingerprints, the binding becomes stale even if the old mutable bytes happen to be present.

[P01335 | 277464:277465 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01336 | 277465:278192 | NORMAL_TEXT]
BASELINE-RELATIVE AUTHORING MAKES REBUILDS IDEMPOTENT. For translation-capable StaticInstanceBinding, derive every authored value from the immutable source baseline plus current Forge scene intent, never by applying another delta to the active package bytes. Let P0 be the baseline 0x808071A3 Position, B0 its baseline proven 0x80809673 AABB, and P1 the current Forge target in the proven local authoring space. Compute delta = P1 - P0, write Position = P1, and write per-instance bound = B0 translated by delta. Do not compute currentPosition + delta or currentBound + delta. This prevents a second Build with unchanged scene intent from moving the object twice and makes Undo/Redo compile from one canonical source of truth.

[P01337 | 278192:278193 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01338 | 278193:279160 | NORMAL_TEXT]
COLLECTION BOUNDS NEED THE SAME BASELINE RULE. The deliberately conservative first field proof expands the collection AABB rather than shrinking/rebuilding it. If later builds simply expand the already-expanded canonical AABB, repeated moves and undo operations can permanently inflate the culling envelope. The deterministic package compiler should instead start from the immutable baseline collection AABB on every compile and conservatively union it with the CURRENT target AABBs for every Forge-authored instance in that collection. For the first one-object proof this is simply union(BaselineCollectionAabb, TargetBound). For later multiple-object translation, union the same baseline envelope with all current target bounds. This never shrinks below stock authored coverage, does not accumulate historical edit positions, and permits a move-back-to-source to return the logical collection envelope to its baseline bytes without inventing a tighter culling box.

[P01339 | 279160:279161 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01340 | 279161:280071 | NORMAL_TEXT]
PROOF AUTHORITY MUST NOT HASH THE EDITABLE TARGET VALUE AS STRUCTURAL IDENTITY. FieldProvenDirectIndex, proven cullingSpace, and later TranslationProven should be tied to a StructuralAuthorityFingerprint built from the exact layout/data tag, bounds tag, group/topology, vector/envelope markers, mesh identity, mapping evidence, culling-space evidence, baseline source relationship, and physical routes plus a mutationRecipeVersion. The current target Position/AABB XYZ belongs to mutable preimage/postimage state and must not be part of the structural proof key. Otherwise the first successful move would make the proof unusable for the second intentional move of the exact same native seam. This does NOT generalize authority to another collection, mapping, route, rotation convention, or scale rule: any structural fingerprint change fails closed, and rotation/scale remain separately unproven capabilities.

[P01341 | 280071:280072 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01342 | 280072:280860 | NORMAL_TEXT]
RECOMMENDED FIRST IMPLEMENTATION MODE: BaselinePinned. For the first true StaticInstanceBinding milestone, prefer compiling from an exact preserved clean logical baseline/package-set fingerprint and applying the current Forge scene target from scratch. This matches the field practice that already restores pre-test package baselines before a new composition and minimizes the number of accepted preimage states. A later KnownPostimageIncremental mode may compile from the active canonical image only when its mutable resources exactly match the last verified Izanami postimage; even then, the target values should still be regenerated from BaselinePreimage rather than incrementally transformed from the postimage. Do not introduce an automatic fuzzy rebase in the first implementation.

[P01343 | 280860:280861 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01344 | 280861:281430 | NORMAL_TEXT]
PROMOTION / OBSERVATION STATE IS SEPARATE FROM NATIVE CAPABILITY PROOF. A validated stage can produce AuthoredPostimageFingerprint. Canonical promotion plus hash/byte verification can advance ExpectedCanonicalPreimageFingerprint. Only an in-game acceptance result can advance native capability evidence such as FieldProvenDirectIndex or TranslationProven. A package that promoted successfully but rendered/culls incorrectly is still a known Izanami postimage for rollback/rebuild accounting; it is not a proven placement capability. Keep these state machines separate.

[P01345 | 281430:281431 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01346 | 281431:282612 | NORMAL_TEXT]
PLACEMENT-CATALOG / BINDING ADDITIONS. Add structuralIdentityFingerprint, structuralAuthorityFingerprint, baselinePackageSetFingerprint, baselinePreimageFingerprint, expectedCanonicalPreimageFingerprint, authoredPostimageFingerprint, mutableFieldMask, mutationRecipeVersion, compileGeneration, preimageState, promotionTransactionId, promotionSetFingerprint, promotionJournalId, commitPointPackage, canonicalGeneration, and rollbackGeneration. For the per-instance translation recipe, mutableFieldMask should name only the selected Position XYZ, the evidence-selected bounds XYZ, and the independently attested collection-bounds XYZ. Everything else remains structural/read-only provenance. A build is not canonical merely because every stage validates individually: promotion must also be a verified package-set transaction, with all referenced physical-owner packages promoted and hash-checked before the latest/metadata-root package becomes the commit point. The UI can expose Source State = Baseline | Last Izanami Build | Drifted, Build State = Clean | Dirty | Requires Rebind, while preserving Package-backed / Requires Build & Reload until a runtime binding actually exists.

[P01347 | 282612:282613 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01348 | 282613:283306 | NORMAL_TEXT]
ACCEPTANCE TESTS FOR THE COMPILER BEFORE THE DESTINY FIELD LAUNCH. With one source-attested candidate, Build twice without changing scene intent and require identical reconstructed logical transform/bounds/collection-bounds bytes on both outputs. Move the Forge target, build, then undo to the source target and require the logical mutable resource bytes to return to the baseline recipe result rather than retaining a historically expanded collection AABB. Mutate one protected source byte or substitute an unknown canonical postimage and require staging to fail before any package is promoted. These tests validate Izanami's binding lifecycle without adding a new Destiny-native assumption.

[P01349 | 283306:283307 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01350 | 283307:284299 | NORMAL_TEXT]
2026-08-20 UPDATE — IMPLEMENTATION-DERIVED / FIELD-RECONCILED: split persistent PackagePlacementBinding identity from mutable package preimage/postimage state and defined a baseline-relative, idempotent compile rule. The key consequence for the upcoming one-instance translation is that Position, per-instance AABB, and conservative collection bounds must always be regenerated from immutable source baseline + current Forge intent rather than incrementally re-edited from the last canonical package. Field-proven mapping/translation authority is keyed by structural layout/resource/route evidence, while expected canonical mutable bytes evolve only through verified Izanami promotion. This prevents successful builds from self-invalidating their own bindings, prevents repeated-build delta compounding and collection-bound inflation, and still fails closed on unknown external drift. No unpublished local source, DLL, package file, or running Destiny process was changed by this research pa

[P01351 | 284299:284300 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01352 | 284300:284301 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01353 | 284301:284389 | NORMAL_TEXT]
17.49 IMPLEMENTATION-DERIVED CRASH-SAFE MULTI-OWNER PROMOTION COMMIT POINT — 2026-08-20

[P01354 | 284389:284390 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01355 | 284390:284957 | NORMAL_TEXT]
WHY THIS MATTERS NOW. The first true StaticInstanceBinding is deliberately a multi-resource mutation: the selected 0x808071A3 transform lives in the 0x8080966D static collection, while its culling AABB lives in a separately referenced 0x80809671 resource. Existing FIELD-TESTED Tower work also proves that a latest package row may resolve a block body from an older physical owner patch. Those two facts mean a logically atomic Forge edit can span more than one canonical .pkg file. Stage validation by itself does not make the promoted canonical package set atomic.

[P01356 | 284957:284958 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01357 | 284958:285498 | NORMAL_TEXT]
SOURCE-DERIVED PHYSICAL-OWNER FACT. Public tiger-pkg D2 reading selects a block body from the currently opened package only when that package's patch id equals BlockHeader.patch_id; otherwise it opens <path_base>_<patch_id>.pkg and reads the block at that row's offset. Source: https://github.com/v4nguard/tiger-pkg/blob/657f41c0851001b2d371592b2f7a5cb9c686ddb4/src/d2_shared.rs . This matches the already FIELD-TESTED Izanami owner-preserving route model, while native owner observations remain the authoritative route evidence for Tower.

[P01358 | 285498:285499 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01359 | 285499:286354 | NORMAL_TEXT]
IMPLEMENTATION-DERIVED CONSEQUENCE: DEFINE A PACKAGE-SET COMMIT POINT. Because Destiny must already be closed before canonical package replacement, the remaining failure mode is not an in-process reader race; it is an interrupted copy/crash/power loss that leaves canonical files from different Izanami generations. Treat every promotion as a transaction over the complete set of canonical package files touched by the build. The latest/metadata-root package should be the commit-point file for a family when its block table is what redirects the new logical entries to physical owner bodies. Promote and verify every referenced owner file first; promote the latest/metadata-root package last. Rollback should reverse that visibility order: restore the latest/metadata-root file first so the new routes are no longer advertised, then restore owner files.

[P01360 | 286354:286355 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01361 | 286355:287158 | NORMAL_TEXT]
PROMOTION JOURNAL. Before touching any canonical file, persist a PromotionJournal next to Izanami's stage metadata with: promotionJournalId; promotionSetFingerprint; canonicalGenerationBefore/After; every canonical path; baseline SHA-256/size; staged SHA-256/size; expected package/patch id; physical-owner role; latest/commit-point role; backup path/hash; and state. Minimal states: Prepared -> OwnersPromoted -> CommitPointPromoted -> Verified, with RolledBack and RecoveryRequired terminal/recovery states. A subsequent Izanami/Sunrise preflight that sees any journal not in Verified or RolledBack must fail closed before launching Destiny or installing another build. Do not silently 'finish' an interrupted promotion from assumptions; revalidate every canonical preimage and staged artifact first.

[P01362 | 287158:287159 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01363 | 287159:287763 | NORMAL_TEXT]
FILE-REPLACEMENT RULE. Never stream-copy directly over a canonical .pkg and never hardlink a stage artifact to a canonical path. Use a same-volume temporary sibling, write/copy the complete bytes, fsync/close where available, verify SHA-256 and header/package identity, then replace/rename into the canonical pathname. The previous FIELD-TESTED hardlink incident is direct project evidence that link identity can turn a seemingly isolated stage write into a canonical mutation. Promotion must additionally assert that stage and canonical paths do not share file identity before authoring or replacement.

[P01364 | 287763:287764 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01365 | 287764:287807 | NORMAL_TEXT]
OWNER-FIRST / LATEST-LAST SAFETY CONTRACT.

[P01366 | 287807:287889 | NORMAL_TEXT]
1. Stage every owner and latest artifact under noncanonical .izanami-stage names.

[P01367 | 287889:288075 | NORMAL_TEXT]
2. Validate logical entry bytes, source-codec/encryption/authentication, block rows, owner patch ids, offsets, source-route fingerprints, and package/header identity for the entire set.

[P01368 | 288075:288199 | NORMAL_TEXT]
3. Snapshot/verify the BaselinePinned canonical hashes that the build expects. Any unknown drift aborts before replacement.

[P01369 | 288199:288314 | NORMAL_TEXT]
4. Prepare backups of every canonical file in the promotion set and verify backup hashes before changing anything.

[P01370 | 288314:288478 | NORMAL_TEXT]
5. Promote owner files referenced by the new latest block rows first, one complete-file replacement at a time, verifying each canonical postimage hash immediately.

[P01371 | 288478:288585 | NORMAL_TEXT]
6. Recheck that all new latest rows resolve only to owner files already at the intended staged generation.

[P01372 | 288585:288676 | NORMAL_TEXT]
7. Promote the latest/metadata-root package last. This is the package-family commit point.

[P01373 | 288676:288825 | NORMAL_TEXT]
8. Re-read the complete canonical package set and require the expected PromotionSetFingerprint before marking Verified or allowing the field launch.

[P01374 | 288825:289031 | NORMAL_TEXT]
9. On rollback or failed post-promotion verification, restore the latest/metadata-root commit-point file first, then restore owner files, and require exact baseline hashes before clearing RecoveryRequired.

[P01375 | 289031:289032 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01376 | 289032:289621 | NORMAL_TEXT]
MULTI-RESOURCE STATICINSTANCEBINDING. The transform resource and bounds resource may resolve through different block-owner files. The compiler must therefore produce one PromotionSet for the complete mutable closure, not one independent promotion per edited TagHash. PackagePlacementBinding should record which canonical package generation satisfied each resource's physical-route fingerprint. If the transform postimage is generation N but the bounds postimage is generation N-1, the binding state is MixedGeneration/RecoveryRequired and Destiny must not be launched for that experiment.

[P01377 | 289621:289622 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01378 | 289622:290030 | NORMAL_TEXT]
SAME-FILE CASE. If every changed block body and its relevant metadata are in one canonical package file, the same model collapses naturally to one temporary-file replacement: that file is both owner and commit point. Do not special-case this into direct in-place writes; keeping the same transaction journal and hash verification preserves deterministic recovery and makes later multi-owner expansion safer.

[P01379 | 290030:290031 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01380 | 290031:290734 | NORMAL_TEXT]
ACCEPTANCE TESTS BEFORE THE FIRST TRUE INSTANCE FIELD LAUNCH. Add offline tests that intentionally interrupt promotion after each journal state and require the next preflight to detect the incomplete generation without launching. Require: (a) owner-first partial promotion + restart -> RecoveryRequired; (b) latest promoted without a complete owner set is rejected by pre-commit validation; (c) a Verified set re-hashes exactly to promotionSetFingerprint; (d) rollback reproduces baseline package hashes byte-for-byte; (e) stage/canonical same-file-identity or hardlink detection fails before authoring; and (f) Build twice unchanged still produces the identical package-set postimage defined in 17.48.

[P01381 | 290734:290735 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01382 | 290735:291157 | NORMAL_TEXT]
FIELD-AUTHORITY BOUNDARY. This section does not claim a new native package-write primitive or change the current field acceptance test. It is an implementation safety contract derived from the already proven owner-routing behavior and the two-resource StaticInstanceBinding closure. Native route observations, DirectIndex/culling proof, collision behavior, and per-instance translation remain separate FIELD-TESTED gates.

[P01383 | 291157:291158 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01384 | 291158:291778 | NORMAL_TEXT]
2026-08-20 SOURCE-DERIVED / IMPLEMENTATION UPDATE: Public D2 package-reader behavior confirms that block metadata can redirect reads into a separate physical patch file, so the now-required transform+bounds mutation can span multiple canonical package files. Izanami promotion should therefore be journaled as one package-set transaction: validate all stages, promote/verify physical owners first, promote the latest metadata-root last as the commit point, verify the complete canonical set, and reverse that order for rollback. This closes a mixed-generation failure mode without widening the native write assumptions.

[P01385 | 291778:291779 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01386 | 291779:291851 | NORMAL_TEXT]
17.50. SOURCE-DERIVED RENDER-COMPLETE STATIC GEOMETRY GATE — 2026-08-21

[P01387 | 291851:291852 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01388 | 291852:293095 | NORMAL_TEXT]
MEANINGFUL FINDING. The existing Shadowkeep bounds-correlation plan was still vulnerable to a false negative: it could compare an authored per-instance culling AABB against only the opaque static geometry even when the selected SStaticMesh also owns special-stage geometry. Published pre-Beyond-Light Alkahest shows SStaticMesh loading opaque_meshes plus special_meshes into one StaticModel. StaticModel::draw uses the already-bound shared instance scope and identical instance_count for both, drawing highest-detail opaque groups first and then highest-detail special meshes. The same source describes special meshes as transparent/decal/light-shaft-occluder/etc. geometry and gives them buffers/index ranges/techniques but no independent placement transform. Published later Alkahest then applies one group/per-instance visibility result before calling model.render_all for the visible static group, and render_all includes those special stages. Remote GitHub evidence only: cohaereo/alkahest prebl-0.5 crates/alkahest-data/src/statics.rs and crates/alkahest-renderer/src/ecs/render/static_geometry.rs; later corroboration from current crates/render/src/feature/static_geometry.rs. No unpublished local Izanami source is inferred from this.

[P01389 | 293095:293096 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01390 | 293096:294042 | NORMAL_TEXT]
IMPLEMENTATION CONSEQUENCE. StaticBoundsCorrelation should be explicit about geometry coverage. The robust predicted box for a transform is the union of all decoded highest-detail position-bearing geometry that shares that static placement and is gated by the same instance visibility contract. An OpaqueOnly prediction is acceptable as diagnostic evidence, but when specialMeshCount>0 it must not by itself downgrade DirectIndex or reject an otherwise coherent bounds candidate. Candidate ranking should prefer specialMeshCount==0 for the first unprojected Position-XYZ field proof because that removes an unrelated vertex-layout/render-stage assumption. If no route-safe isolated candidate is special-free, either decode the special buffers using their input-layout/buffer/index metadata and include them in the union, or mark geometryCoverageMode=SpecialPresentUnresolved and cap the mapping evidence below HighConfidenceDirectIndexCandidate.

[P01391 | 294042:294043 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01392 | 294043:294615 | NORMAL_TEXT]
CATALOG / BINDING PROVENANCE. Add specialMeshCount, specialRenderStages, specialGeometryFingerprint, geometryCoverageMode, geometryCoverageComplete, predictedOpaqueAabb, predictedRenderCompleteAabb (optional until complete), and boundsCorrelationCoveragePenalty. These are read-only diagnostic/proof inputs and are not mutable package seams. They belong in StructuralAuthorityFingerprint only to the extent required to prove the selected source static and the correlation recipe; Forge writes still preserve all mesh/static identities and render-stage data byte-for-byte.

[P01393 | 294615:294616 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01394 | 294616:295285 | NORMAL_TEXT]
FIRST-TEST RULE REMAINS NARROW. This finding does not widen the writable closure. The true acceptance experiment still starts from unprojected source topology, preserves every group/vector size and row, mesh identity, quaternion, scale, AO/opaque bytes, and outer row, changes exactly one 0x808071A3 Position XYZ, translates only its evidence-selected 0x80809673 AABB XYZ by the same delta, and conservatively expands independently attested collection bounds if required. Visual movement, multi-view culling, and collision remain separate acceptance signals. Prefer a special-free static so the culling correlation itself does not depend on incomplete render geometry.

[P01395 | 295285:295286 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01396 | 295286:295775 | NORMAL_TEXT]
DATED UPDATE — 2026-08-21 — SOURCE-DERIVED: same-era Alkahest proves opaque and special static geometry share one instance-placement scope; later Alkahest corroborates that group/per-instance visibility gates model.render_all across stages. Placement-candidate ranking and StaticBoundsCorrelation now track render-geometry completeness and prefer specialMeshCount==0 for the first true StaticInstanceBinding proof. No FIELD-TESTED Izanami capability claim is added by this source finding.

[P01397 | 295775:295776 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01398 | 295776:295900 | NORMAL_TEXT]
17.51 SOURCE-DERIVED PR RECHECK — ENTITY SPAWNER SUCCESSOR, RUNTIME TEXTURE OVERRIDE, AND FORGE-USEFUL TOOLING — 2026-08-21

[P01399 | 295900:295901 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01400 | 295901:296265 | NORMAL_TEXT]
SOURCE-DERIVED / REMOTE GITHUB ONLY. A fresh review of current stanuwu/Sunrise pull requests found several pieces that materially help Izanami even though most are not merge candidates. Preserve the dirty Izanami worktree and treat these branches as reverse-engineering/tooling evidence unless a narrow piece is deliberately reimplemented with Izanami validation.

[P01401 | 296265:296266 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01402 | 296266:297266 | NORMAL_TEXT]
PR #66 PLAYBOOK / MISSION CREATOR CONTAINS A SUBSTANTIALLY SAFER SUCCESSOR TO PR #46 ENTITY SPAWNER. PR #46 is closed/unmerged and its final spawn_runtime hard-codes the recovered PlacementInitialize, DirectInitialize, ObjectFactory, ObjectTransform, TagResolver, WorldRaycast, PlayerComponentUpdate, and object-datum descriptor RVAs. PR #66 is also closed/unmerged, but its inherited spawn runtime replaces the first six executable targets and the PlayerComponentUpdate target with narrow main-image signatures and resolves TagResolver from a validated relative call. The remaining major fixed-address seam is the object-datum descriptor RVA used to resolve a returned 32-bit datum into the live object record. This materially addresses the earlier maintainer objection to hard-coded function RVAs and makes #66 the better source basis for a future RuntimeObjectBinding adapter, while still requiring Izanami to recover/signature or otherwise validate the datum-table descriptor before adopting it.

[P01403 | 297266:297267 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01404 | 297267:297978 | NORMAL_TEXT]
RUNTIME SPAWN ABI REMAINS HIGH-VALUE EVIDENCE. The #66 implementation keeps the recovered PlacementInitialize/DirectInitialize -> placement descriptor -> ObjectFactory pipeline. It writes quaternion at descriptor +0x10 and {x,y,z,positive uniform scale} at +0x20, receives a 32-bit datum handle, and for object types requiring activation queues ObjectTransform on the controlled player's PlayerComponentUpdate seam after stock update. This matches Izanami's preferred thread-affinity architecture: editor/UI actions enqueue intent, while engine-object creation/transform work runs from a proven gameplay update context. Do not serialize the returned datum; it belongs only in an ephemeral RuntimeObjectBinding.

[P01405 | 297978:297979 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01406 | 297979:298745 | NORMAL_TEXT]
PR #66 ALSO ADDS REUSABLE FORGE TOOLING. Its client/content/blob_read.h provides bounded whole-value reads plus self-relative pointer/resource resolution with the class word immediately before the resource target, closely matching the ResourcePointer provenance already recovered for Shadowkeep package rows. It also adds a camera_projection helper that maps world positions to the Sunrise HUD from the resolved camera pose. These are useful design references for a Forge world-space selection/marker overlay and for consolidating package-blob parsing. The Mission Creator HUD/objective/playbook code is not a native Destiny UI node, but it demonstrates a practical world-marker/objective overlay architecture that could become the restrained in-game Forge surface.

[P01407 | 298745:298746 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01408 | 298746:299147 | NORMAL_TEXT]
PR #66 WAS CLOSED FOR PROJECT-SCOPE POLICY, NOT BECAUSE THESE TECHNICAL RESULTS WERE DISPROVEN. The maintainer comments state that new feature PRs are currently not accepted and that this client-heavy modding direction is outside Sunrise's intended architecture. That makes the code inappropriate to merge wholesale upstream, but it remains valuable reverse-engineering evidence for the Izanami fork.

[P01409 | 299147:299148 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01410 | 299148:299831 | NORMAL_TEXT]
PR #53 RUNTIME BOOTFLOW IS OPEN AND RELEVANT TO THE UI TRACK, BUT THE SEAM IS NARROWER THAN A GENERAL GPU-TAG REGISTRAR. Its override table is an explicit allowlist of 18 stock texture header/data TagHash pairs from package 0x010A. The GPU-entry dispatcher detour only substitutes when the incoming tag matches one of those known stock header/data identities, after validating the replacement DDS/Tiger header shape. Treat this as ResidentTextureOverride evidence: Izanami may be able to reskin known native/menu texture identities at runtime without repacking a package, but this does not prove arbitrary new texture TagHashes, new UI nodes, or arbitrary GPU-resource registration.

[P01411 | 299831:299832 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01412 | 299832:300481 | NORMAL_TEXT]
PR #58 WORLD POPULATION REMAINS CLOSED/UNMERGED AND ITS PLACEMENT EXTRACTION SHOULD BE TREATED AS HEURISTIC DISCOVERY ONLY. Its own field notes say extraction is unavailable on 175 of 466 locations, including the Moon, and the related Entity Spawner review explicitly says the extraction work was only partly correct: names were good, lists were not. Use #58 to learn candidate traversal patterns or discover approximate authored positions, but never use its extracted list/order as persistent PackagePlacementBinding authority. Current Sunrise build-data/cache catalogs are the preferred architectural home for reusable placement/spawn extraction.

[P01413 | 300481:300482 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01414 | 300482:300853 | NORMAL_TEXT]
PR #57 PRESENTATION CONTROLS IS CLOSED/UNMERGED BUT USEFUL FOR EDIT MODE. It provides signature-resolved native HUD suppression and first-person weapon hiding and was tested in game. Izanami can treat the underlying presentation seams as optional editor-mode polish after the package/runtime object path is reliable; they are not prerequisites for native placement work.

[P01415 | 300853:300854 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01416 | 300854:301563 | NORMAL_TEXT]
CURRENT PRIORITY CONSEQUENCE. Do not merge any of these PR branches into the dirty Izanami worktree before the current group-13/entity/collision field result. The strongest new implementation takeaway is narrower: when RuntimeObjectBinding becomes the active milestone, use the #66 signature-based spawn targets as the starting reverse-engineering evidence, replace/validate the remaining object-datum table fixed RVA, retain PlayerComponentUpdate as the execution seam, and bind the returned datum only ephemerally to ForgeUUID. In parallel, #53 provides the best current evidence for runtime TagHash-addressed custom textures, and #66 camera projection provides a usable pattern for in-world Forge markers.

[P01417 | 301563:301564 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01418 | 301564:302339 | NORMAL_TEXT]
DATED UPDATE — 2026-08-21 — SOURCE-DERIVED: current PR review found that the closed #66 Mission Creator branch contains a materially improved Entity Spawner successor: most native spawn/transform/raycast/update targets have been converted from the hard-coded RVAs in #46 to narrow signatures, leaving the object-datum descriptor as the main fixed-address seam. #66 also contributes bounded blob/resource-pointer helpers and world-to-screen camera projection useful to Forge. Open #53 provides a TagHash-addressed runtime GPU texture override useful for custom UI presentation. These findings improve the future RuntimeObjectBinding and UI implementation plan but do not change the pending group-13/entity/collision field package or add a new FIELD-TESTED Izanami capability.

[P01419 | 302339:302340 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01420 | 302340:302469 | NORMAL_TEXT]
17.52 SOURCE-DERIVED DEEP PR / CURRENT-MASTER PASS — RUNTIME RESIDENCY, DATUM LIFETIME, AND SPAWN-CATALOG AUTHORITY — 2026-08-21

[P01421 | 302469:302470 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01422 | 302470:302779 | NORMAL_TEXT]
SOURCE-DERIVED / REMOTE GITHUB ONLY. This pass inspected the actual #46/#66 spawn implementations, maintainer review history, current Sunrise world-step/build-data code, and the #53 texture override. It does not infer unpublished Izanami source or change the promoted group-13/entity/collision field package.

[P01423 | 302779:302780 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01424 | 302780:303456 | NORMAL_TEXT]
PR #46 REVIEW FEEDBACK SHOULD BE TREATED AS AN IZANAMI ARCHITECTURAL REQUIREMENT, NOT JUST UPSTREAM STYLE. The maintainer identified two merge blockers: hard-coded RVAs instead of patterns, and extraction living outside Sunrise's existing extraction/cache stack. After an attempted fix, the maintainer again objected to added RVAs and explicitly characterized extraction as only partly correct: names good, lists not. This reinforces two Forge rules: recovered executable targets must be signature/structurally validated, and persistent asset/placement catalogs must be rebuilt on the validated package-reader/build-data path rather than inheriting PR-local list assumptions.

[P01425 | 303456:303457 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01426 | 303457:304096 | NORMAL_TEXT]
PR #66 EXPOSES A USEFUL RUNTIME RESIDENCY ORACLE. The newer spawn runtime resolves a candidate definition through the native TagResolver and defines is_tag_resident(tag) as resolver(tag) != nullptr; request() refuses to spawn a tag unless that test passes. For Izanami this is a strong runtime discriminator for a cross-map asset palette: PackageReadable and RuntimeResident must be separate capability states. A foreign definition can exist in installed packages yet be unavailable to ObjectFactory in the current destination. Do not attempt to force a nonresident runtime spawn merely because PackagePlacementCatalog can read its bytes.

[P01427 | 304096:304097 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01428 | 304097:304870 | NORMAL_TEXT]
THE RETURNED 32-BIT DATUM HAS A CONCRETE EPHEMERAL VALIDATION CONTRACT. #66's remaining fixed-address object-datum descriptor contains a base pointer at descriptor +0x08 and stride at +0x10; the implementation requires stride 0xE0, derives the slot as base + (datum & 0x1FFF) * stride, and accepts the object only when the live-handle field at object +0x0C still equals the complete returned datum. This is much stronger than retaining a naked slot index. RuntimeObjectBinding should mirror that concept but replace the descriptor RVA with a recovered/validated seam: store the complete datum, validate generation/full handle before every transform/destruction operation, and invalidate the binding immediately when that equality fails. Raw datums remain non-serializable.

[P01429 | 304870:304871 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01430 | 304871:305563 | NORMAL_TEXT]
CURRENT SUNRISE MASTER ALREADY HAS A BETTER READ-ONLY SPAWN/ARRIVAL CATALOG FOUNDATION THAN PR #58. state/build_data/spawn_sets stores up to 65,536 world positions, grouped by package stem and spawn-set name hash, and records bubble masks plus whether a set is declared in the map package or only named activity packages. That metadata directly expresses residency/context relationships relevant to Forge: a spawn set in the map package travels with geometry, while activity-package sets depend on the selected activity package set. Prefer extending this integrated build-data domain for SpawnPlacementCatalog/arrival alignment instead of adopting PR #58's incomplete ad-hoc placement lists.

[P01431 | 305563:305564 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01432 | 305564:306216 | NORMAL_TEXT]
RUNTIME OBJECT COMMANDS SHOULD BE WORLD-EPOCH GATED. Current Sunrise's bootflow world-step accessor publishes activity steps and defines a fresh in-world state only for step 38 with a sample younger than one second; steps 33-37 are transitioning. A future RuntimeObjectBinding queue should therefore require a fresh in_world() observation before executing PlacementInitialize/ObjectFactory/ObjectTransform work, assign every live datum to a world/activity epoch, and discard/invalidate queued operations and handles when the world leaves step 38 or enters a new transition. A non-null player/object pointer by itself is not a sufficient lifetime gate.

[P01433 | 306216:306217 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01434 | 306217:307126 | NORMAL_TEXT]
CROSS-MAP ASSET PALETTE CONSEQUENCE. Keep at least three distinct capabilities per catalog asset: PackageStaticReadable/Relocatable for package-backed SStaticMesh/static-instance authoring; RuntimeDefinitionResident for definition/entity tags that pass the native TagResolver/ObjectFactory path in the current world; and RuntimeUnavailableNonresident for installed-but-unresolved tags. PR #66 does NOT prove that a raw SStaticMesh 0x808071A7 tag can be passed directly to ObjectFactory. Static meshes remain on the package-backed placement path unless an independently recovered entity/object-definition relationship proves otherwise. This distinction is especially important for the non-Tower baseplate question: first identify the foreign baseplate's static mesh and dependencies for package relocation/rebinding, while separately testing whether any corresponding runtime-spawnable definition is resident.

[P01435 | 307126:307127 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01436 | 307127:307539 | NORMAL_TEXT]
PR #53 TEXTURE OVERRIDE CONSEQUENCE. Reclassify it as ResidentTextureOverride, not arbitrary TagHash injection. The exact-stock-tag allowlist still makes it valuable for Forge presentation: known menu/boot/native texture identities can potentially be replaced at runtime with validated DDS content, but a general Toolbox icon/resource registry would need an additional registration or package-backed asset path.

[P01437 | 307539:307540 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01438 | 307540:308297 | NORMAL_TEXT]
IMMEDIATE IMPLEMENTATION ORDER FROM THIS PASS. (1) keep the current group-13/entity/collision field observation as the next field test; (2) for RuntimeObjectBinding research, port only the #66 signature-derived PlacementInitialize/DirectInitialize/ObjectFactory/ObjectTransform/raycast/update seams and recover the object-datum descriptor without a fixed RVA; (3) gate every runtime command on fresh world-step/epoch state and full-datum validation; (4) build cross-map asset capabilities around PackageReadable versus RuntimeResident rather than one generic 'available' flag; and (5) use Sunrise's integrated build-data/cache domains, especially spawn_sets and package class scans, as the persistent catalog substrate instead of PR-local extraction lists.

[P01439 | 308297:308298 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01440 | 308298:308936 | NORMAL_TEXT]
DATED UPDATE — 2026-08-21 — SOURCE-DERIVED: deep PR/current-master inspection found that #66's native TagResolver is directly useful as a runtime residency oracle, its datum-table logic gives a concrete full-handle lifetime check for ephemeral RuntimeObjectBinding, current Sunrise spawn_sets already supplies a better cache-integrated arrival/residency catalog than #58, and current world-step state provides the right epoch gate for live object commands. #53 was narrowed from 'arbitrary TagHash texture replacement' to an allowlisted resident-stock-texture override. No FIELD-TESTED Izanami capability claim is added by these findings

[P01441 | 308936:308937 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01442 | 308937:309021 | NORMAL_TEXT]
17.53 SOURCE-DERIVED CURRENT-MASTER ENTITY HOST / SCRIPT-HOST BOUNDARY — 2026-08-21

[P01443 | 309021:309547 | NORMAL_TEXT]
SOURCE-DERIVED / REMOTE GITHUB ONLY. This pass inspected the large current Sunrise gameplay/physics/entity-host subsystem and reconciled it with PR #46/#58/#66. The subsystem was already present in the upstream ancestry merged into the Izanami branch baseline, so this is not claimed as a post-baseline code addition; it is previously underused architecture that materially sharpens the runtime plan. It does not supersede any Codex/user FIELD-TESTED result and does not change the promoted group-13/entity/collision package.

[P01444 | 309547:309548 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01445 | 309548:310298 | NORMAL_TEXT]
A SERVER LOGICAL-ACTOR HOST ALREADY EXISTS. Current Sunrise has a generation-checked ActorStore plus a closed HostCommand surface covering logical actor spawn/remove, kinematic targets and teleport, motion authority, controllers/pathing, combat/damage, trigger create/remove, objective counters, participant credit, incident emission, tick timers, checkpoints, and reward intents. SpawnActorCommand explicitly creates a policy-owned logical actor without allocating wire identity. This means the future Forge/Fate scripting problem should not be framed as “build an actor host from scratch.” The missing layer is a scripting/policy frontend plus the client-visible replication body that turns authoritative logical actors into real Destiny entities.

[P01446 | 310298:310299 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01447 | 310299:311345 | NORMAL_TEXT]
THE GENERIC EXTERNAL ENTITY ENVELOPE IS SUBSTANTIALLY RECOVERED BUT NOT LIVE. middleware/gameplay/external/external_entity_codec defines a 13-bit entity slot plus 4-bit incarnation token, create/update/remove/lifecycle/anchor flags, entity types including sobject, and separate baseline/update type payloads. The server replication planner already maps Operation::create to entityCreate|entityUpdate, Operation::update to entityUpdate, and Operation::remove to entityRemove while preserving allocation generation, lifecycle sequence, bubble and token bounds. However, both the external entity codec/shadow source and the default settings make the current boundary explicit: gameplay_external_body is disabled and the codec comments that no caller exists yet. WorldCoordinator’s fallback is literally scriptless_payload_codec(), which supports only EntityType::sobject with zero baseline/update payload bytes. Therefore server-side create/update/remove wire semantics are SOURCE-DERIVED infrastructure, not a working replicated-object capability.

[P01448 | 311345:311346 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01449 | 311346:311924 | NORMAL_TEXT]
ARCHITECTURAL CORRECTION TO THE OLD PR #58 DESPAWN LIMITATION. PR #58’s client-only spawner could not despawn because removal belonged to the server side. Current Sunrise now contains a server actor lifecycle, allocation/incarnation model, remove planner operation and encoded entityRemove semantics. That supersedes the old architecture as a dead end, but it does NOT prove despawn in Destiny: until the external-body transport caller and the real type-specific sobject baseline/update payload are recovered, enabled and field-tested, replicated spawn/remove remains unproven.

[P01450 | 311924:311925 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01451 | 311925:312737 | NORMAL_TEXT]
RUNTIME BINDINGS SHOULD SPLIT INTO TWO BACKENDS. Keep PR #66 as evidence for ClientLocalRuntimeObjectBinding: native TagResolver residency, PlacementInitialize/DirectInitialize -> ObjectFactory, full-datum validation, game-thread/world-epoch gating, and immediate client-local lifetime. Separately define a future ReplicatedActorBinding around Sunrise’s logical ActorKey/generation plus server wire token {slot, incarnation}, allocation generation and lifecycle sequence. The two identities are not interchangeable: the PR #66 Destiny datum is a client native handle, while Sunrise’s 13+4 token is a network entity identity. Neither raw value belongs in persistent .iforge scene data; ForgeUUID remains the stable editor identity and may acquire one or both ephemeral runtime components depending on capability.

[P01452 | 312737:312738 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01453 | 312738:313431 | NORMAL_TEXT]
THE “SCRIPT HOST” GAP IS NOW MUCH NARROWER. A future Fate/mission scripting frontend should target the typed HostCommand surface rather than directly poking client native memory. That gives deterministic, validated intents for actor spawn/remove, movement, triggers, objectives, timers, checkpoint/reward requests and related gameplay policy. No actual general script VM/frontend was found in this pass, and the README’s new bungie-lua-decompiler reference is research tooling rather than proof of a Sunrise Lua host. Treat the command host as the server-policy substrate; do not claim Fate execution until a frontend/dispatcher and its persistence/authority rules are implemented and tested.

[P01454 | 313431:313432 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01455 | 313432:314123 | NORMAL_TEXT]
PHYSICS OWNERSHIP MUST REMAIN SEPARATED. The large server/gameplay/physics backend uses Sunrise-owned proxy/simulation structures (including AABB-style intersection logic); it is not a shortcut for editing Destiny’s native map Havok. By contrast, the merged client noclip hook signature-resolves native hkpSimulation and a character-motion vtable, walks active/inactive islands, and refreshes/verifies the current character rigid body before changing its motion state. That is useful native-Havok diagnostic/lifetime evidence, but it does not identify or author static map collision shapes. Package CollisionPlacementBinding remains the correct path for the six Tower Havok-owning map rows.

[P01456 | 314123:314124 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01457 | 314124:314842 | NORMAL_TEXT]
CROSS-MAP TOOLBOX CONSEQUENCE. Build the all-game browser as capability layers rather than one object list. Current package_class_scan can enumerate installed entries by class/package family, so 0x808071A7 static meshes can form a global PackageStaticReadable catalog. PR #66 TagResolver independently determines current-world RuntimeDefinitionResident definitions. A third ReplicatedActorCapable state should remain disabled/unknown until the sobject external payload schema and transport integration are recovered. This makes it possible to list a foreign baseplate or prop without falsely implying that package relocation, client-local ObjectFactory spawning, and server-replicated spawning are the same operation.

[P01458 | 314842:314843 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01459 | 314843:315678 | NORMAL_TEXT]
NEXT RESEARCH TARGETS. For the client-local path, recover/validate the #66 object-datum table descriptor without a fixed RVA and separately recover destruction semantics if needed. For the replicated path, prioritize the missing external entity type-0/sobject baseline and update body: determine where blueprint/definition identity and transform/state are encoded, locate the intended gameplay_external_body transport caller/gate, and use retail traces/history/source to recover the exact client contract. Do not enable gameplay_external_body simply because the generic envelope parses; the current zero-payload scriptless fallback is explicit evidence that the native body contract is still incomplete. Keep the current package-backed StaticInstanceBinding and group-13/collision field observation as the immediate project milestone.

[P01460 | 315678:315679 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01461 | 315679:316534 | NORMAL_TEXT]
DATED UPDATE — 2026-08-21 — SOURCE-DERIVED: deeper current-master inspection found that Sunrise already contains most of a deterministic server logical-actor host and generic entity lifecycle/replication planner, including create/update/remove wire-envelope semantics with generation/incarnation safety. The crucial missing seam is now more specific: gameplay_external_body has no active caller, is disabled by default, and the only coordinator fallback is an empty type-0 sobject payload. This splits Forge runtime work into a near-term client-local #66 ObjectFactory backend and a later replicated actor backend, and reframes the script-host problem as adding a frontend/policy adapter plus recovering the real native sobject payload rather than inventing the entire host architecture. No FIELD-TESTED Izanami capability claim is added by this finding.

[P01462 | 316534:316597 | HEADING_1]
17.54 FIELD-TESTED BLACK-SCREEN RESULT AND ENTITY-CLASS REPAIR

[P01463 | 316597:317126 | NORMAL_TEXT]
FIELD-TESTED RESULT. The promoted group-13/broad-null-row/collision candidate completed activity host setup, changed to city_tower_social_d2, completed the initial slice transition and physics join, and entered activity:in_world. Destiny remained responsive, but the screen stayed black and no Guardian materialized. No package-trust rejection, world-transition failure, or process crash appeared. This isolates the failure downstream of world loading and makes loss of required world/bootstrap placement data the leading cause.

[P01464 | 317126:317879 | NORMAL_TEXT]
SOURCE-DERIVED CORRECTION. The failed builder rule treated every null-resource 0x90 map row whose first word merely looked like a package tag as an entity placement. That classification was too broad. Sunrise PR #58 identifies 0x808099D6 as the placement-table class but accepts a row as an authored entity placement only when its tag resolves to entity-definition class 0x80809C0F. PR #46 and its #66 successor use the same 0x80809C0F entity-definition identity. Current Sunrise master independently keeps player arrival data in the integrated spawn_sets catalog and only attaches a spawn-set hash when its declaring map/activity package is loaded. Therefore the previous count of 227 means tag-shaped null-resource rows, not 227 proven prop entities.

[P01465 | 317879:318441 | NORMAL_TEXT]
IMPLEMENTED REPAIR. custom_package_builder now resolves each null-resource row tag through the package reader and suppresses the row only when the resolved class is exactly 0x80809C0F. Unreadable, non-entity, spawn/bootstrap, and otherwise unclassified rows fail closed and remain byte-identical. The six field-inspected 0x80807246 collision-resource rows remain a separate suppression path. This should preserve the Guardian/bootstrap data while retaining a narrowly justified entity-prop quarantine, but the causal claim remains pending the next field retest.

[P01466 | 318441:318964 | NORMAL_TEXT]
BUILD AND PACKAGE STATE. Destiny was closed after the black-screen observation. The failed active package family was archived under .izanami-failed-broad-null-row-quarantine-black-screen. Canonical Tower patches 2/3/4/5/8 were restored to the pre-flat-surface routing baseline as independent single-link files and hash-verified against their rollback sources. The corrected Release DLL was built and deployed identically to both game locations with SHA-256 3E9478FE0001E5AFC2796F35F1FB2833598681A118512BDD348437CD7CFB96DB.

[P01467 | 318964:319487 | NORMAL_TEXT]
NEXT CONTROL. Start Destiny with the corrected DLL, open Izanami Forge, select Blank Baseplate / Tower Carrier Control, and press Build Blank World Draft exactly once. Do not field-launch that draft before the game is closed and the generated stage files are independently validated and promoted. The next field acceptance signals are: Guardian spawns, group-13 renders as the isolated surface, loose true-entity props are reduced, and the six disconnected collision collections no longer create the previous phantom walls

[P01468 | 319487:319585 | NORMAL_TEXT]
17.55 SOURCE-DERIVED OBJECT-DATUM RVA ELIMINATION PATH AND TYPE-AWARE ENTITY TOOLBOX — 2026-08-21

[P01469 | 319585:319914 | NORMAL_TEXT]
SOURCE-DERIVED / REMOTE GITHUB ONLY. This pass inspected current Sunrise handle-resolution targets plus PR #66's entity-name/spawn-panel implementation. It does not infer unpublished Izanami source, does not add a FIELD-TESTED runtime-object capability, and does not change Section 17.54's corrected black-screen control/retest.

[P01470 | 319914:319915 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01471 | 319915:320871 | NORMAL_TEXT]
CURRENT MASTER PROVIDES A CONCRETE STYLE FOR ELIMINATING FIXED TABLE/GLOBAL RVAS. client/content/handles/handle_resolver resolves content handles through a caller-supplied tables slot, validates table/record bounds and stride, and deliberately avoids retaining a raw game pointer. client/targets/game/game_content_targets derives that tables slot from the uniquely resolved queuezObjectResolver signature by decoding its RIP-relative displacement, and separately validates nearby immediates/calls before publishing the target group. This content-handle resolver is NOT the same ABI as PR #66's live object-datum table: its namespace requires content table ids >=1024 and its descriptor/record correction model differs. The important reusable result is the resolution method: find a stable native consumer, decode its RIP-relative table/global operand, validate layout invariants, then publish a complete target set instead of keeping module+RVA constants.

[P01472 | 320871:320872 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01473 | 320872:322043 | NORMAL_TEXT]
HYPOTHESIS / READ-ONLY VALIDATION EXPERIMENT FOR THE REMAINING PR #66 OBJECT-DATUM RVA. Current teleport_lifecycle already signature-resolves Destiny's controlled-biped-handle function. The recovered signature reaches the same low-13-bit datum indexing idiom used by #66: `AND 0x1FFF` followed immediately by an `IMUL` whose memory operand is RIP-relative. PR #66 independently resolves a returned object datum as base + (datum & 0x1FFF) * stride, requires stride == 0xE0, and accepts the record only when object+0x0C contains the complete original datum. The next RuntimeObjectBinding reverse-engineering step should therefore decode the controlled-handle function's RIP-relative IMUL operand and adjacent object-table/base access read-only, then require the #66 invariants against the current controlled-player datum. If the decoded table supplies stride 0xE0 and the resulting slot's +0x0C full handle equals the controlled datum, promote that exact signature/operand relationship to a validated ObjectDatumTable target and remove the fixed `module + 0x1F93420` seam. A merely plausible pointer/stride is not sufficient and must not enable spawn/transform operations.

[P01474 | 322043:322044 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01475 | 322044:322924 | NORMAL_TEXT]
PR #66 ALSO PROVIDES A MUCH SAFER ENTITY-TOOLBOX TAXONOMY THAN A GENERIC TAG LIST. entity_name_cache scans installed named-bag class 0x80809478, follows budget header/body classes 0x808099D1/0x80809F10, and retains associated tags only when they resolve to entity-definition class 0x80809C0F before attaching localized aliases. Its spawn panel then scans 0x80809C0F package entries, rejects tags that are not currently resident through TagResolver, reads the native object-type byte, and groups candidates by semantic type. Recovered type values include StaticMesh=1, PropCosmeticStatic=4, PropCosmeticMovable=5, PropNetworkedStatic=7, PropNetworkedMovable=8, Interactive=11, Biped=12, Vehicle=15, Emitter=17, Projectile=18, ItemAmmo=20, ItemLoot=21, and System=28. These are native ENTITY-definition categories and must remain distinct from package static-mesh class 0x808071A7.

[P01476 | 322924:322925 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01477 | 322925:323648 | NORMAL_TEXT]
SECTION 17.54 CONSEQUENCE. The implemented repair that suppresses a null-resource row only when its tag resolves exactly to 0x80809C0F remains the correct immediate control and should be field-tested unchanged. For later blank-world cleanup, however, entity class alone should not automatically imply 'safe prop to remove.' Extend the read-only entity-placement/catalog layer with objectType/name/package provenance so cosmetic props can be separated from Biped, Interactive, System, networked, or other potentially bootstrap/gameplay-relevant entities. This is a future safety refinement, not a claim that one of those categories caused the black screen; preserve the current corrected retest as the causal discriminator.

[P01478 | 323648:323649 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01479 | 323649:324355 | NORMAL_TEXT]
CACHE / CAPABILITY DESIGN. Do not copy PR #66's standalone EntityNames.json freshness rule into persistent Forge data: that cache's quick `current()` test only checks its generator marker near the file header and does not prove the installed package inventory is unchanged. Rebuild entity-name/type catalog data inside Sunrise's existing build-data/cache pipeline with the package-directory/content fingerprint as authority. Keep runtime residency dynamic and world-epoch scoped. The all-game Toolbox can then expose separate states such as PackageEntityReadable, NamedEntity, ObjectTypeKnown, RuntimeResident, and RuntimeSpawnable, alongside the separate PackageStaticReadable path for 0x808071A7 meshes.

[P01480 | 324355:324356 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01481 | 324356:324956 | NORMAL_TEXT]
DATED UPDATE — 2026-08-21 — SOURCE-DERIVED: current-master handle resolution suggests a concrete path to eliminate PR #66's last major fixed object-datum RVA by decoding the already-signature-resolved controlled-handle consumer and validating the same low-13-bit / 0xE0-stride / full-datum invariants. PR #66's named-bag + exact 0x80809C0F + object-type pipeline also sharpens both the Forge Toolbox and future entity-quarantine safety. The Section 17.54 corrected field retest remains unchanged. No local repository files, DLLs, packages, or running Destiny process were changed by this research pa

[P01482 | 324956:325017 | HEADING_1]
17.55 CLASS-GATED FIELD RESULT AND VISIBILITY-BUNDLE CONTROL

[P01483 | 325017:325529 | NORMAL_TEXT]
FIELD RESULT. The rebuilt class-gated draft identified 227 Tower-local rows whose tags resolve exactly to entity-definition class 0x80809C0F, plus six inline resources of class 0x80807246 that affected the tested replacement path. This proves the 227 rows are genuine entity placements. It does not make any of them a player-spawn record. Player arrival is now package-confirmed as a separate spawn-set domain: class 0x80809162 owns sets whose inline 0x80809164 rows carry rotation, position, and set-name hash.

[P01484 | 325529:326028 | NORMAL_TEXT]
VISIBILITY-BUNDLE CONTROL. custom_package_builder preserves all 227 class-validated entity placements byte-for-byte and disconnects six 0x80807246 visibility-bundle resources. Each affected placement is reduced to scale 0.0001 and its resource-relative pointer is cleared. Telemetry now reports preserved_entities=227 and visibility_bundles=6. This control does not touch the 30 direct-Havok placement rows or the 16 entity-model placement rows now identified across Tower base and activity layers.

[P01485 | 326028:326782 | NORMAL_TEXT]
BUILD AND INDEPENDENT VALIDATION. The Release DLL in both game locations remains SHA-256 52CBE48F94AFFFDDDA9716ACF3BDBEAE9C0A53CCCD077359D629E60CBDCE9739. The generated visibility-bundle control stage passed the rebuilt tag-probe against an isolated package directory and again after promotion against the active package directory. The active Tower map table 0x80ED22FB remains readable with one row and transform rotation [0,0,0,1], translation [82.79,42.272,10.525], and scale 1.0. Map graph root 0x80ED2352 resolves 820 nodes and 161 tables. Probe telemetry was entities=227, suppressed=0, disconnected visibility-bundle rows=6. The six affected visibility-bundle tables are 0x80ED2270, 0x80ED25AF, 0x80ED266E, 0x80ED29F4, 0x80ED2CC2, and 0x80ED3976.

[P01486 | 326782:327546 | NORMAL_TEXT]
PROMOTION AND ROLLBACK. With Destiny fully closed, the validated candidate was promoted to active Tower patches 2, 3, 4, 5, and 8. Guarded preflight verified every playable-baseline hash and every candidate hash before changing a canonical package. Rollback hardlinks were created beside each active package with suffix .izanami-pre-collision-only-control. Active candidate SHA-256 values are: patch 2 49AD5B294806F3C9754E9046BA03C98B61FAF7C9796F942C91624F6A2E5DAED3; patch 3 143F696D66C6E1917A3A8F29E80A0EBAF92BBE0A6CC06DF5357AAE1BD4CF5335; patch 4 D8434CD9D908A3A07340F1811D0689C9DFC380DBA567D39353B82C1DC4BE98A9; patch 5 AA7ABCC7A3E603DC4ADC60F8EB0E7E1744FFF1295463DA3FFB43D97D1F9E1740; patch 8 F88EFF9D15A8CD7852E2C7882D8A74380E41181C8EAC62CCFF3B5CDA32ED5AB5.

[P01487 | 327546:327996 | NORMAL_TEXT]
COMPLETED FIELD CONTROL. This test has been run. The Guardian loaded, many presentation/gameplay objects remained, phantom collision remained, and the selected replacement was a staircase/floor fragment without matched collision. It proved that preserving the 227 base entities is compatible with arrival and that suppressing six visibility bundles is not a complete blank-world or collision solution. The next controls are defined in Section 17.58.

[P01488 | 327996:328047 | HEADING_1]
17.56 INSTALLED MAP, ENTITY, AND RESOURCE TAXONOMY

[P01489 | 328047:328068 | HEADING_2]
SCOPE AND CONFIDENCE

[P01490 | 328068:328812 | NORMAL_TEXT]
This section inventories every map package family in the installed Shadowkeep-format Destiny 2 package set used by this Sunrise build. It does not claim coverage of every map from later retail versions or content that is not installed locally. Evidence labels are strict: SOURCE-DERIVED means named by Sunrise source or the recovered native enum; PACKAGE-CONFIRMED means decoded consistently from the installed package inventory; FIELD-TESTED means observed in the running game; NAME-DERIVED means a role inferred only from a package-family name; HYPOTHESIS means a proposed explanation that still needs a controlled test. Package scans were run against an isolated playable-baseline package view, so the active game packages were not changed.

[P01491 | 328812:328813 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01492 | 328813:328844 | HEADING_2]
VISIBILITY-BUNDLE FIELD RESULT

[P01493 | 328844:329467 | NORMAL_TEXT]
FIELD-TESTED. The collision-only control loaded far enough for direct world observation. Large numbers of animated entities, lights, interactables, VFX, loose props, and other objects remained. Phantom collision remained where visible scenery had already been removed. The replacement visual selected as a supposed baseplate was actually part of a staircase/floor assembly, and that injected staircase fragment did not have its matching collision. This falsifies two earlier assumptions: class 0x80807246 is not the Tower's complete collision system, and the selected replacement asset is not a valid standalone baseplate.

[P01494 | 329467:329468 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01495 | 329468:329991 | NORMAL_TEXT]
FIELD-TESTED/PACKAGE-CONFIRMED INTERPRETATION. Disconnecting the six Tower rows of class 0x80807246 affected the tested replacement path but did not remove legacy structural collision. Across all 424 installed rows, 363 payloads directly reference Umbra 24/0 visibility/occlusion assets, while only 95 have a structured path to Havok within depth four. The evidence-safe label is VisibilityBundle_OptionalHavok_FieldCollision. Its exact native class name remains unknown, and it must not be treated as all world collision.

[P01496 | 329991:329992 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01497 | 329992:330013 | HEADING_2]
SHARED PACKAGE SHAPE

[P01498 | 330013:330609 | NORMAL_TEXT]
PACKAGE-CONFIRMED. The scanner found 14,838 entries referenced as map-data-table class 0x808099D6. Of these, 14,837 passed the common array-layout checks; one globals entry did not have the normal map-table layout and was rejected rather than force-parsed. Every valid table uses the same decoded shape: array descriptor at +0x08, fixed 0x90-byte placement rows, and an inline-resource relative pointer at row +0x78. The scan classified all 161,426 valid placement rows without a malformed row: 63,345 rows resolve to entity-definition class 0x80809C0F, and 98,081 rows contain inline resources.

[P01499 | 330609:330610 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01500 | 330610:331082 | NORMAL_TEXT]
PACKAGE-CONFIRMED. The 164 physical map package families collapse into 85 logical map families. Seventy-nine logical families have both a base package and a paired _activities package. The six unpaired roots are activities, environments, globals, mercury_trials_lighthouse, orphaned, and pvp_vex_tube. Package-family roots, table tags, row transforms, referenced tags, resource classes, and geometry indices remain map-specific even though the container format is shared.

[P01501 | 331082:331083 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01502 | 331083:331118 | HEADING_2]
SOURCE-DERIVED ENTITY OBJECT TYPES

[P01503 | 331118:331742 | NORMAL_TEXT]
The native entity-definition class is 0x80809C0F and the object-type byte is at definition +0x96. The complete recovered source enum is: Inherited=0; StaticMesh=1; PropSimpleDeprecated=2; PropExpensiveDeprecated=3; PropCosmeticStatic=4; PropCosmeticMovable=5; PropCosmeticMovableGarbage=6; PropNetworkedStatic=7; PropNetworkedMovable=8; PropCinematic=9; Speedtree=10; Interactive=11; Biped=12; Creature=13; Weapon=14; Vehicle=15; Turret=16; Emitter=17; Projectile=18; Item=19; ItemAmmo=20; ItemLoot=21; Gear=22; HopOn=23; HopOnGearBiped=24; HopOnGearWeapon=25; HopOnGearShip=26; HopOnGearSparrow=27; System=28; Invalid=255.

[P01504 | 331742:331743 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01505 | 331743:332639 | NORMAL_TEXT]
PACKAGE-CONFIRMED DEFINITION/PLACEMENT COUNTS. StaticMesh 8,195/25,323; PropSimpleDeprecated 688/2,314; PropExpensiveDeprecated 72/2,458; PropCosmeticStatic 1,102/3,550; PropCosmeticMovable 190/2,294; PropCosmeticMovableGarbage 802/97; PropNetworkedStatic 397/7,858; PropNetworkedMovable 148/2,978; PropCinematic 6,745/408; Speedtree 1/0; Interactive 1,026/2,875; Biped 888/25; Creature 11/129; Weapon 416/16; Vehicle 78/34; Turret 102/16; Emitter 8,093/11,960; Projectile 553/63; Item 26/1; ItemAmmo 9/0; ItemLoot 47/9; Gear 1,311/0; HopOn 3,961/24; HopOnGearBiped 5,943/0; HopOnGearWeapon 3,292/0; HopOnGearShip 717/0; System 1,422/913. Inherited, HopOnGearSparrow, and Invalid had no readable definition or placement in this installed inventory. A definition count is not an instance count: one definition can be placed many times, and many definitions are not directly present in map tables.

[P01506 | 332639:332640 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01507 | 332640:333168 | NORMAL_TEXT]
INTERPRETIVE GROUPING. StaticMesh, Prop*, PropCinematic, Speedtree, and Emitter are presentation/world-object categories. Interactive, Biped, Creature, Weapon, Vehicle, Turret, Projectile, Item, ItemAmmo, and ItemLoot are gameplay-facing actor/item categories. Gear and HopOn* are equipment or attachment-oriented categories. System is engine/gameplay infrastructure. This grouping follows the source names but remains an interpretation; object type alone does not prove that an instance is safe to remove, spawn, or transform.

[P01508 | 333168:333169 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01509 | 333169:333196 | HEADING_2]
INLINE RESOURCE PLACEMENTS

[P01510 | 333196:333744 | NORMAL_TEXT]
SOURCE-DERIVED/DIRECT-REFERENCE-CONFIRMED. The census found 51 inline resource classes. Eleven now have evidence-safe categories: StaticMap 0x808071B3; Terrain 0x8080714B; visibility bundle with optional Havok 0x80807246; direct-Havok placement 0x8080929B; entity-model placement 0x80806DE0; expensive-light sequence 0x80807133; light collection 0x80806F5A; map decals 0x80806E62; sky objects 0x80806F91; Wwise event sequence 0x80806B5B; and Wwise event placement 0x80806B59. Forty placement classes remain without an evidence-safe semantic label.

[P01511 | 333744:333745 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01512 | 333745:334357 | NORMAL_TEXT]
PACKAGE-CONFIRMED HIGH-FREQUENCY CLASSES, shown as base/activity counts: unclassified 0x80806CBF 21,567/0; Wwise sequence 0x80806B5B 15,124/5,290; unclassified 0x808038A0 4,616/5,580; unclassified activity-heavy 0x80806725 4/8,508; Wwise placement 0x80806B59 5,481/2,600; unclassified 0x80806B7F 2,635/1,340; expensive-light sequence 0x80807133 3,323/0; unclassified 0x80806FAD 3,194/88; entity-model placement 0x80806DE0 2,283/0; unclassified 0x808089E8 1,257/869; direct-Havok placement 0x8080929B 1,427/354. Evidence-safe labels describe observed references; they do not claim recovered native wrapper names.

[P01513 | 334357:334358 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01514 | 334358:334393 | HEADING_2]
BASE LAYERS VERSUS ACTIVITY LAYERS

[P01515 | 334393:334859 | NORMAL_TEXT]
PACKAGE-CONFIRMED. All 1,338 StaticMap rows, all 1,608 Terrain rows, and all 424 class-0x80807246 rows occur in base or unpaired package families; none occur in an _activities package. Entity placements split 34,551 in base/unpaired layers and 28,794 in activity layers. Other inline resources split 71,489 in base/unpaired layers and 26,592 in activity layers. A complete world therefore cannot be reduced reliably by modifying only the base package's entity rows.

[P01516 | 334859:334860 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01517 | 334860:335353 | NORMAL_TEXT]
PACKAGE-CONFIRMED WITH BOUNDED INFERENCE. Classes 0x80806725 (8,508 of 8,512 rows in activity layers) and 0x80806733 (474 of 482) are activity-heavy and reference the recurring 0x80807F52 family; their exact roles remain unknown. Class 0x80807133 is an expensive-light sequence and 0x80806DE0 is an entity-model placement, both base-only in this inventory. Class 0x80806CBF is also base-only but remains semantically unclassified. Distribution is a prioritization signal, not write authority.

[P01518 | 335353:335354 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01519 | 335354:335371 | HEADING_2]
TOWER CASE STUDY

[P01520 | 335371:335714 | NORMAL_TEXT]
PACKAGE-CONFIRMED. city_tower_d2 base contains 136 valid tables and 1,563 rows: 227 entity placements and 1,336 inline resources, including 13 StaticMap rows and six class-0x80807246 rows. Its entity types are 102 StaticMesh, 53 Emitter, 29 PropSimpleDeprecated, 22 PropCosmeticMovable, nine Interactive, eight System, and four PropCinematic.

[P01521 | 335714:335715 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01522 | 335715:336200 | NORMAL_TEXT]
PACKAGE-CONFIRMED. city_tower_d2_activities independently contains 90 valid tables and 3,315 rows: 1,625 entity placements and 1,690 inline resources. Its entities include 1,493 StaticMesh, 63 PropCosmeticStatic, 19 PropSimpleDeprecated, 15 PropCosmeticMovable, nine ItemLoot, eight System, seven PropNetworkedMovable, four Biped, four Emitter, two PropCinematic, and one Weapon. Its inline rows include 1,430 instances of unknown class 0x808038A0 and 125 of unknown class 0x80806725.

[P01523 | 336200:336201 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01524 | 336201:336754 | NORMAL_TEXT]
CORRECTED INFERENCE. The untouched activity layer remains the leading explanation for surviving visible and animated Tower objects, but the collision ownership is now sharper. Tower contains 30 untouched 0x8080929B direct-Havok placement rows, split 14 base and 16 activity, plus 16 base 0x80806DE0 entity-model placement rows of which 15 directly reference Havok. These are the leading package-level explanation for phantom structural collision. The 13 StaticMap parents remain visual/aggregate candidates and are no longer the first collision target.

[P01525 | 336754:336755 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01526 | 336755:336793 | HEADING_2]
COMPLETE LOGICAL MAP-FAMILY INVENTORY

[P01527 | 336793:336948 | NORMAL_TEXT]
NAME-DERIVED ROLE ONLY. These roles are organizational labels inferred from package names; the counts and existence of every family are package-confirmed.

[P01528 | 336948:336949 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01529 | 336949:336980 | NORMAL_TEXT]
Dungeon (1): dungeon_prophecy.

[P01530 | 336980:336981 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01531 | 336981:337095 | NORMAL_TEXT]
Gambit arenas (6): gambit_badlands, gambit_dreamycliffs, gambit_hold, gambit_ledge, gambit_scrap, gambit_trinity.

[P01532 | 337095:337096 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01533 | 337096:337127 | NORMAL_TEXT]
Orbit/front-end (1): orbit_d2.

[P01534 | 337127:337128 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01535 | 337128:337584 | NORMAL_TEXT]
PvP arenas (32): pvp_anomaly_2, pvp_arena_hive_2, pvp_bacon, pvp_bannerfall_2, pvp_city_defense_2, pvp_cliffside, pvp_colony_ship_2, pvp_echo, pvp_elevator, pvp_estoc, pvp_factory_2, pvp_fort, pvp_glaive, pvp_greenhouse_2, pvp_grove, pvp_hull, pvp_katana, pvp_longshot_2, pvp_manhattan, pvp_mojo, pvp_ness, pvp_observatory, pvp_peak, pvp_pickles, pvp_sabre, pvp_shaft, pvp_slag, pvp_street, pvp_utopia, pvp_vex_tube, pvp_vex_tube_2, pvp_wilderness_town_2.

[P01536 | 337584:337585 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01537 | 337585:337666 | NORMAL_TEXT]
Seasonal/event spaces (3): advent_summer_event, infinite_forest_spring, sundial.

[P01538 | 337666:337667 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01539 | 337667:337751 | NORMAL_TEXT]
Shared/system families (5): activities, bootstrap, environments, globals, orphaned.

[P01540 | 337751:337752 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01541 | 337752:337892 | NORMAL_TEXT]
Social spaces (6): city_tower_d16_t0, city_tower_d2, d2_campaign_social_space, mercury_trials_lighthouse, trials_social_space, trophy_hall.

[P01542 | 337892:337893 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01543 | 337893:338349 | NORMAL_TEXT]
World/mission spaces (31): arcade_ember, arcade_homecoming, arcade_reunion, arcade_spark, arcade_thunder, black_garden, cabal_ship, cayde_6_feet_under, commando, cosmo_killers_01, cosmo_launchpad, dreaming_city, eden, edz, fleet, infinite_forest_live, last_city_crater, last_city_liberation, leviathan, luna, mercury_destination, mercury_lost_woods, pandora, penumbra, planet_x, polaris, prison_of_elders, sabotage, sky_island, tangled_shore, the_journey.

[P01544 | 338349:338350 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01545 | 338350:338368 | HEADING_2]
WHAT IS CONFIRMED

[P01546 | 338368:339036 | NORMAL_TEXT]
The map table and entity-definition formats are shared across the installed package set. Visual entities, inline world resources, collision, activity behavior, and player-arrival/bootstrap data are distinct ownership domains. Base and activity layers coexist for most logical maps. Removing a render placement does not remove its collision, and injecting a visual resource does not automatically inject matching physics. The current staircase result proves that the selected surface asset and collision resource were mismatched. The global reuse of class 0x80807246 proves it is not Tower-specific, while the field result proves it is not the entire collision system.

[P01547 | 339036:339037 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01548 | 339037:339056 | HEADING_2]
WORKING HYPOTHESES

[P01549 | 339056:339935 | NORMAL_TEXT]
The surviving Tower scenery and behavior are primarily sourced by city_tower_d2_activities plus unsuppressed base inline resources. The main phantom structural collision is most likely owned by the untouched direct-Havok and model-linked placement rows, with additional nested physics still possible, rather than by the six visibility bundles alone. Class 0x808038A0 must be downgraded to an opaque data-only/marker candidate: its 10,196 rows are mixed across base and activity layers and no stable direct package-tag association appears in the first decoded 0x90-byte window. No exact semantic name is justified. Classes 0x80806725 and 0x80806733 are likely encounter/activity infrastructure because they are almost activity-exclusive. None of these hypotheses should drive destructive package rewrites without a one-class, one-layer control and independent package validation.

[P01550 | 339935:339936 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01551 | 339936:339976 | HEADING_2]
FORGE CONSEQUENCES AND NEXT EXPERIMENTS

[P01552 | 339976:340217 | NORMAL_TEXT]
1. Extend the builder and probe to treat each logical map as a base-plus-activities composition and record package family, layer, table tag, row index, transform, entity object type, resource class, and dependency graph for every placement.

[P01553 | 340217:340420 | NORMAL_TEXT]
2. Isolate the Tower activity layer in controls instead of treating the 227 base entities as the whole world. Preserve player-arrival, spawn-set, host, and bootstrap records until positively identified.

[P01554 | 340420:340540 | NORMAL_TEXT]
3. Decode class 0x808038A0 and the activity-exclusive 0x80806725/0x80806733 families before broad activity suppression.

[P01555 | 340540:340830 | NORMAL_TEXT]
4. Run controlled Tower tests against the 30 direct-Havok rows first, split base versus activity, then against the 15 model-linked Havok rows while preserving spawn sets and roster-critical data. Traverse StaticMap subtrees only if collision remains after those direct owners are isolated.

[P01556 | 340830:341027 | NORMAL_TEXT]
5. Replace the staircase fragment with a field-identified flat mesh and its matched collision resource. A Forge baseplate asset must be validated as a pair: visible geometry plus walkable physics.

[P01557 | 341027:341306 | NORMAL_TEXT]
6. Keep future experiments single-axis: base entities, activity entities, one inline class, one StaticMap subtree, or one collision subtree per build. Record Guardian spawn, world render, UI responsiveness, visible deltas, collision deltas, and crash/freeze behavior separately.

[P01558 | 341306:341642 | NORMAL_TEXT]
7. Use the resulting inventory as the Forge Explorer/Toolbox data model. The editor should show package availability, logical map/layer, native object type, dependency state, runtime residency, render support, collision support, and whether transform/spawn is actually writable rather than presenting every tag as an equivalent object.

[P01559 | 341642:341643 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01560 | 341643:341666 | HEADING_2]
REPRODUCIBLE ARTIFACTS

[P01561 | 341666:342316 | NORMAL_TEXT]
The read-only probes are B:\!!izanami\Depot\tag-probe\src\bin\map-census.rs, resource-shape-census.rs, tag-class-graph-census.rs, collision-bundle-paths.rs, tower-collision-inventory.rs, and spawn-set-census.rs. Outputs are under B:\!!izanami\Depot\tag-probe\census-output-20260821. The new row-level files are tower-collision-resource-rows.tsv and spawn-points.tsv; their compact summaries are tower-collision-resource-summary.md and spawn-set-summary.md. The census and probes did not change active Destiny packages. Source terminology was corrected and the local Release DLL compiled successfully, but it was not copied into either game location.

[P01562 | 342316:342317 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01563 | 342317:342318 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01564 | 342318:342419 | HEADING_1]
17.57 SOURCE-DERIVED ACTIVITY-LAYER ROSTER CRITICALITY AND PACKAGE-INVENTORY CORRECTION — 2026-08-21

[P01565 | 342419:342933 | NORMAL_TEXT]
SOURCE-DERIVED / REMOTE GITHUB ONLY. This pass inspected the typed scenario/roster path in current Sunrise and at the remote izanami-forge branch head, plus the package-class scanner used by both trees. The roster logic is already present in the Izanami branch ancestry, so this is an underused safety contract rather than a post-baseline feature. It does not infer unpublished dirty-local source, does not change the FIELD-TESTED map/entity/resource census in Section 17.56, and adds no runtime capability claim.

[P01566 | 342933:342934 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01567 | 342934:343827 | NORMAL_TEXT]
BROAD _activities SUPPRESSION IS NOT SAFE UNTIL ROSTER-CRITICAL OBJECTS ARE MASKED. Sunrise's scenario roster builder follows destination bubble/slice state into registries and placed objects, resolves each object's declared slot descriptors, and refuses to publish a group that is short even one declared descriptor. The source comments are unusually explicit about the consequence: the client holds the whole current-bubble apply while a required record is unseeded, and the publish path notes that an absent expected key can be dereferenced unchecked on switch-out. Therefore Section 17.56's activity-layer discovery must not be converted into blanket city_tower_d2_activities suppression merely because a class is frequent or visually prop-like. Activity-layer rows can participate in player binding, lifetime, authority, or bubble lifecycle even when their visible role looks incidental.

[P01568 | 343827:343828 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01569 | 343828:344764 | NORMAL_TEXT]
THE ROSTER SAFETY SEAM IS BYTE/TYPE-IDENTIFIABLE ENOUGH TO BUILD A READ-ONLY MASK. Sunrise's placed-object slot-descriptor class is 0x80809C36, reached through known chain classes 0x80809468 and 0x80809B14. The recovered descriptor carries registryKey at +0x30, slot type at +0x34, slot index at +0x36, sense schema at +0x44, and auth schema at +0x48. The scenario builder explicitly recognizes slot type 13 as Participation/player-binding and slot type 17 as Lifetime; auth/sense presence is reduced to the wire flags, with an auth schema meaning the host holds authority and the object reaches the world through the bubble grant. Candidate ordering prioritizes player-binding, lifetime-reporting, and primary-registry groups. The installed publish universe is small enough to protect deliberately: the source reports only 56 installed objects carrying publishable wire slot types, despite walking thousands of placed objects overall.

[P01570 | 344764:344765 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01571 | 344765:345731 | NORMAL_TEXT]
SLICE-SET INTERSECTION GIVES A REAL DESTINATION-SPECIFIC CRITICALITY MODEL. Sunrise's roster-intersection/publish code classifies a registry key present in every slice set as top-level, a key present in only some slice sets as per-bubble with an explicit bubble mask, and a key absent from the destination as dropped; inconsistent duplicate declarations are treated as invalid rather than silently normalized. Izanami should expose this as a read-only RosterCriticalMask / ActivityLayerSafetyCatalog before any activity cleanup. Recommended provenance per protected object is: logical map family; base/activity layer; scenario and registry identity; placed-object tag; registry key; roster group; slot index/type/flags; critical reason = Participation13 | Lifetime17 | AuthSenseSlot | PrimaryRegistry | OtherRosterSlot; top-level/per-bubble classification; slice-set/bubble mask; source package/tag/block route; and any validated dependency path to a map-table row.

[P01572 | 345731:345732 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01573 | 345732:346466 | NORMAL_TEXT]
DO NOT ASSUME SCENARIO-REGISTRY OBJECT TAG == MAP-TABLE ENTITY ROW. The roster walk proves critical scenario object identity and lifecycle topology, but it does not by itself prove that a registry object tag is the same native identity stored in one of Section 17.56's 0x808099D6 map rows. Until the graph relation is explicitly resolved, protect the roster object's package/dependency closure and classify potentially related map rows as ProtectedUnknown rather than guessing an exact row mapping. A map row should become rosterCritical only after a typed/validated dependency edge connects it to the roster object or definition. This keeps the safety mask useful without turning another heuristic TagHash walk into write authority.

[P01574 | 346466:346467 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01575 | 346467:347353 | NORMAL_TEXT]
SAFER FIRST ACTIVITY-LAYER CONTROL. After the currently promoted collision/activity control is observed, preserve all RosterCritical and ProtectedUnknown objects and run one-axis activity experiments only on rows proven outside that mask. The first useful control can suppress one non-critical entity object-type family from city_tower_d2_activities, or one inline resource class, while leaving every other activity row byte-identical. StaticMesh or Emitter are plausible high-volume candidates only after no roster reachability is demonstrated; their names alone are not a safety proof. Record Guardian materialization, world/apply completion, bubble/switch-out behavior, UI responsiveness, render delta, VFX/interactable delta, and collision delta separately. This sharpens Section 17.56's instruction to preserve spawn/host/bootstrap state into an implementable source-derived gate.

[P01576 | 347353:347354 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01577 | 347354:348079 | NORMAL_TEXT]
PACKAGE-INVENTORY CORRECTION. Current Sunrise master and the remote Izanami branch package_class_scan expose class-filtered scan_class / scan_class_entries, not a generic all-entry scan API. The generic scan_entries inventory walk inspected in the Mission Creator/#66 lineage is a branch addition, not an upstream-current capability. Section 17.56's local census is therefore valid as a separate read-only artifact, but if Izanami wants the all-game Toolbox inventory inside the main Sunrise build-data/cache path it should deliberately port/refactor that narrow generic visitor behavior, preserve current package-family/fingerprint validation, and avoid claiming that current master already supplies an all-entry cache API.

[P01578 | 348079:348080 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01579 | 348080:348488 | NORMAL_TEXT]
BRANCH-INTEGRATION NOTE. The public remote izanami-forge branch is currently diverged from public master, and the dirty local worktree remains authoritative. Do not wholesale merge/rebase merely to obtain any of the source patterns above. Compare/reimplement the small roster-criticality and inventory seams file-by-file so Codex's unpublished field-test changes and package safety work are not overwritten.

[P01580 | 348488:348489 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01581 | 348489:349361 | NORMAL_TEXT]
DATED UPDATE — 2026-08-21 — SOURCE-DERIVED: the current scenario roster implementation provides a concrete safety reason and a tractable typed mask for the untouched Tower activity layer: missing/incomplete roster groups can stall current-bubble apply, and a missing published key is explicitly unsafe on switch-out. Before suppressing city_tower_d2_activities content, Izanami should preserve Participation/Lifetime/authority/primary-registry objects and their unresolved dependency closure, then run one-class or one-object-type controls only outside that mask. Also corrected the package-inventory assumption: current master/remote Izanami provide class-filter scans, while the generic all-entry scanner is a PR-branch addition that must be deliberately integrated. No local repository files, DLLs, packages, or running Destiny process were changed by this research pa

[P01582 | 349361:349362 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01583 | 349362:349429 | HEADING_1]
17.58 CROSS-MAP VALIDATION, COLLISION OWNERSHIP, AND SPAWN DOMAINS

[P01584 | 349429:349458 | HEADING_2]
FORMAT CORRECTION AND METHOD

[P01585 | 349458:350022 | NORMAL_TEXT]
PACKAGE/SOURCE CORRECTION. In this installed Shadowkeep format, file type/subtype 26/7 is Havok, 27/0 is Criware video, and 24/0 is Umbra visibility/occlusion data. An earlier exploratory probe treated 27/0 as Havok; every collision conclusion in this section was regenerated after correcting that discriminator. Direct references were profiled over the first decoded 0x90 bytes of all 98,081 inline resource placements. Dependency traversal follows only structured 8/0 and 16/0 tags, so arbitrary words inside raw binary payloads cannot create false graph edges.

[P01586 | 350022:350365 | NORMAL_TEXT]
COVERAGE. The read-only baseline contains 14,837 structurally valid map tables, 161,426 placement rows, 63,345 entity placements, 98,081 inline resource placements, 386 spawn-set tags, and 8,892 decoded spawn points. Cross-map controls include large destinations, a dungeon, Gambit, PvP, a seasonal space, Tower, and orbit/front-end packages.

[P01587 | 350365:350397 | HEADING_2]
EVIDENCE-SAFE RESOURCE TAXONOMY

[P01588 | 350397:350963 | NORMAL_TEXT]
DIRECT PHYSICS AND MODEL WRAPPERS. Class 0x8080929B appears 1,781 times; every row directly references Havok 26/7 at resource +0x10, and 1,502 rows carry a second Havok reference at +0x60. Class 0x80806DE0 appears 2,283 times; every row directly references source-named s_entity_model class 0x808073A5 at +0x10, and 2,173 rows (95.2 percent) directly reference Havok at +0x40. Evidence-safe labels are HavokPlacement_DirectConfirmed and EntityModelPlacement_RefConfirmed. These labels describe the wrapper's observed references, not a recovered native wrapper name.

[P01589 | 350963:351545 | NORMAL_TEXT]
PRESENTATION AND AUDIO WRAPPERS. Class 0x80807133 has 3,323 base-only rows and always references s_expensive_light at +0x10. Class 0x80806F5A has 719 rows and always references s_light_collection at +0x10. Class 0x80806E62 has 760 rows, 759 of which reference s_map_decals at +0x10. Class 0x80806F91 has 177 rows and always references s_sky_objects at +0x10. Classes 0x80806B5B and 0x80806B59 have 20,414 and 8,081 rows respectively; 99.3 percent directly reference source-named s_wwise_event at +0x10. StaticMap 0x808071B3 and Terrain 0x8080714B retain their source-derived names.

[P01590 | 351545:351574 | HEADING_2]
VISIBILITY-BUNDLE CORRECTION

[P01591 | 351574:352046 | NORMAL_TEXT]
Class 0x80807246 has 424 base-only rows across 79 logical map families. Every row points at a unique 0x80807320 payload. Of those payloads, 363 directly reference one or more Umbra 24/0 assets. Only 95 have a structured path to Havok within depth four: 34 at depth one, 22 at depth two, six at depth three, and 33 at depth four; 329 have no such path. The primary category is therefore a visibility/world bundle with optional physics, not a universal collision placement.

[P01592 | 352046:352403 | NORMAL_TEXT]
Tower has six of these bundles. Five directly reference Umbra assets, but only table 0x80ED25AF reaches Havok through 0x808092DB and table 0x80ED29F4 reaches Havok directly. The other four have no structured Havok path within depth four. This explains why suppressing all six had a narrow field effect without removing Tower's phantom structural collision.

[P01593 | 352403:352439 | HEADING_2]
TOWER ROW-LEVEL COLLISION INVENTORY

[P01594 | 352439:352932 | NORMAL_TEXT]
The Tower base-plus-activity inventory contains 65 rows in the four collision-relevant categories currently under study: 13 StaticMap rows, six visibility bundles, 16 entity-model rows, 14 base direct-Havok rows, and 16 activity direct-Havok rows. All 30 class-0x8080929B rows carry explicit Havok tags and span broad Tower coordinates. They use five distinct Havok tags across five map tables, which is consistent with instantiated structural collision regions rather than one global toggle.

[P01595 | 352932:353400 | NORMAL_TEXT]
Fifteen of Tower's 16 entity-model rows directly reference the same Havok tag 0x80C6D120 at resource +0x40; the remaining row has no direct Havok reference in its decoded window. The 13 StaticMap placement parents have no direct Havok reference in their placement windows, and only 33 of 2,504 StaticMap parent tags globally reach Havok within four structured graph steps. The next collision control should therefore target direct-Havok rows before StaticMap parents.

[P01596 | 353400:353436 | HEADING_2]
PLAYER ARRIVAL IS A SEPARATE DOMAIN

[P01597 | 353436:353856 | NORMAL_TEXT]
SOURCE/PACKAGE-CONFIRMED. Player starts are not members of the 227 Tower base entity placements. Sunrise's spawn reader identifies spawn-set class 0x80809162 and 48-byte inline point class 0x80809164; each point carries rotation, position, and a set-name hash. The installed census found 386 set tags, 385 valid non-empty sets, and 8,892 points across 83 physical package families and 77 of the 85 logical map families.

[P01598 | 353856:354283 | NORMAL_TEXT]
Tower owns five base spawn sets and one activity spawn set: 61 points total, with 34 ordinary-arrival points carrying default hash 0x2EA8FB98 and 27 points carrying other hashes. Set 0x80ED3B2D contains 12 default points bounded by X 16.88 to 34.62, Y 63.37 to 66.13, and Z 18.97 to 18.99. The existing Forge target near (26, 65, 18.9) lies inside that authored arrival cluster, independently validating the target coordinate.

[P01599 | 354283:354728 | NORMAL_TEXT]
Eight logical families have no directly owned spawn-set tag in the scanned inventory: bootstrap, environments, gambit_dreamycliffs, globals, mercury_trials_lighthouse, orbit_d2, pvp_vex_tube_2, and pvp_wilderness_town_2. Some are shared/front-end or may rely on another loaded package. A blank-world package must therefore preserve or deliberately author a compatible spawn set and scenario binding; retaining entity rows alone is insufficient.

[P01600 | 354728:354762 | HEADING_2]
REPRESENTATIVE CROSS-MAP CONTROLS

[P01601 | 354762:355346 | NORMAL_TEXT]
Tower combines 13 StaticMap, six visibility bundles, 30 direct-Havok, 16 entity-model, 46 expensive-light, 12 decal, 10 light-collection, and two sky-object rows. EDZ combines 188 StaticMap, 219 Terrain, 47 visibility bundles, 82 direct-Havok, 124 entity-model, 263 expensive-light, 70 decal, 72 light-collection, and eight sky-object rows. Dreaming City has 67 StaticMap, 107 Terrain, 21 bundles, 192 direct-Havok, 110 entity-model, and 236 expensive-light rows. Prophecy has seven StaticMap, 24 Terrain, three bundles, 31 direct-Havok, 35 entity-model, and 83 expensive-light rows.

[P01602 | 355346:355904 | NORMAL_TEXT]
Gambit Badlands has two StaticMap, eight Terrain, one bundle, 43 direct-Havok, and three entity-model rows. Bannerfall has two StaticMap and one visibility bundle whose payload reaches Havok, but no dedicated 0x8080929B or 0x80806DE0 row. Orbit is the decisive negative control: it has 21 visibility bundles, 13 sky-object rows, and 12 StaticMap rows, but no direct-Havok, Terrain, or entity-model placement; none of its 21 bundle payloads reaches Havok within depth four. This strongly separates visibility/scene packaging from general collision ownership.

[P01603 | 355904:355942 | HEADING_2]
COLLISION COMPOSITION IS MAP-SPECIFIC

[P01604 | 355942:356474 | NORMAL_TEXT]
Across 85 logical map families, no single carrier is universal. Using T=Terrain, B=visibility bundle, H=direct-Havok placement, and M=entity-model placement: 30 families contain T+B+H+M; 26 contain T+B+M without H; seven contain B only; four contain none of these four; four contain T+B only; four contain T+B+H; three contain B+H; three contain B+H+M; two contain B+M; one contains M only; and one contains H only. A custom map composer must build a typed dependency set per map rather than applying one global suppression recipe.

[P01605 | 356474:356507 | HEADING_2]
REVISED UNKNOWN-CLASS BOUNDARIES

[P01606 | 356507:357125 | NORMAL_TEXT]
Class 0x808038A0 has 10,196 rows split 4,616 base and 5,580 activity. It has no material stable direct package-tag association in the first 0x90-byte window, so the earlier generic activity-support label is withdrawn; it remains an opaque data-only/marker candidate. Class 0x80806725 has 8,512 rows, 8,508 in activity layers, and always references 0x80807F52 at +0x20 plus 0x80806745 at +0x28. Class 0x80806733 has 482 rows, 474 in activity layers; 468 occur as exactly 78 rows in each of the six Gambit activity families. These distributions support activity-oriented hypotheses but do not establish exact semantics.

[P01607 | 357125:357420 | NORMAL_TEXT]
Class 0x80806CBF has 21,567 base-only rows. Nearly every row references class 0x80806F68 in a repeating sequence, and 0x80806F68 tags consistently reference technique/scope families, but the placement wrapper's exact role remains unknown. It should not be suppressed merely because it is large.

[P01608 | 357420:357445 | HEADING_2]
ENGINEERING CONSEQUENCES

[P01609 | 357445:357717 | NORMAL_TEXT]
1. Blank-world composition must be category- and layer-aware. Preserve scenario, roster-critical, spawn-set, host, and bootstrap data while isolating entities, static world, terrain, physics, visibility, lighting, decals, sky, audio, and activity resources independently.

[P01610 | 357717:358022 | NORMAL_TEXT]
2. The next controlled phantom-collision test should suppress only the 14 base direct-Havok rows, then only the 16 activity direct-Havok rows, followed by the 15 model-linked Havok rows if needed. Guardian materialization, UI responsiveness, collision delta, and render delta must be recorded separately.

[P01611 | 358022:358371 | NORMAL_TEXT]
3. A usable baseplate requires matched visual geometry and walkable physics. The staircase experiment proved that redirecting a StaticMap parent does not automatically redirect or instantiate matching collision. Entity-model wrappers with paired Havok are promising schema examples, but no Tower row is yet proven to be a standalone flat baseplate.

[P01612 | 358371:358692 | NORMAL_TEXT]
4. The custom package path should explicitly select or author a spawn set instead of assuming an absent hash or an entity placement will produce arrival. Tower set 0x80ED3B2D is a validated carrier control; a true custom package needs its own point set, compatible scenario/slice binding, and preserved roster lifecycle.

[P01613 | 358692:359136 | NORMAL_TEXT]
5. The Forge Explorer/Toolbox data model should expose separate roots for Entities, Static World, Terrain, Physics, Visibility, Lighting, Decals, Sky, Audio, Spawn and Activity. Each item needs package/layer provenance, native/evidence-safe type, dependency and residency state, render support, collision support, and actual spawn/transform capability. A tag must not be presented as movable merely because its map-table transform is readable.

[P01614 | 359136:359182 | HEADING_2]
SOURCE CORRECTIONS AND REPRODUCIBLE ARTIFACTS

[P01615 | 359182:359573 | NORMAL_TEXT]
The builder's internal 0x80807246 terminology and Forge status text were corrected from world collision to visibility bundle. This is a naming and telemetry correction only; package-edit behavior was not expanded. The local Release target compiled successfully to build\x64\Release\steam_api64.dll. It was not copied into either game directory, and active Destiny packages were not changed.

[P01616 | 359573:360137 | NORMAL_TEXT]
Read-only artifacts are under B:\!!izanami\Depot\tag-probe\census-output-20260821. Key files are resource-class-reference-windows.tsv, collision-bundle-paths.tsv, tower-collision-resource-rows.tsv, spawn-set-family-census.tsv, and spawn-points.tsv. Compact summaries are resource-class-profiles.md, collision-bundle-path-summary.md, tower-collision-resource-summary.md, and spawn-set-summary.md. Probe sources are map-census.rs, resource-shape-census.rs, tag-class-graph-census.rs, collision-bundle-paths.rs, tower-collision-inventory.rs, and spawn-set-census.rs.

[P01617 | 360137:360157 | HEADING_2]
CONFIDENCE BOUNDARY

[P01618 | 360157:360709 | NORMAL_TEXT]
The shared map-table, entity-definition, spawn-set, direct-Havok, and direct-reference classifications are package- or source-confirmed. Exact native names for many placement wrappers remain unknown. A structured dependency path proves reachability, not runtime ownership; a direct Havok reference is stronger but still requires a one-axis field test before it becomes package-write authority. No conclusion here establishes that arbitrary retail Destiny maps can be safely repackaged without their scenario, roster, streaming, and activity contracts.

[P01619 | 360709:360710 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01620 | 360710:360711 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01621 | 360711:360812 | NORMAL_TEXT]
17.59 SOURCE-DERIVED PR #77 CACHE VERSION RECOVERY AND FORGE BUILD-DATA DOMAIN CONTRACT — 2026-08-21

[P01622 | 360812:361116 | NORMAL_TEXT]
SOURCE-DERIVED / REMOTE GITHUB ONLY. PR #77 merged into Sunrise master on 2026-08-21; this section is now current-master behavior rather than an unmerged-branch proposal. It does not infer unpublished dirty-local Izanami source, change any FIELD-TESTED capability, or modify the running package/DLL set.

[P01623 | 361116:361117 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01624 | 361117:362018 | NORMAL_TEXT]
PR #77 CORRECTS A DEVELOPMENT-CACHE FAILURE MODE THAT MATTERS FOR IZANAMI. Current master’s build-data cache reader treats an older cache format as stale/rebuildable but treats a cache whose formatVersion is newer than the executable as invalid. PR #77 changes that policy so any format-version mismatch is stale and therefore rebuildable, while bad magic remains invalid. In a multi-writer development workflow where Codex, Izanami experiments, and upstream-derived builds may advance cache schemas at different times, the current-master behavior can strand a perfectly disposable newer cache as a hard invalid state when temporarily running an older binary. Izanami should deliberately adopt the PR #77 mismatch=>stale/rebuild rule for build-data caches, or isolate Forge’s catalog cache under its own versioned namespace, rather than requiring manual cache surgery during branch/build transitions.

[P01625 | 362018:362019 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01626 | 362019:362696 | NORMAL_TEXT]
CURRENT MASTER ALREADY HAS THE RIGHT PUBLISHING MODEL FOR A FORGE CATALOG. state/build_data/runtime/domain_markers.cpp maintains per-domain readiness with SRW-locked clear/publish/ready markers instead of exposing partially rebuilt data. A future ForgeAssetCatalog should be another complete-generation domain, not an ad-hoc JSON file or PR-local list. Recommended generation identity is {cacheFormatVersion, packageInventoryFingerprint, extractorRevision, schemaRevision}. Build into scratch state, validate counts/routes/class markers, then publish the generation atomically; readers retain the last complete generation or report unavailable, never a half-populated catalog.

[P01627 | 362696:362697 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01628 | 362697:363197 | NORMAL_TEXT]
SEPARATE CACHE AUTHORITY FROM RUNTIME AUTHORITY. Persistent catalog rows may cache package/tag/class/name/object-type/map-layer/resource-route facts under the package inventory fingerprint. Do not cache PR #66 TagResolver residency, Destiny datum handles, world epochs, or replicated actor tokens as durable build-data facts: those remain dynamic per-world/per-session capability state. A cache hit can prove PackageReadable/Named/ObjectTypeKnown provenance, not RuntimeResident or RuntimeSpawnable.

[P01629 | 363197:363198 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01630 | 363198:363668 | NORMAL_TEXT]
IMPLEMENTATION CONSEQUENCE. Deliberately reimplement the small PR #77 stale-version behavior and a typed ForgeAssetCatalog domain inside the validated Sunrise build-data/cache architecture; do not wholesale merge/rebase the dirty Izanami worktree for it. The same domain can consume the generic all-entry inventory visitor only after that #66-branch behavior is independently ported as noted in Section 17.57. No package/DLL/runtime mutation is implied by this section.

[P01631 | 363668:363669 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01632 | 363669:364198 | NORMAL_TEXT]
DATED UPDATE — 2026-08-21 — SOURCE-DERIVED: PR #77 exposes a concrete cache-version recovery rule that is safer for Izanami’s fast-moving catalog schemas: any version mismatch rebuilds instead of treating a newer cache as permanently invalid. Current master’s per-domain publish markers provide the matching atomic-generation architecture. Forge’s persistent Toolbox/Explorer catalog should therefore become a package-fingerprinted build-data domain, while runtime residency and native handles remain uncached world-epoch state.

[P01633 | 364198:364199 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01634 | 364199:364311 | NORMAL_TEXT]
17.60 SOURCE-DERIVED PR #50/#69 + CURRENT NOCLIP — COMMAND THREADING AND COLLISION-ACCEPTANCE MODE — 2026-08-21

[P01635 | 364311:364574 | NORMAL_TEXT]
SOURCE-DERIVED / REMOTE GITHUB ONLY, with PR-author field observations explicitly labeled separately below. This section does not claim Izanami field-testing of these controls and does not alter the current package-backed collision or StaticInstanceBinding plan.

[P01636 | 364574:364575 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01637 | 364575:365653 | NORMAL_TEXT]
PR #50 PROVIDES A USEFUL REQUEST/RESULT QUEUE PATTERN BUT THE WRONG EXECUTION THREAD FOR NATIVE OBJECT WORK. Its console queue is a bounded FIFO with a monotonic nonzero u64 ticket, SRW-lock-protected submission, and a drain path that removes one invocation under the lock but executes the handler after releasing the lock, then reports the result by ticket. That is a good model for the external Forge editor: requests should carry ticket, sceneRevision, backend, and worldEpochSnapshot; results should carry the same identifiers so stale responses cannot mutate a newer scene state. However, PR #50 drains from overlay rendering, so its execution context is render/frame code. Do not run ObjectFactory/ObjectTransform from that queue drain. The ClientLocalRuntime backend should drain only from the already recovered PR #66 PlayerComponentUpdate seam, with fresh in_world/world-epoch and full-datum validation; package-build commands can use a separate non-native backend. Preserve the PR #50 rule that potentially expensive/recursive handlers execute outside the queue lock.

[P01638 | 365653:365654 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01639 | 365654:366347 | NORMAL_TEXT]
PR #69 NO-TURNBACK IS USEFUL AS EDITOR TRANSIT, NOT AS A COLLISION ACCEPTANCE CONDITION. The branch signature-resolves a native turnback target, verifies the expected instruction preimage before patching, and restores the original bytes on disable/uninstall. Its contributor field report says the no-turnback patch immediately removes the countdown and restoring it restores normal turnback/death behavior. The same report notes godmode has respawn/state side effects and can leave abnormal low-health/passive-regeneration/turnback behavior after disable. Treat no-turnback as optional EditorTransitMode convenience and keep godmode out of the default Forge editing/collision-validation path.

[P01640 | 366347:366348 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01641 | 366348:367409 | NORMAL_TEXT]
CURRENT MASTER PLAYER-MOVEMENT OVERRIDES CAN MASK THE EXACT COLLISION SIGNAL IZANAMI IS TRYING TO MEASURE. horizontal_noclip hooks native hkpSimulation::stepDeltaTime, finds a character-motion rigid body in Havok islands, captures pre-step horizontal state, runs the original step, then overwrites selected horizontal lanes; that island scan does not itself prove the body is the controlled Guardian. Independently, current fly writes the controlled player's horizontal velocity before Havok and restores the player's Z/vertical velocity after Havok through the teleport physics-component seam. Both can alter the observed collision outcome without changing static map Havok. Therefore any field test intended to prove the 14 base direct-Havok rows, 16 activity direct-Havok rows, 15 model-linked Havok rows, or a future CollisionPlacementBinding MUST run in CollisionAcceptanceMode with fly=false, noclip=false, noTurnback=false, and godmode=false. Otherwise real support/collision can be present while movement assistance masks or replaces the native result.

[P01642 | 367409:367410 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01643 | 367410:367971 | NORMAL_TEXT]
TWO EXPLICIT FORGE TEST MODES. EditorTransitMode may enable fly/noclip and optionally no-turnback for camera/visual inspection, asset identification, and traversal only; observations collected there are not collision acceptance evidence. CollisionAcceptanceMode explicitly requires fly=false, noclip=false, noTurnback=false, and godmode=false and is the only mode allowed to promote a package collision hypothesis to FIELD-PROVEN. Log the mode with every field observation so render movement, Guardian materialization, support, and collision are not conflated.

[P01644 | 367971:367972 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01645 | 367972:368527 | NORMAL_TEXT]
IMMEDIATE PROJECT CONSEQUENCE. The next Section 17.58 collision controls should preserve their one-axis package mutation order and additionally lock CollisionAcceptanceMode before observation. Separately, the two-surface editor should adopt a ticketed ForgeCommandBus patterned after PR #50 but route native runtime commands to the PR #66 gameplay-update execution seam rather than the render thread. PR #50 and #69 remain reverse-engineering/architecture evidence, not merge candidates, and the dirty local worktree should not be rebased to obtain them.

[P01646 | 368527:368528 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01647 | 368528:369225 | NORMAL_TEXT]
DATED UPDATE — 2026-08-21 — SOURCE-DERIVED / PR-FIELD-OBSERVED: PR #50 contributes a safe ticketed queue pattern but drains from render code, so Izanami’s native object backend must keep PR #66’s gameplay-thread affinity. PR #69 makes no-turnback a plausible editor-transit aid, while current master noclip explicitly overwrites post-Havok player motion and can therefore invalidate collision acceptance. Added explicit EditorTransitMode versus CollisionAcceptanceMode; the direct-Havok/model-linked collision controls must be judged only with all movement/godmode/turnback overrides disabled. No local repository files, DLLs, packages, or running Destiny process were changed by this research pa

[P01648 | 369225:369326 | NORMAL_TEXT]
17.61 SOURCE-DERIVED REPLICATED REMOVE LIFECYCLE AND RUNTIME-TARGET RESOLUTION CONTRACT — 2026-08-21

[P01649 | 369326:369327 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01650 | 369327:369668 | NORMAL_TEXT]
SOURCE-DERIVED / REMOTE GITHUB ONLY. This pass inspected current Sunrise master plus the relevant PR lineage for replicated external entities and native target resolution. It does not infer unpublished Izanami source, does not change the promoted Tower package set, and does not upgrade any runtime-spawn/despawn capability to FIELD-TESTED.

[P01651 | 369668:369669 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01652 | 369669:370783 | NORMAL_TEXT]
STRICT REPLICATED REMOVE IS NOW A CONCRETE SERVER-SIDE LIFECYCLE, NOT JUST A GENERIC FLAG. Current external_entity_codec defines a 17-bit entity token as 13-bit slot + 4-bit incarnation and reserves entityRemove = 0x0004. The strict administrative remove body is deliberately minimal: exact remove lifecycle form, no anchor, no trailing state, lifecycle revision zero, zero baseline/update payload, and a one-bit false subrecord. replication_planner::request_remove does not simply erase state: if a create was never committed and nothing is in flight it may release the allocation immediately without emitting a pointless remove; otherwise removal remains pending until causally ready. external_plan converts that operation into the strict remove envelope, and replication_outcomes releases the peer allocation and clears the actor record only after the matching remove contribution succeeds. Commit/outcome validation is tied to peer generation, actor-record generation, allocation, contribution ticket, packet generation, and version state, preventing a stale acknowledgement from deleting a newer incarnation.

[P01653 | 370783:370784 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01654 | 370784:371707 | NORMAL_TEXT]
RUNTIME CAPABILITY BOUNDARY. This materially improves the future ReplicatedActorBinding design and supersedes the old architectural assumption that server-backed deletion would need to be invented from scratch. It still does NOT prove live Destiny-visible despawn: the gameplay_external_body transport/caller remains gated/incomplete and the real client-visible sobject payload contract is not yet established. Therefore replicated deletion and client-local native deletion remain separate backends. A future ReplicatedActorBinding should model RequestRemove -> causally-ready strict remove -> acknowledged outcome -> allocation release/record clear, keyed by complete token/incarnation plus peer/world generation. A ClientLocalRuntimeObjectBinding created through PR #66 still needs an independently recovered native destruction seam; do not substitute a server remove envelope for local ObjectFactory object destruction.

[P01655 | 371707:371708 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01656 | 371708:373073 | NORMAL_TEXT]
PR #66 NATIVE TARGETS SHOULD ENTER SUNRISE'S SHARED TARGET-RESOLUTION SWEEP RATHER THAN EACH RUNNING A STANDALONE PE SCAN. Merged PR #24 changed the core signature matcher to anchor on the first exact byte and current patterns::registry preserves fail-closed uniqueness: a second match invalidates the target. Current client activation inspects the executable image/ranges once, then resolves the main game-target definition set as one ordered sweep with exact failed-target reporting. By contrast, scan_main_image_unique performs its own module/range inspection for each optional target. When RuntimeObjectBinding becomes active, port the #66 PlacementInitialize, DirectInitialize, ObjectFactory, ObjectTransform, PlayerComponentUpdate, TagResolver anchor, and optional raycast signatures into one Forge runtime-object target group resolved from the already-inspected executable ranges. Expose RuntimeObjectsAvailable only when the required group resolves coherently; an optional Forge-group miss should disable that backend without killing unrelated Sunrise activation. This centralizes uniqueness/version evidence, avoids repeated executable-range scans, and produces one target-set fingerprint. Add the object-datum descriptor to the same group only after the Section 17.55 signature-derived descriptor hypothesis validates; never fall back to #66's fixed RVA.

[P01657 | 373073:373074 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01658 | 373074:373962 | NORMAL_TEXT]
FULL DATUM IDENTITY MUST REMAIN DISTINCT FROM LOW-13-BIT PLAYER-PHYSICS OWNERSHIP. Current teleport/player-physics code intentionally compares the controlled handle's low 13-bit index for short-lived player-body attribution, and its own comments note that physics owns player position while direct object-placement writes can move the camera alone. That is appropriate for a current-tick player-physics seam, but it is not sufficient lifetime identity for arbitrary spawned objects. RuntimeObjectBinding must continue to retain the complete returned datum, validate the full live-handle equality/generation before every operation, and bind it to a fresh world epoch. Treat PlayerPhysicsOwnership = low13/current context and RuntimeObjectIdentity = full datum/generation/world epoch as different concepts so teleport helper logic is never reused as a generic spawned-object validity test.

[P01659 | 373962:373963 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01660 | 373963:374621 | NORMAL_TEXT]
IMMEDIATE IMPLEMENTATION CONSEQUENCE. The collision/baseplate field sequence remains unchanged and should not be combined with these runtime findings. After the current package-backed StaticInstanceBinding/collision controls, the RuntimeObjectBinding implementation order is: shared optional signature group -> validated object-datum descriptor -> fresh in-world/world-epoch gate -> full-datum validity -> create/transform queue on gameplay update -> separately recovered local destruction. In parallel, any future ReplicatedActorBinding deletion should use the strict causal/acknowledged remove lifecycle above rather than immediate server-record deletion.

[P01661 | 374621:374622 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01662 | 374622:375373 | NORMAL_TEXT]
DATED UPDATE — 2026-08-21 — SOURCE-DERIVED: current Sunrise master exposes an exact causal replicated-remove state machine whose allocation is released only after the correct remove outcome, sharpening the future ReplicatedActorBinding delete contract without proving live client despawn. Merged PR #24/current target resolution also provide the right integration pattern for #66's native spawn signatures: one fail-closed optional target group resolved from the already-inspected executable image, not repeated per-hook scans. Finally, player-physics low13 ownership is now explicitly separated from full-datum RuntimeObjectBinding identity. No local Izanami source, DLL, canonical package, or running Destiny process was changed by this research pa

[P01663 | 375373:375557 | NORMAL_TEXT]
17.62 SOURCE-DERIVED RUNTIMEOBJECTBINDING CAPABILITY CORRECTION — RESIDENCY ≠ SPAWN SUCCESS, OBJECTTRANSFORM IS ACTIVATION-ONLY IN #46/#66, AND DATUM NAMESPACE SEPARATION — 2026-08-21

[P01664 | 375557:375881 | NORMAL_TEXT]
SOURCE-DERIVED / REMOTE GITHUB ONLY. This pass compared the exact current #66 Mission Creator spawn runtime against PR #46 and current Sunrise master. It does not infer unpublished Izanami source, does not change the current collision/baseplate package sequence, and does not add any FIELD-TESTED runtime-object capability.

[P01665 | 375881:376856 | NORMAL_TEXT]
RUNTIME DEFINITION RESIDENCY IS ONLY A PREFLIGHT, NOT SPAWNABILITY. In #66, is_tag_resident(tag) is exactly native TagResolver(tag) != nullptr, and request() rejects nonresident definitions before enqueue. But spawn_one() can still fail at PlacementInitialize, at the DirectInitialize fallback, at descriptor resolution, at ObjectFactory, or at subsequent datum validation. The servicing path does not propagate spawn_one()'s returned datum to the caller, so a true return from request()/request_line means only that a request was accepted into the queue. The earlier RuntimeSpawnableResident label is therefore superseded by RuntimeDefinitionResident. Recommended runtime states are PackageEntityReadable -> RuntimeDefinitionResident -> RuntimeFactorySpawnAttemptable -> RuntimeFactorySpawnProven, where only RuntimeFactorySpawnProven means ObjectFactory returned a non-invalid datum and the full datum validated against the live object table under the current world epoch.

[P01666 | 376856:377924 | NORMAL_TEXT]
#66 OBJECTTRANSFORM IS POST-FACTORY ACTIVATION, NOT A PROVEN GENERAL LIVE MOVE/ROTATE/SCALE API. Both #46 and #66 write the requested quaternion at placement descriptor +0x10 and {x,y,z,positive uniform scale} at +0x20 before ObjectFactory, so initial pose/scale is part of creation. ObjectTransform is queued only for definition object types 8, 11, 20, and 21 after ObjectFactory returns a datum. Under the recovered object-type enum those are PropNetworkedMovable, Interactive, ItemAmmo, and ItemLoot. The activation queue resolves and full-datum-validates the object, retries at most four times, and then calls ObjectTransform. Most spawnable object types never pass through that post-factory transform path, and spawn_runtime.h exposes no public operation for moving an arbitrary already-spawned datum. Therefore the current evidence-safe ClientLocalRuntimeObjectBinding capability is CreateWithInitialTransform plus OptionalPostFactoryActivation for the known activation classes — not LiveMove/Rotate/Scale. Do not wire a live Forge gizmo to ObjectTransform yet.

[P01667 | 377924:378680 | NORMAL_TEXT]
FIRST LIVE-TRANSFORM EXPERIMENT SHOULD BE TYPE-BOUNDED. After client-local spawn itself is field-proven, choose one disposable resident definition of object type 8 or 11 because #66 already demonstrates that native ObjectTransform is called for those classes as part of activation. Create it through the validated factory path, retain and revalidate the complete datum, then from the same PlayerComponentUpdate execution seam issue one small translation-only ObjectTransform call after activation and observe whether the native object actually moves and remains stable. Only after that control should a non-activation object type be tested separately. Success on type 8/11 must not be generalized to every entity class without its own acceptance evidence.

[P01668 | 378680:379318 | NORMAL_TEXT]
FORGE NEEDS AN EXPLICIT SPAWN RESULT CHANNEL. A future ForgeCommandBus cannot treat the current #66 request() boolean as command completion. The runtime-object backend should return a ticketed result such as {ticket, sceneRevision, worldEpoch, tag, status, datum}, with fail-closed statuses including Nonresident, InitializeFailed, DescriptorFailed, FactoryInvalidDatum, DatumValidationFailed, and SpawnValidated. Only SpawnValidated attaches an ephemeral ClientLocalRuntimeObjectBinding to ForgeUUID. This also makes undo/error UI truthful: queue acceptance, native factory success, and runtime-handle attachment become separate states.

[P01669 | 379318:380048 | NORMAL_TEXT]
CLIENT-LOCAL DESTRUCTION REMAINS UNSUPPORTED. The #66 public runtime surface exposes install/uninstall, readiness/busy state, residency/object-type queries, spawn requests/lines, shortcuts, and cancel; it exposes no destroy-by-datum and no arbitrary transform-existing-object command. cancel/uninstall clear pending request/activation state but do not prove destruction of native objects already created by ObjectFactory. Keep ClientLocalRuntimeObjectBinding.DestroyUnsupported until a native destruction seam is independently recovered and field-tested. Section 17.61's replicated server remove lifecycle remains a separate ReplicatedActorBinding mechanism and must not be substituted for local ObjectFactory object destruction.

[P01670 | 380048:380831 | NORMAL_TEXT]
OBJECTFACTORY DATUMS MUST NOT BE FED INTO CURRENT content::handles::resolve. Current master client/content/handles uses a different content-handle namespace and descriptor ABI: low-13 record index plus content table id, content table ids >=1024, a 64-byte descriptor, record array at +0x08, record stride at +0x30, and correction metadata. #66's ObjectFactory datum path instead uses one object-datum descriptor with base at +0x08, stride at +0x10, required stride 0xE0, low-13 slot selection, and complete live datum at object +0x0C. Reuse current master only for its signature/RIP-relative target-resolution style. Section 17.55's object-datum-table hypothesis must resolve and validate the object-specific table/consumer and the 0xE0/+0x0C invariants before enabling the backend.

[P01671 | 380831:381434 | NORMAL_TEXT]
WORLD-EPOCH REFINEMENT. #66's activity-location diagnostics combine bootflow::in_world() with the live region-session state and committed destination. RuntimeObjectBinding should therefore key ephemeral handles and residency samples to a world identity stronger than bootflow step alone: at minimum fresh in_world plus live session/destination identity. On destination/session change, invalidate every attached native datum, clear pending runtime-object results, and re-sample RuntimeDefinitionResident. A definition that resolved in one destination must not inherit that capability into another world.

[P01672 | 381434:382084 | NORMAL_TEXT]
IMMEDIATE PROJECT CONSEQUENCE. Keep the current package-backed collision controls and true unprojected StaticInstanceBinding work unchanged. For the later client-local backend, the implementation order is now: shared optional signature target group -> validated object-datum descriptor -> world/session epoch -> explicit spawn result channel -> full-datum validation -> field-proven CreateWithInitialTransform -> type-8/11 translation control -> only then consider broader live transform support -> separately recover local destruction. No local repository files, DLLs, canonical packages, or running Destiny process were changed by this research pa

[P01673 | 382084:382658 | NORMAL_TEXT]
DATED UPDATE — 2026-08-21 — SOURCE-DERIVED: exact #46/#66 source comparison shows that #66 materially improves target resolution but not the underlying spawn ABI or object capabilities. TagResolver non-null proves only runtime definition residency; request success proves only queue acceptance; ObjectTransform is used as a post-factory activation step for object types 8/11/20/21 rather than as an exposed general live-transform API; and no client-local destruction operation is present. The Forge runtime model now separates RuntimeDefinitionResident, RuntimeFactorySpawn

[P01674 | 382658:382659 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01675 | 382659:382751 | NORMAL_TEXT]
17.63 SOURCE-DERIVED CONTROLLED-PLAYER HAVOK SUPPORT-PROBE IDENTITY CORRECTION — 2026-08-21

[P01676 | 382751:383083 | NORMAL_TEXT]
SOURCE-DERIVED / REMOTE GITHUB ONLY. This pass compared current Sunrise fly, noclip, and teleport/player-physics source plus the public remote Izanami PR #65 helper lineage. It does not infer unpublished dirty-local source, does not change the active Tower package/DLL set, and does not promote any collision owner to FIELD-TESTED.

[P01677 | 383083:383084 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01678 | 383084:383657 | NORMAL_TEXT]
NOCLIP'S ISLAND SCAN IS A CHARACTER-BODY DISCOVERER, NOT LOCAL-PLAYER IDENTITY AUTHORITY. current horizontal_noclip::character_body() walks active/inactive Havok islands and returns the first rigid body whose motion vtable matches the recovered hkpCharacterMotion vtable. That is sufficient for the noclip feature's current assumptions, but the source does not prove that the selected body is the controlled Guardian when multiple character-motion bodies exist. Therefore a future NativeHavokSupportProbe must not reuse the island-first result as its player identity seam.

[P01679 | 383657:383658 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01680 | 383658:384532 | NORMAL_TEXT]
CURRENT TELEPORT/PLAYER-PHYSICS CODE PROVIDES THE STRONGER CONTROLLED-PLAYER PATH. The teleport runtime caches a local player component only after the component's owner handle matches the current controlled handle in the low-13-bit player-physics context. Its body_of(component) chain resolves the rigid body through the component's native physics-object links, and read_position()/read_velocity() read that exact body. A read-only support probe should sample through local_player_component() -> owns_local_player(component) -> read_position/read_velocity after the original Havok step, failing unavailable rather than falling back to the first character body in the island list. This preserves the Section 17.61 boundary: low13/current-context ownership is acceptable for controlled-player physics attribution, but it is not generic RuntimeObjectBinding lifetime identity.

[P01681 | 384532:384533 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01682 | 384533:385509 | NORMAL_TEXT]
SUPPORT-PROBE ACCEPTANCE CONTRACT. Run only under a fresh in-world plus live session/destination epoch and only in CollisionAcceptanceMode with fly=false, noclip=false, noTurnback=false, and godmode=false. Snapshot the validated local player component and reset the observation window whenever the world/session epoch changes, the component changes, a respawn/teleport occurs, or any movement override becomes active. If the actual dirty Izanami tree later confirms/reimplements PR #65's full controlled-handle helper, include that full handle in the probe epoch as an additional reset key; do not assume the remote PR helper already exists in unpublished local source. Classify SupportObserved only after a controlled multi-sample window with stable Z and near-zero vertical velocity; classify NoSupportObserved only after sustained decreasing Z with negative vertical velocity. Transitional/ambiguous windows remain Unknown rather than being forced into a pass/fail result.

[P01683 | 385509:385510 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01684 | 385510:386226 | NORMAL_TEXT]
FIELD-AUTHORITY BOUNDARY. This probe still does not expose Havok contact manifolds or identify the exact static shape touching the Guardian. It becomes strong collision-ownership evidence only when a one-axis package mutation changes SupportObserved <-> NoSupportObserved while world/session identity, player component, spawn point, and all movement overrides remain controlled. The immediate Section 17.58 sequence therefore gains an objective second signal alongside visual/player observation: base direct-Havok rows, activity direct-Havok rows, then model-linked Havok rows can each be scored for Guardian materialization, render delta, subjective collision delta, and controlled-player support state separately.

[P01685 | 386226:386227 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01686 | 386227:386757 | NORMAL_TEXT]
PR #73 REINFORCES BUT DOES NOT DRIVE THIS CONTRACT. Its closed/unmerged coordinate-fly experiment signature-scans Havok stepDeltaTime and directly carries player position after physics, explicitly bypassing collision; the maintainer closed that feature as not planned. Current master already provides enough evidence because ordinary fly writes controlled-player horizontal velocity before Havok and restores Z/vertical velocity after Havok. Treat PR #73 as corroborating reverse-engineering evidence only, not a merge candidate.

[P01687 | 386757:386758 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01688 | 386758:387454 | NORMAL_TEXT]
DATED UPDATE — 2026-08-21 — SOURCE-DERIVED: corrected CollisionAcceptanceMode to disable fly as well as noclip/no-turnback/godmode, because current master fly itself modifies the controlled player's Havok-observed motion. Also corrected the proposed support-probe identity seam: noclip's island scan returns the first character-motion rigid body and does not prove local-player ownership, while the teleport physics-component path explicitly validates the controlled player before resolving position/velocity. The next collision controls can therefore use a read-only, controlled-player-specific post-Havok support signal without widening any package mutation or claiming an exact contact shape.

[P01689 | 387454:387455 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01690 | 387455:387456 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01691 | 387456:387457 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01692 | 387457:387458 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01693 | 387458:387637 | NORMAL_TEXT]
17.64 SOURCE-DERIVED DEEP PR / CURRENT-MASTER PASS — COMPOSITE RUNTIME WORLD IDENTITY, PROJECTION LIMITS, RESIDENT TEXTURE SLOT FLEXIBILITY, AND WORLD-BOUNDS CATALOG — 2026-08-21

[P01694 | 387637:387638 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01695 | 387638:388065 | NORMAL_TEXT]
SOURCE-DERIVED / REMOTE GITHUB ONLY. This pass inspected current Sunrise master plus the actual source of recent PRs, especially #66 Mission Creator, #53 runtime bootflow texture override, #54 Live Weapon Editor, and the now-merged #77 cache fix. It does not infer unpublished dirty-local Izanami source, does not upgrade any FIELD-TESTED Forge capability, and does not change the currently promoted package/DLL/runtime state.

[P01696 | 388065:388066 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01697 | 388066:388840 | NORMAL_TEXT]
PR #77 IS NOW CURRENT-MASTER BEHAVIOR. PR #77 merged into Sunrise master on 2026-08-21. Build-data cache version handling now treats any format-version mismatch as stale/rebuildable rather than treating a newer cache as a hard-invalid state. Together with current build-data publication semantics, this sharpens the Forge catalog architecture: package-derived ForgePackageAssetCatalog data belongs in the persistent build-data generation before cache freeze, while world-specific TagResolver residency, live native datums, and session/world epochs belong in a separate in-memory RuntimeResidencyOverlay. Current build-data publication becomes intentionally frozen after a cache is persisted, so dynamic world state must never be serialized into that fixed package snapshot.

[P01698 | 388840:388841 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01699 | 388841:389795 | NORMAL_TEXT]
PR #66 PROVIDES A STRONGER RUNTIME-WORLD EPOCH THAN BOOTFLOW STEP 38 ALONE. Its activity_location diagnostic considers a location valid only when bootflow::in_world() is fresh and a live region session exists, then snapshots the committed activity destination for that session and derives region/bubble/slice context. When the client leaves world it clears nearest-spawn state and resets published player position so stale coordinates do not leak into the next destination. A future RuntimeObjectBinding queue should therefore use a composite RuntimeWorldIdentity such as {liveRegionSessionId, committedDestinationPackageName, fullControlledIdentity}, optionally with a region/bubble subepoch. Any session/destination/world-exit change invalidates queued native operations, attached datums, runtime-residency samples, and map-local caches before ObjectFactory/ObjectTransform work can run. Fresh step-38 alone remains necessary but no longer sufficient.

[P01700 | 389795:389796 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01701 | 389796:390617 | NORMAL_TEXT]
PR #66 CAMERA PROJECTION IS MARKER-GRADE, NOT GIZMO-GRADE. The helper reconstructs right/up from camera forward and world-Z-up, does not recover camera roll, and uses a manually configured vertical FOV (default 60 degrees, clamped 30..120) because native live FOV is not recovered. Its own comments warn that markers drift when the user's real FOV differs, especially toward screen edges. This is suitable for coarse Forge labels, objective markers, off-screen bearings, and debug annotations. It is not authoritative enough for pixel-accurate transform handles, viewport hit-testing, or selection rays. A production in-game gizmo overlay still needs a native view/projection-matrix seam, or at minimum recovered live FOV + roll + viewport transform. WorldRaycast remains separately useful for crosshair/world placement.

[P01702 | 390617:390618 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01703 | 390618:391505 | NORMAL_TEXT]
PR #53 RESIDENT TEXTURE OVERRIDE IS IDENTITY-CONSTRAINED BUT PAYLOAD-FLEXIBLE. The detour still substitutes only an explicit allowlist of 18 known stock Tiger texture header/data TagHash pairs from package 0x010A, so it is not arbitrary TagHash registration and does not create new native UI nodes. However, the replacement path parses the supplied DDS and rebuilds the stock Tiger 0x28 texture header fields for data size, format, width, height, depth, and array size before the native GPU consumer receives it. Source-wise, a known resident native texture slot can therefore carry a different validated 2D DDS payload/dimensions/format; stock-dimension equality is not enforced by the override itself. Treat this as ResidentTextureOverride evidence for known menu/boot/native art identities, not as proof that every downstream native UI layout tolerates arbitrary aspect/size changes.

[P01704 | 391505:391506 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01705 | 391506:392526 | NORMAL_TEXT]
CURRENT MASTER SERVER PHYSICS HAS A CONCRETE WORLD-BOUNDS BLOCKER FOR REPLICATED FORGE ACTORS. physics_session opens the deterministic host scene with zero world bounds and explicitly notes that although the backend can accept the scene, the first body positioned outside those zero bounds is refused. The TODO proposes using actual destination extents, but current state/build_data/scenarios does not store a world AABB/extents contract. Therefore the deterministic ReplicatedActorBinding path cannot become actor-ready merely by enabling host actor commands: it first needs a read-only WorldBoundsCatalog keyed by destination/region/bubble/package-inventory fingerprint. The safest source candidates are conservative unions of package-derived direct-Havok bounds and/or validated static-map/terrain placement extents. Until this exists, ordinary nonzero server actor positions may be rejected even when the command lifecycle itself is correct. This does not affect the nearer-term client-local #66 ObjectFactory path.

[P01706 | 392526:392527 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01707 | 392527:393182 | NORMAL_TEXT]
PR #54 CONTRIBUTES A USEFUL THUMBNAIL-CACHE PATTERN, NOT CONTENT TO COPY. The closed/out-of-scope Live Weapon Editor branch uses a hash-indexed packed icon table, WIC decode to RGBA, immutable D3D11 texture/SRV creation, and a bounded 192-entry LRU that releases evicted views. Its bundled item_icons.pack/item_names.bin should not become an Izanami dependency or redistributed game-content cache. Reuse only the architecture as an InstalledAssetIconProvider that reads thumbnails from the user's installed package data and caches decoded GPU views. This is a practical future Forge Toolbox optimization once package-derived art identities are cataloged.

[P01708 | 393182:393183 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01709 | 393183:393905 | NORMAL_TEXT]
IMPLEMENTATION CONSEQUENCE. Keep the current package-backed collision/baseplate controls and the true unprojected StaticInstanceBinding acceptance test unchanged. In parallel, harden the future runtime/editor architecture around four rules: persistent package catalog versus ephemeral runtime overlay; composite session+destination+controlled-identity world epochs; marker-grade versus gizmo-grade projection capabilities; and explicit server WorldBoundsCatalog before deterministic replicated actor spawning. Do not merge #53/#54/#66 wholesale into the dirty Izanami tree. Reimplement only the narrow seams whose source contracts are validated and preserve their provenance separately from FIELD-TESTED Izanami behavior.

[P01710 | 393905:393906 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01711 | 393906:394676 | NORMAL_TEXT]
DATED UPDATE — 2026-08-21 — SOURCE-DERIVED: PR #77 is now merged current-master behavior; #66 activity_location upgrades the live-object invalidation key from bootflow step alone to a session/destination-aware runtime world identity; #66 camera projection is intentionally approximate because live FOV and roll are unresolved; #53 can rewrite dimensions/format/data size inside known resident stock texture identities but does not register new tags; and current deterministic server physics cannot safely host ordinary world-positioned actors until destination extents are supplied, which requires a new read-only WorldBoundsCatalog because the present scenario build-data schema has no world-bounds field. No FIELD-TESTED Izanami capability claim is added by this pass

[P01712 | 394676:394756 | HEADING_1]
17.65 FIELD-TESTED BASE DIRECT-HAVOK NEGATIVE RESULT AND MODEL-LINKED FOLLOW-UP

[P01713 | 394756:394777 | HEADING_2]
17.65.1 Field result

[P01714 | 394777:395412 | NORMAL_TEXT]
FIELD-TESTED / CONTROL RESULT. Tower Carrier Control loaded normally with all six visibility bundles preserved and exactly 14 base-package class 0x8080929B direct-Havok placements disconnected. The user observed that phantom world collision was unchanged, animated/entity content was unchanged, and the isolated staircase/floor geometry still had no collision. This rules out the 14 Tower-base 0x8080929B placement wrappers as the owner of the observed phantom collision and as the missing collision source for the isolated stair mesh. It does not classify the 16 activity-package 0x8080929B rows or the model-linked Havok references.

[P01715 | 395412:395441 | HEADING_2]
17.65.2 Next controlled pass

[P01716 | 395441:395953 | NORMAL_TEXT]
The clean Tower baseline contains 16 class 0x80806DE0 entity-model placements. Fifteen carry the same explicit Shadowkeep Havok tag 0x80C6D120 at inline resource offset +0x40, while their primary visual model reference is separate at +0x10. Nine of those placements are concentrated around the validated player-arrival region, including positions near (30.88, 60.92, 24.77) and (14.05, 63.69, 24.80). This makes the +0x40 field a stronger collision-owner candidate than disconnecting the entire model placement.

[P01717 | 395953:396325 | NORMAL_TEXT]
A new fail-closed control is implemented and deployed. It requires the clean 65-row source view, preserves all 16 model placements and their visual references, preserves all six visibility bundles and all 14 base direct-Havok placements, and nulls exactly 15 occurrences of tag 0x80C6D120 at +0x40. It refuses to stage if any expected class count or tag identity differs.

[P01718 | 396325:396368 | HEADING_2]
17.65.3 Acceptance logic and current state

[P01719 | 396368:396800 | NORMAL_TEXT]
If phantom collision changes while model visuals remain, the 0x80806DE0 +0x40 Havok field owns at least part of the collision layer. If collision remains unchanged, restore the 65-row baseline and isolate the 16 activity-package 0x8080929B rows next. Animated entities, interactables, VFX, lights, and spawn data remain a separate removal track; this collision pass intentionally preserves them so the result stays single-variable.

[P01720 | 396800:398316 | NORMAL_TEXT]
FIELD-TESTED LOADER RESULT. The null-reference control was staged, validated, and promoted, but it did not reach a playable collision test. Tower Carrier Control reached activity:initial_slice_set_loading and native initial-slice instantiation, then destiny2.exe crashed with Windows APPCRASH exception 0xC0000005 at module offset 0x469AFB. The preceding package and session transitions were successful and the crash occurred only after slice instantiation began. Therefore the entity-model +0x40 Havok reference is load-critical and cannot be treated as an optional nullable collision field. All five active owner files were restored from their dedicated pre-control rollback copies. The first scale-control staging attempt then failed closed because one of the 16 model rows carries a valid non-Havok +0x40 value; the guard was corrected to preserve it while still requiring exactly 15 references to 0x80C6D120. The corrected scale control is now staged, independently validated, and promoted. The active view retains all 65 relevant rows, all 15 model-linked Havok references, all six visibility bundles, all 14 base direct-Havok rows, and all 16 activity direct-Havok rows; exactly 16 class 0x80806DE0 placement scales read 0.000100. All 227 Tower-base entity rows were preserved by staging telemetry. Dedicated pre-scale rollback copies exist for all five active owner files. The next operator action is Tower Carrier Control -> Launch In Destiny. Do not build another Blank World Draft before this field test.

[P01721 | 398316:398317 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01722 | 398317:398318 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01723 | 398318:398425 | NORMAL_TEXT]
17.66 SOURCE-DERIVED NATIVE WORLD-RAYCAST PROBE AND MODEL-LINKED SCALE-CONTROL INTERPRETATION — 2026-08-21

[P01724 | 398425:398426 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01725 | 398426:398889 | NORMAL_TEXT]
EVIDENCE CLASSIFICATION. SOURCE-DERIVED / REMOTE GITHUB ONLY. This pass re-inspected the full PR #46 and PR #66 spawn-runtime implementations and same-era pre-Beyond-Light Alkahest map/dynamic-geometry source, then reconciled those results against the current FIELD-TESTED Tower/collision baseline. It does not infer unpublished local Izanami source, does not change the currently prepared 0x80806DE0 outer-scale control, and adds no new FIELD-TESTED capability.

[P01726 | 398889:398890 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01727 | 398890:399714 | NORMAL_TEXT]
PR #66 RECOVERS A USEFUL NATIVE WORLD-RAYCAST SEAM THAT SHOULD BE KEPT OPTIONAL AND READ-ONLY FIRST. The #46/#66 runtime ABI is a native bool-returning WorldRaycast with four float-vector inputs, two ignored-object integer arguments, one float parameter, and output pointers for hit fraction, hit position, and material id. #66 calls it with start/end world vectors, supplies the currently controlled datum in both ignored-object slots when available (otherwise -1), and receives {hit bool, fraction, hit.xyz, material}. #46 used the older fixed-target implementation; #66 keeps the same recovered ABI while resolving the executable target by signature. Current Sunrise master does not expose an equivalent generic world-raycast API, so this is still PR-derived reverse-engineering evidence rather than an upstream service.

[P01728 | 399714:399715 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01729 | 399715:400532 | NORMAL_TEXT]
FORGE IMPLEMENTATION CONSEQUENCE: add an optional NativeWorldRaycastProbe / SurfaceSnapQuery beside, not inside, the required RuntimeObjectBinding target set. A request should carry ticket, sceneRevision, worldSessionEpoch, start, end, and the full controlled-object identity snapshot. Execute the native call from the same validated gameplay-thread context used for runtime-object work, and discard the result if the world/session epoch or controlled identity changed before completion. Return a typed result such as {hit, fraction, position, materialId}. Do not make ObjectFactory availability depend on this signature: runtime spawning can remain available if raycast resolution fails. Conversely, do not execute a resolved raycast while the client is transitioning or the request belongs to an older world epoch.

[P01730 | 400532:400533 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01731 | 400533:401041 | NORMAL_TEXT]
AUTHORITY BOUNDARY. This raycast is immediately useful for under-crosshair placement, surface snapping, distance-to-surface feedback, and collision diagnostics, but it is NOT object picking: the recovered call returns no hit datum/object identity. The material integer is also diagnostic only until a separate source/native mapping ties it to a material/resource identity. A successful ray therefore must not be converted into a PackagePlacementBinding, RuntimeObjectBinding, or Havok-owner claim by itself.

[P01732 | 401041:401042 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01733 | 401042:401728 | NORMAL_TEXT]
COLLISION-DIAGNOSTIC CONSEQUENCE. Once implemented read-only, pair a fixed downward/forward NativeWorldRaycastProbe with the already planned controlled-player post-Havok support probe during one-axis collision tests. With fly/noclip/no-turnback/godmode disabled, a package change that simultaneously changes ray hit/fraction/position and flips the controlled Guardian between SupportObserved and NoSupportObserved is much stronger collision-layer evidence than either signal alone. It still does not name the exact Havok shape or map row; ownership becomes field evidence only when one isolated package mutation changes these observations while the other candidate layers remain fixed.

[P01734 | 401728:401729 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01735 | 401729:402607 | NORMAL_TEXT]
SAME-ERA OUTER-PLACEMENT SCALE EVIDENCE SHARPENS THE CURRENT 0x80806DE0 CONTROL. The prebl-0.5 Alkahest map loader constructs each map-row Transform directly from translation.xyz, the stored quaternion, and translation.w as a uniform Vec3 scale. For entity-loading branches, that outer transform is passed into load_entity_into_scene; the same-era dynamic renderer then derives mesh_to_world from Transform::local_to_world while model-local scale/offset remain separate model data. This is strong source evidence that reducing an 0x80806DE0 map row's outer Translation.W to 0.0001 is a lower-assumption way to suppress/shrink its visible placed model than nulling internal references: it preserves the +0x10 visual-model relationship, the load-critical +0x40 model-linked Havok relationship, and the rest of the resource graph while changing only the outer placement transform.

[P01736 | 402607:402608 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01737 | 402608:403330 | NORMAL_TEXT]
IMPORTANT LIMIT: THIS DOES NOT PROVE HAVOK SHAPE SCALE. Public rendering/tool source establishes outer transform use for the visual/entity path, but it does not establish that native Destiny applies the same W scale to the referenced Havok shape in this exact 0x80806DE0 chain. Therefore the currently prepared all-16 outer-scale=0.0001 package remains a FIELD-TEST-PENDING discriminator, not a proven collision-removal recipe. If it loads and visible models shrink/disappear while collision remains unchanged, that is evidence that render placement scale and model-linked Havok support are decoupled or differently composed. If collision also changes, follow with a narrower one-row control before attributing ownership.

[P01738 | 403330:403331 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01739 | 403331:403985 | NORMAL_TEXT]
SAFER FOLLOW-UP IF THE SCALE CONTROL IS AMBIGUOUS. After exact rollback to the verified baseline, keep Translation.W=1 and preserve both the +0x10 visual-model and +0x40 Havok references. Translate exactly one near-arrival 0x80806DE0 outer map row by a distinctive XYZ delta, then observe three channels independently: visible model displacement, NativeWorldRaycastProbe surface changes, and controlled-player post-Havok support. Translation-only removes Havok-scale semantics from the experiment and is therefore the preferred second discriminator if the all-row scale control cannot tell whether model-linked collision follows the placement transform.

[P01740 | 403985:403986 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01741 | 403986:404536 | NORMAL_TEXT]
HYPOTHESIS — SHARED MODEL-LINKED HAVOK INSTANCE. Fifteen of the sixteen clean Tower 0x80806DE0 rows currently share the same model-linked Havok identity 0x80C6D120 while retaining separate outer placement transforms. The most economical interpretation is that one reusable local Havok/model resource can be instantiated by multiple map-row transforms, but this is not yet field-proven. Do not mutate the shared +0x40 reference or Havok topology to test the hypothesis; the field-safe route is outer-row transform isolation with references preserved.

[P01742 | 404536:404537 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01743 | 404537:404961 | NORMAL_TEXT]
IMMEDIATE FIELD ORDER IS UNCHANGED. Do not rebuild or combine the current 0x80806DE0 scale-control experiment because of this source finding. Capture that field result first. The raycast work is a future optional read-only diagnostic/runtime-placement helper; the true unprojected StaticInstanceBinding milestone still preserves all source group/vector topology and remains separate from model-linked collision experiments.

[P01744 | 404961:404962 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01745 | 404962:405392 | NORMAL_TEXT]
REMOTE SOURCE PROVENANCE. stanuwu/Sunrise PR #66 and PR #46 spawn_runtime.cpp (WorldRaycast ABI and call site); cohaereo/alkahest prebl-0.5 crates/alkahest-renderer/src/loaders/map.rs (outer row Transform: translation.xyz / stored quaternion / translation.w scale and entity-loader handoff); cohaereo/alkahest prebl-0.5 dynamic-geometry renderer (mesh_to_world = Transform::local_to_world with model-local scale/offset separate).

[P01746 | 405392:405393 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01747 | 405393:405893 | NORMAL_TEXT]
DATED UPDATE — 2026-08-21 — SOURCE-DERIVED: recovered a signature-based native world-raycast seam suitable for optional surface snapping/collision diagnostics and tightened its authority boundaries; independently strengthened the interpretation of the current 0x80806DE0 outer-scale control as a low-assumption visual-placement suppression while keeping native Havok scaling explicitly unresolved. No local source, DLL, canonical package, or running Destiny process was changed by this research pass

[P01748 | 405893:405967 | HEADING_1]
17.67 FIELD-TESTED MODEL-SCALE NEGATIVE AND ACTIVITY DIRECT-HAVOK CONTROL

[P01749 | 405967:406004 | HEADING_2]
17.67.1 Model-placement field result

[P01750 | 406004:406737 | NORMAL_TEXT]
FIELD-TESTED / CONTROL RESULT. The corrected all-16 class 0x80806DE0 outer-placement scale control preserved the clean 65-row dependency view and all 15 model-linked Havok references, loaded successfully, and reached activity:in_world. The user reported that all previously observed problems remained: phantom structural collision was unchanged, animated/entity content remained, and the isolated staircase/floor geometry still lacked matched collision. This rules out the outer transforms of those 16 entity-model placements as the owner of the observed phantom collision or the missing collision source for the isolated surface. All five active Tower owner files were restored from their dedicated pre-model-scale rollback copies.

[P01751 | 406737:406786 | HEADING_2]
17.67.2 Activity direct-Havok control definition

[P01752 | 406786:407410 | NORMAL_TEXT]
The last untested direct-Havok placement family was activity package 0x0212. Table 0x80C24CED contains exactly two class 0x8080929B placements and table 0x80C250E3 contains exactly fourteen, for sixteen total. The control staged those rows as a distinct canonical patch-6 transaction, requiring source patch 5, both exact table identities, and the exact 2 + 14 count. It scaled and disconnected only those sixteen inline direct-Havok resources while preserving the Tower base package and every entity/spawn row. The following field result records that this isolated control loaded but changed none of the observed problems.

[P01753 | 407410:407455 | HEADING_2]
17.67.3 Current deployed state and next gate

[P01754 | 407455:408280 | NORMAL_TEXT]
FIELD-TESTED / NEGATIVE CONTROL. The promoted activity-package control loaded through activity:in_world, but the user reported all three observed problems unchanged: phantom structural collision remained, animated/entity content remained, and the isolated staircase/floor still had no matched collision. This rules out the sixteen activity-package class 0x8080929B direct-Havok placement wrappers as owners of those behaviors. The active package files were restored from the dedicated pre-control backups, activity patch 6 was removed, and offline inventory returned to the exact clean 65-row baseline. Together with the prior base-wrapper, visibility-bundle, entity-model-reference, and entity-model-transform results, this exhausts the ordinary placement-level Havok candidates currently identified in the Tower map graph.

[P01755 | 408280:408434 | HEADING_1]
17.68 SOURCE-DERIVED CURRENT-MASTER / PR DEEP PASS — OPTIONAL FORGE TARGET GROUP, NATIVE WIDGET BITMAP CATALOG, AND SAFE SLICE-SET SELECTION — 2026-08-21

[P01756 | 408434:409059 | NORMAL_TEXT]
SOURCE-DERIVED / REMOTE GITHUB ONLY. This pass compared the remote Izanami baseline 830a9a58eb7855d111a1d3eab606b45c0df38fc8 against current Sunrise master 01888412edd6aba5071b78fef83917c9e6ef21f4 and inspected current target resolution, bitmap hooks, scenario/roster classification, PR #39 orbit-slice-set work, and the older entity-spawner lineage. The branches are diverged; no reviewed upstream change invalidates the current Shadowkeep 0x8080966D package/static-instance assumptions, so the dirty Izanami worktree should not be blindly rebased. Relevant upstream mechanisms should be ported selectively and revalidated.

[P01757 | 409059:409060 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01758 | 409060:410094 | NORMAL_TEXT]
OPTIONAL FORGE RUNTIME TARGET GROUP. Current Sunrise master already resolves native game targets through one executable-image sweep and deliberately separates activation-required targets from optional diagnostic/derived targets. This should become the integration model for the #66 runtime-object seams. Do NOT append PlacementInitialize, DirectInitialize, ObjectFactory, ObjectTransform, PlayerComponentUpdate, TagResolver, or the future recovered object-datum descriptor to Sunrise's activation-required target prefix: one stale Forge signature must not make ordinary Sunrise activation fail. Add a separate all-or-nothing optional Forge runtime-object target group resolved from the same inspected image. Publish RuntimeObjectsAvailable only when the required Forge subgroup coherently resolves; keep WorldRaycast/camera helpers as separately optional capabilities. The object-datum descriptor joins the group only after the fixed-RVA replacement is independently recovered/validated; there is no fallback to #66's hard-coded RVA.

[P01759 | 410094:410095 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01760 | 410095:411343 | NORMAL_TEXT]
NATIVE WIDGET BITMAP CATALOG. Current master has a signature-resolved native widget bitmap-reference setter shared by seven sibling widget classes. Its setter receives a 12-byte triple: {bound property definition tag, bitmap reference, draw state}. The existing crash guard validates true bitmap references (top byte 0x80/0x81 or the invalid sentinel), substitutes the sentinel for malformed references, and currently logs new valid bitmap references without retaining the complete valid property/ref/state relation. Extend this READ-ONLY first into NativeWidgetBitmapCatalog: record {propertyDefinitionTag, bitmapReference, drawState, uiContextEpoch}, deduplicated by full triple/context, then resolve the observed bitmap references through installed package metadata and correlate them with PR #53-style resident GPU texture header/data requests. This gives Izanami a systematic way to discover native Director/orbit/menu texture slots that are actually used by live widgets before attempting resident texture reskinning. It does NOT create buttons/layout nodes, prove arbitrary bitmap registration, or prove that one widget bitmap reference maps one-to-one to a #53 data/header pair; those relationships remain package/runtime-attestation work.

[P01761 | 411343:411344 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01762 | 411344:412247 | NORMAL_TEXT]
SAFE EXISTING SLICE-SET SELECTION. PR #39 is useful evidence for destination/package -> orbit slice-set mapping, but its implementation mutates an executable immediate and NOPs an instruction at runtime. Current Sunrise master supersedes that patching style with a signature-resolved detour on the actual slice-set name-hash picker: stock logic runs first and Sunrise substitutes the known orbit slice-set only when the selector is the orbit case and the original selection remains unresolved. If Forge later needs an existing Forge/Mods presentation slice-set, preserve #39's mapping idea but extend the current picker detour to consult a validated per-destination desired EXISTING slice-set hash. Do not copy #39's self-modifying-code/NOP approach. This can select already-authored native presentation content; it is not evidence that Izanami can create a new Director node or a new slice-set layout.

[P01763 | 412247:412248 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01764 | 412248:413450 | NORMAL_TEXT]
ROSTER-CRITICAL ACTIVITY SAFETY IS GROUP-COMPLETE, NOT SLOT-TYPE-ONLY. Current scenario classification proves that a roster group is unusable when its decoded slot count does not equal the declared slot count, because the client registers one record per declared slot and can hold the whole current-bubble apply while one member remains unseeded. Current build-data also distinguishes groups present in every slice set (safe global groups) from groups present only in particular bubbles (must remain per-bubble; promoting them globally can destabilize teardown). Therefore ActivityLayerSafetyCatalog / RosterCriticalMask must retain and protect complete group provenance: registry key/object tag, declared slot count, raw slot index/type/flags, slice-set coverage, and bubble membership. Types 13 Participation and 17 Lifetime remain high-priority semantic signals, but they are not the whole safety rule. A row/object contributing to a globally or currently published complete group stays Protected unless the whole group contract is deliberately reconstructed. This does not change the currently promoted 0x0212 activity direct-Havok control, which preserves the relevant entity/spawn/roster chains.

[P01765 | 413450:413451 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

[P01766 | 413451:414325 | NORMAL_TEXT]
DATED UPDATE — 2026-08-21 — SOURCE-DERIVED: current-master/PR inspection sharpened three implementation seams without widening any FIELD-TESTED claim. #66's runtime-object signatures should integrate as an optional atomic target group so a Forge-only signature miss cannot break Sunrise activation; the native widget bitmap setter exposes a property/ref/state triple suitable for a read-only menu-texture discovery catalog that can be correlated with #53 resident overrides; and PR #39's destination mapping should be retained only as data while current master's safe slice-set picker detour replaces its executable-patching method. Scenario source also upgrades roster protection from slot-type heuristics to complete declared group + slice-set/bubble coverage. No local Izanami source, DLL, canonical package, or running Destiny process was changed by this research pass.

[P01767 | 414325:414404 | HEADING_1]
17.69 SOURCE-DERIVED TOWER NODE-OWNERSHIP CENSUS AND SELECTIVE SCENERY CONTROL

[P01768 | 414404:414434 | HEADING_2]
17.69.1 Decoded row ownership

[P01769 | 414434:415105 | NORMAL_TEXT]
SOURCE-DERIVED / OFFLINE PACKAGE CENSUS. Every one of the 1,563 reachable city_tower_d2 map rows carries a valid entity-definition tag at row offset +0x00. Of those rows, 1,336 also carry an inline component-list head at +0x78 and 227 have no component list. The earlier phrase "227 Tower entity rows" therefore described only standalone entity placements, not the complete set of map-node entity owners. The 227 standalone rows classify exactly as 102 StaticMesh, 29 PropSimpleDeprecated, 22 PropCosmeticMovable, 4 PropCinematic, 53 Emitter, 9 Interactive, and 8 System. This exact partition accounts for all standalone rows and provides a fail-closed removal boundary.

[P01770 | 415105:415138 | HEADING_2]
17.69.2 Implemented next control

[P01771 | 415138:415897 | NORMAL_TEXT]
IMPLEMENTED / BUILD VERIFIED / FIELD TEST PENDING. The package builder no longer generates the disproven activity patch. Its next Blank Baseplate build keeps every component-backed row and preserves all 8 standalone System plus 9 standalone Interactive nodes. It moves exactly the other 210 standalone scenery entities to Z = -10000 and sets their outer uniform scale to 0.0001. The control preserves the retained sky layer and the restored 65-row collision inventory. The Release target builds successfully, the deployed DLL matches the build artifact, and Destiny remains closed. This is intentionally a scenery-ownership test: success means the obvious static props, movable/cinematic props, and emitters disappear while launch and required nodes survive.

[P01772 | 415897:415927 | HEADING_2]
17.69.3 Collision consequence

[P01773 | 415927:416688 | NORMAL_TEXT]
All identified placement-wrapper collision controls are now negative or non-viable: visibility/world bundles had no observed effect, base and activity direct-Havok wrappers had no observed effect, entity-model outer scale had no observed effect, and nulling the model-linked Havok reference crashed native slice instantiation. Phantom collision therefore should not be attacked with another broad placement-wrapper deletion. The next collision pass must inspect component payloads, slice-level physics ownership, and native world-physics observations. A moved visual static mesh does not acquire collision automatically, so the final baseplate requires a deliberately paired visible surface and collision resource or a proven runtime-spawned collidable object.

[P01774 | 416688:416736 | HEADING_2]
17.69.4 Field-tested standalone class partition

[P01775 | 416736:417218 | NORMAL_TEXT]
FIELD-TESTED / POSITIVE PARTIAL CONTROL. The promoted package reached activity:in_world. The user observed that some props were removed, especially most animated props. Lights, decals, some flags, rubble, and parts of the grass remained, and phantom collision remained. This proves the standalone suppression path owns real visible scenery, while the surviving visuals are predominantly component-backed and the phantom collision is independent of the suppressed standalone actors.

[P01776 | 417218:417261 | NORMAL_TEXT]
Suppressed standalone classes (210 total):

[P01777 | 417261:417277 | NORMAL_TEXT | LIST id=kix.mya83k73jgwz level=0]
StaticMesh: 102

[P01778 | 417277:417302 | NORMAL_TEXT | LIST id=kix.mya83k73jgwz level=0]
PropSimpleDeprecated: 29

[P01779 | 417302:417326 | NORMAL_TEXT | LIST id=kix.mya83k73jgwz level=0]
PropCosmeticMovable: 22

[P01780 | 417326:417343 | NORMAL_TEXT | LIST id=kix.mya83k73jgwz level=0]
PropCinematic: 4

[P01781 | 417343:417355 | NORMAL_TEXT | LIST id=kix.mya83k73jgwz level=0]
Emitter: 53

[P01782 | 417355:417586 | NORMAL_TEXT]
Preserved standalone classes (17 total): Interactive: 9; System: 8. These were deliberately retained as the fail-closed launch-critical set. Every one of the 1,336 component-backed rows was also retained during this field control.

[P01783 | 417586:417587 | NORMAL_TEXT]
⟦EMPTY PARAGRAPH⟧

