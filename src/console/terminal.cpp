#ifndef __TERMINAL__
#define __TERMINAL__

#include "../include/libcpp.cpp"
#include "handler.cpp"

void init_terminal()
{
    terminal_initialize();
}

void write_str(char* str)
{
    terminal_writestring(str);
}

void write(char ch)
{
    terminal_putchar(ch);
}

void clear_scr()
{
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
    terminal_column = 0;
    terminal_row = 0;
    update_cursor(0, 0);
}

void clear_scr_with_color_and_fore(vga_color color, vga_color fore)
{
    terminal_color = vga_entry_color(fore, color);
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
    terminal_column = 0;
    terminal_row = 0;
    update_cursor(0, 0);
}

void clear_scr_with_color(vga_color color)
{
    clear_scr_with_color_and_fore(color, (vga_color)terminal_color);
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

uint16_t get_cursor_position(void)
{
    uint16_t pos = 0;
    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    pos |= ((uint16_t)inb(0x3D5)) << 8;
    return pos;
}

void disable_cursor()
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

#endif
