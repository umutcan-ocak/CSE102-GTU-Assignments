#include <stdio.h>

/* Function to find the size of the array */
int find_size_of_array(int a, int b, int number_array[]) {
    int size = 0;
    while (number_array[size] != -1) {
        size++;
    }
    return size;
}

/* Function to draw the histogram */
void draw_histogram(int a, int b, int number_array[]) {
    int size = find_size_of_array(a, b, number_array);
    int freq[b - a + 1];
    int max_freq = 0;
    int i, j;

    /* Initialize frequency array */
    for (i = 0; i <= b - a; i++) {
        freq[i] = 0;
    }

    /* Count frequencies */
    for (i = 0; i < size; i++) {
        if (number_array[i] >= a && number_array[i] <= b) {
            freq[number_array[i] - a]++;
        }
    }

    /* Find maximum frequency */
    for (i = 0; i <= b - a; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
        }
    }

    /* Draw histogram */
    for (i = max_freq; i >= 1; i--) {
        for (j = a; j <= b; j++) {
            if (freq[j - a] >= i) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

/* Function to calculate the average */
float average(int a, int b, int number_array[]) {
    int size = find_size_of_array(a, b, number_array);
    int i, j;
    int sum = 0;
    int count = 0;
    float mean;

    /* Calculate sum and count */
    for (i = a; i <= b; i++) {
        for (j = 0; j < size; j++) {
            if (number_array[j] == i) {
                sum += i;
                count++;
            }
        }
    }

    /* Calculate mean */
    mean = (float) sum / count;
    printf("Average: %f\n", mean);
}

/*Function to calculate the mode */
void mode(int a, int b, int number_array[]) {
    int size = find_size_of_array(a, b, number_array);
    int i, j;
    int max = 0;
    int mode_count = 0;
    int mode_values[size];

    /* Find mode(s) */
    for (i = a; i <= b; i++) {
        int count = 0;
        for (j = 0; j < size; j++) {
            if (number_array[j] == i) {
                count++;
            }
        }
        if (count > max) {
            max = count;
            mode_count = 1;
            mode_values[0] = i;
        } else if (count == max) {
            mode_values[mode_count] = i;
            mode_count++;
        }
    }

    /* Print mode(s) */
    printf("Mode(s): ");
    for (i = 0; i < mode_count; i++) {
        printf("%d ", mode_values[i]);
    }
    printf("\n");
}

/* Function to calculate the median */
void median(int a, int b, int number_array[]) {
    int size = find_size_of_array(a, b, number_array);
    int i, j;
    int temp;

    /* Sort the array */
    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            if (number_array[i] > number_array[j]) {
                temp = number_array[i];
                number_array[i] = number_array[j];
                number_array[j] = temp;
            }
        }
    }

    float median_number = 0;
    if (size % 2 == 0) {
        median_number = (number_array[size / 2 - 1] + number_array[size / 2]) / 2.0;
    } else {
        median_number = number_array[size / 2];
    }

    printf("Median: %f\n", median_number);
}

int main() {
    /*Creating an array of 200 elements and initializing it with values.*/
    int number_array[200] = {58, 63, 62, 62, 62, 62, 63, 74, 80, 57, 73, 58, 70, 58, 69, 73, 57, 80, 85, 71, 83, 62, 58, 74, 66, 70, 63, 71, 85, 67, 70, 71, 63, 71, 62, 57, 58, 59, 74, 66, 56, 63, 73, 74, 71, 80, 80, 84, 69, 74,-1};
    int i, j;
    int a, b;
    int size;
    int choice;
    int adding[5];

    printf("Enter A and B values: ");
    scanf("%d %d", &a, &b);
    draw_histogram(a, b, number_array);

    printf("Would you like to add numbers?(1 for yes, 0 for no): ");
    scanf("%d", &choice);
    
    /*If the user doesn't want to add numbers, calculate average, mode, and median.*/
    if (choice == 0) {
        average(a, b, number_array);
        median(a, b, number_array);
        mode(a, b, number_array);
        
    } else {
        int count = 0;
        size = find_size_of_array(a, b, number_array);
        while (count < 5) {
            int number;
            scanf("\n%d", &number);
            /*Continue until the user enters -1.*/
            if (number == -1) {
                break;
            }
            /*Check if the entered number is between 50 and 200.*/
            if (number < 50 || number > 200) {
                printf("Warning: Number should be between 50 and 200.\n");
                continue;
            }
            /*Add the entered numbers to the adding array.*/
            adding[count] = number;
            count++;
        }
        /*Add the entered numbers to the number_array.*/
        for (j = 0; j < count; j++) {
            number_array[size++] = adding[j];
        }
        /*Draw the histogram with the added numbers.*/
        number_array[size] = -1;
        draw_histogram(a, b, number_array);
        average(a, b, number_array);       
        median(a, b, number_array);
        mode(a, b, number_array);
    }

    return 0;
}
