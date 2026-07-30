#include "gearLoader/gearLoader_c.h"
#include "baseMod/baseMod_c.h"
#include "polychrome.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

static const BaseMod_Api* _baseModApi;

BYTE *base;

uint32_t DoFiberExist;
uint32_t TensionBack;

uint32_t palSelect1 = 0;
uint32_t palSelect2 = 0;
uint32_t ed_glowtoggle = 1;
uint32_t pf_char = 1;
uint32_t pf_enable = 0;
uint32_t pf_list[26] = {0};

typedef struct {
    char* name;
    uint32_t* value;
} setting;

setting settings[] = {
    {"eddieGlow",&ed_glowtoggle},
    {"none_use6rows",&pf_list[0]},
    {"sl_use6rows",&pf_list[1]},{"ky_use6rows",&pf_list[2]},
    {"my_use6rows",&pf_list[3]},{"ml_use6rows",&pf_list[4]},
    {"ax_use6rows",&pf_list[5]},{"po_use6rows",&pf_list[6]},
    {"ch_use6rows",&pf_list[7]},{"ed_use6rows",&pf_list[8]},
    {"bk_use6rows",&pf_list[9]},{"fa_use6rows",&pf_list[10]},
    {"ts_use6rows",&pf_list[11]},{"jm_use6rows",&pf_list[12]},
    {"an_use6rows",&pf_list[13]},{"jy_use6rows",&pf_list[14]},
    {"ve_use6rows",&pf_list[15]},{"dz_use6rows",&pf_list[16]},
    {"sy_use6rows",&pf_list[17]},{"in_use6rows",&pf_list[18]},
    {"zp_use6rows",&pf_list[19]},{"yy_use6rows",&pf_list[20]},
    {"rk_use6rows",&pf_list[21]},{"ab_use6rows",&pf_list[22]},
    {"fr_use6rows",&pf_list[23]},{"kr_use6rows",&pf_list[24]},
    {"js_use6rows",&pf_list[25]},
};

color_range tensionColors[5] = {
    {.r1 = 0x1e, .g1 = 0x1e, .b1 = 0x69, 
     .r2 = 0x50, .g2 = 0x50, .b2 = 0xe6},
    {.r1 = 0x00, .g1 = 0x64, .b1 = 0x00, 
     .r2 = 0x00, .g2 = 0xdc, .b2 = 0x00},
    {.r1 = 0xdc, .g1 = 0x46, .b1 = 0x46, 
     .r2 = 0xfa, .g2 = 0xc3, .b2 = 0xc3},
    {.r1 = 0x96, .g1 = 0x50, .b1 = 0x96, 
     .r2 = 0xfa, .g2 = 0xc8, .b2 = 0xfa},
    {.r1 = 0x9b, .g1 = 0x78, .b1 = 0x37, 
     .r2 = 0xff, .g2 = 0xdc, .b2 = 0x69}
};

rgb_entry theEvilOnes[] = {
    {"Tension<25%_1",&tensionColors[0].r1,&tensionColors[0].g1,&tensionColors[0].b1},
    {"Tension<25%_2",&tensionColors[0].r2,&tensionColors[0].g2,&tensionColors[0].b2},
    {"Tension25%_1",&tensionColors[1].r1,&tensionColors[1].g1,&tensionColors[1].b1},
    {"Tension25%_2",&tensionColors[1].r2,&tensionColors[1].g2,&tensionColors[1].b2},
    {"Tension50%_1",&tensionColors[2].r1,&tensionColors[2].g1,&tensionColors[2].b1},
    {"Tension50%_2",&tensionColors[2].r2,&tensionColors[2].g2,&tensionColors[2].b2},
    {"Tension75%_1",&tensionColors[3].r1,&tensionColors[3].g1,&tensionColors[3].b1},
    {"Tension75%_2",&tensionColors[3].r2,&tensionColors[3].g2,&tensionColors[3].b2},
    {"Tension100%_1",&tensionColors[4].r1,&tensionColors[4].g1,&tensionColors[4].b1},
    {"Tension100%_2",&tensionColors[4].r2,&tensionColors[4].g2,&tensionColors[4].b2},
};

