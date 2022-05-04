#pragma once

#include "_Classes/_CellList/_Object/ObjectBase.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"

class ObjWire final : public ObjectBase {
public:
	ObjWire();
	ObjWire(Vector3 pos, float r);
	virtual ~ObjWire();

	virtual void Initialize(const int id);  // IDはゴールのIDとして利用
	virtual void LoadAssets(std::wstring file_name);
	virtual void Update(const float deltaTime);

	virtual void HitAction(ObjectBase* hitObject);

	// 空の実装
	virtual void LoadAssets(DX9::MODEL& model) {}  // モデルは使わない
	virtual void Render() {}  // モデルの描画はない
	virtual void Render(DX9::MODEL& model) {}
	virtual void UIRender() {}

private:
	const SimpleMath::Vector3 SCALE = SimpleMath::Vector3(13.75f, 2.25f + 0.1f, 0.0f);
	const float ROT_TUNING_Z[2] = { 1.1f, -1.1f };
	const float ROT_Z[2] = { 0.415f, -0.415f };

	std::vector<ObjBall*> hasBalls_;
};