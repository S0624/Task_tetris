#pragma once
//#include "SceneBase.h"
#include"UI/Vec2.h"

class ObjectMino
{
public:
	typedef enum state {
		empty = 0,
		input = 1,
		frame = 9,
		move = 2
	};

public:
	ObjectMino();
	virtual ~ObjectMino() {}

	//������
	virtual void Init();
	//�I������
	virtual void End() {}

	//�~�m�̏���������
	virtual void MinoInit();
	//�~�m�̈ړ�����
	virtual void MoveUpdate();
	//�~�m���u���ꂽ���ǂ���
	virtual bool Placed() { return m_placed; }
	void MinoAcquisition();
	//�X�V����
	virtual void Update();
	//�`�揈��
	virtual void Draw();

	//field�̏��
	int Field(int field[12][22]);

	//�~�m��X���W
	int PosX();
	//�~�m��Y���W
	int PosY();
	//�u���ꂽ�t���O������
	bool Flag();
	//�Q�[���I�[�o�[�̃t���O
	bool EndFlag();

	virtual void MinoPos(int posX, int posY);


private:
	int m_frametimer;	//�t���[���^�C�}�[
	int m_minotimer;	//�~�m�̃^�C�}�[
	Vec2 m_pos;			//�~�m�̈ʒu
	Vec2 m_size;		//�~�m�̃T�C�Y
	int m_gravity;		//�~�m�̏d�͗���
	float m_speed;		//�����ꂽ���̃~�m�̃X�s�[�h	
	bool m_placed;		//�~�m���u���ꂽ���ǂ���
	int m_suspend;		//������Ă���~�m��������܂ł̃^�C�}�[
	int m_generation;
	int m_field[12][22];

	int m_posX;
	int m_posY;
};

