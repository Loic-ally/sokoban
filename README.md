# Pokémon Sokoban

Welcome to **Pokémon Sokoban**! This is a delightful twist on the classic Sokoban puzzle game, featuring Pokémon-themed boxes. In this game, you'll push these themed boxes around a warehouse, aiming to get them to designated storage locations. This implementation of Sokoban is written in C using CFSML.

<!-- ![Pokémon Sokoban Banner](path/to/banner/image.png)  Add a banner image for visual appeal -->

## Table of Contents
- [Pokémon Sokoban](#pokémon-sokoban)
  - [Table of Contents](#table-of-contents)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Gameplay](#gameplay)
    - [Controls](#controls)
  - [Future Plans](#future-plans)
  - [Contributing](#contributing)
  - [License](#license)

## Installation

To install and run **Pokémon Sokoban**, follow these steps:

1. **Clone the repository**:
   ```sh
   git clone https://github.com/Loic-ally/sokoban.git
   cd sokoban

2. **Build the project using Make**:
   ```sh
   make
   ```

## Usage

**Once the project is built, you can start the game by running**:
```sh
./sokoban
```

## Gameplay

The objective of the game is to push all the Pokémon-themed boxes onto the storage locations. The player can move up, down, left, and right. However, the player can only push one box at a time and cannot pull boxes.

### Controls
* **Arrow Keys**: Move the player up, down, left, or right
* **R**: Restart the current level
* **Q**: Quit the game

## Future Plans

Currently, the levels are randomly generated, and some may not be solvable. Our future plans include training an AI to generate only solvable levels, ensuring a more enjoyable and challenging experience for players.

## Contributing

Contributions are welcome! If you have any ideas or improvements, feel free to open an issue or submit a pull request.

1. **Fork the repository**
2. **Create a new branch**:
   ```sh
   git checkout -b feature/your-feature-name
   ```

3. **Commit your changes**:
   ```sh
   git commit -m 'Add some feature'
   ```

4. **Push to the branch**:
   ```sh
   git push origin feature/your-feature-name
   ```

5. **Open a pull request**
