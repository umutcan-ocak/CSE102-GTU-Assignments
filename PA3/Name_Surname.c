#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 256 /* 16x16 board */
#define BOARD_DIM 16    
#define MID_INDEX 136 /* Center index on the board for the player */
#define ECTS_PER_COURSE 8
#define ECTS_FIRST_GRADE 32
#define ECTS_SECOND_GRADE 24
#define WALL_COUNT 2

int grade1[8] = {119,120,121,135,137,151,152,153};
int grade2[24] = {85,86,87,88,89,90,91,101,107,117,123,133,139,149,155,165,171,181,182,183,184,185,186,187};
char board[BOARD_SIZE]; /* The game board */
int playerPosition = MID_INDEX; /* Player's current position on the board */ 
int ects = 0; /* ECTS points the player has collected */
int c=0;
int d=0;

int innerWallStart[WALL_COUNT] = {6, 6}; /* Starting positions of the inner walls */ 
int innerWallEnd[WALL_COUNT] = {10, 10};  /* Ending positions of the inner walls */
int outerWallStart[WALL_COUNT] = {4, 4};  /* Starting positions of the outer walls */
int outerWallEnd[WALL_COUNT] = {12, 12};  /* Ending positions of the outer walls */

void initialize_game() {
    int k,i,j;
    /* Fill the board with empty spaces */

    for (i = 0; i < BOARD_SIZE; i++) {
        board[i] = '.';
    }

    /* Place walls in two concentric squares */
    for (k = 0; k < WALL_COUNT; k++) {
        for (i = outerWallStart[k]; i <= outerWallEnd[k]; i++) {
            for (j = outerWallStart[k]; j <= outerWallEnd[k]; j++) {
                /* Create the outer wall */
                if ((i == outerWallStart[k] || i == outerWallEnd[k]) || (j == outerWallStart[k] || j == outerWallEnd[k])) {
                    board[i * BOARD_DIM + j] = '#';
                }
            }
        }

        for (i = innerWallStart[k]; i <= innerWallEnd[k]; i++) {
            for (j = innerWallStart[k]; j <= innerWallEnd[k]; j++) {
                /* Create the inner wall */
                if ((i == innerWallStart[k] || i == innerWallEnd[k]) || (j == innerWallStart[k] || j == innerWallEnd[k])) {
                    board[i * BOARD_DIM + j] = '#';
                }
            }
        }
    }
    /* Place the player at the center */
    board[MID_INDEX] = 'P';

    /* Randomly place the '1' and '2' objects */
    srand(time(0));
    for (i=0; i < 4; i++) {
        int pos;
        
        pos = rand() % 8;

        if(grade1[pos]>0)
            board[grade1[pos]] = '1';
        else
            i--;

        grade1[pos] = 0;
    }

    for (i = 0; i < 3; i++) {
        int pos;
        
        pos = rand() % 24;
        
        if(grade2[pos]>0)
            board[grade2[pos]] = '2';
        else
            i--;
        
        grade2[pos] = 0;
    }

    /* Place the target at the bottom right corner */
    board[BOARD_SIZE - 1] = 'X';
}

void print_board() {
    int i;
    printf("Use W (Up), A (Left), S (Down), D (Right) to move.\n");	
    for (i = 0; i < BOARD_SIZE; i++) {
        printf("%c ", board[i]);
        if ((i + 1) % BOARD_DIM == 0) {
            printf("\n");
        }
    }
    printf("\nTotal ECTS: %d\n", ects); /* Display total ECTS collected */
}

