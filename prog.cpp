#include <iostream>
#include <ncurses.h>

int main() {
	initscr();

	// WINDOW *win = newwin(10, 12, 0, 0); 
	int ch;
	// nodelay(stdscr, TRUE);
	noecho();
	for (;;) {
		if ((ch = getch()) == ERR) {
			addch('a');
		} else {
			if (ch == KEY_ENTER) {
				move(1, 0);
				refresh();
			} else {
				addch(ch | A_UNDERLINE);
			}
			// std::cerr << ch << std::endl;
		}
	}
}
