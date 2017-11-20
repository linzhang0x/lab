#include <iostream>
#include <curses.h>


void printyx(const char *str, int y, int x);

int main() {
	initscr();
	int ch;
	int row;
	int col;
	noecho();
	//raw();
	//keypad(stdscr, true);
	getmaxyx(stdscr, row, col);
	printyx("NORMAL", row - 1, 0);
	// 2 是整个
	// 5 是半个
	curs_set(2);
	for (;;) {
		if ((ch = getch()) == ERR) {
			printyx("ERR", row - 1, 0);
		}
		else {
			int cury = getcury(curscr);
			int curx = getcurx(curscr);
			switch (ch)
			{
			case 'h':
				move(cury, curx - 1);
				break;
			case 'j':
				move(cury + 1, curx);
				break;
			case 'k':
				move(cury - 1, curx);
				break;
			case 'l':
				move(cury, curx + 1);
				break;
			default:
				break;
			}
			refresh();
			//printyx("w", cury, curx);
			cury = getcury(curscr);
			curx = getcurx(curscr);
			addch('A' | A_BOLD);
			move(cury, curx);
			continue;
		}
	}
}

void printyx(const char *str, int y, int x) {
	int curx = getcurx(stdscr);
	int cury = getcury(stdscr);
	move(y, x);
	printw(str);
	move(cury, curx);
}