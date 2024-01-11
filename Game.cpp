#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Function prototypes
void resetBoard();
void printBoard();
bool playerMove(char choice);
void computerMove();
int minimax(char board[9], int depth, bool isMaximizing);
char checkWinner(const char board[9]);
bool isBoardFull(const char board[9]);
void gamePlay();

char gameMatrix[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

void resetBoard() {
  for (int i = 0; i < 9; i++) {
    gameMatrix[i] = ' ';
  }
}

void printBoard() {
  for (int i = 0; i < 9; i++) {
    std::cout << " " << gameMatrix[i] << " ";
    if (i % 3 == 2 && i < 8) {
      std::cout << "\n---+---+---\n";
    } else if (i < 8) {
      std::cout << "|";
    }
  }
  std::cout << "\n\n";
  for (int i = 1; i <= 9; i++) {
    std::cout << " " << i << " ";
    if (i % 3 == 0 && i < 9) {
      std::cout << "\n---+---+---\n";
    } else if (i < 9) {
      std::cout << "|";
    }
  }
  std::cout << "\n";
}

bool playerMove(char choice) {
  int index = choice - '1';

  if (gameMatrix[index] == ' ') {
    gameMatrix[index] = 'O';
    return true;
  } else {
    std::cout << "That slot is already occupied! Choose another one.\n";
    return false;
  }
}

void computerMove() {
  int bestScore = -1000;
  int bestMove = -1;

  for (int i = 0; i < 9; i++) {
    if (gameMatrix[i] == ' ') {
      gameMatrix[i] = 'X';
      int score = minimax(gameMatrix, 0, false);
      gameMatrix[i] = ' ';

      if (score > bestScore) {
        bestScore = score;
        bestMove = i;
      }
    }
  }

  gameMatrix[bestMove] = 'X';
}

int minimax(char board[9], int depth, bool isMaximizing) {
  char winner = checkWinner(board);

  if (winner != ' ') {
    return winner == 'X' ? 1 : -1;
  }

  if (isBoardFull(board)) {
    return 0;
  }

  if (isMaximizing) {
    int bestScore = -1000;
    for (int i = 0; i < 9; i++) {
      if (board[i] == ' ') {
        board[i] = 'X';
        int score = minimax(board, depth + 1, false);
        board[i] = ' ';
        bestScore = std::max(score, bestScore);
      }
    }
    return bestScore;
  } else {
    int bestScore = 1000;
    for (int i = 0; i < 9; i++) {
      if (board[i] == ' ') {
        board[i] = 'O';
        int score = minimax(board, depth + 1, true);
        board[i] = ' ';
        bestScore = std::min(score, bestScore);
      }
    }
    return bestScore;
  }
}

char checkWinner(const char board[9]) {
  for (int i = 0; i < 3; i++) {
    if (board[i * 3] == board[i * 3 + 1] &&
        board[i * 3 + 1] == board[i * 3 + 2] && board[i * 3] != ' ') {
      return board[i * 3];
    }
    if (board[i] == board[i + 3] && board[i + 3] == board[i + 6] &&
        board[i] != ' ') {
      return board[i];
    }
  }

  if (board[0] == board[4] && board[4] == board[8] && board[0] != ' ') {
    return board[0];
  }

  if (board[2] == board[4] && board[4] == board[6] && board[2] != ' ') {
    return board[2];
  }

  return ' ';
}

bool isBoardFull(const char board[9]) {
  for (int i = 0; i < 9; i++) {
    if (board[i] == ' ') {
      return false;
    }
  }
  return true;
}

void gamePlay() {
  char choice;
  int counter = 0;

  while (true) {
    printBoard();

    if (counter % 2 == 0) {
      std::cout << "Input the number where you want to mark (1-9): ";
      std::cin >> choice;

      if (playerMove(choice)) {
        counter++;
      } else {
        continue;
      }
    } else {
      computerMove();
      counter++;
    }

    char winner = checkWinner(gameMatrix);
    if (winner != ' ') {
      printBoard();
      if (winner == 'X') {
        std::cout << "\n--------YOU LOSE-----------------\n";
      } else {
        std::cout << "\n-----------------YOU WIN-----------------\n";
      }
      break;
    }

    if (isBoardFull(gameMatrix)) {
      printBoard();
      std::cout << "-----------------ITS A TIE--------------------\n";
      break;
    }
  }

  std::cout << "Want to play another game? [Y]es / [N]o\n";
  char ch;
  std::cin >> ch;
  if (ch == 'n' || ch == 'N') {
    exit(EXIT_SUCCESS);
  } else {
    resetBoard();
    gamePlay();
  }
}

int main(int argc, char *argv[]) {
  srand(static_cast<unsigned int>(time(nullptr)));

  std::cout << "Would you like to play? [Y]es / [N]o\n";
  char choice;
  std::cin >> choice;

  if (choice == 'N' || choice == 'n') {
    exit(EXIT_SUCCESS);
  }

  gamePlay();

  return EXIT_SUCCESS;
}
