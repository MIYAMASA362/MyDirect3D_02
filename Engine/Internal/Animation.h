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
//	名前空間
//===============================================	
namespace NTexture
{
	void FrameInit();
	void FrameUpdate();
	int Get_Frame();
}

//===============================================
//	関数宣言	
//===============================================
bool Animation_NoLoop(Transform2* pTransform, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation);		//ループしない
void Animation_Loop(Transform2* pTransform, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation);		//ループする
void Animation_Loop_Rotate(Transform2* pTransform, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation);	//ループ回転する

void Animation_Score(Transform2* pTransform, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation, int Score, bool bLeft, bool bZero, int digitNum);	//スコア

#endif

