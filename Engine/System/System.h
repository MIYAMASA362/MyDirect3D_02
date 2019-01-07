//
//	System.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/13
//===============================================
#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H

#include<d3dx9.h>
#include"common.h"

//===============================================
//	�}�N����`
//===============================================
#define CLASS_NAME		("GameWindow")

#ifndef WINDOW_STYLE				//�E�B���h�E�X�^�C��
#define WINDOW_STYLE	(WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX  | WS_THICKFRAME))
#endif // !WINDOW_STYLE

#ifndef WINDOW_CAPTION				//�E�B���h�E��
#define WINDOW_CAPTION	("NONE")
#endif // !WINDOW_CAPTION

#ifndef BG_COLOR					//�w�i�F
#define BG_COLOR (D3DCOLOR_RGBA(75, 75, 75, 255))
#endif // !BG_COLOR

#ifndef WINDOWSCREEN_WIDTH			//�X�N���[����
#define WINDOWSCREEN_WIDTH (1024)
#endif // !WINDOWSCREEN_WIDTH

#ifndef WINDOWSCREEN_HEIGHT			//�X�N���[���c
#define WINDOWSCREEN_HEIGHT (576)
#endif // !WINDOWSCREEN_HEIGHT

#define DEBUG_KEY_ENABLE	//�f�o�b�O�L�[�̗L��

//===============================================
//	���C���֐�
//===============================================
void Main_Initialize(void);		//������
void Main_UpdateBegin(void);	//�O�X�V
void Main_Render(void);			//�`��
void Main_UpdateEnd(void);		//��X�V
void Main_Finalize(void);		//�I��

//===============================================
//	�֐�	
//===============================================
HWND *System_GethWnd();
HINSTANCE *System_GethInstance();

#ifndef INPUT_H
LPDIRECT3DDEVICE9 System_GetDevice(void);
#endif // !INPUT_H

#endif // !SYSTEM_CPP

