#pragma once

enum CHARA_STATE {
	PLAYING,
	BEATEN,
	CHARASTATE_NONE
};

class ObjPlayer;

class CharaState {
public:
	CharaState() {}
	virtual ~CharaState() {}

	virtual void Initialize(int id, ObjPlayer* player) = 0;
	virtual void LoadAssets() = 0;
	virtual void Update(const float deltaTime) = 0;

	virtual float GetRotateX() = 0;
};

/*
	[��邱��]
	�E�������Ƃ��ꂽ���ŏ�����؂�ւ���
	�E�G�t�F�N�g�́A���ꂼ���STATE���œǂݍ��ރf�[�^��ς���

	<Playing>    <Beaten>
	�X���X�^�[ : ���j
	���f��     :  -
	collision  :  -
	��{����   : �ҋ@�v���O�����Ɣ��j�G�t�F�N�g�Đ��̂�
	���G       :  -
*/