# chess-game

A simple game of chess that two players can play against each other on the command line.

![chess-game_screenshot](https://github.com/user-attachments/assets/9731ac26-89d6-4ba5-a7b5-65c47964ea60)

## Table Of Contents
  * [Installation](#installation)
    + [With Docker](#with-docker)
    + [Without Docker](#without-docker)
  * [How to play](#how-to-play)
  * [Issues](#issues)
  * [TODO](#todo)


## Installation

### With Docker
You can run the latest release with 
```bash
docker run -it ghcr.io/lseif/chess-game:latest
```

If you want to play with features that are pushed to the repository but not released yet, you can clone this repository and 
as super user or a different user in the docker group you can build the container with 
```bash
docker build -t chess-game <path-to-project-root-directory>
```
This might take a while. Afterwards you can run the game with 
```bash
docker run -it chess-game
```

### Without Docker
To build and run the game without docker you need cmake version 3.16 or higher and c++ 17.
After you have cloned the repository it's recommended to create a build directory where the cmake build files will be stored. In the projects root directory run:
```bash 
mkdir build
```
Generate the cmake build system inside the build directory:
```bash
cd build
cmake ..
```
Build the project with
```bash
cmake --build .
```
 On linux this should create an executable file inside the current directory named ```chess```. You can run it on linux with \
 ```./chess```. On Windows it`s created inside the generated Debug folder. Run it with ```start <path-to-file>/chess.exe```.

 ## How to play
A player can move a piece by inputing it's coordinates. The game will than ask him to give the coordinates of the field he wants the piece to move to. If the move is agaisnt the traditional chess rules the Player will be asked to do a different move.
The player with the red pieces begins. the game refers to him as white. The player with the green pieces is refered to as black. You can press `ctrl` + `d` to end the game.
 
## Issues
There currently no known Issues.

When you encounter other issues or have feature requests please open an issue.

## TODO
- improve unit tests
- show the Pieces that got taken and show how many points of material a player is up or behind
- add GUI
- make it possible to move pieces with algebraic chess notation
