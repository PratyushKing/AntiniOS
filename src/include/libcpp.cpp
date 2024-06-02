#ifndef __GENERAL_LIB_CPP__
#define __GENERAL_LIB_CPP__

#include <stddef.h>
#include <stdint.h>

void outb(unsigned short port, unsigned char val)
{
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
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
    char* buffer = nullptr;
    if (value < 0) {
        value = -value;
        uint_to_string((uint32_t)value, buffer + 1, strlen(buffer) - 1);
        buffer[0] = '-';
    } else {
        uint_to_string((uint32_t)value, buffer, strlen(buffer));
    }
    return buffer;
}

extern "C" {

void *memcpy(void *dest, const void *src, size_t n) {
    uint8_t *pdest = static_cast<uint8_t *>(dest);
    const uint8_t *psrc = static_cast<const uint8_t *>(src);

    for (size_t i = 0; i < n; i++) {
        pdest[i] = psrc[i];
    }

    return dest;
}

void *memset(void *s, int c, size_t n) {
    uint8_t *p = static_cast<uint8_t *>(s);

    for (size_t i = 0; i < n; i++) {
        p[i] = static_cast<uint8_t>(c);
    }

    return s;
}

void *memmove(void *dest, const void *src, size_t n) {
    uint8_t *pdest = static_cast<uint8_t *>(dest);
    const uint8_t *psrc = static_cast<const uint8_t *>(src);

    if (src > dest) {
        for (size_t i = 0; i < n; i++) {
            pdest[i] = psrc[i];
        }
    } else if (src < dest) {
        for (size_t i = n; i > 0; i--) {
            pdest[i-1] = psrc[i-1];
        }
    }

    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const uint8_t *p1 = static_cast<const uint8_t *>(s1);
    const uint8_t *p2 = static_cast<const uint8_t *>(s2);

    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }

    return 0;
}

}

void E9WriteString(const char* str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
        outb(0xE9, str[i]);
}

#endif
