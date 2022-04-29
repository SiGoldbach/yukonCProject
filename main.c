#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "GameLogic.h"
#include "GamrLogic2.h"

struct card {
    char type[2];
    int visible;
    struct card *next;

};
struct head {
    struct card *next;
};

void SI(int split, char *cardDeck);

void printBoard2(struct head *board);

void SD(char filename[], char *cardDeck);

void P(char *cardDeck, struct head *board);

void SR(char *cardDeck);

void LD(char cards[]);

void printArrArray(char cards[]);

void printBoard(struct head *board);

void QQ();

void headFiller(struct head board[]);

void boardFiller(struct head Board[], char cards[]);


int main() {

    char cards[104];
    char *cardsPointer = cards;

    LD(cardsPointer);

    // Different methods available.
    SR(cards);
    printf("\n");

    SD("cards.txt", cardsPointer);
    // printArrArray(cardsPointer);

    /* SI(5, cards);
      printf("\n");
    */
    struct head board[7];
    struct head *boardPoints = board;
    struct head aceField[4];
    struct head *aceFieldPointer = aceField;
    headFiller(aceFieldPointer);
    headFiller(boardPoints);


    P(cardsPointer, board);
    // prints board-method.
    printBoard(board);
    // Calls QQ (exit-method).
    return 0;
}

// loader vores kort fra filen.
void LD(char cards[]) {
    FILE *inStream;
    if (inStream == NULL) {
        printf("Nullpointer");
        inStream = fopen("KortTilSolitare.txt", "r");
    } else {
        inStream = fopen("cards.txt", "r");
    }
    char read[104];
    int counter = 0;
    while (!feof(inStream)) {
        fgets(read, 100, inStream);
        cards[counter] = read[0];
        cards[counter + 1] = read[1];
        counter = counter + 2;
    }
    fclose(inStream);
}

void printArrArray(char cards[]) {
    int cardPrintedNUm = 0;
    int rowsPrinted = 0;
    // prints out the first line containing the different
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    for (int j = 0; j < 104; ++j) {
        printf("%c", cards[j]);
        if (j % 2 != 0) {
            printf("\t");
            cardPrintedNUm++;
            if (cardPrintedNUm % 7 == 0) {
                rowsPrinted++;
                if (rowsPrinted % 2 != 0) {
                    printf("\t[]\tF%d", rowsPrinted / 2 + 1);
                }
                printf("\n");
            }
        }
    }
}

void printBoard(struct head *board) {
    // prints out the first line containing the different
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    struct card *cards[7];
    for (int i = 0; i < 7; ++i) {
        cards[i] = board[i].next;
    }

    for (int j = 0; j < 11; ++j) {

        for (int i = 0; i < 7; ++i) {
            if(cards[i] == NULL){
                printf("  \t");
            }else {

                if (cards[i]->visible == 0) {
                    printf("[]\t");
                } else {
                    printf("%c%c\t", cards[i]->type[0], cards[i]->type[1]);
                }

                cards[i] = cards[i]->next;
            }
        }
        if ( j == 0){
            printf("\t[]\tF1");
        }
        if ( j == 2) {
            printf("\t[]\tF2");
        }
        if ( j == 4) {
            printf("\t[]\tF3");
        }
        if (j == 6) {
            printf("\t[]\tF4");
        }
        printf("\n");

    }
}
/*
void printBoard2(struct head *board){
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    int length[7];
    for (int i = 0; i < 7; ++i) {
        int count=0;
        if (board->next!=NULL){
            struct card c1=*board->next;
            while (c1.next!=NULL){
                count++;
                c1=*c1.next;
            }
        }
    }
    for (int i = 0; i < 7; ++i) {
        printf("%c%c\t", length[7]);


    }


}
*/
// method to split card into smaller stacks and sort them back into one deck in order of 1 by 1 from each deck.
void SI(int split, char *cardDeck) {
    if (split > 52 || split < 0) {
        printf("you entered invalid card deck split-size\n");
        return;
    }
    char deck1[split * 2];
    char deck2[104 - split * 2];
    for (int i = 0; i < 104; i++) {
        if (i < split * 2) {
            deck1[i] = cardDeck[i];
        } else {
            deck2[i - split * 2] = cardDeck[i];
        }
    }
    int removedCardDeck1 = 0;
    int removedCardDeck2 = 0;
    for (int i = 0; i < 104; i += 2) {

        if ((i % 4 == 0 && removedCardDeck1 < split) || removedCardDeck2 >= (52 - split)) {
            cardDeck[i] = deck1[removedCardDeck1 * 2];
            cardDeck[i + 1] = deck1[removedCardDeck1 * 2 + 1];
            removedCardDeck1++;
        } else {
            cardDeck[i] = deck2[removedCardDeck2 * 2];
            cardDeck[i + 1] = deck2[removedCardDeck2 * 2 + 1];
            removedCardDeck2++;
        }
    }
}

