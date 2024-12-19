#include <stdio.h>
#include <string.h>
#define MAX_COL_COUNT 100
#define MAX_ROW_COUNT 100

/*Function to search for pattern P1*/
void search_p1(char strs[][MAX_COL_COUNT], int num_rows, int matches[][2], int *num_matches) {
    
    const char *pattern = "***++++***++++***";
    int pattern_length = strlen(pattern);
    
    int i, j;
    /*Loop through each row of the text*/
    for (i = 0; i < num_rows; i++) {
        for (j = 0; j < MAX_COL_COUNT - pattern_length + 1; j++) {
            /*If a match is found, record its position in the matches array*/
            if (strncmp(&strs[i][j], pattern, pattern_length) == 0) {
                matches[*num_matches][0] = i+1;
                matches[*num_matches][1] = j+1;
                (*num_matches)++;
            }
        }
    }
    
}
/*Function to search for pattern P2*/
void search_p2(char strs[][MAX_COL_COUNT], int num_rows, int matches[][2], int *num_matches) {
    const char *pattern = "+*+*+";
    int pattern_length = strlen(pattern);
    int i, j;
    for (j = 0; j < MAX_COL_COUNT; j++) {
        for (i = 0; i < num_rows - pattern_length + 1; i++) {
            /*Check if the substring matches the pattern*/
            if (strncmp(&strs[i][j], pattern, pattern_length) == 0) {
                /*If a match is found, record its position in the matches array*/
                matches[*num_matches][0] = i+1;
                matches[*num_matches][1] = j+1;
                (*num_matches)++;
            }
        }
    }
    
}
/*Function to search for pattern P3 diagonally*/
void search_p3(char strs[][MAX_COL_COUNT], int num_rows, int matches[][2], int *num_matches) {
    const char *pattern = "+**+++****+++**+";
    int pattern_length = strlen(pattern);
    int i, j;

    /*Left to right diagonal search */ 
    for (i = 0; i < num_rows - pattern_length + 1; i++) {
        for (j = 0; j < MAX_COL_COUNT - pattern_length + 1; j++) {
            int k;
            for (k = 0; k < pattern_length; k++) {
                if (strs[i + k][j + k] != pattern[k]) {
                    break;
                }
            }
            /*If a match is found, record its position in the matches array*/
            if (k == pattern_length) {
                matches[*num_matches][0] = i+1;
                matches[*num_matches][1] = j+1;
                (*num_matches)++;
            }
        }
    }

    /*Right to left diagonal search */
    for (i = 0; i < num_rows - pattern_length + 1; i++) {
        for (j = MAX_COL_COUNT - 1; j >= pattern_length - 1; j--) {
            int k;
            for (k = 0; k < pattern_length; k++) {
                if (strs[i + k][j - k] != pattern[k]) {
                    break;
                }
            }
            if (k == pattern_length) {
                matches[*num_matches][0] = i+1;
                matches[*num_matches][1] = j - pattern_length + 3;
                (*num_matches)++;
            }
        }
    }
}

int main() {
    FILE *fptr;
    fptr = fopen("input2.txt", "r");
    /*Open the file for reading*/
    
    /*Check if the file was opened successfully*/
    if (fptr == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char str[MAX_COL_COUNT];
    char strs[MAX_ROW_COUNT][MAX_COL_COUNT];
    int num_rows = 0;

    /*Read lines from the file and store them in a 2D array*/
    while (fgets(str, MAX_COL_COUNT, fptr) != NULL && num_rows < MAX_ROW_COUNT) {
        sscanf(str, "%s", strs[num_rows]);
        num_rows++;
    }
    /*Close the file*/
    fclose(fptr);

    int matches[MAX_ROW_COUNT * MAX_COL_COUNT][2];
    int num_matches = 0;

    /*Search for patterns P1, P2, and P3 in the text*/
    search_p1(strs, num_rows, matches, &num_matches);  
    search_p2(strs, num_rows, matches, &num_matches);
    search_p3(strs, num_rows, matches, &num_matches); 
    
    int i;
    /*Print the matches found*/
    for (i = 0; i < num_matches; i++) {
        if (i < num_matches / 2) {
            printf("P1(%d, %d)\n", matches[i][0], matches[i][1]);
        } else if (i < num_matches / 2 * 2) {
            printf("P2(%d, %d)\n", matches[i][0], matches[i][1]);
        } else {
            printf("P3 @ (%d, %d)\n", matches[i][0], matches[i][1]);
        }
    }

    return 0;
}