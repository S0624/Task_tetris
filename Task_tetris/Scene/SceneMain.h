#pragma once
#include "SceneBase.h"
#include"UI/Vec2.h"
class SceneMain : public SceneBase		//�p�����ăN���X���쐬
{
//public:
//	typedef enum state {
//		empty = 0,
//		input = 1
//	};

public:
	SceneMain();
	virtual ~SceneMain() {}

	//������
	virtual void Init()override;
	//�I������
	virtual void End()override {}

	//�~�m�̈ړ�����
	virtual void MoveUpdate();
	//�X�V����
	virtual SceneBase* Update()override;
	//�`�揈��
	virtual void Draw() override;

private:
	int m_frametimer;	//�t���[���^�C�}�[
	Vec2 m_pos;			//�~�m�̈ʒu
	Vec2 m_size;		//�~�m�̃T�C�Y
	int m_gravity;		//�~�m�̏d�͗���
	float m_speed;		//�����ꂽ���̃~�m�̃X�s�[�h	
};

