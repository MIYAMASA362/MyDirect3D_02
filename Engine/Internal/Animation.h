//
//	Animetion.h
//		USER:HIROMASA IKEDA		DATE:2018/09/28
//===============================================
#pragma once
#ifndef ANIMETION_H
#define ANIMETION_H

#include<d3dx9.h>

#include"common.h"
#include"CTransform.h"
#include"Texture.h"

//===============================================
//	���O���
//===============================================	
namespace NTexture
{
	void FrameInit();
	void FrameUpdate();
	int Get_Frame();
}

//===============================================
//	�֐��錾	
//===============================================
bool Animation_NoLoop(Transform2* pTransform, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation);		//���[�v���Ȃ�
void Animation_Loop(Transform2* pTransform, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation);		//���[�v����
void Animation_Loop_Rotate(Transform2* pTransform, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation);	//���[�v��]����

void Animation_Score(Transform2* pTransform, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation, int Score, bool bLeft, bool bZero, int digitNum);	//�X�R�A

#endif

