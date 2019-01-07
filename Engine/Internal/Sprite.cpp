//
//	Sprite.cpp
//		Author:HIROMASA IKEDA	Date:2018/09/13
//===============================================
#define _USE_MATH_DEFINES
#include<math.h>

#include"Texture.h"
#include"Sprite.h"
#include"CTransform.h"
#include"System.h"

//===============================================
//	�}�N����`
//===============================================
#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define FVF_TEXVERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//===============================================
//	�O���[�o���ϐ�
//===============================================
static LPDIRECT3DDEVICE9		g_pD3DDevice	= NULL;

//===============================================
//	�f�o�C�X�ݒ�
//===============================================
void Sprite_SetDevice(LPDIRECT3DDEVICE9 pD3DDevice)
{
	g_pD3DDevice = pD3DDevice;
	return;
}

//===============================================
//	�|���S��
//===============================================
void Render2D_Porigon(const Transform2* pTransform2)
{
	float width		= pTransform2->Scale.x * 0.5f;
	float height	= pTransform2->Scale.y * 0.5f;

	Vertex2D Porigon[4] =
	{
		{ D3DXVECTOR4(pTransform2->Position.x - width,pTransform2->Position.y - height,0.0f,1.0f),pTransform2->Color },
		{ D3DXVECTOR4(pTransform2->Position.x + width,pTransform2->Position.y - height,0.0f,1.0f),pTransform2->Color },
		{ D3DXVECTOR4(pTransform2->Position.x - width,pTransform2->Position.y + height,0.0f,1.0f),pTransform2->Color },
		{ D3DXVECTOR4(pTransform2->Position.x + width,pTransform2->Position.y + height,0.0f,1.0f),pTransform2->Color },
	};

	g_pD3DDevice->SetFVF(FVF_VERTEX2D);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Porigon, sizeof(Porigon[0]));
}

//===============================================
//	�~�|���S��
//===============================================
void Render2D_Porigon_Circle(const Transform2* pTransform2,float radius)
{
	float angle = 30;
	angle *=(float)M_PI / 180;

	Vertex2D Porigon[14];

	for(int i = 0; i < 14; i++)
	{
		if(i == 0)
		{
			Porigon[i].position.x = pTransform2->Position.x;
			Porigon[i].position.y = pTransform2->Position.y;
		}
		else
		{
			Porigon[i].position.x = cosf((i - 1) * angle) * radius + pTransform2->Position.x;
			Porigon[i].position.y = sinf((i - 1) * angle) * radius + pTransform2->Position.y;
		}

		Porigon[i].position.z = 0.0f;
		Porigon[i].position.w = 1.0f;
		Porigon[i].color = pTransform2->Color;
	}

	g_pD3DDevice->SetFVF(FVF_VERTEX2D);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 12, &Porigon, sizeof(Porigon[0]));
}


//===============================================
//	���C���`��
//===============================================
void Render2D_Line(D3DXVECTOR2 Vector1,D3DXVECTOR2 Vector2)
{
	D3DXVECTOR2 Line[] = { Vector1,Vector2 };

	LPD3DXLINE pLine;
	D3DXCreateLine(g_pD3DDevice,&pLine);
	pLine->SetWidth(10.0f);					//���̑���
	pLine->Begin();
	pLine->Draw(Line,2,D3DCOLOR_RGBA(255,0,0,255));
	pLine->End();
}

//===============================================
//	�|���S����]
//===============================================
void Render2D_Porigon_Rotate(const Transform2* pTransform2)
{
	float width  = pTransform2->Scale.x * 0.5f;
	float height = pTransform2->Scale.y * 0.5f;

	float Rotation = pTransform2->Rotation * (float)M_PI / 180.0f;

	float px[4] = { 0 };
	float py[4] = { 0 };

	px[0] = (-width) * cosf(Rotation) - (-height) * sinf(Rotation);
	py[0] = (-width) * sinf(Rotation) + (-height) * cosf(Rotation);

	px[1] = width * cosf(Rotation) - (-height) * sinf(Rotation);
	py[1] = width * sinf(Rotation) + (-height) * cosf(Rotation);

	px[2] = (-width) * cosf(Rotation) - height * sinf(Rotation);
	py[2] = (-width) * sinf(Rotation) + height * cosf(Rotation);

	px[3] = width * cosf(Rotation) - height * sinf(Rotation);
	py[3] = width * sinf(Rotation) + height * cosf(Rotation);

	Vertex2D Porigon[4] =
	{
		{ D3DXVECTOR4(px[0] + pTransform2->Position.x + width - 0.5f, py[0] + pTransform2->Position.y + height - 0.5f,	0.0f,1.0f),	pTransform2->Color},
		{ D3DXVECTOR4(px[1] + pTransform2->Position.x + width - 0.5f, py[1] + pTransform2->Position.y + height - 0.5f,	0.0f,1.0f),	pTransform2->Color},
		{ D3DXVECTOR4(px[2] + pTransform2->Position.x + width - 0.5f, py[2] + pTransform2->Position.y + height - 0.5f,	0.0f,1.0f),	pTransform2->Color},
		{ D3DXVECTOR4(px[3] + pTransform2->Position.x + width - 0.5f, py[3] + pTransform2->Position.y + height - 0.5f,	0.0f,1.0f),	pTransform2->Color}
	};

	g_pD3DDevice->SetFVF(FVF_VERTEX2D);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Porigon, sizeof(Porigon[0]));

}

