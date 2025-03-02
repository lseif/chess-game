## chess-game

A simple game of chess that two players can play against each other on the command line.

![chess-game_screenshot](https://github.com/user-attachments/assets/9731ac26-89d6-4ba5-a7b5-65c47964ea60)

## Installation
To build and run the game you need cmake version 3.51 or higher and c++ 17.
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
A player can move a piece by inputing it's coordinates. The game will than ask him to give the coordinates of the the field he wants the piece to move to. If the move is agaisnt the traditional chess rules the Player will be asked to do a different move.
The player with the red pieces begins. the game refers to him as white. The player with the red pieces is refered to as black.
 
## Issues
There currently no known Issues.

When you encounter other issues or have feature requests please open an issue.

## TODO
- improve unit tests, use CTests
- show the Pieces that got taken and show how many points of material a player is up or behind
- add GUI
