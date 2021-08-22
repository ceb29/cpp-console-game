#include <windows.h>
#include "game_timer.h"

const int screen_width = 120;
const int screen_height = 30;
const int screen_mult = screen_width * screen_height;

class Screen {
    HANDLE h_screen_buffer;
    DWORD buffer_data;
    wchar_t* char_buffer;
    COORD buffer_coord;
    int buff_ind;
    int index_plus;

public:
    Screen(void);
    ~Screen(void);
    void border(void);
    void start(void);
    void write(void);
    void test1(Game_Time);
    void test2(Game_Time);
};