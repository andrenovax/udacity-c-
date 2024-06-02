# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

## Snake vs Worm Game Description:

In this exciting game variation, the classic Snake competes against Worms for food. The game begins with a single worm, and the number of worms increases as the player's score rises.

## Gameplay Overview:

### Initial Setup:

The game starts with one worm on the grid.
For every 10 points the player scores, an additional worm is added to the grid.

### Worm Behavior:

Worms use the A* algorithm to navigate towards the food.
Worms grow and increase their speed each time they consume food, mirroring the snake's behavior.
Worms treat worms as obstacles, avoiding them in their pathfinding.

### Collision Rules:

Worm vs. Snake:

  Food Collision:
    If both the snake and a worm reach the food simultaneously, the snake takes priority and consumes the food.
  Worm Head vs. Snake Body:
    If a worm's head touches the snake's body (excluding the snake's head), the worm cuts the snake at the collision point, grows, and speeds up.
  Snake Head vs. Worm Body Ends:
    If the snake's head touches either end of a worm's body, the worm shrinks, but the snake remains unaffected.
  Snake Head vs. Worm Body Middle:
    If the snake's head collides with the middle of a worm's body, the worm splits into two separate worms.
  Snake Destroys Worm:
    If the snake consumes the last segment of a worm and the number of worms on the grid falls below the minimum, a new worm is added to the grid.

Worm vs. Worm:

    Worms avoid colliding with each other, treating other worms as obstacles.
    Worms do not take, bite or consume other worms' segments.

Special Movement Rules for Worms:

    If a worm has no valid path to the food, its tail will become its new head, allowing it to reverse direction.
    If no valid moves are possible, the worm will remain stationary and wait.


## Criteria

https://docs.google.com/spreadsheets/d/1D41HT7mS4rH06P8_BLK3JnGjhM6tEQp2w6YNlv9rUQw/edit#gid=0
