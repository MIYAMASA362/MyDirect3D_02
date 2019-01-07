//
//	Texture.h
//		Auther:HIROMASA IKEDA	Date:2018/09/13
//===============================================
#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include<d3dx9.h>
#include"common.h"

//===============================================
//	�}�N����`
//===============================================
#define TEXTURE_FILENAME_MAX (64)

//===============================================
//	���O���
//===============================================
namespace NTexture
{
	//==============================================
	//	�f�[�^
	//==============================================
	struct Data
	{
		LPDIRECT3DTEXTURE9 pTexture;
		UINT width;
		UINT height;
	};

	//==============================================
	//	�e�N�X�`����
	//==============================================
	enum Name
	{
		CubeTexture,
		BillBoardTex,
		MeshFieldTex,
		MeshCylinderTex,
		Billboard_Burst,
		Billboard_Shadow,
		Billboard_Wall,
		NAME_END,	//�e�N�X�`���I���
		NAME_NONE		//�w�薳���ꍇ
	};

	//==============================================
	//	�֐�
	//==============================================
	void Initialize();
	void Finalize();
	LPDIRECT3DTEXTURE9 Get_Texture(const Name name);
	Data* Get_Data(const Name name);
	UINT Get_Width(const Name name);
	UINT Get_Height(const Name name);

	//==============================================
	//	ATexture	���ۃN���X
	//==============================================
	class ATexture
	{
	public:
		Name name;				//�E�e�N�X�`����

	public:
		//�R���X�g���N�^
		ATexture() :ATexture(Name::NAME_NONE) {};
		ATexture(Name name);

		//�f�X�g���N�^
		~ATexture();

	public:
		UINT Get_Width();		//�E���摜�̕���Ԃ��܂��B
		UINT Get_Height();		//�E���摜�̍�����Ԃ��܂��B
		LPDIRECT3DTEXTURE9 Get_Texture();	//�E�e�N�X�`���f�[�^�̎擾�B
	};

	//==============================================
	//	CTexture	��{�e�N�X�`��
	//==============================================
	class CTexture:public ATexture
	{
	public:
		D3DXVECTOR2 Coord;	//�E�e�N�X�`�����W(����)
		D3DXVECTOR2 Scale;	//�E�e�N�X�`���T�C�Y

	public:
		CTexture() :CTexture(Name::NAME_NONE,{ 0.0f,0.0f }, { 0.0f,0.0f }) {};
		CTexture(Name name, D3DXVECTOR2 Coord, D3DXVECTOR2 Scale);
		~CTexture();

	public:
		//Get
		D3DXVECTOR2 Get_Coord();	//�E�e�N�X�`�����W��Ԃ��܂��B
		D3DXVECTOR2 Get_Scale();		//�E�e�N�X�`���T�C�Y��Ԃ��܂��B
	
		//Set
		void Set_Coord(D3DXVECTOR2 Coord);	//�E�e�N�X�`�����W��ݒ肵�܂��B
		void Set_Scale(D3DXVECTOR2 Scale);	//�E�e�N�X�`���T�C�Y��ݒ肵�܂��B
	};

	//==============================================
	//	CAnimation	�A�j���[�V����
	//==============================================
	class CAnimation
	{
	public:

	public:
		int AnimaPatern;			//�A�j���[�V����
		int MaxPatern;				//�ő�A�j���[�V����
		int YMaxPatern;				//���ő�A�j���[�V����
		int Waitframe;				//�A�j���[�V�������x
		int Createframe;			//�������ꂽ���̃t���[��

	public:
		CAnimation() :CAnimation(0, 0, 0, 1) {};
		CAnimation(int MaxPatern, int YMaxPatern, int Waitframe) :CAnimation(0, MaxPatern, YMaxPatern, Waitframe) {};
		CAnimation(int AnimaPatern, int MaxPatern, int YMaxPatern, int Waitframe);
		~CAnimation();

	public:
		bool Loop();		//���[�v����
		bool NoLoop();		//���[�v���Ȃ�

	};
}
#endif
