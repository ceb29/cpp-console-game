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
}

Screen::~Screen(void) {
    delete[] char_buffer;
}

HANDLE Screen::get_handle(void) {
    return h_screen_buffer;
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
    set_font();
    set_size();
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

SMALL_RECT Screen::test_write_console_output(SMALL_RECT x) {
    CHAR_INFO char_inf[200];
    for (int i = 0; i < 200; i++) {
        char_inf[i].Char.UnicodeChar = L' ';
        char_inf[i].Attributes = FOREGROUND_BLUE;
    }
    WriteConsoleOutput(h_screen_buffer, char_inf, { 20, 10 }, { 0, 0 }, &x);
    x.Left += 1;
    x.Right = screen_width;
    x.Top += 1;
    x.Bottom = screen_height;
    for (int i = 0; i < 200; i++) {
        char_inf[i].Char.UnicodeChar = L' ';
        char_inf[i].Attributes = BACKGROUND_RED;
    }
    WriteConsoleOutput(h_screen_buffer, char_inf, { 20, 10 }, { 0, 0 }, &x);
    return x;
}

CONSOLE_FONT_INFOEX Screen::get_font(void) {
    CONSOLE_FONT_INFOEX text_1;
    text_1.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(h_screen_buffer, FALSE, &text_1);
    return text_1;
}

void Screen::set_font(void) {
    CONSOLE_FONT_INFOEX text;
    text = get_font();
    int x = text.dwFontSize.X;
    int y = text.dwFontSize.Y;
    text.dwFontSize.X = fontx;
    text.dwFontSize.Y = fonty;
    SetCurrentConsoleFontEx(h_screen_buffer, FALSE, &text);
}

void Screen::set_size(void) {
    SMALL_RECT a;
    a.Left = 0;
    a.Right = screen_width-1;
    a.Top = 0;
    a.Bottom = screen_height-1;
    SetConsoleScreenBufferSize(h_screen_buffer, {screen_width, screen_height});
    SetConsoleWindowInfo(h_screen_buffer, TRUE, &a);
}