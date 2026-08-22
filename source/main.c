#include "polyexterns.h"

static const Polychrome_Api _api = {
	sizeof(Polychrome_Api),
	POLYCHROME_API_VERSION_NUM,

	&_colorsetApi
};

const BaseMod_Api* _baseModApi;

BYTE *base;

uint32_t DoFiberExist;
uint32_t TensionBack;

void PatchSafe(void* address, void* data, size_t size) { //copied from patch.h, blame the compiler for being mean
    DWORD oldProtect;
    WINBOOL success = VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect);

    memcpy(address, data, size);

    success = VirtualProtect(address, size, oldProtect, &oldProtect);
}

__attribute__((naked)) void tensionStackOverride(void) {
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

void properCycleFix(void) {
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

void patchCycling(void) {
    int flag = 4;
    int limit = 6;
    PatchSafe(base+0x112803,&flag,1); //sets the flag to 4
	PatchSafe(base+0x112935,&limit,1); //sets raipal limit to 6 rows
	PatchSafe(base+0x1128ef,&limit,1); //sets firepal limit to 6 rows
}

void patch(void) {
	DoFiberExist = (uint32_t)base+0x103100;
    TensionBack = (uint32_t)base+0x1edc1a+5;

	char jump[5] = {0xE9};
	*(DWORD*)(jump+1) = (DWORD)tensionStackOverride - ((DWORD)(base+0x1edc1a) + 5);

    PatchSafe(base+0x1edc1a,jump,5);

	properCycleFix();
    patchCycling();

    printf("[Polychrome] Changes Applied\n");
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

	int32_t apiLoaded = api->RegisterApi(ctx, &_api, POLYCHROME_NAME, POLYCHROME_API_VERSION_SEM_VER);
	if (apiLoaded > 0) {
		printf("Polychrome API loading failed. Continuing... [%d]\n", apiLoaded);
	}
	
    loadSettings();
	reloadColors();
	patch();
    
    printf("[Polychrome] Let there be colors\n");
}


