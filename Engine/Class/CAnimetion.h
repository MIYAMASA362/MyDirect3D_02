//
//	CAnimetion.h
//		Author:HIROMASA IKEDA		DATE:2018/09/28
//===============================================
#pragma once
#ifndef ANIMETIONCLASS_H
#define ANIMETIONCLASS_H

#include"common.h"
#include"Texture.h"
#include"CTransform.h"

//===============================================
//	Animetion : 2D��p�@�N���X	
//===============================================
class Animetion
{
private:

public:
	int AnimePatern;			//�A�j���[�V����
	int MaxPatern;				//�ő�A�j���[�V����
	int YMaxPatern;				//���ő�A�j���[�V����
	int Waitframe;				//�A�j���[�V�������x
	int Createframe;			//�������ꂽ���̃t���[��

	//�R���X�g���N�^
	Animetion();
	Animetion(int MaxPatern,int YMaxPatern,int Waitframe);
};

#endif // !ANIMETIONCLASS_H

