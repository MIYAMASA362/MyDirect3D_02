//
//	FileData.h
//		Author:HIROMASA IKEDA	DATE:2018/09/11
//===============================================
#pragma once
#ifndef FILEDATA_H
#define FILEDATA_H

#include<stdio.h>

//===============================================
//	�֐�
//===============================================
bool File_Open(const char* FileName);	//�t�@�C���̓ǂݍ���
void File_SeekTop();					//�擪��Seek
FILE* File_Get();						//�t�@�C���擾
void File_Close();						//�t�@�C�����N���[�Y

#endif // !FILEDATA_H




