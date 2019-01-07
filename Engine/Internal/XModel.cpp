//
//	XModel.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/19
//===============================================
//	�ύX�� Changed By 
//		Name:Minoda Takamasa DATE:2018/10/23
//		Name:HIROMASA IKEDA	 DATE:2018/11/15
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#define _CRT_SECURE_NO_WARNINGS
#include<d3dx9.h>
#include<string.h>

#include"XModel.h"
#include"System.h"

//Class


//===============================================
//	�}�N����`		define
//===============================================
#define MODELS_FILE ("Models/")
#define MODELS_FILE_NUM (60)
#define MODELS_NAME_NUM (30)

//�A�N�Z�X
struct Path
{
 	NXModel::Name name;
	const char FileName[MODELS_FILE_NUM];		//���f���̓����Ă���t�@�C��(�e�N�X�`�����Q�Ƃ����)
	const char ModelName[MODELS_NAME_NUM];	//x���f��
};

//===============================================
//	XModel ���O���
//===============================================
namespace NXModel
{
	//==============================================
	//	�e���f���f�[�^
	//==============================================

	//�e���f����Path��ݒ�
	static Path path[] =
	{
		{ AIRPLANE_BODY,"Airplane_Body","Airplane_Body.x" },
		{ AIRPLANE_PROPELLER,"Airplane_Propeller","Airplane_Propeller.x" },
		{ AIRPLANE_WingBD,"Airplane_WingBD","Airplane_WingBD.x" },
		{ AIRPLANE_WingBU,"Airplane_WingBU","Airplane_WingBU.x" },
		{ AIRPLANE_WingLD,"Airplane_WingLD","Airplane_WingLD.x" },
		{ AIRPLANE_WingLU,"Airplane_WingLU","Airplane_WingLU.x" },
		{ AIRPLANE_WingRD,"Airplane_WingRD","Airplane_WingRD.x" },
		{ AIRPLANE_WingRU,"Airplane_WingRU","Airplane_WingRU.x" },
		{ AIRPLANE_MODEL,"Airplane","Airplane.x" },
		{ TREE,"Tree","Tree.x" }
	};

	//�f�[�^�ۑ�
	static Data Index[NAME_END];

	//==============================================
	//	�֐�
	//==============================================

