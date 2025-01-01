#include "Game.h"
#include "Gui.h"
#include "SelectScene.h"
#include <cstddef>
#include <ctime>
#include <iostream>
#include <ncurses.h>
#include <sys/time.h>
#include <unistd.h>
using namespace std;

int main() {

    srand(time(0));
    struct timeval time_now {};

    gettimeofday(&time_now, NULL);
    time_t oldTime = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
    time_t currentTime = oldTime;

    int scene = 0;
    SelectScene *sc = new SelectScene();
    Game *game;
    while (true) {
        gettimeofday(&time_now, NULL);
        currentTime = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
        if (currentTime - oldTime < 50) {
            usleep(25);
            continue;
        }
        if (scene == 0) {
            int selection = sc->update();
            if (selection == -1) {

            } else {
                scene = 1;
                game = new Game(selection == 2);
            }
        } else if (scene == 1) {
            game->update();
        }
        oldTime = currentTime;
    }
    return 0;
}
