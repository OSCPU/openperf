#include <stddef.h>
#include <stdint.h>
size_t utf8enc(unsigned char *, uint32_t);
size_t utf8dec(uint32_t *, const unsigned char *, size_t);
size_t utf16enc(uint16_t *, uint32_t);
