//
//	Scene.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef SCENE_H
#define SCENE_H

//================================================
//	インクルード	include
//================================================
#include"common.h"

#include<d3dx9.h>
#include"Behavior.h"
//================================================
//	マクロ定義	define
//================================================


//================================================
//	列挙型		enum
//================================================


//================================================
//	構造体		struct/typedef
//================================================


//================================================
//	グローバル変数　global
//================================================


//================================================
//	クラス		class
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
		virtual void Initialize() PURE;		//初期化
		virtual void UpdateBegin() PURE;	//前更新
		virtual void Render() PURE;			//描画
		virtual void UpdateEnd() PURE;		//後更新
		virtual void Finalize() PURE;		//終了
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