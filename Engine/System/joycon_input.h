//=============================================================================
//
// �W���C�R�����͏��� [joycon_input.h]
//
//=============================================================================
#ifndef JOYCON_INPUT_H
#define JOYCON_INPUT_H

#include <Windows.h>
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION		(0x0800)
#endif // !DIRECTINPUT_VERSION

#include <dinput.h>


#define JOYCON_LEFT_STICK_X		(g_Joy.lRx)					// ���X�e�B�b�NX���
#define JOYCON_LEFT_STICK_Y		(g_Joy.lRy)					// ���X�e�B�b�NY���
#define JOYCON_AV_YAW			(g_Joy.lRz)					// �p���x���i���[�j
#define JOYCON_AV_ROLL			(g_Joy.rglSlider[0])		// �p���x���i���[���j
#define JOYCON_AV_PITCH			(g_Joy.rglSlider[1])		// �p���x���i�s�b�`�j
#define BASE_POSITION			(32767)						// ��ʒu


// �W���C�R�����z�{�^�����
typedef enum
{
	JOYCON_BUTTON_INDEX_L_DOWN = 0,				// ���{�^��
	JOYCON_BUTTON_INDEX_L_UP,					// ��{�^��
	JOYCON_BUTTON_INDEX_L_RIGHT,				// �E�{�^��
	JOYCON_BUTTON_INDEX_L_LEFT,					// ���{�^��
	JOYCON_BUTTON_INDEX_L_SR,					// ����SR�{�^��
	JOYCON_BUTTON_INDEX_L_SL,					// ����SL�{�^��
	JOYCON_BUTTON_INDEX_L_L,					// L�{�^��
	JOYCON_BUTTON_INDEX_L_ZL,					// ZL�{�^��
	JOYCON_BUTTON_INDEX_L_MINUS,				// �}�C�i�X�{�^��
	JOYCON_BUTTON_INDEX_L_STICK = 11,			// ���X�e�B�b�N��������
	JOYCON_BUTTON_INDEX_R_Y = 16,				// Y�{�^��
	JOYCON_BUTTON_INDEX_R_X,					// X�{�^��
	JOYCON_BUTTON_INDEX_R_B,					// B�{�^��
	JOYCON_BUTTON_INDEX_R_A,					// A�{�^��
	JOYCON_BUTTON_INDEX_R_SR,					// �E��SR�{�^��
	JOYCON_BUTTON_INDEX_R_SL,					// �E��SL�{�^��
	JOYCON_BUTTON_INDEX_R_R,					// R�{�^��
	JOYCON_BUTTON_INDEX_R_ZR,					// ZR�{�^��
	JOYCON_BUTTON_INDEX_R_PLUS = 25,			// �v���X�{�^��
	JOYCON_BUTTON_INDEX_R_STICK,				// �E�X�e�B�b�N
	JOYCON_BUTTON_INDEX_R_HOME = 28,			// �z�[���{�^��

	JOYCON_BUTTON_INDEX_MAX
}JOYCON_BUTTON_INDEX;


// �v���g�^�C�v�錾
HRESULT JoyconInput_Initialize(HWND hWnd, LPDIRECTINPUT8 pInput);
void JoyconInput_Finalize(void);
void JoyconInput_Update(void);
bool JoyconInput_IsPress(int nKey);
bool JoyconInput_IsTrigger(int nKey);
bool JoyconInput_IsRelease(int nKey);
int JoyconInput_GetLeftStickX(void);
int JoyconInput_GetLeftStickY(void);
int JoyconInput_GetAVYaw(void);
int JoyconInput_GetAVRoll(void);
int JoyconInput_GetAVPitch(void);

void JoyconInput_Draw(void);


#endif