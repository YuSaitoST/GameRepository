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
	virtual void UIRender();  // 画像描画はある

private:
	void SetTransforms();  // 一応おいておく

	std::vector<DX9::SPRITE> sprite_;

private:
	const std::wstring FILENAME_WIRE[4][4] = {
		{
		  L"_Images\\_Main\\_Wire\\_G_Green\\upperLeft.png",
		  L"_Images\\_Main\\_Wire\\_G_Green\\upperRight.png",
		  L"_Images\\_Main\\_Wire\\_G_Green\\lowerLeft.png",
		  L"_Images\\_Main\\_Wire\\_G_Green\\lowerRight.png"
		},
		{
		  L"_Images\\_Main\\_Wire\\_G_Pink\\upperLeft.png",
		  L"_Images\\_Main\\_Wire\\_G_Pink\\upperRight.png",
		  L"_Images\\_Main\\_Wire\\_G_Pink\\lowerLeft.png",
		  L"_Images\\_Main\\_Wire\\_G_Pink\\lowerRight.png"
		},
		{ 
	      L"_Images\\_Main\\_Wire\\_G_Red\\upperLeft.png",
		  L"_Images\\_Main\\_Wire\\_G_Red\\upperRight.png",
		  L"_Images\\_Main\\_Wire\\_G_Red\\lowerLeft.png",
		  L"_Images\\_Main\\_Wire\\_G_Red\\lowerRight.png"
		},
		{ 
		  L"_Images\\_Main\\_Wire\\_G_Blue\\upperLeft.png",
		  L"_Images\\_Main\\_Wire\\_G_Blue\\upperRight.png",
		  L"_Images\\_Main\\_Wire\\_G_Blue\\lowerLeft.png",
		  L"_Images\\_Main\\_Wire\\_G_Blue\\lowerRight.png"
		}
	};
};