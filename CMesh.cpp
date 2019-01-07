//
//	CMesh.cpp
//		Author:HIROMASA IKEDA	DATE:2018/11/14
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"
#include"System.h"

//class
#include"Cube.h"
#include"CMesh.h"
#include"XModel.h"

//===============================================
//	マクロ定義		define
//===============================================

//===============================================
//	グローバル変数	global
//===============================================

//===============================================
//	CMesh 抽象
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
AMesh::AMesh()
{
	
}

//===============================================
//	CStandardMesh
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
CStandardMesh::CStandardMesh():AMesh()
{
	this->pTexture = new NTexture::CTexture();
	this->Material.Diffuse = this->Material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	this->FVF = FVF_CUBE_VERTEX3D;
	this->PrimitiveType = CUBE_PRIMITIVE_TYPE;
	this->Model = GetModel_Cube();
	this->DataSize = sizeof(CubeVertex3D);
	this->PrimitiveCount = CUBE_PRIMITIVE_NUM;
}

//-------------------------------------
//	描画
//-------------------------------------
void CStandardMesh::begin()
{
	LPDIRECT3DDEVICE9 Device = System_GetDevice();
	Device->SetMaterial(&this->Material);

	Device->SetFVF(this->FVF);

	if (this->pTexture->name == NTexture::NAME_NONE)
	{
		Device->SetTexture(0, NULL);
	}
	else
	{
		Device->SetTexture(0, pTexture->Get_Texture());
	}

	Device->DrawPrimitiveUP(this->PrimitiveType, this->PrimitiveCount, this->Model, this->DataSize);

	return;
}

//-------------------------------------
//	テクスチャ設定
//-------------------------------------
void CStandardMesh::Set_Texture(NTexture::ATexture Texture)
{
	this->pTexture = &Texture;
}

void CStandardMesh::Set_Texture(NTexture::ATexture* pTexture)
{
	this->pTexture = pTexture;
}

//===============================================
//	CAnimationMesh	アニメーション
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
CAnimationMesh::CAnimationMesh()
{
	
}

//-------------------------------------
//	デストラクタ
//-------------------------------------
CAnimationMesh::~CAnimationMesh()
{
	
}

//-------------------------------------
//	描画	アニメーション実装できてない
//-------------------------------------
void CAnimationMesh::begin()
{
	CStandardMesh::begin();
}

//===============================================
//	CXModelMesh Xモデルデータ
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
CXModelMesh::CXModelMesh()
{
	this->pMesh = NULL;
	this->pMeshMaterials = NULL;
	this->pMeshTextures = NULL;
	this->dwNumMaterials = NULL;
}

//-------------------------------------
//	描画
//-------------------------------------
void CXModelMesh::begin()
{
	//マテリアルの数だけループさせる
	for (DWORD i = 0; i < this->dwNumMaterials; i++)
	{
		//マテリアル設定
		System_GetDevice()->SetMaterial(&this->pMeshMaterials[i]);
		//テクスチャ設定
		System_GetDevice()->SetTexture(0, this->pMeshTextures[i]);
		//レンダリング
		this->pMesh->DrawSubset(i);
	}
}

//===============================================
//	モデル名
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
CXModelName::CXModelName(NXModel::Name name)
{
	this->Model = name;
}

//-------------------------------------
//	描画
//-------------------------------------
void CXModelName::begin()
{
	NXModel::Data* pMesh = NXModel::Get(Model);

	for(DWORD i = 0; i < pMesh->dwNumMaterials; i++)
	{
		System_GetDevice()->SetMaterial(&pMesh->pMaterials[i]);
		System_GetDevice()->SetTexture(0,pMesh->pTextures[i]);
		pMesh->pMesh->DrawSubset(i);
	}
}



