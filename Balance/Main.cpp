#include <DxLib.h>
#include <string>
#include "WindowInfo.h"
#include "GamePlayManager.h"


//����ҏW���|�W�g���m�F�p
// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//	Window���[�h�̐ݒ��Window�^�C�g����ݒ肷��
	ChangeWindowMode(true);
	SetMainWindowText("Balance");

	//	��ʃT�C�Y��ݒ�
	SetGraphMode(WindowInfo::WindowWidth, WindowInfo::WindowHeight, 16);
	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;				// �G���[���N�����璼���ɏI��
	}

	//	�`�����w��
	SetDrawScreen(DX_SCREEN_BACK);

	//	��ʔw�i�̐F��ݒ肷��
	SetBackgroundColor(0, 0, 0);
	//	���s
	GamePlayManager::Instance().Update();

	//	�������
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}