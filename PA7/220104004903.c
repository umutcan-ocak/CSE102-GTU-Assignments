#include <stdio.h>
#define N 12

void initializeGame(int n, int board[][7]) {
    int i, j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 6; j++) {
            board[i][j] = n;
        }
       
        board[i][6] = 0; /* Set the large cup of each player to 0 initially */
    }
}

void printBoard(int board[][7]) {
    int i;
    printf("+----+---+---+---+---+---+---+----+\n");
    printf("|    ");
    for (i = 0; i < 6; i++) {
        printf("|%2d ", board[1][5 - i]); /* Print the upper row of cups */
    }
    printf("|    |\n");
    printf("|%2d  +---+---+---+---+---+---+ %2d |\n", board[1][6], board[0][6]); /* Print the scores */
    printf("|    ");
    for (i = 0; i < 6; i++) {
        printf("|%2d ", board[0][i]); /* Print the lower row of cups */
    }
    printf("|    |\n");
    printf("+----+---+---+---+---+---+---+----+\n");
}

void move(int selected_cup, int board[][7], int player_turn) {
    int i;
    int stones_to_distribute = board[selected_cup / 7][selected_cup % 7];
    board[selected_cup / 7][selected_cup % 7] = 0; /* Remove stones from the selected cup */

    int current_cup = selected_cup;

    for (i = 0; i < stones_to_distribute; i++) {
        current_cup = (current_cup + 1) % 14; /* Move to the next cup */

        if (current_cup == 6 && selected_cup / 7 == 0) {
            board[0][6]++; /* Add a stone to the player's large cup */
        } else if (current_cup == 13 && selected_cup / 7 == 1) {
            board[1][6]++; /* Add a stone to the computer's large cup */
        } else {
            board[current_cup / 7][current_cup % 7]++; /* Distribute a stone to the current cup */
        }

        if (current_cup == 13) {
            current_cup = -1; /* Reset the current cup index if it reaches the end */
        } else if (current_cup == selected_cup) {
            current_cup = (current_cup + 1) % 14; /* Skip the selected cup */
        }
    }

    if (current_cup == 6 && player_turn == 1) {
        printf("The last stone lands in your large cup. You get another turn.\n");
        printBoard(board);
        int selected_cup_player;
        do {
            printf("Select a cup (1-6): ");
            scanf("%d", &selected_cup_player);
        } while (selected_cup_player < 1 || selected_cup_player > 6);
        selected_cup_player--;

        move(selected_cup_player, board, 1); /* Continue the turn */
        return; 
    }

    if (current_cup != 6 && board[current_cup / 7][current_cup % 7] == 1) {
        printf("The last stone lands in an empty cup. Computer takes the turn.\n");
        int max_stones_computer = 0;
        int selected_cup_computer = 0;
        for (i = 0; i < 6; i++) {
            if (board[1][i] > max_stones_computer) {
                max_stones_computer = board[1][i];
                selected_cup_computer = i;
            }
        }
        move(selected_cup_computer + 6, board, 0); /* Computer makes the move */
        return; 
    }
}
int gamePlay(int board[][7]) {
    int i;

    /* Main gameplay loop */
    while (1) {
        int empty_count_player = 0;
        int empty_count_computer = 0;

        /* Check if either player has emptied all cups on their side */
        for (i = 0; i < 6; i++) {
            if (board[1][i] == 0) empty_count_computer++;
            if (board[0][i] == 0) empty_count_player++;
        }

        /* If one player has emptied all cups, end the game loop */
        if (empty_count_player == 6 || empty_count_computer == 6) break;

        /* Player's turn */
        int selected_cup_player;
        printf("Your turn. Select a cup (1-6): ");
        scanf("%d", &selected_cup_player);
        selected_cup_player--;
        move(selected_cup_player, board, 1); /* Execute the player's move */
        printBoard(board); /* Print the updated board */

        /* Check again if either player has emptied all cups */
        empty_count_player = 0;
        empty_count_computer = 0;
        for (i = 0; i < 6; i++) {
            if (board[1][i] == 0) empty_count_computer++;
            if (board[0][i] == 0) empty_count_player++;
        }

        /* If one player has emptied all cups, end the game loop */
        if (empty_count_player == 6 || empty_count_computer == 6) break;

        /* Computer's turn */
        int max_stones_computer = 0;
        int selected_cup_computer = 0;
        for (i = 0; i < 6; i++) {
            /* 
             * Determine the cup with the most stones on the computer's side
             * as its move strategy.
             */
            if (board[1][i] > max_stones_computer) {
                max_stones_computer = board[1][i];
                selected_cup_computer = i;
            }
        }
        printf("Computer's turn: %d\n", selected_cup_computer + 1);
        move(selected_cup_computer + 7, board, 0); /* Execute the computer's move */
        printBoard(board); /* Print the updated board */
    }

    /* Calculate final scores */
    int score_player = 0, score_computer = 0;
    for (i = 0; i < 6; i++) {
        score_player += board[0][i];
        score_computer += board[1][i];
    }

    /* Display game over message and result */
    printf("Game over!\n");
    if (score_player > score_computer) {
        printf("Congratulations! You win!\n");
        return 1;
    } else if (score_player < score_computer) {
        printf("Sorry! You lose!\n");
        return 0;
    } else {
        printf("It's a tie!\n");
        return -1;
    }
}
int main() {
    int board[2][7];
    initializeGame(N / 6, board); /* Initialize the game board */
    printBoard(board); /* Print the initial board */
    gamePlay(board); /* Start the game */

    return 0;
}

