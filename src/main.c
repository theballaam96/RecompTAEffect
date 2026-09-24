#include "modding.h"
#include "ultra64.h"
#include "enums.h"
#include "common_structs.h"

typedef struct {
    s32 id;
    u8 images_per_frame_horizontal;
    u8 images_per_frame_vertical;
    u8 unk6;
    u8 codec;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 table;
    s16 width;
    s16 height;
    s16 image_count;
    s16 images[1]; // TODO: How many elements? m2c doesn't support VLAs
} SpriteData;

s8 ta_timer = -1;
u8 sparkle_index = 0;

extern SpriteData D_global_asm_8071FC8C;
extern SpriteData D_global_asm_8071FCC0;
extern SpriteData D_global_asm_8071FC58;
extern Actor *gCurrentPlayer;
void func_global_asm_8071498C(void *arg0);
void func_global_asm_80717D4C(Struct80717D84 *arg0, s32 arg1);
void func_global_asm_807149B8(u8 arg0);
void func_global_asm_80714950(s32 arg0);
f32 func_global_asm_80612790(s16 arg0);
f32 func_global_asm_80612794(s16 arg0);
Struct80717D84 *drawSpriteAtPosition(void *sprite, f32 scale, f32 x, f32 y, f32 z);
s16 playSound(s16 arg0, s32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5);
void changeActorColor(u8 red, u8 green, u8 blue, u8 alpha);

static SpriteData *ta_sprites[] = {
    &D_global_asm_8071FC8C,
    &D_global_asm_8071FC8C, // Diddy Placeholder
    &D_global_asm_8071FC8C, // Lanky Placeholder
    &D_global_asm_8071FC58,
    &D_global_asm_8071FCC0,
};
static s16 sfxs[] = {
    560, 103, 218, 182, 198
};

RECOMP_CALLBACK("dk64_tag_anywhere", recomp_on_tag_anywhere_tag) void taeffect_on_ta(u8 old, u8 new) {
    ta_timer = 0;
    sparkle_index = 0;
    if (new < 5) {
        sparkle_index = new;
    }
    playSound(sfxs[sparkle_index], 0x4FFF, 63.0f, 1.0f, 0, 0);
}

RECOMP_CALLBACK("*", dk64recomp_every_frame) void taeffect_everyframe(void){
    s32 r;
    s32 i, j;
    f32 x, y, z;

    if (ta_timer < 0) {
        return;
    }
    if (ta_timer > 7) {
        ta_timer = -1;
        return;
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            func_global_asm_8071498C(func_global_asm_80717D4C);
            func_global_asm_807149B8(1);
            r = RANDNUM();
            func_global_asm_80714950(((r >> 0xF) % 10000) % 120 + 80);
            x = gCurrentPlayer->x_position + (10.0f * func_global_asm_80612794(((ta_timer + (i * 2)) * 512) & 0xFFF));
            y = gCurrentPlayer->y_position + 10.0f;
            z = gCurrentPlayer->z_position + (10.0f * func_global_asm_80612790(((ta_timer + (i * 2)) * 512) & 0xFFF));
            if (sparkle_index == 1) {
                // Diddy
                changeActorColor(0xFF, 0x00, 0x00, 0xFF);
            } else if (sparkle_index == 2) {
                // Lanky
                changeActorColor(0x16, 0x99, 0xFF, 0xFF);
            }
            drawSpriteAtPosition(ta_sprites[sparkle_index], 0.6f, x, y, z);
        }
    }
    ta_timer++;
}