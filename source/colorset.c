#include "polyexterns.h"

PC_Color8 POLYCHROME_CALL GetARGBColorById(int32_t colorId) {
	if (colorId >= COLOR_ID_MAX) return BLACK;

	uint32_t color = color32List[colorId].color;
	return (PC_Color8){
		(color >> 24) & 0xFF,
		(color >> 16) & 0xFF,
		(color >> 8) & 0xFF,
		color & 0xFF
	};
}

void POLYCHROME_CALL SetARGBColorById(int32_t colorId, PC_Color8 color) {
	if (colorId >= COLOR_ID_MAX) return;

	uint32_t color32 = (color.a << 24) | (color.r << 16) | (color.g << 8) | color.b;
	color32List[colorId].color = color32;
	PatchSafe(base+color32List[colorId].addr,&color32List[colorId].color,4);
}

PC_Color8 POLYCHROME_CALL GetARGBColorByName(char* name) {
	for (int i = 0; i < COLOR_ID_MAX; i++) {
		if (strcmp(color32List[i].name ,name) == 0) {
			uint32_t color = color32List[i].color;
			return (PC_Color8){
				(color >> 24) & 0xFF,
				(color >> 16) & 0xFF,
				(color >> 8) & 0xFF,
				color & 0xFF
			};
		}
	}
	return BLACK;
}

void POLYCHROME_CALL SetARGBColorByName(char* name, PC_Color8 color) {
	uint32_t color32 = (color.a << 24) | (color.r << 16) | (color.g << 8) | color.b;
	for (int i = 0; i < COLOR_ID_MAX; i++) {
		if (strcmp(color32List[i].name ,name) == 0) {
			color32List[i].color = color32;
			PatchSafe(base+color32List[i].addr,&color32List[i].color,4);
			return;
		}
	}
	return;
}

const Polychrome_ColorsetApi _colorsetApi = {
	.size = sizeof(Polychrome_ColorsetApi),
	.version = POLYCHROME_API_VERSION_NUM,

	.GetARGBColorById = GetARGBColorById,
	.GetARGBColorByName = GetARGBColorByName,
	.SetARGBColorById = SetARGBColorById,
	.SetARGBColorByName = SetARGBColorByName
};

const Polychrome_ColorsetApi* GetColorsetApi() {
	return &_colorsetApi;
}
