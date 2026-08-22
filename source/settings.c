#include <stdbool.h>

#include "polyexterns.h"
#include "gearLoader/ggxxacpr_c.h"

#define SETTINGS_COUNT 27

uint32_t p1PaletteSelect = 0;
uint32_t p2PaletteSelect = 0;
uint32_t paletteFixCharacter = ENTITY_ID_SOL;
uint32_t paletteFixList[26] = {0};
uint32_t paletteFixEnable = 0;
uint32_t toggleEddieGlow = 1;

setting settings[SETTINGS_COUNT] = {
    {"eddieGlow",    &toggleEddieGlow},
    {"none_use6rows",&paletteFixList[ENTITY_ID_NONE]},
    {"sl_use6rows",  &paletteFixList[ENTITY_ID_SOL]},
	{"ky_use6rows",  &paletteFixList[ENTITY_ID_KY]},
    {"my_use6rows",  &paletteFixList[ENTITY_ID_MAY]},
	{"ml_use6rows",  &paletteFixList[ENTITY_ID_MILLIA]},
    {"ax_use6rows",  &paletteFixList[ENTITY_ID_AXL]},
	{"po_use6rows",  &paletteFixList[ENTITY_ID_POTEMKIN]},
    {"ch_use6rows",  &paletteFixList[ENTITY_ID_CHIPP]},
	{"ed_use6rows",  &paletteFixList[ENTITY_ID_EDDIE]},
    {"bk_use6rows",  &paletteFixList[ENTITY_ID_BAIKEN]},
	{"fa_use6rows",  &paletteFixList[ENTITY_ID_FAUST]},
    {"ts_use6rows",  &paletteFixList[ENTITY_ID_TESTAMENT]},
	{"jm_use6rows",  &paletteFixList[ENTITY_ID_JAM]},
    {"an_use6rows",  &paletteFixList[ENTITY_ID_ANJI]},
	{"jy_use6rows",  &paletteFixList[ENTITY_ID_JOHNNY]},
    {"ve_use6rows",  &paletteFixList[ENTITY_ID_VENOM]},
	{"dz_use6rows",  &paletteFixList[ENTITY_ID_DIZZY]},
    {"sy_use6rows",  &paletteFixList[ENTITY_ID_SLAYER]},
	{"in_use6rows",  &paletteFixList[ENTITY_ID_I_NO]},
    {"zp_use6rows",  &paletteFixList[ENTITY_ID_ZAPPA]},
	{"yy_use6rows",  &paletteFixList[ENTITY_ID_BRIDGET]},
    {"rk_use6rows",  &paletteFixList[ENTITY_ID_ROBO_KY]},
	{"ab_use6rows",  &paletteFixList[ENTITY_ID_ABA]},
    {"fr_use6rows",  &paletteFixList[ENTITY_ID_ORDER_SOL]},
	{"kr_use6rows",  &paletteFixList[ENTITY_ID_KLIFF]},
    {"js_use6rows",  &paletteFixList[ENTITY_ID_JUSTICE]},
};

__attribute__ ((stdcall)) void eddieGlowToggle() {
    uint32_t disable = 0;
    uint32_t position = 5;
    uint32_t length = 0x10070605;
    if (toggleEddieGlow == true) {
        PatchSafe(base+0x22C6E4,&position,1);
        PatchSafe(base+0x22C6BA,&length,4);
    } else {
        PatchSafe(base+0x22C6E4,&disable,1);
        PatchSafe(base+0x22C6BA,&disable,4);
    }
}

__attribute__ ((stdcall)) void updateFixOption() {
    paletteFixEnable = paletteFixList[paletteFixCharacter];
}

__attribute__ ((stdcall)) void useSix() {
    int fix1[2] = {0x44,0x7C};
    int fix2[2] = {0x84,0xBC};

    uint32_t offsetsByIdno[26] = {
        0x11280a,0x11280e,0x112812,0x112816,0x11281a,
        0x11281e,0x112822,0x112829,0x112830,0x112837,
        0x11283e,0x112845,0x11284c,0x112853,0x11285a,
        0x112861,0x112868,0x11286f,0x112876,0x11287d,
        0x112884,0x11288b,0x112892,0x112899,0x1128a0,
        0x1128a7
    };

    paletteFixList[paletteFixCharacter] = paletteFixEnable;

    if (paletteFixCharacter < 6) {
        PatchSafe(base+offsetsByIdno[paletteFixCharacter],&fix1[paletteFixEnable],1);
    } else {
        PatchSafe(base+offsetsByIdno[paletteFixCharacter],&fix2[paletteFixEnable],1);
    }
}

void swapPalette(int player) {
	uint16_t palette;
	GGXXACPR_Entity *playerEntityPtr;

	playerEntityPtr = _baseModApi->GameData->GetPlayer(player);

	if (player == 0) {
		palette = p1PaletteSelect;
		PatchSafe(base+0x6d6414,&palette,2);
	} else {
		palette = p2PaletteSelect;
		PatchSafe(base+0x6d6416,&palette,2);
	}

	if (playerEntityPtr != NULL) {
		uint32_t sendPalette = (uint32_t)base+0x13c830;
		__asm__ (
			".intel_syntax noprefix\n\t"
		    "push %0\n\t"
		    "call %1\n\t"
		    "add esp,0x4\n\t"
			".att_syntax prefix\n\t"
			:
			: "r"(playerEntityPtr),
		      "r"(sendPalette)
		);
	}
}

__attribute__ ((stdcall)) void swapPaletteP1() {
    swapPalette(0);
}

__attribute__ ((stdcall)) void swapPaletteP2() {
	swapPalette(1);
}

