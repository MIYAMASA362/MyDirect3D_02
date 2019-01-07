//
//	Debug_font.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/20
//===============================================
//
//	����������Ȃ��B�����~�X���Ă�
//
//-----------------------------------------------
#include<d3dx9.h>
#include<stdio.h>
#include"System.h"
#include"debug_font.h"

//===============================================
//	�}�N����`
//===============================================
#define DEBUG_PRINTF_BUFFER_MAX (256) // ������p�o�b�t�@�ʁi���Ȃ��Ƃ��͑��₷���Ɓj

//===============================================
//	�t�H���g
//===============================================
#if defined(_DEBUG) || defined(DEBUG)
static LPD3DXFONT g_pD3DXFont = NULL;
#endif

//===============================================
//	����������
//===============================================
void DebugFont_Initialize(void) 
{
#if defined(_DEBUG) || defined(DEBUG)
	LPDIRECT3DDEVICE9 pD3DDevice = System_GetDevice();
	D3DXCreateFont(
		pD3DDevice,
		16,
		0,
		0,
		0,
		FALSE,
		SHIFTJIS_CHARSET,	//���{��g���Ȃ炱��
		OUT_DEFAULT_PRECIS,	
		DEFAULT_QUALITY,
		DEFAULT_PITCH,	//������
		"Terminal",	//�t�H���g
		&g_pD3DXFont
	);
#endif
}

//===============================================
//	�I������
//===============================================
void DebugFont_Finalize(void) 
{
#if defined(_DEBUG) || defined(DEBUG)
	if (g_pD3DXFont) 
	{
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}
#endif
}

//===============================================
//	�`��
//===============================================
void DebugFont_Draw(int x,int y,const char* pFormat, ...) 
{
#if defined(_DEBUG) || defined(DEBUG)
	//���̋�`�Ƀt�H���g�|���S���\���Ă��銴��
	RECT rect = {x,y,WINDOWSCREEN_WIDTH,WINDOWSCREEN_HEIGHT};
	
	va_list argp;
	va_start(argp, pFormat);
	// ������p�o�b�t�@
	char buf[DEBUG_PRINTF_BUFFER_MAX];
	vsprintf_s(buf, DEBUG_PRINTF_BUFFER_MAX, pFormat, argp);
	va_end(argp);
	
	g_pD3DXFont->DrawText(
		NULL,
		buf,
		-1,	//�w�肵����������\��(-1���ƑS��)
		&rect,
		DT_LEFT,
		D3DCOLOR_RGBA(0,255,0,255)	//�����F
		);
#else
	UNREFERENCED_PARAMETER(pFormat);
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);
#endif
}