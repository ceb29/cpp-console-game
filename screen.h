#include <windows.h>
#include "game_timer.h"

const int screen_width = 750;
const int screen_height = 200;
const int screen_mult = screen_width * screen_height;

class Screen {
    HANDLE h_screen_buffer;
    DWORD buffer_data;
    wchar_t* char_buffer;
    COORD buffer_coord;
    int buff_ind;
    int index_plus;
    CONSOLE_CURSOR_INFO cursor_info;
    
public:
    Screen(void);
    ~Screen(void);
    HANDLE get_handle(void);
    void border(void);
    void start(void);
    void write(void);
    CONSOLE_FONT_INFOEX get_font(void);
    void set_font(void);
    void set_size(void);
    void test1(Game_Time);
    void test2(Game_Time);
};