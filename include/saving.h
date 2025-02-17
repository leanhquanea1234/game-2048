#ifndef _SAVING_H_
#define _SAVING_H_

#include "my_library.h"

void saveGame(const char* filename, const Board& gameBoard, const SavedBoard& savedBoard);
void loadGame(const char* filename, Board& gameBoard, SavedBoard& savedBoard);

#endif