#include <windows.h>
#include <iostream>
#include <time.h>

void screen_border(wchar_t*, int, int, int);

int main(void)
{
    //variables for game clock
    unsigned long long int seconds = 0;
    clock_t timer;
    float clock_millis;
    //variables for console screen buffer
    const int screen_width = 120;
    const int screen_height = 30;
    const int screen_mult = screen_width * screen_height;
    HANDLE h_screen_buffer;
    DWORD buffer_data = 0;
    wchar_t char_buffer[screen_mult];
    COORD buffer_coord = { 0, 0 };
    int char_buffer_ind = 122;
    //setup console screen buffer
    screen_border(char_buffer, screen_width, screen_height, screen_mult);
    h_screen_buffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(h_screen_buffer);
    WriteConsoleOutputCharacter(h_screen_buffer, char_buffer, screen_mult, buffer_coord, &buffer_data);
    timer = clock();
    //start main loop (exit if esc key is pressed)
    while (GetAsyncKeyState(VK_ESCAPE) == 0) {
        clock_millis = ((float)(clock() - timer)) / CLOCKS_PER_SEC;
        if (clock_millis >= 1) {
            timer = clock();
            seconds++;
            char_buffer[char_buffer_ind] = 'x';
            if (char_buffer_ind > screen_width - screen_height) {
                char_buffer_ind++;
            }
        }
        WriteConsoleOutputCharacter(
            h_screen_buffer, char_buffer, screen_mult, buffer_coord, &buffer_data);
    }
    return 0;
}

void screen_border(wchar_t* char_buff, int width, int height, int mult) {
    wchar_t char_border = '-';
    for (int i = 0; i < mult; i++) {
        if (i < width || i % width == 0 || i % width == width - 1) {
            char_buff[i] = char_border;
        }
        else if (i < mult - width) {
            char_buff[i] = ' ';
        }
        else {
            char_buff[i] = char_border;
        }
    }
}