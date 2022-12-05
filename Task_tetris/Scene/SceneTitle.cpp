#include"DxLib.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include"UI/Pad.h"
#include"game.h"

namespace
{
	bool kCheckisTrigger = false;							//�{�^���������ꂽ���`�F�b�N���邽�߂ɗp��
	const char*  kNameTitle = "TETRIS";						//�^�C�g��
	const char*  kNameGuide = "�{�^���������Ă�������";		//�K�C�h�̕\��
}

SceneTitle::SceneTitle() :
	m_fadeSpeed(-5),										//�t�F�[�h���x
	m_fadeColor(255)										//�t�F�[�h�J���[
{
}

void SceneTitle::Init()
{
}


SceneBase* SceneTitle::Update()
{
	Fead();
	
	if (m_fadeColor < 0)
	{
		m_fadeColor = 0;
	}
	if(m_fadeColor > 255)
	{
		m_fadeSpeed = 255;
		return(new SceneMain);
		kCheckisTrigger = false;
	}

	return this;
}
void SceneTitle::Fead()
{
	m_fadeColor += m_fadeSpeed;				//�t�F�[�h����
	if (kCheckisTrigger == false)			//�t�F�[�h���I���܂ŏ������~�߂�
	{
		if (m_fadeColor > 0)
		{
			return;
		}
	}
	if (kCheckisTrigger == true)			//�{�^���������ꂽ��t�F�[�h����܂ő�����󂯕t���Ȃ�
	{
		if (m_fadeColor <= 255)
		{
			return;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_1))		//�{�^���������ꂽ��t�F�[�h���J�n����
	{
		kCheckisTrigger = true;
		m_fadeSpeed *= -1;
	}
}
void SceneTitle::Draw()
{
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kNameTitle, -1)) / 2, 425, kNameTitle, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kNameGuide, -1)) / 2, 500, kNameGuide, GetColor(255, 255, 255));			//�^�C�g���K�C�h�̕\��

	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeColor);				//�t�F�[�h
	DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), true);				//���Ԃ���F
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);						//���ɖ߂�
}