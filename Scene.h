//
//	Scene.h
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef SCENE_H
#define SCENE_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"

#include<d3dx9.h>
#include"Behavior.h"
//================================================
//	�}�N����`	define
//================================================


//================================================
//	�񋓌^		enum
//================================================


//================================================
//	�\����		struct/typedef
//================================================


//================================================
//	�O���[�o���ϐ��@global
//================================================


//================================================
//	�N���X		class
//================================================
namespace NSCENE
{
	//-------------------------------------
	//	AScene
	//-------------------------------------
	class AScene
	{
	public:
		char* pName;
	public:
		AScene();
		~AScene();
	public:
		virtual void Initialize() PURE;		//������
		virtual void UpdateBegin() PURE;	//�O�X�V
		virtual void Render() PURE;			//�`��
		virtual void UpdateEnd() PURE;		//��X�V
		virtual void Finalize() PURE;		//�I��
	};

	void Initialize(AScene* Scene);
	void UpdateBegin();
	void Render();
	void UpdateEnd();
	void Finalize();

	void Check();
	void Change(AScene* NextScene);
}

#endif