//
//	FileData.cpp
//		USER:HIROMASA IKEDA		DATE:2018/09/11
//===============================================
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"System.h"
#include"FileData.h"

//===============================================
//	�O���[�o���ϐ�
//===============================================
static FILE* pFile;

//===============================================
//	FileOpen	
//===============================================
bool File_Open(const char* FileName)
{
	pFile = NULL;
	pFile = fopen(FileName,"rb+");

	if(pFile == NULL)
	{
		MessageBox(*System_GethWnd(), "�Z�[�u�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B", "�ǂݍ��ݎ��s", MB_OK);
		DestroyWindow(*System_GethWnd());
		return false;
	}

	return true;
}

//===============================================
//	File_SeekTop()
//===============================================
void File_SeekTop()
{
	fseek(pFile,0L,SEEK_SET);
}

//===============================================
//	File_Get()
//===============================================
FILE* File_Get()
{
	return pFile;
}

//===============================================
//	File_Close()
//===============================================
void File_Close()
{
	fclose(pFile);
}
