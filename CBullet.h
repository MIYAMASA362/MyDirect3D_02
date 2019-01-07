//
//	CBullet.h
//		Author:HIROMASA IKEDA	DATE:2018/11/22
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CBULLET_H
#define CBULLET_H

//================================================
//	�C���N���[�h	include
//================================================
#include<d3dx9.h>
#include<vector>
#include"common.h"

#include"CTransform.h"
//Class

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
//	�N���X		class
//================================================

//-------------------------------------
//	CBullet
//-------------------------------------
class CBullet
{
public:
	static std::vector<CBullet*> pIndex;

public:
	static void g_Update();
	static void g_Render();

public:
	static float Speed;			//�e��

private:
	D3DXVECTOR3 CreatePosition;
	D3DXVECTOR3 face;

public:
	Transform transform;	//�ʒu���

public:
	//�R���X�g���N�^
	CBullet(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 face);

	//�f�X�g���N�^
	~CBullet();

public:
	void Update();			//�X�V
	void Render();			//�`��

	void Destroy();			//�폜
};

void CBullet_Create(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 face);
void CBullet_Finalize();

#endif