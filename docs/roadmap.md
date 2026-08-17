# Game Engine Learning Roadmap

> **목표:** 기존 라이브러리를 활용해 게임 엔진 전체 구조와 C++ 프로그래밍을 먼저 익힌 뒤, 각 subsystem을 하나씩 직접 구현하면서 그래픽스·물리·오디오·수학·시스템 프로그래밍의 내부 원리를 이해한다.
>
> 장기적으로는 이 기반을 이용해 **World Simulation / Artificial Life / Evolution / Natural Selection / Neuroevolution** 영역으로 확장한다.

---

# 1. Learning Philosophy

이 프로젝트의 목적은 처음부터 모든 것을 직접 구현하는 것이 아니다.

학습은 다음 4단계로 진행한다.

```text
Level 1 — Integration
─────────────────────────────
기존 라이브러리를 사용해
작동하는 작은 게임 엔진을 만든다.

           ↓

Level 2 — Architecture
─────────────────────────────
각 subsystem의 역할과
의존성, 경계를 이해한다.

           ↓

Level 3 — Implementation
─────────────────────────────
기존 Black Box를 하나씩 열어
직접 구현한다.

           ↓

Level 4 — Engineering
─────────────────────────────
성능, 메모리, 병렬처리,
tooling까지 확장한다.
```

핵심 원칙:

> **Use → Understand → Abstract → Reimplement → Optimize**

처음에는 `Box2D가 어떻게 충돌을 계산하는가?`를 몰라도 된다.

먼저:

```text
Physics Engine은
게임 엔진에서 어떤 역할을 하는가?
```

를 이해한다.

그 다음:

```text
Physics와 Scene은
어떤 API로 연결되어야 하는가?
```

를 이해한다.

그 후:

```text
Collision / Impulse / Constraint Solver는
어떻게 동작하는가?
```

를 공부하며 직접 구현한다.

---

# 2. Long-Term Architecture

최종적으로 다음과 같은 엔진을 만드는 것을 목표로 한다.

```text
MyEngine
│
├── Core
│   ├── Application
│   ├── GameLoop
│   ├── Time
│   ├── Logging
│   └── Profiling
│
├── Platform
│   ├── Window
│   ├── Input
│   └── FileSystem
│
├── Scene
│   ├── Entity
│   ├── Component
│   └── Transform
│
├── Renderer
│   ├── Mesh
│   ├── Material
│   ├── Texture
│   ├── Camera
│   └── RendererBackend
│
├── Physics
│   ├── Collider
│   ├── RigidBody
│   └── PhysicsBackend
│
├── Audio
│   ├── AudioSource
│   └── AudioBackend
│
├── Asset
│
├── Gameplay
│
├── Editor
│
└── Labs
    ├── MathLab
    ├── RasterizerLab
    ├── PhysicsLab
    ├── AudioLab
    └── PerformanceLab
```

---

# 3. Initial Technology Stack

초기에는 의도적으로 기존 구현을 사용한다.

| 영역 | 초기 선택 |
|---|---|
| Language | C++20/23 |
| Build | CMake |
| Platform / Window / Input | SDL3 |
| Graphics | OpenGL |
| Math | GLM |
| Physics 2D | Box2D |
| Physics 3D | Jolt Physics |
| Audio | miniaudio |
| Model | glTF / 기존 loader |
| Version Control | Git |

초기 구조:

```text
                Game
                  │
                  ▼
              MyEngine
                  │
       ┌──────────┼──────────┐
       ▼          ▼          ▼
    Renderer   Physics     Audio
       │          │          │
    OpenGL    Box2D/Jolt  miniaudio

        Platform → SDL3
        Math     → GLM
```

후기 구조:

```text
                Game
                  │
                  ▼
              MyEngine
                  │
       ┌──────────┼──────────┐
       ▼          ▼          ▼
   MyRenderer  MyPhysics   MyAudio
       │
     MyMath
```

---

# 4. Suggested Repository Structure

```text
MyEngine/
│
├── Engine/
│   ├── Core/
│   ├── Platform/
│   ├── Renderer/
│   ├── Physics/
│   ├── Audio/
│   ├── Scene/
│   └── Asset/
│
├── Editor/
│
├── Games/
│   ├── Breakout/
│   └── Marble/
│
├── Labs/
│   ├── MathLab/
│   ├── RasterizerLab/
│   ├── PhysicsLab/
│   ├── AudioLab/
│   └── PerformanceLab/
│
├── Tests/
│
├── Assets/
│
└── CMakeLists.txt
```

`Labs`는 매우 중요하다.

엔진 본체에서 바로 실험하지 않고:

```text
Engine 문제 발견
       ↓
Labs에서 독립적으로 실험
       ↓
원리 이해
       ↓
Engine에 반영
```

하는 구조로 사용한다.

---

# PART I — ENGINE USER

## Milestone 0 — Engine Bootstrap

### Goal

> `MyEngine`이라는 C++ 프로그램이 정상적으로 build/run된다.

```text
main()
  ↓
Engine::Initialize()
  ↓
Engine::Run()
  ↓
Engine::Shutdown()
```

### Learn

