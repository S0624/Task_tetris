#pragma once
#include "SceneBase.h"

class SceneMain : public SceneBase		//�p�����ăN���X���쐬
{
public:
	SceneMain();
	virtual ~SceneMain() {}

	//������
	virtual void Init()override;
	//�I������
	virtual void End()override {}

	//�X�V����
	virtual SceneBase* Update()override;
	//�`�揈��
	virtual void Draw() override;

private:
	
};

