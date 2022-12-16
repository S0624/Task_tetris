#include"DxLib.h"
#include "ObjectMino.h"
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

	int kCoordinateX = 0;						//���ݒn������W���擾����
	int kCoordinateY = 0;						//���ݒn������W���擾����

	bool kIsEnd = false;						//�Q�[���̏I���t���O
	int kSuspend = 30;							//�~�m��������ď�̃~�m�������Ă���܂ł̎���

}

ObjectMino::ObjectMino() :
	m_frametimer(),								//�t���[���^�C�}�[
	m_pos(),									//�~�m�̃|�W�V����
	m_size(),									//�~�m�̃T�C�Y
	m_gravity(),								//�~�m�̏d��
	m_speed(),									//�~�m�̗����X�s�[�h
	m_placed(false),							//�u���ꂽ���ǂ���
	m_minotimer(),								//�~�m�����܂ōs���Ēu�����܂ł̃C���^�[�o��
	m_suspend()									//�~�m��������Ă��痎������܂ł̃^�C�}�[
{
	MinoInit();
}

void ObjectMino::Init()
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


void ObjectMino::MinoInit()
{
	m_pos.x = 180;								//�����ʒu
	m_pos.y = 25;								//�����ʒu
	m_size.x = 26;								//�����T�C�Y
	m_size.y = 26;								//�����T�C�Y
	m_gravity = m_size.y / 2;								//�d��
	m_speed = 2.5f;								//�X�s�[�h
	m_placed = false;
}

void ObjectMino::MoveUpdate()
{
	kCoordinateY = (m_pos.y - 25) / m_size.y;						//�~�m�̌��ݒn�����W�ɂ���
	kCoordinateX = (m_pos.x - kFieldDisplace) / m_size.x;			//�~�m�̌��ݒn�����W�ɂ���

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
		if (field[kCoordinateX - 1][kCoordinateY] == empty)
		{
			m_pos.x -= m_size.x;						//�L�[�������ꂽ�牟���ꂽ�����ɓ���
		}
	}
	if (Pad::isTrigger(PAD_INPUT_RIGHT))			//�E�̈ړ������A�ړ�����
	{
		if (field[kCoordinateX + 1][kCoordinateY] == empty)
		{
			m_pos.x += m_size.x;
		}
	}

	if (field[kCoordinateX][kCoordinateY + 1] != empty)								//field������o�Ȃ��悤�ɐݒ�
	{
		m_placed = true;
		return;
	}

	if (Pad::isTrigger(PAD_INPUT_UP))				//��̈ړ�����
	{
		for (int i = 0; i <= kBlocHeight; i++)
		{
			if (field[kCoordinateX][i] != empty)
			{
				m_pos.y = i + (i * 25);				//�u����ꏊ�̃`�F�b�N
				break;
			}
		}
	}

	if (Pad::isPress(PAD_INPUT_DOWN))				//���̈ړ�����
	{
		if (field[kCoordinateX][kCoordinateY] == empty)
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

void ObjectMino::Update()
{
	if (m_suspend > 0)
	{
		m_suspend--;
	}

	if (m_minotimer <= 0)
	{
		field[kCoordinateX][kCoordinateY] = input;		//�u���ꂽ��field�ɑ������
		m_placed = false;								//�t���O�����Ƃɖ߂�
		m_minotimer = kMinoTimer;
		if (m_suspend <= 0)
		{
			MinoInit();
		}
	}

	for (int j = 1; j < kBlocWindht - 1; j++)
	{
		if (field[j][0] != empty)
		{
			kIsEnd = true;								//�Q�[���I�[�o�[
		}
	}
	if (kIsEnd == false)
	{
		MoveUpdate();									//�~�m�̈ړ�����
	}

	bool disappear = false;
	int height = 0;
	for (int i = 1; i < kBlocHeight - 1; i++)
	{
		if (field[1][i] == input && field[2][i] == input && field[3][i] == input
			&& field[4][i] == input && field[5][i] == input && field[6][i] == input
			&& field[7][i] == input && field[8][i] == input && field[9][i] == input && field[10][i] == input)
		{
			disappear = true;
			height = i;
		}
	}
	for (int j = 1; j < kBlocWindht - 1; j++)
	{
		if (disappear == true)
		{
			field[j][height] = empty;
			m_suspend = kSuspend;
		}
	}

	//if (disappear == true)
	if (m_suspend == 1)
	{
		for (int i = kBlocHeight - 2; i >= 1; i--)
		{
			for (int j = 1; j < kBlocWindht - 1; j++)
			{
				field[j][i] = field[j][i - 1];
			}
		}
	}

	//return this;
}
void ObjectMino::Draw()
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

	DrawString(m_pos.x, m_pos.y, "��", GetColor(255, 0, 0));



	///////////////////////////////////////
	///        �m�F�p�̐��l�\��         ///
	///////////////////////////////////////

	if (kIsEnd == false)
	{
		DrawString(500, 0, "GamePlay", GetColor(255, 0, 0));
	}
	if (kIsEnd == true)
	{
		DrawString(500, 0, "GameOver", GetColor(255, 0, 0));
	}

	//DrawFormatString(600, 0, GetColor(255, 255, 255), "%d", kCount);
	//DrawFormatString(650, 0, GetColor(255, 255, 255), "%d", kTotal);
	DrawFormatString(650, 0, GetColor(255, 255, 255), "%d", m_suspend);
}