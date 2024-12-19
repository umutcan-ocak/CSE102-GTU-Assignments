#include <stdio.h>
/*Function prototypes*/
void readNews();
void menu();
void readedNews();
void magicNumbers();

/*Main function*/
void main() {
    menu();
}
/*Function to read news from files*/
void readNews() {
    FILE *fptr;
    FILE *fp;
    char read;
    int choice;
    /*Prompt user to choose a news to read*/
    printf("Which news do you want to read:");
    scanf("%d", &choice);
    /*Open the file containing the list of read news*/
    fptr = fopen("readed_news_id.txt", "r");

    /*Check if the chosen news has been read before*/
    while ((read = fgetc(fptr)) != EOF) {
        if (read == choice + '0') {
            /*If the news has been read, prompt the user if they want to read it again*/
            printf("This news is already read. Do you want to read it again? Yes(1) / No (0):");
            scanf("%d", &choice);
            if (choice == 0) {
                fclose(fptr);
                return;
            }
            break;
        }
    }
    fclose(fptr);
    /*Open the file corresponding to the chosen news for reading*/
    switch (choice) {
        case 1:
            fp = fopen("1.txt", "r");
            break;

        case 2:
            fp = fopen("2.txt", "r");
            break;

        case 3:
            fp = fopen("3.txt", "r");
            break;

        case 4:
            fp = fopen("4.txt", "r");
            break;

        default:
            printf("Invalid choice!\n");
            return;
    }
    /*Display the content of the chosen news*/
    if (fp == NULL) {
        printf("Error opening news file!\n");
        return;
    }

    while ((read = fgetc(fp)) != EOF) {
        printf("%c", read);
    }
    fclose(fp);
    int flag = 0; /*Flag to indicate if the chosen news has been read before*/
    
    /*Open the file containing the list of read news*/  
    fptr = fopen("readed_news_id.txt", "r");
    
    /*Check if the chosen news has been read before*/
    while ((read = fgetc(fptr)) != EOF) {
        if (read == choice + '0') {
            flag = 1; /*Set flag to 1 if the chosen news has been read before*/
            fclose(fptr);
            break;

        }
    }  
    /*If the chosen news has not been read before, update the list of read news*/
    if (flag != 1) {
        fptr = fopen("readed_news_id.txt", "a");
        fprintf(fptr, "%d. new is readed\n", choice);
        fclose(fptr); 
        
    }  
}
/*Function to display the menu and handle user inputs*/
void menu() {
    char menu;
    FILE *fpr;
    char c;
    do { 
        /*Display the menu options*/
        printf("\n###########Daily Press###########\n\n");
        printf("Today's news are listed for you : \n\n");
               
        fpr = fopen("1.txt", "r");
        printf("\nTitle of 1. news: ");
        while (fscanf(fpr, "%c", &c) && c != '\n') {
            printf("%c", c);
        }
        fclose(fpr);
             
        printf("\nTitle of 2. news: ");
        fpr = fopen("2.txt", "r");
        while(fscanf(fpr, "%c", &c) && c != '\n'){
            printf("%c", c);
        }
        fclose(fpr);
               
        printf("\nTitle of 3. news: ");
        fpr = fopen("3.txt", "r");
        while(fscanf(fpr, "%c", &c) && c != '\n'){
            printf("%c", c);
        }
        fclose(fpr);
              
        printf("\nTitle of 4. news: ");
        fpr = fopen("4.txt", "r");
        while(fscanf(fpr, "%c", &c) && c != '\n'){
            printf("%c", c);
        }
        fclose(fpr);
        
        printf("\nWhat do you want to do?\n");
        printf("a. Read a new\n");
        printf("b. List the readed news\n");
        printf("c. Get decrypted information from the news\n");
        scanf(" %c", &menu);
        
        /*Handle user inputs*/
        switch (menu) {
            case 'a':
                readNews();
                printf("\nDo you want to continue (y/n):");
                scanf(" %c", &menu);
                break;

            case 'b':
                readedNews();
                printf("\nDo you want to continue (y/n):");
                scanf(" %c", &menu);
                break;

            case 'c':
                magicNumbers();    
                printf("\nDo you want to continue (y/n):"); 
                scanf(" %c", &menu);          
                break;

            default:
                printf("Invalid choice\n");
                break;
        }
    } while (menu != 'n');
}
/*Function to display the list of read news*/
void readedNews() {
    FILE *fptr;
    char read;
    /*Open the file containing the list of read news*/
    fptr = fopen("readed_news_id.txt", "r");
    if (fptr == NULL) {
        printf("Error opening readed news file!\n");
        return;
    }
    
    int isEmpty = 1;
    /*Display the list of read news*/
    while ((read = fgetc(fptr)) != EOF) {
        printf("%c", read);
        isEmpty = 0;
    }
    fclose(fptr);
    if (isEmpty) {
        printf("There is no readed news yet.\n");
    }
}
/*Function to decrypt information from the news*/
void magicNumbers(){
    int number;
    double sum = 0;
    double magicNumber = 0; 
    int temp;
    char read;
    printf("Which news do you want to decrypt:");
    scanf("%d", &number);
    FILE *str;
    /*Open the file corresponding to the chosen news for decryption*/
    switch (number){
        case 1:
            str = fopen("1.txt", "r");
            break;
        case 2:
            str = fopen("2.txt", "r");
            break;
        case 3:
            str = fopen("3.txt", "r");
            break;
        case 4:
            str = fopen("4.txt", "r");
            break;
        default:
            printf("Invalid choice!\n");
            return;
    }
    /*Decrypt the information from the chosen news*/
    while ((read = fgetc(str)) != EOF) {
        if (read == '#') {
            if (fscanf(str, "%d", &temp) == 1) {
                sum = (temp * temp * temp) - (temp * temp) + 2;
                magicNumber += sum*sum;
                printf("#");
                printf("%d", temp);
            } 
            }  
            printf("%c", read);
        }   
    /*Display the decrypted information*/
    printf("\n\nThe decrypted information is: %.2lf\n", magicNumber);
    fclose(str);
}