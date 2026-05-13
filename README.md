# Laughing Octo Journey 🐙

Welcome to the **Laughing Octo Journey**, a whimsical text-based adventure game written in C. 

In this game, you take on the role of a happy-go-lucky octopus exploring the wonders of the ocean floor. Your goal is to explore, collect treasures, and keep your "Laughter Level" high!

## Features

- **Whimsical Ocean World:** Explore unique locations like the Coral Reef, Dark Cave, and Sunken Shipwreck.
- **Inventory System:** Collect items like Shiny Pearls and Golden Dubloons.
- **Mood System:** Use the `laugh` command to boost your octopus's happiness.
- **Pure C:** Lightweight and fast, built with standard C libraries.

## Commands

- `north`, `south`, `east`, `west`: Move between locations.
- `look`: Examine your current surroundings and see items.
- `take <item>`: Pick up an item (e.g., `take Shiny Pearl`).
- `inventory`: List the items you are carrying.
- `laugh`: Let out a bubbly giggle and boost your Laughter Level.
- `status`: Check your current location and stats.
- `help`: See the list of commands.
- `quit`: Exit the journey.

## Building and Running

### Prerequisites

- A C compiler (like `gcc` or `clang`)
- `make` build tool

### Instructions

1. **Compile the game:**
   ```bash
   make
   ```

2. **Run the game:**
   ```bash
   ./octo-adventure
   ```

3. **Clean build files:**
   ```bash
   make clean
   ```

## Project Structure

- `main.c`: Entry point and game loop.
- `world.c/h`: Map and location logic.
- `player.c/h`: Player actions and state.
- `game.h`: Core data structures.
- `Makefile`: Build configuration.

Stay octo-awesome!
