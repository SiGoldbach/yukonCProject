//
// Created by siggo on 22-04-2022.
//

#ifndef YUKON_GAMRLOGIC2_H
#define YUKON_GAMRLOGIC2_H

#endif //YUKON_GAMRLOGIC2_H

/*
 *  Command that quits the current game and goes back to the STARTUP phase. The memory still
 *  contains the deck of cards used to play the game that we are quitting. So, if we use the command P
 *  again after Q, we basically restart the last game.
 */
void quitGame();


void quitGame() {
    printf("\nWrite 'Q' to enter main menu \n");
    char q;
    char Q;
    scanf("%c", &q);
    if (q == Q) {
        exit(0);
    }
}

