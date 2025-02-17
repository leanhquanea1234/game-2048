#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include "my_library.h"



bool initializeGameBoard(Board &gameBoard);
void addRandomTile(Board &gameBoard);
bool moveTile(Board &gameBoard, short direction);
bool checkValidMovement(const Board& gameBoard, SavedBoard &savedBoard);
bool checkPossibleMove(const Board &gameBoard);
void deleteGameBoard(Board &gameBoard);
void clearGameBoard(Board& gameBoard);


// -----UNDO & REDO-----

void updateUndoList(const Board &gameBoard, SavedBoard &savedBoard);

bool undoGame(Board &gameBoard, SavedBoard &savedBoard);
bool redoGame(Board &gameBoard, SavedBoard &savedBoard);

void resetRedoList(SavedBoard &savedBoard);
void resetSavedBoard(SavedBoard &savedBoard);

#endif // !_GAME_LOGIC_H_