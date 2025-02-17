#ifndef _MY_LIBRARY_H_
#define _MY_LIBRARY_H_

#include <iostream>
#include <fstream>
#include <ctime>
#include "linked_list.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


const short UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4, UNDO = 5, REDO = 6;

const short END_SESSION = 0, MENU = 1, IN_SESSION = 2;
const short CONTINUE = 0, GAME_OVER = 1, RESTART = 2,  OVERFLOWED = -1;

const unsigned long long MAX_LL = 18446744073709551614;

struct Board {
	unsigned long long score = 0, step = 0;
	unsigned int **value;
};

struct SavedBoard {
	List<Board*> undoList, redoList;
};

//-----USER DEFINED-----
#include "config.h"
#include "game_logic.h"
#include "saving.h"
#include "terminal_rendering.h"
#include "rendering.h"


#endif // !_MY_LIBRARY_H_