#include <iostream>
#include "screen.h"

int main(void)
{
    //setup console screen buffer
    Screen screen;
    screen.start();
    //setup game clock
    Game_Time game_clock(clock());
    unsigned long long past_time = game_clock.get_millis();
    int delay = 1000;
    screen.write();
    //start main loop (exit if esc key is pressed)
    while (GetAsyncKeyState(VK_ESCAPE) == 0) {
        game_clock.update_time();
        if (game_clock.get_millis() - past_time > delay){
            screen.test2(game_clock);
            screen.write();
            past_time = game_clock.get_millis(); 
        }
        //screen.test1(game_clock);
    }
    return 0;
}