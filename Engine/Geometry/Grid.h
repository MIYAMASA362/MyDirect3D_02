//
//	Grid.h
//		Author:HIROMASA IKEDA	DATE:2018/09/27
//===============================================
#pragma once
#ifndef GRID_H
#define	GRID_H

#include<d3dx9.h>

//===============================================
//	�}�N����`
//===============================================
//#define DISABLE_GRID		//Grid�𖳌�
#define GRID_WIDTH (1)
#define GRID_COLOR (D3DCOLOR_RGBA(255,255,255,255))

//===============================================
//	�֐�
//===============================================
void Grid_Initialize();
void Grid_Render();

#endif // !GRID_H

