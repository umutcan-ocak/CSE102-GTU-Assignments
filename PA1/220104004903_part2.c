#include <stdio.h>

#define ALPHABET_SIZE 61

char alphabet[ALPHABET_SIZE] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '(', '<', '=', '+', ')', '[', '*', '/', ']', '{', '>', '!', '-', '}', '?', '\\', '&', '|', '%', '_', ';', '"', '#', '.', '\'', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

/*Function to decrypt a character given a shift value*/
char Decrypt(char ch, int shift) {
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        if (ch == alphabet[i]) {
            
            int index = (i - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
            return alphabet[index]; /*Return the decrypted character*/
        }
    }
    return ch; 
}


int sezar() {
    int key = 10, sum = 0;
    long int studentID = 220104004903;
    
    /*Calculate the sum of digits in the student ID*/
    while (studentID != 0){
        sum += studentID % 10;
        studentID /= 10;
    }

    while (sum >= 10){
        int tempSum = 0;
        while (sum != 0){
            tempSum += sum % 10;
            sum /= 10;
        }
        sum = tempSum;
    }
    
    key = sum; /*Set the key to the calculated sum*/
    return key; /*Return the key*/
}

int main() {
    char c, c1,c2;
    int shiftA = sezar(); /*Calculate the shift value using the sezar function*/
    
    /*Loop through each character from the input*/
    
    while (scanf("%c", &c) == 1) {
        
        if (c == '@') {
            
            scanf("%c", &c);
            
            if(c == ' '){ /*Check if the character after '@' is a space*/
               
                scanf("%c", &c1);
                scanf("%c", &c2); 
                
                printf("/*There is %c%c characters as comment.*/", Decrypt(c1, shiftA), Decrypt(c2, shiftA)); 
            }	
        } else {
            printf("%c", Decrypt(c, shiftA)); /*Decrypt and print the character*/
        }
    }

    return 0;
}

