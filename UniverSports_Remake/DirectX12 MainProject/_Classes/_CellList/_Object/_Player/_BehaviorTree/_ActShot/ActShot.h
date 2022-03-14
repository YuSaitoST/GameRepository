#pragma once

#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_Classes/_CellList/_Object/_Player/_BehaviorTree/ActionBase.h"

class ActShot final : public ActionBase {
public:
	ActShot() : isShot_(false) {}
	virtual ~ActShot() {}

	virtual void Initialize(int id) {}
	virtual void LoadAssets() {}
	virtual void Update(const float deltaTime, SimpleMath::Vector2 direction, ObjPlayer& player);
	virtual void Update(const float deltaTime, ObjPlayer& player);
	virtual void UIRender() {}

	virtual bool Think(ObjPlayer& player);

private:
	bool isShot_;
};