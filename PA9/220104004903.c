#include <stdio.h>
#include <string.h>

/*Define maximum number of flowers and maximum size of the map*/
#define MAX_NUM_FLOWER 100
#define MAX_SIZE_MAP 50 

/*Define a structure for the forest*/
typedef struct {
    char map[MAX_SIZE_MAP][MAX_SIZE_MAP]; /*Map of the forest*/
    int width, height; /*Width and height of the forest*/
    int flower_x[MAX_NUM_FLOWER];   /*X coordinates of the flowers*/
    int flower_y[MAX_NUM_FLOWER];  /*Y coordinates of the flowers*/
    int flower_count; /*Number of flowers in the forest*/
} Forest;

/*Define a structure for the botanist*/
typedef struct {
    int coord_x, coord_y; /*Coordinates of the botanist*/
    int number_of_bottles; /*Number of bottles the botanist has*/
    int collected_flowers; /*Number of flowers the botanist has collected*/
} Botanist;

/*Initialize the game*/
void init_game(Forest *forest, Botanist *botanist) {
    /*Open the file for reading*/
    FILE *file = fopen("init.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    /*Read the dimensions of the forest*/
    if (fscanf(file, "%d,%d", &forest->height, &forest->width) != 2) {
        printf("Error reading forest dimensions.\n");
        fclose(file);
        return;
    }
    
    /*Read the coordinates of the botanist and the number of bottles*/
    if (fscanf(file, "%d,%d,%d", &botanist->coord_x, &botanist->coord_y, &botanist->number_of_bottles) != 3) {
        printf("Error reading botanist information.\n");
        fclose(file);
        return;
    }
    
    /*Initialize the number of flowers to 0*/
    forest->flower_count = 0;

    fgetc(file);

    /*Read the map of the forest*/
    char input_line[MAX_SIZE_MAP * 2];
    int i, col;
    for (i = 0; i < forest->height; i++) {
        fgets(input_line, sizeof(input_line), file);

        col = 0;
        char *p;

        for (p = strtok(input_line, ",\n"); p != NULL && col < forest->width; p = strtok(NULL, ",\n")) {
            forest->map[i][col++] = *p;
            if (*p == 'X') { 
                /*If the current character is a flower ('X'), store its coordinates*/
                forest->flower_x[forest->flower_count] = i;
                forest->flower_y[forest->flower_count] = col - 1;
                forest->flower_count++;
            }
        }
    }

    fclose(file);
}

/*Search for flowers in the forest*/
void search(Forest *forest, Botanist *botanist, int x, int y) {
    /*Base case: If the coordinates are out of bounds, return*/
    if (x < 0 || x >= forest->height || y < 0 || y >= forest->width) {
        return;
    }
    /*If the current cell contains a flower, collect it*/
    if (forest->map[x][y] == 'X') {
        forest->map[x][y] = ' '; 
        botanist->collected_flowers++;
    }
    /*If the current cell is empty, mark it as visited and continue searching*/
    if (forest->map[x][y] == ' ') {
        forest->map[x][y] = 'B'; 
        search(forest, botanist, x - 1, y);
        search(forest, botanist, x + 1, y);
        search(forest, botanist, x, y - 1);
        search(forest, botanist, x, y + 1);
    }
}

/*Display the current state of the forest*/
void display_forest(Forest *forest, Botanist *botanist) {
    
    /*Display the number of collected flowers and the number of bottles left*/
    printf("Collected flowers: %d/%d\n", botanist->collected_flowers, forest->flower_count);
    printf("Not used bottle number: %d\n", botanist->number_of_bottles - botanist->collected_flowers);
    
    /*Display the botanist's coordinates and the forest map*/
    printf("Botanist coordinates: (%d,%d)\n", botanist->coord_x, botanist->coord_y);
    int i, j;

    for (i = 0; i < forest->height; i++) {
        for (j = 0; j < forest->width; j++) {
            if (i == botanist->coord_x && j == botanist->coord_y) {
                printf("B,");
            } else if (forest->map[i][j] == 'X') {
                printf("X,");
            } else if (forest->map[i][j] == 'T') {
                printf("T,");
            } else {
                printf(" ,");
            }
        }
        printf("\n");
    }
}
/*Function to save the final state of the forest to a file*/
void save_final_state(Forest *forest) {
    FILE *file = fopen("last.txt", "w");
    if (!file) {
        printf("Failed to open file for writing.\n");
        return;
    }
    /*Write the forest map to the file*/
    int i, j;
    for (i = 0; i < forest->height; i++) {
        for (j = 0; j < forest->width; j++) {
            if (j == forest->width - 1) {
                fprintf(file, "%c", forest->map[i][j]);
            } else {
                fprintf(file, "%c,", forest->map[i][j]);
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
/*Function to move the botanist within the forest*/
int move_botanist(Forest *forest, Botanist *botanist, char direction) {
    /*Calculate the new coordinates based on the direction*/
    int new_x = botanist->coord_x;
    int new_y = botanist->coord_y;

    switch (direction) {
        case 'r':
            new_y++;
            break;
        case 'l':
            new_y--;
            break;
        case 'u':
            new_x--;
            break;
        case 'd':
            new_x++;
            break;
        case 'q':
            printf("Quitting the game.\n");
            return -1;
        default:
            printf("Invalid direction. Please use 'r' (right), 'l' (left), 'u' (up), 'd' (down), or 'q' (quit).\n");
            return 0;
    }
    /*Check if the new coordinates are within bounds*/
    if (new_x < 0 || new_x >= forest->height || new_y < 0 || new_y >= forest->width) {
        printf("Warning: Out of bounds.\n");
        return 0;
    }
    /*Check if the new coordinates are on a tree or a flower*/
    if (forest->map[new_x][new_y] == 'T') {
        new_x = botanist->coord_x;
        new_y = botanist->coord_y;
        printf("Warning: Cannot move onto trees or flowers.\n");
        return 0;
    }
    /*If the new position contains a flower, collect it*/
    if(forest->map[new_x][new_y] == 'X'){
        botanist->collected_flowers++;
        forest->map[botanist->coord_x][botanist->coord_y] = ' ';
        botanist->coord_x = new_x;
        botanist->coord_y = new_y;
        forest->map[new_x][new_y] = 'B';
        return 0;
    }
    /*Move the botanist to the new position*/
    forest->map[botanist->coord_x][botanist->coord_y] = ' ';
    botanist->coord_x = new_x;
    botanist->coord_y = new_y;
    forest->map[new_x][new_y] = 'B';

    return 1;
}

/*Main function to run the game*/
int main() {
    /*Declare variables for the forest and the botanist*/
    Forest forest;
    Botanist botanist;
    init_game(&forest, &botanist);

    char direction;
    while (1) {
        /*Display the current state of the forest*/
        display_forest(&forest, &botanist);
        printf("Enter direction (r=right, l=left, u=up, d=down, q=quit): ");
        scanf(" %c", &direction);

        /*Move the botanist based on the input direction*/
        if (move_botanist(&forest, &botanist, direction) == -1) {
            break;
            /*If the user quits, exit the game loop*/
        }
        
        /*Search for flowers in the forest*/
        search(&forest, &botanist, botanist.coord_x, botanist.coord_y);
        
        /*If all flowers are collected, display a message and exit the game*/
        if (botanist.collected_flowers >= forest.flower_count) {
            display_forest(&forest, &botanist);
            printf("Botanist says: 'I've found it!' Collected flowers: %d/%d\n", botanist.collected_flowers, forest.flower_count);
            printf("Congratulations! You've collected all rare flowers. Exiting...\n");
            break;
        }
    }
    /*Save the final state of the forest to a file*/
    save_final_state(&forest);

    return 0;
}
