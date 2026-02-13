# C-NIM-game-project
This is a NIM game created using C++ that player vs. computer interaction with multiple difficulties. The game includes feature that allow the user to save and extract a game.
The cpp file requires a local c++ compile environment


================================================================================
                            NIM COIN GAME
================================================================================

GAME DESCRIPTION
----------------
A C++ implementation of the classic NIM coin game with multiple difficulty 
levels, save/replay functionality, and customizable game settings.

NIM is a mathematical strategy game where players take turns removing coins 
from a pile. The game can be configured so that either taking the last coin 
wins or loses. Players compete against an AI opponent with varying difficulty 
levels.


FEATURES
--------

Game Modes:
  - Two win conditions: Last coin wins or last coin loses
  - Customizable settings:
      * Adjustable number of coins (starting pile)
      * Configurable maximum coins per turn
      * Choose who goes first (player or computer)

AI Difficulty Levels:
  1. Naive Version: Computer makes random moves
  2. Smart Version: Computer calculates and executes optimal moves when available
  3. Coach Version: Computer provides guidance and allows you to learn optimal 
     strategies
       - Shows when optimal moves exist
       - Allows you to retry your move
       - Lets you choose if the computer should play optimally or randomly

Additional Features:
  - Save Game: Save completed games to replay later
  - Replay Game: Load and watch previously saved games
  - File Name Validation: Ensures safe file names across different operating 
    systems
  - Move Recording: Complete game history with every move tracked


HOW TO PLAY
-----------

Starting the Game:
  1. Compile and run the program
  2. Use the menu to configure game settings
  3. Press 'G' to start the game
  4. Take turns with the computer removing coins
  5. Win or lose based on the configured win condition

Menu Options:
  W/L - Set win condition (last coin wins/loses)
  C   - Change number of coins
  T   - Change maximum coins per turn
  P   - Switch who goes first
  D   - Change AI difficulty level
  G   - Start the game
  R   - Replay a saved game
  Q   - Quit

Game Strategy:
  The game has mathematical optimal strategies based on the formula:
  - Last coin wins: Optimal move exists when coins % (max_take + 1) ≠ 0
  - Last coin loses: Optimal move exists when (coins - 1) % (max_take + 1) ≠ 0
  
  Use Coach mode to learn these strategies!


COMPILATION
-----------

Basic compilation:
  g++ -o nim_game main.cpp

With optimization:
  g++ -O2 -o nim_game main.cpp


REQUIREMENTS
------------
  - C++ compiler with C++11 support or later
  - Standard C++ libraries: iostream, cstdlib, fstream, string, vector


FILE STRUCTURE
--------------
  - main.cpp - Complete game implementation
  - *.txt    - Saved game files (created when you save games)


SAVE FILE FORMAT
----------------
Game saves store:
  - Game configuration (coins, max take, first player, win condition)
  - AI difficulty level
  - Complete move history
  - Game outcome


EXAMPLE GAMEPLAY
----------------

******************************
************ Menu ************
******************************
total coins: 12
maximum take: 3
the player go first
the player drawing the last coin loses

It's your turn! How many coins you wanna draw? 
> 2
10 left...

The computer took 1 coins...
9 left...


KNOWN LIMITATIONS
-----------------
  - File names limited to 200 characters
  - Cannot save games in progress (only completed games)
  - Single-player mode only (against AI)


FUTURE ENHANCEMENTS
-------------------
Potential improvements could include:
  - Multiplayer (human vs human) mode
  - Graphical user interface
  - More AI difficulty levels
  - Game statistics tracking
  - Undo/redo moves during gameplay


LICENSE
-------
This project is open source and available for educational purposes.


AUTHOR
------
Created as a learning project for C++ programming and game theory.

================================================================================
Enjoy the game and try to beat the smart AI!
================================================================================
