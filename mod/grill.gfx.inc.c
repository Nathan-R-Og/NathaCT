#include "common.h"

Vtx funnyAsset_grill8_mesh_vtx_0[4] = {
	{{ {-920, 0, -90}, 0, {2683, -18043}, {0, 127, 0, 255} }},
	{{ {-920, 0, 90}, 0, {-1691, -18043}, {0, 127, 0, 255} }},
	{{ {920, 0, 90}, 0, {-1691, 19035}, {0, 127, 0, 255} }},
	{{ {920, 0, -90}, 0, {2683, 19035}, {0, 127, 0, 255} }},
};

Gfx grill_mesh[] = {
    gsDPPipeSync(),
    
    //lights. yeah
    gsSPSetLights1(JungleLand_jlScope_Light),
    //idk, global?
    gsDPSetCycleType(G_CYC_1CYCLE),
    //idk (edited)
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    //inits geometry modes for the entire gfx
    gsSPClearGeometryMode(G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    //(edited)
    gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK),
    gsDPSetColorDither(G_CD_BAYER),

    //general texture settings ; global??? i guess??? just make sure to change it when you need to
    gsSPTexture(0x10000, 0x10000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    //sets palette type (?)
    //edited
    gsDPSetTextureLUT(G_TT_NONE),

    gsDPLoadTextureTile_4b(JL_grill_ci4_png, G_IM_FMT_IA, 32, 0, 0, 0, 31, 31, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetPrimColor(0, 0, 178, 40, 40, 255),

	gsSPVertex(&funnyAsset_grill8_mesh_vtx_0[0], 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsDPPipeSync(),
    
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};


Vec3f gl_colv[] = {
{ -920.0, 0.0, -90.0 },
{ -920.0, 0.0, 90.0 },
{ 920.0, 0.0, 90.0 },
{ 920.0, 0.0, -90.0 },
};

Vec3w gl_colt[] = {
{ 0, 1, 2 },
{ 0, 2, 3 },
};

Rect3D gl_cols = {
{-920.0, 0.0, -90.0},{920.0, 0.0, 90.0}
};

ModelCollision grill_collision = {
4, 2, &gl_colv[0], &gl_colt[0], &gl_cols
};
