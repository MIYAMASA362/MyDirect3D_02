//
//	CGameObject.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/29
//===============================================
#include<d3dx9.h>
#include<vector>

#include"Cube.h"
#include"CGameObject.h"

/*
//===============================================
//	�O���[�o���ϐ�
//===============================================
std::vector<GameObject*> GameObject::pIndex;

//===============================================
//	GameObject �N���X
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
GameObject::GameObject(Transform* pTransform)
{
	this->transform		= *pTransform;
	this->pIndex.push_back(this);
}

//-------------------------------------
//	�f�X�g���N�^
//-------------------------------------
GameObject::~GameObject()
{

}

//-------------------------------------
//	�e��ݒ�
//-------------------------------------
void GameObject::Set_Parent(GameObject* pParent)
{
	this->transform.Set_Parent(&pParent->transform);
}

//------------------------------------
//	�X�V����
//------------------------------------
void GameObject::Update()
{

}

//------------------------------------
//	�`�揈��
//------------------------------------
void GameObject::Render()
{
	render.Begin(&this->transform);
}

//===============================================
//	�O���[�o��
//===============================================

//-----------------------------------
//	�S�̍X�V
//-----------------------------------
void GameObject::g_Update()
{
	for(int i = 0; i < pIndex.size(); i++)
	{
		pIndex.at(i)->Update();
	}
}

//----------------------------------
//	�S�̕`��
//----------------------------------
void GameObject::g_Render()
{
	for(int i = 0; i< pIndex.size(); i++)
	{
		pIndex.at(i)->Render();
	}
}
*/
