# WorldForge Roadmap

Build a game engine by using existing libraries first, then reimplementing subsystems from scratch (Renderer, Physics, Audio, Math). Long-term extension: evolve the engine into a World Simulation / Artificial Life / Neuroevolution platform.

Progression rule: `Use -> Understand -> Abstract -> Reimplement -> Optimize`. Don't build abstractions speculatively — implement first, hit a real problem, then abstract.

## Tech Stack

| Area | Initial choice |
|---|---|
| Language | C++20/23 |
| Build | CMake |
| Platform / Window / Input | SDL3 |
| Graphics | OpenGL |
| Math | GLM (later: own `MyMath`) |
| Physics 2D | Box2D (later: own `MyPhysics`) |
| Physics 3D | Jolt Physics |
| Audio | miniaudio (later: own `MyAudio`) |
| Model format | glTF |
| VCS | Git |

Dependency direction, early vs. late:

```
Early:                          Late:
Game -> MyEngine                Game -> MyEngine
  Renderer -> OpenGL               MyRenderer -> MyMath
  Physics  -> Box2D/Jolt           MyPhysics
  Audio    -> miniaudio            MyAudio
  Platform -> SDL3
  Math     -> GLM
```

## Target Engine Architecture

```
MyEngine
├── Core        (Application, GameLoop, Time, Logging, Profiling)
├── Platform    (Window, Input, FileSystem)
├── Scene       (Entity, Component, Transform)
├── Renderer    (Mesh, Material, Texture, Camera, RendererBackend)
├── Physics     (Collider, RigidBody, PhysicsBackend)
├── Audio       (AudioSource, AudioBackend)
├── Asset
├── Gameplay
├── Editor
└── Labs        (MathLab, RasterizerLab, PhysicsLab, AudioLab, PerformanceLab)
```

## Repository Structure

```
MyEngine/
├── Engine/   (Core, Platform, Renderer, Physics, Audio, Scene, Asset)
├── Editor/
├── Games/    (Breakout, Marble, ...)
├── Labs/     (MathLab, RasterizerLab, PhysicsLab, AudioLab, PerformanceLab)
├── Tests/
├── Assets/
└── CMakeLists.txt
```

`Labs/` is for isolated experiments: hit a problem in the engine -> reproduce it standalone in Labs -> understand it -> bring the fix/insight back into Engine. Don't experiment directly inside engine code.

When a game milestone surfaces friction, log it to `ENGINE_NOTES.md`; extra ideas that aren't urgent go to `BACKLOG.md`. These notes drive the next milestone's scope.

---

## Part I — Engine User

| # | Milestone | Goal | Definition of Done |
|---|---|---|---|
| 0 | Bootstrap | Working C++ program that builds and runs | Debug build; Release build; Engine/Game targets separated; debugger breakpoints work; git repo initialized |
| 1 | Window / Input / Game Loop | Window on screen, keyboard-controlled object, real game loop (`ProcessEvents -> Update(dt) -> Render`) | Window creation; close event; keyboard input; mouse input; delta time; object moves |
| 2 | Basic Renderer | Game code can call `renderer.Draw(sprite)` | Triangle renders; textured quad renders; multiple sprites; shader load/compile; window resize handled |
| 3 | Scene / Entity / Component | Engine manages game objects via Entity+Component (`player.Add<Transform>()`) | Entity create/destroy; Transform component; Renderer component; scene updates entities; entity ID/handle |
| 4 | Assets / Physics / Audio Integration | Wire existing Asset/Physics/Audio subsystems into Scene | Texture asset loading; audio playback; collision detection; rigid body; asset cache; collision-triggers-sound |
| 5 | Game #1 (2D) | Ship a complete 2D game (Breakout / Asteroids / Pong variant) using the full 2D stack | Game finished — prioritize completion over new engine features; log friction to `ENGINE_NOTES.md` |

## Part II — Engine Architect

| # | Milestone | Goal | Definition of Done |
|---|---|---|---|
| 6 | Architecture Refactoring | Hide external libs behind engine-owned interfaces (`IRenderer`, `IPhysics`, `IAudio`) — dependency inversion | Only start after Game #1 is done. Don't pre-design abstractions — abstract only after a repeated, real problem shows up |

## Part III — 3D Engine

| # | Milestone | Goal | Definition of Done |
|---|---|---|---|
| 7 | 3D Transform / Camera | WASD + mouse-controlled 3D camera and cube, using GLM (`vec3`, `mat4`, `quat`) | 3D cube renders; perspective projection; WASD movement; mouse look; aspect ratio handled |
| 8 | Blender → MyEngine | Import a Blender-authored model via glTF asset pipeline (Mesh/Material/Texture) | Model import; texture; material; directional light; model transform |
| 9 | 3D Physics Integration | Integrate Jolt Physics; drop and stack boxes | Concept-level only: PhysicsWorld, Body, Collider, Mass, Static/Dynamic, timestep, transform sync |
| 10 | Game #2 (3D) | Ship a small 3D game (e.g. marble game) exercising the full 3D stack | Uses 3D renderer, camera, input, physics, collision, imported models, materials, lighting, audio, scene, asset |

## Part IV — Engine Implementer

Replace each black-box dependency with an own implementation, one at a time.

