#include <iostream>
#include "screen.h"
#include "block.h"
//
//just use write console for move_pixels 
//instead of writing text attributes row by row, text attributes can be written as column and row
//
rect_coord get_rect_cord(int width, int length, coord center);

int fps = 100;
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
    rect_coord block1_coord = get_rect_cord(10, 10, create_coord(10, 15));
    coord block1_speed = create_coord(10, 5);
    Block block1(block1_coord, screen.get_handle(), block1_speed);
    //start main loop (exit if esc key is pressed)
    while (GetAsyncKeyState(VK_RETURN) == 0) {
        //set up screen
        //press enter when done
    }
    block1.set_block();
    screen.write();
    while (GetAsyncKeyState(VK_ESCAPE) == 0) {
        game_clock.update_time();
        if (game_clock.get_millis() - past_time > delay) {
            block1.wall_bounce();
            block1.move_block();
            //block1.move_pixels();
            past_time = game_clock.get_millis();
        }
        //screen.write();
    }
    return 0;
} 

rect_coord get_rect_cord(int width, int length, coord center) {
    int screen_ratio = screen_width / screen_height;
    if (width > 1 && length > 1) {
        width = (width * screen_ratio) / 2;
        length = length / 2;
    }
    else {
        width = (width * screen_ratio);
    }
    rect_coord new_coord;
    new_coord.x_start_coord = center.x - width;
    new_coord.x_end_coord  = center.x + width;
    new_coord.y_start_coord = center.y - length;
    new_coord.y_end_coord = center.y + length;
    return new_coord;
}