- C++ project structure
- `.h / .cpp`
- class / struct
- constructor / destructor
- reference / pointer
- `std::vector`
- `std::string`
- `unique_ptr`
- RAII
- namespace
- CMake
- compiler / linker
- debugger
- Git

### Definition of Done

- [ ] Debug build 가능
- [ ] Release build 가능
- [ ] Engine과 Game target 분리
- [ ] Debugger로 breakpoint 사용 가능
- [ ] Git repository 구성

### References

- **LearnCpp** — C++ 학습
  - https://www.learncpp.com/
- **cppreference** — C++ reference
  - https://en.cppreference.com/
- **CMake Tutorial**
  - https://cmake.org/cmake/help/latest/guide/tutorial/

---

# Milestone 1 — Window / Input / Game Loop

### Goal

> Window를 띄우고 키보드로 화면의 object를 움직인다.

```text
while (running)
{
    ProcessEvents();
    Update(deltaTime);
    Render();
}
```

### Architecture

```text
Application
│
├── Window
├── Input
├── Time
└── GameLoop
```

### Learn

- Frame
- FPS
- Delta Time
- Fixed timestep 개념
- Polling
- Event
- Callback
- Lambda
- Object lifetime

### Definition of Done

- [ ] Window 생성
- [ ] Close event 처리
- [ ] Keyboard input
- [ ] Mouse input
- [ ] Delta time 계산
- [ ] Object 이동

### References

- SDL3 Documentation
  - https://wiki.libsdl.org/SDL3/
- The Cherno — Game Engine / Hazel
  - https://www.youtube.com/@TheCherno

---

# Milestone 2 — Basic Renderer

### Goal

게임 코드에서:

```cpp
renderer.Draw(sprite);
```

와 같이 사용할 수 있게 만든다.

### Architecture

```text
Game
 ↓
Renderer
 ↓
OpenGL
 ↓
GPU
```

### Implement

```text
Renderer
├── Shader
├── Texture
├── Sprite
└── RenderCommand
```

### Learn

이 단계에서는 깊게 파지 않는다.

- CPU / GPU
- Vertex
- Vertex Buffer
- Index Buffer
- Texture
- Shader
- Framebuffer
- Draw Call

### Definition of Done

- [ ] Triangle 렌더링
- [ ] Texture 렌더링
- [ ] 여러 Sprite 렌더링
- [ ] Shader load/compile
- [ ] Window resize 지원

### References

- **LearnOpenGL**
  - https://learnopengl.com/
- Khronos OpenGL Wiki
  - https://wikis.khronos.org/opengl/

---

# Milestone 3 — Scene / Entity / Component

### Goal

게임 객체들을 엔진이 관리하도록 한다.

```text
Scene
│
├── Player
│   ├── Transform
│   ├── SpriteRenderer
│   └── PlayerController
│
├── Enemy
│   ├── Transform
│   └── SpriteRenderer
│
└── Camera
```

### Example API

```cpp
Entity player = scene.CreateEntity();

player.Add<Transform>();
player.Add<SpriteRenderer>();
```

### Learn

#### C++

- Composition
- Template
- Ownership
- Handle / ID
- Containers
- Lifetime

#### Architecture

- Entity
- Component
- System
- Scene
- GameObject
- ECS 개념

### Definition of Done

- [ ] Entity 생성/삭제
- [ ] Transform component
- [ ] Renderer component
- [ ] Scene에서 entity update
- [ ] Entity ID / Handle

### References

- The Cherno — Hazel
- Pikuma — C++ 2D Game Engine Programming
  - https://pikuma.com/courses/cpp-2d-game-engine-development
- Game Programming Patterns
  - https://gameprogrammingpatterns.com/

---

# Milestone 4 — Assets / Physics / Audio Integration

### Goal

기존 subsystem을 엔진에 연결한다.

```text
                  Scene
                    │
       ┌────────────┼────────────┐
       ▼            ▼            ▼
    Renderer      Physics      Audio
       │            │            │
    OpenGL        Box2D      miniaudio
```

### Implement

```text
AssetManager
PhysicsWorld
AudioEngine
```

### Example

```cpp
audio.Play("hit.wav");

physics.AddBody(entity);

renderer.Draw(entity);
```

### Learn

- subsystem
- resource lifetime
- asset loading
- physics step
- audio source
- subsystem communication

### Definition of Done

- [ ] Texture asset loading
- [ ] Audio playback
- [ ] Collision
- [ ] Rigid body
- [ ] Asset cache
- [ ] Collision event → sound

### References

- Box2D
  - https://box2d.org/
- miniaudio
  - https://miniaud.io/
- SDL3

---

# Milestone 5 — Game #1

## Build a Complete 2D Game

추천:

- Breakout
- Asteroids
- Pong 확장판

예:

```text
████ ████ ████ ████
████ ████ ████ ████


           ●


         ━━━━━
```

### 반드시 사용

- Scene
- Entity
- Input
- Renderer
- Texture
- Collision
- Physics
- Audio
- Asset
- Game State

### 중요한 규칙

이 단계에서는 엔진 기능 추가보다 **게임 완성**이 우선이다.

