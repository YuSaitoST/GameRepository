#include "ObjWire.h"
#include "_Strategy/_Wires/Wires.h"
#include "_Strategy/_Goals/Goals.h"
#include "_Classes/_CellList/_BallsInstructor/BallsInstructor.h"
#include "_Classes/_CellList/_Object/_Ball/_State/_Goal/StGoal.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"
#include "_Classes/_FileNames/FileNames.h"
#include "DontDestroyOnLoad.h"

ObjWire::ObjWire() {
	cp_ = nullptr;
	SetMember(NONE_OBJ_ID, NONE_COLLI_TYPE, Vector3::Zero, 0.0f);

	physics_ = nullptr;
	strategy_ = nullptr;
	se_goal_ = nullptr;
}

ObjWire::ObjWire(Vector3 pos, float r) {
	cp_ = nullptr;
	SetMember(WIRE, ORIENTEDBOX, pos, r);

	if (DontDestroy->GameMode_.isHANDBALL())
		strategy_ = std::make_unique<Goals>();
	else
		strategy_ = std::make_unique<Wires>();

	se_goal_ = std::make_unique<SoundPlayer>();
}

void ObjWire::Initialize(const int id) {
	id_my_ = id;
	physics_ = std::make_unique<btObject>(XMFLOAT3(pos_.x, pos_.y, 0.0f), XMFLOAT3(WIRE_PARAM.SCALE.x, WIRE_PARAM.SCALE.y, 1.0f), WIRE_PARAM.BULLET_ROT_Z[id_my_], 0.0f);
	se_goal_->Initialize(USFN_SOUND::SE::GOAL, SOUND_TYPE::SE, 0.0f);

	UpdateToMorton();
}

void ObjWire::LoadAssets(std::wstring file_name) {
	const Quaternion _qua = Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, WIRE_PARAM.MOD_ROT_Z[id_my_]);
	DX9::MODEL mod_wire_ = DX9::Model::CreateBox(DXTK->Device9, WIRE_PARAM.SCALE.x, WIRE_PARAM.SCALE.y * WIRE_PARAM.COLLIDER_SCALE_Y_CORRECTIONVALUE, 1.0f);

	mod_wire_->SetRotation(_qua.x, _qua.y, _qua.z);
	collision_->SetColli(mod_wire_->GetBoundingOrientedBox());
	collision_->SetPosition(XMFLOAT3(pos_.x, pos_.y, 0.0f));
}

void ObjWire::Update(const float deltaTime) {
	strategy_->Update(this);
}

void ObjWire::HitAction(ObjectBase* object) {
	// 衝突したものがないなら早期リターン
	if (object == nullptr)
		return;

	if (object->myObjectType() == OBJ_TYPE::PLAYER) {
		// ゴール内にボールが入っていなければ早期リターン
		if (hasBallsID_.size() <= 0)
			return;

		ObjPlayer* player = dynamic_cast<ObjPlayer*>(object);

		// 自分の陣地ではないのなら早期リターン
		if (player->myObjectID() != id_my_)
			return;

		// ボールを持っているなら早期リターン
		if (player->HasBall())
			return;

		const int ballID = hasBallsID_.back();
		player->CautchedBall(hasBallsID_.back());
		ObjBall* ball = ballsInstructor_->Access(ballID);
		ball->WasCaught(id_my_, player->GetHandPos());
		ball->SwitchColor(ObjBall::COLOR_TYPE::PLAYERS_COLOR);
		hasBallsID_.pop_back();
	}
	else if (object->myObjectType() == OBJ_TYPE::BALL) {
		ObjBall* ball = dynamic_cast<ObjBall*>(object);

		// 投げられたボールでなければ早期リターン
		if (ball->NowState() != B_STATE::SHOT)
			return;

		// 自分のゴールにボールが入らないように早期リターン
		if (ball->GetOwnerID() == id_my_)
			return;

		se_goal_->PlayOneShot();
		hasBallsID_.push_back(ball->myObjectID());
		std::unique_ptr<StGoal> goal = std::make_unique<StGoal>();
		ball->SwitchState(goal.release());
		ball->WasGoaled();
	}
}