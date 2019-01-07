//
//	Title.cpp
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"

//class
#include"Title.h"
#include"CRender.h"
#include"CMesh.h"
#include"CCamera.h"

//===============================================
//	�}�N����`		define
//===============================================

class TitleScene : public NSCENE::AScene
{
public:
	void Initialize();
	void UpdateBegin();
	void Render();
	void UpdateEnd();
	void Finalize();
};

class Object
{
public:
	CXModelMesh model;
	CTransform transform;
};

//===============================================
//	�O���[�o���ϐ�	global
//===============================================
TitleScene g_Title;	//�^�C�g��Scene
Object object;

//===============================================
//	�֐�
//===============================================
void TitleScene::Initialize()
{
	this->pName = "TitleScene";
	NXModel::Load_XModelMesh(&object.model,"Airplane.x","Airplane");
}

void TitleScene::UpdateBegin()
{

}

void TitleScene::Render()
{
	NRender3D::Render(&object.model,&object.transform);
}

void TitleScene::UpdateEnd()
{

}

void TitleScene::Finalize()
{

}

//===============================================
//	Get_TitleScene
//===============================================
NSCENE::AScene* Get_TitleScene()
{
	return &g_Title;
}
