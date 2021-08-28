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
    block_width = block.x_end_coord - block.x_start_coord;
    block_height = block.y_end_coord - block.y_start_coord;
    change_width = block_width;
}

Block::Block(rect_coord block_coord, HANDLE screen_buff, coord speed_cord) {
    screen_buffer = screen_buff;
    block = block_coord;
    attributes = FOREGROUND_BLUE | BACKGROUND_RED;
    buff_data = 0;
    move_coord = speed_cord;
    x_speed = speed_cord.x;
    y_speed = speed_cord.y;
    block_width = block.x_end_coord - block.x_start_coord;
    block_height = block.y_end_coord - block.y_start_coord;
    change_width = block_width;
}

coord Block::get_move_coord(void) {
    return move_coord;
}

void Block::draw_block(void) {
    int x = block.x_end_coord - block.x_start_coord;
    int y = block.y_end_coord - block.y_start_coord;
    for (int i = 0; i < y; i++) {
        COORD color_coord = { block.x_start_coord, block.y_start_coord + i };
        FillConsoleOutputAttribute(screen_buffer, attributes, x, color_coord, &buff_data);
    }
}

void Block::set_block(void) {
    attributes = BACKGROUND_RED;
    draw_block();
}

void Block::clear_block(void) {
    attributes = FOREGROUND_BLUE;
    draw_block();
}

void Block::update_coord(void) {
    block.x_start_coord += move_coord.x * 2;
    block.x_end_coord += move_coord.x * 2;
    block.y_start_coord += move_coord.y;
    block.y_end_coord += move_coord.y;
}

void Block::move_block(void) {
    clear_block();
    update_coord();
    set_block();
}

void Block::clear_pixels_tb(void) {
    int move_coord_x = move_coord.x * 2;
    COORD color_coord = { block.x_start_coord, block.y_start_coord };
    if (move_coord.y >= 0) {
        //clear top
        if (block.x_start_coord < 1) {
            color_coord.X = 0;
        }
        for (int i = 0; i < move_coord.y; i++) {
            FillConsoleOutputAttribute(screen_buffer, attributes, block_width, color_coord, &buff_data);
            color_coord.Y++;
        }
    }
    else if (move_coord.y < 0) {
        //clear bottom
        color_coord.Y = block.y_end_coord - 1;
        color_coord.X = block.x_start_coord + move_coord_x;
        if (block.x_start_coord < 1) {
            color_coord.X = 0;
        }
        for (int i = 0; i < -move_coord.y; i++) {
            FillConsoleOutputAttribute(screen_buffer, attributes, block_width - move_coord_x, color_coord, &buff_data);
            color_coord.Y--;
        }
    }
}

void Block::clear_pixels_rl(void) {
    int move_coord_x = move_coord.x * 2;
    COORD color_coord = { block.x_start_coord, block.y_start_coord };
    if (move_coord.x < 0) {
        //clear right
        color_coord.X = block.x_end_coord;
        color_coord.Y = block.y_start_coord;
        for (int i = 0; i < block_height; i++) {
            FillConsoleOutputAttribute(screen_buffer, attributes, -move_coord_x, color_coord, &buff_data);
            color_coord.Y++;
        }
    }
    else if (move_coord.x >= 0) {
        //clear left
        color_coord.X = block.x_start_coord;
        color_coord.Y = block.y_start_coord;
        for (int i = 0; i < block_height; i++) {
            FillConsoleOutputAttribute(screen_buffer, attributes, move_coord_x, color_coord, &buff_data);
            color_coord.Y++;
        }
    }
}

void Block::clear_pixels() {
    //need to add functions, to break code up
    attributes = FOREGROUND_BLUE;
    clear_pixels_tb();
    clear_pixels_rl();
}

