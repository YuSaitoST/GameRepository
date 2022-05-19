#include "ObjWire.h"
#include "_Classes/_CellList/_BallsInstructor/BallsInstructor.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "_Strategy/_Wires/Wires.h"
#include "_Strategy/_Goals/Goals.h"
#include "DontDestroyOnLoad.h"

ObjWire::ObjWire() {
	cp_ = nullptr;
	SetMember(NONE_OBJ_ID, NONE_COLLI_TYPE, Vector3::Zero, 0.0f);
}

ObjWire::ObjWire(Vector3 pos, float r) {
	cp_ = nullptr;
	SetMember(WIRE, ORIENTEDBOX, pos, r);

	if (DontDestroy->GameMode_.isDODGEBALL_NOMAL())
		strategy_ = new Wires();
	else
		strategy_ = new Goals();

	se_goal_ = new SoundPlayer();
}

ObjWire::~ObjWire() {
	delete physics_;
}

void ObjWire::Initialize(const int id) {
	id_my_ = id;
	physics_ = new btObject(BOX, Vector3(pos_.x, pos_.y, 0.0f), SCALE, ROT_Z[id_my_ % 2], 0.0f);
	se_goal_->Initialize(L"_Sounds\\_SE\\_Main\\se_goal.wav", SOUND_TYPE::SE, 0.0f);

	UpdateToMorton();
}

void ObjWire::LoadAssets(std::wstring file_name) {
	const Vector3 _rotate = XMFLOAT3(0.0f,0.0f, ROT_TUNING_Z[id_my_ % 2] * 1.5f);
	const Quaternion _qua = Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, _rotate.z);
	DX9::MODEL mod_wire_ = DX9::Model::CreateBox(DXTK->Device9, SCALE.x, SCALE.y, 1.0f);

	mod_wire_->SetRotation(_qua.x, _qua.y, _qua.z);
	collision_->SetColli(mod_wire_->GetBoundingOrientedBox());
	collision_->SetPosition(Vector3(pos_.x, pos_.y, 0.0f));
}

void ObjWire::Update(const float deltaTime) {
	strategy_->Update(this);
}

void ObjWire::HitAction(ObjectBase* object) {
	// 衝突したものがないなら早期リターン
	if (object == nullptr)
		return;

	if (object->myObjectType() == OBJ_TYPE::PLAYER) {
		ObjPlayer* player = dynamic_cast<ObjPlayer*>(object);

		// 自分の陣地ではないのなら早期リターン
		if (player->myObjectID() != id_my_)
			return;

		// ゴール内にボールが入っていなければ早期リターン
		if (hasBalls_.size() <= 0)
			return;

		// ボールを持っているなら早期リターン
		if (player->HasBall())
			return;

		player->CautchedBall(hasBalls_.back()->myObjectID());
		BallsInstructor::BallCautch(player->myObjectID(), hasBalls_.back()->myObjectID());
		hasBalls_.pop_back();

	}
	else if (object->myObjectType() == OBJ_TYPE::BALL) {
		ObjBall* ball = dynamic_cast<ObjBall*>(object);

		// 投げられたボールでなければ早期リターン
		if (ball->NowState() != B_STATE::SHOT)
			return;

		ball->SwitchState(B_STATE::GOAL);
		hasBalls_.push_back(ball);
		se_goal_->PlayOneShot();
	}
}