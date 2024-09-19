#include "common.h"

Vtx funnyAsset_square_mesh_vtx_0[4] = {
	{{ {-144, 0, 179}, 0, {2032, -16}, {0, 127, 0, 255} }},
	{{ {144, 0, 179}, 0, {-16, -16}, {0, 127, 0, 255} }},
	{{ {144, 0, -179}, 0, {-16, 2032}, {0, 127, 0, 255} }},
	{{ {-144, 0, -179}, 0, {2032, 2032}, {0, 127, 0, 255} }},
};

Gfx square_mesh[] = {
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

    gsDPPipeSync(),
	

    gsDPLoadTLUT_pal16(0, JL_metal_ci4_pal),
    gsDPLoadTextureTile_4b(JL_metal_ci4_png, G_IM_FMT_CI, 64, 64, 0, 0, 63, 63, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),

	gsSPVertex(&funnyAsset_square_mesh_vtx_0[0], 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};


Vec3f sq_colv[] = {
{ -144.0, 0.0, 179.0 },
{ 144.0, 0.0, 179.0 },
{ 144.0, 0.0, -179.0 },
{ -144.0, 0.0, -179.0 },
};

Vec3w sq_colt[] = {
{ 0, 1, 2 },
{ 0, 2, 3 },
};

Rect3D sq_cols = {
{-144.0, 0.0, -179.0},{144.0, 0.0, 179.0}
};

ModelCollision square_collision = {
4, 2, &sq_colv[0], &sq_colt[0], &sq_cols
};
