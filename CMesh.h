//
//	CMesh.h
//		Author:HIROMASA IEKDA	DATE:2018/11/28
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CMESH_H
#define CMESH_H

//================================================
//	インクルード	include
//================================================
#include<d3dx9.h>
#include"common.h"

#include"Texture.h"
#include"XModel.h"

//================================================
//	マクロ定義	define
//================================================

//================================================
//	列挙型		enum
//================================================


//================================================
//	構造体		struct/typedef
//================================================


//================================================
//	グローバル変数　global
//================================================


//===============================================
//	クラス
//===============================================

//===============================================
//	AMesh 抽象
//===============================================
class AMesh
{
private:

public:
	AMesh();

public:
	virtual void begin() = 0;	//描画

};

//===============================================
//	CStandardMesh	テクスチャ
//===============================================
class CStandardMesh :public AMesh
{
private:

public:
	NTexture::ATexture* pTexture;
	D3DMATERIAL9 Material;

	DWORD FVF;
	D3DPRIMITIVETYPE PrimitiveType;
	void* Model;
	UINT DataSize;
	UINT PrimitiveCount;

public:
	CStandardMesh();

public:
	virtual void begin() override;

public:
	void Set_Texture(NTexture::ATexture* pTexture);
	void Set_Texture(NTexture::ATexture Texture);
};

//===============================================
//	CAnimationMesh 
//===============================================
class CAnimationMesh:public CStandardMesh
{
public:
	bool Loop;	//ループする
	NTexture::CTexture Texture;
	NTexture::CAnimation Animation;

public:
	CAnimationMesh();
	~CAnimationMesh();
public:
	virtual void begin() override;
};

//===============================================
//	CXModelMesh Xモデルデータ
//===============================================
class CXModelMesh :public AMesh
{
private:

public:
	LPD3DXMESH pMesh;
	D3DMATERIAL9* pMeshMaterials;
	LPDIRECT3DTEXTURE9* pMeshTextures;
	DWORD dwNumMaterials;

public:
	CXModelMesh();

public:
	void begin() override;
};

//===============================================
//	CXModelName Xモデル名
//===============================================
class CXModelName :public AMesh
{
public:
	//モデル名を登録
	NXModel::Name Model;
public:
	CXModelName(NXModel::Name name);
public:
	void begin() override;
};

//=========================================================
//	関数
//=========================================================


#endif