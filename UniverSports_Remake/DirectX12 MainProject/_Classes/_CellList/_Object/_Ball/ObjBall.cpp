#include "ObjBall.h"
#include "_State/_Standby/StStandby.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"
#include "_Classes/_Field/Field.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "DontDestroyOnLoad.h"

ObjBall::ObjBall() {
	cp_ = nullptr;
	pos_ = Vector2::Zero;
	SetMember(NONE_OBJ_ID, NONE_COLLI_TYPE, Vector3::Zero, 0.0f);

	ownerHandPos_ = nullptr;
	physics_ = nullptr;
	colorType_ = DEFAULT_COLOR;
	pos_z_ = 0.0f;
	id_owner_ = -1;
	isInPlayerHands_ = false;
	isBreak_ = false;
}

ObjBall::ObjBall(Vector3 pos, float r) {
	cp_ = nullptr;
	pos_ = Vector2::Zero;
	SetMember(BALL, COLLI_TYPE::SPHRER, pos, r);

	std::unique_ptr<StStandby> standby = std::make_unique<StStandby>();
	SwitchState(standby.release());

	physics_ = std::make_unique<btObject>(pos, BALL_PARAM.OBJ_SCALE, 0.0f, 1.0f);
	colorType_ = DEFAULT_COLOR;
	pos_z_ = 0.0f;
	id_owner_ = -1;
	ownerHandPos_ = nullptr;
	isInPlayerHands_ = false;
	isBreak_ = false;
}

ObjBall::~ObjBall() {
	if (ownerHandPos_ != nullptr) {
		delete ownerHandPos_;
		ownerHandPos_ = nullptr;
	}

	if (state_ != nullptr) {
		delete state_;
		state_ = nullptr;
	}
}

void ObjBall::Initialize(const int id) {
	physics_->SetActivationState(DISABLE_DEACTIVATION);

	id_my_ = id;

	pos_z_ = 0.0f;
	id_owner_ = -1;
	isInPlayerHands_ = false;
	isBreak_ = false;
}

void ObjBall::LoadAssets(DX9::MODEL& model) {
	collision_->SetColli(model->GetBoundingSphere());
	collision_->SetColliScale(BALL_PARAM.COL_SCALE);
	
	r_ = model->GetBoundingSphere().Radius;
}

void ObjBall::Update(const float deltaTime) {
	state_->Update(this);

	pos_ = physics_->GetCenterOfMassPosition();
	SetTransform(XMFLOAT3(pos_.x, pos_.y, pos_z_), rotate_);

	UpdateToMorton();
}

void ObjBall::Render(DX9::MODEL& model) {
	model->SetPosition(XMFLOAT3(pos_.x, pos_.y, pos_z_));
	model->SetRotation(XMFLOAT3(rotate_.x, rotate_.y, 0.0f));
	model->SetMaterial(ChangeMaterial(colorType_));
	model->Draw();
}

/**
* @brief 状態変更
* @param state 状態
*/
void ObjBall::SwitchState(BallState* state) {
	state_ = state;
	state_->Initialize();
}

/**
* @brief 状態に応じたマテリアルを返す
* @param colorType 色の形式
* @return マテリアル
*/
D3DMATERIAL9 ObjBall::ChangeMaterial(COLOR_TYPE colorType) {
	D3DMATERIAL9 _mat{};
	switch (colorType) {
		case DEFAULT_COLOR	:	_mat = GetNomMaterial();
								break;
		case PLAYERS_COLOR	:	_mat.Diffuse = USMaterial::P_DIFFUSE[DontDestroy->ChoseColor_[id_owner_]];
								_mat.Ambient = USMaterial::P_AMBIENT;
								break;
		case TEAM_COLOR		:	break;
	}
	return _mat;
}

/**
* @brief 追尾処理
*/
void ObjBall::Following(float pos_z) {
	pos_ = *ownerHandPos_;
	SetPhysicsPosition(XMFLOAT3(pos_.x, pos_.y, pos_z));
}

/**
* @brief キャッチされた際の処理
* @param ownerID 持ち主のID
*/
void ObjBall::WasCaught(const int ownerID, XMFLOAT2* handPos) {
	id_owner_ = ownerID;
	ownerHandPos_ = handPos;
	isInPlayerHands_ = true;
	pos_z_ = -6.0f;
	ResetVelocity();
	AssignTransform(XMFLOAT3(pos_.x, pos_.y, pos_z_), forward_);
}

/**
* @brief 投げられた際の処理
* @param forward 正面ベクトル
*/
void ObjBall::WasThrown(Vector2 forward) {
	forward_ = forward;
	isInPlayerHands_ = false;
	AddPower(XMFLOAT3(pos_.x,pos_.y,pos_z_), XMFLOAT3(forward_.x, forward_.y, 0.0f), BALL_PARAM.SPEED_SHOT);
}

/**
* @brief ゴールした際の処理
*/
void ObjBall::WasGoaled() {
	pos_z_ = POS_Z_AT_GOAL;
	id_owner_ = -1;
	isInPlayerHands_ = false;
	SwitchColor(COLOR_TYPE::DEFAULT_COLOR);
	FlagResets();
	ResetVelocity();
}

/**
* @brief 相手プレイヤーに衝突した際のリセット処理
*/
void ObjBall::WasGuessed() {
	DontDestroy->Score_[id_owner_] += 1;
	BallBreak();
}

/**
* @brief 場外に出た際のリセット処理
*/
void ObjBall::BallBreak() {
	pos_z_				= 0.0f;
	id_owner_			= -1;
	isBreak_			= true;
	isInPlayerHands_	= false;
	ownerHandPos_		= nullptr;
	AssignTransform(Vector3(FIELD::HALF_X, FIELD::HALF_Y, 0.0f), Vector2::Zero);
}