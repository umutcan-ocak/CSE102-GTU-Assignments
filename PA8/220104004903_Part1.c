#include <stdio.h>
#include <string.h>

#define PEOPLE 24
#define MAX_VALUE_LENGTH 50

/*Function to print a person's information*/
void print_person(char name[], char surname[], int age, char branchs1[], char branchs2[]) {
    printf("%-20s %-20s %-8d %-20s %10s\n", name, surname, age, branchs1, branchs2);
}
/*unction to sort people by age and display their information*/
void sort_people_by_age(char names[PEOPLE][MAX_VALUE_LENGTH], char surnames[PEOPLE][MAX_VALUE_LENGTH], int ages[PEOPLE], char branchs1[PEOPLE][MAX_VALUE_LENGTH], char branchs2[PEOPLE][MAX_VALUE_LENGTH]){
    int i, j;
    /*Sorting people by age*/
    for (i = 0; i < PEOPLE - 1; i++){
        for (j = i + 1; j < PEOPLE; j++){

            if (ages[i] > ages[j]){
                /*Swapping ages*/
                int temp = ages[i];
                ages[i] = ages[j];
                ages[j] = temp;
                /*Swapping names*/
                char temp_name[MAX_VALUE_LENGTH];
                strcpy(temp_name, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], temp_name);
                /*Swapping surnames*/
                char temp_surname[MAX_VALUE_LENGTH];
                strcpy(temp_surname, surnames[i]);
                strcpy(surnames[i], surnames[j]);
                strcpy(surnames[j], temp_surname);
                char temp_branchs1[MAX_VALUE_LENGTH];
                /*Swapping branch 1*/
                strcpy(temp_branchs1, branchs1[i]);
                strcpy(branchs1[i], branchs1[j]);
                strcpy(branchs1[j], temp_branchs1);
                /*Swapping branch 2*/
                char temp_branchs2[MAX_VALUE_LENGTH];
                strcpy(temp_branchs2, branchs2[i]);
                strcpy(branchs2[i], branchs2[j]);
                strcpy(branchs2[j], temp_branchs2);
            }
        }
    }
    /*Printing sorted information*/
    printf("%-20s %-20s %-8s %-20s %-20s\n", "NAME", "SURNAME", "AGE",  "BRANCH1",  "BRANCH2");
    for(i = 0; i < PEOPLE; i++){
        /*Checking if branch2 is "0"*/
        if (strcmp(branchs2[i], "0") != 0) {
            print_person(names[i], surnames[i], ages[i], branchs1[i], branchs2[i]);
        } else {
            print_person(names[i], surnames[i], ages[i], branchs1[i], "");
        }
    }
}
/*Function to sort people by branch and display their information*/
void sort_people_by_branch(char names[PEOPLE][MAX_VALUE_LENGTH], char surnames[PEOPLE][MAX_VALUE_LENGTH], int ages[PEOPLE], char branchs1[PEOPLE][MAX_VALUE_LENGTH], char branchs2[PEOPLE][MAX_VALUE_LENGTH]){
    int i, j;
    /*Sorting people by branch*/
    for (i = 0; i < PEOPLE - 1; i++){
        for (j = i + 1; j < PEOPLE; j++){
            if (strcmp(branchs1[i], branchs1[j]) > 0 || (strcmp(branchs1[i], branchs1[j]) == 0 && ages[i] > ages[j])){
                /*Swapping ages*/
                int temp = ages[i];
                ages[i] = ages[j];
                ages[j] = temp;
                /*Swapping names*/
                char temp_name[MAX_VALUE_LENGTH];
                strcpy(temp_name, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], temp_name);
                /*Swapping surnames*/
                char temp_surname[MAX_VALUE_LENGTH];
                strcpy(temp_surname, surnames[i]);
                strcpy(surnames[i], surnames[j]);
                strcpy(surnames[j], temp_surname);
                /*Swapping branch 1*/
                char temp_branchs1[MAX_VALUE_LENGTH];
                strcpy(temp_branchs1, branchs1[i]);
                strcpy(branchs1[i], branchs1[j]);
                strcpy(branchs1[j], temp_branchs1);
                /*Swapping branch 2*/
                char temp_branchs2[MAX_VALUE_LENGTH];
                strcpy(temp_branchs2, branchs2[i]);
                strcpy(branchs2[i], branchs2[j]);
                strcpy(branchs2[j], temp_branchs2);
            }
        }
    }
    /*Printing sorted information*/
    printf("%-20s %-20s %-8s %-20s %-20s\n", "NAME", "SURNAME", "AGE", "BRANCH1", "BRANCH2");
    for(i = 0; i < PEOPLE; i++){
        /*Checking if branch2 is "0"*/
        if (strcmp(branchs2[i], "0") != 0) {
            print_person(names[i], surnames[i], ages[i], branchs1[i], branchs2[i]);
        } else {
            print_person(names[i], surnames[i], ages[i], branchs1[i], "");
        }
    }
}
/*Function to filter people by branch and display their information*/
void filter_people_by_branch(char names[PEOPLE][MAX_VALUE_LENGTH], char surnames[PEOPLE][MAX_VALUE_LENGTH], int ages[PEOPLE], char branchs1[PEOPLE][MAX_VALUE_LENGTH], char branchs2[PEOPLE][MAX_VALUE_LENGTH]){
    int i;
    printf("%-20s %-20s %-8s %-20s %-20s\n", "NAME", "SURNAME", "AGE", "BRANCH1", "BRANCH2");
    for(i = 0; i < PEOPLE; i++){
        /*Checking if branch2 is not "0" and if the branch contains "SCIENCE"*/
        if(strcmp(branchs2[i], "0") != 0 && (strstr(branchs1[i], "SCIENCE") != NULL || strstr(branchs2[i], "SCIENCE") != NULL)){
            print_person(names[i], surnames[i], ages[i], branchs1[i], branchs2[i]);
        } else if (strstr(branchs1[i], "SCIENCE") != NULL) {
            /*Printing person with only branch1 if branch2 is "0"*/
            print_person(names[i], surnames[i], ages[i], branchs1[i], "");
        }
    }
}
/*Function to filter people by profession and display their information*/
void filter_people_by_profession(char names[PEOPLE][MAX_VALUE_LENGTH], char surnames[PEOPLE][MAX_VALUE_LENGTH], int ages[PEOPLE], char branchs1[PEOPLE][MAX_VALUE_LENGTH], char branchs2[PEOPLE][MAX_VALUE_LENGTH]){
    int i;
    printf("%-20s %-20s %-8s %-20s %-20s\n", "NAME", "SURNAME", "AGE", "BRANCH1", "BRANCH2");
    for(i = 0; i < PEOPLE; i++){
        /*Checking if branch2 is not "0" and if it contains "COMPUTER SCIENCE" but not "MATHEMATICS"*/
        if(strcmp(branchs2[i], "0") != 0 && (strstr(branchs1[i], "COMPUTER SCIENCE") != NULL && strstr(branchs2[i], "MATHEMATICS") == NULL)){
            print_person(names[i], surnames[i], ages[i], branchs1[i], branchs2[i]);
        } else if (strstr(branchs1[i], "COMPUTER SCIENCE") != NULL && strstr(branchs2[i], "MATHEMATICS") == NULL) {
            /*Printing person with only branch1 if branch2 is "0"*/
            print_person(names[i], surnames[i], ages[i], branchs1[i], "");
        }
    }
}
/*Function to read data from a file*/
void read_data(char names[PEOPLE][MAX_VALUE_LENGTH], char surnames[PEOPLE][MAX_VALUE_LENGTH], int ages[PEOPLE], char branchs1[PEOPLE][MAX_VALUE_LENGTH], char branchs2[PEOPLE][MAX_VALUE_LENGTH]){
    FILE *file = fopen("input1.txt", "r");
    if(file == NULL){
        printf("File not found\n");
        return;
    }
    char line[100];
    int i;  
    for(i = 0; i < PEOPLE && fgets(line, sizeof(line), file) != NULL; i++){
        /*Initializing arrays for each person*/
        names[i][0] = '\0';
        surnames[i][0] = '\0';
        branchs1[i][0] = '\0';
        branchs2[i][0] = '\0';

        /*Parsing the line using comma as delimiter*/
        char *token = strtok(line, ",");
        if (token != NULL) {
            /*Copying name*/
            strcpy(names[i], token);
            token = strtok(NULL, ",");
            if (token != NULL) {
                /*Copying surname*/
                strcpy(surnames[i], token);
                token = strtok(NULL, ","); 
            }
        }
        if (token != NULL) {
            int age;
            /*Parsing age*/
            if (sscanf(token, "%d", &age) != 1) {
                printf("Invalid age: %s\n", token);
                continue;
            }
            ages[i] = age;
            token = strtok(NULL, ",");
        }
        int branchCount = 0;
        /*Parsing branch information*/
        while (token != NULL) {
            if (branchCount == 0) {
                strcat(branchs1[i], token);
                strcat(branchs1[i], ", ");
            } else if (branchCount == 1) {
                strcat(branchs2[i], token);
                strcat(branchs2[i], ", ");
            }
            token = strtok(NULL, ",");
            branchCount++;
        }
        /*Removing trailing comma and space*/
        if (strlen(branchs1[i]) > 0) {
            branchs1[i][strlen(branchs1[i]) - 2] = '\0';
        }
        if (strlen(branchs2[i]) > 0) {
            branchs2[i][strlen(branchs2[i]) - 2] = '\0';
        } else {
            strcpy(branchs2[i], "0");
        }
    }
    fclose(file); 
}

int main(){
    char names[PEOPLE][MAX_VALUE_LENGTH];
    char surnames[PEOPLE][MAX_VALUE_LENGTH];
    int ages[PEOPLE];
    char branchs1[PEOPLE][MAX_VALUE_LENGTH];
    char branchs2[PEOPLE][MAX_VALUE_LENGTH];
    /*Reading data from file*/
    read_data(names, surnames, ages, branchs1, branchs2);

    int choice;
    do {
        /*Displaying the main menu options*/
        printf("**Menu**\n");
        printf("1. Sort and display all individuals by age\n");
        printf("2. Sort and display individuals in the branch by age\n");
        printf("3. Show individuals with the branch 'SCIENCE'\n");
        printf("4. Show computer scientist who are not mathematicians\n");
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                sort_people_by_age(names, surnames, ages, branchs1, branchs2);
                break;
            case 2:
                sort_people_by_branch(names, surnames, ages, branchs1, branchs2);
                break;
            case 3:
                filter_people_by_branch(names, surnames, ages, branchs1, branchs2);
                break;
            case 4:
                filter_people_by_profession(names, surnames, ages, branchs1, branchs2);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while(choice != 5);  
    return 0;
}