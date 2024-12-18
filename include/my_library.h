#ifndef _MY_LIBRARY_H_
#define _MY_LIBRARY_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <ctime>
#include <conio.h> // WIN specfic

const short EXIT = 0, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4, UNDO = 5, REDO = 6;

struct Board {
	int size = 0;
	unsigned long long highcore = 0;
	unsigned int **value, step = 0;
};

struct SavedBoard {
	std::deque<Board*> undoStack;
	std::stack<Board*> redoStack;
};

//-----USER DEFINED-----
#include "game_logic.h"
#include "terminal_rendering.h"
#include "user_input.h"



#endif // !_MY_LIBRARY_H_