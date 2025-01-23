#ifndef _MY_LIBRARY_H_
#define _MY_LIBRARY_H_

#include <iostream>
#include <fstream>
#include <ctime>
#include <conio.h> // WIN specfic
#include "linked_list.h"


const short EXIT = 0, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4, UNDO = 5, REDO = 6;

struct Board {
	int size = 0;
	unsigned long long score = 0, step = 0;
	unsigned int **value;
};

struct SavedBoard {
	List<Board*> undoList, redoList;
};

//-----USER DEFINED-----
#include "game_logic.h"
#include "terminal_rendering.h"
#include "user_input.h"


#endif // !_MY_LIBRARY_H_