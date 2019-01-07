//
//	XModel.h
//		Author:HIROMASA IKEDA	DATE:2018/10/19
//===============================================
//	�ύX�� Changed By
//		Name:Minoda Takamasa	DATE:2018/10/23
//
//-----------------------------------------------
//�G���[�\��
//
//	�EModels//�@
//		XModel::Name��Path�̐��������Ă��Ȃ�
//
//===============================================

#pragma once
#ifndef XMODEL_H
#define XMODEL_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"
#include<d3dx9.h>

#include"CMesh.h"
//================================================
//	�}�N����`	define
//================================================

//===============================================
//	XModel ���O���
//===============================================
namespace NXModel
{
	//==============================================
	//	�\����
	//==============================================

	//���f���̃f�[�^�^
	struct Data
	{
		LPD3DXMESH pMesh;
		D3DMATERIAL9* pMaterials;
		LPDIRECT3DTEXTURE9* pTextures;
		DWORD dwNumMaterials;
	};

	//==============================================
	//	��
	//==============================================

	//���f����
	const enum Name
	{
		AIRPLANE_BODY,
		AIRPLANE_PROPELLER,
		AIRPLANE_WingBD,
		AIRPLANE_WingBU,
		AIRPLANE_WingLD,
		AIRPLANE_WingLU,
		AIRPLANE_WingRD,
		AIRPLANE_WingRU,
		AIRPLANE_MODEL,
		TREE,
		NAME_END,
		MODEL_NONE
	};

	//==============================================
	//	�֐�
	//==============================================
	void Load(const int index);
	void Render(const int index);
	void Initialize();
	void Finalize();
	Data* Get(const Name name);
	void Load_XModelMesh(CXModelMesh* LoadMesh, char* ModelFile, char* path);
}


#endif