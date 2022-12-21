#include"DxLib.h"
#include "SceneMain.h"
#include"ObjectMino.h"
#include"UI/Pad.h"
#include"game.h"

namespace
{
	ObjectMino mino;
	//ObjectMino Mino[2];

	constexpr int kFieldHeight = 0;				//field�̑傫��
	constexpr int kFieldWindth = 0;				//field�̑傫��
	constexpr int kFieldFloor = 570;			//field�̉�
	constexpr int kFieldDisplace = 50;			//field�����炷


	constexpr int kFrameTimer = 50;				//�~�m����������C���^�[�o��
	constexpr int kMinoTimer = 5;				//�~�m���ݒu�����܂ł̎���

	constexpr int kBlocHeight = 22;				//field�̍���
	constexpr int kBlocWindht = 12;				//field�̉���
	int kField[kBlocWindht][kBlocHeight];		//field�̐ݒu

	int kCoordinateX = 0;						//���ݒn������W���擾����
	int kCoordinateY = 0;						//���ݒn������W���擾����

	bool kIsEnd = false;						//�Q�[���̏I���t���O
	int kSuspend = 30;							//�~�m��������ď�̃~�m�������Ă���܂ł̎���

	float kPosX = 0;
	float kPosY = 0;
}

SceneMain::SceneMain() :
	m_frametimer(),								//�t���[���^�C�}�[
	m_pos(),									//�~�m�̃|�W�V����
	m_size(),									//�~�m�̃T�C�Y
	m_gravity(),								//�~�m�̏d��
	m_speed(),									//�~�m�̗����X�s�[�h
	m_placed(false),							//�u���ꂽ���ǂ���
	m_minotimer(),								//�~�m�����܂ōs���Ēu�����܂ł̃C���^�[�o��
	m_suspend()									//�~�m��������Ă��痎������܂ł̃^�C�}�[
{
	//mino.MinoInit();
	//for (auto& mino : Mino)
	{
		mino.Init();
		mino.MinoInit();
	}
	//for (auto& mino : Mino)
	//{
	//	mino.MinoInit();
	//}
}

void SceneMain::Init()
{

	//m_frametimer = kFrameTimer;					//�^�C�}�[��ݒ�
	//m_minotimer = kMinoTimer;
	//
	for (int i = 0; i < kBlocHeight; i++)		//field�̏�����
	{
		for (int j = 0; j < kBlocWindht; j++)
		{
			kField[j][i] = empty;
		}
	}

	for (int i = 0; i < kBlocHeight; i++)		//�t���[���̕\��
	{
		kField[0][i] = frame;
		kField[11][i] = frame;
	}
	for (int j = 0; j < kBlocWindht; j++)
	{
		kField[j][21] = frame;
	}
}


void SceneMain::MinoInit()
{
	//	m_pos.x = 180;								//�����ʒu
	//	m_pos.y = 25;								//�����ʒu
	//	m_size.x = 26;								//�����T�C�Y
	//	m_size.y = 26;								//�����T�C�Y
	//	m_gravity = m_size.y / 2;								//�d��
	//	m_speed = 2.5f;								//�X�s�[�h
	//	m_placed = false;
}

