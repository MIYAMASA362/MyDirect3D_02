//
//	Sprite.h
//		Author:HIROMASA IEDA	Date:2018/09/13
//===============================================
#pragma once
#ifndef SPRITE_H
#define SPRITE_H

#include<d3dx9.h>
#include"CTransform.h"
#include"Texture.h"

//===============================================
//	�\����
//===============================================

//-------------------------------------
//	Vertex2D
//-------------------------------------
typedef struct Vertex2D
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
}Vertex2D;

//-------------------------------------
//	TexVertex2D
//-------------------------------------
typedef struct TexVertex2D
{
	D3DXVECTOR4 Position;
	D3DCOLOR Color;
	D3DXVECTOR2 TexCoord;
}TexVertex2D;

//===============================================
//	�֐�
//===============================================

void Sprite_SetDevice(LPDIRECT3DDEVICE9 pD3DDevice);							//�f�o�C�X�ݒ�
void Render2D_Porigon(const Transform2* pTransform2);							//�|���S���`��
void Render2D_Porigon_Circle(const Transform2* pTransform2,float radius);		//�~�|���S��
void Render2D_Line(D3DXVECTOR2 Vector1, D3DXVECTOR2 Vector2);					//��(�����Ƃ��ݒ�ł����)
void Render2D_Porigon_Rotate(const Transform2* pTransform2);					//�|���S����]
void Render2D_Texture_Size(const Transform2* pTransform2, NTexture::CTexture* pTexture);	//�摜�T�C�Y�`��
void Render2D_Texture_Fill(Transform2* pTransform2, NTexture::CTexture* pTexture);			//�|���S���T�C�Y�ɕ`��
void Render2D_Texture_Clip(Transform2* pTransform2, NTexture::CTexture* pTexture);			//�e�N�X�`���؂蔲���T�C�Y�`��
void Render2D_Sprite(Transform2* pTransform2, NTexture::CTexture* pTexture);				//�X�v���C�g�`��
void Render2D_Sprite_Rotate(Transform2* pTransform2, NTexture::CTexture* pTexture);		//��

#endif

