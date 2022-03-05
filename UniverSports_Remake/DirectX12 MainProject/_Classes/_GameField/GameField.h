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
	DX9::SPRITE sprite_;
	SimpleMath::Vector3 pos_;
};