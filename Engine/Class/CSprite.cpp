//
//	CSprite.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/01
//===============================================
#include<d3dx9.h>
#include"CSprite.h"
#include"Sprite.h"

//===============================================
//	Sprite�N���X
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
Sprite::Sprite()
{

}

//-------------------------------------
//	�R���X�g���N�^�@�|�C���^�^
//-------------------------------------
Sprite::Sprite(Transform2* pTransform2, NTexture::CTexture* pTexture) :render(&this->transform,&this->texture)
{
	this->transform = *pTransform2;
	this->texture = *pTexture;
	this->animation = {};
}

Sprite::Sprite(Transform2* pTransform2, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation):render(&this->transform,&this->texture,&this->animation)
{
	this->transform		= *pTransform2;
	this->texture		= *pTexture;
	this->animation		= *pAnimation;
}