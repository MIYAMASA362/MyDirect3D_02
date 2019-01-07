//
//	Transform.cpp
//		Author:HIROMASA IKEDA	DATA:2018/11/22
//===============================================
#include<d3dx9.h>
#include"CTransform.h"

//===============================================
//	�O���[�o���ϐ�
//===============================================

//=========================================================
//	CTransform
//=========================================================

//===============================================
//	Constructor/Destroctor
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
CTransform::CTransform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation)
{
	this->m_bEnable_Convert = true;
	this->m_bConverted = false;
	this->m_pParent = NULL;

	//���[���h�ʒu��ݒ�
	this->m_Position = Position;
	this->m_Rotation = Rotation;
	this->m_Scale = Scale;

	this->Get_MtxWorld();
}

//-------------------------------------
//	�f�X�g���N�^
//-------------------------------------
CTransform::~CTransform()
{
	this->m_pParent = NULL;

	//�q�������Ă���Ȃ�
	if (this->m_pChild.size() > 0)
	{
		for (int i = 0; i < this->m_pChild.size(); i++)
		{
			//�e�𖳂���
			this->m_pChild.at(i)->Release_Parent();
		}
	}
}

//===============================================
//	�s��ϊ�
//===============================================

//-------------------------------------
//	�s��ϊ� �J�n
//-------------------------------------

