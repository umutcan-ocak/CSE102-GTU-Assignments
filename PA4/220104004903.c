#include <stdio.h>
/* Function to find the first initial of a specific student */ 
char first_initial(FILE *id_file, int id) {
    int current_id = 0;
    char ch;
    while ((ch = fgetc(id_file)) != EOF) {
        /* Check if the character is a digit */
        if (ch >= '0' && ch <= '9') {
            current_id = current_id * 10 + (ch - '0');
        } else if (ch == ';') {
            if (current_id == id) {
                /* Check if the ID matches the provided ID */
                char first_initial = fgetc(id_file);

                /* Return the first initial */
                return first_initial;
            } else {
                /* Skip the rest of the line if the ID doesn't match */
                while ((ch = fgetc(id_file)) != EOF && ch != '\n') {}
                current_id = 0;
            }
        }
    }
    /* Return null character if the ID is not found */
    return '\0';
}
/*Function to find the last initial of a specific student*/

char last_initial(FILE *id_file, int id) {
    int current_id = 0;
    char ch, last_initial = '\0';
    
    /* Loop through the file until the end */
    while ((ch = fgetc(id_file)) != EOF) {
        if (ch >= '0' && ch <= '9') {
            current_id = current_id * 10 + (ch - '0');
        } else if (ch == ';') { /* Check for delimiter */
            if (current_id == id) {
                fgetc(id_file); /*Skip the first initial*/
                last_initial = fgetc(id_file);
                return last_initial;    /* Return the last initial */
            } else {
                while ((ch = fgetc(id_file)) != EOF && ch != '\n') {}
                current_id = 0;
                /* Reset the student ID */
            }
        }
    }
    return last_initial;
}
/*Function to get student IDs based on their first initial*/
int get_id_fi(FILE *id_fp, char initial_to_find) {
    int id = 0;
    char first_initial;
    int found = 0;

    FILE *output_file = fopen("text1.txt", "w");
    /*Open a file to store the output*/

    if (output_file == NULL) {
        printf("Unable to open the file.");
        return 0;
    }

    int ch;
    while ((ch = fgetc(id_fp)) != EOF) {
       /*Check if the character is a digit (part of the student ID)*/
        if (ch >= '0' && ch <= '9') {
            id = id * 10 + (ch - '0'); /*Build the student ID*/
        } else if (ch == ';') {
            first_initial = fgetc(id_fp);
            
            /*Check if the first initial matches the provided initial to find*/
            if (first_initial == initial_to_find) {
                
                /*Write the student ID and first initial to the output file*/
                fprintf(output_file, "Student ID: %d, First Initial: %c\n", id, first_initial);
                found = 1;
                /*Set the found flag to true*/
            }

            while ((ch = fgetc(id_fp)) != EOF && ch != '\n') {}
            id = 0;
            /*Reset the student ID for the next iteration*/
        }
    }

    fclose(output_file); /*Close the output file*/

    output_file = fopen("text1.txt", "r");
    if (output_file != NULL) {
        printf("Content of text1.txt:\n");
        /*Print the content of the output file character by character*/
        while ((ch = fgetc(output_file)) != EOF) {
            putchar(ch);
        }
        fclose(output_file);
    } else {
        printf("Unable to open text1.txt to print its content.\n");
    }

    return found;
}
/*Function to get student IDs based on their last initial*/
int get_id_li(FILE *id_fp, char last_initial) {
    int id = 0;
    char first_initial, initial;
    int found = 0; /*Flag to indicate if any matching records were found*/

    FILE *output_file = fopen("text2.txt", "w");

    if (output_file == NULL) {
        printf("Unable to open the file.");
        return 0;
        /*Return 0 if unable to open the output file*/
    }

    int ch;
    /*Read each line of the input file until the end*/
    while (fscanf(id_fp, "%d;%c;%c\n", &id, &first_initial, &initial) == 3) {
        if (initial == last_initial) {
            /*Check if the last initial matches the specified last initial*/
            fprintf(output_file, "Student with last initial '%c' has ID: %d\n", last_initial, id);
            found = 1;
        }
    }

    fclose(output_file);

    output_file = fopen("text2.txt", "r");
    /*Open the output file for reading*/

    if (output_file != NULL) {
        printf("Content of text2.txt:\n");
        /*Print the content of the output file*/
        while ((ch = fgetc(output_file)) != EOF) {
            putchar(ch);
        }
        fclose(output_file); /*Close the output file*/
    } else {
        printf("Unable to open text2.txt to print its content.\n");
    }

    return found;
    /*Return whether any matching records were found*/
}
/*Function to calculate the grade of a student based on their midterm and final scores*/
char calculate_grade(float midterm, float final, float midterm_avg, float final_avg) {
    if (midterm < 40 || final < 40 || (midterm < midterm_avg && final < final_avg)) {
        return 'F';
        /* Return 'F' for fail if either the midterm or final score is below 40 or both are below their respective averages */
    } else if (midterm >= 40 && midterm < midterm_avg && final < final_avg) {
        return 'D';
        /* Return 'D' for below average if midterm score is above or equal to 40, below the midterm average, and final score is below the final average */
    } else if (midterm >= 40 && midterm < midterm_avg && final >= final_avg) {
        return 'C';
        /* Return 'C' for satisfactory if midterm score is above or equal to 40, below the midterm average, and final score is above or equal to the final average */
    } else if (midterm >= midterm_avg && midterm < midterm_avg && final >= final_avg && (midterm + final) / 2.0 < 90) {
        return 'B';
        /* Return 'B' for above average if midterm score is above the midterm average, final score is above the final average, and the average of the two scores is below 90 */
    } else {
        return 'A';
        /* Return 'A' for excellent if both midterm and final scores are above 90 */
    }
}

