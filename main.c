#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

void SIRandom(char *cardDeck);

void QQ2();

void SD(char filename[], char *cardDeck);

void P(char *cardDeck, struct head *board);

void SR(char *cardDeck);

int LD(char cards[], char name[]);

void printArrArray(char cards[]);

void printBoard(struct head *board);

void QQ();

void Q();

void headFiller(struct head board[]);

int calculateLongestRowOfCards(struct head board[]);

int move(struct head board[], const char card[], int startRow, int tooRow);

int moveWholeRow(struct head board[], int startRow, int tooRow);

int moveKingToEmptyRow(struct head board[], char const card[], int startRow, int tooRow);

int commandBeforeGameHub();

void welcomeText();

void playGameWelcomeText();

void playGame(struct head *board, struct head *aceSpace);

/**
 * We are here defining a correct what a deck should hold with to chararray in look only fashion;
 */
char types[4] = {'C', 'D', 'H', 'S'};
char values[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K'};


int main() {
    commandBeforeGameHub();


}


int commandBeforeGameHub() {
    char cards[104];
    char *cardsPointer = cards;
    struct head board[7];
    struct head *boardPoints = board;
    struct head aceField[4];
    struct head *aceFieldPointer = aceField;
    headFiller(aceFieldPointer);
    headFiller(boardPoints);
    char command[50];
    char lastCommand[50];
    int printLast = 0;
    int activeDeckBoolean = 0;
    welcomeText();
    while (1) {
        printf("LAST Command: ");
        if (printLast) {
            printf("%s\n", lastCommand);
        } else {
            printf("\n");
        }
        printf("Message: OK\n");
        printf("INPUT >");
        scanf("%s", command);
        if (strlen(command) == 2) {
            if (command[0] == 'L' && command[1] == 'D') {
                if (LD(cardsPointer, "")) {
                    activeDeckBoolean = 1;
                } else {
                    printf("Cant load deck properly");
                }

            } else if (command[0] == 'S' && command[1] == 'W') {
                if (activeDeckBoolean)
                    printArrArray(cards);
                else
                    printf("No active deck ");
            } else if (command[0] == 'Q' && command[1] == 'Q') {
                QQ2();
            } else if (command[0] == 'S' && command[1] == 'R') {
                if (activeDeckBoolean) {
                    SR(cardsPointer);
                } else {
                    printf("No active card deck");
                }
            } else if (command[0] == 'S' && command[1] == 'D') {
                if (activeDeckBoolean) {
                    SD("", cardsPointer);
                } else {
                    printf("There is no deck to save.");
                }
            } else if ((command[0] == 'S' && command[1] == 'I')) {
                SIRandom(cardsPointer);
            }

            if (command[0] == '#')
                break;

        } else if (command[0] == 'S' && command[1] == 'I') {
            switch (strlen(command)) {
                case 4:
                    SR(cardsPointer);
                    break;
                case 5:
                    SI(command[4] - 48, cardsPointer);
                    break;
                case 6:
                    printf("");
                    int big = (command[4] - 48) * 10;
                    int small = command[5] - 48;
                    SI(big + small, cardsPointer);

                    break;
                default:
                    printf("You entered a number that is definitely to high or in a weird format");
                    break;
            }

        } else if (command[0] == 'S' && command[1] == 'D') {
            if (!activeDeckBoolean) {
                printf("There is no active card deck");

            } else {
                char fileName[50];
                int start = 3;
                for (int i = 0; i < strlen(command) - 4; ++i) {
                    fileName[i] = command[start];
                    start++;
                }
                printf("%s", fileName);
                SD(fileName, cardsPointer);
            }
        } else if (command[0] == 'L' && command[1] == 'D') {
            char fileName[50];
            int start = 3;
            for (int i = 0; i < strlen(command) - 4; ++i) {
                fileName[i] = command[start];
                start++;
            }
            printf("%s", fileName);
            LD(cardsPointer, fileName);


        } else if (command[0] == 'P') {
            if (activeDeckBoolean) {
                P(cardsPointer, board);
                printf("P works");
                playGameWelcomeText();
                playGame(board, aceField);

            } else
                printf("No deck loaded");
        }
        strcpy(lastCommand, command);
        printLast = 1;


        printf("\n");


    }

    LD(cardsPointer, NULL);

    // Different methods available.
    SR(cards);
    printf("\n");

    SD("cards.txt", cardsPointer);
    // printArrArray(cardsPointer);

    /* SI(5, cards);
      printf("\n");
    */




    P(cardsPointer, board);
    // prints board-method.
    printBoard(board);
    move(board, "KH", 5, 0);
    printBoard(board);
    moveWholeRow(board, 0, 6);
    printBoard(board);
    moveKingToEmptyRow(board, "KS", 6, 0);
    printBoard(board);
    printf("\n");



    // Calls QQ (exit-method).
    return 0;


}

void playGame(struct head *board, struct head *aceSpace) {
    printBoard(board);
    int printLast = 0;
    char command[50];
    char lastCommand[50];
    welcomeText();
    while (1) {
        printf("LAST Command: ");
        if (printLast) {
            printf("%s\n", lastCommand);
        } else {
            printf("\n");
        }
        printf("Message: OK\n");
        printf("INPUT >");
        scanf("%s", command);
        strcpy(lastCommand, command);
        if (strlen(command) == 1) {
            if (command[0] == 'Q') {

            } else if (command[0] == '#') {
                break;
            }
        }
        printLast = 1;
    }


}


/**
 * Loading cards from a specified file, if you do not want a specified file,
 * If you do not want a specified file call with string "";
 * @param cards
 * @param name
 * @return
 */
int LD(char cards[], char name[]) {
    FILE *inStream;
    if (strlen(name) != 0) {
        printf("Loading custom file\n");
        inStream = fopen(name, "r");
    } else {
        printf("Loading standard deck\n");
        inStream = fopen("KortTilSolitare.txt", "r");
    }
    if (inStream == NULL) {
        printf("cmake-build-debug/KortTilSolitare.txt\n");
        return 0;
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
    return 1;
}

/**
 * This is the print method we use while not playing the game. which just takes a char array.
 * No reason to allocate memory and put into linked lists before the game starts.
 * The reader is maybe going to disagree with this...
 * @param cards
 */
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

/**
 * This method is used to print the baord after the game has been started.
 * @param board
 */
void printBoard(struct head *board) {

    // prints out the first line containing the different
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    struct card *cards[7];
    for (int i = 0; i < 7; ++i) {
        cards[i] = board[i].next;
    }

    for (int j = 0; j < calculateLongestRowOfCards(board); ++j) {

        for (int i = 0; i < 7; ++i) {
            if (cards[i] == NULL) {
                printf("  \t");
            } else {

                if (cards[i]->visible == 0) {
                    printf("[]\t");
                } else {
                    printf("%c%c\t", cards[i]->type[0], cards[i]->type[1]);
                }

                cards[i] = cards[i]->next;
            }
        }
        if (j % 2 == 0 && j <= 6) {
            printf("\t[]\tF%d", j / 2 + 1);
        }

        printf("\n");

    }
}

/**
 * method to split card into smaller stacks and sort them back into one deck in order of 1 by 1 from each deck.
 */
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

/**
 * Generates a random number and then calling SI
 * @param cardDeck
 */
void SIRandom(char *cardDeck) {
    SI(rand() % 51, cardDeck);
}

/**
 * This shuffles the deck in a random order
 * @param cardDeck
 */
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

/**
 * Print the deck to a specified file.
 * It is possible to write to a default file called cards.txt if you call with an empty string.
 * @param filename
 * @param cardDeck
 */
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

/**
 * Exits program
 */
void QQ2() {
    exit(0);
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

/**
 * Command that allocates memory to the 52 cards and puts them into linked lists.
 * @param cardDeck
 * @param board
 */
void P(char *cardDeck, struct head *board) {
    // måske skal det ikke være "struct card"
    struct card *c1 = malloc(sizeof(struct card));
    c1->type[0] = cardDeck[0];
    c1->type[1] = cardDeck[1];
    c1->visible = 1;
    c1->next = NULL;
    board[0].next = c1;
    int cardCounter = 1;
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

void Q(char *cardDeck, struct head *board, struct head *aceFieldtemp) {
    struct card* currentCard;
    struct card* prevCard;
    for (int i = 0; i < 7; ++i) {
        currentCard = &board[i];
        while (currentCard->next != NULL) {
            prevCard = currentCard;
            currentCard= currentCard->next;
            free(prevCard);

        }
        free(currentCard);
    }
    while (aceFieldtemp->next != NULL) {
        currentCard = &aceFieldtemp->next;
        aceFieldtemp->next = currentCard->next;
        free(currentCard);
    }

    return;
}

/**
 * Filling the start of the array with linked lists.
 * @param board
 */
void headFiller(struct head board[]) {

    for (int i = 0; i < 7; ++i) {
        struct head h1;
        h1.next=NULL;
        board[i] = h1;
    }
}

/**
 * This is a method helping the print method.
 * The printBoard is made in a way where need the longest row for it to print pretty
 * @param board
 * @return
 */
int calculateLongestRowOfCards(struct head board[]) {
    int longestRow = 0;
    for (int i = 0; i < 7; ++i) {
        if (board[i].next == NULL) {
            continue;
        }
        struct card *cardForIteratingList = board[i].next;
        int cur = 1;
        while (cardForIteratingList->next != NULL) {
            cur++;
            cardForIteratingList = cardForIteratingList->next;
        }
        if (cur > longestRow) {
            longestRow = cur;
        }


    }
    return longestRow;
}

/**
 * Standard move, as not moving an entire row or moving a king
 * @param board
 * @param card
 * @param startRow
 * @param tooRow
 * @return
 */
int move(struct head board[], char const card[], int startRow, int tooRow) {
    printf("#move\n");
    if (startRow > 6 || tooRow > 6) {
        return 0;
    }
    struct card *current = board[startRow].next;
    struct card *result = NULL;
    printf("%c%c", current->next->type[0], current->next->type[1]);
    while (1) {
        if (current->next == NULL) {
            return 0;
        }
        printf("%c%c", current->next->type[0], current->next->type[1]);
        if (current->next->type[0] == card[0] && current->next->type[1] == card[1]) {
            result = current->next;
            break;
        }
        current = current->next;
    }
    printf("\n");
    printf("Current: %c%c\n", current->type[0], current->type[1]);
    printf("Result: %c%c", result->type[0], result->type[1]);
    printf("\n");
    struct card *to = board[tooRow].next;
    while (1) {
        if (to->next == NULL) {
            to->next = result;
            break;
        }
        to = to->next;
    }
    current->next = NULL;
    return 1;
}

/**
 * For moving whole rows only
 */
int moveWholeRow(struct head board[], int startRow, int tooRow) {
    printf("#moveWholeRow\n");
    struct card *rowStartToBeMoved = board[startRow].next;
    printf("%C%C\n", rowStartToBeMoved->type[0], rowStartToBeMoved->type[1]);
    struct card *IteratingCard = board[tooRow].next;
    while (IteratingCard->next != NULL) {
        printf("%C%C ", IteratingCard->type[0], IteratingCard->type[1]);

        IteratingCard = IteratingCard->next;
    }
    IteratingCard->next = rowStartToBeMoved;
    board[startRow].next = NULL;
    printf("\n");

    return 1;


}

/**
 * Only for moving kings to an empty row
 * @param board
 * @param card
 * @param startRow
 * @param tooRow
 * @return
 */
int moveKingToEmptyRow(struct head board[], char const card[], int startRow, int tooRow) {
    printf("#moveKingToEmptyRow");
    struct card *kingFinder = board[startRow].next;
    printf("%C%C", kingFinder->type[0], kingFinder->type[1]);
    if (kingFinder->type[0] == card[0] && kingFinder->type[1] == card[1]) {
        board[tooRow].next = kingFinder;
        board[startRow].next = NULL;
    }
    while (1) {
        if (kingFinder->next->type[0] == card[0] && kingFinder->next->type[1] == card[1]) {
            board[tooRow].next = kingFinder->next;
            kingFinder->next = NULL;
            break;
        }
        kingFinder = kingFinder->next;

    }
    return 1;

}

/**
 * Welcome text to get an overview of the commands
 */
void welcomeText() {
    printf("Welcome to yukon game\n");
    printf("Commands are as follows\n");
    printf("LD: Load a sorted predefined deck\n");
    printf("LD<UserInput> Load a specific dek of cards\n");
    printf("SR: Shuffle the cards\n");
    printf("SD: Load deck into cards.txt\n");
    printf("SD<UserInput>: Create or overwrite deck into a file\n");
    printf("SI: Do a random deck split\n");
    printf("SI<UserInput>: Do a specific deck split\n");
    printf("SW: Show the cards\n");
    printf("QQ: Exit the application\n");
    printf("P: play the game\n\n");


}

/**
 * Welcome command used when starting the game to help the player out.
 */
void playGameWelcomeText() {
    printf("\nYou just started a game with a loaded deck\n");
    printf("These are the possible moves\n");
    printf("Cx:nt->Cy\n");
    printf("Cx->Cy\n");
    printf("Cx->Fy\n");
    printf("Fx->Cy\n");
    printf("Where C is row number and F is ace column\n");
    printf("n stand for number and t stands for type\n");
    printf("Exiting the game back to startScreen is also possible with command Q\n");


}