//===============================================
//	�摜�T�C�Y�`��
//===============================================
void Render2D_Texture_Size(const Transform2* pTransform2,NTexture::CTexture* pTexture) 
{
	float width  = pTexture->Get_Width() * 0.5f;
	float height = pTexture->Get_Height() *0.5f;

	TexVertex2D Sprite[4] = 
	{
		{ D3DXVECTOR4(pTransform2->Position.x - width - 0.5f, pTransform2->Position.y - height - 0.5f, 0.0f,1.0f),pTransform2->Color,D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR4(pTransform2->Position.x + width - 0.5f, pTransform2->Position.y - height - 0.5f, 0.0f,1.0f),pTransform2->Color,D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR4(pTransform2->Position.x - width - 0.5f, pTransform2->Position.y + height - 0.5f, 0.0f,1.0f),pTransform2->Color,D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR4(pTransform2->Position.x + width - 0.5f, pTransform2->Position.y + height - 0.5f, 0.0f,1.0f),pTransform2->Color,D3DXVECTOR2(1.0f,1.0f) }
	};

	g_pD3DDevice->SetFVF(FVF_TEXVERTEX2D);
	g_pD3DDevice->SetTexture(0, NTexture::Get_Texture(pTexture->name));
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Sprite, sizeof(Sprite[0]));

}

//===============================================
//	�|���S���T�C�Y�ɕ`��
//===============================================
void Render2D_Texture_Fill(Transform2* pTransform2,NTexture::CTexture* pTexture) 
{
	float width  = pTransform2->Scale.x *0.5f;
	float height = pTransform2->Scale.y *0.5f;

	TexVertex2D Sprite[4] =
	{
		{ D3DXVECTOR4(pTransform2->Position.x - width - 0.5f, pTransform2->Position.y - height - 0.5f, 0.0f,1.0f),pTransform2->Color,D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR4(pTransform2->Position.x + width - 0.5f, pTransform2->Position.y - height - 0.5f, 0.0f,1.0f),pTransform2->Color,D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR4(pTransform2->Position.x - width - 0.5f, pTransform2->Position.y + height - 0.5f, 0.0f,1.0f),pTransform2->Color,D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR4(pTransform2->Position.x + width - 0.5f, pTransform2->Position.y + height - 0.5f, 0.0f,1.0f),pTransform2->Color,D3DXVECTOR2(1.0f,1.0f) }
	};

	g_pD3DDevice->SetFVF(FVF_TEXVERTEX2D);
	g_pD3DDevice->SetTexture(0, pTexture->Get_Texture());
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Sprite, sizeof(Sprite[0]));

}

//===============================================
//	�e�N�X�`���̐؂蔲���T�C�Y
//===============================================
void Render2D_Texture_Clip(Transform2* pTransform2,NTexture::CTexture* pTexture)
{
	float width  = (float)pTexture->Get_Width();
	float height = (float)pTexture->Get_Height();

	float u0 = (float)pTexture->Coord.x / width;
	float v0 = (float)pTexture->Coord.y / height;
	float u1 = u0 + (float)pTexture->Scale.x / width;
	float v1 = v0 + (float)pTexture->Scale.y / height;

	width  = pTexture->Scale.x  * 0.5f;
	height = pTexture->Scale.y * 0.5f;

	TexVertex2D Sprite[4] =
	{
		{ D3DXVECTOR4(pTransform2->Position.x - width - 0.5f, pTransform2->Position.y - height - 0.5f, 0.0f,1.0f), pTransform2->Color, D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(pTransform2->Position.x + width - 0.5f, pTransform2->Position.y - height - 0.5f, 0.0f,1.0f), pTransform2->Color, D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(pTransform2->Position.x - width - 0.5f, pTransform2->Position.y + height - 0.5f, 0.0f,1.0f), pTransform2->Color, D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(pTransform2->Position.x + width - 0.5f, pTransform2->Position.y + height - 0.5f, 0.0f,1.0f), pTransform2->Color, D3DXVECTOR2(u1,v1) }
	};

	g_pD3DDevice->SetFVF(FVF_TEXVERTEX2D);
	g_pD3DDevice->SetTexture(0, pTexture->Get_Texture());
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Sprite, sizeof(Sprite[0]));

}

