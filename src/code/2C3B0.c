#include "common.h"

typedef struct unk80176840 {
    char unk_00[0x10];
} unk80176840;

u8 D_80176820;
u8 D_80176821;
u8 D_80176822;
u8 D_80176823;
s32 D_80176824;
s32 D_80176828;
s32 D_8017682C;
s32 gMultiplayerBGM;
s32 D_80176834;
s32 D_80176838;
s32 D_8017683C;
unk80176840 D_80176840;


typedef struct unk800FE564 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} unk800FE564;


extern unk800FE564 D_800FE564[];

void func_8005456C(f32, f32, f32, f32, f32, s32);
void func_80073090(void);
s32 func_8008BE14(void);
void func_800A0D90(void);
void func_800678EC(s32, s32, s32, s32, s32);
void func_80058BE4(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7);
void func_800536D8(void);
void func_80059F28(f32, f32, f32, f32, f32, f32, f32, f32, s32);

extern s32 D_800F0B58;
extern s32 D_800F0B5C;
extern s32 D_800F0B68[4][4];
extern s32 D_800F0BC0[4];
extern s32 D_800F0BD0[4];
extern s32 D_800FE404;
extern s32 D_800FE708;
extern s32 D_800FE74C;
extern s32 D_80168EBC;
extern s32 D_80168EC0;
extern s32 D_80168FEC;
extern s32 D_80168FF0;
extern s32 D_8016911C;
extern s32 D_80169120;
extern s32 D_8016924C;
extern s32 D_80169250;
extern s32 D_801749AC;



void func_80050FB0(void) {
    s32 i;

    if (D_801749B0.unk_04 == 0) {
        for (i = 0; i < 4; i++) {
            if (gPlayerActors[i].active == 1) {
                if (gPlayerActors[i].pos.y < -10.0f) {
                    D_800F0BE4[D_800F0BE0[i]].unk_00++;
                    func_8005456C(gPlayerActors[i].pos.x, -300.0f, gPlayerActors[i].pos.z, gPlayerActors[i].pos.y, 200.0f, gSelectedCharacters[i]);
                }
            }
        }
    }
}

void func_800510E0(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (gPlayerActors[i].active == 1) {
            if (++D_800F0B68[i][D_800F0BC0[i]] >= 100) {
                D_800F0B68[i][D_800F0BC0[i]] = 99;
            }
        }
    }
}