void SR(char *cardDeck) {
    srand(time(NULL));
    for (int i = 0; i < 52; i++) {
        char cardToShuffle = cardDeck[i * 2];
        char cardToShuffle2 = cardDeck[i * 2 + 1];

        int randomCardLocation = (rand() % (i + 1)) * 2;
        char currentVal = cardDeck[randomCardLocation];
        char currentFaction = cardDeck[randomCardLocation + 1];
        char nextVal;
        char nextFaction;
        for (int j = randomCardLocation / 2; j < i; j++) {
            nextVal = cardDeck[j * 2 + 2];
            nextFaction = cardDeck[j * 2 + 3];
            cardDeck[j * 2 + 2] = currentVal;
            cardDeck[j * 2 + 3] = currentFaction;
            currentVal = nextVal;
            currentFaction = nextFaction;
        }
        cardDeck[randomCardLocation] = cardToShuffle;
        cardDeck[randomCardLocation + 1] = cardToShuffle2;

    }
}

// makes file named cards and prints the current deck.
void SD(char filename[], char *cardDeck) {
    FILE *f;
    if (strlen(filename) == 0) {
        f = fopen("cards.txt", "wb");
    } else {
        f = fopen(filename, "wb");
    }
    for (int i = 0; i < 104; i += 2) {
        fprintf(f, "%c", cardDeck[i]);
        fprintf(f, "%c\n", cardDeck[i + 1]);

    }
    fclose(f);
}

// Command to quit program
void QQ() {
    printf("\nWrite 'QQ' to exit the program \n");
    char a;
    char b;
    scanf("%c%c", &a, &b);
    if (a == 'Q' && b == 'Q') {
        exit(0);
    }
}

// Command to play the game
void P(char *cardDeck, struct head *board) {
    // måske skal det ikke være "struct card"
    struct card *c1 = malloc(sizeof(struct card));
    int cardCounter = 0;
    LD(cardDeck);
    headFiller(board);
    c1->type[0] = cardDeck[0];
    c1->type[1] = cardDeck[1];
    c1->visible = 1;
    c1->next = NULL;

    board[0].next = c1;
    cardCounter = 1;
    for (int i = 1; i < 7; ++i) {
        struct card **nextCard = &board[i].next;
        for (int j = 1; j < i + 6; ++j) {
            struct card *c2 = malloc(sizeof(struct card));
            c2->type[0] = cardDeck[cardCounter * 2];
            c2->type[1] = cardDeck[cardCounter * 2 + 1];
            c2->next = NULL;
            if (j < i + 1) {
                c2->visible = 0;
            } else {
                c2->visible = 1;
            }
            *nextCard = c2;
            nextCard = &c2->next;
            cardCounter++;
        }
    }
}

void headFiller(struct head board[]) {

    for (int i = 0; i < 7; ++i) {
        struct head h1;
        board[i] = h1;
    }
}

void boardFiller(struct head Board[], char cards[]) {
    int numberPnt = 0;
    int typePnt = 1;
    struct card c1;
    c1.type[0] = cards[numberPnt];
    c1.type[1] = cards[typePnt];
    c1.visible = 1;
    Board[0].next = &c1;
    for (int i = 0; i < 6; ++i) {
        numberPnt = numberPnt + 2;
        typePnt = typePnt + 2;
        struct card c2;
        c2.type[0] = cards[numberPnt];
        c2.type[1] = cards[typePnt];
        c2.visible = 0;
        Board[i + 1].next = &c2;


    }


}
