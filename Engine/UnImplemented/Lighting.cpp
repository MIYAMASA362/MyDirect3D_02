//
//	Lighting.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/04
//===============================================
#include"Lighting.h"
#include"System.h"

//===============================================
//	�O���[�o���ϐ�
//===============================================
#define COLORVALUE_RGBA(r,g,b,a) D3DCOLORVALUE{r/255,g/255,b/255,a/255}

static D3DLIGHT9 g_DirectLight;
static D3DXVECTOR3 g_DirectLight_Direction;
static bool g_bMaterialEnable = false;				//�}�e���A�����L����

namespace NLighting
{
	//�������֐�
	void Initialize()
	{
		LPDIRECT3DDEVICE9 Device = System_GetDevice();

		//------------------------------------
		//	�`��ݒ�
		//------------------------------------
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//������������ON
		Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//�w�iDSET�̃u�����h�ݒ�
		Device->SetRenderState(D3DRS_ZENABLE, TRUE);						//�[�x��K�p

																			//�A���t�@�e�X�g
		Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		Device->SetRenderState(D3DRS_ALPHAREF, 200);
		Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//�e�N�X�`���|���S�����ߏ���

		Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

		//------------------------------------
		//	���C�e�B���O
		//------------------------------------
		Device->SetRenderState(D3DRS_LIGHTING, FALSE);	//���C�e�B���O��ON/OFF

		ZeroMemory(&g_DirectLight, sizeof(g_DirectLight));
		g_DirectLight.Type = D3DLIGHT_DIRECTIONAL;

		g_DirectLight_Direction = D3DXVECTOR3(0.0f, -1.0f, -1.0f);
		D3DXVec3Normalize(&g_DirectLight_Direction, &g_DirectLight_Direction);

		g_DirectLight.Diffuse = COLORVALUE_RGBA(255, 255, 255, 255);
		g_DirectLight.Direction = g_DirectLight_Direction;

		Device->SetLight(0, &g_DirectLight);
		Device->LightEnable(0, TRUE);
		Device->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);	//�@���x�N�g����P�ʃx�N�g�����F�g��E�k���̕ω�
		Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

		//�A���r�G���g
		Device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_RGBA(84, 84, 84, 255));
		Device->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

		g_bMaterialEnable = true;

	}

	//���C�g���Z�b�g
	void Set_Light(BOOL bSet)
	{
		System_GetDevice()->SetRenderState(D3DRS_LIGHTING, bSet);	//���C�e�B���O��ON
	}

	//�}�e���A���̖���
	void Set_MaterialDisEnable()
	{
		if (g_bMaterialEnable)
		{
			System_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
			System_GetDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
			g_bMaterialEnable = false;
		}

		return;
	}

	//�}�e���A���̗L��
	void Set_MaterialEnable()
	{
		if (!g_bMaterialEnable)
		{
			System_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
			System_GetDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
			g_bMaterialEnable = true;
		}

		return;
	}
}