//===============================================
//	�X�v���C�g�`��
//===============================================
void Render2D_Sprite(Transform2* pTransform2,NTexture::CTexture* pTexture)
{
	float width		= (float)pTexture->Get_Width();
	float height	= (float)pTexture->Get_Height();

	float u0 =		(float)pTexture->Coord.x		 / width;
	float v0 =		(float)pTexture->Coord.y		 / height;
	float u1 = u0 + (float)pTexture->Scale.x  / width;
	float v1 = v0 + (float)pTexture->Scale.y / height;

	width  = pTransform2->Scale.x * 0.5f;
	height = pTransform2->Scale.y * 0.5f;

	TexVertex2D Sprite[4] =
	{
		{ D3DXVECTOR4(pTransform2->Position.x - width - 0.5f, pTransform2->Position.y - height - 0.5f, 0.0f,1.0f), pTransform2->Color, D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(pTransform2->Position.x + width - 0.5f, pTransform2->Position.y - height - 0.5f, 0.0f,1.0f), pTransform2->Color, D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(pTransform2->Position.x - width - 0.5f, pTransform2->Position.y + height - 0.5f, 0.0f,1.0f), pTransform2->Color, D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(pTransform2->Position.x + width - 0.5f, pTransform2->Position.y + height - 0.5f, 0.0f,1.0f), pTransform2->Color, D3DXVECTOR2(u1,v1) }
	};

	g_pD3DDevice->SetFVF(FVF_TEXVERTEX2D);
	g_pD3DDevice->SetTexture(0, pTexture->Get_Texture());
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Sprite, sizeof(Sprite[0]));

}

//===============================================
//	�X�v���C�g�`��
//===============================================
void Render2D_Sprite_Rotate(Transform2* pTransform2,NTexture::CTexture* pTexture)
{
	float width  = pTransform2->Scale.x * 0.5f;
	float height = pTransform2->Scale.y * 0.5f;

	float Rotation = pTransform2->Rotation * (float)M_PI / 180.0f;

	float px[4] = { 0 };
	float py[4] = { 0 };

	px[0] = (-width)*cosf(Rotation) - (-height) * sinf(Rotation);
	py[0] = (-width)*sinf(Rotation) + (-height) * cosf(Rotation);

	px[1] = width * cosf(Rotation) - (-height) * sinf(Rotation);
	py[1] = width * sinf(Rotation) + (-height) * cosf(Rotation);

	px[2] = (-width) * cosf(Rotation) - height * sinf(Rotation);
	py[2] = (-width) * sinf(Rotation) + height * cosf(Rotation);

	px[3] = width * cosf(Rotation) - height * sinf(Rotation);
	py[3] = width * sinf(Rotation) + height * cosf(Rotation);
	
	width  = (float)pTexture->Get_Width();
	height = (float)pTexture->Get_Height();

	float u0 = pTexture->Coord.x / width;
	float v0 = pTexture->Coord.y / height;
	float u1 = u0 + pTexture->Scale.x / width;
	float v1 = v0 + pTexture->Scale.y / height;

	width  = pTransform2->Scale.x  * 0.5f;
	height = pTransform2->Scale.y * 0.5f;

	TexVertex2D Sprite[4] =
	{
		{ D3DXVECTOR4(px[0] + pTransform2->Position.x + width - 0.5f, py[0] + pTransform2->Position.y + height - 0.5f,	0.0f,1.0f),	pTransform2->Color,	D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(px[1] + pTransform2->Position.x + width - 0.5f, py[1] + pTransform2->Position.y + height - 0.5f,	0.0f,1.0f),	pTransform2->Color,	D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(px[2] + pTransform2->Position.x + width - 0.5f, py[2] + pTransform2->Position.y + height - 0.5f,	0.0f,1.0f),	pTransform2->Color,	D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(px[3] + pTransform2->Position.x + width - 0.5f, py[3] + pTransform2->Position.y + height - 0.5f,	0.0f,1.0f),	pTransform2->Color,	D3DXVECTOR2(u1,v1) }
	};

	g_pD3DDevice->SetFVF(FVF_TEXVERTEX2D);
	g_pD3DDevice->SetTexture(0, pTexture->Get_Texture());
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Sprite, sizeof(Sprite[0]));

}
