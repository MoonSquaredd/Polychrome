#ifndef POLYCHROME
#define POLYCHROME

#define POLYCHROME_VERSION 0x000201

#include <stdint.h>

typedef struct {
    char* name;
    uint32_t color;
    uint32_t addr;
    uint32_t original;
} color_entry;
#define COLOR_ENTRY_SIZE 16

typedef struct {
    uint32_t r1;
    uint32_t g1;
    uint32_t b1;

    uint32_t r2;
    uint32_t g2;
    uint32_t b2;
} color_range;

typedef struct {
    char* name;
    uint32_t* r;
    uint32_t* g;
    uint32_t* b;
} rgb_entry;
#define RGB_ENTRY_SIZE 16

extern color_entry color32List[128];

#endif
