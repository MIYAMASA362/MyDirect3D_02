//
//	Main.cpp
//		Author:HIROMASA IKEDA		Date:2018/10/22
//================================================
#include"common.h"
#include<time.h>
#include<math.h>
#include"System.h"
#include"input.h"

#include"Lighting.h"
#include"XModel.h"

#include"Billboard.h"

//Class
#include"CUI.h"
#include"CGameObject.h"
#include"CCamera.h"

#include"CTransform.h"

#include"WinSock.h"
#include"CAirplane.h"
#include"Grid.h"
#include"CBullet.h"
#include"Animation.h"
#include"CBurst.h"

#include"MeshField.h"
#include"FbxModel.h"

//Scene
#include"Scene.h"
#include"Title.h"

//===============================================
//	グローバル変数
//===============================================

//カメラ
static OperationCamera g_Camera(
	{0,5,5}
);

static CAirplane Airplane(
	&Transform(
		{ 0.0f,2.0f,0.0f },
		{ 0.005f,0.005f,0.005f },
		{ 0.0f, 0.0f, 0.0f}
	)
);

static GameObject Object(
	&Transform(
		{0.0f,2.0f,0.0f},
		{1.0f,1.0f,1.0f}
	)
);

static NTexture::CTexture texture(NTexture::Billboard_Burst, { 0.0f,0.0f }, {128,128});
static NTexture::CAnimation animation(18,6,4);

//=============================================================
//	初期化処理
//=============================================================
void Main_Initialize(void)
{
	Billboard_Initialize();
	NXModel::Initialize();

	//g_Camera.Set_Main();
	Airplane.Boarding();
	

	//Grid_Initialize();
	NMeshField::Initialize();
	fbx::Initialize();
	fbx::Finalize();

	//最初のシーン読み込み
	//NSCENE::Initialize(Get_TitleScene());
}

//=============================================================
//	前 更新処理
//=============================================================
void Main_UpdateBegin(void)
{
	NTexture::FrameUpdate();
	
	Transform::ConvertReset();
	
	GameObject::g_Update();
	ABillboard::g_Update();
	CBullet::g_Update();
	CBurst::g_Update();

	//g_Camera.transform = Airplane.transform;

	//	カメラの向きで移動するやつ
	//----------------------------------------------
	g_Camera.Update();

	//NSCENE::UpdateBegin();
}

//=============================================================
//	描画処理
//=============================================================
void Main_Render(void)
{

	NMeshField::Render_SkyDome(D3DXVECTOR3(0.0f,0.0f,0.0f), NTexture::MeshCylinderTex);
	NMeshField::Render_Ground(D3DXVECTOR3(0.0f, 0.0f, 0.0f), NTexture::MeshFieldTex);
	
	BillBoardShadow_Create(Airplane.transform.position, { 1.0f,1.0f,1.0f });
	AnimaBillBoard_Create({ 0.0f,2.0f,0.0f }, {1.0f,1.0f,1.0f},&texture,&animation);
	CBurst::g_Render();

	ACamera::Begin();		//描画開始
	GameObject::g_Render();
	ABillboard::g_Render();
	CBullet::g_Render();

	//Grid_Render();
	//NSCENE::Render();
}


//=============================================================
//	後 処理
//=============================================================
void Main_UpdateEnd()
{
	//NSCENE::UpdateEnd();
}

//=============================================================
//	終了処理
//=============================================================
void Main_Finalize(void)
{
	//NSCENE::Finalize();
	BillBoard_Finalaize();
	NMeshField::Finalize();
	CBullet_Finalize();
	NXModel::Finalize();
}
