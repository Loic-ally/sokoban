# Pokokoban

Pokokoban is a themed version of the classic puzzle game Sokoban, where the player pushes Pokémon-themed boxes around a warehouse, trying to get them to storage locations. This implementation of Sokoban is written in C using CFSML.

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Gameplay](#gameplay)
- [Future Plans](#future-plans)
- [Contributing](#contributing)
- [License](#license)

## Installation

To install and run Pokokoban, follow these steps:

1. **Clone the repository**:
   ```sh
   git clone https://github.com/Loic-ally/sokoban.git
   cd sokoban
   ```

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
* **Z,S,Q,D**: Move the player up, down, left, or right
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
