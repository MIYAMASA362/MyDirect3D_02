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
//	マクロ定義
//===============================================
#define TEXTURE_FILENAME_MAX (64)

//===============================================
//	名前空間
//===============================================
namespace NTexture
{
	//==============================================
	//	データ
	//==============================================
	struct Data
	{
		LPDIRECT3DTEXTURE9 pTexture;
		UINT width;
		UINT height;
	};

	//==============================================
	//	テクスチャ名
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
		NAME_END,	//テクスチャ終わり
		NAME_NONE		//指定無い場合
	};

	//==============================================
	//	関数
	//==============================================
	void Initialize();
	void Finalize();
	LPDIRECT3DTEXTURE9 Get_Texture(const Name name);
	Data* Get_Data(const Name name);
	UINT Get_Width(const Name name);
	UINT Get_Height(const Name name);

	//==============================================
	//	ATexture	抽象クラス
	//==============================================
	class ATexture
	{
	public:
		Name name;				//・テクスチャ名

	public:
		//コンストラクタ
		ATexture() :ATexture(Name::NAME_NONE) {};
		ATexture(Name name);

		//デストラクタ
		~ATexture();

	public:
		UINT Get_Width();		//・元画像の幅を返します。
		UINT Get_Height();		//・元画像の高さを返します。
		LPDIRECT3DTEXTURE9 Get_Texture();	//・テクスチャデータの取得。
	};

	//==============================================
	//	CTexture	基本テクスチャ
	//==============================================
	class CTexture:public ATexture
	{
	public:
		D3DXVECTOR2 Coord;	//・テクスチャ座標(左上)
		D3DXVECTOR2 Scale;	//・テクスチャサイズ

	public:
		CTexture() :CTexture(Name::NAME_NONE,{ 0.0f,0.0f }, { 0.0f,0.0f }) {};
		CTexture(Name name, D3DXVECTOR2 Coord, D3DXVECTOR2 Scale);
		~CTexture();

	public:
		//Get
		D3DXVECTOR2 Get_Coord();	//・テクスチャ座標を返します。
		D3DXVECTOR2 Get_Scale();		//・テクスチャサイズを返します。
	
		//Set
		void Set_Coord(D3DXVECTOR2 Coord);	//・テクスチャ座標を設定します。
		void Set_Scale(D3DXVECTOR2 Scale);	//・テクスチャサイズを設定します。
	};

	//==============================================
	//	CAnimation	アニメーション
	//==============================================
	class CAnimation
	{
	public:

	public:
		int AnimaPatern;			//アニメーション
		int MaxPatern;				//最大アニメーション
		int YMaxPatern;				//横最大アニメーション
		int Waitframe;				//アニメーション速度
		int Createframe;			//生成された時のフレーム

	public:
		CAnimation() :CAnimation(0, 0, 0, 1) {};
		CAnimation(int MaxPatern, int YMaxPatern, int Waitframe) :CAnimation(0, MaxPatern, YMaxPatern, Waitframe) {};
		CAnimation(int AnimaPatern, int MaxPatern, int YMaxPatern, int Waitframe);
		~CAnimation();

	public:
		bool Loop();		//ループ処理
		bool NoLoop();		//ループしない

	};
}
#endif
