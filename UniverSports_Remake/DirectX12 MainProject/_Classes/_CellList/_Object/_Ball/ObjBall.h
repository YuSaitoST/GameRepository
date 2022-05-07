#pragma once

#include "_Classes/_CellList/_Object/ObjectBase.h"
#include "_State/BallState.h"
#include "_State/_Float/StFloat.h"
#include "_State/_Cautch/StCautch.h"
#include "_State/_Shot/StShot.h"
#include "_State/_Standby/StStandby.h"
#include "_State/_Goal/StGoal.h"

class ObjBall final : public ObjectBase {
private:
	const D3DCOLORVALUE P_DIFFUSE[5] = {
		D3DCOLORVALUE(0.0f,0.65f,0.0f,1.0f),  // 緑(PL.1)
		D3DCOLORVALUE(0.65f,0.0f,0.65f,1.0f),  // 紫(PL.2)
		D3DCOLORVALUE(0.65f,0.0f,0.0f,1.0f),  // 赤(PL.3)
		D3DCOLORVALUE(0.0f,0.0f,0.65f,1.0f),  // 青(PL.4)
		D3DCOLORVALUE(0.0f,0.0f,0.0f,0.0f)
	};
	const D3DCOLORVALUE P_AMBIENT = D3DCOLORVALUE(0.35f, 0.35f, 0.35f, 1.0f);

public:
	enum COLOR_TYPE { DEFAULT_COLOR, PLAYERS_COLOR, TEAM_COLOR };

public:
	ObjBall();
	ObjBall(Vector3 pos, float r);
	virtual ~ObjBall();

	virtual void Initialize(const int id);
	virtual void LoadAssets(std::wstring file_name) {}
	virtual void LoadAssets(DX9::MODEL& model);
	virtual void Update(const float deltaTime);
	virtual void Render() {}
	virtual void Render(DX9::MODEL& model);
	virtual void UIRender() {}

	virtual void HitAction(ObjectBase* hitObject) {}

	void WasCaught(const int ownerID);  // HitInstructorクラスで呼ぶ、ビリヤードモードでは1つだけInitizalizeでこれ呼ぶ
	void WasThrown(Vector2 forward);
	void WasGuessed();
	void BallReset();

	void SwitchState(B_STATE state);
	void SwitchColor(COLOR_TYPE colorType);


	void Moving(Vector3 power) { physics_->Moving(power); }
	void AddPower(Vector3 forward, float speed);
	void AssignPosition() { pos_ = physics_->GetCenterOfMassPosition(); }
	void AssignTransform(Vector3 position, Vector2 forward) {
		pos_ = Vector2(position.x, position.y);
		pos_z_ = position.z;
		forward_ = forward;
	}
	void PhysicsControll(Vector3 position) {
		AssignTransform(position, Vector2::Zero);
		physics_->SetCenterOfMassTransform(Vector3(pos_.x, pos_.y, pos_z_), Vector3::Zero);
	}
	void ResetVelocity() { physics_->ResetVelocity(); }
	void SetOwnerID(int id_player) { id_owner_ = id_player; }
	void SetBallBreak(bool flag) { isBreak_ = flag; }
	void FlagResets() { isInPlayerHands_ = isBreak_ = false; }
	int GetOwnerID() const { return id_owner_; }
	float myPosZ() const { return pos_z_; }
	bool IsInPlayerHands() const { return isInPlayerHands_; }
	bool IsBreaked() const { return isBreak_; }
	B_STATE NowState() const { return state_->MyState(); }

	static float pos_z_smallest_;

private:
	void SetTransforms();
	D3DMATERIAL9 ChangeMaterial(COLOR_TYPE colorType);

	BallState* state_;
	StFloat st_float_;
	StCautch st_cautch_;
	StShot st_shot_;
	StStandby st_standby_;
	StGoal st_goal_;

	COLOR_TYPE colorType_;
	float pos_z_;
	int id_owner_;
	bool isInPlayerHands_;
	bool isBreak_;
};