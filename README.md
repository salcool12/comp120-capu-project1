# Project 1: Tic-Tac-Toe vs Computer

This is a tic-tac-toe game where you play against the computer. You are O and always go first, and the computer is X. The computer picks its moves randomly, so it's not very good, but it always makes a legal move. After each game you can play again or quit.

## How to compile and run

```
gcc -std=c11 -Wall -o tictactoe tictactoe.c
./tictactoe
```

## How to play

The squares are numbered 0 to 8:

```
 0 | 1 | 2
---+---+---
 3 | 4 | 5
---+---+---
 6 | 7 | 8
```

On your turn, type the number of an empty square. Empty squares show their number on the board so you can see which ones are left. You win by getting three O's in a row across, down, or diagonally. If the board fills up with no winner, it's a draw. At the end of a game, type y to play again or q to quit.

If you type a number outside 0-8, a square that's already taken, or something that isn't a number, the program tells you what was wrong and asks again.

## How the program works

The board is stored in `char board[9]`, with a space meaning an empty square. The program is split into small functions:

- `init_board` clears the board
- `display_board` prints the board, using a temporary array `c[9]` so empty squares show their numbers
- `is_winner` checks the 3 rows, 3 columns and 2 diagonals for three in a row
- `other_player` switches between O and X
- `get_human_move` keeps asking until the user enters a valid empty square
- `get_computer_move` picks random squares with `rand()` until it finds an empty one
- `take_turn` gets a move from the current player and puts it on the board
- `play_game` plays one full game
- `play_again` asks if the user wants another game

There are also a few small helpers: `is_empty`, `is_full` and `clear_input`. `clear_input` throws away the rest of the line after `scanf`, so if the user types something like `abc` it doesn't get stuck in the input and cause an endless loop.

The main loop in `play_game` is a `for` loop over the 9 possible turns. Each turn the current player moves, the board is shown, and if that player has won the game ends. Otherwise it switches to the other player. If all 9 turns go by without a winner, it's a draw.

I used `while` loops for input checking since they repeat until the input is valid, `do...while` for the computer's random pick and for the main game loop since both need to run at least once, and `for` loops for things that run a fixed number of times, like the turns and going through the board. True/false values like `game_over` and `valid` use `bool` from `stdbool.h`. `srand(time(NULL))` is called once at the start of `main` so every run plays differently.
ding READMEt.md…]()

