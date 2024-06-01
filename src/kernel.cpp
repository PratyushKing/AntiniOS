#include "console/terminal.cpp"
#include "include/libcpp.cpp"
#include <stdbool.h>

extern "C" void kernel_main(void)
{
    init_terminal();
    clear_scr_with_color_and_fore(VGA_COLOR_BLUE, VGA_COLOR_YELLOW);
    terminal_writestring("Welcome to AntiniOS\n");
}
