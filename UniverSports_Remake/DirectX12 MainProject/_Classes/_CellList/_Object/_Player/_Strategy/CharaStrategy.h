#pragma once

#include "Base/pch.h"
#include "_Classes/_CellList/_Object/_Player/_BehaviorTree/_ActMove/ActMove.h"
#include "_Classes/_CellList/_Object/_Player/_BehaviorTree/_ActThrasher/ActThrasher.h"

using namespace DirectX;

enum OPERATE_TYPE {
	MANUAL,
	COMPUTER,
	NONE_OPERATE_TYPE
};

class ObjPlayer;

class CharaStrategy {
public:
	CharaStrategy() : rotate_x_(0.0f) { actList_ = { new ActMove(), new ActThrasher() }; };
	virtual ~CharaStrategy() {};

	virtual void Initialize(int id, ObjPlayer* player) = 0;
	virtual void LoadAssets() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void UIRender() {
		for (ActionBase* act : actList_)
			act->UIRender();
	}

	virtual void SeekRotate(const float deltaTime, int index) = 0;

	inline float GetRotateX() const { return rotate_x_; };
	inline SimpleMath::Vector2 GetForward() const { return SimpleMath::Vector2(prevForward_.x, prevForward_.y); };

protected:
	ObjPlayer* player_;
	std::vector<ActionBase*> actList_;
	SimpleMath::Vector3 direction_;
	SimpleMath::Vector3 prevForward_;
	float rotate_x_;
};