__attribute__((naked)) void detour() {
    __asm__ (
		".intel_syntax noprefix\n\t"
        "push eax\n\t"		
        //t10_0
        "mov eax,dword ptr [_tensionColors + 24*0 + 0]\n\t"
        "mov dword ptr [ebp + -0x1c],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*0 + 4]\n\t"
        "mov dword ptr [ebp + -0x30],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*0 + 8]\n\t"
        "mov dword ptr [ebp + -0x80],eax\n\t"
        //t10_1
        "mov eax,dword ptr [_tensionColors + 24*0 + 12]\n\t"
        "mov dword ptr [ebp + -0x6c],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*0 + 16]\n\t"
        "mov dword ptr [ebp + -0x58],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*0 + 20]\n\t"
        "mov dword ptr [ebp + -0x44],eax\n\t"
        //t25_0
        "mov eax,dword ptr [_tensionColors + 24*1 + 0]\n\t"
        "mov dword ptr [ebp + -0x18],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*1 + 4]\n\t"
        "mov dword ptr [ebp + -0x2c],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*1 + 8]\n\t"
        "mov dword ptr [ebp + -0x7c],eax\n\t"
        //t25_1
        "mov eax,dword ptr [_tensionColors + 24*1 + 12]\n\t"
        "mov dword ptr [ebp + -0x68],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*1 + 16]\n\t"
        "mov dword ptr [ebp + -0x54],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*1 + 20]\n\t"
        "mov dword ptr [ebp + -0x40],eax\n\t"
        //t50_0
        "mov eax,dword ptr [_tensionColors + 24*2 + 0]\n\t"
        "mov dword ptr [ebp + -0x14],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*2 + 4]\n\t"
        "mov dword ptr [ebp + -0x28],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*2 + 8]\n\t"
        "mov dword ptr [ebp + -0x78],eax\n\t"
        //t50_1
        "mov eax,dword ptr [_tensionColors + 24*2 + 12]\n\t"
        "mov dword ptr [ebp + -0x64],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*2 + 16]\n\t"
        "mov dword ptr [ebp + -0x50],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*2 + 20]\n\t"
        "mov dword ptr [ebp + -0x3c],eax\n\t"
        //t75_0
        "mov eax,dword ptr [_tensionColors + 24*3 + 0]\n\t"
        "mov dword ptr [ebp + -0x10],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*3 + 4]\n\t"
        "mov dword ptr [ebp + -0x24],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*3 + 8]\n\t"
        "mov dword ptr [ebp + -0x74],eax\n\t"
        //t75_1
        "mov eax,dword ptr [_tensionColors + 24*3 + 12]\n\t"
        "mov dword ptr [ebp + -0x60],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*3 + 16]\n\t"
        "mov dword ptr [ebp + -0x4c],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*3 + 20]\n\t"
        "mov dword ptr [ebp + -0x38],eax\n\t"
        //t100_0
        "mov eax,dword ptr [_tensionColors + 24*4 + 0]\n\t"
        "mov dword ptr [ebp + -0x0c],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*4 + 4]\n\t"
        "mov dword ptr [ebp + -0x20],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*4 + 8]\n\t"
        "mov dword ptr [ebp + -0x70],eax\n\t"
        //t100_1
        "mov eax,dword ptr [_tensionColors + 24*4 + 12]\n\t"
        "mov dword ptr [ebp + -0x5c],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*4 + 16]\n\t"
        "mov dword ptr [ebp + -0x48],eax\n\t"
        "mov eax,dword ptr [_tensionColors + 24*4 + 20]\n\t"
        "mov dword ptr [ebp + -0x34],eax\n\t"
        "pop eax\n\t"
		"call [%0]\n\t"
        "jmp [%1]\n\t"
		".att_syntax prefix\n\t"
		:
		: "m"(DoFiberExist), 
          "m"(TensionBack)
	);
}

void PatchSafe(void* address, void* data, size_t size) { //copied from patch.h, blame the compiler for being mean
    DWORD oldProtect;
    WINBOOL success = VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect);

    memcpy(address, data, size);

    success = VirtualProtect(address, size, oldProtect, &oldProtect);
}

void ProperCycleFix() {
    int loop_count = 4;
    int short_jump = 8;
    int big_jump = 16;
    char cycle_nops[57] = {0};

	for (int i = 0; i < 57; i++) {
		cycle_nops[i] = 0x90; 
	}
	
	PatchSafe(base+0x1079bc,&loop_count,4);
	PatchSafe(base+0x107ade,&short_jump,1);
	PatchSafe(base+0x107ae1,&big_jump,1);
	PatchSafe(base+0x107aa3,cycle_nops,57);
}

