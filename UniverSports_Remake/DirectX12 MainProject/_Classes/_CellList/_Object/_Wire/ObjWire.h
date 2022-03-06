#pragma once

#include "_Classes/_CellList/_Object/ObjectBase.h"

class ObjWire final : public ObjectBase {
public:
	ObjWire();
	ObjWire(Vector3 pos, float r);
	virtual ~ObjWire();

	virtual void Initialize(int id);  // ID�̓S�[����ID�Ƃ��ė��p
	virtual void LoadAssets(std::wstring file_name);  // FILE_NAME�͋󕶎��ł���,�ǂݍ��݂͂��Ȃ�����
	virtual void LoadAssets(DX9::MODEL model) {};  // ���f���͎g��Ȃ�
	virtual void Update(const float deltaTime);  // �S�[����p���郂�[�h�Ŕ�������邽��
	virtual void Render() {};  // ���f���̕`��͂Ȃ�
	virtual void UIRender() {};

private:
	void SetTransforms();  // �ꉞ�����Ă���
};