int can_pass_wall1(int nextIndex) {
    int k,i,j;   
     for (k = 0; k < WALL_COUNT; k++) {
         for (i = innerWallStart[k]; i <= innerWallEnd[k]; i++) {
             for (j = innerWallStart[k]; j <= innerWallEnd[k]; j++) {
 
                 if ((i == innerWallStart[k] || i == innerWallEnd[k]) || (j == innerWallStart[k] || j == innerWallEnd[k])) {
                     if((i * BOARD_DIM + j)==nextIndex)
                         return 0;
                 }
             }
         }
        
        }
        for (k = 0; k < WALL_COUNT; k++) {
            for (i = outerWallStart[k]; i <= outerWallEnd[k]; i++) {
                for (j = outerWallStart[k]; j <= outerWallEnd[k]; j++) {

                    if ((i == outerWallStart[k] || i == outerWallEnd[k]) || (j == outerWallStart[k] || j == outerWallEnd[k])) {
                        if((i * BOARD_DIM + j)==nextIndex)
                            return 0;
                    }
                }
            }
        }
    
    return 1; 
}
int can_pass_wall(int nextIndex) {
    int k,i,j;
    /* Logic to determine if a wall can be passed */
    if (ects < ECTS_FIRST_GRADE) {
     for (k = 0; k < WALL_COUNT; k++) {
         for (i = innerWallStart[k]; i <= innerWallEnd[k]; i++) {
             for (j = innerWallStart[k]; j <= innerWallEnd[k]; j++) {
                 /* Create the inner wall */
                 if ((i == innerWallStart[k] || i == innerWallEnd[k]) || (j == innerWallStart[k] || j == innerWallEnd[k])) {
                     if((i * BOARD_DIM + j)==nextIndex)
                         return 0;
                 }
             }
         }
        
        }
        
    }
    if (ects < (ECTS_FIRST_GRADE + ECTS_SECOND_GRADE)) {
        for (k = 0; k < WALL_COUNT; k++) {
            for (i = outerWallStart[k]; i <= outerWallEnd[k]; i++) {
                for (j = outerWallStart[k]; j <= outerWallEnd[k]; j++) {
                    /* Create the outer wall */
                    if ((i == outerWallStart[k] || i == outerWallEnd[k]) || (j == outerWallStart[k] || j == outerWallEnd[k])) {
                        if((i * BOARD_DIM + j)==nextIndex)
                            return 0;
                    }
                }
            }
        }
    }
    return 1; /* Can pass */
}


void move_player(char direction) {
    int playerX = playerPosition / BOARD_DIM;
    int playerY = playerPosition % BOARD_DIM;
    int newX = playerX, newY = playerY;

    /* Determine new position based on direction */
        switch (direction) {
        case 'w':
        case 'W':
            newX--; break;
        case 's':
        case 'S':
            newX++; break;
        case 'a':
        case 'A':
            newY--; break;
        case 'd':
        case 'D':
            newY++; break;
    }

    /* Calculate new index and prevent moving out of bounds */
    int newIndex = newX * BOARD_DIM + newY;
    if (newIndex < 0 || newIndex >= BOARD_SIZE) return;

    /* Check if it's a wall and if player can pass */
    if (board[newIndex] == '#' && !can_pass_wall(newIndex)) {
        printf("Not enough ECTS to pass the wall.\n");
        return;
    }
    
    if (board[newIndex] == '#' && can_pass_wall1(playerPosition)){
        c=1;
        
            playerPosition = newIndex;
            board[playerPosition] = 'P';
            if(direction=='a')
                board[playerPosition+1] = '.';
            else if(direction =='d')
                board[playerPosition-1] = '.';
            else if(direction=='w' )
                board[playerPosition+16] = '.';
            else if(direction =='s')
                board[playerPosition-16] = '.';
        
        
    }
    if ( board[newIndex] == '#') {
        board[playerPosition]='#';
        playerPosition = newIndex;
        board[playerPosition] = 'P';
    }
      
    /* Move the player if the new position is not a wall or is passable */
    else if (board[newIndex] == '.' || board[newIndex] == 'X') {
        if(c==1){
            board[playerPosition]='#';
            playerPosition = newIndex;
            board[playerPosition] = 'P';
            d=1;
            c=0;
        }
        else{
            board[playerPosition] = '.';
            playerPosition = newIndex;
            board[playerPosition] = 'P';
        }
    } else if (board[newIndex] == '1') {
        ects += ECTS_PER_COURSE; /* Increase ECTS */
        board[playerPosition] = '.';
        playerPosition = newIndex;
        board[playerPosition] = 'P';
    } else if (board[newIndex] == '2' && ects >= ECTS_FIRST_GRADE) {
        ects += ECTS_PER_COURSE; /* Increase ECTS */
        board[playerPosition] = '.';
        playerPosition = newIndex;
        board[playerPosition] = 'P';
    }
}

int main() {
    char direction;
    int step_counter = 0;
    initialize_game(); 

    do {
        print_board();
        printf("Enter your move: ");
        scanf(" %c", &direction);
        move_player(direction);
        step_counter++;

        if (playerPosition == 255) {           
            printf("\nCongratulations! You've reached the target and completed the game!\n");
            printf("Total number of moves: %d \n", step_counter);
            break;
        }
    } while (1);   
    return 0;

}