__attribute__ ((stdcall)) void reloadColors() {
    FILE *fptr = fopen("mods/Polychrome/colors.txt","r");
    if (!fptr) {
        printf("[Polychrome] colors.txt not found in mods folder. Trying Mods.\n");
        fptr = fopen("Mods/Polychrome/colors.txt","r");
        if (!fptr) {
            printf("[Polychrome] colors.txt not found in Mods folder.\n");
            return;
        }
    }

    char line[256];
    char type[256];

    while (fgets(line, sizeof(line), fptr)) {
        char name[64];
        char colorhex[16];
        char *unhash;

        if (line[0] == '/' || line[0] == '\n') {
            continue;
        } else if (line[0] == '#') {
            strcpy(type,line);
            continue;
        }

        if (sscanf(line," %63[^:] : #%15s", name, colorhex) == 2) {
            unhash = colorhex;
            if (*unhash == '#') {
                unhash++;
            }    
            uint32_t color = strtoul(unhash,NULL,16);

            if (strcmp(type,"#RGB\n") == 0) {
                for (int i = 0; i < (sizeof(tensionRanges)/RGB_ENTRY_SIZE); i++) {
                    if (strcmp(name,tensionRanges[i].name) == 0) {
                        *tensionRanges[i].r = (color >> 16) & 0xFF;
                        *tensionRanges[i].g = (color >> 8) & 0xFF;
                        *tensionRanges[i].b = color & 0xFF;
                        continue;
                    }
                }
            } else if (strcmp(type,"#ARGB\n") == 0) {
                for (int i = 0; i < (sizeof(color32List)/COLOR_ENTRY_SIZE); i++) {
                    if (strcmp(name,color32List[i].name) == 0) {
                        color32List[i].color = color;
                        PatchSafe(base+color32List[i].addr,&color32List[i].color,4);
                        continue;
                    }
                }
            } else if (strcmp(type,"#RGB5\n") == 0) {
                continue;
            }
        }
    }
    fclose(fptr);
    return;
}

__attribute__ ((stdcall)) void restoreDefaults() {
	for (int i = 0; i < (sizeof(color32List)/COLOR_ENTRY_SIZE); i++) {
        color32List[i].color = color32List[i].original;
        PatchSafe(base+color32List[i].addr,&color32List[i].color,4);  
    }
}

__attribute__ ((stdcall)) void saveSettings() {
    FILE *fptr = fopen("mods/Polychrome/settings.txt","w");
    for (int i = 0; i < SETTINGS_COUNT; i++) {
        fprintf(fptr,"%s:%d\n",settings[i].name,*settings[i].value);
    }
    fclose(fptr);
}

void loadSettings(void) {
    FILE *fptr = fopen("mods/Polychrome/settings.txt","r");
    if (fptr != NULL) {
        char line[256];

        while (fgets(line, sizeof(line), fptr)) {
            char name[64];
            char value[8];

            if (line[0] == '/' || line[0] == '\n') {
                continue;
            }

            if (sscanf(line," %63[^:] : %8s", name, value) == 2) {
                for (int i = 0; i < SETTINGS_COUNT; i++) {
                    if (strcmp(name,settings[i].name) == 0) {
                        *settings[i].value = strtoul(value,NULL,10);
                    }
                }    
            }
        }
        fclose(fptr);
        eddieGlowToggle();
        for (int i = 0; i < 26; i++) {
            paletteFixCharacter = i;
            paletteFixEnable = paletteFixList[paletteFixCharacter];
            useSix();
        }
        paletteFixCharacter = ENTITY_ID_SOL;
        paletteFixEnable = paletteFixList[paletteFixCharacter];
    }
}

void createSettingsMenu(void) {
	static const char *toggle[2] = {"NO","YES"};
    static const char *palSlots[22] = {
        "P","K","S","HS","D",
        "EX.P","EX.K","EX.S","EX.HS","EX.D",
        "SLS.P","SLS.K","SLS.S","SLS.HS","GOLD",
        "REL.P","REL.K","REL.S","REL.HS","SHADOW",
        "SLS.D","REL.D"
    };
    static const char *charById[26] = {
        "NONE","SOL","KY","MAY","MILLIA","AXL","POTEMKIN",
        "CHIPP","EDDIE","BAIKEN","FAUST","TESTAMENT","JAM",
        "ANJI","JOHNNY","VENOM","DIZZY","SLAYER","I-NO",
        "ZAPPA","BRIDGET","ROBO-KY","A.B.A","ORDER-SOL",
        "KLIFF","JUSTICE"
    };
    static BaseMod_ModMenuEntry menuEntry[7] = {
        {"Change P1 Palette",  &p1PaletteSelect,    0,21,palSlots,NULL,swapPaletteP1},
        {"Change P2 Palette",  &p2PaletteSelect,    0,21,palSlots,NULL,swapPaletteP2},
        {"Eddie Glow",         &toggleEddieGlow,    0, 1,toggle,  NULL,eddieGlowToggle},
        {"Cycling Palette Fix",&paletteFixCharacter,1,25,charById,NULL,updateFixOption},
        {"    Use 6 Rows",     &paletteFixEnable,   0, 1,toggle,  NULL,useSix},
        {"Reload Colors",      NULL,0,0,NULL,reloadColors,   NULL},
		{"Restore Defaults",   NULL,0,0,NULL,restoreDefaults,NULL},
        {"Save Settings",      NULL,0,0,NULL,saveSettings,   NULL}
    };
    _baseModApi->ModMenu->RegisterMenuTab("POLYCHROME",menuEntry,7);
}
