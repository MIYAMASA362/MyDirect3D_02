//
//	UI.h
//		Author:HIROMASA IKEDA	DATE:2018/08/28
//===============================================
#pragma once

#ifndef UI_H
#define UI_H

#include<d3dx9.h>
#include"CTransform.h"
#include"CSprite.h"

//===============================================
//	UI �N���X
//===============================================
class UI : public Sprite
{
private:
	
public:

	//�R���X�g���N�^
	UI(Transform2* pTransform2, NTexture::CTexture* pTexture);
	UI(Transform2* pTransform2, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation);

	void Set(Transform2* pTransform2);
	bool Click();	//�N���b�N��
	bool Hover();	//�z�o�[��
};

#endif // !UI_H