D3DXMATRIX CTransform::Convert()
{
	if (this->m_bConverted == true || this->m_bEnable_Convert == true) return this->m_MtxWorld;

	D3DXMatrixIdentity(&this->m_MtxWorld);
	D3DXMatrixTranslation(&this->m_MtxTransform, this->m_Position.x, this->m_Position.y, this->m_Position.z);
	D3DXMatrixScaling(&this->m_MtxScale, this->m_Scale.x, this->m_Scale.y, this->m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&this->m_MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	this->m_MtxWorld = this->m_MtxScale * this->m_MtxRotation * this->m_MtxTransform;

	if (this->Have_a_Parent())
	{
		this->m_MtxWorld *= this->m_pParent->Convert();
	}

	this->m_bConverted = true;

	return this->m_MtxWorld;
}

//-------------------------------------
//	���[���h���
//-------------------------------------

D3DXVECTOR3* CTransform::Position()
{
	this->Get_Position();
	return &this->m_Rotation;
}

D3DXVECTOR3* CTransform::Rotation()
{
	this->Get_Rotation();
	return &this->m_Rotation;
}

D3DXVECTOR3* CTransform::Scale()
{
	this->Get_Scale();
	return &this->m_Scale;
}

//�EGet Position	�ʒu���
D3DXVECTOR3 CTransform::Get_Position()
{
	if (this->Have_a_Parent())
	{
		D3DXVECTOR3 position;
		D3DXVec3TransformCoord(&position, &position, &this->Get_MtxWorld());
		return position;
	}

	return this->m_Position;
}

//�EGet Rotation	��]���
//	�e�̃��[���h��]�l�Ɏ��g�̉�]�l�����Z
//
D3DXVECTOR3 CTransform::Get_Rotation()
{
	if (this->Have_a_Parent())
	{
		this->m_Rotation += this->m_pParent->Get_Rotation();
	}

	return this->m_Rotation;
}

//�EGet Scale		�傫�����
//	�e�̃X�P�[���l�Ɏ��g�̃X�P�[���l����Z
//	
D3DXVECTOR3 CTransform::Get_Scale()
{
	D3DXVECTOR3 Scale = this->m_Scale;

	if (this->Have_a_Parent())
	{
		D3DXVECTOR3 ParentScale = this->m_pParent->Get_Scale();
		Scale.x *= ParentScale.x;
		Scale.y *= ParentScale.y;
		Scale.z *= ParentScale.z;
	}

	return Scale;
}

//Set Position
void CTransform::Set_Position(D3DXVECTOR3 Position)
{
	//�e�Ƃ̑��Έʒu���Z�o
	if (this->Have_a_Parent())
	{
		Position -= this->m_pParent->Get_Position();
	}

	this->m_Position = Position;

	return;
}

//Set Rotation
void CTransform::Set_Rotation(D3DXVECTOR3 Rotation)
{
	if (this->Have_a_Parent())
	{
		Rotation -= this->m_pParent->Get_Rotation();
	}

	this->m_Rotation = Rotation;

	return;
}

//Set Scale
void CTransform::Set_Scale(D3DXVECTOR3 Scale)
{
	if (this->Have_a_Parent())
	{
		D3DXVECTOR3 scale = this->m_pParent->Get_Scale();
		Scale.x /= scale.x;
		Scale.y /= scale.y;
		Scale.z /= scale.z;
	}

	this->m_Scale = Scale;
	return;
}

//-------------------------------------
//	�s��֌W
//-------------------------------------

D3DXMATRIX* CTransform::MtxTransform()
{
	this->Get_MtxTransform();
	return &this->m_MtxTransform;
}

D3DXMATRIX* CTransform::MtxScale()
{
	this->Get_MtxScale();
	return &this->m_MtxScale;
}

D3DXMATRIX* CTransform::MtxRotation()
{
	this->Get_MtxRotation();
	return &this->m_MtxRotation;
}

D3DXMATRIX* CTransform::MtxWorld()
{
	this->Get_MtxWorld();
	return &this->m_MtxWorld;
}

//	Get MtxTransform	�ʒu�s��
D3DXMATRIX CTransform::Get_MtxTransform()
{
	D3DXMatrixTranslation(&this->m_MtxTransform, this->m_Position.x, this->m_Position.y, this->m_Position.z);

	if (this->Have_a_Parent())
	{
		this->m_MtxTransform *= this->m_pParent->Get_MtxTransform();
	}

	return this->m_MtxTransform;
}

//	Get MtxRotation	��]�s��
D3DXMATRIX CTransform::Get_MtxRotation()
{
	D3DXMatrixRotationYawPitchRoll(&this->m_MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	if (this->Have_a_Parent())
	{
		this->m_MtxRotation *= this->m_pParent->Get_MtxRotation();
	}

	return this->m_MtxRotation;
}

//	Get MtxScale	�T�C�Y�s��
D3DXMATRIX CTransform::Get_MtxScale()
{
	D3DXMatrixScaling(&this->m_MtxScale, this->m_Scale.x, this->m_Scale.y, this->m_Scale.z);

	if (this->Have_a_Parent())
	{
		this->m_MtxScale *= this->m_pParent->Get_MtxScale();
	}

	return this->m_MtxScale;
}

//	Get MtxWorld ���[���h��ԍs��
D3DXMATRIX CTransform::Get_MtxWorld()
{
	D3DXMatrixTranslation(&this->m_MtxTransform, this->m_Position.x, this->m_Position.y, this->m_Position.z);
	D3DXMatrixRotationYawPitchRoll(&this->m_MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);
	D3DXMatrixScaling(&this->m_MtxScale, this->m_Scale.x, this->m_Scale.y, this->m_Scale.z);

	this->m_MtxWorld = this->m_MtxScale * this->m_MtxRotation * this->m_MtxTransform;

	if (this->Have_a_Parent())
	{
		this->m_MtxWorld *= this->m_pParent->Get_MtxWorld();
	}

	return this->m_MtxWorld;
}

//-------------------------------------
//	���΍s�� �擾
//-------------------------------------

D3DXMATRIX CTransform::Get_localMtxTransform()
{
	D3DXMatrixTranslation(&this->m_MtxTransform, this->m_Position.x, this->m_Position.y, this->m_Position.z);
	return this->m_MtxTransform;
}

D3DXMATRIX CTransform::Get_localMtxScale()
{
	D3DXMatrixScaling(&this->m_MtxScale, this->m_Scale.x, this->m_Scale.y, this->m_Scale.z);
	return this->m_MtxScale;
}

D3DXMATRIX CTransform::Get_localMtxRotation()
{
	D3DXMatrixRotationYawPitchRoll(&this->m_MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);
	return this->m_MtxRotation;
}

D3DXMATRIX CTransform::Get_localMtxWorld()
{
	this->m_MtxWorld = this->Get_MtxScale() * this->Get_MtxRotation() * this->Get_MtxTransform();
	return this->m_MtxWorld;
}

//-------------------------------------
//	�s��@�ݒ�
//-------------------------------------

void CTransform::Set_MtxTransform(D3DXMATRIX MtxTransform)
{
	this->m_MtxTransform = MtxTransform;
}

void CTransform::Set_MtxScale(D3DXMATRIX MtxScale)
{
	this->m_MtxScale = MtxScale;
}

void CTransform::Set_MtxRotation(D3DXMATRIX MtxRotation)
{
	this->m_MtxRotation = MtxRotation;
}

void CTransform::Set_MtxWorld(D3DXMATRIX MtxWorld)
{
	this->m_MtxWorld = MtxWorld;
}

//-------------------------------------
//	���Έʒu �擾
//-------------------------------------

D3DXVECTOR3 CTransform::Get_localPosition()
{
	return this->m_Position;
}

D3DXVECTOR3 CTransform::Get_localRotation()
{
	return this->m_Rotation;
}

D3DXVECTOR3 CTransform::Get_localScale()
{
	return this->m_Scale;
}

//-------------------------------------
//	���Έʒu �ݒ�
//-------------------------------------

void CTransform::Set_localPosition(D3DXVECTOR3 position)
{
	this->m_Position = position;
}

void CTransform::Set_localRotation(D3DXVECTOR3 rotation)
{
	this->m_Rotation = rotation;
}

void CTransform::Set_localScale(D3DXVECTOR3 scale)
{
	this->m_Scale = scale;
}

//-------------------------------------
//	�����֌W
//-------------------------------------

//Get ��
D3DXVECTOR3 CTransform::Get_Up()
{
	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	//up
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXVec3TransformNormal(&up, &up, &MtxRotation);
	D3DXVec3Normalize(&up, &up);

	return up;
}

//Get �E
D3DXVECTOR3 CTransform::Get_Right()
{
	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	//right
	D3DXVECTOR3 right(1.0f, 0.0f, 0.0f);
	D3DXVec3TransformNormal(&right, &right, &MtxRotation);
	D3DXVec3Normalize(&right, &right);

	return right;
}

//Get �O
D3DXVECTOR3 CTransform::Get_Forward()
{
	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	//right
	D3DXVECTOR3 forward(0.0f, 0.0f, 1.0f);
	D3DXVec3TransformNormal(&forward, &forward, &MtxRotation);
	D3DXVec3Normalize(&forward, &forward);

	return forward;
}

//===============================================
//	��]�֐�
//===============================================

//-------------------------------------
//	Rotation
//-------------------------------------
void CTransform::RotationVec3(const D3DXVECTOR3 value)
{
	this->m_Rotation += value;	//���Z

	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	return;
}

//-------------------------------------
//	RotationAxis
//-------------------------------------
void CTransform::RotationAxis(const D3DXVECTOR3 Axis, const float Value)
{
	D3DXMATRIX MtxAxis;
	D3DXMatrixRotationAxis(&MtxAxis, &Axis, Value);

	D3DXVECTOR3 VecAxis;
	D3DXVec3TransformNormal(&VecAxis, &VecAxis, &MtxAxis);	//�ω��l�𓾂�

	this->m_Rotation += VecAxis;	//���Z

	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	return;
}

//===============================================
//	�e�q�֌W
//===============================================

//-------------------------------------
//	�e��ݒ�
//-------------------------------------
void CTransform::Set_Parent(CTransform* pParent)
{
	this->m_pParent = pParent;
	pParent->m_pChild.push_back(this);
}

//-------------------------------------
//	�擾
//-------------------------------------
CTransform* CTransform::Get_Parent()
{
	return this->m_pParent;
}

//-------------------------------------
//	�e�Ɨ����
//-------------------------------------
void CTransform::Release_Parent()
{
	this->m_pParent = NULL;
}

void CTransform::ConvertEnable(bool enable)
{
	this->m_bEnable_Convert = enable;
}

bool CTransform::Have_a_Parent()
{
	if (this->m_pParent != NULL)
	{
		return true;
	}

	return false;
};

/*
//===============================================
//	Transform
//===============================================

//-------------------------------------
//	�ĕϊ����\
//-------------------------------------
void Transform::ConvertReset()
{
	for(int i = 0; i < pIndex.size();i++)
	{
		pIndex.at(i)->bConverted = false;	//Window�ŃG���[���N���錴�����ۂ�
	}
}

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
Transform::Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation)
{
	this->bConverted = false;
	this->pParent = NULL;

	//���[���h���
	this->Position = Position;
	this->Scale = Scale;
	this->Rotation = Rotation;

	//���[�J�����
	this->position = Position;
	this->scale = Scale;
	this->rotation = Rotation;

	this->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXVec3Normalize(&this->forward, &this->forward);
	D3DXVec3Cross(&this->right, &this->forward, &this->up);
	D3DXVec3Normalize(&this->right, &this->right);

	pIndex.push_back(this);
}

//-------------------------------------
//	�f�X�g���N�^
//-------------------------------------
Transform::~Transform()
{
	this->pParent = NULL;

	//�q�������Ă���Ȃ�
	if (this->pChild.size() > 0)
	{
		for (int i = 0; i < this->pChild.size(); i--)
		{
			//�q�ɐe�̎��S��`����
			this->pChild.at(i)->Release_Parent();
		}
	}

	this->pChild.clear();
}

//-------------------------------------
//	�e��ݒ�
//-------------------------------------
void Transform::Set_Parent(Transform* pParent)
{
	this->pParent = pParent;
	pParent->pChild.push_back(this);	//�e�Ɏq���o��������

	this->Position = pParent->Position + this->position;
	this->Scale = pParent->Scale + this->scale;
	this->Rotation = pParent->Rotation + this->rotation;

}

//-------------------------------------
//	�����X�V
//-------------------------------------
Transform* Transform::Set_UpdateTransform()
{
	if (this->pParent != NULL)
	{
		this->Position = pParent->Position + this->position;
		this->Scale = pParent->Scale + this->scale;
		this->Rotation = pParent->Rotation + this->rotation;
	}
	else
	{
		this->Position = this->position;
		this->Rotation = this->rotation;
		this->Scale = this->scale;
	}

	return this;
}

//-------------------------------------
//	�e���擾
//-------------------------------------	
Transform* Transform::Get_Parent()
{
	return this->pParent;
}

//-------------------------------------
//	�s��ϊ�
//-------------------------------------
D3DXMATRIX Transform::Convert()
{
	this->bConverted = false;
	this->Set_UpdateTransform();
	if (this->bConverted) return this->MtxWorld;	//��x�ϊ�����Ă���

	//�e�s��
	D3DXMATRIX MtxTransform;	//�ʒu
	D3DXMATRIX MtxScale;		//�傫��
	D3DXMATRIX MtxRotation;		//��]

	//�s��ϊ�
	D3DXMatrixTranslation(&MtxTransform, this->position.x, this->position.y, this->position.z);
	D3DXMatrixScaling(&MtxScale, this->scale.x, this->scale.y, this->scale.z);
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->rotation.y, this->rotation.x, this->rotation.z);

	//����
	this->up = D3DXVECTOR3(0.0f,1.0f,0.0f);
	D3DXVec3TransformNormal(&this->up,&this->up,&MtxRotation);
	D3DXVec3Normalize(&this->up, &this->up);

	//�O���
	this->forward = D3DXVECTOR3(0.0f,0.0f,1.0f);
	D3DXVec3TransformNormal(&this->forward,&this->forward,&MtxRotation);
	D3DXVec3Normalize(&this->forward, &this->forward);

	//�E���
	D3DXVec3Cross(&this->right, &this->up, &this->forward);

	//���[���h�s��̍쐬
	D3DXMatrixIdentity(&this->MtxWorld);
	this->MtxWorld = MtxScale * MtxRotation * MtxTransform;

	//�e������
	if (this->pParent != NULL)
	{
		//�e�̍s�񌩂Ă���
		this->MtxWorld *= this->pParent->Convert();
	}

	//�ϊ��I��	
	this->bConverted = true;

	return this->MtxWorld;
}

//-------------------------------------
//	�e�����
//-------------------------------------
void Transform::Release_Parent()
{
	this->pParent = NULL;
}
*/

//===============================================
//	Transform2
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
Transform2::Transform2()
{
	Position = { 0.0f,0.0f };
	Scale = { 1.0f,1.0f };
	Rotation = 0;
	Color = Color;
}

Transform2::Transform2(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, float Rotation)
{
	this->Position = Position;
	this->Scale = Scale;
	this->Rotation = Rotation;
	Color = D3DCOLOR_RGBA(255, 255, 255, 255);
}

Transform2::Transform2(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, float Rotation, D3DCOLOR Color)
{
	this->Position = Position;
	this->Scale = Scale;
	this->Rotation = Rotation;
	this->Color = Color;
}
