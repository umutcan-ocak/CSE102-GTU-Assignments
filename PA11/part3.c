#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*Define constants*/
#define SUITS 4
#define FACES 13
#define DECK_SIZE (SUITS * FACES)

/*Structure card definition*/
struct card {
    const char *face;
    const char *suit;
};
/*Function shuffle shuffles the deck*/
void shuffle(struct card * const wDeck) {
    int i, j;
    struct card temp;
    for (i = 0; i < DECK_SIZE; i++) {
        j = rand() % DECK_SIZE;
        temp = wDeck[i];
        wDeck[i] = wDeck[j];
        wDeck[j] = temp;
    }
}
/*Function main begins program execution*/
int main() {
    /*Initialize arrays of pointers*/
    const char *suits[SUITS] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    const char *faces[FACES] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
    struct card deck[DECK_SIZE];
    int i;
    /*Initialize the deck*/
    for (i = 0; i < DECK_SIZE; i++) {
        deck[i].face = faces[i % FACES];
        deck[i].suit = suits[i / FACES];
    }

    /*Seed the random number generator*/
    srand(time(NULL));

    /*Shuffle the deck*/
    shuffle(deck);

    /*Print the shuffled deck*/
    for (i = 0; i < DECK_SIZE; i++) {
        printf("%5s of %-8s%s", deck[i].face, deck[i].suit, (i + 1) % 2 ? " " : "\n");
    }
    printf("\n");
    return 0;
}
