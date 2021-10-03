#include "kernel.h"
#include <stddef.h>
#include <stdint.h>


uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t terminal_make_char(char c, char colour)
{
    return (colour << 8) | c;
}

void terminal_putchar(int x, int y, char c, char colour)
{
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c , colour);
}

void terminal_writechar(char c, char colour)
{
    terminal_putchar(terminal_col, terminal_row, c ,colour);
    terminal_col += 1;
    if (terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }
}
void terminal_initialize()
{
    video_mem = (uint16_t *)(0xB8000);
    terminal_row = 0;
    terminal_col = 0;
    for (int i = 0; i < VGA_HEIGHT; i++)
    {
        for (int j = 0; j < VGA_WIDTH; i++)
        {
            terminal_putchar(j, i, ' ', 0);
        }
    }

}

size_t strlen(const char* str)
{
    size_t len = 0;
    while(str[len])
    {
        len++;
    }

    return len;
}

void print(const char *str)
{
    size_t len = 0;
    for (int i = 0; i < len; i++)
    {
        terminal_writechar(str[i], 15);
    }
}


void kernel_main()
{
    terminal_initialize();

    print("Hello World!");
}
