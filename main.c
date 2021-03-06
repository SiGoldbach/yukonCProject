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

int checkIfDeckIsValid(const char cards[]);

int simpleMove(struct head board[], int startRow, int endPile);

int moveToSIdePile(struct head board[], struct head pile[], int startRow, int endPile);

void showMoreCards(struct head board[]);

void QQ2();

void SD(char filename[], char *cardDeck);

void P(const char *cardDeck, struct head *board);

void SR(char *cardDeck);

int LD(char cards[], char name[]);

void printArrArray(char cards[]);

void printBoard(struct head *board, struct head *aceSpace);

int isPileMoveValid(struct card *bCard, struct card *toBeMovedCard);

void Q(struct head *board, struct head *aceFieldTemp);

void headFiller(struct head board[]);

int calculateLongestRowOfCards(struct head board[]);

int move(struct head board[], const char card[], int startRow, int tooRow);

int moveWholeRow(struct head board[], int startRow, int tooRow);

int moveKingToEmptyRow(struct head board[], char const card[], int startRow, int tooRow);

void welcomeText();

int checkIfWon(struct head board[]);

void playGameWelcomeText();

int commandBeforeGameHub();

void playGame(struct head *board, struct head *aceSpace);

int isMoveValid(struct card *bCard, struct card *toBeMovedCard);

/**
 * We are here defining a correct what types a deck should have to help some methods;
 */
char values[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};


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
                    if (checkIfDeckIsValid(cards)) {
                        activeDeckBoolean = 1;
                    } else {
                        printf("Deck is invalid");
                    }
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
                for (int i = 0; i < strlen(command) - -1; ++i) {
                    fileName[i] = command[start];
                    start++;
                }
                printf("%s", fileName);
                SD(fileName, cardsPointer);
            }
        } else if (command[0] == 'L' && command[1] == 'D') {
            char fileName[50];
            int start = 3;
            for (int i = 0; i < strlen(command) - 1; ++i) {
                fileName[i] = command[start];
                start++;
            }
            if (LD(cardsPointer, fileName)) {
                if (checkIfDeckIsValid(cards)) {
                    activeDeckBoolean = 1;
                } else {
                    printf("Deck is invalid");
                }
            }


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
    // Calls QQ (exit-method).
    return 0;

}

