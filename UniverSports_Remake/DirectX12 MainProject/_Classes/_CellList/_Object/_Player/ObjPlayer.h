#pragma once

#include "_Classes/_CellList/_Object/ObjectBase.h"

#include "_State/CharaState.h"
#include "_Strategy/CharaStrategy.h"
#include "_Strategy/_ManualChara/ManualChara.h"
#include "_Strategy/_ComputerChara/ComputerChara.h"

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
	virtual void LoadAssets(DX9::MODEL& model) {};
	virtual void Update(const float deltaTime);
	virtual void Render();
	virtual void Render(DX9::MODEL& model) {};
	virtual void UIRender();

	void Moving(Vector3 power) { physics_->Moving(power); };
	void AssignPosition() {
		pos_ = physics_->GetCenterOfMassPosition();
	}

	void AnimReset();
	void AnimSet(MOTION motion, float deltaTime);

private:
	void SetTransforms();

	CharaStrategy* strategy_;
	MOTION motion_;
	DX9::SKINNEDMODEL model_;
};