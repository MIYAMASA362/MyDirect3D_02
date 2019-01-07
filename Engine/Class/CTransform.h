//
//	Transform.h
//		Author:HIROMASA IKEDA	DATE:2018/11/22
//===============================================
#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<d3dx9.h>
#include<vector>

class CTransform
{
private:
	bool m_bEnable_Convert;			//�ϊ����L��
	bool m_bConverted;				//�ϊ�������

private:
	CTransform* m_pParent;				//�e
	std::vector<CTransform*> m_pChild;	//�q

	//�s��
	D3DXMATRIX m_MtxTransform;
	D3DXMATRIX m_MtxScale;
	D3DXMATRIX m_MtxRotation;
	D3DXMATRIX m_MtxWorld;

	//���[�J�����
	D3DXVECTOR3 m_Position;			//�ʒu
	D3DXVECTOR3 m_Rotation;			//��]�@Radian
	D3DXVECTOR3 m_Scale;			//�傫��

public:
	//�R���X�g���N�^
	CTransform() :CTransform({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }) {};
	CTransform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation);

	//�f�X�g���N�^
	~CTransform();

private:
	D3DXMATRIX Convert();					//�s��ϊ��J�n

public: //����

	D3DXVECTOR3 Get_Up();				//�����
	D3DXVECTOR3 Get_Forward();			//�O����
	D3DXVECTOR3 Get_Right();			//�E����

public:	//�s��

		//�|�C���^�[�^
	D3DXMATRIX* MtxTransform();
	D3DXMATRIX* MtxScale();
	D3DXMATRIX* MtxRotation();
	D3DXMATRIX* MtxWorld();

	D3DXMATRIX Get_MtxTransform();		//�ʒu�s��
	D3DXMATRIX Get_MtxScale();			//��]�s��
	D3DXMATRIX Get_MtxRotation();		//�傫���s��
	D3DXMATRIX Get_MtxWorld();			//��ԍs��

	void Set_MtxTransform(D3DXMATRIX MtxTransform);
	void Set_MtxScale(D3DXMATRIX MtxScale);
	void Set_MtxRotation(D3DXMATRIX MtxRotation);
	void Set_MtxWorld(D3DXMATRIX MtxWorld);

	D3DXMATRIX Get_localMtxTransform();	//�ʒu�s��
	D3DXMATRIX Get_localMtxScale();		//��]�s��
	D3DXMATRIX Get_localMtxRotation();	//�傫���s��
	D3DXMATRIX Get_localMtxWorld();		//��ԍs��

public:	//���[���h���

		//�|�C���^�[�^
	D3DXVECTOR3* Position();
	D3DXVECTOR3* Rotation();
	D3DXVECTOR3* Scale();

	D3DXVECTOR3 Get_Position();		//�ʒu���
	D3DXVECTOR3 Get_Rotation();		//��]���
	D3DXVECTOR3 Get_Scale();		//�傫�����

	void Set_Position(D3DXVECTOR3 Position);
	void Set_Rotation(D3DXVECTOR3 Rotation);
	void Set_Scale(D3DXVECTOR3 Scale);

public:	//���Ώ��

	D3DXVECTOR3 Get_localPosition();
	D3DXVECTOR3 Get_localRotation();
	D3DXVECTOR3 Get_localScale();

	void Set_localPosition(D3DXVECTOR3 position);
	void Set_localRotation(D3DXVECTOR3 rotation);
	void Set_localScale(D3DXVECTOR3 scale);

public:	//�e�q�֌W
	void Set_Parent(CTransform* pParent);	//�e��ݒ�
	CTransform* Get_Parent();
	void Release_Parent();					//�e�Ɨ����

public://	��]�֐�
	void RotationVec3(const D3DXVECTOR3 value);
	void RotationAxis(const D3DXVECTOR3 Axis, const float value);

public:
	//�ϊ��̗L���E����
	void ConvertEnable(bool enable);

	//�e������
	bool Have_a_Parent();

};


//===============================================
//	Transform2 : 2D��p�@�N���X
//===============================================
class Transform2
{
private:

public:
	D3DXVECTOR2 Position;	//�ʒu
	D3DXVECTOR2 Scale;		//�T�C�Y
	float Rotation;			//��]
	D3DCOLOR Color;			//�F

	//�R���X�g���N�^
	Transform2();
	Transform2(D3DXVECTOR2 Position,D3DXVECTOR2 Scale,float Rotation);
	Transform2(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, float Rotation,D3DCOLOR Color);
	
};

#endif