게임을 만들면서 발견되는 불편함을 기록한다.

```text
ENGINE_NOTES.md

- Scene switching이 불편하다.
- Entity deletion이 위험하다.
- Physics와 Transform ownership이 이상하다.
- Texture가 중복 load된다.
- Game code가 OpenGL을 직접 알고 있다.
```

이 목록이 다음 단계의 학습 주제가 된다.

---

# PART II — ENGINE ARCHITECT

# Milestone 6 — Architecture Refactoring

게임 하나를 완성한 다음에만 진행한다.

### Goal

외부 라이브러리에 대한 의존성을 엔진 내부로 숨긴다.

```text
                    Engine
                      │
          ┌───────────┼───────────┐
          ▼           ▼           ▼

      IRenderer   IPhysics     IAudio
          │           │           │
          ▼           ▼           ▼

       OpenGL        Box2D      miniaudio
```

예:

```cpp
class IPhysicsBackend
{
public:
    virtual BodyHandle CreateBody(...) = 0;
    virtual void Step(float dt) = 0;
};
```

### Learn

- Interface
- Dependency inversion
- Dependency direction
- Backend
- Handle
- Ownership
- Abstraction boundary

### Important Rule

> 추상화를 미리 예측하지 않는다.

```text
구현
 ↓
사용
 ↓
문제 발견
 ↓
반복되는 구조 발견
 ↓
추상화
```

순서로 진행한다.

### Core Reference

**Game Engine Architecture — Jason Gregory**

전체 게임 엔진 구조를 이해하는 지도처럼 사용한다.

처음부터 정독하기보다 현재 작업 중인 subsystem의 chapter를 읽는다.

- https://www.gameenginebook.com/

---

# PART III — 3D ENGINE

# Milestone 7 — 3D Transform / Camera

### Goal

> WASD + Mouse로 이동 가능한 3D Camera와 Cube.

```text
        +-------+
       /       /|
      +-------+ |
      |       | +
      |       |/
      +-------+
```

### Initial Math

이 단계에서는 GLM을 사용한다.

```cpp
glm::vec3
glm::mat4
glm::quat
```

### Learn

- Vector
- Matrix
- Transform
- Local Space
- World Space
- View Space
- Clip Space
- Perspective
- Camera

### Definition of Done

- [ ] 3D Cube
- [ ] Perspective projection
- [ ] WASD movement
- [ ] Mouse look
- [ ] Window aspect ratio 대응

### References

- LearnOpenGL — Coordinate Systems
- LearnOpenGL — Camera
- GLM
  - https://github.com/g-truc/glm

---

# Milestone 8 — Blender → MyEngine

### Goal

> Blender에서 만든 모델을 자신의 엔진에 불러온다.

```text
Blender
   ↓
glTF
   ↓
Asset Pipeline
   ↓
Mesh
Material
Texture
   ↓
MyEngine
```

### Learn

- Vertex
- Index
- Normal
- UV
- Tangent
- Mesh
- Material
- Shader
- Model transform

### Add

- Directional Light
- Material
- Texture
- Simple lighting

### Definition of Done

- [ ] Blender model import
- [ ] Texture
- [ ] Material
- [ ] Directional light
- [ ] Model transform

---

# Milestone 9 — 3D Physics Integration

### Goal

기존 3D physics engine을 연결한다.

추천:

**Jolt Physics**

```text
Entity

├── Transform
├── MeshRenderer
├── Collider
└── RigidBody
        │
        ▼
       Jolt
```

### Target

```text
        □
        ↓

        □
       □□
      □□□
────────────────
```

상자를 떨어뜨리고 쌓는다.

### Learn

아직 내부 solver를 구현하지 않는다.

먼저:

- Physics World
- Body
- Collider
- Mass
- Static / Dynamic
- Physics timestep
- Transform synchronization

을 이해한다.

### Reference

- Jolt Physics
  - https://github.com/jrouwe/JoltPhysics

---

# Milestone 10 — Game #2

## Build a Small 3D Game

추천:

### Marble Game

```text
              ●

        _____/ \____
       /            \
 _____/              \_____
```

### 반드시 포함

- 3D Renderer
- Camera
- Input
- Physics
- Collision
- Imported Models
- Material
- Lighting
- Audio
- Scene
- Asset

이 시점에서 게임 엔진 전체를 **두 번 관통**한 상태가 된다.

---

# PART IV — ENGINE IMPLEMENTER

이제 Black Box를 하나씩 제거한다.

```text
현재

GLM
OpenGL
Box2D / Jolt
miniaudio

        ↓

직접 구현

MyMath
MyRenderer
MyPhysics
MyAudio
```

---

# Milestone 11 — MyMath

## Build a Math Library

```text
MyMath
├── Vec2
├── Vec3
├── Vec4
├── Mat3
├── Mat4
└── Quaternion
```

### Learn

```text
Vector
  ↓
Dot Product
  ↓
Cross Product
  ↓
Matrix
  ↓
Basis
  ↓
Coordinate Transformation
  ↓
Projection
  ↓
Quaternion
```

### Questions to Answer

