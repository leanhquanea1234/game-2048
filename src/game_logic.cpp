#include "game_logic.h"


/*
There will be a size x size board. '2' tiles will be spawn randomly with a rate of SPAWN_RATE out of total 
empty tiles. 
min spawned tiles will be 1 if the board has empty tile. 
The game ends when there is no more possible move.

Current max size is 5 x 5
2^(size * size) is the theoretically maximal point of 1 tile, that will be the winning solution

TO DO: set max size in input

*/


const double SPAWN_RATE = 0.1;
const int UNDO_CAP = 100;

bool initializeGameBoard(Board &gameBoard, const int &size) {
	gameBoard.size = size;
	gameBoard.value = new unsigned int*[size];
	if (gameBoard.value == nullptr) return 0;
	for (int i = 0; i < size; i++) {
		gameBoard.value[i] = new unsigned int[size];
		if (gameBoard.value[i] == nullptr) return 0;
	}

	for (int i = 0; i < gameBoard.size; i++)
		for (int j = 0; j < gameBoard.size; j++)
			gameBoard.value[i][j] = 0;

	return 1;
}

void updateHighscore(Board &gameBoard, const unsigned long long &value) {
	gameBoard.highcore += value;
}

void addRandomTile(Board &gameBoard) {
	srand(time(NULL));
	std::vector<std::pair<int, int>> emptyTile;
	int countEmptyTile = 0;

	for (int i = 0; i < gameBoard.size; i++)
		for (int j = 0; j < gameBoard.size; j++)
			if (!gameBoard.value[i][j]) {
				emptyTile.push_back({ i, j });
				countEmptyTile++;
			}

	if (!countEmptyTile) return;

	int maxSpawnTile = SPAWN_RATE * countEmptyTile;
	if (!maxSpawnTile) maxSpawnTile = 1;

	int spawnTile = 1 + rand() % maxSpawnTile;
	int tileChosen;

	for (int i = 0; i < spawnTile; i++) {
		tileChosen = rand() % countEmptyTile;
		gameBoard.value[emptyTile[tileChosen].first][emptyTile[tileChosen].second] = 2;
		emptyTile.erase(emptyTile.begin() + tileChosen);
		countEmptyTile--;
	}
}

unsigned long long mergeTile(unsigned int *line, const int &size) {
	unsigned long long score = 0;
	for(int i = 0; i < size - 1; i++)
		if (line[i] && line[i] == line[i + 1]) {
			line[i] <<= 1;
			line[i + 1] = 0;
			score += line[i];
		}
	return score;
}

void shiftTile(unsigned int *line, const int &size) {
	std::vector<unsigned int> temp;
	
	for (int i = 0; i < size; i++)
		if (line[i]) temp.push_back(line[i]);

	// copy temp -> line, the rest of line fills back with 0 
	int i = 0;
	for (; i < temp.size(); i++)
		line[i] = temp[i];
	for (; i < size; i++)
		line[i] = 0;
}

void moveTile(Board &gameBoard, short direction) {
	unsigned int *line = new unsigned int[gameBoard.size];
	gameBoard.step++;

	for (int i = 0; i < gameBoard.size; i++) {
		for(int j = 0; j < gameBoard.size; j++)
			switch (direction) { // extract board to line
				case UP: line[j] = gameBoard.value[j][i]; break;
				case DOWN: line[j] = gameBoard.value[gameBoard.size - 1 - j][i]; break;
				case LEFT: line[j] = gameBoard.value[i][j]; break;
				case RIGHT: line[j] = gameBoard.value[i][gameBoard.size - 1 - j]; break;
			}

		shiftTile(line, gameBoard.size);
		// merge and update score
		updateHighscore(gameBoard, mergeTile(line, gameBoard.size));
		shiftTile(line, gameBoard.size); // shift again bc of prev merge

		for (int j = 0; j < gameBoard.size; j++)
			switch (direction) { // extract line to board
			case UP:  gameBoard.value[j][i] = line[j]; break;
			case DOWN: gameBoard.value[gameBoard.size - 1 - j][i] = line[j]; break;
			case LEFT: gameBoard.value[i][j] = line[j]; break;
			case RIGHT: gameBoard.value[i][gameBoard.size - 1 - j] = line[j]; break;
			}
	}
	delete[] line;
}