void SceneMain::MoveUpdate()
{
	//for (auto& mino : Mino)
	//{
		//mino.MoveUpdate();
	//}
	//	kCoordinateY = (m_pos.y - 25) / m_size.y;						//�~�m�̌��ݒn�����W�ɂ���
	//	kCoordinateX = (m_pos.x - kFieldDisplace) / m_size.x;			//�~�m�̌��ݒn�����W�ɂ���
	//
	//	if (m_placed == true)								//	�~�m�̐ݒu����
	//	{
	//		if (m_minotimer > 0)
	//		{
	//			m_minotimer--;
	//			return;
	//		}
	//	}
	//
	//	if (Pad::isTrigger(PAD_INPUT_LEFT))				//���̈ړ������A�ړ�����
	//	{
	//		if (field[kCoordinateX - 1][kCoordinateY] == empty)
	//		{
	//			m_pos.x -= m_size.x;						//�L�[�������ꂽ�牟���ꂽ�����ɓ���
	//		}
	//	}
	//	if (Pad::isTrigger(PAD_INPUT_RIGHT))			//�E�̈ړ������A�ړ�����
	//	{
	//		if (field[kCoordinateX + 1][kCoordinateY] == empty)
	//		{
	//			m_pos.x += m_size.x;
	//		}
	//	}
	//	
	//	if (field[kCoordinateX][kCoordinateY + 1] != empty)								//field������o�Ȃ��悤�ɐݒ�
	//	{
	//		m_placed = true;
	//		return;
	//	}						
	//
	//	if (Pad::isTrigger(PAD_INPUT_UP))				//��̈ړ�����
	//	{
	//		for (int i = 0; i <= kBlocHeight; i++)
	//		{
	//			if (field[kCoordinateX][i] != empty)
	//			{
	//				m_pos.y = i + (i * 25);				//�u����ꏊ�̃`�F�b�N
	//				break;
	//			}
	//		}
	//	}
	//	
	//	if (Pad::isPress(PAD_INPUT_DOWN))				//���̈ړ�����
	//	{
	//		if (field[kCoordinateX][kCoordinateY] == empty)
	//		{
	//			m_pos.y += m_speed;							//�L�[�������ꂽ�牟���ꂽ�����ɓ���
	//		}
	//		return;										//������Ă���Ԃ̓t���[���^�C�}�[�̏������X�L�b�v����
	//	}
	//	
	//	if (m_frametimer > 0)							//���L�[��������Ă��Ȃ��Ƃ��̓^�C�}�[�̐������炷
	//	{
	//		m_frametimer--;
	//	}
	//	if (m_frametimer == 0)							//�^�C�}�[���[���ɂȂ����痎��������
	//	{
	//		m_pos.y += m_gravity;
	//		m_frametimer = kFrameTimer;					//������������^�C�}�[�̐��l�����ɖ߂�
	//	}
}

SceneBase* SceneMain::Update()
{
	//for (auto& mino : Mino) 
	{
		mino.Update();
	}

	if (mino.flag() == true)
	{
		kField[mino.PosX()][mino.PosY()] = input;		//�u���ꂽ��field�ɑ������
	}

	if (m_suspend > 0)
	{
		m_suspend--;
	}

	//if (m_minotimer <= 0)
	//{
	//	field[kCoordinateX][kCoordinateY] = input;		//�u���ꂽ��field�ɑ������
	//	m_placed = false;								//�t���O�����Ƃɖ߂�
	//	m_minotimer = kMinoTimer;
	//	for (auto& mino : Mino)
	//	{
	//		if (m_suspend <= 0)
	//		{
	//			mino.MinoInit();
	//		}
	//	}
	//}
	//
	//for (int j = 1; j < kBlocWindht - 1; j++)
	//{
	//	if (field[j][0] != empty)
	//	{
	//		kIsEnd = true;								//�Q�[���I�[�o�[
	//	}
	//}
	//if (kIsEnd == false)
	//{
	//	for (auto& mino : Mino)
	//	{
	//		mino.MoveUpdate();									//�~�m�̈ړ�����
	//	}
	//}
	//
	bool disappear = false;
	int height = 0;
	for (int i = 1; i < kBlocHeight - 1; i++)
	{
		if (kField[1][i] == input && kField[2][i] == input && kField[3][i] == input
			&& kField[4][i] == input && kField[5][i] == input && kField[6][i] == input
			&& kField[7][i] == input && kField[8][i] == input && kField[9][i] == input && kField[10][i] == input)
		{
			disappear = true;
			height = i;
		}
	}
	for (int j = 1; j < kBlocWindht - 1; j++)
	{
		if (disappear == true)
		{
			kField[j][height] = empty;
			m_suspend = kSuspend;
		}
	}

	if (m_suspend <= 0)
	{
		MinoInit();
	}

	if (m_suspend == 1)
		//if (disappear == true)
	{
		for (int i = kBlocHeight - 2; i >= 1; i--)
		{
			for (int j = 1; j < kBlocWindht - 1; j++)
			{
				kField[j][i] = kField[j][i - 1];
			}
		}
	}

	mino.Field(kField);		//field�̐ݒu;

	return this;
}
void SceneMain::Draw()
{
	for (int i = 0; i < kBlocHeight; i++)
	{
		for (int j = 0; j < kBlocWindht; j++)
		{
			switch (kField[j][i])
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

	//for (auto& mino : Mino)
	{
		mino.Draw();
	}


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
	DrawFormatString(650, 200, GetColor(255, 255, 255), "%d", mino.PosX());
	DrawFormatString(650, 250, GetColor(255, 255, 255), "%d", mino.PosY());
}