#include "screen.h"

Screen::Screen(void) {
    buffer_data = 0;
    char_buffer = new wchar_t[screen_mult];
    buffer_coord = { 0, 0 };
    buff_ind = 121;
    index_plus = 0;
    h_screen_buffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    cursor_info.bVisible = FALSE;
    cursor_info.dwSize = 1;
    attributes = FOREGROUND_BLUE|BACKGROUND_RED;
}

Screen::~Screen(void) {
    delete[] char_buffer;
}

void Screen::border(void) {
    wchar_t char_border = '-';
    for (int i = 0; i < screen_mult; i++) {
        if (i < screen_width || i % screen_width == 0 || i % screen_width == screen_width - 1) {
            char_buffer[i] = char_border;
        }
        else if (i < screen_mult - screen_width) {
            char_buffer[i] = L' ';
        }
        else {
            char_buffer[i] = char_border;
        }
    }
}

void Screen::start(void) {
    border();
    SetConsoleActiveScreenBuffer(h_screen_buffer);
    SetConsoleCursorInfo(h_screen_buffer, &cursor_info); //remove cursor
    WriteConsoleOutputCharacter(h_screen_buffer, char_buffer, screen_mult, buffer_coord, &buffer_data);
}

void Screen::write(void) {
    WriteConsoleOutputCharacter(h_screen_buffer, char_buffer, screen_mult, buffer_coord, &buffer_data);
}

void Screen::test1(Game_Time g_time) {
    if (g_time.get_millis() >= 1) {
        if (char_buffer[buff_ind] != L'-') {
            char_buffer[buff_ind] = L'a' + index_plus;
        }
        if (buff_ind < screen_mult) {
            buff_ind++;
        }
        else {
            buff_ind = 0;
            if (index_plus < 25) {
                index_plus++;
            }
            else {
                index_plus = 0;
            }
        }
    }
}

void Screen::test2(Game_Time g_time) {
    wchar_t char_border = '-';
    for (int i = 0; i < screen_mult; i++) {
        if (char_buffer[buff_ind] != L'-') {
            char_buffer[buff_ind] = L'a' + index_plus;
        }
        if (buff_ind < screen_mult) {
            buff_ind++;
        }
        else {
            buff_ind = 0;
            if (index_plus < 25) {
                index_plus++;
            }
            else {
                index_plus = 0;
            }
        }
    }
}

void Screen::draw_block(rect_coord block) {
    int x = block.x_end_coord - block.x_start_coord;
    int y = block.y_end_coord - block.y_start_coord;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            COORD color_cood = { block.x_start_coord + j, block.y_start_coord + i };
            WriteConsoleOutputAttribute(h_screen_buffer, &attributes, 1, color_cood, &buffer_data);
        }
    }
}

void Screen::set_block(rect_coord block) {
    attributes = FOREGROUND_BLUE | BACKGROUND_RED;
    draw_block(block);
}

void Screen::clear_block(rect_coord block) {
    attributes = FOREGROUND_BLUE;
    draw_block(block);
}

rect_coord Screen::move_block(rect_coord block, int x_speed,int y_speed) {
    clear_block(block);
    block.x_start_coord += 2;
    block.x_end_coord += 2;
    block.y_start_coord += 1;
    block.y_end_coord += 1;
    set_block(block);
    return block;
 }

rect_coord create_block(int x_start, int x_end, int y_start, int y_end) {
    rect_coord block;
    block.x_start_coord = x_start;
    block.x_end_coord = x_end;
    block.y_start_coord = y_start;
    block.y_end_coord = y_end;
    return block;
}