bool checkPossibleMove(const Board &gameBoard) {
	for(int i = 0; i < gameBoard.size - 1; i++)
		for (int j = 0; j < gameBoard.size - 1; j++) {
			if (!gameBoard.value[i][j]) return true;
			else if (gameBoard.value[i][j] == gameBoard.value[i + 1][j] || gameBoard.value[i][j] == gameBoard.value[i][j + 1])
				return true;
		}
	return false;
}

void deleteGameBoard(Board &gameBoard) {
	for (int i = 0; i < gameBoard.size; i++)
		delete[] gameBoard.value[i];
	delete[] gameBoard.value;
	
	gameBoard.value = nullptr;
	gameBoard.size = 0;
	gameBoard.highcore = 0;
	gameBoard.step = 0;
}

// -----UNDO & REDO-----
/*
General ideal: savedGame has stack, queue to save pointer to gameBoard, so that gameBoard.value
just gets passed by its address.

undoStack is a dequeue to delete its oldest state when UNDO_CAP reaches its limit, still behaves like
a stack in normal circumstance though.
*/
Board* copyState(const Board &gameBoard) {
	Board *newGameBoard = new Board;
	if (!initializeGameBoard(*newGameBoard, gameBoard.size))
		return nullptr;

	newGameBoard->highcore = gameBoard.highcore;
	newGameBoard->size = gameBoard.size;
	newGameBoard->step = gameBoard.step;
	for (int i = 0; i < gameBoard.size; i++)
		for (int j = 0; j < gameBoard.size; j++)
			newGameBoard->value[i][j] = gameBoard.value[i][j];

	return newGameBoard;
}

// transfer gameboard to new pointer
Board* transferStateToPointer(Board &gameBoard) {
	Board *newGameBoard = new Board;
	*newGameBoard = gameBoard;

	return newGameBoard;
}

void updateUndoStack(const Board &gameBoard, SavedBoard &savedBoard) {
	if (savedBoard.undoStack.size() == UNDO_CAP) 
		savedBoard.undoStack.pop_back();
	savedBoard.undoStack.push_front(copyState(gameBoard));
}

bool undoGame(Board &gameBoard, SavedBoard &savedBoard) {
	if (savedBoard.undoStack.empty()) return false;
	Board *previousState = savedBoard.undoStack.front();
	savedBoard.undoStack.pop_front();

	savedBoard.redoStack.push(transferStateToPointer(gameBoard));
	gameBoard = *previousState;
	delete previousState;
	return true;
}

bool redoGame(Board &gameBoard, SavedBoard &savedBoard) {
	if (savedBoard.redoStack.empty()) return false;
	Board *nextState = savedBoard.redoStack.top();
	savedBoard.redoStack.pop();

	savedBoard.undoStack.push_front(transferStateToPointer(gameBoard));
	gameBoard = *nextState;
	delete nextState;
	return true;
}

void resetRedoStack(SavedBoard &savedBoard) {
	Board *temp;
	while (!savedBoard.redoStack.empty()) {
		temp = savedBoard.redoStack.top();
		savedBoard.redoStack.pop();
		deleteGameBoard(*temp);
		delete temp;
	}
}

void resetUndoStack(SavedBoard &savedBoard) {
	Board *temp;
	while (!savedBoard.undoStack.empty()) {
		temp = savedBoard.undoStack.front();
		savedBoard.undoStack.pop_front();
		deleteGameBoard(*temp);
		delete temp;
	}
}
void resetSavedBoard(SavedBoard &savedBoard) {
	resetRedoStack(savedBoard);
	resetUndoStack(savedBoard);
}