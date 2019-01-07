//
//	CMesh.h
//		Author:HIROMASA IEKDA	DATE:2018/11/28
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CMESH_H
#define CMESH_H

//================================================
//	�C���N���[�h	include
//================================================
#include<d3dx9.h>
#include"common.h"

#include"Texture.h"
#include"XModel.h"

//================================================
//	�}�N����`	define
//================================================

//================================================
//	�񋓌^		enum
//================================================


//================================================
//	�\����		struct/typedef
//================================================


//================================================
//	�O���[�o���ϐ��@global
//================================================


//===============================================
//	�N���X
//===============================================

//===============================================
//	AMesh ����
//===============================================
class AMesh
{
private:

public:
	AMesh();

public:
	virtual void begin() = 0;	//�`��

};

//===============================================
//	CStandardMesh	�e�N�X�`��
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
	bool Loop;	//���[�v����
	NTexture::CTexture Texture;
	NTexture::CAnimation Animation;

public:
	CAnimationMesh();
	~CAnimationMesh();
public:
	virtual void begin() override;
};

//===============================================
//	CXModelMesh X���f���f�[�^
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
//	CXModelName X���f����
//===============================================
class CXModelName :public AMesh
{
public:
	//���f������o�^
	NXModel::Name Model;
public:
	CXModelName(NXModel::Name name);
public:
	void begin() override;
};

//=========================================================
//	�֐�
//=========================================================


#endif