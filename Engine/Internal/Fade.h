//
//	Fade.h
//		Author:HIROMASA IEKDA		DATE:2018/07/11
//===============================================
//
//	�g���ĂȂ�
//
//-----------------------------------------------
#pragma once
#ifndef FADE_H
#define FADE_H

#include<d3dx9.h>
#include"common.h"

//===============================================
//	�֐�
//===============================================
void Fade_Initialize();
void Fade_Update();
void Fade_Render();
void Fade_Triger(bool bOut, int frame, D3DCOLOR Color);

bool Fade_IsFade();
bool Fade_Alpha();

#endif // !FADE_H


