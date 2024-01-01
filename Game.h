#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdbool.h>

void resetBoard();
void printBoard();
bool playerMove(char choice);
void computerMove();
bool checkForWin(char symbol);
void gamePlay();

#endif
