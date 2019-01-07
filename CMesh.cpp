//
//	CMesh.cpp
//		Author:HIROMASA IKEDA	DATE:2018/11/14
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"
#include"System.h"

//class
#include"Cube.h"
#include"CMesh.h"
#include"XModel.h"

//===============================================
//	�}�N����`		define
//===============================================

//===============================================
//	�O���[�o���ϐ�	global
//===============================================

//===============================================
//	CMesh ����
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
AMesh::AMesh()
{
	
}

//===============================================
//	CStandardMesh
//===============================================

//-------------------------------------
//	�R���X�g���N�^
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
//	�`��
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
//	�e�N�X�`���ݒ�
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
//	CAnimationMesh	�A�j���[�V����
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
CAnimationMesh::CAnimationMesh()
{
	
}

//-------------------------------------
//	�f�X�g���N�^
//-------------------------------------
CAnimationMesh::~CAnimationMesh()
{
	
}

//-------------------------------------
//	�`��	�A�j���[�V���������ł��ĂȂ�
//-------------------------------------
void CAnimationMesh::begin()
{
	CStandardMesh::begin();
}

//===============================================
//	CXModelMesh X���f���f�[�^
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
CXModelMesh::CXModelMesh()
{
	this->pMesh = NULL;
	this->pMeshMaterials = NULL;
	this->pMeshTextures = NULL;
	this->dwNumMaterials = NULL;
}

//-------------------------------------
//	�`��
//-------------------------------------
void CXModelMesh::begin()
{
	//�}�e���A���̐��������[�v������
	for (DWORD i = 0; i < this->dwNumMaterials; i++)
	{
		//�}�e���A���ݒ�
		System_GetDevice()->SetMaterial(&this->pMeshMaterials[i]);
		//�e�N�X�`���ݒ�
		System_GetDevice()->SetTexture(0, this->pMeshTextures[i]);
		//�����_�����O
		this->pMesh->DrawSubset(i);
	}
}

//===============================================
//	���f����
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
CXModelName::CXModelName(NXModel::Name name)
{
	this->Model = name;
}

//-------------------------------------
//	�`��
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



