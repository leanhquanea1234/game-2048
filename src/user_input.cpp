#include "user_input.h"



short getInput() {
	char keyInput = _getch();

	switch(keyInput) {
		case 'w': case 'W': return UP; break;
		case 's': case 'S': return DOWN; break;
		case 'a': case 'A': return LEFT; break;
		case 'd': case 'D': return RIGHT; break;
		case 'q': case 'Q': return EXIT; break;
		case 'u': return UNDO; break;
		case 'r': return REDO; break;
		default:
			return getInput();
	}
}