#include <stdio.h>

void SI(int split, char *cardDeck);

int main() {
    FILE *inStream;
    inStream = fopen("C:\\Users\\vniel\\CLionProjects\\yukonCProject\\KortTilSolitare.txt", "r");
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
    SI(100, cards);
    printf("\n");

    int cardPrintedNUm = 0;
    int rowsPrinted = 0;
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

    fclose(inStream);

    return 0;
}

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
            cardDeck[i] = deck1[removedCardDeck1*2];
            cardDeck[i+1] = deck1[removedCardDeck1*2+1];
            removedCardDeck1++;
        } else {
            cardDeck[i] = deck2[removedCardDeck2*2];
            cardDeck[i+1] = deck2[removedCardDeck2*2+1];
            removedCardDeck2++;
        }
    }
}
