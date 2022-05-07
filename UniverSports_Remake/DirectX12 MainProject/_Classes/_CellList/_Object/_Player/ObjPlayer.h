#pragma once

#include "_Classes/_CellList/_Object/ObjectBase.h"
#include "_Classes/_CellList/_Object/_Player/_MyLife/MyLife.h"
#include "_Classes/_CellList/_TeamID/TeamID.h"
#include "_State/CharaState.h"
#include "_Strategy/CharaStrategy.h"
#include "_Strategy/_ManualChara/ManualChara.h"
#include "_Strategy/_ComputerChara/ComputerChara.h"
#include "_Barrier/Barrier.h"

#include "_EffDown/EffDown.h"

#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"

#include"_Classes/FileNames.h"

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
	void AlphaRender();

	virtual void HitAction(ObjectBase* hitObject);

	void CreateModel(std::wstring fileName) {
		model_ = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, fileName.c_str());
		model_->SetScale(0.018f);
		model_->SetMaterial(GetNomMaterial());
	}

	void ReDecision(const int plID, std::wstring fileName) {
		CreateModel(fileName);
		pos_ = Vector2(GAME_CONST.S_POS[plID].x, GAME_CONST.S_POS[plID].y);
		rotate_ = Vector2(0.0f, GAME_CONST.Player_FacingRight);
		SetTransforms(pos_, rotate_);
	}

	void ChangeStrategy() {
		strategy_ = new ComputerChara();
		strategy_->Initialize(id_my_, this);
	}

	void AsjustmentForward();

	void Moving(Vector3 power) { physics_->Moving(power); };
	void Shoting(const int ballID);
	void CautchedBall(const int ballID);
	void AssignPosition() { pos_ = physics_->GetCenterOfMassPosition(); }
	void AssignDirection(Vector2 dir) { forward_ = dir; }
	void SetTarget(ObjectBase* target) { targetObj_ = target; }

	int myLife() const { return life_->NowLifePoint(); }
	bool HasBall() const { return hasBall_; }
	Vector2 Get_HandPos();
	int MyBallID() const { return myBallID_; }

private:
	void Playing(const float deltaTime);
	void Beaten(const float deltaTime);

	void SetTransforms(const Vector2 pos, const Vector2 rotate);
	void AnimReset();
	void AnimSet(MOTION motion, float deltaTime);
	MOTION AnimChange();

	const SimpleMath::Vector2 POS_HAND = { -2.75f, -3.0f };

	MyLife*				life_;
	TeamID*				teamID_;
	OriTimer*			ti_respone_;
	EffDown*			eff_down_;
	CharaStrategy*		strategy_;
	Barrier*			barrier_;
	ObjectBase*			targetObj_;
	DX9::SKINNEDMODEL	model_;
	Vector2				handForward_;
	bool				hasBall_;
	bool				isDown_;
	int					myBallID_;
};