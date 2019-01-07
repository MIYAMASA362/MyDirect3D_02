//
//	Title.cpp
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"

//class
#include"Title.h"
#include"CRender.h"
#include"CMesh.h"
#include"CCamera.h"

//===============================================
//	マクロ定義		define
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
//	グローバル変数	global
//===============================================
TitleScene g_Title;	//タイトルScene
Object object;

//===============================================
//	関数
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
