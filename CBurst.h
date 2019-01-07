//
//	CBurst.h
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CBURST_H
#define CBURST_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"
#include<d3dx9.h>
#include<vector>

//Class
#include"Billboard.h"

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
//	CBurst
//-------------------------------------
class CBurst
{
public:
	static std::vector<CBurst*> pIndex;
	static void g_Update();
	static void g_Render();

public:
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Scale;
	NTexture::CTexture texture;
	NTexture::CAnimation animation;

public:
	CBurst(D3DXVECTOR3 Position,D3DXVECTOR3 Scale);
	~CBurst();

public:
	void Update();
	void Render();

};

void Burst_Create(D3DXVECTOR3 Position,D3DXVECTOR3 Scale);

#endif