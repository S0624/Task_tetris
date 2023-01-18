#include"DxLib.h"
#include "ObjectMino.h"
#include"Scene/SceneMain.h"
#include"UI/Pad.h"
#include"game.h"

#include<cassert>

namespace
{
	SceneMain main;
	constexpr int kFieldHeight = 0;				//field�̑傫��
	constexpr int kFieldWindth = 0;				//field�̑傫��
	constexpr int kBlocHeight = 22;				//field�̍���
	constexpr int kBlocWindht = 12;				//field�̉���
	constexpr int kFieldFloor = 570;			//field�̉�
	constexpr int kFieldDisplace = 50;			//field�����炷

	constexpr int kFrameTimer = 50;				//�~�m����������C���^�[�o��
	constexpr int kMinoTimer = 5;				//�~�m���ݒu�����܂ł̎���

	int kField[kBlocWindht][kBlocHeight];		//field�̐ݒu

	int kCoordinateX = 0;						//���ݒn������W���擾����
	int kCoordinateY = 0;						//���ݒn������W���擾����

	bool kIsEnd = false;						//�Q�[���̏I���t���O
	constexpr int kSuspend = 10;				//�~�m��������ď�̃~�m�������Ă���܂ł̎���
	constexpr int kGeneration = 10;				//���̃~�m�̐����C���^-�o��

	float kPosX;
	float kPosY;
	bool kFlag = false;
	constexpr int kMinoblock = 4;

	//
	int minoBlock[kMinoblock][kMinoblock] = {
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
	};
	
	//I
	int Imino1[kMinoblock][kMinoblock] = {
	{0,0,2,0},
	{0,0,2,0},
	{0,0,2,0},
	{0,0,2,0}
	};
	int Imino2[kMinoblock][kMinoblock] = {
	{2,2,2,2},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
	};
	
	//O
	int Omino[kMinoblock][kMinoblock] = {
	{0,2,2,0},
	{0,2,2,0},
	{0,0,0,0},
	{0,0,0,0}
	};
	
	//T
	int Tmino1[kMinoblock][kMinoblock] = {
	{0,2,0,0},
	{2,2,2,0},
	{0,0,0,0},
	{0,0,0,0}
	};
	int Tmino2[kMinoblock][kMinoblock] = {
	{0,2,0,0},
	{2,2,0,0},
	{0,2,0,0},
	{0,0,0,0}
	};
	int Tmino3[kMinoblock][kMinoblock] = {
	{0,0,0,0},
	{0,0,0,0},
	{2,2,2,0},
	{0,2,0,0}
	};
	int Tmino4[kMinoblock][kMinoblock] = {
	{0,2,0,0},
	{0,2,2,0},
	{0,2,0,0},
	{0,0,0,0}
	};

	//S
	int Smino1[kMinoblock][kMinoblock] = {
	{0,2,2,0},
	{2,2,0,0},
	{0,0,0,0},
	{0,0,0,0}
	};
	
	//Z
	int Zmino1[kMinoblock][kMinoblock] = {
	{2,2,0,0},
	{0,2,2,0},
	{0,0,0,0},
	{0,0,0,0}
	};

	//J

	//L

	//
	int kPadflag = false;
	int kMinoRight = 0;
	int kMinoLeft = 0;
	int kMinoUp = 0;
	int kMinoDown = 0;
	int kRotation = 0;
}

ObjectMino::ObjectMino() :
	m_frametimer(),								//�t���[���^�C�}�[
	m_pos(),									//�~�m�̃|�W�V����
	m_size(),									//�~�m�̃T�C�Y
	m_gravity(),								//�~�m�̏d��
	m_speed(),									//�~�m�̗����X�s�[�h
	m_placed(false),							//�u���ꂽ���ǂ���
	m_minotimer(),								//�~�m�����܂ōs���Ēu�����܂ł̃C���^�[�o��
	m_suspend(),								//�~�m��������Ă��痎������܂ł̃^�C�}�[
	m_generation()								//���̃~�m�̐����C���^�[�o��
{
	MinoInit();
}

void ObjectMino::Init()
{
	m_frametimer = kFrameTimer;					//�^�C�}�[��ݒ�
	m_minotimer = kMinoTimer;					//�^�C�}�[��ݒ�
	m_generation = kGeneration;
	
}


