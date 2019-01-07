//
//	Animetion.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/28
//===============================================
#include<d3dx9.h>
#include<math.h>

#include"Texture.h"
#include"CTexture.h"
#include"CTransform.h"
#include"Sprite.h"
#include"Animetion.h"
#include"CAnimetion.h"

//==============================================
//	�O���[�o���ϐ��錾
//==============================================
static int g_FrameCounter;	//�E�t���[���J�E���^

//===============================================
//	�t���[���ݒ�
//===============================================
void Animetion_Initialize()
{
	g_FrameCounter = 0;
}

//===============================================
//	�t���[���擾	
//===============================================
int Animetion_GetFrame()
{
	return g_FrameCounter;
}

//===============================================
//	�t���[���X�V
//===============================================
void Animetion_Update()
{
	g_FrameCounter++;
}

//===============================================
//	�A�j���[�V���� NOLOOP
//===============================================
bool Animetion_NoLoop(Transform2* pTransform,Texture* pTexture,Animetion* pAnimetion)
{
	float width  = (float)pTexture->GetWidth();
	float height = (float)pTexture->GetHeight();

	pAnimetion->AnimePatern  = min((g_FrameCounter / pAnimetion->Waitframe),pAnimetion->MaxPatern);

	Texture Tex = *pTexture;
	Tex.TexCoord = { pTexture->TexScale.width * (pAnimetion->AnimePatern % pAnimetion->YMaxPatern),pTexture->TexScale.height * (pAnimetion->AnimePatern / pAnimetion->YMaxPatern) };
	Render2D_Texture_Clip(pTransform,&Tex);

	return pAnimetion->AnimePatern >= pAnimetion->MaxPatern;
}

//===============================================
//	�A�j���[�V���� LOOP
//===============================================
void Animetion_Loop(Transform2* pTransform,Texture* pTexture,Animetion* pAnimetion)
{
	float width  = (float)pTexture->GetWidth();
	float height = (float)pTexture->GetHeight();

	pAnimetion->AnimePatern = (g_FrameCounter / pAnimetion->Waitframe) % pAnimetion->MaxPatern;

	Texture Tex = *pTexture;
	Tex.TexCoord = { pTexture->TexScale.width * (pAnimetion->AnimePatern % pAnimetion->YMaxPatern),pTexture->TexScale.height * (pAnimetion->AnimePatern / pAnimetion->YMaxPatern) };
	Render2D_Texture_Clip(pTransform,&Tex);
}

//===============================================
//	��]�A�j���[�V����
//===============================================
void Animetion_Loop_Rotate(Transform2* pTransform,Texture* pTexture,Animetion* pAnimetion)
{
	float width  = (float)pTexture->GetWidth();
	float height = (float)pTexture->GetHeight();

	pAnimetion->AnimePatern = (g_FrameCounter / pAnimetion->Waitframe) % pAnimetion->MaxPatern;

	Texture Tex = *pTexture;
	Tex.TexCoord = { pTexture->TexScale.width * (pAnimetion->AnimePatern % pAnimetion->YMaxPatern),pTexture->TexScale.height * (pAnimetion->AnimePatern / pAnimetion->YMaxPatern) };
	Render2D_Sprite_Rotate(pTransform,&Tex);
}

//===============================================
//	�X�R�A�A�j���[�V����
//===============================================
void Animetion_Score(Transform2* pTransform,Texture* pTexture,Animetion* pAnimetion, int Score, bool bLeft, bool bZero, int digitNum)
{
	int digit = 0, MaxScore = 1;
	TEXCOORD AnimeTex = {};

	//���擾
	for (digit = 0; digit < digitNum; digit++)
	{
		MaxScore *= 10;
	}

	//�J�E���g�I�[�o�[
	if (Score >= MaxScore)
	{
		Score = MaxScore - 1;
	}

	//���l��
	if (bLeft)
	{
		//�����擾
		digit = 0;
		for (int score = Score; score > 0; digit++)
		{
			score /= 10;
		}

		//���l��
		D3DXVECTOR2 position = { pTransform->Position.x + (pTransform->Scale.x * 0.5f) * digit,pTransform->Position.y };
		while (digit > 0)
		{
			Transform2 transform2 = *pTransform;
			Texture AnimeTex = *pTexture;

			int AnimePatern = Score % 10;
			AnimeTex.TexCoord = { pTexture->TexScale.width * (AnimePatern % pAnimetion->YMaxPatern), pTexture->TexScale.height *(AnimePatern / pAnimetion->YMaxPatern) };
			transform2.Position = { position.x - (pTransform->Scale.x * 0.5f),position.y };
			Render2D_Sprite(&transform2,&AnimeTex);
			Score /= 10;
			digit--;
		}
	}
	//�E�l��
	else
	{
		//�ʒu����
		D3DXVECTOR2 position( (pTransform->Scale.x * 0.7f) * digit,pTransform->Position.y );

		//0����
		if (!bZero)
		{
			digit = 0;
			int score = Score;
			do
			{
				score /= 10;
				digit++;
			} while (score > 0);
		}
		//�E�l��
		while (digit > 0)
		{
			Transform2 transform2 = *pTransform;
			Texture AnimeTex = *pTexture;
			
			int AnimePatern = Score % 10;
			AnimeTex.TexCoord = { pTexture->TexScale.width * (AnimePatern % pAnimetion->YMaxPatern),pTexture->TexScale.height *(AnimePatern / pAnimetion->YMaxPatern) };
			transform2.Position = { position.x - (pTransform->Scale.x * 0.75f),position.y };
			Render2D_Sprite(&transform2,&AnimeTex);
			Score /= 10;
			digit--;
		}
	}
}
