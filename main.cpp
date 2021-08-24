#include <iostream>
#include "screen.h"
#include "block.h"

int fps = 60;
int delay = 1000 / fps;

int main(void)
{
    //setup console screen buffer
    Screen screen;
    screen.start();
    //setup game clock
    Game_Time game_clock(clock());
    unsigned long long past_time = game_clock.get_millis();
    //create a block
    rect_coord block1_coord = create_rect(1, 20, 1, 5);
    coord block1_speed = create_coord(1, 1);
    Block block1(block1_coord, screen.get_handle(), block1_speed);
    block1.set_block();
    screen.write();
    //start main loop (exit if esc key is pressed)
    while (GetAsyncKeyState(VK_ESCAPE) == 0) {
        game_clock.update_time();
        if (game_clock.get_millis() - past_time > delay) {
            block1.wall_bounce();
            block1.move_block();
            past_time = game_clock.get_millis();
        }
        //screen.write();
    }
    return 0;
} 