/*Function to calculate the average grade of a student*/
float average_grade(const char *info_fp, int id) {
    FILE *file = fopen(info_fp, "r");

    if (file == NULL) {
        printf("Could not open file %s", info_fp);
        return -1;
    }

    int current_id = 0;
    int grade_sum = 0;
    int grade_count = 0;
    char ch;
    /* Loop through the file character by character */
    while ((ch = fgetc(file)) != EOF) {
        /* Check if the character is a digit */
        if (ch >= '0' && ch <= '9') {
                /* Convert character to integer and update current ID */
            current_id = current_id * 10 + (ch - '0');
        } else if (ch == ';') {
            /* Check if the current ID matches the given ID */
            if (current_id == id) {
                /* Read grades and calculate average */
                while ((ch = fgetc(file)) != EOF && ch != '\n') {
                    if (ch >= '0' && ch <= '9') {
                        /* Convert character to integer and update grade sum */
                        grade_sum += ch - '0';
                        grade_count++;
                    }
                }
                break;
                /* Exit loop after finding grades for the given ID */
            } 
            else {
                /* Skip to the next line if the current ID does not match */
                while ((ch = fgetc(file)) != EOF && ch != '\n') {}
                current_id = 0;
                /* Reset current ID */
            }
        }
    }

    fclose(file);

    /* If no grades were found, return -1 */
    if (grade_count == 0) {
        return -1;
    }
     /* Calculate and return the average grade */
    return (float)grade_sum / grade_count;
}
/*Function to print the pass/fail status for each student*/
void print_pass_fail(const char *info_fp) {
    /*Open the file containing student information*/
    FILE *file = fopen(info_fp, "r");
    
    /*Check if the file could be opened*/
    if (file == NULL) {
        printf("Could not open file %s", info_fp);
        return;
    }

    int id, midterm1, midterm2, final, course_id;
    float midterm_avg, final_avg;

    printf("Pass/Fail status for each student:\n");


    /*Iterate through each line of the file*/
    while (fscanf(file, "%d;%d;%d;%d;%d\n", &id, &midterm1, &midterm2, &final, &course_id) == 5 ||
           fscanf(file, "%d;%d;%d;%d\n", &id, &midterm1, &final, &course_id) == 4) {
        midterm_avg = (midterm1 + midterm2) / 2.0;
        final_avg = final;

        char grade;
        if (midterm_avg >= 0 && final_avg >= 0) {
            grade = calculate_grade(midterm1, final, midterm_avg, final_avg);
        } else {
            grade = 'N'; /*If grades are not available, set grade to 'N'*/
        }

        printf("Student ID: %d, Course ID: %d, ", id, course_id);
        if (grade == 'N') {
            printf("No grades available\n");
        } else {
            if (course_id == 108) {
                /*If the course ID is 108, print "PASSED"/"FAILED" accordingly*/
                printf("%s, Grade: %c\n", (grade != 'F') ? "PASSED" : "FAILED", grade);
            } else {
                printf("%s, Grade: %c\n", (grade != 'F') ? "PASSED" : "FAILED", grade);
            }
        }
    }

    fclose(file);
}