- Dot product가 왜 각도를 나타내는가?
- Cross product는 왜 normal vector가 되는가?
- 왜 3D transform에서 4×4 matrix를 사용하는가?
- Homogeneous coordinate란 무엇인가?
- Perspective divide는 왜 필요한가?
- Quaternion은 어떤 문제를 해결하는가?

### Final Goal

기존:

```cpp
glm::vec3
```

를:

```cpp
Vec3
```

로 점차 교체한다.

### References

- Game Engine Architecture — 3D Math
- Scratchapixel
  - https://www.scratchapixel.com/
- 3Blue1Brown — Essence of Linear Algebra

---

# Milestone 12 — CPU Software Renderer

## Graphics Deep Dive

GPU를 사용하지 않고 3D rendering pipeline을 직접 구현한다.

```text
Vertex
 ↓
Transform
 ↓
Projection
 ↓
Clipping
 ↓
Rasterization
 ↓
Interpolation
 ↓
Depth Test
 ↓
Shading
 ↓
Pixel
```

### Step 1

```text
setPixel()
Line
Triangle
```

### Step 2

```text
Triangle Filling
Barycentric Coordinates
```

### Step 3

```text
3D Transform
Camera
Perspective
```

### Step 4

```text
Clipping
Z-buffer
```

### Step 5

```text
Texture Mapping
Perspective Correct Interpolation
```

### Step 6

```text
Normal
Diffuse Lighting
```

### Final Goal

> CPU만으로 textured 3D model 렌더링.

### References

**TinyRenderer**

- https://github.com/ssloy/tinyrenderer

**Scratchapixel**

- https://www.scratchapixel.com/

**Pikuma — 3D Computer Graphics Programming**

- https://pikuma.com/courses/learn-3d-computer-graphics-programming

---

# Milestone 13 — Renderer Backend

Software Renderer를 기존 엔진에 연결한다.

```text
                IRenderer
                    │
           ┌────────┴─────────┐
           ▼                  ▼

   OpenGLRenderer      SoftwareRenderer
```

동일한 Scene을:

```text
Backend = OpenGL
```

또는:

```text
Backend = Software
```

로 렌더링할 수 있게 한다.

### Purpose

이 단계에서 **Renderer abstraction의 의미를 실제로 체감**한다.

---

# Milestone 14 — MyPhysics2D

## Physics Deep Dive

처음부터 3D 물리를 만들지 않는다.

2D rigid-body physics engine을 만든다.

```text
Particle
 ↓
Velocity / Acceleration
 ↓
Force
 ↓
Numerical Integration
 ↓
Rigid Body
 ↓
Rotation
 ↓
Collision Detection
 ↓
Collision Response
 ↓
Impulse
 ↓
Friction
 ↓
Constraint
 ↓
Joint
```

### Physics

- Newton's Laws
- \(F = ma\)
- Momentum
- Impulse
- Torque
- Angular Velocity
- Moment of Inertia
- Energy

### Numerical Methods

- Explicit Euler
- Semi-Implicit Euler
- Verlet
- RK 개념

### Collision

```text
Circle vs Circle
AABB
OBB
SAT
```

이후 관심이 생기면:

```text
GJK
EPA
```

### Solver

후반:

- Constraint
- Jacobian
- Sequential Impulse
- Iterative Solver

### References

**Pikuma — Game Physics Engine Programming**

- https://pikuma.com/courses/game-physics-engine-programming

**Box2D source & documentation**

- https://box2d.org/

**Erin Catto — Physics / Constraint 자료**

- Box2D 관련 GDC presentations

---

# Milestone 15 — Physics Backend

```text
              IPhysics2D
                  │
       ┌──────────┴──────────┐
       ▼                     ▼

     Box2D               MyPhysics
```

같은 scene을 두 backend에서 실행한다.

### Test Scene

```text
    □
   □□
  □□□
 □□□□
──────────────
```

### Compare

- Stability
- Penetration
- Friction
- Stacking
- Timestep sensitivity
- Performance

### Questions

> 왜 내 physics에서는 박스가 흔들리는가?

> Box2D는 왜 안정적인가?

> Solver iteration을 늘리면 왜 결과가 달라지는가?

이 질문들이 다음 학습 주제가 된다.

---

# Milestone 16 — MyAudio

## Audio / DSP Deep Dive

초기:

```cpp
audio.Play("gun.wav");
```

였다면 이제 내부를 공부한다.

### Digital Audio

```text
Wave
 ↓
Sampling
 ↓
Sample Rate
 ↓
Bit Depth
 ↓
Nyquist
 ↓
Aliasing
```

### Signal Generation

직접 생성:

- Sine
- Square
- Saw
- Triangle
- Noise

### Mixer

```text
Sound A ─┐
Sound B ─┼──→ Mixer ─→ Output
Sound C ─┘
```

### DSP

- Gain
- Pan
- Clipping
- Low-pass
- High-pass
- Delay
- Reverb 기초
- Convolution
- Fourier transform 개념

### Spatial Audio

- Distance attenuation
- Stereo panning
- Doppler
- Occlusion
- HRTF 개념

### References

- The Audio Programmer
  - https://www.youtube.com/@TheAudioProgrammer
