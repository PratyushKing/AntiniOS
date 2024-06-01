#include "console/terminal.cpp"
#include "include/libcpp.cpp"
#include <stdbool.h>

extern "C" void kernel_main(void)
{
    init_terminal();
    terminal_setcolor(VGA_COLOR_GREEN);
    clear_scr_with_color(VGA_COLOR_BLUE);
    terminal_writestring("Hello, AntiniOS!\n");
}