void ObjectMino::MinoInit()
{
	m_pos.x = 154;								//�����ʒu
	m_pos.y = 25;								//�����ʒu
	m_size.x = 26;								//�����T�C�Y
	m_size.y = 26;								//�����T�C�Y
	m_gravity = m_size.y / 2;								//�d��
	m_speed = 2.5f;								//�X�s�[�h
	m_placed = false;


	for (int i = 0; i < kMinoblock; i++)		//field�̏�����
	{
		for (int j = 0; j < kMinoblock; j++)
		{
			minoBlock[j][i] = Omino[i][j];;
			//minoBlock[j][i] = Imino1[i][j];
			//minoBlock[j][i] = Zmino1[i][j];
		}
	}
}

void ObjectMino::MoveUpdate()
{
	//if (Pad::isTrigger(PAD_INPUT_1))				//��]
	//{
	//	kRotation += 1;
	//	kPadflag = true;
	//	for (int i = 0; i < 4; i++)		//field�̏�����
	//	{
	//		for (int j = 0; j < 4; j++)
	//		{
	//			if (kRotation == 0)
	//			{
	//				minoBlock[j][i] = Imino1[i][j];;
	//				//minoBlock[j][i] = Imino1[i][j];;
	//				//kRotation = 0;
	//			}
	//			if (kRotation == 1)
	//			{
	//				minoBlock[j][i] = Imino2[i][j];;
	//			}
	//			if (kRotation == 2)
	//			{
	//				//minoBlock[j][i] = Imino1[i][j];;
	//				kRotation = 0;
	//			}
	//		}
	//	}
	//}

	kCoordinateY = (m_pos.y - 26) / m_size.y;						//�~�m�̌��ݒn�����W�ɂ���
	kCoordinateX = (m_pos.x - kFieldDisplace) / m_size.x;			//�~�m�̌��ݒn�����W�ɂ���

	if (m_placed == true)								//	�~�m�̐ݒu����
	{
		if (m_minotimer > 0)
		{
			m_minotimer--;
			return;
		}
	}
	if (m_placed == false)
	{
		if (Pad::isTrigger(PAD_INPUT_LEFT))				//���̈ړ������A�ړ�����
		{
			if (kField[kCoordinateX + kMinoLeft - 1][kCoordinateY] == empty)
			//if (kField[kCoordinateX + kMinoLeft - 1][kCoordinateY] == empty)
			{
				m_pos.x -= m_size.x;						//�L�[�������ꂽ�牟���ꂽ�����ɓ���
			}
		}
		if (Pad::isTrigger(PAD_INPUT_RIGHT))			//�E�̈ړ������A�ړ�����
		{
			if (kField[kCoordinateX + kMinoRight + 1][kCoordinateY] == empty)
			{
				m_pos.x += m_size.x;
			}
		}
	}
	
	if (kField[kCoordinateX + kMinoRight][kCoordinateY + kMinoDown + 1] != empty ||
		kField[kCoordinateX + kMinoLeft][kCoordinateY + kMinoDown + 1] != empty)								//field������o�Ȃ��悤�ɐݒ�
	{
		m_placed = true;
		return;
	}
	if (Pad::isTrigger(PAD_INPUT_UP))				//��̈ړ�����
	{
		int checkdown = 0;
		for (int i = kCoordinateY; i < kBlocHeight; i++)
		{
			if (kField[kCoordinateX + kMinoLeft][i] != empty)
			{
				checkdown = i;
				break;
			}
		
		}
		for (int i = kCoordinateY; i < kBlocHeight; i++)
		{
			if (kField[kCoordinateX + kMinoRight][i] != empty)
			{
				if (checkdown > i)
				{
					checkdown = i;
				}
				break;
			}

		}
		m_pos.y = ((checkdown - kMinoDown) * 26);				//�u����ꏊ�̃`�F�b�N
	}
	if (Pad::isPress(PAD_INPUT_DOWN))				//���̈ړ�����
	{
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

void ObjectMino::MinoAcquisition()
{
	int left = kMinoblock;					//�����Ƃ邽�߂̕ϐ�
	int right = 0;							//�E���Ƃ邽�߂̕ϐ�
	int up = kMinoblock;					//����Ƃ邽�߂̕ϐ�
	int down = 0;							//�����Ƃ邽�߂̕ϐ�

	//�����Ƃ邽�߂̏���
	for (int i = 0; i < kMinoblock; i++)
	{
		for (int j = 0; j < kMinoblock; j++)
		{
			if (minoBlock[j][i] == 2)
			{
				if (left >= j)				//�������Ă��鐔����菬�������̂�����������������
				{
					left = j;
				}
			}
		}
	}
	//�E���Ƃ邽�߂̏���
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (minoBlock[j][i] == 2)
			{
				if (right <= j)
				{
					right = j;				//�������Ă��鐔�����傫�����̂�����������������
				}
			}
		}
	}
	//����Ƃ邽�߂̏���
	for (int i = 0; i < kMinoblock; i++)
	{
		for (int j = 0; j < kMinoblock; j++)
		{
			if (minoBlock[j][i] == 2)
			{
				if (up >= i)				//�������Ă��鐔����菬�������̂�����������������
				{
					up = i;
				}
			}
		}
	}
	//�����Ƃ邽�߂̏���
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (minoBlock[j][i] == 2)
			{
				if (down <= i)
				{
					down = i;				//�������Ă��鐔�����傫�����̂�����������������
				}
			}
		}
	}


	kMinoLeft = left;
	kMinoRight = right;
	kMinoUp = up;
	kMinoDown = down;

}

