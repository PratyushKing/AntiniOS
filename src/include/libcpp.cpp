#ifndef __GENERAL_LIB_CPP__
#define __GENERAL_LIB_CPP__

#include <stddef.h>
#include <stdint.h>
#include <cstring>

void outb(unsigned short port, unsigned char val)
{
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile("inb %w1, %b0"
                     : "=a"(ret)
                     : "Nd"(port)
                     : "memory");
    return ret;
}

void uint_to_string(uint32_t value, char* buffer, uint32_t buffer_size)
{
    // idk what this code is but i have been manually debugging it and now it works..
    uint32_t temp = value;
    uint32_t digits = 0;

    do {
        temp /= 10;
        digits++;
    } while (temp);

    if (digits + 1 > buffer_size) {
        return;
    }
    buffer[digits] = '\0';
    do {
        buffer[--digits] = '0' + value % 10;
        value /= 10;
    } while (value);
}

void int_to_string(int value, char* buffer, uint32_t buffer_size)
{
    if (value < 0) {
        value = -value;
        uint_to_string((uint32_t)value, buffer + 1, buffer_size - 1);
        buffer[0] = '-';
    } else {
        uint_to_string((uint32_t)value, buffer, buffer_size);
    }
}

char* ret_int_to_string(int value)
{
    char* buffer = "";
    if (value < 0) {
        value = -value;
        uint_to_string((uint32_t)value, buffer + 1, strlen(buffer) - 1);
        buffer[0] = '-';
    } else {
        uint_to_string((uint32_t)value, buffer, strlen(buffer));
    }
    return buffer;
}

void DebugString(const char* str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
        outb(0xE9, str[i]);
}

#endif
