#include "block.h"

Block::Block(rect_coord block_in, HANDLE screen_buff) {
    screen_buffer = screen_buff;
    block = block_in;
    attributes = FOREGROUND_BLUE | BACKGROUND_RED;
    buff_data = 0;
}
    
void Block::draw_block(void) {
    int x = block.x_end_coord - block.x_start_coord;
    int y = block.y_end_coord - block.y_start_coord;
    for (int i = 0; i < y; i++) {
        COORD color_coord = { block.x_start_coord, block.y_start_coord + i};
        FillConsoleOutputAttribute(screen_buffer, attributes, x, color_coord, &buff_data);
    }
}

void Block::set_block(void) {
    attributes = FOREGROUND_BLUE | BACKGROUND_RED;
    draw_block();
}

void Block::clear_block(void) {
    attributes = FOREGROUND_BLUE;
    draw_block();
}

rect_coord Block::move_block(int x_speed, int y_speed) {
    clear_block();
    block.x_start_coord += x_speed*2;
    block.x_end_coord += x_speed*2;
    block.y_start_coord += y_speed;
    block.y_end_coord += y_speed;
    set_block();
    return block;
}

rect_coord create_rect(int x_start, int x_end, int y_start, int y_end) {
    rect_coord block;
    block.x_start_coord = x_start;
    block.x_end_coord = x_end;
    block.y_start_coord = y_start;
    block.y_end_coord = y_end;
    return block;
}

coord create_coord(int x, int y) {
    coord coordinate;
    coordinate.x = x;
    coordinate.y = y;
    return coordinate;
}