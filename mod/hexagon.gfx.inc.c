#include "common.h"

Vtx funnyAsset_hexa_mesh_vtx_0[12] = {
	{{ {241, 0, 86}, 0, {667, 2032}, {0, 127, 0, 255} }},
	{{ {80, 0, 86}, 0, {667, 1349}, {0, 127, 0, 255} }},
	{{ {80, 0, 257}, 0, {-16, 1349}, {0, 127, 0, 255} }},
	{{ {80, 0, -86}, 0, {1349, 1349}, {0, 127, 0, 255} }},
	{{ {241, 0, -86}, 0, {1349, 2032}, {0, 127, 0, 255} }},
	{{ {80, 0, -257}, 0, {2032, 1349}, {0, 127, 0, 255} }},
	{{ {-80, 0, -257}, 0, {2032, 667}, {0, 127, 0, 255} }},
	{{ {-80, 0, -86}, 0, {1349, 667}, {0, 127, 0, 255} }},
	{{ {-241, 0, -86}, 0, {1349, -16}, {0, 127, 0, 255} }},
	{{ {-80, 0, 86}, 0, {667, 667}, {0, 127, 0, 255} }},
	{{ {-241, 0, 86}, 0, {667, -16}, {0, 127, 0, 255} }},
	{{ {-80, 0, 257}, 0, {-16, 667}, {0, 127, 0, 255} }},
};

Gfx hexagon_mesh[] = {
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

	gsSPVertex(&funnyAsset_hexa_mesh_vtx_0[0], 12, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
	gsSP2Triangles(3, 0, 4, 0, 5, 3, 4, 0),
	gsSP2Triangles(6, 3, 5, 0, 6, 7, 3, 0),
	gsSP2Triangles(6, 8, 7, 0, 8, 9, 7, 0),
	gsSP2Triangles(8, 10, 9, 0, 10, 11, 9, 0),
	gsSP2Triangles(9, 11, 2, 0, 9, 2, 1, 0),
	gsSP2Triangles(7, 9, 1, 0, 7, 1, 3, 0),
    gsDPPipeSync(),
    
    
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};


Vec3f hex_colv[] = {
{ 241.0, 0.0, 86.0 },
{ 80.0, 0.0, 86.0 },
{ 80.0, 0.0, 257.0 },
{ 80.0, 0.0, -86.0 },
{ 241.0, 0.0, -86.0 },
{ 80.0, 0.0, -257.0 },
{ -80.0, 0.0, -257.0 },
{ -80.0, 0.0, -86.0 },
{ -241.0, 0.0, -86.0 },
{ -80.0, 0.0, 86.0 },
{ -241.0, 0.0, 86.0 },
{ -80.0, 0.0, 257.0 },
};

Vec3w hex_colt[] = {
{ 0, 1, 2 },
{ 3, 1, 0 },
{ 3, 0, 4 },
{ 5, 3, 4 },
{ 6, 3, 5 },
{ 6, 7, 3 },
{ 6, 8, 7 },
{ 8, 9, 7 },
{ 8, 10, 9 },
{ 10, 11, 9 },
{ 9, 11, 2 },
{ 9, 2, 1 },
{ 7, 9, 1 },
{ 7, 1, 3 },
};

Rect3D hex_cols = {
{-241.0, 0.0, -257.0},{241.0, 0.0, 257.0}
};

ModelCollision hexagon_collision = {
12, 14, &hex_colv[0], &hex_colt[0], &hex_cols
};
