//
//	Input.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/16
//===============================================
#include<Windows.h>
#include<dinput.h>
#include"input.h"

#include"joycon_input.h"
#include"Dualshock4.h"
#include"Dualshock4.hpp"

//===============================================
//	�O���[�o���ϐ�
//===============================================
static LPDIRECTINPUT8		g_pInput		= NULL;				// DirectInput�I�u�W�F�N�g�ւ̃|�C���^

static LPDIRECTINPUTDEVICE8	g_pDevKeyboard = NULL;				// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
static BYTE					g_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏�񃏁[�N
static BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K�[��񃏁[�N
static BYTE					g_aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X��񃏁[�N

static LPDIRECTINPUTDEVICE8	g_pDevMouse		= NULL;				// ���̓f�o�C�X(�}�E�X)
static DIMOUSESTATE2		g_MouseState2	= { NULL };			//�}�E�X�̏��
static POINT				g_MousePos		= { NULL };			//�}�E�X�̏ꏊ

//===============================================
//	�֐�
//===============================================

//===============================================
//	������
//===============================================
void Input_Initalize(HWND hWnd,HINSTANCE hInstance )
{

	if (g_pInput == NULL) {

		// DirectInput�I�u�W�F�N�g�̍쐬
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL))) {
			MessageBox(hWnd, "Input�f�o�C�X�̎擾�Ɏ��s���܂����B", "�G���[", MB_OK);
			DestroyWindow(hWnd);
			return;
		}
	}

	// ���͏����̏�����
	if (g_pInput == NULL) {
		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�������ł�", "�G���[", MB_ICONWARNING);
		DestroyWindow(hWnd);
		return;
	}

	//------------------------------------
	//	�L�[�{�[�h
	//------------------------------------
	// �f�o�C�X�̍쐬
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "�L�[�{�[�h������", "�G���[", MB_ICONWARNING);
		DestroyWindow(hWnd);
		return;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�G���[", MB_ICONWARNING);
		DestroyWindow(hWnd);
		return;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�G���[", MB_ICONWARNING);
		DestroyWindow(hWnd);
		return;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevKeyboard->Acquire();

	//------------------------------------
	//	�}�E�X
	//------------------------------------
	//�}�E�X�f�o�C�X�擾
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		MessageBox(hWnd, "�}�E�X�������ł�", "�G���[", MB_ICONWARNING);
		DestroyWindow(hWnd);
		return;
	}

	//�}�E�X�̃f�[�^�t�H�[�}�b�g
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		MessageBox(hWnd, "�}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�G���[", MB_ICONWARNING);
		DestroyWindow(hWnd);
		return;
	}

	//�}�E�X�̋������[�h
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "�}�E�X�̋������[�h��ݒ�ł��܂���ł����B", "�G���[", MB_ICONWARNING);
		DestroyWindow(hWnd);
		return;
	}

	g_pDevMouse->Acquire();
}

//===============================================
//	���͍X�V
//===============================================
void Input_Update(HWND hWnd)
{
	//---------------------------------
	//	�L�[�{�[�h���
	//---------------------------------
	BYTE aKeyState[NUM_KEY_MAX];	//�L�[�X�e�[�^�X

	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		// aKeyState[DIK_SPACE] & 0x80

		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			// �L�[�g���K�[�E�����[�X���𐶐�
			g_aKeyStateTrigger[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			g_aKeyStateRelease[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & g_aKeyState[nCnKey];

			// �L�[�v���X����ۑ�
			g_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		g_pDevKeyboard->Acquire();
	}

	//------------------------------------
	//	�}�E�X���
	//------------------------------------
	GetCursorPos(&g_MousePos);					//�}�E�X��XY���W
	ScreenToClient(hWnd, &g_MousePos);		//�E�B���h�E�����W�ɕϊ�


	//�}�E�X�̃X�e�[�^�X
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &g_MouseState2)))
	{
		//���ڃf�[�^�̎擾�ɐ���
		int i = 0;
	}
	else
	{
		g_pDevMouse->Acquire();
	}

}

//===============================================
//	�I������
//===============================================
void Input_Finalize()
{
	//�}�E�X�f�o�C�X�̊J��
	if (g_pDevMouse != NULL)
	{
		g_pDevMouse->Unacquire();
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	if (g_pDevKeyboard != NULL)
	{
		// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
		// �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// ���͏����̏I������
	if (g_pInput != NULL) {

		// DirectInput�I�u�W�F�N�g�̊J��
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//===============================================
//	�L�[�{�[�h���
//===============================================

//-------------------------------------
//	�L�[�{�[�h�������Ă�
//-------------------------------------
bool Keyboard_IsPress(int nDIK)
{
	return (g_aKeyState[nDIK] & 0x80) ? true : false;
}

//-------------------------------------
//	�L�[�{�[�h��������
//-------------------------------------
bool Keyboard_IsTrigger(int nDIK)
{
	return (g_aKeyStateTrigger[nDIK] & 0x80) ? true : false;
}

//-------------------------------------
//	�L�[�{�[�h�������
//-------------------------------------
bool Keyboard_IsRelease(int nDIK)
{
	return (g_aKeyStateRelease[nDIK] & 0x80) ? true : false;
}

//===============================================
//	�}�E�X���
//===============================================

//-------------------------------------
//	���N���b�N
//-------------------------------------
bool Mouse_IsLeftDown()
{
	return (g_MouseState2.rgbButtons[0] & 0x80) ? true : false;
}

//-------------------------------------
//	�E�N���b�N
//-------------------------------------
bool Mouse_IsRightDown()
{
	return (g_MouseState2.rgbButtons[1] & 0x80) ? true : false;
}

//-------------------------------------
//	�z�C�[���N���b�N
//-------------------------------------
bool Mouse_IsCenterDown()
{
	return (g_MouseState2.rgbButtons[2] & 0x80) ? true : false;
}

//-------------------------------------
//	�}�E�X�����x�@X
//-------------------------------------
float Mouse_IsAccelerationX()
{
	return (float)g_MouseState2.lX;
}

//-------------------------------------
//	�}�E�X�����x�@Y
//-------------------------------------
float Mouse_IsAccelerationY()
{
	return (float)g_MouseState2.lY;
}

//-------------------------------------
//	�}�E�X�����x�@Z�@(�X�N���[��)
//-------------------------------------
float Mouse_IsAccelerationZ()
{
	return (float)g_MouseState2.lZ;
}

//-------------------------------------
//	�}�E�XX���W
//-------------------------------------
float Mouse_IsMouseX()
{
	return (float)g_MousePos.x;
}

//-------------------------------------
//	�}�E�XY���W
//-------------------------------------
float Mouse_IsMouseY()
{
	return (float)g_MousePos.y;
}


