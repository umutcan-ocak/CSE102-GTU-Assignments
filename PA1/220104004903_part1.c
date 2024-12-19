#include <stdio.h>

#define ALPHABET_SIZE 61

/*Define the size of the alphabet including letters, digits, and special characters*/

char alphabet[61] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
'(', '<', '=', '+', ')', '[', '*', '/', ']', '{', '>', '!', '-', '}', '?',
'\\', '&', '|', '%', '_', ';', '"', '#', '.', '\'', '0', '1', '2', '3', '4',
'5', '6', '7', '8', '9'};

/*Function to encrypt a character by shifting it in the alphabet*/

char Encrypt(char ch, int shift) {
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        if (ch == alphabet[i]) {
            return alphabet[(i + shift) % ALPHABET_SIZE];
        }
    }
    return ch;
}

/*Function to compute the sum of digits of a student ID and ensure it's a single digit*/

int sezar() {
    int sum = 0;
    long int studentID = 220104004903;
    
    /*Calculate the sum of digits*/
   
    while (studentID != 0) {
        sum += studentID % 10;
        studentID /= 10;
    }
    
    /*Ensure the sum is a single digit*/
     
     while (sum >= 10) {
        int tempSum = 0;
        while (sum != 0) {
            tempSum += sum % 10;
            sum /= 10;
        }
        sum = tempSum;
    }
    
    return sum;
}

int main() {
    char c;    
    int shiftA = sezar(); /*Calculate the shift amount based on the student ID*/
    int a1 = 0, a2 = 0, x = 0;
    int commentCount = 0; 
   
    /*Read characters from input*/
   
    while (scanf("%c", &c) == 1) {
        if (c == '/') {
            scanf("%c", &c);
            if (c == '*') {
                x = 1;
                commentCount++; /*Increment comment count when a comment starts*/
            }
        }
        if (x == 1) {
            if (c == '*') {
                scanf("%c", &c);
                if (c == '/') {
                    
                    x = 0;                   
                    
                    a1 = commentCount / 10;
                    a2 = commentCount % 10;                    
                    
                    char charA1 = '0' + a1;
                    char charA2 = '0' + a2;
                    
                    /*Print encrypted comment count*/
   		            
   		            printf("@ %c%c", Encrypt(charA1, shiftA), Encrypt(charA2, shiftA));
                }
            } else {
               
                if (c != ' '){ 
                    
                    commentCount++; /*Increment comment count for non-space characters within a comment*/
                }
            }
        } else {
            
            printf("%c", Encrypt(c, shiftA)); /*Encrypt and print non-comment characters*/
        }
    }
    
    return 0;
}

