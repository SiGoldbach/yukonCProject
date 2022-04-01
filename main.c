#include <stdio.h>

int main() {
    FILE *inStream;
    inStream = fopen("C:\\Users\\Sebastian\\CLionProjects\\yukon\\KortTilSolitare.txt", "r");
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
    printf("\n");

    int cardPrintedNUm=0;
    for (int j = 0; j <= 104; ++j) {
        printf("%c", cards[j]);
        if (j % 2 != 0) {
            printf("\t");
            cardPrintedNUm++;
        }


    }


    fclose(inStream);

    return 0;
}