s32 func_8005119C(void) {
    s32 i, j;
    s32 sum_1 = 0;
    s32 sum_2 = 0;
    
    s32 var_v0 = D_801749AC;
    if (D_800F0B58 == 6) {
        var_v0 = 1;
    }
    
    switch (var_v0) {
        case 2:
            for (i = 0; i < 4 ; i++) {
                s32 total = 0;
                if (gPlayerActors[i].active == 1) {
                    for (j = 0; j < 4; j++) {
                        if (gPlayerActors[j].active == 1) {
                            if (i != j && D_800F0BE4[D_800F0BE0[j]].unk_00 < D_800F0BE4[D_800F0BE0[i]].unk_00) {
                                total++; 
                            }
                            D_800F0BC0[i] = total;
                        }    
                    }
                    if (D_800F0BC0[i] == 0) {
                        sum_1 += 1;
                    }
                    if (D_800F0BC0[i] == 1) {
                        sum_2 += 1;
                    }
                }
            }

            if (sum_2 == 2) {
                for (i = 0; i < 4; i++) {
                    if (gPlayerActors[i].active == 1 && D_800F0BC0[i] == 3) {
                        D_800F0BC0[i] = 2;
                    }
                }
            }
            if (sum_1 == 1) {
                sum_1 = 0;
            } else {
                sum_1--;
            }
            break;
        case 1:
            for (i = 0; i < 4; i++) {
                if (gPlayerActors[i].active == 1) {
                    D_800F0BC0[i] = D_800F0BD0[i] - 1;
                    
                    if (D_800F0BD0[i] < 2) {
                        D_800F0BC0[i] = 0;
                    }
                    if (D_800F0BC0[i] == 0) {
                        sum_1++;
                    }
                }
            }
            sum_1--;
            break;
    }
    return sum_1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/code/2C3B0/func_80051548.s")

f32 func_80051678(u8 arg0, f32* arg1, f32 arg2, f32 arg3) {
    f32 ret;
    f32 temp_f12;
    f32 temp_f12_2;
    
    ret = arg3 - arg2;
    switch (arg0) {
    default:
        break;
    case 2:
        temp_f12 = ret / 6.0f;
        *arg1 = temp_f12 + arg2;
        ret = temp_f12 * 4.0f;
        break;
    case 3:
        temp_f12 = ret / 8;
        *arg1 = temp_f12 + arg2;
        ret = temp_f12 * 3.0f;
        break;
    case 4:
        *arg1 = arg2;
        ret = ret / 3.0f;
        break;
    }
    return ret;
}

void func_8005171C(void) {
    if ((gCurrentZone == 6) && ((D_800F0B50 % 60) == 0)) {
        PLAYSFX(137, 0, 0x10);
    }
}

s32 func_8005177C(s32 arg0) {
    s32 i;
    s32 activeCount = 0;

    for (i = 0; i < 4; i++) {
        if (gPlayerActors[i].active && (D_80168D78[i] != (((i & 0xFF) == 4) * 0))) {
            if (arg0 != i) {
                activeCount++;
                continue;
            }
            break;
        }
    }
    if (i == 4) {
        activeCount = -1;
    }
    return activeCount;
}


#pragma GLOBAL_ASM("asm/nonmatchings/code/2C3B0/func_800517EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/code/2C3B0/func_80051910.s")

#pragma GLOBAL_ASM("asm/nonmatchings/code/2C3B0/func_80051B24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/code/2C3B0/func_80051F38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/code/2C3B0/func_80052094.s")

#pragma GLOBAL_ASM("asm/nonmatchings/code/2C3B0/func_800522A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/code/2C3B0/func_800523E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/code/2C3B0/func_800525E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/code/2C3B0/func_80052890.s")

#pragma GLOBAL_ASM("asm/nonmatchings/code/2C3B0/func_800536D8.s")

//prints "HURRY!" during MP Battle [9 times]
void Multiplayer_PrintHurry(void) {
    if ((D_80176824 <= 1800) && (D_80176824 > 1710) && ((D_80176824 % 10) < 5)) {
        SetTextGradientFromPalette(1); 
        PrintTextWrapper(100.0f, 10.0f, 0.0f, 1.0f, "ＨＵＲＲＹ！", 1);
    }
}

void func_80053950(void) {
    f32 var_f0 = 1.0f;
    if (D_80176824 < 0x3A3) {
        SetTextGradient(0xFFU, 0x3CU, 0U, 0xFFU, 0xFF, 0, 0, 0xFF, 0xFF, 0x3C, 0, 0xFF, 0xFF, 0, 0, 0xFF);
        if (D_80176824 < 0x15) {
            var_f0 = (f32) D_80176824 / 20.0f;
        }
        func_800523E4(136.0f, ((1.0f - var_f0) * 12.0f) + 10.0f, 1.0f, var_f0, (s32) ((s32) D_80176824 / 30) % 60, 2, 1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/code/2C3B0/func_80053A70.s")

void func_80053CA0(void) {
    s32 i, j;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 8; j++) {
            func_800612F0(i);
            func_80059F28((j * 0x28), (i * 0x30), 0, 0, 1.0f, 40.0f, 48.0f, j, 0xCE);
        }
    }
    func_800536D8();
}

#pragma GLOBAL_ASM("asm/nonmatchings/code/2C3B0/func_80053DA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/code/2C3B0/func_80053FA0.s")

void func_8005423C(void) {
    s32 i;
    for (i = 0; i < 6; i++){
        setPlayerContextEyes(i, 0, 0);
    }
}

//https://decomp.me/scratch/YLdZC
#pragma GLOBAL_ASM("asm/nonmatchings/code/2C3B0/func_80054284.s")
void func_800771DC(s32*, f32, f32, s32, s32, s32*, f32, f32, f32, f32); /* extern */

void func_8005444C(void) {
    if (D_801749B0.unk_04 == 1) {
        func_800771DC(&D_800FE404, 16.0f, 16.0f, 1, 5, &D_800F0B5C, 0.0f, 0.0f, 320.0f, 240.0f);
    }
    switch (D_800F0B5C) {
    case -2:
    case 1:
        D_800F0B5C = -1;
        return;
    case 2:
        D_800FE74C = 0;
        D_800F0B5C = -1;
        func_8005423C();
        SetProcessType(0xE);
        return;
    case 3:
        D_800FE74C = 0;
        D_800F0B5C = -1;
        func_8005423C();
        SetProcessType(7);
        return;
    case 4:
        D_800FE74C = 0;
        D_800F0B5C = -1;
        func_8005423C();
        SetProcessType(6);
        /* fallthrough */
    default:
        return;
    }
}

void func_8005456C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    Mtx sp30;

    if (D_800F0B50 & 1) {
        setPrimColor(D_800FE564[arg5].unk0, D_800FE564[arg5].unk1, D_800FE564[arg5].unk2, D_800FE564[arg5].unk3 * flabs((arg3 / arg1)));
        guAlign(&sp30, 0.0f, 0.0f, 100.0f, 0.0f);
        func_80058BE4(&sp30, arg0, arg1, arg2, arg4, arg4, 0.0f, 0x4A);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/code/2C3B0/func_800546F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/code/2C3B0/func_80054864.s")

void Process_Ranking(void) {
    switch (gGameModeState) {
    case 0:
        D_800FFDF4 = 1;
        D_800FE708 = 0;
        DMAStruct_Print();
        func_800A1EC4();
        loadSprite(0xD4);
        loadSprite(SPRITE_PORTRAITDAVY);
        loadSprite(SPRITE_PORTRAITJACK);
        loadSprite(SPRITE_PORTRAITFRED);
        loadSprite(SPRITE_PORTRAITLINDA);
        loadSprite(SPRITE_PORTRAITBLACK);
        loadSprite(SPRITE_PORTRAITWHITE);
        loadSprite(0x6E);
        loadSprite(0xBD);
        loadSprite(0xBE);
        loadSprite(0xBF);
        loadSprite(0xC0);
        loadSprite(0xC1);
        loadSprite(0xC2);
        TaskInit();
        D_80168DA0 = 4;
        gGameModeState++;
        UseFixedRNGSeed = FALSE;
        D_800FFDF0 = 2;
        func_8008BE14();
        func_80088198();
        D_801FC9AC = 0;
        func_800678EC(0, 0, 0, 0, 0x10);
        func_8008F114();
        break;
    case 1:
        func_80072D34();
        gGameModeState++;
        func_8008F114();
        break;
    case 2:
        func_8008F16C();
        D_8017499C++;
        break;
    case 3:
        SetProcessType(GAME_MODE_TITLE_SCREEN);
        break;
    }
    func_8008C094();
}

void func_800557F8(void) {
    s32 i;

    switch (gGameModeState) {
    case 0:
        D_800FFDF4 = 1;
        DMAStruct_Print();
        func_800A0D90();

        for (i = 0; i < 4; i++) {
            gPlayerActors[i].exists = gPlayerActors[i].active;
        }

        loadSprite(0xCE);
        loadSprite(0x6E);
        loadSprite(0xD5);
        loadPlayerEyes(CHARA_DAVY);
        loadPlayerEyes(CHARA_JACK);
        loadPlayerEyes(CHARA_FRED);
        loadPlayerEyes(CHARA_LINDA);
        loadPlayerEyes(CHARA_BLACK);
        loadPlayerEyes(CHARA_WHITE);
        TaskInit();
        D_80168DA0 = 4;
        gGameModeState++;
        UseFixedRNGSeed = FALSE;
        D_800FFDF0 = 2;
        func_8008BE14();
        func_80088198();
        D_801FC9AC = 0;
        func_8008F114();
        break;
    case 1:
        func_80073090();
        gGameModeState++;
        func_8008F114();
        break;
    case 2:
        func_8008F16C();
        D_8017499C++;
        break;
    case 3:
        SetProcessType(GAME_MODE_TITLE_SCREEN);
        break;
    }

    func_8008C094();
}

void Process_Boot(void) {
    switch (gGameModeState) {
    case 0:
        D_800FFDF4 = 1;
        DMAStruct_Print();
        func_800A1EC4();
        loadSprite(94);
        TaskInit();
        func_8002E0CC();
        gGameModeState++;
        UseFixedRNGSeed = FALSE;
        D_800FFDF0 = 2;
        D_801FC9AC = 0;
        func_8008F114();
        break;
    case 1:
        checkControllerRumble();
        gGameModeState++;
        func_8008F114();
        break;
    case 2:
        func_8008F16C();
        D_8017499C++;
        break;
    case 3:
        SetProcessType(GAME_MODE_SUPPLY_SYSTEM_LOGO);
        break;
    }

    func_8008C094();
}

void Process_SunsoftLogo(void) {
    switch (gGameModeState) { 
    case 0:
        D_800FFDF4 = 1;
        DMAStruct_Print();
        func_800A1EC4();
        loadSprite(0xCD);
        TaskInit();
        func_8002E0CC();
        gGameModeState++;
        UseFixedRNGSeed = FALSE;
        D_800FFDF0 = 2;
        D_801FC9AC = 0;
        break;
    case 1:
        func_80073FD8();
        gGameModeState++;
        func_8008F114();
        break;
    case 2:
        func_8008F16C();
        D_8017499C++;
        break;
    case 3:
        SetProcessType(GAME_MODE_SUPPLY_SYSTEM_LOGO);
        break;
    }
    
    func_8008C094();
}