#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BOARD_SIZE 9

void init_board(char board[]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = ' ';
    }
}

void display_board(char board[]) {
    char c[BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == ' ') {
            c[i] = '0' + i;
        } else {
            c[i] = board[i];
        }
    }

    printf("\n");
    printf(" %c | %c | %c\n", c[0], c[1], c[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", c[3], c[4], c[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", c[6], c[7], c[8]);
    printf("\n");
}

bool is_empty(char board[], int square) {
    return board[square] == ' ';
}

bool is_full(char board[]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == ' ') {
            return false;
        }
    }
    return true;
}

bool is_winner(char board[], char p) {
    // check rows
    if (board[0] == p && board[1] == p && board[2] == p) return true;
    if (board[3] == p && board[4] == p && board[5] == p) return true;
    if (board[6] == p && board[7] == p && board[8] == p) return true;

    // check columns
    if (board[0] == p && board[3] == p && board[6] == p) return true;
    if (board[1] == p && board[4] == p && board[7] == p) return true;
    if (board[2] == p && board[5] == p && board[8] == p) return true;

    // check diagonals
    if (board[0] == p && board[4] == p && board[8] == p) return true;
    if (board[2] == p && board[4] == p && board[6] == p) return true;

    return false;
}

char other_player(char player) {
    if (player == 'O') {
        return 'X';
    }
    return 'O';
}

void clear_input(void) {
    while (getchar() != '\n');
}

int get_human_move(char board[]) {
    int square = -1;
    bool valid = false;

    while (!valid) {
        printf("Your turn (O). Enter a square number (0-8): ");
        int result = scanf("%d", &square);
        clear_input();

        if (result != 1) {
            printf("  That is not a number. Please enter a number from 0 to 8.\n");
        } else if (square < 0 || square > 8) {
            printf("  %d is not on the board. Please enter a number from 0 to 8.\n", square);
        } else if (!is_empty(board, square)) {
            printf("  That square is already taken. Choose an empty one.\n");
        } else {
            valid = true;
        }
    }

    return square;
}

int get_computer_move(char board[]) {
    int square;
    do {
        square = rand() % BOARD_SIZE;
    } while (!is_empty(board, square));

    return square;
}

void take_turn(char board[], char player) {
    int square;

    if (player == 'O') {
        square = get_human_move(board);
        board[square] = 'O';
    } else {
        printf("Computer (X) is thinking...\n");
        square = get_computer_move(board);
        board[square] = 'X';

        if (is_winner(board, 'X') || is_full(board)) {
            printf("Computer (X) chose square %d.\n", square);
        } else {
            printf("Computer (X) chose square %d. Your move next!\n", square);
        }
    }
}

void play_game(void) {
    char board[BOARD_SIZE];
    char player = 'O';
    bool game_over = false;

    init_board(board);
    display_board(board);

    for (int turn = 0; turn < BOARD_SIZE && !game_over; turn++) {
        take_turn(board, player);
        display_board(board);

        if (is_winner(board, player)) {
            game_over = true;
        } else {
            player = other_player(player);
        }
    }

    if (!game_over) {
        printf("It's a draw! Nobody got three in a row.\n");
    } else if (player == 'O') {
        printf("You (O) win! Congratulations!\n");
    } else {
        printf("The computer (X) wins. Better luck next time!\n");
    }
}

bool play_again(void) {
    char answer;
    bool valid = false;

    while (!valid) {
        printf("\nPlay again? Enter y to play again or q to quit: ");
        if (scanf(" %c", &answer) == EOF) {
            return false;
        }
        clear_input();

        if (answer == 'y' || answer == 'Y' || answer == 'q' || answer == 'Q') {
            valid = true;
        } else {
            printf("  Please enter y or q.\n");
        }
    }

    return (answer == 'y' || answer == 'Y');
}

int main(void) {
    srand(time(NULL));

    printf("=====================================\n");
    printf("        TIC-TAC-TOE vs COMPUTER\n");
    printf("=====================================\n");
    printf("You are O and you go first. The computer is X.\n");
    printf("On your turn, type the number of an empty square:\n");

    do {
        play_game();
    } while (play_again());

    printf("\nBye! See you next time.\n");
    return 0;
}

