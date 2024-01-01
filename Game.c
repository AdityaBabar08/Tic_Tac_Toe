#include "Game.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char gameMatrix[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '},
};

void resetBoard() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      gameMatrix[i][j] = ' ';
    }
  }
}

void printBoard() {
  printf(" %c | %c | %c ", gameMatrix[0][0], gameMatrix[0][1],
         gameMatrix[0][2]);
  printf("\n---+---+---\n");

  printf(" %c | %c | %c ", gameMatrix[1][0], gameMatrix[1][1],
         gameMatrix[1][2]);
  printf("\n---+---+---\n");

  printf(" %c | %c | %c ", gameMatrix[2][0], gameMatrix[2][1],
         gameMatrix[2][2]);
  printf("\n");

  printf("\n\n");

  printf(" 1 | 2 | 3 ");
  printf("\n---+---+---\n");

  printf(" 4 | 5 | 6 ");
  printf("\n---+---+---\n");

  printf(" 7 | 8 | 9 ");
  printf("\n");
}

bool playerMove(char choice) {
  int row = (choice - '1') / 3;
  int col = (choice - '1') % 3;

  if (gameMatrix[row][col] == ' ') {
    gameMatrix[row][col] = 'O';
    return true;
  } else {
    printf("That slot is already occupied! Choose another one.\n");
    return false;
    // Prompt the player to choose again
  }
}

void computerMove() {
  int emptySpots[9];
  int emptyCount = 0;

  for (int i = 0; i < 9; i++) {
    if (gameMatrix[i / 3][i % 3] == ' ') {
      emptySpots[emptyCount++] = i + 1;
    }
  }

  if (emptyCount > 0) {
    int randomIndex = rand() % emptyCount;
    int chosenSpot = emptySpots[randomIndex];
    int row = (chosenSpot - 1) / 3;
    int col = (chosenSpot - 1) % 3;
    gameMatrix[row][col] = 'X';
  }
}

bool checkForWin(char symbol) {
  for (int i = 0; i < 3; i++) {
    // Check rows and columns
    if (gameMatrix[i][0] == symbol && gameMatrix[i][1] == symbol &&
        gameMatrix[i][2] == symbol) {
      return true;
    }
    if (gameMatrix[0][i] == symbol && gameMatrix[1][i] == symbol &&
        gameMatrix[2][i] == symbol) {
      return true;
    }
  }
  // Check diagonals
  if (gameMatrix[0][0] == symbol && gameMatrix[1][1] == symbol &&
      gameMatrix[2][2] == symbol) {
    return true;
  }
  if (gameMatrix[0][2] == symbol && gameMatrix[1][1] == symbol &&
      gameMatrix[2][0] == symbol) {
    return true;
  }
  return false;
}
void gamePlay() {
  char choice;
  int counter = 0;

  while (true) {
    printBoard();
    printf("Input the number where you want to mark (1-9): ");
    choice = getchar();
    getchar(); // Consume newline character

    if (playerMove(choice)) {
      // continue;
    } else {
      continue;
    }

    counter++;

    computerMove();
    // printBoard();
    if (counter >= 3) {
      if (checkForWin('X')) {
        printBoard();
        printf("\n--------YOU LOSE-----------------\n");
        printf("Want to play another game? [Y]es / [N]o\n");
        char ch = getchar();
        getchar();
        if (ch == 'n' || ch == 'N') {
          exit(EXIT_SUCCESS);

        } else {
          resetBoard();
          gamePlay();
        }
      } else if (checkForWin('O')) {
        printBoard();
        printf("\n-----------------YOU WIN-----------------\n");

        printf("Want to play another game? [Y]es / [N]o\n");
        char ch = getchar();
        getchar();
        if (ch == 'n' || ch == 'N') {
          exit(EXIT_SUCCESS);

        } else {
          resetBoard();
          gamePlay();
        }
      }
    }
    if (counter == 5) {
      printBoard();
      printf("-----------------ITS A TIE--------------------\n");

      printf("Want to play another game? [Y]es / [N]o\n");
      char ch = getchar();
      getchar();
      if (ch == 'n' || ch == 'N') {
        exit(EXIT_SUCCESS);

      } else {
        resetBoard();
        gamePlay();
      }
    }
  }
}

int main(int argc, char *argv[]) {
  srand((unsigned int)time(NULL));

  printf("Would you like to play? [Y]es / [N]o\n");
  char choice = getchar();

  if (choice == 'N' || choice == 'n') {
    exit(EXIT_SUCCESS);
  }

  getchar(); // Consume newline character
  gamePlay();

  return EXIT_SUCCESS;
}
