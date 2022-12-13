#include"DxLib.h"
#include "SceneMain.h"
#include"UI/Pad.h"
#include"game.h"

namespace
{
	constexpr int kFieldHeight = 0;				//field�̑傫��
	constexpr int kFieldWindth = 0;				//field�̑傫��
	constexpr int kBlocHeight = 22;				//field�̍���
	constexpr int kBlocWindht = 12;				//field�̉���
	constexpr int kFieldFloor = 570;			//field�̉�
	constexpr int kFieldDisplace = 50;			//field�����炷


	constexpr int kFrameTimer = 50;				//�~�m����������C���^�[�o��
	constexpr int kMinoTimer = 5;				//�~�m���ݒu�����܂ł̎���

	int field[kBlocWindht][kBlocHeight];		//field�̐ݒu
	
	int m_coordinateX = 0;
	int m_coordinateY = 0;

	bool isEnd = false;
}

SceneMain::SceneMain():
	m_frametimer(),								//�t���[���^�C�}�[
	m_pos(),									//�~�m�̃|�W�V����
	m_size(),									//�~�m�̃T�C�Y
	m_gravity(),								//�~�m�̏d��
	m_speed(),									//�~�m�̗����X�s�[�h
	m_placed(false),
	m_minotimer()
{
	MinoInit();
}

void SceneMain::Init()
{
	m_frametimer = kFrameTimer;					//�^�C�}�[��ݒ�
	m_minotimer = kMinoTimer;
	
	for (int i = 0; i < kBlocHeight; i++)		//field�̏�����
	{
		for (int j = 0; j < kBlocWindht; j++)
		{
			field[j][i] = empty;
		}
	}
	
	for (int i = 0; i < kBlocHeight; i++)		//�t���[���̕\��
	{
		field[0][i] = frame;
		field[11][i] = frame;
	}
	for (int j = 0; j < kBlocWindht; j++)
	{
		field[j][21] = frame;
	}
}


void SceneMain::MinoInit()
{
	m_pos.x = 180;								//�����ʒu
	m_pos.y = 25;								//�����ʒu
	m_size.x = 26;								//�����T�C�Y
	m_size.y = 26;								//�����T�C�Y
	m_gravity = m_size.y / 2;								//�d��
	m_speed = 2.5f;								//�X�s�[�h
	m_placed = false;
}

void SceneMain::MoveUpdate()
{
	m_coordinateY = (m_pos.y - 25) / m_size.y;
	m_coordinateX = (m_pos.x - kFieldDisplace) / m_size.x;

	if (m_placed == true)								//	�~�m�̐ݒu����
	{
		if (m_minotimer > 0)
		{
			m_minotimer--;
			return;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_LEFT))				//���̈ړ������A�ړ�����
	{
		if (field[m_coordinateX - 1][m_coordinateY] == empty)
		{
			m_pos.x -= m_size.x;						//�L�[�������ꂽ�牟���ꂽ�����ɓ���
		}
	}
	if (Pad::isTrigger(PAD_INPUT_RIGHT))			//�E�̈ړ������A�ړ�����
	{
		if (field[m_coordinateX + 1][m_coordinateY] == empty)
		{
			m_pos.x += m_size.x;
		}
	}
	
	if (field[m_coordinateX][m_coordinateY + 1] != empty)								//field������o�Ȃ��悤�ɐݒ�
	{
		m_placed = true;
		return;
	}						

	if (Pad::isTrigger(PAD_INPUT_UP))				//��̈ړ�����
	{
		for (int i = kBlocHeight; i > 0; i--)
		{
			if (field[m_coordinateX][i - 1] == empty)
			{
				m_pos.y = i + (i * 25);				//�u����ꏊ�̃`�F�b�N
				break;
			}
		}
	}
	
	if (Pad::isPress(PAD_INPUT_DOWN))				//���̈ړ�����
	{
		if (field[m_coordinateX][m_coordinateY + 1] == empty)
		{
			m_pos.y += m_speed;							//�L�[�������ꂽ�牟���ꂽ�����ɓ���
		}
		return;										//������Ă���Ԃ̓t���[���^�C�}�[�̏������X�L�b�v����
	}
	
	if (m_frametimer > 0)							//���L�[��������Ă��Ȃ��Ƃ��̓^�C�}�[�̐������炷
	{
		m_frametimer--;
	}
	if (m_frametimer == 0)							//�^�C�}�[���[���ɂȂ����痎��������
	{
		m_pos.y += m_gravity;
		m_frametimer = kFrameTimer;					//������������^�C�}�[�̐��l�����ɖ߂�
	}
}

SceneBase* SceneMain::Update()
{
	if (m_minotimer <= 0)
	{
		field[m_coordinateX][m_coordinateY] = input;
		m_placed = false;
		m_minotimer = kMinoTimer;
		MinoInit();
	}

	for (int j = 1; j < kBlocWindht - 1; j++)
	{
		if (field[j][0] != empty)
		{
			isEnd = true;
		}
	}
	if (isEnd == false)
	{
		MoveUpdate();									//�~�m�̈ړ�����
	}

	for (int j = 1; j < kBlocWindht - 1; j++)
	{
		if (field[1][20] == input && field[2][20] == input && field[3][20] == input
			&& field[4][20] == input && field[5][20] == input && field[6][20] == input
			&& field[7][20] == input && field[8][20] == input && field[9][20] == input && field[10][20] == input)
		{
			field[j][20] = empty;
		}
	}

	return this;
}
void SceneMain::Draw()
{
	for (int i = 0; i < kBlocHeight; i++)
	{
		for (int j = 0; j < kBlocWindht; j++)
		{
			switch (field[j][i])
			{
			case empty:
				DrawString(kFieldDisplace + j + (j * 25), 25 + i + (i * 25), "�@", GetColor(255, 255, 255));
			default:
				break;
			case input:
				DrawString(kFieldDisplace + j + (j * 25), 25 + i + (i * 25), "��", GetColor(255, 255, 255));
				break;
			case frame:
				DrawString(kFieldDisplace + j + (j * 25), 25 + i + (i * 25), "��", GetColor(255, 255, 255));
				break;
			}
		}
	}

	DrawString(m_pos.x, m_pos.y, "��",GetColor(255, 0, 0));



	///////////////////////////////////////
	///        �m�F�p�̐��l�\��         ///
	///////////////////////////////////////

	if (isEnd == false)
	{
		DrawString(500, 0, "GamePlay", GetColor(255, 0, 0));
	}
	if (isEnd == true)
	{
		DrawString(500, 0, "GameOver", GetColor(255, 0, 0));
	}
}
