#include "terminal_rendering.h"

short getInput() {
	char keyInput;
	std::cin >> keyInput;

	switch(keyInput) {
		case 'w': case 'W': return UP; break;
		case 's': case 'S': return DOWN; break;
		case 'a': case 'A': return LEFT; break;
		case 'd': case 'D': return RIGHT; break;
		case 'q': case 'Q': return END_SESSION; break;
		case 'u': return UNDO; break;
		case 'r': return REDO; break;
		default:
			return getInput();
	}
}

void printGameBoard(const Board &gameBoard) {
	system("CLS");
	std::cout << "SCORE: " << gameBoard.score << '\n';
	std::cout << "STEPS: " << gameBoard.step << '\n';
	for (int i = 0; i < gameBoard.size; i++) {
		for (int j = 0; j < gameBoard.size; j++)
			std::cout << gameBoard.value[i][j] << ' ';
		std::cout << '\n';
	}
	std::cout << '\n';
}

bool runCycle(Board &gameBoard, SavedBoard &savedBoard) {
	if (!checkPossibleMove(gameBoard)) return false;
	short userInput;

	printGameBoard(gameBoard);
	userInput = getInput();
	if (userInput == UNDO) {
		undoGame(gameBoard, savedBoard);
		return true;
	}
	else if (userInput == REDO) {
		redoGame(gameBoard, savedBoard);
		return true;
	}
	else if (userInput == END_SESSION) return false;

	updateUndoList(gameBoard, savedBoard);
	moveTile(gameBoard, userInput);
	resetRedoList(savedBoard);
	addRandomTile(gameBoard);
	
	return true;
}

void RunGameTerminal(Board &gameBoard, SavedBoard &savedBoard) {
	initializeGameBoard(gameBoard, GAME_SIZE);
    addRandomTile(gameBoard);

	while (runCycle(gameBoard, savedBoard));
	deleteGameBoard(gameBoard);
	resetSavedBoard(savedBoard);
}