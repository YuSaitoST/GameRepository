#include "ObjWire.h"
#include "DontDestroyOnLoad.h"

ObjWire::ObjWire() {
	cp_ = nullptr;
	SetMember(NONE, Vector3::Zero, 0.0f);

	rotate_ = Vector2::Zero;
}

ObjWire::ObjWire(Vector3 pos, float r) {
	cp_ = nullptr;
	SetMember(WIRE, pos, r);

	rotate_ = Vector2(0.0f, GAME_CONST.Player_FacingRight);
}

ObjWire::~ObjWire() {

}

void ObjWire::Initialize(int id) {
	id_my_ = id;
}

void ObjWire::LoadAssets(std::wstring file_name) {
	DX9::MODEL mod;
	collision_->SetColli(mod->GetBoundingSphere());
	collision_->SetColliScale(1.2f);

	if (DontDestroy->GameMode_ == 0)
		sprite_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Main\\_Wire\\honeycomb_wire02.png"));
	else
		for (int _i = 0; _i < 4; ++_i)
			sprite_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, FILENAME_WIRE[DontDestroy->ChoseColor_[_i]][_i].c_str()));

	//SetTransforms();
}  // FILE_NAMEは空文字でいい,読み込みはしないから

void ObjWire::Update(const float deltaTime) {
	if (DontDestroy->GameMode_ != 3)
		return;

	ObjectBase::Update();
}  // ゴールを用いるモードで判定をするため

void ObjWire::UIRender() {
	for (DX9::SPRITE sp : sprite_)
		DX9::SpriteBatch->DrawSimple(sp.Get(), SimpleMath::Vector3(0.0f, 0.0f, -981.0f));
}