#pragma once

#include "_Classes/_CellList/_Object/ObjectBase.h"
#include "_State/BallState.h"
#include "_State/_Float/StFloat.h"
#include "_State/_Cautch/StCautch.h"

class ObjBall final : public ObjectBase {
private:
	const D3DCOLORVALUE P_DIFFUSE[5] = {
		D3DCOLORVALUE(0.0f,0.65f,0.0f,1.0f),
		D3DCOLORVALUE(0.65f,0.0f,0.65f,1.0f),
		D3DCOLORVALUE(0.65f,0.0f,0.0f,1.0f),
		D3DCOLORVALUE(0.0f,0.0f,0.65f,1.0f),
		D3DCOLORVALUE(0.0f,0.0f,0.0f,0.0f)
	};
	const D3DCOLORVALUE P_AMBIENT = D3DCOLORVALUE(0.35f, 0.35f, 0.35f, 1.0f);

public:
	enum STATE {
		FLOAT,
		CAUTCH,
		SHOT,
		GOAL,
		NONE_STATE
	};
	enum COLOR_TYPE {
		NOMAL_COLOR,
		PLAYER_COLOR,
		TEAM_COLOR
	};

public:
	ObjBall();
	ObjBall(Vector3 pos, float r);
	virtual ~ObjBall();

	virtual void Initialize(const int id);
	virtual void LoadAssets(std::wstring file_name) {};
	virtual void LoadAssets(DX9::MODEL& model);
	virtual void Update(const float deltaTime);
	virtual void Render() {};
	virtual void Render(DX9::MODEL& model);
	virtual void UIRender() {};

	void SwitchState(STATE state);
	void SwitchColor(COLOR_TYPE colorType);
	void Moving(Vector3 power) { physics_->Moving(power); };
	void AddPower(Vector3 forward, float speed);
	void AssignPosition() {
		pos_ = physics_->GetCenterOfMassPosition();
	}
	void AssignTransform(Vector2 position, Vector2 forward) {
		pos_ = position;
		forward_ = forward;
	}
	void PhysicsControll(Vector2 position) {
		AssignTransform(position, Vector2::Zero);
		physics_->SetCenterOfMassTransform(Vector3(pos_.x, pos_.y, 0.0f), Vector3::Zero);
	}
	void ResetVelocity() {
		physics_->ResetVelocity();
	}
	void SetOwnerID(int id_player) { id_owner_ = id_player; };
	int GetOwnerID() const { return id_owner_; };
	bool IsInPlayerHands() const { return isInPlayerHands_; }

private:
	void SetTransforms();
	D3DMATERIAL9 ChangeMaterial(COLOR_TYPE colorType);

	BallState* state_;
	COLOR_TYPE colorType_;
	DX9::MODEL model_;
	float pos_z_;  // “Š‚°‚éÛ‚É“®‚©‚·(—\’èA‘½•ª‚»‚¤‚µ‚½•û‚ªŒ©‰h‚¦‚¢‚¢)
	int id_owner_;
	bool isInPlayerHands_;
};