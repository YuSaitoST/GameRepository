#include "ObjBall.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"
#include "_Classes/_Field/Field.h"
#include "DontDestroyOnLoad.h"

ObjBall::ObjBall() {
	cp_ = nullptr;
	pos_ = Vector2::Zero;
	SetMember(NONE_OBJ_ID, NONE_COLLI_TYPE, Vector3::Zero, 0.0f);

	SwitchState(B_STATE::STANDBY);
	//state_ = &st_standby_;

	physics_ = new btObject(NONE_BULLET_TYPE, Vector3::Zero, Vector3::Zero, 0.0f, 0.0f);
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

	SwitchState(B_STATE::STANDBY);
	//state_ = &st_standby_;

	physics_ = new btObject(BULLET_TYPE::BT_SPHRER, pos, Vector3::Zero, 0.0f, 1.0f);
	colorType_ = DEFAULT_COLOR;
	pos_z_ = 0.0f;
	id_owner_ = -1;
	isInPlayerHands_ = false;
	isBreak_ = false;

}

ObjBall::~ObjBall() {
	delete physics_;
	if (state_ != nullptr) {
		delete state_;
		state_ = nullptr;
	}
}

void ObjBall::Initialize(const int id) {
	physics_->SetActivationState(DISABLE_DEACTIVATION);

	pos_		= state_->GetPosition();
	forward_	= state_->GetForward();

	state_->Initialize();

	id_my_		= id;

	pos_z_ = 0.0f;
	id_owner_ = -1;
	isInPlayerHands_ = false;
	isBreak_ = false;
}

void ObjBall::LoadAssets(DX9::MODEL& model) {
	collision_->SetColli(model->GetBoundingSphere());

	AddPower(Vector3(forward_.x, forward_.y, 0.0f), GAME_CONST.BA_SPEED_FLOAT);
	
	//pos_ = physics_->GetCenterOfMassPosition();
	//SetTransform(XMFLOAT3(pos_.x, pos_.y, pos_z_), rotate_);

	r_ = model->GetBoundingSphere().Radius;

	//UpdateToMorton();
}

void ObjBall::Update(const float deltaTime) {
	state_->Update(this);

	pos_ = physics_->GetCenterOfMassPosition();

	SetTransform(XMFLOAT3(pos_.x, pos_.y, pos_z_), rotate_);

	UpdateToMorton();
}

void ObjBall::Render(DX9::MODEL& model) {
	model->SetPosition(Vector3(pos_.x, pos_.y, pos_z_));
	model->SetRotation(Vector3(rotate_.x, rotate_.y, 0.0f));
	model->SetMaterial(ChangeMaterial(colorType_));
	model->Draw();
}

/**
* @brief 状態の変化
* @param state 状態
*/
void ObjBall::SwitchState(B_STATE state) {
	switch (state) {
		case B_STATE::STANDBY	:state_ = &st_standby_; break;
		case B_STATE::FLOATING	:state_ = &st_float_;	break;
		case B_STATE::CAUTCH	:state_ = &st_cautch_;	break;
		case B_STATE::SHOT		:state_ = &st_shot_;	break;
		case B_STATE::GOAL		:state_ = &st_goal_;	break;
		default					:assert(!"ObjBall::SwitchState : 不正な状態です");
	}

	state_->Initialize();
	UpdateToMorton();
}

/**
* @brief 色の変更
* @param colorType 色のタイプ
*/
void ObjBall::SwitchColor(COLOR_TYPE colorType) {
	colorType_ = colorType;
}

/**
* @brief 色の変更
* @param colorType 色のタイプ
* @return マテリアル
*/
D3DMATERIAL9 ObjBall::ChangeMaterial(COLOR_TYPE colorType) {
	D3DMATERIAL9 _mat{};

	switch (colorType) {
		case DEFAULT_COLOR : _mat = GetNomMaterial(); break;
		case PLAYERS_COLOR : _mat.Diffuse = P_DIFFUSE[std::min(std::max(0, DontDestroy->ChoseColor_[id_owner_]), 4 - 1)]; _mat.Ambient = P_AMBIENT; break;
		case TEAM_COLOR    : break;
		default			   : assert(!"ObjBall_assert : 不正な色指定"); break;
	}

	return _mat;
}

/**
* @brief 力を加え飛ばす処理
* @param forwrad 正面ベクトル
* @param speed 速度
*/
void ObjBall::AddPower(Vector3 forward, float speed) {
	physics_->SetLinerVelocity(forward * speed);
	physics_->SetCenterOfMassTransform(Vector3(pos_.x, pos_.y, pos_z_), Vector3::Zero);

	pos_ = physics_->GetCenterOfMassPosition();
	SetTransform(XMFLOAT3(pos_.x, pos_.y, pos_z_), rotate_);
}

/**
* @brief キャッチされた時の処理
* @param ownerID 持ち主のID
*/
void ObjBall::WasCaught(const int ownerID) {
	id_owner_ = ownerID;
	isInPlayerHands_ = true;
	pos_z_ = -3.0f;
	ResetVelocity();
	AssignTransform(Vector3(pos_.x, pos_.y, pos_z_), forward_);
}

/**
* @brief 投げられた時の処理
* @param forward 正面ベクトル
*/
void ObjBall::WasThrown(Vector2 forward) {
	forward_ = forward;
	isInPlayerHands_ = false;
	AddPower(Vector3(forward_.x, forward_.y, 0.0f), GAME_CONST.BA_SPEED_SHOT);
}

void ObjBall::WasGoaled() {
	pos_z_ = 3.0f;
	id_owner_ = -1;
	SwitchColor(COLOR_TYPE::DEFAULT_COLOR);
	FlagResets();
	ResetVelocity();
}

/**
* @brief プレイヤーとの衝突による破壊時の処理
*/
void ObjBall::WasGuessed() {
	DontDestroy->Score_[id_owner_] += 1;
	BallBreak();
}

/**
* @brief 破壊時の処理
*/
void ObjBall::BallBreak() {
	pos_z_ = 0.0f;
	id_owner_ = -1;
	isBreak_ = true;
	isInPlayerHands_ = false;
	AssignTransform(Vector3(FIELD::SIDE_X, FIELD::SIDE_Y, 0.0f), Vector2::Zero);
}