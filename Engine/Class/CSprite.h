//
//	CSprite.h
//		Author:HIROMASA IEKDA	DATE:2018/10/01
//===============================================
#pragma once
#include<d3dx9.h>
#include"CTransform.h"
#include"CRender.h"

//===============================================
//	Sprite �N���X
//===============================================
class Sprite
{
private:

public:
	Render2D render;
	Transform2 transform;	//�ʒu
	NTexture::CTexture texture;		//�e�N�X�`��
	NTexture::CAnimation animation;	//�A�j���[�V�����X�e�[�^�X

	//�R���X�g���N�^
	Sprite();
	Sprite(Transform2* pTransform2,NTexture::CTexture* pTexture);
	Sprite(Transform2* pTransform2,NTexture::CTexture* pTexture,NTexture::CAnimation* pAnimation);

};