void playGame(struct head *board, struct head *aceSpace) {
    int printLast = 0;
    char command[50];
    char lastCommand[50];
    welcomeText();
    while (1) {
        showMoreCards(board);
        printBoard(board, aceSpace);
        if (!checkIfWon(board)) {
            printf("You have won the game\n");
        }
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
                Q(board, aceSpace);
                return;

            } else if (command[0] == '#') {
                break;
            }
        } else if (strlen(command) == 9) {

            char K = command[3];
            char type = command[4];
            char specificKing[2];
            specificKing[0] = K;
            specificKing[1] = type;
            move(board, specificKing, command[1] - 49, command[8] - 49);

        } else if (strlen(command) == 6) {
            if (command[4] == 'F') {
                printf("In if ");
                moveToSIdePile(board, aceSpace, command[1] - 49, command[5] - 49);
            } else if (command[0] == 'F') {
                printf("In F2");

            } else {
                simpleMove(board, command[1] - 49, command[5] - 49);
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
int LD(char cards[], char name[]) {                                // Load Deck
    FILE *inStream;                                                    // File stream
    if (strlen(name) != 0) {                                   // If name is not empty
        printf("Loading custom file\n");                    // Print loading custom file
        inStream = fopen(name, "r");                 // Open file
    } else {                                                       // If name is empty
        printf("Loading standard deck\n");                  // Print loading standard deck
        inStream = fopen("KortTilSolitare.txt", "r"); // Open file
    }
    if (inStream == NULL) {                                         // If file is not found
        printf("cant find deck\n");                         // Print cant find deck
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
 * This method is not complete according to the requirements, it just makes sure the deck resembles a deck with the right amount of each type and number
 * Just so the game doesnt break and destroys P methods.
 * @param cards
 * @return
 */
int checkIfDeckIsValid(const char cards[]) {
    int countForTwo = 0;
    int countForThree = 0;
    int countForFour = 0;
    int countForFive = 0;
    int countForSix = 0;
    int countForSeven = 0;
    int countForEight = 0;
    int countForNine = 0;
    int countForTen = 0;
    int countForJack = 0;
    int countForQueen = 0;
    int countForKing = 0;
    int countForAce = 0;

    for (int i = 0; i < 104; i += 2) {

        switch (cards[i]) {
            case 'A':
                countForAce++;
                break;
            case 'K':
                countForKing++;
                break;
            case 'Q':
                countForQueen++;
                break;
            case 'J':
                countForJack++;
                break;
            case 'T':
                countForTen++;
                break;
            case '9':
                countForNine++;
                break;
            case '8':
                countForEight++;
                break;
            case '7':
                countForSeven++;
                break;
            case '6':
                countForSix++;
                break;
            case '5':
                countForFive++;
                break;
            case '4':
                countForFour++;
                break;
            case '3':
                countForThree++;
                break;
            case '2':
                countForTwo++;
                break;

                //cases that are not correct cards

            default:
                return 0;
        }

    }
    int countForClubs = 0;
    int countForSpades = 0;
    int countForHearts = 0;
    int countForDiamonds = 0;
    for (int i = 1; i < 104; i += 2) {
        switch (cards[i]) {
            case 'S':
                countForSpades++;
                break;
            case 'D':
                countForDiamonds++;
                break;
            case 'H':
                countForHearts++;
                break;
            case 'C':
                countForClubs++;
                break;
            default:
                return 0;


        }

    }
    if (countForAce != 4) {
        return 0;
    }
    if (countForKing != 4) {
        return 0;
    }
    if (countForQueen != 4) {
        return 0;
    }
    if (countForJack != 4) {
        return 0;
    }
    if (countForTen != 4) {
        return 0;
    }
    if (countForNine != 4) {
        return 0;
    }
    if (countForEight != 4) {
        return 0;
    }
    if (countForSeven != 4) {
        return 0;
    }
    if (countForSix != 4) {
        return 0;
    }
    if (countForFive != 4) {
        return 0;
    }
    if (countForFour != 4) {
        return 0;
    }
    if (countForThree != 4) {
        return 0;
    }
    if (countForTwo != 4) {
        return 0;
    }
    if (countForSpades != 13) {
        return 0;
    }
    if (countForClubs != 13) {
        return 0;
    }
    if (countForHearts != 13) {
        return 0;
    }
    if (countForDiamonds != 13) {
        return 0;
    }
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
 * This method is used to print the board after the game has been started.
 * @param board
 */
void printBoard(struct head *board, struct head *aceSpace) {
    int timesPrintingAcePiles = 0;

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
            if (aceSpace[timesPrintingAcePiles].next == NULL)
                printf("\t[]\tF%d", j / 2 + 1);
            else {
                struct card *temp = aceSpace[timesPrintingAcePiles].next;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                printf("\t%c%c\tF%d", temp->type[0], temp->type[1], j / 2 + 1);


            }
            timesPrintingAcePiles++;
        }

        printf("\n");

    }
}

/**
 * method to split card into smaller stacks and sort them back into one deck in order of 1 by 1 from each deck.
 */
void SI(int split, char *cardDeck) { //split is the number of decks
    if (split > 52 || split < 0) { //if the number of decks is not valid
        printf("you entered invalid card deck split-size\n"); //print error message
        return; //return to main
    }
    char deck1[split * 2]; //create deck 1
    char deck2[104 - split * 2]; //create deck 2
    for (int i = 0; i < 104; i++) { //loop through all cards
        if (i < split * 2) { //if the card is in deck 1
            deck1[i] = cardDeck[i]; //add card to deck 1
        } else { //if the card is in deck 2
            deck2[i - split * 2] = cardDeck[i]; //add card to deck 2
        }
    }
    int removedCardDeck1 = 0; //create counter for deck 1
    int removedCardDeck2 = 0; //create counter for deck 2
    for (int i = 0; i < 104; i += 2) { //loop through all cards

        if ((i % 4 == 0 && removedCardDeck1 < split) || removedCardDeck2 >= (52 - split)) { //if the card is in deck 1
            cardDeck[i] = deck1[removedCardDeck1 * 2]; //add card to deck 1
            cardDeck[i + 1] = deck1[removedCardDeck1 * 2 + 1]; //add card to deck 1
            removedCardDeck1++; //increment counter
        } else { //if the card is in deck 2
            cardDeck[i] = deck2[removedCardDeck2 * 2]; //add card to deck 2
            cardDeck[i + 1] = deck2[removedCardDeck2 * 2 + 1]; //add card to deck 2
            removedCardDeck2++; //increment counter
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

/**
 * Command that allocates memory to the 52 cards and puts them into linked lists.
 * @param cardDeck
 * @param board
 */
void P(const char *cardDeck, struct head *board) {
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

void Q(struct head *board, struct head *aceFieldTemp) {
    struct card *currentCard;
    struct card *prevCard;
    for (int i = 0; i < 7; ++i) {
        if (board[i].next == NULL)
            continue;
        currentCard = board[i].next;
        while (currentCard->next != NULL) {
            prevCard = currentCard;
            currentCard = currentCard->next;
            free(prevCard);

        }
        free(currentCard);
    }
    for (int i = 0; i < 4; i++) {
        if (aceFieldTemp[i].next == NULL)
            continue;
        currentCard = aceFieldTemp[i].next;
        while (currentCard->next != NULL) {
            prevCard = currentCard;
            currentCard = currentCard->next;
            free(prevCard);
        }
        free(currentCard);
    }
}

/**
 * Filling the start of the array with linked lists.
 * @param board
 */
void headFiller(struct head board[]) {

    for (int i = 0; i < 7; ++i) {
        struct head h1;
        h1.next = NULL;
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
    if (startRow > 6 || tooRow > 6) {
        return 0;
    }
    if (board[startRow].next->type[0] == card[0] && board[startRow].next->type[1] == card[1]) {
        moveWholeRow(board, startRow, tooRow);
        return 1;
    }
    struct card *current = board[startRow].next;
    struct card *result = NULL;
    while (1) {
        if (current->next == NULL) {
            return 0;
        }
        if (current->next->type[0] == card[0] && current->next->type[1] == card[1]) {
            result = current->next;
            break;
        }
        current = current->next;
    }
    if (board[tooRow].next == NULL) {
        moveKingToEmptyRow(board, card, startRow, tooRow);
        return 0;
    }
    struct card *to = board[tooRow].next;
    while (1) {
        if (to->next == NULL) {
            if (!isMoveValid(to, result)) {
                return 0;
            }
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
    if (rowStartToBeMoved->visible == 0) {
        printf("Illegal move\n");
        return 0;

    }
    printf("%C%C\n", rowStartToBeMoved->type[0], rowStartToBeMoved->type[1]);
    struct card *IteratingCard = board[tooRow].next;
    while (IteratingCard->next != NULL) {
        printf("%C%C ", IteratingCard->type[0], IteratingCard->type[1]);

        IteratingCard = IteratingCard->next;
    }
    if (isMoveValid(IteratingCard, rowStartToBeMoved)) {
        IteratingCard->next = rowStartToBeMoved;
        board[startRow].next = NULL;
    } else {
        return 0;
    }

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
    if ((startRow > 6 || startRow < 0) || (tooRow > 6 || tooRow < 0)) {
        printf("Wrong startRow or toRow\n");
        return 0;
    }
    if (card[0] != 'K') {
        printf("Only kings can be move to empty rows\n");
        return 0;
    }
    if (board[startRow].next == NULL) {
        printf("There is nothing in that row\n");
        return 0;
    }
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

int moveToSIdePile(struct head board[], struct head pile[], int startRow, int endPile) {
    if ((startRow > 6 || startRow < 0) || (endPile > 3 || endPile < 0)) {
        printf("Wrong startRow or endPile\n");
        return 0;
    }

    if (board[startRow].next == NULL) {
        printf("There is no cards in that row\n");
        return 0;
    }
    if (board[startRow].next->next == NULL) {
        if (pile[endPile].next == NULL) {
            if (board->next->type[0] == 'A') {
                pile[endPile].next = board[startRow].next;
                board[startRow].next = NULL;
                return 1;

            } else {
                printf("Only aces can lay on the bottom of a pile\n");
                return 0;
            }
        } else {
            struct card *cardToBePlacedUpon = pile[endPile].next;
            while (cardToBePlacedUpon->next != NULL) {
                cardToBePlacedUpon = cardToBePlacedUpon->next;
            }
            if (isPileMoveValid(pile[endPile].next, board[startRow].next)) {
                cardToBePlacedUpon->next = board[startRow].next;
                board[startRow].next = NULL;
                return 1;
            } else {
                return 0;
            }


        }
        //Finding the bottom card value

    } else {
        struct card *cardToBeMoved = board[startRow].next;
        while (cardToBeMoved->next->next != NULL) {
            cardToBeMoved = cardToBeMoved->next;
        }
        if (pile[endPile].next == NULL) {
            if (cardToBeMoved->next->type[0] == 'A') {
                pile[endPile].next = cardToBeMoved->next;
                cardToBeMoved->next = NULL;
                return 1;
            } else {
                printf("Only aces can be there\n");
                return 0;
            }
        } else {
            struct card *iterator = pile[endPile].next;
            while (iterator->next != NULL) {
                iterator = iterator->next;
            }
            if (isPileMoveValid(iterator, cardToBeMoved->next)) {
                iterator->next = cardToBeMoved->next;
                cardToBeMoved->next = NULL;
                return 1;
            } else {
                return 0;
            }
        }

    }
}

int simpleMove(struct head board[], int startRow, int endPile) {
    if (board[startRow].next == NULL) {
        printf("There are no cards in this row\n");
        return 0;
    }
    //Finding the right card to be moved if it is on top do moveWholeRow if it is not do move
    struct card *toBeMoved = board[startRow].next;
    if (toBeMoved->next == NULL) {
        return moveWholeRow(board, startRow, endPile);
    } else {
        while (toBeMoved->next != NULL) {
            toBeMoved = toBeMoved->next;
        }
        char card[2];
        card[0] = toBeMoved->type[0];
        card[1] = toBeMoved->type[1];
        return move(board, card, startRow, endPile);

    }


}

/**
 * Welcome text to get an overview of the commands
 */
void welcomeText() {
    printf("Welcome to yukon game\n");
    printf("Commands are as follows\n");
    printf("LD: Load a sorted predefined deck\n");
    printf("LD<UserInput: Load a specific dek of cards; Do not put > at the end\n");
    printf("SR: Shuffle the cards\n");
    printf("SD: Load deck into cards.txt\n");
    printf("SD<UserInput: Create or overwrite deck into a file; Do not put > at the end \n");
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

/**
 * Show more cards used every time right before show bord to make sure all faceUp cards are face up.
 * @param board
 */
void showMoreCards(struct head board[]) {
    for (int i = 0; i < 7; ++i) {
        if (board[i].next == NULL) {
            continue;
        }
        struct card *iterator = board[i].next;
        while (iterator->next != NULL) {
            iterator = iterator->next;
        }
        iterator->visible = 1;
    }


}

int checkIfWon(struct head board[]) {
    for (int i = 0; i < 7; ++i) {
        if (board[i].next != NULL) {
            return 1;
        }
    }
    printf("Congratulations you won\n");
    return 0;
}

int isMoveValid(struct card *bCard, struct card *toBeMovedCard) {
    if (bCard->type[0] == 'A') {
        printf("Ace is the smallest card\n");
        return 0;
    }
    if (!toBeMovedCard->visible) {
        printf("Invisible card\n");
        return 0;
    }
    char valueOfCard = bCard->type[0];
    int position = -1;

    for (int i = 0; i < 13; ++i) {
        if (valueOfCard == values[i]) {
            position = i;
        }
    }
    if (position == -1) {
        printf("Something is wrong!\n");
        return 0;
    }
    if (toBeMovedCard->type[0] != values[position - 1]) {
        printf("%c is not smaller than %c\n", toBeMovedCard->type[0], values[position]);
        return 0;
    }
    if (toBeMovedCard->type[1] == bCard->type[1]) {
        printf("Same type\n");
        return 0;
    }
    return 1;


}

int isPileMoveValid(struct card *bCard, struct card *toBeMovedCard) {
    if (toBeMovedCard->type[0] == 'A') {
        printf("Aces can only be on the bottom\n");
        return 0;
    }
    if (bCard->type[0] == 'K') {
        printf("The pile is full\n");
        return 0;
    }
    char valueOfCard = bCard->type[0];
    int position = -1;

    for (int i = 0; i < 13; ++i) {
        if (valueOfCard == values[i]) {
            position = i;
        }
    }
    if (toBeMovedCard->type[0] != values[position + 1]) {
        printf("%c is not supposed to lay on top of %c\n", toBeMovedCard->type[0], values[position]);
        return 0;
    }
    if (toBeMovedCard->type[1] != bCard->type[1]) {
        printf("Not Same type\n");
        return 0;
    }
    return 1;


}

