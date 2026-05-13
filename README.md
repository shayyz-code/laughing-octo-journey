# Laughing Octo Journey 🐙

Welcome to the **Laughing Octo Journey**, a high-fidelity 2D graphical adventure game written in C using the **Raylib** library.

In this game, you take on the role of a happy-go-lucky octopus exploring a living, breathing ocean floor. Navigate through distinct biomes, collect bioluminescent treasures, and keep your "Jolly Meter" high!

## High-Fidelity Features

- **Underwater Shaders:** Real-time GLSL fragment shaders create a dynamic ripple distortion effect for an immersive water feel.
- **Living Ocean (Particle System):** Rising air bubbles and drifting "marine snow" particles give the water volume and life.
- **Frame-Based Animation:** A custom animation system gives the octopus fluid tentacle movement as it swims.
- **Bioluminescence:** The octopus and hidden treasures emit a soft, atmospheric glow, especially vital in the dark depths of the Abyss.
- **Spatial Exploration:** Seamlessly swim across the screen and transition between areas by touching the edges.
- **Professional Architecture:** Modular C code with a dedicated post-processing pipeline and shader management.

## Controls

- **Movement:** Hold `Arrow Keys` or `WASD` to swim freely.
- **Transition:** Touch the screen edges to enter a new ocean zone.
- **Take Item:** Press `T` to pick up a treasure you've found.
- **Giggle:** Press `L` to let out a bubbly octopus giggle and boost your "Jolly Meter".
- **Exit:** Press `ESC` or close the window.

## Building and Running

### Prerequisites

- A C compiler (like `gcc` or `clang`)
- `make` build tool
- **Raylib** library (On macOS: `brew install raylib`)

### Instructions

1. **Compile the game:**
   ```bash
   make
   ```

2. **Run the game:**
   ```bash
   ./bin/octo-adventure
   ```

3. **Clean build files:**
   ```bash
   make clean
   ```

## Project Structure

- `include/`: Header files for game logic, world building, and particles.
- `src/`: Core implementation files.
- `shaders/`: GLSL fragment shaders for post-processing effects.
- `bin/`: The final compiled executable.
- `obj/`: Compiled object files.
- `Makefile`: Optimized build configuration for Raylib and framework linking.
-
