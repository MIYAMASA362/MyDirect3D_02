//
//	MeshField.h
//		Author:HIROMASA IEKDA	DATE:2018/11/27
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef MESHFIELD_H
#define MESHFIELD_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"
#include<d3dx9.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"Texture.h"

//================================================
//	�}�N����`	define
//================================================

//-------------------------------------
//	Ground
//-------------------------------------
#define MF_GROUND_GRID_WIDTH (50)		//���O���b�h��
#define MF_GROUND_GRID_DEPTH (50)		//���s�O���b�h��

#define MF_GROUND_SCALE_WIDTH (100)		//���T�C�Y
#define MF_GROUND_SCALE_DEPTH (100)		//���s�T�C�Y

//-------------------------------------
//	Cylinder
//-------------------------------------
#define MF_CYLINDER_HEIGHT (50)			//����
#define MF_CYLINDER_RADIUS (40.0f)		//���a

#define MF_CYLINDER_GRID_WIDTH (100)	//���O���b�h��
#define MF_CYLINDER_GRID_HEIGHT (10)	//�c�O���b�h��

#define MF_CYLINDER_ANGLE ((2*M_PI)/MF_CYLINDER_GRID_WIDTH)					//1�O���b�h�p�x
#define MF_CYLINDER_A_HEIGHT (MF_CYLINDER_HEIGHT / MF_CYLINDER_GRID_HEIGHT)	//1�O���b�h����

//-------------------------------------
//	SkyDome
//-------------------------------------
#define MF_SKYDORM_RADIUS (50)			//���a
#define MF_SKYDORM_GRID_HEIGHT (50)		//�c�O���b�h��
#define MF_SKYDORM_GRID_WIDTH (50)		//���O���b�h��

#define MF_SKYDORM_ANGLE_WIDTH	( (2*M_PI) / MF_SKYDORM_GRID_WIDTH ) //1�O���b�h�p�x
#define MF_SKYDORM_ANGLE_HEIGHT	( (M_PI_2) / MF_SKYDORM_GRID_HEIGHT) //1�O���b�h

//================================================
//	���O���
//================================================
namespace NMeshField
{
	//================================================
	//	�֐�		function
	//================================================
	void Initialize();

	void Render_Ground(const D3DXVECTOR3 Center, const NTexture::Name TextureName);
	void Render_Cylinder(const D3DXVECTOR3 Center, const NTexture::Name TextureName);
	void Render_SkyDome(const D3DXVECTOR3 Center, const NTexture::Name TextureName);

	void Finalize();
}

#endif