#include"DxLib.h"
#include "SceneMain.h"
#include"UI/Pad.h"
#include"game.h"

namespace
{
	constexpr int kFieldHeight = 0;				//field�̑傫��
	constexpr int kFieldWindth = 0;				//field�̑傫��
	//constexpr int kFieldHeight = 75;
	//constexpr int kFieldWindth = 100;
	constexpr int kBlocHeight = 20;				//field�̍���
	constexpr int kBlocWindht = 10;				//field�̉���
	constexpr int kFieldFloor = 570;			//field�̉�

	constexpr int kFrameTimer = 50;

	int field[kBlocHeight][kBlocWindht];
	
	int x = 0;
	int y = 0;

	const char* kNameTitle = "Main���";
	const char* kNameGuide = "������";
}

SceneMain::SceneMain():
	m_frametimer(),								//�t���[���^�C�}�[
	m_pos(),									//�~�m�̃|�W�V����
	m_size(),									//�~�m�̃T�C�Y
	m_gravity(),								//�~�m�̏d��
	m_speed()									//�~�m�̗����X�s�[�h
{
	m_pos.x = 150;								//�����ʒu
	m_pos.y = 0;								//�����ʒu
	//m_pos.x = 250;
	//m_pos.y = 75;
	m_size.x = 30;								//�����T�C�Y
	m_size.y = 30;								//�����T�C�Y
	m_gravity = 15;								//�d��
	m_speed = 2.5f;								//�X�s�[�h
}

void SceneMain::Init()
{
	m_frametimer = kFrameTimer;					//�^�C�}�[��ݒ�
	for (int i = 0; i < kBlocHeight; i++)
	{
		for (int j = 0; j < kBlocWindht; j++)
		{
			field[j][i] = 0;
			//field[j][i] = empty;
		}
	}
	

	//for (int i = 0; i < kBlocHeight; i++)
	//{
	//	printfDx("\n");
	//	for (int j = 0; j < kBlocWindht; j++)
	//	{
	//		switch (field[j][i])
	//		{
	//		case 0:
	//			printfDx("%d",j);
	//			break;
	//		case 1:
	//			printfDx("8");
	//		default:
	//			break;
	//		}
	//	}
	//}
}


void SceneMain::MoveUpdate()
{
	if (Pad::isTrigger(PAD_INPUT_LEFT))				//���̈ړ������A�ړ�����
	{
		m_pos.x -= m_size.x;						//�L�[�������ꂽ�牟���ꂽ�����ɓ���
		if (m_pos.x < 0)
		{
			m_pos.x = 0;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_RIGHT))			//�E�̈ړ������A�ړ�����
	{
		m_pos.x += m_size.x;						//�L�[�������ꂽ�牟���ꂽ�����ɓ���
		//m_pos.x += m_size.x;						//�L�[�������ꂽ�牟���ꂽ�����ɓ���
		if (m_pos.x > 270)
		{
			m_pos.x = 270;
		}
	}

	if (m_pos.y > 600)								//field����o�Ȃ��悤�ɐݒ�
	{
		m_pos.y = 600;
	}
	if (Pad::isTrigger(PAD_INPUT_UP))				//��̈ړ�����
	{
		m_pos.y = kFieldFloor;								//�L�[�������ꂽ���u�ŉ��܂�
	}

	if (Pad::isPress(PAD_INPUT_DOWN))				//���̈ړ�����
	{
		m_pos.y += m_speed;							//�L�[�������ꂽ�牟���ꂽ�����ɓ���
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
	if (m_pos.y > kFieldFloor)								//field����o�Ȃ��悤�ɐݒ�
	{
		m_pos.y = kFieldFloor;
	}


	//////////
	//y = static_cast<int>(m_pos.y / m_size.y);
	//x = static_cast<int>(m_pos.x / m_size.x);
	
	
	y = m_pos.y / m_size.y;
	x = m_pos.x / m_size.x;
	
	if (m_pos.y == kFieldFloor)								//
	{
		field[19][1] = 1;
	}
}

SceneBase* SceneMain::Update()
{
	MoveUpdate();									//�~�m�̈ړ�����

	return this;
}
void SceneMain::Draw()
{
	//DrawBox(kFieldWindth, kFieldHeight + 30, 430, 705, GetColor(255, 255, 255), false);					//field�̘g
	//DrawBox(kFieldWindth, kFieldHeight, 430, 705, GetColor(255, 255, 255), false);					//field�̘g
	DrawBox(kFieldWindth, kFieldHeight, 300, 600, GetColor(255, 255, 255), false);					//field�̘g

	DrawBox(static_cast<int>(m_pos.x + 2), static_cast<int>(m_pos.y + 2),						//�~�m�̕\��
		static_cast<int>(m_pos.x + m_size.x - 2), static_cast<int>(m_pos.y + m_size.y - 2),
		GetColor(0, 255, 255), false);

	for (int i = 0; i < kBlocHeight; i++)
	{
		//DrawFormatString(kFieldWindth, kFieldHeight + (i * 30), GetColor(255, 255, 255), " %d", i);
		DrawFormatString(kFieldWindth, kFieldHeight + (i * 30), GetColor(255, 255, 255), " %d", i);
		for (int j = 0; j < kBlocWindht; j++)
		{
			DrawFormatString(kFieldWindth + (j * 30), kFieldHeight, GetColor(255, 255, 255), " %d", j);
		}
	}
	DrawFormatString(500, 0, GetColor(255, 255, 255), " %d", m_frametimer);
	DrawFormatString(600, 0, GetColor(255, 255, 255), " {x %d,y %d}", static_cast<int>(m_pos.x / 30), static_cast<int>(m_pos.y / 30));		//���W
	DrawFormatString(600, 75, GetColor(255, 255, 255), " {x %d,y %d}", static_cast<int>(x), static_cast<int>(y));		//���W
	DrawFormatString(600, 100, GetColor(255, 255, 255), " y %d", y);		//���W
	//DrawFormatString(600, 125, GetColor(255, 255, 255), " x %d", x);		//���W
	
	///////////////////////////////////////
	if (field[y][x] == 1)
	{
		DrawFormatString(600, 50, GetColor(255, 255, 255), " %d", 1);
	}
}