__attribute__ ((stdcall)) void Patch() {
    DoFiberExist = (uint32_t)base+0x103100;
    TensionBack = (uint32_t)base+0x1edc1a+5;

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
                for (int i = 0; i < (sizeof(theEvilOnes)/RGB_ENTRY_SIZE); i++) {
                    if (strcmp(name,theEvilOnes[i].name) == 0) {
                        *theEvilOnes[i].r = (color >> 16) & 0xFF;
                        *theEvilOnes[i].g = (color >> 8) & 0xFF;
                        *theEvilOnes[i].b = color & 0xFF;
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

	char jump[5] = {0xE9};
	*(DWORD*)(jump+1) = (DWORD)detour - ((DWORD)(base+0x1edc1a) + 5);

    PatchSafe(base+0x1edc1a,jump,5);

    printf("[Polychrome] Changes Applied\n");
    return;
}

__attribute__ ((stdcall)) void EdGlowToggle() {
    uint32_t disable = 0;
    uint32_t position = 5;
    uint32_t length = 0x10070605;
    if (ed_glowtoggle == 1) {
        PatchSafe(base+0x22C6E4,&position,1);
        PatchSafe(base+0x22C6BA,&length,4);
    } else {
        PatchSafe(base+0x22C6E4,&disable,1);
        PatchSafe(base+0x22C6BA,&disable,4);
    }
}

void PatchCycling() {
    int flag = 4;
    int limit = 6;
    PatchSafe(base+0x112803,&flag,1); //sets the flag to 4
	PatchSafe(base+0x112935,&limit,1); //sets raipal limit to 6 rows
	PatchSafe(base+0x1128ef,&limit,1); //sets firepal limit to 6 rows
}

__attribute__ ((stdcall)) void updateFixOption() {
    pf_enable = pf_list[pf_char];
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

    pf_list[pf_char] = pf_enable;

    if (pf_char < 6) {
        PatchSafe(base+offsetsByIdno[pf_char],&fix1[pf_enable],1);
    } else {
        PatchSafe(base+offsetsByIdno[pf_char],&fix2[pf_enable],1);
    }
}

__attribute__ ((stdcall)) void SwapPalP1() {
    uint16_t p = (uint16_t)palSelect1;
    PatchSafe(base+0x6d6414,&p,2);

    GGXXACPR_Entity *p1;
    p1 = _baseModApi->GameData->GetPlayer(0);

    if (p1 != NULL) {
        uint32_t sendPal = (uint32_t)base+0x13c830;
        __asm__ (
		    ".intel_syntax noprefix\n\t"
            "push %0\n\t"
            "call %1\n\t"
            "add esp,0x4\n\t"
		    ".att_syntax prefix\n\t"
		    :
		    : "r"(p1),
              "r"(sendPal)
	    );
    }
}

__attribute__ ((stdcall)) void SwapPalP2() {
    uint16_t p = (uint16_t)palSelect2;
    PatchSafe(base+0x6d6416,&p,2);

    GGXXACPR_Entity *p2;
    p2 = _baseModApi->GameData->GetPlayer(1);

    if (p2 != NULL) {
        uint32_t sendPal = (uint32_t)base+0x13c830;
        __asm__ (
		    ".intel_syntax noprefix\n\t"
            "push %0\n\t"
            "call %1\n\t"
            "add esp,0x4\n\t"
		    ".att_syntax prefix\n\t"
		    :
		    : "r"(p2),
              "r"(sendPal)
	    );
    }
}

__attribute__ ((stdcall)) void saveSettings() {
    FILE *fptr = fopen("mods/Polychrome/settings.txt","w");
    for (int i = 0; i < 27; i++) {
        fprintf(fptr,"%s:%d\n",settings[i].name,*settings[i].value);
    }
    fclose(fptr);
}

void loadSettings() {
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
                for (int i = 0; i < 27; i++) {
                    if (strcmp(name,settings[i].name) == 0) {
                        *settings[i].value = strtoul(value,NULL,10);
                    }
                }    
            }
        }
        fclose(fptr);
        EdGlowToggle();
        for (int i = 0; i < 26; i++) {
            pf_char = i;
            pf_enable = pf_list[pf_char];
            useSix();
        }
        pf_char = 1;
        pf_enable = pf_list[pf_char];
    }
}

GEARLOADER_EXPORT void GEARLOADER_CALL Init(GearLoaderContext* ctx, GearLoaderApi* api) {
    base = (BYTE *)GetModuleHandle(NULL);

    const void* retApi;
    SemanticVersion retVer;
    int32_t result = api->RetrieveModApi(ctx,BASEMOD_NAME,BASEMOD_API_VERSION,&retApi,&retVer);

    if (result != 0) {
        printf("BaseMod loading failed for Polychrome (X) - result = %d\n", result);
        return;
    }

    _baseModApi = (const BaseMod_Api*)retApi;
    loadSettings();
	Patch();
    ProperCycleFix();
    PatchCycling();
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
        {"Change P1 Palette",&palSelect1,0,21,palSlots,NULL,SwapPalP1},
        {"Change P2 Palette",&palSelect2,0,21,palSlots,NULL,SwapPalP2},
        {"Eddie Glow",&ed_glowtoggle,0,1,toggle,NULL,EdGlowToggle},
        {"Cycling Palette Fix",&pf_char,1,25,charById,NULL,updateFixOption},
        {"    Use 6 Rows",&pf_enable,0,1,toggle,NULL,useSix},
        {"Reload Colors",NULL,0,0,NULL,Patch,NULL},
        {"Save Settings",NULL,0,0,NULL,saveSettings,NULL}
    };
    _baseModApi->ModMenu->RegisterMenuTab("POLYCHROME",menuEntry,7);
    printf("[Polychrome] Let there be colors\n");
}


