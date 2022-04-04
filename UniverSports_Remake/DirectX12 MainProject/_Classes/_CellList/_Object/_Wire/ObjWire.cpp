#include "ObjWire.h"
#include "DontDestroyOnLoad.h"

ObjWire::ObjWire() {
	cp_ = nullptr;
	SetMember(NONE_OBJ_ID, NONE_COLLI_TYPE, Vector3::Zero, 0.0f);
}

ObjWire::ObjWire(Vector3 pos, float r) {
	cp_ = nullptr;
	SetMember(WIRE, ORIENTEDBOX, pos, r);
}

ObjWire::~ObjWire() {
	delete physics_;
}

void ObjWire::Initialize(const int id) {
	id_my_ = id;
	physics_ = new btObject(BOX, Vector3(pos_.x, pos_.y, 0.0f), SCALE, ROT_Z[id_my_ % 2], 0.0f);

	UpdateToMorton();
}

void ObjWire::LoadAssets(std::wstring file_name) {
	const Vector3 _rotate = XMFLOAT3(0.0f,0.0f, ROT_TUNING_Z[id_my_ % 2] * 1.5f);
	const Quaternion _qua = Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, _rotate.z);
	DX9::MODEL mod_wire_ = DX9::Model::CreateBox(DXTK->Device9, SCALE.x, SCALE.y, 1.0f);

	mod_wire_->SetRotation(_qua.x, _qua.y, _qua.z);
	collision_->SetColli(mod_wire_->GetBoundingOrientedBox());
	collision_->SetPosition(Vector3(pos_.x, pos_.y, 0.0f));

}  // FILE_NAME‚Í‹ó•¶Žš‚Å‚¢‚¢,“Ç‚Ýž‚Ý‚Í‚µ‚È‚¢‚©‚ç