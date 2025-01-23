#ifndef _MY_LIBRARY_H_
#define _MY_LIBRARY_H_

#include <iostream>
#include <fstream>
#include <ctime>
#include "linked_list.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


const short OVERFLOWED = 10, END_SESSION = 0, MENU = 1, IN_SESSION = 2, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4, UNDO = 5, REDO = 6;
const unsigned long long MAX_LL = 18446744073709551615;

struct Board {
	int size = 0;
	unsigned long long score = 0, step = 0;
	unsigned int **value;
};

struct SavedBoard {
	List<Board*> undoList, redoList;
};

//-----USER DEFINED-----
#include "config.h"
#include "game_logic.h"
#include "terminal_rendering.h"
#include "rendering.h"


#endif // !_MY_LIBRARY_H_