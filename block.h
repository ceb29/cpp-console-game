#ifndef BLOCK_H
#define BLOCK_H

#include <windows.h>

struct rect_coord {
    int x_start_coord;
    int y_start_coord;
    int x_end_coord;
    int y_end_coord;
};

struct coord {
    int x;
    int y;
};

class Block {
    HANDLE screen_buffer;
    rect_coord block;
    WORD attributes;
    DWORD buff_data;
    coord move_coord;
    int x_speed;
    int y_speed;
    int block_width;
    int block_height;
    int change_width;

public:
    Block(rect_coord, HANDLE);
    Block(rect_coord, HANDLE, coord);
    void draw_block(void);
    void set_block(void);
    void clear_block(void);
    void update_coord(void);
    void move_block(void);
    void clear_pixels_tb(void);
    void clear_pixels_rl(void);
    void clear_pixels(void);
    void add_pixels_tb(void);
    void add_pixels_rl(void);
    void add_pixels(void);
    void move_pixels(void);
    void wall_bounce(void);
};

rect_coord create_rect(int, int, int, int);
coord create_coord(int, int);

#endif