- miniaudio
  - https://miniaud.io/

---

# PART V — ENGINE ENGINEERING

# Milestone 17 — Profiling

## Rule

> Optimize only after measuring.

### Build

```text
FPS       : 144
Frame     : 6.94 ms

Game      : 0.62 ms
Physics   : 0.81 ms
Render    : 3.12 ms

Entities  : 12,450
DrawCalls : 314
```

### Learn

- CPU profiler
- Frame time
- Hotspot
- Benchmark
- Instrumentation

---

# Milestone 18 — Memory / Data Layout

### Learn

- Stack
- Heap
- Cache
- Cache Line
- Alignment
- Pool Allocator
- Arena Allocator
- Object Pool
- Data-Oriented Design
- AoS vs SoA

Example:

```text
Array of Structures

Organism
Organism
Organism
Organism
```

versus:

```text
Structure of Arrays

Positions[]
Velocities[]
Energies[]
```

### Target

10,000~100,000 entity benchmark를 만들어 구조에 따른 차이를 측정한다.

---

# Milestone 19 — Multithreading / Job System

### Architecture

```text
                    Main Thread
                         │
          ┌──────────────┼───────────────┐
          ▼              ▼               ▼
      Physics Job   Animation Job   Asset Job

            Worker Thread Pool
```

### Learn

- `std::thread`
- mutex
- atomic
- condition variable
- race condition
- lock contention
- thread pool
- task
- job queue
- dependency

---

# Low-Level Reference

이 시점부터 **Handmade Hero**를 참고하기 좋다.

초반보다 여기에서 보면:

- Memory
- Platform layer
- Rendering
- Performance
- Code organization

에 대한 판단 근거를 훨씬 이해하기 쉽다.

- https://hero.handmade.network/

---

# PART VI — TOOLS / EDITOR

# Milestone 20 — MyEngine Editor

### Target

```text
┌─────────────────────────────────────┐
│ MyEngine Editor                     │
├───────────┬─────────────────────────┤
│ Hierarchy │                         │
│           │       Scene View        │
│ Player    │                         │
│ Light     │          [Cube]         │
│ Camera    │                         │
├───────────┴─────────────────────────┤
│ Inspector                           │
│ Position   0 2 4                    │
│ Rotation   0 0 0                    │
│ Scale      1 1 1                    │
└─────────────────────────────────────┘
```

### Features

- Hierarchy
- Inspector
- Entity creation
- Transform editing
- Scene save/load
- Asset Browser
- Play / Stop
- Physics debug draw
- Renderer debug view
- Profiler

---

# FINAL CAPSTONE — Build a Game

엔진 기능 추가를 멈추고 작은 게임 하나를 완성한다.

추천:

- 3D Physics Puzzle
- Marble Game 확장판
- 작은 FPS Arena
- 작은 Robot Simulation
- 3D Exploration Game

### 최소 사용 기능

- [ ] 3D Renderer
- [ ] Imported Models
- [ ] Materials
- [ ] Lighting
- [ ] Physics
- [ ] Audio
- [ ] Input
- [ ] Scene
- [ ] Asset
- [ ] UI
- [ ] Multiple Levels
- [ ] Editor
- [ ] Profiling

---

# Milestone Overview

| # | Milestone | Main Result |
|---|---|---|
| 0 | Bootstrap | 실행되는 C++ Engine |
| 1 | Game Loop | Window / Input / Time |
| 2 | Renderer | Sprite Renderer |
| 3 | Scene | Entity / Component |
| 4 | Integration | Physics / Audio / Assets |
| 5 | Game #1 | 완성된 2D Game |
| 6 | Architecture | Backend abstraction |
| 7 | 3D | Cube / Camera |
| 8 | Asset Pipeline | Blender → Engine |
| 9 | Physics 3D | Rigid Body |
| 10 | Game #2 | 완성된 3D Game |
| 11 | MyMath | Math Library |
| 12 | Rasterizer | Software Renderer |
| 13 | MyRenderer | Renderer Backend |
| 14 | MyPhysics | 2D Physics Engine |
| 15 | Physics Backend | Box2D ↔ MyPhysics |
| 16 | MyAudio | Mixer / DSP |
| 17 | Profiling | Performance Measurement |
| 18 | Memory | Data-Oriented Design |
| 19 | Job System | Multithreading |
| 20 | Editor | Engine Tools |
| Final | Capstone | 완성된 Game |

---

# Core Reference Map

## C++

**LearnCpp**

C++ 학습용.

https://www.learncpp.com/

**cppreference**

언어/API reference.

https://en.cppreference.com/

---

## Engine Architecture

**Game Engine Architecture — Jason Gregory**

엔진 전체 구조를 이해하기 위한 핵심 reference.

https://www.gameenginebook.com/

**The Cherno — Hazel**

실제 C++ engine architecture 구현 참고.

https://www.youtube.com/@TheCherno

**Pikuma — C++ 2D Game Engine**

초기 integration 단계와 잘 맞는 프로젝트형 강좌.

https://pikuma.com/courses/cpp-2d-game-engine-development

---

## Graphics

**LearnOpenGL**

