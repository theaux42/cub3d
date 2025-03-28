# Cube3D - Raycasting Renderer 🎮🕹️

## Project Overview
Cube3D is a 3D rendering project inspired by the classic Wolfenstein 3D game, implemented in C using raycasting techniques and the MinilibX graphics library. The goal is to create a simple yet immersive first-person perspective game engine from scratch.

## 🚀 Project Features
- Raycasting rendering technique
- First-person view navigation
- 2D minimap 
- Wall collision detection
- Dynamic field of view adjustment
- Smooth player movement and rotation

## 📋 Technical Requirements
- Language: C
- Graphics Library: MinilibX
- Rendering Technique: Raycasting
- Platforms: Linux / macOS

## 🔧 Key Technical Concepts
### Raycasting Algorithm
- Casts rays from the player's position
- Calculates wall distances and heights
- Renders 3D perspective from 2D map

### Player Mechanics
- WASD/Arrow key movement
- Rotation with A/D keys
- Sprint functionality
- FOV (Field of View) adjustment

## 🛠️ Compilation

### Prerequisites
- GCC Compiler
- MinilibX library
- Make

### Compilation Command
```bash
make
```

### Running the Program
```bash
./cube3d map.cub
```

## 🎮 Controls

### Movement
- ⬆️ Up Arrow / W: Move Forward
- ⬇️ Down Arrow / S: Move Backward
- ⬅️ Left Arrow: Strafe Left
- ➡️ Right Arrow: Strafe Right

### Camera
- A: Rotate Left
- D: Rotate Right
- Shift: Sprint
- + / -: Adjust Field of View

### Misc
- ESC: Exit Game

## 📦 Project Structure
```
cube3d/
│
├── src/
│   ├── main.c
│   ├── raycasting.c
│   ├── player_movement.c
│   └── rendering.c
│
├── includes/
│   ├── cube3d.h
│   └── structs.h
│
├── maps/
│   ├── basic.cub
│   └── complex.cub
│
└── Makefile
```

## 🧠 Raycasting Explanation
Raycasting is a rendering technique that simulates a 3D environment by:
1. Casting rays from the player's position
2. Calculating intersections with walls
3. Projecting walls onto a 2D screen
4. Rendering walls with perspective correction

## 🚧 Challenges & Learning Outcomes
- Low-level graphics rendering
- Performance optimization
- Mathematical transformations
- Memory management in C
- Complex algorithm implementation

## 🔍 Performance Considerations
- Optimize ray calculations
- Efficient map traversal
- Minimize computational complexity

## 📝 Notes
- Inspired by Wolfenstein 3D (1992)
- Educational project to understand basic 3D rendering
- Not a full game, but a rendering engine prototype

## 👥 Contributors
- [Your Name]
- [Team Members if applicable]

## 📄 License
[Specify your license, e.g., MIT, GPL]

## 🌟 Acknowledgments
- 42 School Curriculum
- MinilibX Library
- Classic FPS Game Pioneers
