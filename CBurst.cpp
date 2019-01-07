//
//	CBurst.cpp
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"
#include"CBurst.h"

#include<math.h>
#include<time.h>

//class
#include"Billboard.h"
#include"Animation.h"
#include"System.h"

//===============================================
//	�}�N����`		define
//===============================================


//===============================================
//	�O���[�o���ϐ�	global
//===============================================
static CBurst* g_Bullet;
std::vector<CBurst*> CBurst::pIndex;

void CBurst::g_Update()
{
	for(int i = 0; i< pIndex.size(); i++)
	{
		pIndex.at(i)->Update();
	}
}

void CBurst::g_Render()
{
	for (int i = 0; i< pIndex.size(); i++)
	{
		pIndex.at(i)->Render();
	}
}

//===============================================
//	CBurst
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
CBurst::CBurst(D3DXVECTOR3 Position,D3DXVECTOR3 Scale)
:
	texture(NTexture::Billboard_Burst, { 0,0 }, { 128,128 }),
	animation(18, 6, 4)
{
	this->Position = Position;
	this->Scale = Scale;
	this->pIndex.push_back(this);
}

//-------------------------------------
//	�f�X�g���N�^
//-------------------------------------
CBurst::~CBurst()
{
	std::vector<CBurst*>::iterator me = pIndex.begin();

	while (me != pIndex.end())
	{
		if ((*me) == this)
		{
			me = pIndex.erase(me);
			break;
		}
		me++;
	}
}

void CBurst::Update()
{
 	if(animation.AnimaPatern >= animation.MaxPatern-1)
	{
		this->~CBurst();
	}
}

void CBurst::Render()
{
	LPDIRECT3DDEVICE9 Device = System_GetDevice();
	Device->SetRenderState(D3DRS_ZENABLE, FALSE);
	//Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ZERO);
	//Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);

	AnimaBillBoard_Create(this->Position, this->Scale, &texture, &animation);

	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//�w�iDSET�̃u�����h�ݒ�
	Device->SetRenderState(D3DRS_ZENABLE, TRUE);
}

void Burst_Create(D3DXVECTOR3 Position,D3DXVECTOR3 Scale)
{
	g_Bullet = new CBurst(Position,Scale);
}