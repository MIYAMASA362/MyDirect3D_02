//
//	Cube.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/21
//===============================================
#include<d3dx9.h>	
#include"System.h"
#include"Cube.h"
#include"CGameObject.h"
#include"input.h"
#include"Lighting.h"

#define CUBE_VERTEX_NUM (24)

//===============================================
//	�O���[�o��
//===============================================
static D3DCOLOR g_CubeColor = D3DCOLOR_RGBA(255, 255, 255, 255);

static CubeVertex3D Cube[] =
{
	//����
	{ { -0.5f,	 0.5f,	-0.5f },{ 0.0f,0.0f,-1.0f }, { 0,	0 } },
	{ { 0.5f,	 0.5f,	-0.5f },{ 0.0f,0.0f,-1.0f }, { 0.25, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f },{ 0.0f,0.0f,-1.0f }, { 0,	 0.25 } },

	{ { 0.5f,	 0.5f,	-0.5f },{ 0.0f,0.0f,-1.0f }, { 0.25, 0 } },
	{ { 0.5f,	-0.5f,	-0.5f },{ 0.0f,0.0f,-1.0f }, { 0.25, 0.25 } },
	{ { -0.5f,	-0.5f,	-0.5f },{ 0.0f,0.0f,-1.0f }, { 0,	0.25 } },

	//���
	{ { -0.5f,	 0.5f,	 0.5f },{ 0.0f,1.0f,0.0f }, { 0.25, 0 } },
	{ { 0.5f,	 0.5f,	 0.5f },{ 0.0f,1.0f,0.0f }, { 0.5, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f },{ 0.0f,1.0f,0.0f }, { 0.25, 0.25 } },

	{ { 0.5f,	 0.5f,	 0.5f },{ 0.0f,1.0f,0.0f }, { 0.5, 0 } },
	{ { 0.5f,	 0.5f,	-0.5f },{ 0.0f,1.0f,0.0f }, { 0.5, 0.25 } },
	{ { -0.5f,	 0.5f,	-0.5f },{ 0.0f,1.0f,0.0f }, { 0.25, 0.25 } },

	//�E��
	{ { 0.5f,	 0.5f,	-0.5f },{ 1.0f,0.0f,0.0f }, { 0.5, 0 } },
	{ { 0.5f,	 0.5f,	 0.5f },{ 1.0f,0.0f,0.0f }, { 0.75, 0 } },
	{ { 0.5f,	-0.5f,  -0.5f },{ 1.0f,0.0f,0.0f }, { 0.5, 0.25 } },

	{ { 0.5f,	 0.5f,	0.5f },{ 1.0f,0.0f,0.0f }, { 0.75, 0 } },
	{ { 0.5f,	-0.5f,	0.5f },{ 1.0f,0.0f,0.0f }, { 0.75,0.25 } },
	{ { 0.5f,	-0.5f, -0.5f },{ 1.0f,0.0f,0.0f }, { 0.5,0.25 } },

	//����
	{ { -0.5f,	 0.5f,	 0.5f },{ -1.0f,0.0f,0.0f }, { 0.75, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f },{ -1.0f,0.0f,0.0f }, { 1, 0 } },
	{ { -0.5f,	-0.5f,   0.5f },{ -1.0f,0.0f,0.0f }, { 0.75, 0.25 } },

	{ { -0.5f,	 0.5f, -0.5f },{ -1.0f,0.0f,0.0f }, { 1, 0 } },
	{ { -0.5f,	-0.5f, -0.5f },{ -1.0f,0.0f,0.0f }, { 1, 0.25 } },
	{ { -0.5f,	-0.5f,  0.5f },{ -1.0f,0.0f,0.0f }, { 0.75,0.25 } },

	//����
	{ { 0.5f,	 0.5f, 0.5f },{ 0.0f,0.0f,1.0f }, { 0,0 } },
	{ { -0.5f,	 0.5f, 0.5f },{ 0.0f,0.0f,1.0f }, { 1,0 } },
	{ { 0.5f,	-0.5f, 0.5f },{ 0.0f,0.0f,1.0f }, { 0,1 } },

	{ { -0.5f,	 0.5f, 0.5f },{ 0.0f,0.0f,1.0f }, { 1,0 } },
	{ { -0.5f,	-0.5f, 0.5f },{ 0.0f,0.0f,1.0f }, { 1,1 } },
	{ { 0.5f,	-0.5f, 0.5f },{ 0.0f,0.0f,1.0f }, { 0,1 } },

	//����
	{ { -0.5f,	 -0.5f,	-0.5f },{ 0.0f,-1.0f,0.0f }, { 0.25,0.25 } },
	{ { 0.5f,	 -0.5f,	-0.5f },{ 0.0f,-1.0f,0.0f }, { 0.5,0.25 } },
	{ { -0.5f,	 -0.5f,	 0.5f },{ 0.0f,-1.0f,0.0f }, { 0.25,0.5 } },

	{ { 0.5f,	 -0.5f,	-0.5f },{ 0.0f,-1.0f,0.0f }, { 0.5,0.25 } },
	{ { 0.5f,	 -0.5f,	 0.5f },{ 0.0f,-1.0f,0.0f }, { 0.5,0.5 } },
	{ { -0.5f,	 -0.5f,	 0.5f },{ 0.0f,-1.0f,0.0f }, { 0.25,0.5 } },
};

