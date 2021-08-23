#include <iostream>
#include "screen.h"
#include "block.h"

coord wall_bounce(rect_coord, int, coord); 
int fps = 30;
int delay = 1000 / fps;
int move_speed = 1;

int main(void)
{
    //setup console screen buffer
    Screen screen;
    screen.start();
    //setup game clock
    Game_Time game_clock(clock());
    unsigned long long past_time = game_clock.get_millis();
    //create a block
    rect_coord rect1 = create_rect(1, 20, 1, 5);
    Block block1(rect1, screen.get_handle());
    screen.write();
    block1.set_block();
    //set up speed of block`
    coord move_coord = create_coord(move_speed, move_speed);
    //start main loop (exit if esc key is pressed)
    while (GetAsyncKeyState(VK_ESCAPE) == 0) {
        game_clock.update_time();
        if (game_clock.get_millis() - past_time > delay) {
            move_coord = wall_bounce(rect1, move_speed, move_coord);
            rect1 = block1.move_block(move_coord.x, move_coord.y);
            past_time = game_clock.get_millis();
        }
        screen.write();
    }
    std::cout << screen.get_font().dwFontSize.X << " " << screen.get_font().dwFontSize.Y;
    return 0;
} 

coord wall_bounce(rect_coord rect, int speed, coord current_coord){
    if (rect.x_start_coord < 2) {
        current_coord.x = speed*2;
    }
    else if (rect.x_end_coord > screen_width - 2) {
        current_coord.x = -speed*2;
    }
    else if (rect.y_start_coord < 2) {
        current_coord.y = speed;
    }
    else if (rect.y_end_coord > screen_height - 2) {
        current_coord.y = -speed;
    }
    return current_coord;
}

/*
//test2 (put inside main loop): write new char to entire screen every second
game_clock.update_time();
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