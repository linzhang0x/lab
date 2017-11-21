#include <iostream>
#include <curses.h>

enum MODE {
	MODE_NORMAL,
	MODE_INSERT
};


void printyx(const char *str, int y, int x);
void change_mode(int);
void normal_mode(int);
void insert_mode(int);

WINDOW *win;
int mode = MODE_NORMAL; // 0:NORMAL 1:INSERT
int row;
int col;

int main() {
	initscr();
	int ch;
	noecho();
	getmaxyx(stdscr, row, col);
	win = newwin(row, col, 0, 0);
	if (win == nullptr) {
		return -1;
	}
	if (has_colors()) {
		start_color();
	}
	// 初始化模式
	change_mode(MODE_NORMAL);
	if (termattrs() & A_BLINK) {
		printyx("Y", row - 2, col - 2);
	}
	else {
		printyx("N", row - 2, col - 2);
	}
	// 2 是整个
	// 5 是半个
	curs_set(2);
	box(win, ACS_VLINE, ACS_HLINE);
	wmove(win, 1, 2);
	for (;;) {
		if ((ch = wgetch(win)) == ERR) {
			printyx("ERR", row - 1, 0);
		}
		else {
			switch (mode) {
				case MODE_NORMAL:
					normal_mode(ch);
					break;
				case MODE_INSERT:
					insert_mode(ch);
					break;
				default:
					normal_mode(ch);
					break;
			}
		}
	}
}

void printyx(const char *str, int y, int x) {
	int curx = getcurx(win);
	int cury = getcury(win);
	mvwaddstr(win, y, x, str);
	wmove(win, cury, curx);
}

void change_mode(int m) {
	switch (m) {
		case 0:
			printyx("NORMAL", row - 2, 2);
			break;
		case 1:
			printyx("INSERT", row - 2, 2);
			break;
		default:
			printyx("NORMAL", row - 2, 2);
			break;
	}
	mode = m;
}

void normal_mode(int ch) {
	int cury = getcury(win);
	int curx = getcurx(win);
	switch (ch)
	{
		case 'h':
			wmove(win, cury, curx - 1);
			break;
		case 'j':
			wmove(win, cury + 1, curx);
			break;
		case 'k':
			wmove(win, cury - 1, curx);
			break;
		case 'l':
			wmove(win, cury, curx + 1);
			break;
		case 'i':
			change_mode(MODE_INSERT);
			break;
		default:
			break;
	}
	wrefresh(win);
}

void insert_mode(int ch) {
	switch (ch)
	{
		case 27:
			change_mode(MODE_NORMAL);
			break;
		default:
			waddch(win, ch);
	}
}
