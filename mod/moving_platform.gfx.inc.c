#include "common.h"

Vtx funnyAsset_platform1_mesh_vtx_0[20] = {
	{{ {-106, 11, -70}, 0, {2032, -16}, {0, 127, 0, 255} }},
	{{ {-106, 11, 70}, 0, {-16, -16}, {0, 127, 0, 255} }},
	{{ {106, 11, 70}, 0, {-16, 2032}, {0, 127, 0, 255} }},
	{{ {106, 11, -70}, 0, {2032, 2032}, {0, 127, 0, 255} }},
	{{ {-106, 11, -70}, 0, {3453, 8636}, {129, 0, 0, 255} }},
	{{ {-106, -11, -70}, 0, {3453, -6620}, {129, 0, 0, 255} }},
	{{ {-106, -11, 70}, 0, {-1437, -6620}, {129, 0, 0, 255} }},
	{{ {-106, 11, 70}, 0, {-1437, 8636}, {129, 0, 0, 255} }},
	{{ {106, 11, -70}, 0, {3453, 8636}, {0, 0, 129, 255} }},
	{{ {106, -11, -70}, 0, {3453, -6620}, {0, 0, 129, 255} }},
	{{ {-106, -11, -70}, 0, {-1437, -6620}, {0, 0, 129, 255} }},
	{{ {-106, 11, -70}, 0, {-1437, 8636}, {0, 0, 129, 255} }},
	{{ {106, 11, 70}, 0, {3453, 8636}, {127, 0, 0, 255} }},
	{{ {106, -11, 70}, 0, {3453, -6620}, {127, 0, 0, 255} }},
	{{ {106, -11, -70}, 0, {-1437, -6620}, {127, 0, 0, 255} }},
	{{ {106, 11, -70}, 0, {-1437, 8636}, {127, 0, 0, 255} }},
	{{ {-106, 11, 70}, 0, {3453, 8636}, {0, 0, 127, 255} }},
	{{ {-106, -11, 70}, 0, {3453, -6620}, {0, 0, 127, 255} }},
	{{ {106, -11, 70}, 0, {-1437, -6620}, {0, 0, 127, 255} }},
	{{ {106, 11, 70}, 0, {-1437, 8636}, {0, 0, 127, 255} }},
};

Gfx moving_platform_mesh[] = {
    gsDPPipeSync(),
    
    //lights. yeah
    gsSPSetLights1(JungleLand_jlScope_Light),
    //idk, global?
    gsDPSetCycleType(G_CYC_1CYCLE),
    //idk
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    //inits geometry modes for the entire gfx
    gsSPClearGeometryMode(G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    //dither setting
    gsDPSetColorDither(G_CD_BAYER),

    //general texture settings ; global??? i guess??? just make sure to change it when you need to
    gsSPTexture(0x10000, 0x10000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    //sets palette type (?)
    gsDPSetTextureLUT(G_TT_RGBA16),

    gsDPLoadTLUT_pal16(0, JL_metal_ci4_pal),
    gsDPLoadTextureTile_4b(JL_metal_ci4_png, G_IM_FMT_CI, 64, 64, 0, 0, 63, 63, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),

	gsSPVertex(&funnyAsset_platform1_mesh_vtx_0[0], 20, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsDPPipeSync(),
    
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};


Vec3f mp_colv[] = {
{ -106.0, 11.0, -70.0 },
{ -106.0, 11.0, 70.0 },
{ 106.0, 11.0, 70.0 },
{ 106.0, 11.0, -70.0 },
{ -106.0, 11.0, -70.0 },
{ -106.0, -11.0, -70.0 },
{ -106.0, -11.0, 70.0 },
{ -106.0, 11.0, 70.0 },
{ 106.0, 11.0, -70.0 },
{ 106.0, -11.0, -70.0 },
{ -106.0, -11.0, -70.0 },
{ -106.0, 11.0, -70.0 },
{ 106.0, 11.0, 70.0 },
{ 106.0, -11.0, 70.0 },
{ 106.0, -11.0, -70.0 },
{ 106.0, 11.0, -70.0 },
{ -106.0, 11.0, 70.0 },
{ -106.0, -11.0, 70.0 },
{ 106.0, -11.0, 70.0 },
{ 106.0, 11.0, 70.0 },
};

Vec3w mp_colt[] = {
{ 0, 1, 2 },
{ 0, 2, 3 },
{ 4, 5, 6 },
{ 4, 6, 7 },
{ 8, 9, 10 },
{ 8, 10, 11 },
{ 12, 13, 14 },
{ 12, 14, 15 },
{ 16, 17, 18 },
{ 16, 18, 19 },
};

Rect3D mp_cols = {
{-106.0, -11.0, -70.0},{106.0, 11.0, 70.0}
};

ModelCollision moving_platform_collision = {
20, 10, &mp_colv[0], &mp_colt[0], &mp_cols
};
