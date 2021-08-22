#include "game_timer.h"

//functions for Game_Time
Game_Time::Game_Time(clock_t time) {
    millis = 0;
    timer = time;
    clock_millis = 1.0;
}

unsigned long long int Game_Time::get_millis(void) {
    return millis;
}

void Game_Time::clear_millis(void) {
    if (millis > 10000) {
        millis = 0;
    }
}

void Game_Time::update_time(void) {
    clock_millis = ((float)(clock() - timer)) / CLOCKS_PER_SEC;
    if (clock_millis >= 0.001) {
        timer = clock();
        millis++;
    }
    clear_millis();
}