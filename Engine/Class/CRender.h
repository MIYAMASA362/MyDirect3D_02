//
//	CRender.h
//		Author:HIROMASA IKEDA	DATE:2018/09/29
//===============================================
#pragma once
#ifndef CRENDER_H
#define CRENDER_H

#include<d3dx9.h>
#include<vector>

//Class
#include"CTransform.h"

#include"XModel.h"
#include"CMesh.h"	
#include"Texture.h"

//===============================================
//	��
//===============================================

//===============================================
//	�\����
//===============================================

//===============================================
//	���O���
//===============================================
namespace NRender3D
{
	void Render(AMesh* pModel, CTransform* pTransform);
}

//-------------------------------------
//	Render2D
//-------------------------------------
class Render2D
{
public:

	enum RENDER2D_TYPE
	{
		R2D_PORIGON,
		R2D_RORIGON_ROTATE,
		R2D_TEXTURE_SIZE,
		R2D_TEXTURE_FILL,
		R2D_TEXTURE_CLIP,
		R2D_SPRITE,
		R2D_SPRITE_ROTATE
	};

	//�A�j���[�V����
	enum RENDER2DANIMA_TYPE
	{
		R2DA_NOLOOP,
		R2DA_LOOP,
		R2DA_LOOP_ROTATE
	};

private:

public:
	Transform2* pTransform;
	NTexture::CTexture*	pTexture;
	NTexture::CAnimation* pAnimation;

public:
	//�R���X�g���N�^
	Render2D();
	Render2D(Transform2* pTransform, NTexture::CTexture* pTexture);
	Render2D(Transform2* pTransform, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation);

public:
	bool Begin(RENDER2D_TYPE R2D_TYPE);
	bool Begin(RENDER2DANIMA_TYPE R2DA_TYPE);
};

#endif // !CRENDER_H
