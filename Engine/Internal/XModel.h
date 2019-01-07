//
//	XModel.h
//		Author:HIROMASA IKEDA	DATE:2018/10/19
//===============================================
//	変更者 Changed By
//		Name:Minoda Takamasa	DATE:2018/10/23
//
//-----------------------------------------------
//エラー表示
//
//	・Models//　
//		XModel::NameとPathの数が合っていない
//
//===============================================

#pragma once
#ifndef XMODEL_H
#define XMODEL_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>

#include"CMesh.h"
//================================================
//	マクロ定義	define
//================================================

//===============================================
//	XModel 名前空間
//===============================================
namespace NXModel
{
	//==============================================
	//	構造体
	//==============================================

	//モデルのデータ型
	struct Data
	{
		LPD3DXMESH pMesh;
		D3DMATERIAL9* pMaterials;
		LPDIRECT3DTEXTURE9* pTextures;
		DWORD dwNumMaterials;
	};

	//==============================================
	//	列挙
	//==============================================

	//モデル名
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
	//	関数
	//==============================================
	void Load(const int index);
	void Render(const int index);
	void Initialize();
	void Finalize();
	Data* Get(const Name name);
	void Load_XModelMesh(CXModelMesh* LoadMesh, char* ModelFile, char* path);
}


#endif