	void Load_XModelMesh(CXModelMesh* LoadMesh,char* ModelFile,char* path)
	{

		HRESULT hr;
		char FilePath[MODELS_FILE_NUM + MODELS_NAME_NUM + 10] = { "\0" };

		//���f���ւ̃A�N�Z�X
		strcat(FilePath, MODELS_FILE);
		strcat(FilePath, path);
		strcat(FilePath, "/");
		strcat(FilePath, ModelFile);

		LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

		hr = D3DXLoadMeshFromX(
			FilePath,
			D3DXMESH_SYSTEMMEM,
			System_GetDevice(),
			NULL,
			&pD3DXMtrlBuffer,
			NULL,
			&LoadMesh->dwNumMaterials,
			&LoadMesh->pMesh
		);

		if (FAILED(hr))
		{
			char ErrorText[100] = { "\0" };
			strcat(ErrorText, FilePath);
			strcat(ErrorText, "\n���f���f�[�^���ǂݍ��߂܂���ł����B");

			MessageBox(*System_GethWnd(), ErrorText, "�G���[", MB_OK);
			DestroyWindow(*System_GethWnd());
			return;
		}

		//���f���̃e�N�X�`���ւ̃A�N�Z�X
		strcpy(FilePath, "\0");	//������
		strcat(FilePath, MODELS_FILE);
		strcat(FilePath, path);
		strcat(FilePath, "/");

		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
		LoadMesh->pMeshMaterials = new D3DMATERIAL9[LoadMesh->dwNumMaterials];
		LoadMesh->pMeshTextures = new LPDIRECT3DTEXTURE9[LoadMesh->dwNumMaterials];

		D3DXMATERIAL* pD3DXMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

		for (DWORD i = 0; i < LoadMesh->dwNumMaterials; i++)
		{
			LoadMesh->pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
			LoadMesh->pMeshMaterials[i].Ambient = LoadMesh->pMeshMaterials[i].Diffuse;
			LoadMesh->pMeshTextures[i] = NULL;

			if (d3dxMaterials[i].pTextureFilename != NULL &&
				lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
			{
				//�e�N�X�`���̃p�X
				char TexturePath[200] = { "\0" };
				strcat(TexturePath, FilePath);
				strcat(TexturePath, d3dxMaterials[i].pTextureFilename);

				hr = D3DXCreateTextureFromFile(
					System_GetDevice(),
					TexturePath,
					&LoadMesh->pMeshTextures[i]
				);

				if (FAILED(hr))
				{
					char ErrorText[200] = { "\0" };
					strcat(ErrorText, TexturePath);
					strcat(ErrorText, "\n�e�N�X�`���ǂݍ��݂Ɏ��s���܂����B");

					MessageBox(NULL, ErrorText, "�G���[", MB_OK);
				}
			}
		}

		pD3DXMtrlBuffer->Release();
	}

	//---------------------------------
	//	���f���ǂݍ���
	//---------------------------------
	void Load(const int index)
	{
		HRESULT hr;
		char FilePath[MODELS_FILE_NUM + MODELS_NAME_NUM + 10] = {"\0"};

		//���f���ւ̃A�N�Z�X
		strcat(FilePath,MODELS_FILE);
		strcat(FilePath,path[index].FileName);
		strcat(FilePath,"/");
		strcat(FilePath,path[index].ModelName);

		LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

		hr = D3DXLoadMeshFromX(
			FilePath,
			D3DXMESH_SYSTEMMEM,
			System_GetDevice(),
			NULL,
			&pD3DXMtrlBuffer,
			NULL,
			&Index[index].dwNumMaterials,
			&Index[index].pMesh
		);

		if (FAILED(hr))
		{
			char ErrorText[100] = { "\0" };
			strcat(ErrorText, FilePath);
			strcat(ErrorText, "\n���f���f�[�^���ǂݍ��߂܂���ł����B");

			MessageBox(*System_GethWnd(), ErrorText, "�G���[", MB_OK);
			DestroyWindow(*System_GethWnd());
			return;
		}

		//���f���̃e�N�X�`���ւ̃A�N�Z�X
		strcpy(FilePath, "\0");	//������
		strcat(FilePath, MODELS_FILE);
		strcat(FilePath, path[index].FileName);
		strcat(FilePath, "/");
		
		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
		Index[index].pMaterials = new D3DMATERIAL9[Index[index].dwNumMaterials];
		Index[index].pTextures = new LPDIRECT3DTEXTURE9[Index[index].dwNumMaterials];

		D3DXMATERIAL* pD3DXMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

		for (DWORD i = 0; i < Index[index].dwNumMaterials; i++)
		{
			Index[index].pMaterials[i] = d3dxMaterials[i].MatD3D;
			Index[index].pMaterials[i].Ambient = Index[index].pMaterials[i].Diffuse;
			Index[index].pTextures[i] = NULL;

			if (d3dxMaterials[i].pTextureFilename != NULL &&
				lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
			{
				//�e�N�X�`���̃p�X
				char TexturePath[200] = { "\0" };
				strcat(TexturePath, FilePath);
				strcat(TexturePath, d3dxMaterials[i].pTextureFilename);

				hr = D3DXCreateTextureFromFile(
					System_GetDevice(),
					TexturePath,
					&Index[index].pTextures[i]
				);

				if (FAILED(hr))
				{
					char ErrorText[200] = { "\0" };
					strcat(ErrorText, TexturePath);
					strcat(ErrorText, "\n�e�N�X�`���ǂݍ��݂Ɏ��s���܂����B");

					MessageBox(NULL, ErrorText, "�G���[", MB_OK);
				}
			}
		}
		pD3DXMtrlBuffer->Release();
	}

	//---------------------------------
	//	����������
	//---------------------------------
	void Initialize()
	{
		for(int index = 0; index<NAME_END; index++)
		{
			Load(index);
		}
	}

	//---------------------------------
	//	�`��
	//---------------------------------
	void Render(const int index)
	{
		//�}�e���A���̐��������[�v������
		for (DWORD i = 0; i < Index[index].dwNumMaterials; i++)
		{
			//�}�e���A���ݒ�
			System_GetDevice()->SetMaterial(&Index[index].pMaterials[i]);
			//�e�N�X�`���ݒ�
			System_GetDevice()->SetTexture(0, Index[index].pTextures[i]);
			//�����_�����O
			Index[index].pMesh->DrawSubset(i);
		}
	}

	//---------------------------------
	//	�I������
	//---------------------------------
	void Finalize()
	{
		for (DWORD i = 0; i < NAME_END; i++)
		{
			delete Index[i].pTextures;
			delete Index[i].pMaterials;
			Index[i].pMesh->Release();
		}
	}

	//---------------------------------
	//	���f�� �f�[�^�擾
	//---------------------------------
	Data* Get(const Name name)
	{
		return &Index[name];
	}
}