static CubeVertex3D CubeVertexData[CUBE_VERTEX_NUM] =
{
	//����
	{ { -0.5f,	 0.5f,	-0.5f },{ 0.0f,0.0f,-1.0f },{ 0,	0 } },
	{ { 0.5f,	 0.5f,	-0.5f },{ 0.0f,0.0f,-1.0f },{ 0.25, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f },{ 0.0f,0.0f,-1.0f },{ 0, 0.25 } },
	{ { 0.5f,	-0.5f,	-0.5f },{ 0.0f,0.0f,-1.0f },{ 0.25, 0.25 } },

	//���
	{ { -0.5f,	 0.5f,	 0.5f },{ 0.0f,1.0f,0.0f }, { 0.25, 0 } },
	{ { 0.5f,	 0.5f,	 0.5f },{ 0.0f,1.0f,0.0f }, { 0.5, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f },{ 0.0f,1.0f,0.0f }, { 0.25, 0.25 } },
	{ { 0.5f,	 0.5f,	-0.5f },{ 0.0f,1.0f,0.0f }, { 0.5, 0.25 } },

	//�E��
	{ { 0.5f,	 0.5f,	-0.5f },{ 1.0f,0.0f,0.0f }, { 0.5, 0 } },
	{ { 0.5f,	 0.5f,	 0.5f },{ 1.0f,0.0f,0.0f }, { 0.75, 0 } },
	{ { 0.5f,	-0.5f,  -0.5f },{ 1.0f,0.0f,0.0f }, { 0.5, 0.25 } },
	{ { 0.5f,	-0.5f,	0.5f },{ 1.0f,0.0f,0.0f }, { 0.75,0.25 } },

	//����
	{ { -0.5f,	 0.5f,	 0.5f },{ -1.0f,0.0f,0.0f }, { 0.75, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f },{ -1.0f,0.0f,0.0f }, { 1, 0 } },
	{ { -0.5f,	-0.5f,   0.5f },{ -1.0f,0.0f,0.0f }, { 0.75, 0.25 } },
	{ { -0.5f,	-0.5f,  -0.5f },{ -1.0f,0.0f,0.0f }, { 1, 0.25 } },

	//����
	{ { 0.5f,	 0.5f, 0.5f },{ 0.0f,0.0f,1.0f }, { 0,0.25 } },
	{ { -0.5f,	 0.5f, 0.5f },{ 0.0f,0.0f,1.0f }, { 0.25,0.25 } },
	{ { 0.5f,	-0.5f, 0.5f },{ 0.0f,0.0f,1.0f }, { 0,0.5 } },
	{ { -0.5f,	-0.5f, 0.5f },{ 0.0f,0.0f,1.0f }, { 0.25,0.5 } },

	//����
	{ { -0.5f,	 -0.5f,	-0.5f },{ 0.0f,-1.0f,0.0f }, { 0.25,0.25 } },
	{ { 0.5f,	 -0.5f,	-0.5f },{ 0.0f,-1.0f,0.0f }, { 0.5,0.25 } },
	{ { -0.5f,	 -0.5f,	 0.5f },{ 0.0f,-1.0f,0.0f }, { 0.25,0.5 } },
	{ { 0.5f,	 -0.5f,	 0.5f },{ 0.0f,-1.0f,0.0f }, { 0.5,0.5 } },
};


