//=============================================================================
//
// �W���C�R�����͏��� [joycon_input.cpp]
//
//=============================================================================
#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include "input.h"
#include "debug_font.h"
#include "joycon_input.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔
#define	LIMIT_COUNT_REPEAT	( 5 )	// ���s�[�g�J�E���g���~�b�^�[


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECTINPUTDEVICE8	g_pDevGamepad = NULL;				// ���̓f�o�C�X(�Q�[���p�b�h)�ւ̃|�C���^
BYTE					g_JoyTrigger[NUM_KEY_MAX];			// �Q�[���p�b�h�̃g���K�[��񃏁[�N
BYTE					g_JoyRelease[NUM_KEY_MAX];			// �Q�[���p�b�h�̃����[�X��񃏁[�N
BYTE					g_JoyRepeat[NUM_KEY_MAX];			// �Q�[���p�b�h�̃��s�[�g��񃏁[�N
int						g_JoyRepeatCnt[NUM_KEY_MAX];		// �Q�[���p�b�h�̃��s�[�g�J�E���^

DIJOYSTATE2				g_Joy;								// �Q�[���p�b�h�̏�����
bool					gamepadUseEnable = false;			// �Q�[���p�b�h���g�p�\�Ȃ�true



//=============================================================================
//	�Q�[���p�b�h�̏�����
//=============================================================================
HRESULT JoyconInput_Initialize(HWND hWnd, LPDIRECTINPUT8 pInput)
{
	// �f�o�C�X�̍쐬
	if (FAILED(pInput->CreateDevice(GUID_Joystick, &g_pDevGamepad, NULL)))
	{
		MessageBox(hWnd, "�Q�[���p�b�h���˂��I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevGamepad->SetDataFormat(&c_dfDIJoystick2)))
	{
		MessageBox(hWnd, "�Q�[���p�b�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(g_pDevGamepad->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "�Q�[���p�b�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �Q�[���p�b�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	if (FAILED(g_pDevGamepad->Poll()))
	{
		g_pDevGamepad->Acquire();

	}

	// �Q�[���p�b�h���g�p�\�ɐݒ�
	gamepadUseEnable = true;

	return S_OK;
}

//=============================================================================
//	�Q�[���p�b�h�̏I������
//=============================================================================
void JoyconInput_Finalize(void)
{
	if (g_pDevGamepad != NULL)
	{
		// ���̓f�o�C�X(�Q�[���p�b�h)�̊J��
		// �Q�[���p�b�h�ւ̃A�N�Z�X�����J��(���͐���I��)
		g_pDevGamepad->Unacquire();

		g_pDevGamepad->Release();
		g_pDevGamepad = NULL;
	}
}

//=============================================================================
//	�Q�[���p�b�h�̍X�V����
//=============================================================================
void JoyconInput_Update(void)
{

	DIJOYSTATE2 Joy;


	// �Q�[���p�b�h���g�p�\���ǂ������f
	if (gamepadUseEnable) {

		// �f�o�C�X����f�[�^���擾
		if (SUCCEEDED(g_pDevGamepad->GetDeviceState(sizeof(DIJOYSTATE2), &Joy)))
		{

			for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
			{

				//�L�[�g���K�[�����[�X���̍쐬
				g_JoyTrigger[nCnKey] = (g_Joy.rgbButtons[nCnKey] ^ Joy.rgbButtons[nCnKey]) & Joy.rgbButtons[nCnKey];

				g_JoyRelease[nCnKey] = (g_Joy.rgbButtons[nCnKey] ^ Joy.rgbButtons[nCnKey]) & g_Joy.rgbButtons[nCnKey];

				//�L�[���s�[�g���̐���
				if (Joy.rgbButtons[nCnKey] & 0x80) {			//�s��N�����ꍇ, if( Joy.rgbButtons[nCnKey] & 0x80 )
					if (g_JoyRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT) {
						g_JoyRepeatCnt[nCnKey]++;
						if (g_JoyRepeatCnt[nCnKey] == 1) {
							//if( g_JoyRepeatCnt[nCnKey]==1 || g_JoyRepeatCnt[nCnKey]>=LIMIT_COUNT_REPEAT ){

							g_JoyRepeat[nCnKey] = Joy.rgbButtons[nCnKey];

						}
						else {

							g_JoyRepeat[nCnKey] = 0;

						}
					}
				}
				else {

					g_JoyRepeat[nCnKey] = 0;
					g_JoyRepeatCnt[nCnKey] = 0;

				}

				// �L�[�v���X����ۑ�
				//g_Joy.rgbButtons[nCnKey] = Joy.rgbButtons[nCnKey];

			}

			// �L�[�v���X����ۑ�
			g_Joy = Joy;

		}
		else {
			// �Q�[���p�b�h�ւ̃A�N�Z�X�����擾
			g_pDevGamepad->Acquire();
		}
	}
}

//=============================================================================
//	�Q�[���p�b�h�̃{�^���̃v���X��Ԃ��擾
//=============================================================================
bool JoyconInput_IsPress(int nKey)
{
	//return (g_Joy[nKey] & 0x80) ? true: false;
	return (g_Joy.rgbButtons[nKey] & 0x80) ? true : false;
}

//=============================================================================
//	�Q�[���p�b�h�̃{�^���̃g���K�[��Ԃ��擾
//=============================================================================
bool JoyconInput_IsTrigger(int nKey)
{
	return (g_JoyTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
//	�Q�[���p�b�h�̃{�^���̃����[�X��Ԃ��擾
//=============================================================================
bool JoyconInput_IsRelease(int nKey)
{
	return (g_JoyRelease[nKey] & 0x80) ? true : false;
}


//=============================================================================
//	���X�e�B�b�N��X���W���擾
//=============================================================================
int JoyconInput_GetLeftStickX(void)
{
	return g_Joy.lX - BASE_POSITION;
}

//=============================================================================
//	���X�e�B�b�N��Y���W���擾
//=============================================================================
int JoyconInput_GetLeftStickY(void)
{
	return -g_Joy.lY + BASE_POSITION;
}


//=============================================================================
//	�p���x���擾�i���[�j
//=============================================================================
int JoyconInput_GetAVYaw(void)
{
	return -g_Joy.lRz + BASE_POSITION;
}


//=============================================================================
//	�p���x���擾�i���[���j
//=============================================================================
int JoyconInput_GetAVRoll(void)
{
	return -g_Joy.rglSlider[0] + BASE_POSITION;
}


//=============================================================================
//	�p���x���擾�i�s�b�`�j
//=============================================================================
int JoyconInput_GetAVPitch(void)
{
	return g_Joy.rglSlider[1] - BASE_POSITION;
}



void JoyconInput_Draw(void)
{
#ifdef _DEBUG
	DebugFont_Draw(0, 0, "�X�e�B�b�NX:%d", JoyconInput_GetLeftStickX());
	DebugFont_Draw(0, 20, "�X�e�B�b�NY:%d", JoyconInput_GetLeftStickY());
	DebugFont_Draw(0, 40, "���[:%d", JoyconInput_GetAVYaw());
	DebugFont_Draw(0, 60, "�s�b�`:%d", JoyconInput_GetAVPitch());
	DebugFont_Draw(0, 80, "���[��:%d", JoyconInput_GetAVRoll());
	for (int i = 0; i < 30; i++)
	{
		DebugFont_Draw(200, 20 * i, "�{�^��%d:%d", i, g_Joy.rgbButtons[i]);
	}
#endif // _DEBUG
}