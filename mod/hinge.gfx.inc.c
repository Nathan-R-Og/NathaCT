#include "common.h"

Vtx funnyAsset_hinge_mesh_vtx_0[14] = {
	{{ {-497, 35, -362}, 0, {3453, 8636}, {129, 0, 0, 255} }},
	{{ {-497, -69, -362}, 0, {3453, -6620}, {129, 0, 0, 255} }},
	{{ {-497, 35, 723}, 0, {-1437, 8636}, {129, 0, 0, 255} }},
	{{ {497, 35, 723}, 0, {3453, -6620}, {127, 0, 0, 255} }},
	{{ {497, -69, -362}, 0, {-1437, -6620}, {127, 0, 0, 255} }},
	{{ {497, 35, -362}, 0, {-1437, 8636}, {127, 0, 0, 255} }},
	{{ {-497, 35, -362}, 0, {2032, -16}, {0, 127, 0, 255} }},
	{{ {-497, 35, 723}, 0, {-16, -16}, {0, 127, 0, 255} }},
	{{ {497, 35, 723}, 0, {-16, 2032}, {0, 127, 0, 255} }},
	{{ {497, 35, -362}, 0, {2032, 2032}, {0, 127, 0, 255} }},
	{{ {497, 35, -362}, 0, {3453, 8636}, {0, 0, 129, 255} }},
	{{ {497, -69, -362}, 0, {3453, -6620}, {0, 0, 129, 255} }},
	{{ {-497, -69, -362}, 0, {-1437, -6620}, {0, 0, 129, 255} }},
	{{ {-497, 35, -362}, 0, {-1437, 8636}, {0, 0, 129, 255} }},
};

Gfx hinge_mesh[] = {
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

	gsSPVertex(&funnyAsset_hinge_mesh_vtx_0[0], 14, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
	gsSP2Triangles(10, 11, 12, 0, 10, 12, 13, 0),
    gsDPPipeSync(),

    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};


Vec3f hin_colv[] = {
{ -497.0, 35.0, -362.0 },
{ -497.0, -69.0, -362.0 },
{ -497.0, 35.0, 723.0 },
{ 497.0, 35.0, 723.0 },
{ 497.0, -69.0, -362.0 },
{ 497.0, 35.0, -362.0 },
{ -497.0, 35.0, -362.0 },
{ -497.0, 35.0, 723.0 },
{ 497.0, 35.0, 723.0 },
{ 497.0, 35.0, -362.0 },
{ 497.0, 35.0, -362.0 },
{ 497.0, -69.0, -362.0 },
{ -497.0, -69.0, -362.0 },
{ -497.0, 35.0, -362.0 },
};

Vec3w hin_colt[] = {
{ 0, 1, 2 },
{ 3, 4, 5 },
{ 6, 7, 8 },
{ 6, 8, 9 },
{ 10, 11, 12 },
{ 10, 12, 13 },
};

Rect3D hin_cols = {
{-497.0, -69.0, -362.0},{497.0, 35.0, 723.0}
};

ModelCollision hinge_collision = {
14, 6, &hin_colv[0], &hin_colt[0], &hin_cols
};
