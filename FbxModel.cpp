//
//	FbxModel.cpp
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"

#include"FbxModel.h"

//===============================================
//	�}�N����`		define
//===============================================


//===============================================
//	�O���[�o���ϐ�	global
//===============================================
namespace fbx
{
	//------------------------------------
	//	�O���[�o���ϐ�
	//------------------------------------
	FbxManager* g_lpManager = NULL;	//�}�l�[�W���[

	//------------------------------------
	//	����������
	//------------------------------------
	int Initialize()
	{
		//Fbx�}�l�[�W���̏�����
		g_lpManager = FbxManager::Create();

		//���������s
		if (g_lpManager == NULL) return 1;

		FbxScene* Scene = LoadScene(g_lpManager,"", "Fight Idle.fbx");

		LoadModel(Scene);

		return 0;
	}

	//------------------------------------
	//	�I������
	//------------------------------------
	int Finalize()
	{
		if (g_lpManager != NULL)
		{
			g_lpManager->Destroy();
			g_lpManager = NULL;
		}

		return 0;
	}

	//���[�h
	FbxScene* LoadScene(FbxManager* Manager, const char* Name, const char* FilePath)
	{
		//���o�͐ݒ���쐬
		FbxIOSettings* lpIos = FbxIOSettings::Create(Manager, IOSROOT);

		//���o�͐ݒ��K��
		Manager->SetIOSettings(lpIos);

		//FBX�C���|�[�^�̏�����
		FbxImporter* lpImporter = FbxImporter::Create(Manager, "");

		//FBX�ǂݍ���
		if (!lpImporter->Initialize(FilePath, -1, Manager->GetIOSettings()))
		{
			Manager->Destroy();

			return NULL;
		}

		//�V�[���̏�����
		FbxScene* Scene = FbxScene::Create(Manager, Name);

		//�V�[���̃C���|�[�g
		if (!lpImporter->Import(Scene)) return NULL;

		//�C���|�[�^�̍폜
		lpImporter->Destroy();

		//�O�p�|���S���ϊ�
		FbxGeometryConverter geometryConberter(Manager);
		geometryConberter.Triangulate(Scene, true);

		return Scene;
	}

	//------------------------------------
	//	�m�[�h�擾
	//------------------------------------
	FbxNode* GetNode(const FbxScene* Scene)
	{
		FbxNode* rootNode = Scene->GetRootNode();

		if (rootNode != NULL) return NULL;

		return rootNode;
	}

	int MeshNum(const FbxScene* Scene)
	{
		return Scene->GetSrcObjectCount<FbxMesh>();
	}

	//------------------------------------
	//	���f�����
	//------------------------------------
	void LoadModel(FbxScene* Scene)
	{
		FbxNode* node = FbxNode::Create(Scene,"");		//�m�[�h
		FbxMesh* mesh = FbxMesh::Create(Scene,"");
		//FbxMesh* mesh = Scene->GetRootNode()->GetMesh();	//���b�V��

		int PolygonNum = mesh->GetPolygonCount();			//�|���S����
		int VertexNum = mesh->GetControlPointsCount();		//���_��
		int IndexNum = mesh->GetPolygonVertexCount();		//�C���f�b�N�X��
		FbxVector4* vertex = mesh->GetControlPoints();		//���_���W

		D3DXVECTOR4* Position = new D3DXVECTOR4[VertexNum];	//���_

		//�e���_�ݒ�
		for(int i = 0; i < VertexNum; i++)
		{
			Position[i].x = vertex[i][0];
			Position[i].y = vertex[i][1];
			Position[i].z = vertex[i][2];
			Position[i].w = vertex[i][3];
		}

		//���_�C���f�b�N�X
		int* index = mesh->GetPolygonVertices();	
		int* indexBuffer = new int[IndexNum];
		for(int i = 0; i < IndexNum; i++)
		{
			indexBuffer[i] = index[i];
		}

		D3DXVECTOR3* Normal;		//�@��
		int NormalLayerNum = mesh->GetElementNormalCount();	//�@���Z�b�g��
		for(int i = 0; i < NormalLayerNum; i++)
		{
			FbxGeometryElementNormal* NormalSet = mesh->GetElementNormal(i);		//�@���Z�b�g
			FbxGeometryElement::EMappingMode Mapping = NormalSet->GetMappingMode();//�}�b�s���O���[�h
			FbxGeometryElement::EReferenceMode Refarence = NormalSet->GetReferenceMode();	//���t�@�����X���[�h

			if(Mapping ==  FbxGeometryElement::eByControlPoint)
			{
				if(Refarence == FbxGeometryElement::eDirect)
				{
					int NormalCount = NormalSet->GetDirectArray().GetCount();
					Normal = new D3DXVECTOR3[NormalCount];

					FbxVector4* At = &NormalSet->GetDirectArray().GetAt(i);
					for(int i = 0; i < NormalCount; i++)
					{
						
						Normal[i].x = At[i][0];
						Normal[i].y = At[i][1];
						Normal[i].z = At[i][2];
					}
				}
			}
		}
	}
}
