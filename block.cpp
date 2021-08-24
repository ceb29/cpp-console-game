#include "block.h"
#include "constants.h"

Block::Block(rect_coord block_coord, HANDLE screen_buff) {
    screen_buffer = screen_buff;
    block = block_coord;
    attributes = FOREGROUND_BLUE | BACKGROUND_RED;
    buff_data = 0;
    move_coord = create_coord(0, 0);
    x_speed = move_coord.x;
    y_speed = move_coord.y;
}

Block::Block(rect_coord block_coord, HANDLE screen_buff, coord speed_cord) {
    screen_buffer = screen_buff;
    block = block_coord;
    attributes = FOREGROUND_BLUE | BACKGROUND_RED;
    buff_data = 0;
    move_coord = speed_cord;
    x_speed = speed_cord.x;
    y_speed = speed_cord.y;
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

void Block::move_block(void) {
    clear_block();
    block.x_start_coord += move_coord.x *2;
    block.x_end_coord += move_coord.x *2;
    block.y_start_coord += move_coord.y;
    block.y_end_coord += move_coord.y;
    set_block();
}

void Block::wall_bounce(void) {
    if (block.x_start_coord + x_speed  < 1) {
        move_coord.x = x_speed;
    }
    else if (block.x_end_coord - x_speed > screen_width - 1) {
        move_coord.x = -x_speed;
    }
    else if (block.y_start_coord - y_speed < 1) {
        move_coord.y = y_speed;
    }
    else if (block.y_end_coord + y_speed > screen_height - 1) {
        move_coord.y = -y_speed;
    };
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