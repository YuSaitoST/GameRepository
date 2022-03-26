#pragma once

#include "_Classes/_CellList/_Object/ObjectBase.h"
#include "_Classes/_CellList/_Object/_Player/_MyLife/MyLife.h"

#include "_State/CharaState.h"
#include "_Strategy/CharaStrategy.h"
#include "_Strategy/_ManualChara/ManualChara.h"
#include "_Strategy/_ComputerChara/ComputerChara.h"

#include "_EffDown/EffDown.h"

#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"

class ObjPlayer final : public ObjectBase {
private:
	enum MOTION {
		STAND,
		STAND_TO_CATCH,
		HAND,
		HAND_TO_READY,
		READY,
		IS_SHOT
	};

public:
	ObjPlayer();
	ObjPlayer(OPERATE_TYPE strategy, Vector3 pos, float r);
	virtual ~ObjPlayer();

	virtual void Initialize(const int id);
	virtual void LoadAssets(std::wstring file_name);
	virtual void LoadAssets(DX9::MODEL& model) {}
	virtual void Update(const float deltaTime);
	virtual void Render();
	virtual void Render(DX9::MODEL& model) {}
	virtual void UIRender();

	virtual void HitAction(ObjectBase* hitObject);

	void Moving(Vector3 power) { physics_->Moving(power); };
	void Shoting(ObjBall* ball);
	void AssignPosition() { pos_ = physics_->GetCenterOfMassPosition(); }
	void AssignDirection(Vector2 dir) { forward_ = dir; }
	void SetTarget(ObjectBase* target) { targetObj_ = target; }

	int myLife() const { return life_->NowLifePoint(); }
	bool HasBall() const { return hasBall_; }
	Vector2 Get_HandPos();
	ObjBall* MyBall() const { return myBall_; }

private:
	void Playing(const float deltaTime);
	void Beaten(const float deltaTime);

	void SetTransforms(const Vector2 pos, const Vector2 rotate);
	void AnimReset();
	void AnimSet(MOTION motion, float deltaTime);
	MOTION AnimChange();

	//const SimpleMath::Vector2 POS_HAND = { -2.75f, -3.0f };
	const SimpleMath::Vector2 POS_HAND = { -2.75f, -3.0f };

	MyLife* life_;
	OriTimer* ti_respone_;
	EffDown* eff_down_;
	CharaStrategy* strategy_;
	ObjBall* myBall_;
	ObjectBase* targetObj_;
	DX9::SKINNEDMODEL model_;
	Vector2 handForward_;
	bool hasBall_;
	bool isDown_;
};