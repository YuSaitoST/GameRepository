/**
 * @file ActThrasher.h
 * @brief �����s���N���X
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
#include "_EffThrasher/EffThrasher.h"
#include "_Gauge/Gauge.h"

using namespace DirectX;

//�O���錾
class ObjPlayer;

class ActThrasher : public ActionBase {
public:
	ActThrasher();
	virtual ~ActThrasher();

	virtual void Initialize(int id);
	virtual void LoadAssets();
	virtual void Update(const float deltaTime, SimpleMath::Vector2 direction, ObjPlayer& player);
	virtual void Update(const float deltaTime, ObjPlayer& player);
	virtual void UIRender();

	virtual bool Think(ObjPlayer& player);

private:
	//! �X���X�^�[�G�t�F�N�g
	EffThrasher* effect_;

	//! �X���X�^�[�Q�[�W
	Gauge* gauge_;
};