/*Function to calculate GPA for a given student*/
float calculate_gpa(const char *info_fp, int id) {
    FILE *file = fopen(info_fp, "r");
    if (file == NULL) {
        printf("Could not open file %s", info_fp);
        return -1;
    }

    int current_id, midterm1, midterm2, final, course_id;
    float total_grade_points = 0;

    while (fscanf(file, "%d;%d;%d;%d;%d\n", &current_id, &midterm1, &midterm2, &final, &course_id) == 5) {
        /* Check if the current student ID matches the given ID */
        if (current_id == id) {
            float midterm_avg = (midterm1 + midterm2) / 2.0;
            float final_avg = final;
            float average_grade = (midterm_avg + final_avg) / 2;
            char grade = calculate_grade(midterm_avg, final_avg, midterm_avg, final_avg);

            switch (grade) {
                case 'A':
                    total_grade_points = 4.0;
                    break;
                case 'B':
                    total_grade_points = 3.5;
                    break;
                case 'C':
                    total_grade_points = 3.0;
                    break;
                case 'D':
                    total_grade_points = 2.5;
                    break;
                case 'F':
                    total_grade_points = 1.0;
                    break;
            }
        }
    }

    fclose(file);

    /* If no grades were found, return -1 */
    if (total_grade_points == 0) {
        return -1;
    }

    /* Calculate GPA by dividing total grade points by grade count */
    return total_grade_points;
}
/*Function to print the result of a specific course*/
void print_course_result(const char *info_fp, int course_id) {
    int grade_count = 0;
   
    /*Open the file containing course information*/
    FILE *file = fopen(info_fp, "r");
    if (file == NULL) {
        printf("Could not open file %s", info_fp);
        return;
    }

    int current_id, midterm1, midterm2, final, current_course_id;
    float avg_grade;
    char grade;

    int total_students = 0, passed_students = 0, failed_students = 0;

    /*Iterate through each line of the file*/
    while (fscanf(file, "%d;%d;%d;%d;%d\n", &current_id, &midterm1, &midterm2, &final, &current_course_id) == 5) {
        
        /*Check if the course ID in the current line matches the specified course ID*/
        if (current_course_id == course_id) {
            total_students++; 
            /*Increment the total number of students taking the course*/

           
            /*Calculate the average grades*/
            float midterm_avg = (midterm1 + midterm2) / 2.0;
            float final_avg = final;
            float average_grade = (midterm_avg + final_avg) / 2;
            
            /*Determine the grade based on average grades*/
            char grade = calculate_grade(midterm_avg, final_avg, midterm_avg, final_avg);
            if (grade != 'F') {
                passed_students++;
            } else {
                failed_students++;
            }
        }
    }
    /*Print the result of the course*/
    if (course_id == 108) {
        printf("Course ID: %d\n", course_id);
        printf("Total Students: %d\n", total_students);
        printf("Passed Students: %d\n", passed_students);
        printf("Failed Students: %d\n", failed_students);
    } else {
        printf("Course ID %d not found.\n", course_id);
    }
    /*Close the file*/
    fclose(file);
}
/*Function to print the number of classes for a given instructor*/
void print_num_classes_for_instructor(const char *id_fp, int instructor_id) {
    /*Open the file containing instructor information*/
    FILE *id_file = fopen(id_fp, "r");
    if (id_file == NULL) {
        /*Check if the file could be opened*/
        printf("Could not open file %s\n", id_fp);
        return;
    }
    int id, num_classes, department_id;
    int found = 0; 
    /*Flag to indicate if the instructor was found*/

    while (fscanf(id_file, "%d;%d;%d\n", &id, &num_classes, &department_id) == 3) {
    /*Check if the current line corresponds to the given instructor ID*/
    if (id == instructor_id) {
        printf("Instructor ID: %d\n", instructor_id);
        printf("Number of classes: %d\n", num_classes);
        found = 1;
        /*Set the flag to indicate that the instructor was found*/
        break; 
        /*// Exit the loop since the instructor was found*/
    }

    }
    if (!found) {
        printf("Instructor with ID %d not found.\n", instructor_id);
    }

    fclose(id_file); /*Close the file*/
}

