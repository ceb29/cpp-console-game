#include <iostream>
#include "screen.h"
#include "block.h"

struct coord{
    int x;
    int y;
};

coord wall_bounce(rect_coord, int, coord);
coord create_coord(int, int);

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
    rect_coord rect1 = create_rect(1, 3, 1, 2);
    Block block1(rect1, screen.get_handle());
    screen.write();
    block1.set_block();
    int toggle = 0;
    int move_speed = 1;
    coord move_coord = create_coord(move_speed, move_speed);
    move_coord.x = move_speed;
    move_coord.y = move_speed;
    //start main loop (exit if esc key is pressed)
    while (GetAsyncKeyState(VK_ESCAPE) == 0) {
        game_clock.update_time();
        if (game_clock.get_millis() - past_time > delay) {
            if (toggle == 0) {
                toggle++;
            }
            else {
                move_coord = wall_bounce(rect1, move_speed, move_coord);
                rect1 = block1.move_block(move_coord.x, move_coord.y);
                toggle = 0;
            }
            past_time = game_clock.get_millis();
        }
        screen.write();
    }
    return 0;
} 

coord wall_bounce(rect_coord rect, int speed, coord current_coord){
    if (rect.x_start_coord < 2) {
        current_coord.x = speed;
    }
    else if (rect.x_end_coord > screen_width - 2) {
        current_coord.x = -speed;
    }
    else if (rect.y_start_coord < 2) {
        current_coord.y = speed;
    }
    else if (rect.y_end_coord > screen_height - 2) {
        current_coord.y = -speed;
    }
    return current_coord;
}

coord create_coord(int x, int y) {
    coord coordinate;
    coordinate.x = x;
    coordinate.y = y;
    return coordinate;
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