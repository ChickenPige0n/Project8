#include "Bomb.h"
#include "Bullet.h"
#include "Game.h"
#include "Player.h"
#include "Tank.h"
#include <cstdlib>
#include <ctime>
#include <curses.h>
#include <math.h>
#include <memory>
#include <unistd.h>
Game::Game() {
    gui.init();
    player = new Player(this);
    items.push_back(player);
    items.push_back(new Tank(this, 15, 40, false));
    score = 0;
    bullet_count = 10;
    bullet_timer = 40;
    srand(time(0));
}

void Game::add_bullet(size_t r, size_t c) {
    if (bullet_count > 0) {
        bullet_count--;
        auto dir = player->get_dir();
        dir = dir == Item::None ? Item::Up : dir;
        items.push_back(new Bullet(r, c, this, Item::Up));
    }
}
void Game::add_bomb(size_t r, size_t c) {
    items.push_back(new Bomb(this, r, c));
}

void Game::update() {
    gui.clear();
    gui.printMsg(2, 68, "Bullet", bullet_count);
    gui.printMsg(3, 68, "Score", score);

    if (bullet_timer > 0) {
        bullet_timer--;
    } else {
        bullet_timer = 40;
        if (bullet_count < 20)
            bullet_count++;
    }

    int c = gui.get();
    list<Item *>::iterator bi = items.begin();
    while (bi != items.end()) {
        (*bi)->update(c);

        if ((*bi)->out()) {
            delete *bi;
            bi = items.erase(bi);
        } else {
            bi++;
        }
    }
}

bool Game::query_hit(Bullet *bullet) {
    for (auto tank : get_items<Tank>()) {
        if (bullet->row == tank->row &&
            abs((int)bullet->col - (int)tank->col) < 2) {
            score += 100;
            tank->hit(1);
            return true;
        }
    }
    return false;
}

void Game::complete() {
    gui.clear();
    gui.printMsg(10, 25, "Game ended, score:", score);
    usleep(3000000);
    int c = gui.get();
    if (c == 'q') {
        gui.end();
        exit(0);
    }
    remove_all<Bullet>();
    remove_all<Bomb>();
    
    score = 0;
    player->row = 12;
    player->col = 25;
    bullet_count = 20;
    bullet_timer = 40;
}

template <typename T> list<T *> Game::get_items() {
    auto selected = list<T *>();
    auto ii = items.begin();
    while (ii != items.end()) {
        if (typeid(**ii) == typeid(T)) {
            selected.push_front(dynamic_cast<T *>(*ii));
        }
        ii++;
    }
    return selected;
}

template <typename T> void Game::remove_all() {
    auto ii = items.begin();
    while (ii != items.end()) {
        if (typeid(**ii) == typeid(T)) {
            (*ii)->queue_delete();
        }
        ii++;
    }
}