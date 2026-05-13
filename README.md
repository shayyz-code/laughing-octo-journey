# Laughing Octo Journey 🐙

Welcome to the **Laughing Octo Journey**, a whimsical 2D graphical adventure game written in C using the **Raylib** library.

In this game, you take on the role of a happy-go-lucky octopus exploring the wonders of the ocean floor. Navigate through different ocean zones, collect treasures, and keep your "Laughter Level" high!

## Features

- **2D Graphical Interface:** A colorful underwater world powered by Raylib.
- **Animated Octopus:** Your octopus friend bobs and giggles as you explore.
- **Heads-Up Display (HUD):** Real-time tracking of your current location, description, and "Jolly Meter" (Laughter Level).
- **Professional Structure:** Organized C project layout with clear separation of headers and source files.

## Controls

- **Movement:** Use `Arrow Keys` or `WASD` to swim between locations.
- **Giggle:** Press `L` to let out a bubbly octopus giggle and boost your happiness.
- **Exit:** Close the window or press `ESC` to end your journey.

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

- `include/`: Header files (`game.h`, `world.h`, `player.h`).
- `src/`: Source code logic (`main.c`, `world.c`, `player.c`).
- `bin/`: The final compiled executable.
- `obj/`: Temporary object files during compilation.
- `Makefile`: Build configuration for Raylib and standard frameworks.