void print_course_id_for_student(const char *info_fp, int student_id) {
    FILE *file = fopen(info_fp, "r");
    if (file == NULL) {
        printf("Could not open file %s", info_fp);
        return;
    }

    int current_id, midterm1, midterm2, final, course_id;
    /*Print a header indicating the purpose of the output*/
    printf("Course IDs for student with ID %d:\n", student_id);

    while (fscanf(file, "%d;%d;%d;%d;%d\n", &current_id, &midterm1, &midterm2, &final, &course_id) == 5) {
       /*Check if the current line corresponds to the given student ID*/
        if (current_id == student_id) {
            /*Print the course ID for the student*/
            printf("Course ID: %d\n", course_id);
        }
    }

    fclose(file);
}
/*Main function*/
int main() {
    const char *id_fp = "second 1.txt"; /*File path for student information*/
    const char *info_fp = "first 1.txt"; /*File path for course and grade information*/
    /*User choice*/
    char choice;
    char initial_to_find;
    int student_id, course_id, instructor_id;

    do {
        printf("\nMenu:\n");
        printf("p: Print all the users pass or fail\n");
        printf("n: Print only the user with a specific first initial\n");
        printf("g: Calculate the GPA of a given student\n");
        printf("c: Print whether each user passed or failed the same class\n");
        printf("t: Print the number of classes for the instructor\n");
        printf("d: Print the department of all persons according to the role\n");
        printf("l: Print the course_id of a given student\n");
        printf("e: Quit the program\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'p':
            /*Print pass/fail status for all students*/
                print_pass_fail(info_fp);
                break;
            case 'n':
            /*Print students with a specific first initial*/
                printf("Enter a letter for the first initial: \n");
                scanf(" %c", &initial_to_find);
                FILE *id_file = fopen(id_fp, "r");
                if (id_file == NULL) {
                     printf("Could not open file %s\n", id_fp);
                    break;
                }
                    get_id_fi(id_file, initial_to_find);
                    fclose(id_file);
                    break;

            case 'g':
            /*Calculate and print the GPA of a given student*/
                printf("Enter student ID: ");
                scanf("%d", &student_id);
                printf("GPA of student %d: %.2f\n", student_id, calculate_gpa(info_fp, student_id));
                break;
            case 'c':
            /*Print pass/fail status for a given course*/
                printf("Enter course ID: \n");
                scanf("%d", &course_id);
                getchar(); /*Consume the newline character*/
                print_course_result(info_fp, course_id);
                break;
            case 't':
            /*Print the number of classes for a given instructor*/
                printf("Enter instructor ID: \n");
                scanf("%d", &instructor_id);
                print_num_classes_for_instructor(info_fp, instructor_id);
                break;
            case 'd':              
            /*Print the department of all persons according to role*/
                break;
            case 'l':
            /*Print the course ID for a given student*/
                printf("Enter student ID: \n");
                scanf("%d", &student_id);
                print_course_id_for_student(info_fp, student_id);
                break;
            case 'e':
            /*Exit the program*/
                printf("Exiting program.\n");
                break;
            default:
            /*Invalid choice, try again*/
                printf("Invalid choice. Please try again.\n");

        }
    } while (choice != 'e');
    /*Continue until 'e' is entered*/
    return 0;
}