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

public:
    Block(rect_coord, HANDLE);
    void draw_block(void);
    void set_block(void);
    void clear_block(void);
    rect_coord move_block(int, int);
};

rect_coord create_rect(int, int, int, int);
coord create_coord(int, int);