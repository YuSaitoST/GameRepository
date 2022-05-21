/**
 * @file ActMove.h
 * @brief �ړ��s���N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_CellList\_Object/_Player/_BehaviorTree/ActionBase.h"

using namespace DirectX::SimpleMath;

class ObjPlayer;

class ActMove : public ActionBase {
public:
	ActMove() {}
	virtual ~ActMove() {}

	virtual void Initialize(int id) {}
	virtual void LoadAssets() {}
	virtual void Update(const float deltaTime, Vector2 direction, ObjPlayer& player);
	virtual void Update(const float deltaTime, ObjPlayer& player);
	virtual void UIRender() {}

	virtual bool Think(ObjPlayer& player);

private:
	Vector2 GetVerticalDirection(Vector2 targetsDirection);
	void SeekEscapeDirection(Vector2 targetsDirection);
	void SeekForwardDirection(Vector2 myPosition, Vector2 targetPosition);
};