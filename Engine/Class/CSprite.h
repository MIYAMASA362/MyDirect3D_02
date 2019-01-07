//
//	CSprite.h
//		Author:HIROMASA IEKDA	DATE:2018/10/01
//===============================================
#pragma once
#include<d3dx9.h>
#include"CTransform.h"
#include"CRender.h"

//===============================================
//	Sprite クラス
//===============================================
class Sprite
{
private:

public:
	Render2D render;
	Transform2 transform;	//位置
	NTexture::CTexture texture;		//テクスチャ
	NTexture::CAnimation animation;	//アニメーションステータス

	//コンストラクタ
	Sprite();
	Sprite(Transform2* pTransform2,NTexture::CTexture* pTexture);
	Sprite(Transform2* pTransform2,NTexture::CTexture* pTexture,NTexture::CAnimation* pAnimation);

};


