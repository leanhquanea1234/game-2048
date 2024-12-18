#include "my_library.h"

/*
TODO LIST:
add highscore X
add undo, redo X
add save
rendering with terminal ~
menu f it, later
input X

*/

// what happen in one cycle of a game
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
	else if (userInput == EXIT) return false;

	updateUndoStack(gameBoard, savedBoard);
	moveTile(gameBoard, userInput);
	resetRedoStack(savedBoard);
	addRandomTile(gameBoard);
	
	return true;
}

int main() {
	Board gameBoard;
	SavedBoard savedBoard;
	initializeGameBoard(gameBoard, 5);

	addRandomTile(gameBoard);
	while (runCycle(gameBoard, savedBoard));

	deleteGameBoard(gameBoard);
	resetSavedBoard(savedBoard);
	return 0;
}