void ObjectMino::Update()
{
	MinoAcquisition();
	if (m_minotimer <= 0)
	{
		kFlag = true;
		main.MinoBlock(minoBlock);
		if (m_generation > 0)
		{
			m_generation--;
		}

		if (m_generation <= 0)
		{
			if (m_suspend > 0)
			{
				m_suspend--;
			}
			if (m_suspend <= 0)
			{
				kFlag = false;
				m_placed = false;								//�t���O�����Ƃɖ߂�
				//if (main.intervalFlag() == false)
				{
					//m_pos.x = 180 + m_posX;								//�����ʒu
					//m_pos.y = 25 + m_posY;								//�����ʒu
					MinoInit();
					kRotation = 0;
				}
				m_minotimer = kMinoTimer;
				m_generation = kGeneration;
			}
		}

		for (int j = 1; j < kBlocWindht - 2; j++)
		{
			if (kField[j][0] == input)
			{
				kIsEnd = true;
			}
		}
	}

	//for (int j = 1; j < kBlocWindht - 1; j++)
	//{
	//	if (field[j][0] != empty)
	//	{
	//		kIsEnd = true;								//�Q�[���I�[�o�[
	//	}
	//}

	if (kIsEnd == false)
	{
		MoveUpdate();									//�~�m�̈ړ�����
	}

	//bool disappear = false;
	//int height = 0;
	//for (int i = 1; i < kBlocHeight - 1; i++)
	//{
	//	if (kField[1][i] == input && kField[2][i] == input && kField[3][i] == input
	//		&& kField[4][i] == input && kField[5][i] == input && kField[6][i] == input
	//		&& kField[7][i] == input && kField[8][i] == input && kField[9][i] == input && kField[10][i] == input)
	//	{
	//		disappear = true;
	//		height = i;
	//	}
	//}
	//for (int j = 1; j < kBlocWindht - 1; j++)
	//{
	//	if (disappear == true)
	//	{
	//		kField[j][height] = empty;
	//		m_suspend = kSuspend;
	//	}
	//}
//
	//if (m_suspend == 1)
	//{
	//	for (int i = kBlocHeight - 2; i >= 1; i--)
	//	{
	//		for (int j = 1; j < kBlocWindht - 1; j++)
	//		{
	//			kField[j][i] = kField[j][i - 1];
	//		}
	//	}
	//}

	//return this;
}
void ObjectMino::Draw()
{
	//for (int i = 0; i < kBlocHeight; i++)
	//{
	//	for (int j = 0; j < kBlocWindht; j++)
	//	{
	//		switch (kField[j][i])
	//		{
	//		case empty:
	//			DrawString(kFieldDisplace + j + (j * 25), 25 + i + (i * 25), "�@", GetColor(255, 255, 255));
	//		default:
	//			break;
	//		case input:
	//			//DrawString(kFieldDisplace + j + (j * 25), 25 + i + (i * 25), "a", GetColor(255, 0, 0));
	//			break;
	//		case frame:
	//			DrawString(kFieldDisplace + j + (j * 25), 25 + i + (i * 25), "��", GetColor(255, 255, 255));
	//			break;
	//		}
	//	}
	//}

	for (int i = 0; i < kMinoblock; i++)
	{
		for (int j = 0; j < kMinoblock; j++)
		{
			if (minoBlock[j][i] == 2)
			{
				DrawString(m_pos.x + j + (j * 25), m_pos.y + i + (i * 25), "��", GetColor(255, 0, 0));
			}
		}
	}
	///////////////////////////////////////
	///        �m�F�p�̐��l�\��         ///
	///////////////////////////////////////

	if (kIsEnd == true)
	{
		DrawString(500, 0, "GameOver", GetColor(255, 0, 0));
	}
	else if (kIsEnd == false)
	{
		DrawString(500, 0, "GamePlay", GetColor(255, 0, 0));
	}
	
	if (kPadflag == false)
	{
		DrawString(500, 150, "������Ă��Ȃ�", GetColor(255, 0, 0));
	}
	else if (kPadflag == true)
	{
		DrawString(500, 150, "�����ꂽ", GetColor(255, 0, 0));
	}

	DrawFormatString(650, 280, GetColor(255, 0, 0), "��]%d", kRotation);
	//DrawFormatString(650, 350, GetColor(255, 0, 0), "R%d", kMinoRight);
	//DrawFormatString(650, 380, GetColor(255, 0, 0), "L%d", kMinoLeft);
	//DrawFormatString(650, 410, GetColor(255, 0, 0), "U%d", kMinoUp);
	//DrawFormatString(650, 440, GetColor(255, 0, 0), "D%d", kMinoDown);
	//DrawFormatString(650, 500, GetColor(255, 0, 0), "Y%d", kCoordinateY + kMinoDown);
	//DrawFormatString(650, 530, GetColor(255, 0, 0), "XL%d", kCoordinateX + kMinoLeft);
	//DrawFormatString(650, 560, GetColor(255, 0, 0), "XR%d", kCoordinateX + kMinoRight);
	
	//if (m_placed == false)
	//{
	//	DrawString(500, 100, "f", GetColor(255, 0, 0));
	//}
	//if (m_placed == true)
	//{
	//	DrawString(500, 150, "t", GetColor(255, 0, 0));
	//}
	//DrawFormatString(700, 0, GetColor(0, 255, 255), "%d", a);
	//DrawFormatString(600, 0, GetColor(255, 255, 255), "%d", kCount);
	//DrawFormatString(650, 0, GetColor(255, 255, 255), "%d", kTotal);
	//DrawFormatString(650, 0, GetColor(255, 255, 255), "%d", m_suspend);
	//DrawFormatString(650, 50, GetColor(255, 255, 255), "X:%f", kPosX);
	//DrawFormatString(650, 100, GetColor(255, 255, 255), "Y:%f", kPosY);
	//DrawFormatString(650, 150, GetColor(0, 20, 255), "0:%d", kField[1][20]);
}

int ObjectMino::Field(int field[12][22])
{
	//assert(false);

	for (int i = 0; i < kBlocHeight; i++)		//field�̏�����
	{
		for (int j = 0; j < kBlocWindht; j++)
		{
			kField[j][i] = field[j][i];;
		}
	}
	return 0;
}


int ObjectMino::PosX()
{
	int posx = 0;
	posx = kCoordinateX;
	return posx;
}

int ObjectMino::PosY()
{
	int posy = 0;
	posy = kCoordinateY;
	return posy;
}

bool ObjectMino::Flag()
{
	bool flag;
	flag = kFlag;

	return flag;
}

bool ObjectMino::EndFlag()
{
	bool gameflag;
	gameflag = kIsEnd;

	return gameflag;
}

void ObjectMino::MinoPos(int posX,int posY)
{
	m_posX = posX;
	m_posY = posY;
}

//void ObjectMino::MinoPos(float posX, float posY)
//{
//	kPosX = posX;
//	kPosY = posY;
//}
