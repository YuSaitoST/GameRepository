#pragma once

#include "_Classes/_MoviePlayer/MoviePlayer.h"

class GameField {
public:
	GameField(SimpleMath::Vector3 pos, float sp_z, float scale);
	virtual ~GameField();
	
	void LoadAsset(std::wstring m_file_name, std::wstring s_file_name);
	void Update();
	void Render();

private:
	MoviePlayer* movie_;
	DX9::SPRITE sp_hole_;
	SimpleMath::Vector3 pos_;

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