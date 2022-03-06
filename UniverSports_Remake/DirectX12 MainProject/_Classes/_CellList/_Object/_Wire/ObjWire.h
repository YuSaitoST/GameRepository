#pragma once

#include "_Classes/_CellList/_Object/ObjectBase.h"

class ObjWire final : public ObjectBase {
public:
	ObjWire();
	ObjWire(Vector3 pos, float r);
	virtual ~ObjWire();

	virtual void Initialize(int id);  // IDはゴールのIDとして利用
	virtual void LoadAssets(std::wstring file_name);  // FILE_NAMEは空文字でいい,読み込みはしないから
	virtual void LoadAssets(DX9::MODEL model) {};  // モデルは使わない
	virtual void Update(const float deltaTime);  // ゴールを用いるモードで判定をするため
	virtual void Render() {};  // モデルの描画はない
	virtual void UIRender() {};

private:
	void SetTransforms();  // 一応おいておく
};