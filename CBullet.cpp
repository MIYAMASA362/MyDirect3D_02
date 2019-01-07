//
//	CBullet.cpp
//		Author:HIROMASA IKEDA	DATE:2018/11/22
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"
#include"CBullet.h"

//class
#include"Billboard.h"
#include"CBurst.h"
#include"MeshField.h"

//===============================================
//	�}�N����`		define
//===============================================

//===============================================
//	�O���[�o���ϐ�	global
//===============================================
std::vector<CBullet*> CBullet::pIndex;
float CBullet::Speed = 2.0f;

//===============================================
//	CBullet
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
CBullet::CBullet(D3DXVECTOR3 Position,D3DXVECTOR3 Scale,D3DXVECTOR3 face)
:
	transform(Position,Scale)
{
	this->CreatePosition = Position;
	this->face = face;
	pIndex.push_back(this);
}

//-------------------------------------
//	�f�X�g���N�^
//-------------------------------------
CBullet::~CBullet()
{
	std::vector<CBullet*>::iterator me = pIndex.begin();

	while(me != pIndex.end())
	{
		if((*me) == this)
		{
			me = pIndex.erase(me);
			break;
		}
		me++;
	}
}

//-------------------------------------
//	�X�V����
//-------------------------------------
void CBullet::Update()
{
	this->transform.Position += this->face * Speed;
	//this->transform.Position.y -= 0.2f;	//�e�̗���
	if(this->transform.Position.y <= 0.0f)
	{
		this->Destroy();
	}
	
	D3DXVECTOR3 VecDis = this->CreatePosition - this->transform.Position;
	if (D3DXVec3Length(&VecDis) >= MF_CYLINDER_RADIUS)
	{
		this->Destroy();
	}

}

//-------------------------------------
//	�`�揈��
//-------------------------------------
void CBullet::Render()
{
	BillBoard_Create(&this->transform);
}

//-------------------------------------
//	�폜
//-------------------------------------
void CBullet::Destroy()
{
	Burst_Create(this->transform.Position, { 4.0f,4.0f,4.0f });
	this->~CBullet();
}

//=====================================
//	�O���[�o���֐�
//=====================================

//-------------------------------------
//	�X�V
//-------------------------------------
void CBullet::g_Update()
{
	for(int i =0; i < pIndex.size(); i++)
	{
		pIndex.at(i)->Update();
	}
}

//-------------------------------------
//	�`��
//-------------------------------------
void CBullet::g_Render()
{
	for (int i = 0; i < pIndex.size(); i++)
	{
		pIndex.at(i)->Render();
	}
}

//===============================================
//	�֐�
//===============================================

void CBullet_Create(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 face)
{
	CBullet* bullet = new CBullet(Position,Scale,face);
}

//-------------------------------------
//	�I������
//-------------------------------------
void CBullet_Finalize()	
{
	/*
	//�S�v�f���폜������
	std::vector<CBullet*>::iterator it = CBullet::pIndex.end();
	while(it != CBullet::pIndex.begin())
	{
		delete *it;
		it--;
	}
	*/
	CBullet::pIndex.clear();
}
