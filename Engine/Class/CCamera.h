//
//	CCamera.h
//		Author:HIROMASA IKEDA	DATE:2018/10/16
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CCAMERA_H
#define CCAMERA_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"
#include<d3dx9.h>

//Class
#include"CTransform.h"

//===============================================
//	�}�N����`	define
//===============================================


//================================================
//	�񋓌^		enum
//================================================


//===============================================
//	�}�N����`
//===============================================
#define CAMERA_POS (D3DXVECTOR3(0.0f, 5.0f, 5.0f))		//�J�����ʒu
#define CAMERA_AT (D3DXVECTOR3(0.0f, 0.0f, 0.0f))		//�J�����̒����_
#define CAMERA_UP (D3DXVECTOR3(0.0f,1.0f,0.0f))			//�J�����̏���� (�ǂ���������Ō���́H)
#define CAMERA_FORWARD (D3DXVECTOR3(0.0f,0.0f,-1.0f))	//�J�����O
#define CAMERA_INITIALSPEED (0.05f)						//�J�����̏������x

#define CAMERA_NEAR (0.1f)
#define CAMERA_WAR (100.0f)

#define SCREEN_ASPECT ((float)WINDOWSCREEN_WIDTH / WINDOWSCREEN_HEIGHT)
#define CAMERA_ATDISTANCE (10.0f)
#define CAMERA_FOV (D3DXToRadian(60))

//================================================
//	�O���[�o���ϐ��@global
//================================================

//================================================
//	�N���X		class
//================================================

//-------------------------------------
//	absCamera�@���ۃN���X
//-------------------------------------
class ACamera
{
private:
	static ACamera* pMainCamera;	//���C���J����

public:
	static ACamera* Get_Main();	//���C���J�����擾
	static D3DXMATRIX Get_ViewMatrix();	//View�s��
	static bool Begin();		//�`��J�n

public:
	D3DMATRIX MtxView;			//View�s��

	D3DXVECTOR3 position;		//�ʒu
	D3DXVECTOR3 at;				//�����_
	D3DXVECTOR3 up;				//��
	D3DXVECTOR3 right;			//�E
	D3DXVECTOR3 forward;		//�O

	float atDistance;			//�����_�܂ł̋���
	float fov;					//��p

public:
	ACamera() :ACamera(CAMERA_POS, CAMERA_AT, CAMERA_ATDISTANCE, CAMERA_FOV) {};
	ACamera(D3DXVECTOR3 Position) :ACamera(Position,CAMERA_AT,CAMERA_ATDISTANCE,CAMERA_FOV) {};
	ACamera(D3DXVECTOR3 Position, D3DXVECTOR3 At) :ACamera(Position, At, CAMERA_ATDISTANCE, CAMERA_FOV) {};
	ACamera(D3DXVECTOR3 Position, D3DXVECTOR3 At, float AtDistance) :ACamera(Position, At, AtDistance, CAMERA_FOV) {};
	ACamera(D3DXVECTOR3 Position,D3DXVECTOR3 At,float AtDistance,float fov);

public:
	void Set_Main();			//���C���J�����ɐݒ�

public:
	virtual void Update() PURE;	//�X�V����
};

//-------------------------------------
//	Camera�@�N���X
//-------------------------------------
class Camera:public ACamera
{
public:
	Camera():Camera(CAMERA_POS, CAMERA_AT, CAMERA_ATDISTANCE, CAMERA_FOV) {};
	Camera(D3DXVECTOR3 Position) : Camera(Position, CAMERA_AT, CAMERA_ATDISTANCE, CAMERA_FOV) {};
	Camera(D3DXVECTOR3 Position, D3DXVECTOR3 At) :Camera(Position, At, CAMERA_ATDISTANCE, CAMERA_FOV) {};
	Camera(D3DXVECTOR3 Position, D3DXVECTOR3 At, float AtDistance, float fov);

public:
	virtual void Update() override;		//�X�V
};

//-------------------------------------
//	�}�E�X�E�L�[����Ȃǂ��ł���J����
//-------------------------------------
class OperationCamera:public ACamera
{
private:
	float Speed;
	float SpeedMag;
public:
	OperationCamera() :OperationCamera(CAMERA_POS, CAMERA_AT, CAMERA_ATDISTANCE, CAMERA_FOV) {};
	OperationCamera(D3DXVECTOR3 Position) : OperationCamera(Position, CAMERA_AT, CAMERA_ATDISTANCE, CAMERA_FOV) {};
	OperationCamera(D3DXVECTOR3 Position, D3DXVECTOR3 At, float AtDistance, float fov);
public:
	void Update() final;		//�X�V
};

#endif