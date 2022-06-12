/**
 * @file ObjWire.h
 * @brief ���C���[�N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/ObjectBase.h"
#include "_Strategy/WireStrategy.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"

// �O���錾
class BallsInstructor;
class PlayersInstructor;

class ObjWire final : public ObjectBase {
public:
	ObjWire();
	ObjWire(Vector3 pos, float r);
	virtual ~ObjWire() {}

	virtual void Initialize(const int id);
	virtual void LoadAssets(std::wstring file_name);
	virtual void Update(const float deltaTime);

	virtual void HitAction(ObjectBase* hitObject);

	// ��̎���
	virtual void LoadAssets(DX9::MODEL& model) {}
	virtual void Render() {}
	virtual void Render(DX9::MODEL& model) {}
	virtual void UIRender() {}

	/**
	* @brief �C���X�g���N�^�[�̐ݒ�
	* @param blInstructor �{�[���C���X�g���N�^�[
	* @param plInstructor �v���C���[�C���X�g���N�^�[
	*/
	void SetInstructor(BallsInstructor* blInstructor, PlayersInstructor* plInstructor) { ballsInstructor_ = blInstructor; playersInstructor_ = plInstructor; }

private:
	std::vector<int>				hasBallsID_;	//! �S�[�����̃{�[�����X�g
	std::unique_ptr<WireStrategy>	strategy_;		//! ���C���[�̐U�镑��
	std::unique_ptr<SoundPlayer>	se_goal_;		//! �S�[������SE

	BallsInstructor*	ballsInstructor_;	//! �{�[���C���X�g���N�^�[
	PlayersInstructor*	playersInstructor_;	//! �v���C���[�C���X�g���N�^�[
};