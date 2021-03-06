//
//	Scene.cpp
//		Author:HIROMASA IKEDA	DATE:
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
#include"Scene.h"

//===============================================
//	マクロ定義		define
//===============================================

//===============================================
//	グローバル変数	global
//===============================================

//===============================================
//	クラス名		class
//===============================================
namespace NSCENE
{
	static AScene* g_Scene = NULL;			//現在のシーン
	static AScene* g_NextScene = NULL;		//次のシーン

	//========================================================
	//	AScene
	//========================================================

	//-------------------------------------
	//	コンストラクタ
	//-------------------------------------
	AScene::AScene()
	{
		this->pName = "";
	}

	//------------------------------------
	//	デストラクタ
	//------------------------------------
	AScene::~AScene()
	{
	
	}


	//==============================================
	//	初期化
	//==============================================
	void Initialize(AScene* Scene)
	{
		g_Scene = g_NextScene =Scene;
		g_Scene->Initialize();
	}

	//==============================================
	//	前更新
	//==============================================
	void UpdateBegin()
	{
		g_Scene->UpdateBegin();
	}

	//==============================================
	//	描画
	//==============================================
	void Render()
	{
		g_Scene->Render();
	}

	//==============================================
	//	後更新
	//==============================================
	void UpdateEnd()
	{
		g_Scene->UpdateEnd();
	}

	//==============================================
	//	終了
	//==============================================
	void Finalize()
	{
		g_Scene->Finalize();
	}

	//==============================================
	//	シーンチェック
	//==============================================
	void Check()
	{
		if(g_Scene != g_NextScene)
		{
			Finalize();		//終了
			Initialize(g_NextScene);	//初期化
		}
	}

	//==============================================
	//	シーン変換
	//==============================================
	void Change(AScene* NextScene)
	{
		g_NextScene = NextScene;
	}

}

