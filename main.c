#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#include "time.h"
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

void SD(char filename[], char *cardDeck);

void P(char filename[], char *cardDeck);

void SR(char *cardDeck);

void printArrArray(char cards[]);

void QQ();

void headFiller(struct head board[]);


int main() {
    FILE *inStream;
    inStream = fopen("KortTilSolitare.txt", "r");
    if (inStream == NULL)
        printf("Nullpointer");
    char read[104];
    char cards[104];
    int counter = 0;
    while (!feof(inStream)) {
        fgets(read, 100, inStream);
        cards[counter] = read[0];
        cards[counter + 1] = read[1];
        counter = counter + 2;

    }
    // Different methods available.
    SR(cards);
    printf("\n");

    SD("cards.txt", cards);
    printArrArray(cards);

    /* SI(5, cards);
      printf("\n");
    */
    struct head board[7];
    struct head *boardPoints = board;
    struct head aceField[4];
    struct head *aceFieldPointer = aceField;
    headFiller(aceFieldPointer);
    headFiller(boardPoints);
    struct card c1;
    c1.type[0] = 'A';
    c1.type[1] = 'C';
    board[0].next = &c1;
    //struct card *c1pointer;
    //c1pointer=&c1;
    printf("\n");
    printf("%c%c", board[0].next->type[0], board[0].next->type[1]);


    fclose(inStream);

    // Calls exit-method.
    //
    QQ();
    //
    return 0;
}

void printArrArray(char cards[]) {
    int cardPrintedNUm = 0;
    int rowsPrinted = 0;
    // prints out the first line containing the different
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    for (int j = 0; j <= 104; ++j) {
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
    fputs("Current card deck\n", f);
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
void P(char filename[], char *cardDeck) {
    FILE *f;
    if (strlen(filename) == 0) {
        f = fopen("cards.txt", "r");
    } else {
        f = fopen(filename, "r");
    }
    printf("\n Write 'P' to play the game\n");
    char c;
    scanf("%c", &P);
    if (c == 'P') {
        for (int i = 0; i < 104; i += 2) {
            fprintf(f, "%c", cardDeck[i]);
            fprintf(f, "%c\n", cardDeck[i + 1]);
        }
        fclose(f);
    }
}

void headFiller(struct head board[]) {

    for (int i = 0; i < 7; ++i) {
        struct head h1;
        board[i] = h1;
    }
}