//
//	Cube.h
//		Author:HIROMASA IKEDA	DATE:2018/09/21
//===============================================
#pragma once
#ifndef CUBE_H
#define CUBE_H

#include<d3dx9.h>

//===============================================
//	�}�N��	
//===============================================
#define FVF_CUBE_VERTEX3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 )
#define CUBE_PRIMITIVE_TYPE (D3DPT_TRIANGLELIST)	//�v���~�e�B�u�^�C�v
#define CUBE_PRIMITIVE_NUM	(12)					//�|���S����

//===============================================
//	�\����
//===============================================
typedef struct Cube_Vertex3D_tag
{
	D3DXVECTOR3 Position;	//�ʒu
	D3DXVECTOR3 Normal;		//�@��
	D3DXVECTOR2 TexCoord;	//�e�N�X�`�����W
}CubeVertex3D;

//===============================================
//	Cube ���f���f�[�^
//===============================================


//===============================================
//	�֐�
//===============================================
void Set_CubeColor(D3DCOLOR Color);
void* GetModel_Cube();

void Cube_Initialize();
void Cube_Render();
void Cube_Finalize();
#endif