//===============================================
//	�֐�			function
//===============================================

//-------------------------------------
//	���f���擾
//-------------------------------------
void* GetModel_Cube()
{
	return &Cube[0];
}

//===============================================
//	�o�b�t�@��
//===============================================
static LPDIRECT3DVERTEXBUFFER9	g_pCubeVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9	g_pCubeIndexBuffer = NULL;

static CubeVertex3D* g_pCubeVertex = NULL;
static WORD* g_pCubeVertexIndex = NULL;
static D3DMATERIAL9 g_CubeMatrerial = {};

//-------------------------------------
//	������
//-------------------------------------
void Cube_Initialize()
{
	g_CubeMatrerial.Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	System_GetDevice()->CreateVertexBuffer(
		sizeof(CubeVertex3D) * CUBE_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_CUBE_VERTEX3D,
		D3DPOOL_MANAGED,
		&g_pCubeVertexBuffer,
		NULL
	);

	System_GetDevice()->CreateIndexBuffer(
		sizeof(WORD) * 3 * CUBE_PRIMITIVE_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pCubeIndexBuffer,
		NULL
	);

	g_pCubeVertexBuffer->Lock(0,0,(void**)&g_pCubeVertex,0);
	
	memcpy(&g_pCubeVertex[0],&CubeVertexData[0],sizeof(CubeVertexData[0]) * CUBE_VERTEX_NUM);

	g_pCubeVertexBuffer->Unlock();


	g_pCubeIndexBuffer->Lock(0, 0, (void**)&g_pCubeVertexIndex, 0);

	for(int i = 0; i < CUBE_PRIMITIVE_NUM*0.5f; i++)
	{
		int j = i * 6;		//�C���f�b�N�X��
		int n = i * 4;		//���_��

		g_pCubeVertexIndex[j]	  = n;
		g_pCubeVertexIndex[j + 1] = n + 1;
		g_pCubeVertexIndex[j + 2] = n + 2;

		g_pCubeVertexIndex[j + 3] = n + 1;
		g_pCubeVertexIndex[j + 4] = n + 3;
		g_pCubeVertexIndex[j + 5] = n + 2;
	}

	g_pCubeIndexBuffer->Unlock();
	
}

//-------------------------------------
//	�`��
//-------------------------------------
void Cube_Render()
{
	LPDIRECT3DDEVICE9 Device = System_GetDevice();
	Device->SetMaterial(&g_CubeMatrerial);

	Device->SetStreamSource(0,g_pCubeVertexBuffer,0, sizeof(CubeVertex3D));
	Device->SetIndices(g_pCubeIndexBuffer);
	Device->SetFVF(FVF_CUBE_VERTEX3D);
	Device->DrawIndexedPrimitive(CUBE_PRIMITIVE_TYPE,0,0,3 * CUBE_PRIMITIVE_NUM,0,CUBE_PRIMITIVE_NUM);
}

//-------------------------------------
//	�I������
//-------------------------------------
void Cube_Finalize()
{
	if(g_pCubeIndexBuffer)
	{
		g_pCubeIndexBuffer->Release();
		g_pCubeIndexBuffer = NULL;
	}

	if(g_pCubeVertexBuffer)
	{
		g_pCubeVertexBuffer->Release();
		g_pCubeVertexBuffer = NULL;
	}
}