| # | Milestone | Goal | Definition of Done |
|---|---|---|---|
| 11 | MyMath | Own math library: `Vec2/Vec3/Vec4`, `Mat3/Mat4`, `Quaternion` | Incrementally replaces `glm::vec3` etc. with own `Vec3` etc. across the codebase |
| 12 | CPU Software Renderer | Full CPU rasterization pipeline without a GPU: transform → projection → clip → rasterize → interpolate → depth test → shade | Textured 3D model renders using only the CPU |
| 13 | Renderer Backend | `IRenderer` abstraction with two implementations (`OpenGLRenderer`, `SoftwareRenderer`) selectable for the same scene | Same scene renders correctly on both backends |
| 14 | MyPhysics2D | Own 2D rigid-body physics: integration, collision (circle/AABB/OBB/SAT), impulse resolution, friction, constraints | Boxes stack and behave plausibly |
| 15 | Physics Backend | `IPhysics2D` abstraction with `Box2D` and `MyPhysics` both runnable on the same scene | Compare stability, penetration, friction, stacking, timestep sensitivity, performance between backends |
| 16 | MyAudio | Own audio mixer/DSP: sampling, signal generation (sine/square/saw/noise), mixer, gain/pan, filters, reverb basics, spatial audio | Replaces `miniaudio` playback calls with own mixer |

## Part V — Engine Engineering

| # | Milestone | Goal | Definition of Done |
|---|---|---|---|
| 17 | Profiling | Measure before optimizing | Track FPS, frame time, per-subsystem time (Game/Physics/Render), entity count, draw calls |
| 18 | Memory / Data Layout | Understand stack/heap/cache/alignment, pool & arena allocators, AoS vs SoA | Benchmark 10k–100k entities comparing AoS vs SoA layouts |
| 19 | Multithreading / Job System | Worker thread pool executing Physics/Animation/Asset jobs off the main thread | Job queue with dependencies; no data races |

## Part VI — Tools / Editor

| # | Milestone | Goal | Definition of Done |
|---|---|---|---|
| 20 | MyEngine Editor | Editor with Hierarchy, Inspector, Scene View | Entity creation; transform editing; scene save/load; asset browser; play/stop; physics/render debug views; profiler panel |

## Final Capstone

Stop adding engine features; ship a small game (3D physics puzzle / marble-game expansion / small FPS arena / robot sim / exploration game) using nearly every subsystem: 3D renderer, imported models, materials, lighting, physics, audio, input, scene, asset, UI, multiple levels, editor, profiling.

---

## Extension: World Simulation & Artificial Life

Not a replacement path — an extension built on top of the finished game engine.

```
Game Engine -> Simulation Engine -> World Simulator -> Artificial Life -> Evolution -> Neuroevolution
```

Key difference from games: games optimize for showing something to a human at 60 FPS; simulations optimize for correctness, speed, and reproducibility over many (10,000+) steps. Simulation and rendering must be decoupled.

| Stage | Name | Goal |
|---|---|---|
| S0 | Simulation Runtime | Deterministic, reproducible sim decoupled from rendering: fixed timestep, seeded RNG, pause/single-step/fast-forward/replay, headless mode (same seed -> same result) |
| S1 | Agent World | 1,000–10,000 agents (Position, Velocity, Energy, Sensor, Controller) in a World (Boundaries, Obstacles, Food); requires spatial partitioning (uniform grid / quadtree) |
| S2 | Ecosystem | Add Plants/Food/Herbivores/Predators; energy-based life rules (movement costs energy, food gives energy, energy<=0 -> death); track population/lifespan/birth/death stats; look for predator-prey dynamics |
| S3 | Genome & Generation | Add Genome (bodySize, speed, sensorRange, metabolism, reproductionThreshold, lifespan) with mutation-based inheritance (`child = parent + mutation`); track generations (generational or continuous/steady-state) |
| S4 | Natural Selection | Selection pressure must emerge from world rules only (movement cost, food gain, death blocks reproduction) — never hardcode fitness like "+10 for being fast"; measure trait mean/variance, gene frequency, survival rate |
| S5 | Brain / Sensors / Actions | Replace scripted `if (foodIsNear) moveTowardFood()` with Sensors -> Neural Network -> Actions (move/turn/attack/eat) |
| S6 | Neuroevolution | Put neural network weights into the Genome; behavior evolves without hand-coded rules (`weights + mutation`) |
| S7 | Evolving Neural Topology | Evolve network structure itself, not just weights — NEAT-style: speciation, crossover, topology mutation |
| S8 | Morphological Evolution | Evolve the body itself (limbs, joints, sensors, muscles) via Genome -> Body Generator -> Physics; reuses M9/M14 physics, M11 math, M2/M12 renderer work |
| S9 | Emergence & Complex Systems | Shift focus from individual agents to emergent global behavior from simple local rules (self-organization, cellular automata, population dynamics) |
| S10 | Large-Scale Simulation | Scale to 100k–1M agents: needs ECS, data-oriented design (SoA), spatial partitioning, SIMD, job system, possibly GPU compute; headless max-throughput target |
| S11 | Experiment Platform | Configurable experiment platform: seed/config/population/environment params, batch runs, CSV export, replay/save-state, parallel headless experiments |

### Possible Final Architecture

```
WorldSimulationEngine
├── Core
├── Simulation  (Clock, Scheduler, Random, Replay)
├── World
├── ECS
├── Physics
├── Renderer
├── Environment
├── Organism    (Body, Energy, Sensor, Brain)
├── Genetics    (Genome, Mutation, Crossover, Reproduction)
├── Neural
├── Evolution
├── Statistics
├── Experiment
└── Editor
```