GPU rendering 입문.

https://learnopengl.com/

**TinyRenderer**

Software rasterizer 직접 구현.

https://github.com/ssloy/tinyrenderer

**Scratchapixel**

그래픽스의 수학/알고리즘 이해.

https://www.scratchapixel.com/

**3Blue1Brown — Essence of Linear Algebra**

선형대수 직관.

---

## Physics

**Box2D**

초기 black box이자 나중에는 source reference.

https://box2d.org/

**Jolt Physics**

3D physics integration.

https://github.com/jrouwe/JoltPhysics

**Pikuma — Game Physics Engine Programming**

2D physics engine 직접 제작.

https://pikuma.com/courses/game-physics-engine-programming

**Erin Catto**

Rigid body constraint / solver 심화.

---

## Audio

**miniaudio**

초기 audio backend.

https://miniaud.io/

**The Audio Programmer**

Digital Audio / DSP.

https://www.youtube.com/@TheAudioProgrammer

---

# Study Workflow

모든 milestone은 아래 사이클을 따른다.

```text
① Goal
   ↓
"Cube를 화면에 띄운다."

② Problem
   ↓
"무엇이 필요한가?"

③ Minimum Study
   ↓
Matrix / Shader / Vertex

④ Implementation
   ↓

⑤ Working Result
   ↓

⑥ Retrospective
   ↓
"왜 이렇게 동작하는가?"

⑦ Deep Dive 후보 기록
   ↓

⑧ Next Milestone
```

---

# Definition of Done Rule

각 milestone을 시작할 때 완료조건을 먼저 작성한다.

예:

## 3D Camera

- [ ] Cube가 보인다.
- [ ] Perspective projection이 적용된다.
- [ ] WASD 이동이 된다.
- [ ] Mouse rotation이 된다.
- [ ] Window resize가 된다.
- [ ] Delta time에 독립적이다.

모두 만족하면 다음 단계로 이동한다.

추가 개선 아이디어는:

```text
BACKLOG.md
```

로 옮긴다.

---

# Recommended Time Allocation

대략적인 학습 비율:

```text
Build        60~70%
Study        20~30%
Refactoring  10%
```

목표는:

```text
공부
 ↓
공부
 ↓
공부
 ↓
언젠가 프로젝트
```

가 아니다.

항상:

```text
Goal
 ↓
필요성 발생
 ↓
공부
 ↓
구현
 ↓
작동
 ↓
다음 Goal
```

을 유지한다.

---

# Further Exploration

# World Simulation & Artificial Life

> **이 섹션은 기존 Game Engine Roadmap의 대체 경로가 아니다.**
>
> 앞의 게임 엔진 과정을 기반으로 **더 나아가는 확장 로드맵**이다.

게임 엔진을 어느 정도 구축하고 나면 다음 방향으로 확장할 수 있다.

```text
Game Engine
     ↓
Simulation Engine
     ↓
World Simulator
     ↓
Artificial Life
     ↓
Evolution
     ↓
Neuroevolution
```

최종적으로 목표하는 세계의 예:

```text
             Virtual World

 ┌────────────────────────────────┐
 │                                │
 │  Food             Predator     │
 │   ·                 ▲          │
 │                                │
 │       ◉ Organism               │
 │                                │
 │   ·                ◉           │
 │             ·                  │
 │                                │
 └────────────────────────────────┘

              ↓

      Birth / Survival / Death

              ↓

          Reproduction

              ↓

            Mutation

              ↓

      Natural Selection

              ↓

      Many Generations
```

---

# Simulation Stage S0 — Simulation Runtime

게임과 simulation의 중요한 차이를 이해한다.

게임:

```text
60 FPS
 ↓
사람에게 보여주는 것이 중요
```

Simulation:

```text
10,000+ steps
 ↓
정확성 / 속도 / 재현성이 중요
```

따라서 simulation과 rendering을 분리한다.

```text
Simulation
1000 steps/sec
      │
      ├──────→ Data
      │
      ▼
Renderer
60 FPS
```

### Implement

- Fixed timestep
- Simulation clock
- Random seed
- Deterministic execution 가능한 구조
- Pause
- Single step
- Fast-forward
- Replay

그리고 중요한 기능:

```text
Headless Mode
```

```text
Renderer OFF
Audio OFF

Simulation Only
```

### Goal

> 같은 random seed로 실행하면 같은 결과를 재현할 수 있는 simulation.

---

# Simulation Stage S1 — Agent World

### Goal

1000~10000개의 agent가 움직이는 world.

```text
Agent

├ Position
├ Velocity
├ Energy
├ Sensor
└ Controller
```

환경:

```text
World

├ Boundaries
├ Obstacles
├ Food
└ Agents
```

### Learn

- Agent-based simulation
- Spatial partition
- Uniform grid
- Quadtree
- Large entity population
- Fixed timestep
- Random process

---

# Simulation Stage S2 — Ecosystem

생물과 자원을 추가한다.

```text
World
│
├ Plants
├ Food
├ Herbivores
└ Predators
```

기본 규칙:

```text
Movement
    ↓
Energy Consumption

Food
    ↓
Energy Gain

Energy <= 0
    ↓
Death
```

