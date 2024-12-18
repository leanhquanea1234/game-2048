#include "terminal_rendering.h"

void printMenu() {

}

void printGameBoard(const Board &gameBoard) {
	system("CLS");
	std::cout << "HIGHSCORE: " << gameBoard.highcore << '\n';
	std::cout << "STEPS: " << gameBoard.step << '\n';
	for (int i = 0; i < gameBoard.size; i++) {
		for (int j = 0; j < gameBoard.size; j++)
			std::cout << gameBoard.value[i][j] << ' ';
		std::cout << '\n';
	}
	std::cout << '\n';
}