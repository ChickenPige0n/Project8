#include "Constants.h"
#include "Gui.h"
#include <cstdlib>
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
void Gui::shake() {
    render_shift[0] = rand() % 5 - 2;
    render_shift[1] = rand() % 5 - 2;
}

int Gui::get() {
    int c = wgetch(win);
    flushinp();
    return c;
}

void Gui::paintat(size_t rw, size_t cl, char c) {
    rw += render_shift[0];
    cl += render_shift[1];
    mvwaddch(win, rw, cl, c);
    return;
}

void Gui::paintat(size_t rw, size_t cl, char c, Color color) {
    rw += render_shift[0];
    cl += render_shift[1];
    if (!colored) {
        paintat(rw, cl, c);
        return;
    }
    attron(COLOR_PAIR(color));
    mvwaddch(win, rw, cl, c);
    attroff(COLOR_PAIR(color));
    return;
}

void Gui::printMsg(int row, int col, const char *prompt, int v) {
    mvwprintw(win, row, col, prompt);
    char s[32];
    sprintf(s, "%d", v);
    mvwprintw(win, row, col + strlen(prompt) + 1, s);
}
void Gui::printMsg(int row, int col, const char *prompt) {
    mvwprintw(win, row, col, prompt);
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
void Gui::redraw() {
    wrefresh(win);
    auto reduce = [](int value) -> int {
        if (value > 0) {
            return value - 1;
        } else if (value < 0) {
            return value + 1;
        }
        return 0;
    };
    render_shift[0] = reduce(render_shift[0]);
    render_shift[1] = reduce(render_shift[1]);
}
