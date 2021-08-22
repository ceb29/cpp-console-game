#include "screen.h"

Screen::Screen(void) {
    buffer_data = 0;
    char_buffer = new wchar_t[screen_mult];
    buffer_coord = { 0, 0 };
    buff_ind = 121;
    index_plus = 0;
    h_screen_buffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
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
            char_buffer[i] = ' ';
        }
        else {
            char_buffer[i] = char_border;
        }
    }
}

void Screen::start(void) {
    border();
    SetConsoleActiveScreenBuffer(h_screen_buffer);
    WriteConsoleOutputCharacter(h_screen_buffer, char_buffer, screen_mult, buffer_coord, &buffer_data);
}

void Screen::write(void) {
    WriteConsoleOutputCharacter(h_screen_buffer, char_buffer, screen_mult, buffer_coord, &buffer_data);
}

void Screen::test1(Game_Time g_time) {
    if (g_time.get_millis() >= 1) {
        if (char_buffer[buff_ind] != '-') {
            char_buffer[buff_ind] = 'a' + index_plus;
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
        if (char_buffer[buff_ind] != '-') {
            char_buffer[buff_ind] = 'a' + index_plus;
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