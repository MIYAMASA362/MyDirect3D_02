//
//	Texture.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/13
//===============================================
#define _CRT_SECURE_NO_WARNINGS
#include<d3dx9.h>
#include<math.h>
#include"Texture.h"
#include"System.h"
#include"Animation.h"

#define TEXTURE_FILE ("Texture/")
#define TEXTURE_NAME_NUM (60)

static int g_FrameCounter;

namespace NTexture
{
	//==============================================
	//	構造体
	//==============================================
	struct Path
	{
		Name name;
		const char TextureName[TEXTURE_NAME_NUM];
	};

	//==============================================
	//	テクスチャのパス
	//==============================================
	static Path path[] =
	{
		{ CubeTexture,"tex.png" },
		{ BillBoardTex,"bullet000.png" },
		{ MeshFieldTex,"MeshGround.jpg" },
		{ MeshCylinderTex,"skytex1.jpeg" },
		{ Billboard_Burst,"bomb.png" },
		{ Billboard_Shadow,"shadow000.jpg" },
		{ Billboard_Wall,"KAZTDSCF8777_TP_V.jpg" }
	};

	//==============================================
	//	グローバル変数
	//==============================================
	static Data Index[Name::NAME_END];	//データ

	//==============================================
	//	関数
	//==============================================

	//------------------------------------
	//	Load
	//------------------------------------
	void Load()
	{
		HRESULT hr;
		char ErrorText[256] = {};
		int failded_Count = 0;		//読み込み失敗数。

		for (int i = 0; i < Name::NAME_END; i++)
		{
			char FilePath[TEXTURE_NAME_NUM + 10] = {'\0'};
			D3DXIMAGE_INFO Texture_Info;	//画像データ情報

			strcat(&FilePath[0],TEXTURE_FILE);
			strcat(&FilePath[0],path[i].TextureName);

			//読み込みが失敗した時にはg_pTexture[i]にnullが置かれる
			hr = D3DXCreateTextureFromFile(System_GetDevice(), FilePath, &Index[i].pTexture);

			if (FAILED(hr))
			{
				//エラーの表示
				strcat(ErrorText, path[i].TextureName);
				strcat(ErrorText, "\n");
				failded_Count++;
			}
			else
			{
				//画像データ取得
				D3DXGetImageInfoFromFile(path[i].TextureName, &Texture_Info);
				Index[i].height = Texture_Info.Height;
				Index[i].width = Texture_Info.Width;
			}
		}

		//読み込みに失敗している
		if (failded_Count != 0)
		{
			MessageBox(*System_GethWnd(), ErrorText, "読み込み失敗", MB_OK);
			DestroyWindow(*System_GethWnd());
		}

		return;
	}

	//------------------------------------
	//	UnLoad
	//------------------------------------
	void UnLoad()
	{
		for (int i = 0; i < Name::NAME_END; i++)
		{
			if (Index[i].pTexture != NULL)
			{
				Index[i].pTexture->Release();
				Index[i].pTexture = NULL;
			}
		}
	}

	//------------------------------------
	//	初期化処理
	//------------------------------------
	void Initialize()
	{
		Load();
		FrameInit();	//フレームを初期化
	}

	//------------------------------------
	//	終了処理
	//------------------------------------
	void Finalize()
	{
		UnLoad();
	}

	//------------------------------------
	//	Get_Texture
	//------------------------------------
	LPDIRECT3DTEXTURE9 Get_Texture(const Name name)
	{
		if (name == NAME_END || name == NAME_NONE) return NULL;
		return Index[name].pTexture;
	}

	//------------------------------------
	//	Get_Data
	//------------------------------------
	Data* Get_Data(const Name name)
	{
		if (name == NAME_END || name == NAME_NONE) return NULL;
		return &Index[name];
	}

	//------------------------------------
	//	Get_Width
	//------------------------------------
	UINT Get_Width(const Name name)
	{
		if (name == NAME_END || name == NAME_NONE) return NULL;
		return Index[name].width;
	}

	//------------------------------------
	//	Get_Height
	//------------------------------------
	UINT Get_Height(const Name name)
	{
		if (name == NAME_END || name == NAME_NONE) return NULL;
		return Index[name].height;
	}


	//==============================================
	//	ATexture	抽象クラス
	//==============================================

	//------------------------------------
	//	コンストラクタ
	//------------------------------------
	ATexture::ATexture(Name name)
	{
		this->name = name;
	}

	//------------------------------------
	//	デストラクタ
	//------------------------------------
	ATexture::~ATexture()
	{

	}

	//------------------------------------
	//	Get_Width	・元画像の幅を返します。
	//------------------------------------
	UINT ATexture::Get_Width()
	{
		return NTexture::Get_Width(this->name);
	}

	//------------------------------------
	//	Get_Height
	//------------------------------------
	UINT ATexture::Get_Height()
	{
		return NTexture::Get_Height(this->name);
	}

	//------------------------------------
	//	Get_Data
	//------------------------------------
	LPDIRECT3DTEXTURE9 ATexture::Get_Texture()
	{
		return NTexture::Get_Texture(this->name);
	}

	//==============================================
	//	CTexture	基本クラス
	//==============================================

	//------------------------------------
	//	コンストラクタ
	//------------------------------------

	CTexture::CTexture(Name name, D3DXVECTOR2 Coord, D3DXVECTOR2 Scale) :ATexture(name)
	{
		this->Coord = Coord;
		this->Scale = Scale;
	}

	//------------------------------------
	//	デストラクタ
	//------------------------------------
	CTexture::~CTexture()
	{

	}

	//------------------------------------
	//	Get_Coord
	//------------------------------------
	D3DXVECTOR2 CTexture::Get_Coord()
	{
		return this->Coord;
	}

	//------------------------------------
	//	Get_Size
	//------------------------------------
	D3DXVECTOR2 CTexture::Get_Scale()
	{
		return this->Scale;
	}

	//------------------------------------
	//	Set_Coord
	//------------------------------------
	void CTexture::Set_Coord(D3DXVECTOR2 Coord)
	{
		this->Coord = Coord;
		return;
	}

	//------------------------------------
	//	Set_Size
	//------------------------------------
	void CTexture::Set_Scale(D3DXVECTOR2 Scale)
	{
		this->Scale = Scale;
		return;
	}

	//==============================================
	//	CAnimation
	//==============================================

	//------------------------------------
	//	コンストラクタ
	//------------------------------------
	CAnimation::CAnimation(int AnimaPatern, int MaxPatern, int YMaxPatern, int Waitframe)
	{
		this->AnimaPatern = AnimaPatern;
		this->MaxPatern = MaxPatern;
		this->YMaxPatern = YMaxPatern;
		this->Waitframe = Waitframe;
		this->Createframe = Get_Frame();
	}

	//------------------------------------
	//	デストラクタ
	//------------------------------------
	CAnimation::~CAnimation()
	{
	
	}

	//------------------------------------
	//	Loop
	//------------------------------------
	bool CAnimation::Loop()
	{
		this->AnimaPatern = (g_FrameCounter / this->Waitframe) % this->MaxPatern;
		return this->AnimaPatern >= this->MaxPatern;
	}

	//------------------------------------
	//	NoLoop
	//------------------------------------
	bool CAnimation::NoLoop()
	{
		this->AnimaPatern = min((g_FrameCounter / this->Waitframe), this->MaxPatern);
		return this->AnimaPatern >= this->MaxPatern;
	}

}

