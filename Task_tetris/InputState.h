#pragma once

enum class InputType {
	next,		//���֍s���{�^��
	back,		//�O�ɖ߂�{�^��
	pause		//�|�[�Y�{�^��
};

class InputState
{
private:
	int keypadState;		//�L�[�p�b�h���
	int lastKeypadState;	//���O�̃L�[�p�b�h���
	char keystate[256];		//�L�[�{�[�h���
	char lastKeystate[256];	//���O�̃L�[�{�[�h���

public:
	bool IsTrigger(InputType type)const;		//�������u�Ԃ�true��Ԃ�
	bool IsPressed(InputType type)const;		//�����ꑱ������true��Ԃ�
	void Update();			//�X�V����
};