### Add Statistics

```text
Population
│
│ Prey       /\/\____/\/\
│
│ Predator      /\___/\
│
└────────────────────── Time
```

측정:

- Population
- Average lifespan
- Food amount
- Birth rate
- Death rate

### Goal

> Predator / Prey population dynamics가 나타나는 world.

---

# Simulation Stage S3 — Genome & Generation

각 생물에게 Genome을 추가한다.

```text
Genome
│
├ bodySize
├ speed
├ sensorRange
├ metabolism
├ reproductionThreshold
└ lifespan
```

부모:

```text
speed = 1.00
```

자식:

```text
speed =
parent.speed
+
mutation
```

### Implement

- Reproduction
- Mutation
- Heredity
- Generation tracking
- Gene distribution statistics

### Important

Simulation을 반드시 정확히 분리된 세대로 만들 필요는 없다.

두 방식 모두 실험할 수 있다.

```text
Generational

Generation 1
   ↓
Generation 2
   ↓
Generation 3
```

또는:

```text
Continuous / Steady State

Birth
Death
Birth
Birth
Death
...
```

---

# Simulation Stage S4 — Natural Selection

이제 환경이 selection pressure를 만든다.

예:

```text
World A
Food abundant

World B
Food scarce

World C
Many predators

World D
High movement cost
```

하지만 다음과 같이 프로그래밍하지 않는다.

```text
"빠른 개체에게 +10 fitness"
```

가능하면 세계 법칙만 만든다.

```text
움직이면 에너지 소비
음식을 먹으면 에너지 획득
죽으면 번식 불가능
에너지가 충분하면 번식
자식은 부모와 조금 다름
```

그러면:

```text
Environment
      ↓
Survival Difference
      ↓
Reproduction Difference
      ↓
Gene Frequency Change
```

가 발생한다.

### Measure

- Mean trait
- Variance
- Gene frequency
- Fitness proxy
- Reproduction count
- Survival rate

---

# Simulation Stage S5 — Brain / Sensors / Actions

Scripted AI:

```cpp
if (foodIsNear)
    moveTowardFood();
```

를 점차 제거한다.

대신:

```text
        Sensors

Food Direction
Food Distance
Energy
Enemy Direction
Velocity

           ↓

     Neural Network

           ↓

         Actions

Move
Turn
Attack
Eat
```

으로 변경한다.

### Architecture

```text
Environment
     ↓
Sensors
     ↓
Brain
     ↓
Motor / Action
     ↓
Physics
     ↓
Environment
```

이 구조는 로봇 simulation과 거의 동일하다.

---

# Simulation Stage S6 — Neuroevolution

Neural Network의 parameter를 Genome으로 넣는다.

```text
Genome
   │
   ├ Morphology Genes
   │
   └ Neural Network Genes
              │
              ▼
             Brain
```

부모:

```text
Neural Network
weights
```

자식:

```text
weights + mutation
```

### Goal

사람이 행동 규칙을 작성하지 않아도 행동 전략이 진화하도록 한다.

관찰할 수 있는 현상:

- Food seeking
- Avoidance
- Hunting
- Grouping
- Territorial behavior
- Exploration

이러한 행동을 직접 hard-code하지 않는 것이 핵심이다.

---

# Simulation Stage S7 — Evolving Neural Topology

다음 단계에서는 weight뿐 아니라 network 구조 자체를 진화시킬 수 있다.

관련 주제:

- Genetic Algorithm
- Evolution Strategy
- NEAT
- Speciation
- Crossover
- Mutation
- Topology evolution

### Core Reference

**NEAT**

Kenneth Stanley & Risto Miikkulainen  
*Evolving Neural Networks through Augmenting Topologies*

검색 키워드:

```text
NEAT neuroevolution paper
```

---

# Simulation Stage S8 — Morphological Evolution

이제 Brain뿐 아니라 **Body 자체를 진화**시킨다.

```text
Genome
   ↓
Body Generator
   ↓

Body
├ Limb
├ Limb
├ Joint
├ Sensor
└ Muscle

   ↓

Physics
   ↓
Behavior
```

Genome 예:

```text
Body Genes
├ limbCount
├ limbLength
├ bodySize
├ jointRange
├ muscleStrength
└ sensorPosition
```

이 단계에서 기존 Game Engine Roadmap의:

- Physics
- Constraint
- Joint
- Rigid Body
- Math
- Renderer

지식이 직접 활용된다.

### 중요한 역사적 Reference

**Karl Sims — Evolving Virtual Creatures**

검색:

```text
Karl Sims Evolving Virtual Creatures 1994
```

가상 생명체의 morphology와 controller를 진화시키는 이 분야의 대표적인 고전 연구다.

---

# Simulation Stage S9 — Emergence & Complex Systems

이 단계부터 관심의 중심이:

```text
"개별 Agent를 어떻게 만들까?"
```

에서:

```text
"단순한 local rule로부터
어떤 global behavior가 발생하는가?"
```

로 이동한다.

관련 분야:

