#include "ObjWire.h"
#include "DontDestroyOnLoad.h"

ObjWire::ObjWire() {
	cp_ = nullptr;
	SetMember(NONE_OBJ_ID, Vector3::Zero, 0.0f);

	rotate_ = Vector2::Zero;
}

ObjWire::ObjWire(Vector3 pos, float r) {
	cp_ = nullptr;
	SetMember(WIRE, pos, r);

	rotate_ = Vector2(0.0f, GAME_CONST.Player_FacingRight);
}

ObjWire::~ObjWire() {

}

void ObjWire::Initialize(const int id) {
	id_my_ = id;
}

void ObjWire::LoadAssets(std::wstring file_name) {
	DX9::MODEL mod;
	collision_->SetColli(mod->GetBoundingSphere());
	collision_->SetColliScale(1.2f);

	//SetTransforms();
}  // FILE_NAMEは空文字でいい,読み込みはしないから

void ObjWire::Update(const float deltaTime) {
	if (DontDestroy->GameMode_ != 3)  // ゴールを用いないモードならはじく
		return;

	UpdateToMorton();
}