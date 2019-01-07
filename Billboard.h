//
//	Billboard.h
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef BILLBOARD_H
#define BILLBOARD_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"
#include<d3dx9.h>
#include<vector>

#include"CTransform.h"
#include"Texture.h"

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


//================================================
//	�N���X
//================================================

//-------------------------------------
//	���ۃN���X
//-------------------------------------
class ABillboard
{
public:
	static std::vector<ABillboard*> pIndex;
	static void g_Update();
	static void g_Render();

public:
	D3DXVECTOR3 Position;	//�ʒu
	D3DXVECTOR3 Scale;		//�傫��

public:
	//�R���X�g���N�^
	ABillboard(D3DXVECTOR3 Position,D3DXVECTOR3 Scale);
	~ABillboard();

public:
	virtual void Update() = 0;
	virtual void Render() = 0;
};

//-------------------------------------
//	Billboard
//-------------------------------------
class CBillboard:public ABillboard
{
public:
	
public:
	//�R���X�g���N�^
	CBillboard(D3DXVECTOR3 Position,D3DXVECTOR3 Scale);

	//�f�X�g���N�^
	~CBillboard();

public:
	void Update() override;
	void Render() override;
};

//-------------------------------------
//	AnimationBillboard
//-------------------------------------
class AnimationBillboard:public ABillboard
{
public:
	NTexture::CTexture texture;
	NTexture::CAnimation animation;
public:
	AnimationBillboard() :AnimationBillboard({ 0.0f,0.0f,0.0f }, {1.0f,1.0f,1.0f}) {};
	AnimationBillboard(D3DXVECTOR3 Position,D3DXVECTOR3 Scale);
	~AnimationBillboard();
public:
	void Update() final;
	void Render() final;
};

//================================================
//	�֐�		function
//================================================
void Billboard_Initialize();
void BillBoard_Create(D3DXVECTOR3 position);
void BillBoard_Create(Transform* pTransform);
void BillBoard_Finalaize();
void AnimaBillBoard_Create(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation);
void BillBoardShadow_Create(D3DXVECTOR3 Position, D3DXVECTOR3 Scale);
#endif