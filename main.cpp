#include <iostream>
#include "screen.h"
#include "block.h"

int main(void)
{
    //setup console screen buffer
    Screen screen;
    screen.start();
    //setup game clock
    Game_Time game_clock(clock());
    unsigned long long past_time = game_clock.get_millis();
    int fps = 10;
    int delay = 1000/fps;
    rect_coord rect1 = create_rect(10, 12, 5, 6);
    Block block1(rect1, screen.get_handle());
    screen.write();
    block1.set_block();
    int toggle = 0;
    //start main loop (exit if esc key is pressed)
    while (GetAsyncKeyState(VK_ESCAPE) == 0) {
        game_clock.update_time();
        if (game_clock.get_millis() - past_time > delay) {
            if (toggle == 0) {
                toggle++;
            }
            else {
                rect1 = block1.move_block(2, 1);
                toggle = 0;
            }
            past_time = game_clock.get_millis();
        }
        screen.write();
    }
    return 0;
} 

        /*
        //test2 (put inside main loop): write new char to entire screen every second
        if (game_clock.get_millis() - past_time > delay) {
            screen.test2(game_clock);
            screen.write();
            past_time = game_clock.get_millis();

        }*/

        /*
        //test 1 (put inside main loop): Fill screen one char at a time
            screen.test1;
            screen.write();
        */

