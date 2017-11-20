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
	if (termattrs() & A_BLINK) {
		printyx("Y", row - 1, col - 1);
	}
	else {
		printyx("N", row - 1, col - 1);
	}
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
			// ACS_BBLOCK 半格
			attron(A_BLINK);
			addch(ACS_BLOCK | A_UNDERLINE);
			move(cury, curx);
			continue;
		}
	}
}

void printyx(const char *str, int y, int x) {
	int curx = getcurx(stdscr);
	int cury = getcury(stdscr);
	mvaddstr(y, x, str);
	move(cury, curx);
}