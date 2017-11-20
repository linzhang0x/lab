#include <iostream>
#include <curses.h>


void printyx(const char *str, int y, int x);

WINDOW *win;

int main() {
	initscr();
	int ch;
	int row;
	int col;
	noecho();
	//raw();
	//keypad(stdscr, true);
	getmaxyx(stdscr, row, col);
	win = newwin(row, col, 0, 0);
	if (win == nullptr) {
		return -1;
	}
	if (has_colors()) {
		start_color();
	}
	printyx("NORMAL", row - 2, 1);
	// 2 是整个
	// 5 是半个
	if (termattrs() & A_BLINK) {
		printyx("Y", row - 2, col - 2);
	}
	else {
		printyx("N", row - 2, col - 2);
	}
	printyx("hello world", 10, 10);
	curs_set(2);
	scrollok(win, true);
	box(win, ACS_VLINE, ACS_HLINE);
	wmove(win, 1, 1);
	for (;;) {
		if ((ch = wgetch(win)) == ERR) {
			printyx("ERR", row - 1, 0);
		}
		else {
			int cury = getcury(win);
			int curx = getcurx(win);
			switch (ch)
			{
			case 'h':
				wmove(win, cury, curx - 1);
				break;
			case 'j':
				if (cury > 10) {
					scroll(win);
				}
				else {
					wmove(win, cury + 1, curx);
				}
				break;
			case 'k':
				wmove(win, cury - 1, curx);
				break;
			case 'l':
				wmove(win, cury, curx + 1);
				break;
			default:
				break;
			}
			wrefresh(win);
			cury = getcury(win);
			curx = getcurx(win);
			// ACS_BBLOCK 半格
			wattron(win, A_BLINK);
			waddch(win, ACS_BLOCK | A_UNDERLINE);
			wmove(win, cury, curx);
			continue;
		}
	}
}

void printyx(const char *str, int y, int x) {
	int curx = getcurx(win);
	int cury = getcury(win);
	mvwaddstr(win, y, x, str);
	wmove(win, cury, curx);
}