#include <windows.h>
#include <iostream>
//include <stdio.h>

int main(void)
{
    const int screen_width = 120;
    const int screen_height = 30;
    const int screen_mult = screen_width * screen_height;
    HANDLE h_screen_buffer;
    DWORD D_test = 0;
    wchar_t char_buffer[screen_mult];
    COORD Buf_Coord = { 0, 0};
    wchar_t char_border = '-';

    for (int i = 0; i < screen_mult; i++) {
        if (i < screen_width || i % screen_width == 0 || i % screen_width == screen_width - 1) {
            char_buffer[i] = char_border;
        }
        else if (i < screen_mult - screen_width){
            char_buffer[i] = ' ';
        }
        else {
            char_buffer[i] = char_border;
        }
    }

    h_screen_buffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    SetConsoleActiveScreenBuffer(h_screen_buffer);

    WriteConsoleOutputCharacter(
        h_screen_buffer, char_buffer, screen_mult, Buf_Coord, &D_test);

    while (GetAsyncKeyState(VK_ESCAPE) == 0) {
        WriteConsoleOutputCharacter(
            h_screen_buffer, char_buffer, screen_mult, Buf_Coord, &D_test);

    }

    return 0;
}