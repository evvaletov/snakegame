# CPPND: Capstone Snake Game

This is Eremey Valetov's Capstone project for the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). It is based on the Snake Game starter code provided by Udacity, which inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) StackOverflow post and set of responses.

The starter code was extended with a blob that randomly moves on the game board, and when the snake's head is inside the blob the score decreases. The game prompts the user to choose whether to play with the blob or without it. The update methods of the blob and the snake run in separate threads, and promises and futures are used to signal method completion. The extensions of the started code are detailed more specifically in the **Rubric Points Addressed** section below.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## File and Class Structure

* `main.h`: this is the entry point for the program, which, among other things, prompts the user to choose whether the blob will be used, sets the size of the game board, calls the game loop in class **Game**, and prints the game results at the end of the game.
* `game.h`, `game.cpp`: header and source file for class **Game**, which contains the game loop, the state of the game, methods to update the state of the game, and similar data and methods.
* `renderer.h`, `renderer.cpp`: header and source file for class **Renderer**, which is responsible for rendering the game to the screen using the SDL library.
* `controller.h`, `controller.cpp`: header and source file for class **Controller**, which is responsible for handling keyboard input using the SDL library.
* `character.h`, `character.cpp`: header and source file for class **Character**, which is the parent class for all characters (but not food) in the game.
* `blob.h`, `blob.cpp`: header and source file for class **Blob**, which represents the blob character in the game. The class **Blob** inherits from the character class **Character**.
* `snake.h`, `snake.cpp`: header and source file for class **Snake**, which represents the snake character in the game. The class **Snake** inherits from the character class **Character**.

## Expected Program Behavior

1. The program prompts the user in the terminal to choose whether to play with the blob or without it.
2. The game board starts rendering to a window. A snake moves around the game board, controlled by the arrow keys on the keyboard. Each time it eats a one-cell food object, its speed increases, and the score and the snake's length increase by one. New food is created each time a food object is eaten. If the blob is enabled, it appears as a 3x3 object moving randomly around the screen. If the snake's head is inside the blob, the score decreases.
3. When Ctrl-C is pressed in the terminal or the window with the game board is closed, the game ends, and the score and the final length of the snake are printed to the terminal.

## Rubric Points Addressed

1. **The project accepts user input and processes the input**. This rubric point is addressed in file `main.cpp` and is marked by the comment `FP.1`.
2. **Classes follow an appropriate inheritance hierarchy**. This rubric point is addressed in files `character.h`, `character.cpp`, `snake.h`, `snake.cpp`, `blob.h`, and `blob.cpp`. The classes **Snake** and **Blob** represent characters of the game and inherit from the class **Character**. The class inheritance is marked in files `snake.h` and `blob.h` by the comments `FP.2`.
3. **Derived class functions override virtual base class functions**. This rubric point is addressed in files `character.h`, `character.cpp`, `snake.h`, `snake.cpp`, `blob.h`, and `blob.cpp`. A number of common functions for character classes **Snake** and **Blob** are declared as pure virtual functions in class **Character** and are overridden in the child classes. The overriding functions are market in files `snake.h` and `blob.h` by the comments `FP.3`.
4. **Templates generalizes functions in the project**. A template `Renderer::to_string_with_precision` for outputting numbers with specified precision is used in the file `renderer.cpp` and is marked by the comment `FP.4`.
5. **The project uses multithreading**. The methods `Update()` of classes **Snake** and **Blob** are launched in threads from the class **Game** in `game.cpp`. This is marked by the comment `FP.5` in the file `game.cpp`.
6. **A promise and a future are used in the project**. The methods `Update()` of classes **Snake** and **Blob** use promises and futures to signal their completion to the class **Game**. This is marked by the comments `FP.6` in the file `game.cpp`.