void Block::add_pixels_tb(void) {
    int move_coord_x = move_coord.x * 2;
    COORD color_coord = { block.x_start_coord - move_coord_x, block.y_start_coord - move_coord.y };
    if (move_coord.y < 0 && move_coord.x < 0) {
        //add top
        //if (block.x_start_coord < 1) {
        //    color_coord.X = 0;
        //    change_width += move_coord_x;
        //}
        for (int i = 0; i < -move_coord.y; i++) {
            FillConsoleOutputAttribute(screen_buffer, attributes, change_width, color_coord, &buff_data);
            color_coord.Y--;
        }
    }
    else if (move_coord.y < 0 && move_coord.x >= 0) {
        //add top
        color_coord.X = block.x_start_coord;
        color_coord.Y = block.y_start_coord - move_coord.y;
        for (int i = 0; i < -move_coord.y; i++) {
            FillConsoleOutputAttribute(screen_buffer, attributes, block_width, color_coord, &buff_data);
            color_coord.Y--;
        }
    }
    else if (move_coord.y >= 0 && move_coord.x >= 0) {
        //add bottom
        color_coord.X = block.x_start_coord;
        color_coord.Y = block.y_end_coord - move_coord.y;
        for (int i = 0; i < move_coord.y; i++) {
            FillConsoleOutputAttribute(screen_buffer, attributes, block_width, color_coord, &buff_data);
            color_coord.Y++;
        }
    }
    else if (move_coord.y >= 0 && move_coord.x < 0) {
        //add bottom
        color_coord.X = block.x_start_coord - move_coord_x;
        color_coord.Y = block.y_end_coord - move_coord.y;

        for (int i = 0; i < move_coord.y; i++) {
            FillConsoleOutputAttribute(screen_buffer, attributes, block_width, color_coord, &buff_data);
            color_coord.Y++;
        }
    }
}

void Block::add_pixels_rl(void) {
    int move_coord_x = move_coord.x * 2;
    COORD color_coord = { block.x_start_coord - move_coord_x, block.y_start_coord - move_coord.y };
    if (move_coord.x >= 0 && move_coord.y >= 0) {
        //add right
        color_coord.X = block.x_end_coord - move_coord_x;
        color_coord.Y = block.y_start_coord;
        for (int i = 0; i < block_height; i++) {
            FillConsoleOutputAttribute(screen_buffer, attributes, move_coord.x * 2, color_coord, &buff_data);
            color_coord.Y++;
        }
    }
    else if (move_coord.x >= 0 && move_coord.y < 0) {
        //add right
        color_coord.X = block.x_end_coord - move_coord_x;
        color_coord.Y = block.y_start_coord - move_coord.y;
        for (int i = 0; i < block_height + move_coord.y; i++) {
            FillConsoleOutputAttribute(screen_buffer, attributes, move_coord.x * 2, color_coord, &buff_data);
            color_coord.Y++;
        }
    }
    else if (move_coord.x < 0 && move_coord.y >= 0) {
        //add left
        color_coord.X = block.x_start_coord - move_coord_x;
        color_coord.Y = block.y_start_coord;
        for (int i = 0; i < block_height; i++) {
            FillConsoleOutputAttribute(screen_buffer, attributes, -move_coord.x * 2, color_coord, &buff_data);
            color_coord.Y++;
        }
    }
    else if (move_coord.x < 0 && move_coord.y < 0) {
        //add left
        color_coord.X = block.x_start_coord - move_coord_x;
        color_coord.Y = block.y_start_coord - move_coord.y;
        for (int i = 0; i < block_height + move_coord.y; i++) {
            FillConsoleOutputAttribute(screen_buffer, attributes, -move_coord.x * 2, color_coord, &buff_data);
            color_coord.Y++;
        }
    }
}

void Block::add_pixels(void) {
    //need to add functions, to break code up
    attributes = BACKGROUND_RED;
    add_pixels_tb();
    add_pixels_rl();
}

void Block::move_pixels(void) {
    clear_pixels();
    update_coord();
    add_pixels();
}

void Block::wall_bounce(void) {
    if (block.x_start_coord < 0 && move_coord.x < 0) {
        move_coord.x = -move_coord.x;
    }
    else if (block.x_end_coord > screen_width && move_coord.x > 0) {
        move_coord.x = -move_coord.x;
    }
    else if (block.y_start_coord < 0 && move_coord.y < 0) {
        move_coord.y = -move_coord.y;
    }
    else if (block.y_end_coord > screen_height && move_coord.y > 0) {
        move_coord.y = -move_coord.y;
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