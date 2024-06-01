#ifndef __FRAMEBUFFER_HANDLER__
#define __FRAMEBUFFER_HANDLER__

#include "../include/libcpp.cpp"
#include "../include/types.h"
#include <stddef.h>

/* Hardware text mode color constants. */
typedef enum {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
} vga_color;

static inline char vga_entry_color(vga_color fg, vga_color bg)
{
    return fg | bg << 4;
}

static inline short vga_entry(unsigned char uc, char color)
{
    return (short)uc | (short)color << 8;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
char terminal_color;
short* terminal_buffer;

void update_cursor(int x, int y) // this belongs in terminal.cpp but we need to update cursor on write so it is forced to be here
{
    uint16_t pos = y * VGA_WIDTH + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void terminal_initialize(void)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    terminal_buffer = (short*)0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(char color)
{
    terminal_color = color;
}

void terminal_putentryat(char c, char color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_scroll()
{
    const size_t buffer_size = VGA_HEIGHT * VGA_WIDTH;
    memcpy(terminal_buffer, terminal_buffer + VGA_WIDTH, buffer_size * 2);
    const size_t last_row_offset = VGA_HEIGHT - 1;
    for (size_t x = 0; x < VGA_WIDTH; x++) {
        terminal_putentryat(' ', terminal_color, x, last_row_offset);
    }
}

// void terminal_scroll(int line)
// {
//     int loop;
//     char c;
//
//     for (loop = line * (VGA_WIDTH * 2) + 0xB8000; loop < VGA_WIDTH * 2; loop++) {
//         c = *loop;
//         *(loop - (VGA_WIDTH * 2)) = c;
//     }
// }

void terminal_putchar(char c)
{
    if (c == '\n') {
        if (terminal_row == VGA_HEIGHT) {
            terminal_scroll();
            terminal_column = 0;
            update_cursor(terminal_column, terminal_row);
        } else {
            terminal_row++;
            terminal_column = 0;
        }
    } else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            if (terminal_row == VGA_HEIGHT) {
                terminal_scroll();
            } else {
                terminal_row++;
            }
        }
    }
}

void terminal_write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
    update_cursor(terminal_column, terminal_row);
}

void terminal_writestring(const char* data)
{
    terminal_write(data, strlen(data));
}

#endif
