#pragma once

#include "_Classes/_CellList/_Object/ObjectBase.h"

class ObjWire final : public ObjectBase {
public:
	ObjWire();
	ObjWire(Vector3 pos, float r);
	virtual ~ObjWire();

	virtual void Initialize(const int id);  // ID�̓S�[����ID�Ƃ��ė��p
	virtual void LoadAssets(std::wstring file_name);  // FILE_NAME�͋󕶎��ł���,�ǂݍ��݂͂��Ȃ�����
	virtual void Update(const float deltaTime);  // �S�[����p���郂�[�h�Ŕ�������邽��

	virtual void HitAction(ObjectBase* hitObject);

	// ��̎���
	virtual void LoadAssets(DX9::MODEL& model) {}  // ���f���͎g��Ȃ�
	virtual void Render() {}  // ���f���̕`��͂Ȃ�
	virtual void Render(DX9::MODEL& model) {}
	virtual void UIRender() {}

private:
	const SimpleMath::Vector3 SCALE = SimpleMath::Vector3(13.75f, 2.25f + 0.1f/* + 1.8f*/ , 0.0f);
	const float ROT_TUNING_Z[2] = { 0.25f + 0.383303374, -0.25f + 0.383303374 };

	const float ROT_Z[2] = { 0.415f, -0.415f };
};