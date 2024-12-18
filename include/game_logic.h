#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include "my_library.h"



bool initializeGameBoard(Board &gameBoard, const int &size);
void addRandomTile(Board &gameBoard);
void moveTile(Board &gameBoard, short direction);
bool checkPossibleMove(const Board &gameBoard);
void deleteGameBoard(Board &gameBoard);

// -----UNDO & REDO-----

void updateUndoStack(const Board &gameBoard, SavedBoard &savedBoard);

bool undoGame(Board &gameBoard, SavedBoard &savedBoard);
bool redoGame(Board &gameBoard, SavedBoard &savedBoard);

void resetRedoStack(SavedBoard &savedBoard);
void resetSavedBoard(SavedBoard &savedBoard);

#endif // !_GAME_LOGIC_H_