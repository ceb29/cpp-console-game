#include <windows.h>
#include "game_timer.h"

const int screen_width = 120;
const int screen_height = 30;
const int screen_mult = screen_width * screen_height;

struct rect_coord {
    int x_start_coord;
    int y_start_coord;
    int x_end_coord;
    int y_end_coord;
};

class Screen {
    HANDLE h_screen_buffer;
    DWORD buffer_data;
    wchar_t* char_buffer;
    COORD buffer_coord;
    int buff_ind;
    int index_plus;
    CONSOLE_CURSOR_INFO cursor_info;
    WORD attributes;

public:
    Screen(void);
    ~Screen(void);
    void border(void);
    void start(void);
    void write(void);
    void test1(Game_Time);
    void test2(Game_Time);
    void draw_block(rect_coord);
    void set_block(rect_coord);
    void clear_block(rect_coord);
    rect_coord move_block(rect_coord, int, int);
};

rect_coord create_block(int x_start, int x_end, int y_start, int y_end);