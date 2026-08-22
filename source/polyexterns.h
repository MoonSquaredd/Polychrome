#ifndef POLYEXTERNS
#define POLYEXTERNS

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <windows.h>

#include "polychrome_c.h"
#include "gearLoader/gearLoader_c.h"
#include "baseMod/baseMod_c.h"

#define POLYCHROME_VERSION "0.3.0"
#define POLYCHROME_VERSION_NUM 0x000300
#define POLYCHROME_VERSION_SEM_VER ((SemanticVersion){0,3,0})

#define POLYCHROME_API_VERSION "0.1.0"
#define POLYCHROME_API_VERSION_NUM 0x000100
#define POLYCHROME_API_VERSION_SEM_VER ((SemanticVersion){0,1,0})

#define COLOR_ID_MAX 128

typedef struct {
    char* name;
    uint32_t* value;
} setting;
#define SETTING_SIZE 8

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
#define COLOR_RANGE_SIZE 24

typedef struct {
    char* name;
    uint32_t* r;
    uint32_t* g;
    uint32_t* b;
} rgb_entry;
#define RGB_ENTRY_SIZE 16

extern const BaseMod_Api* _baseModApi;

extern BYTE* base;

extern setting settings[];
extern color_range tensionColors[5];
extern rgb_entry tensionRanges[10];
extern color_entry color32List[COLOR_ID_MAX];

extern void PatchSafe(void*,void*,size_t);

//api
extern const Polychrome_ColorsetApi _colorsetApi;

//settings
extern void __stdcall reloadColors(void);
extern void loadSettings(void);
extern void createSettingsMenu(void);

#endif
