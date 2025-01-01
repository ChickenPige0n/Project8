#include "Constants.h"
#include "Gui.h"
#include <cstring>
#include <ncurses.h>
using namespace std;

void Gui::init() {
    initscr(); /* Start curses mode              */
    refresh(); /* Print it on to the real screen */
    win = stdscr;
    refresh();
    curs_set(0);
    wrefresh(win);
    noecho();
    cbreak();
    keypad(win, true);
    nodelay(win, true);
    flushinp();
    for (int i = MIN_ROW; i <= MAX_ROW; i++) {
        mvaddch(i, MIN_COL - 1, '|');
        mvaddch(i, MAX_COL + 1, '|');
    }
    for (int i = MIN_COL; i <= MAX_COL; i++) {
        mvaddch(MAX_ROW + 1, i, '-');
    }
}

int Gui::get() {
    int c = wgetch(win);
    flushinp();
    return c;
}

void Gui::paintat(size_t rw, size_t cl, char c) {
    mvwaddch(win, rw, cl, c);
    wrefresh(win);
    return;
}

void Gui::paintat(size_t rw, size_t cl, char c, Color color) {
    if (!colored) {
        paintat(rw, cl, c);
        return;
    }
    attron(COLOR_PAIR(color));
    mvwaddch(win, rw, cl, c);
    attroff(COLOR_PAIR(color));
    wrefresh(win);
    return;
}

void Gui::printMsg(int row, int col, const char *prompt, int v) {
    mvwprintw(win, row, col, prompt);
    char s[32];
    sprintf(s, "%d", v);
    mvwprintw(win, row, col + strlen(prompt) + 1, s);
    wrefresh(win);
}
void Gui::printMsg(int row, int col, const char *prompt) {
    mvwprintw(win, row, col, prompt);
    wrefresh(win);
}

void Gui::clear() {
    werase(win);

    for (int i = MIN_ROW; i <= MAX_ROW; i++) {
        mvaddch(i, MIN_COL - 1, '|');
        mvaddch(i, MAX_COL + 1, '|');
    }
    for (int i = MIN_COL; i <= MAX_COL; i++) {
        mvaddch(MAX_ROW + 1, i, '-');
    }
}
