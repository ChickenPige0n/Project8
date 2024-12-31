#include "Gui.h"
#include <ncurses.h>
#include <sys/time.h>

#include "Game.h"
#include <cstddef>
#include <ctime>
#include <iostream>
#include <unistd.h>
using namespace std;

int main() {

    struct timeval time_now {};

    gettimeofday(&time_now, NULL);
    time_t oldTime = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
    time_t currentTime = oldTime;
    Game game;
    while (true) {
        gettimeofday(&time_now, NULL);
        currentTime = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
        if (currentTime - oldTime < 50) {
            usleep(25);
            continue;
        }
        game.update();
        oldTime = currentTime;
    }
    return 0;
}
