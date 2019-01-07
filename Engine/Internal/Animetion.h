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
#include"CTexture.h"
#include"CAnimetion.h"

//===============================================
//	�֐��錾	
//===============================================
void Animetion_Initialize();	
void Animetion_Update();
int Animetion_GetFrame();

bool Animetion_NoLoop(Transform2* pTransform, Texture* pTexture, Animetion* pAnimetion);		//���[�v���Ȃ�
void Animetion_Loop(Transform2* pTransform, Texture* pTexture, Animetion* pAnimetion);			//���[�v����
void Animetion_Loop_Rotate(Transform2* pTransform, Texture* pTexture, Animetion* pAnimetion);	//���[�v��]����

void Animetion_Score(Transform2* pTransform, Texture* pTexture, Animetion* pAnimetion, int Score, bool bLeft, bool bZero, int digitNum);	//�X�R�A

#endif