```text
Complex Systems
│
├ Emergence
├ Self Organization
├ Cellular Automata
├ Dynamical Systems
├ Chaos
├ Networks
└ Population Dynamics
```

예:

```text
Simple Rules
     ↓
Agent Interaction
     ↓
Feedback
     ↓
Population Dynamics
     ↓
Emergent Behavior
```

### References

**The Nature of Code — Daniel Shiffman**

- Autonomous Agents
- Genetic Algorithms
- Neural Networks
- Physics simulation

https://natureofcode.com/

**Complexity — Melanie Mitchell**

복잡계에 대한 전체적인 개념 지도.

**NetLogo Models Library**

다양한 agent-based simulation 사례를 관찰하는 데 좋다.

---

# Simulation Stage S10 — Large-Scale Simulation

생명체가 많아지면 기존 게임 엔진의 low-level 학습이 중요해진다.

```text
1,000 Agents
        ↓
10,000
        ↓
100,000
        ↓
1,000,000
```

필요:

- ECS
- Data-Oriented Design
- Spatial partitioning
- Cache-friendly layout
- SIMD
- Job system
- Multithreading
- GPU compute 가능성

예:

```text
AoS

Organism
Organism
Organism
Organism
```

를:

```text
SoA

Positions[]
Velocities[]
Energy[]
Genome[]
Brain[]
```

구조와 비교한다.

### Goal

> Rendering 없이 가능한 한 많은 simulation step을 실행.

---

# Simulation Stage S11 — Experiment Platform

단순히 화면을 보는 프로그램에서 **실험 가능한 simulation platform**으로 확장한다.

```text
Experiment

├ Config
├ Random Seed
├ Environment
├ Population
├ Simulation
├ Statistics
└ Result
```

예:

```text
Experiment #147

Seed              85124
Population        5000
Food Density      0.23
Mutation Rate     0.015
Predator Ratio    0.10
Simulation Steps  10,000,000
```

### Add

- Config file
- Batch simulation
- Data export
- CSV
- Statistics
- Graph
- Replay
- Save state
- Random seed
- Experiment ID

### Headless Batch

```text
Experiment 1 ─┐
Experiment 2 ─┤
Experiment 3 ─┼──→ Parallel Simulation
Experiment 4 ─┤
Experiment 5 ─┘
```

---

# Possible Final Architecture

게임 엔진에서 시작했던 프로젝트가 최종적으로 다음과 같이 진화할 수 있다.

```text
WorldSimulationEngine
│
├ Core
│
├ Simulation
│   ├ Clock
│   ├ Scheduler
│   ├ Random
│   └ Replay
│
├ World
│
├ ECS
│
├ Physics
│
├ Renderer
│
├ Environment
│
├ Organism
│   ├ Body
│   ├ Energy
│   ├ Sensor
│   └ Brain
│
├ Genetics
│   ├ Genome
│   ├ Mutation
│   ├ Crossover
│   └ Reproduction
│
├ Neural
│
├ Evolution
│
├ Statistics
│
├ Experiment
│
└ Editor
```

---

# Long-Term Learning Map

```text
                       C++
                        │
                        ▼
                  Game Engine
                        │
         ┌──────────────┼──────────────┐
         ▼              ▼              ▼

      Graphics        Physics        Audio
         │              │
         │              ▼
         │        Rigid Body Dynamics
         │              │
         └──────────────┤
                        ▼
                Simulation Engine
                        │
                        ▼
                   Agent World
                        │
                        ▼
                    Ecosystem
                        │
                        ▼
                    Genetics
                        │
                        ▼
               Natural Selection
                        │
            ┌───────────┴──────────┐
            ▼                      ▼

      Neural Brain              Morphology
            │                      │
            ▼                      ▼
      Neuroevolution      Body Evolution
            │                      │
            └───────────┬──────────┘
                        ▼
                 Artificial Life
                        │
                        ▼
                  Complex Systems
                        │
                        ▼
                    Emergence
```

---

# Final Principle

이 전체 프로젝트에서 계속 유지해야 할 원칙은 하나다.

```text
새로운 이론을 먼저 공부한다
```

가 아니라:

```text
만들고 싶은 현상이 있다
        ↓
현재 엔진으로 구현한다
        ↓
문제가 발생한다
        ↓
문제를 이해하기 위해 공부한다
        ↓
직접 구현한다
        ↓
결과를 관찰한다
        ↓
새로운 질문이 생긴다
```

이다.

게임 엔진은 최종 목적이면서 동시에 이후의 더 큰 관심사를 탐구하기 위한 **실험 플랫폼의 기반**이 된다.

```text
Game Engine
     ↓
Understanding Machines
     ↓
Simulation Engine
     ↓
Understanding Worlds
     ↓
Artificial Life
     ↓
Understanding Emergent Systems
```

이 프로젝트의 궁극적인 목적은 특정 게임 엔진을 완성하는 것에 한정되지 않는다.

> **컴퓨터 안에 하나의 세계를 만들고, 그 세계가 어떤 규칙에 의해 움직이며, 그 안에서 복잡한 현상이 어떻게 발생하는지를 직접 구현하고 이해하는 것.**

그것을 장기적인 방향으로 삼는다.