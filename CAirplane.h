//
//	CAirplane.h
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CAIRPLANE_H
#define CAIRPLANE_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"

//Class
#include<d3dx9.h>
#include"CGameObject.h"
#include"CCamera.h"

//================================================
//	�}�N����`	define
//================================================
#define AIRPLANE_ADVANCE_SPEED (0.0025f)
#define AIRPLANE_MAX_PROPELLER_SPEEFD (2.0f)

//================================================
//	�񋓌^		enum
//================================================


//================================================
//	�\����		struct/typedef
//================================================


//================================================
//	�O���[�o���ϐ��@global
//================================================


//================================================
//	�N���X		class
//================================================


//-------------------------------------
//	Airplane
//-------------------------------------
class CAirplane :public GameObject
{
	
private:
	//�p�[�c�Q
	GameObject Propeller;
	GameObject WingRight_Up;
	GameObject WingRight_Down;
	GameObject WingLeft_Up;
	GameObject WingLeft_Down;
	GameObject WingBack_Up;
	GameObject WingBack_Down;

private:
	Camera camera;
	Camera Cockpit;			//���c��

public:
	float Speed;
	float Propeller_Speed;
public:
	CAirplane(Transform* pTransform);

public:	//�J����
	
	void Boarding();	//��荞��
	void Change();		//�؂�ւ�

public:
	//�����n
	void Advance();		//�O�i
	

public:
	void Update();
};

#endif