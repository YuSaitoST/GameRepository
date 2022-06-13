#include "UseTeamColor.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_StandardCalculation/StandardCalculation.h"
#include "DontDestroyOnLoad.h"

UseTeamColor::UseTeamColor() : sprite_{ DX9::SPRITE{}, DX9::SPRITE{} } {
	std::random_device _seed;
	randomEngine_	= std::mt19937(_seed());
	newTeamID_		= std::uniform_int_distribution<>(0, 1);
}

void UseTeamColor::Initialize() {
	const int _MAX = OBJECT_MAX::PLAYER * 0.5f;
	for (int _i = 0; _i <= _MAX; _i += 2) {
		GiveTeamID(_i);
		GiveTeamID(_i + 1);
	}
}

void UseTeamColor::LoadAssets() {
	sprite_[0] = DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::TEAM_A.c_str());
	sprite_[1] = DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::TEAM_B.c_str());
}

void UseTeamColor::Render(int playerID) {
	const auto _param = US2D::Pos::Get().LobbyParam();
	DX9::SpriteBatch->DrawSimple(
		sprite_[DontDestroy->TeamID[playerID]].Get(),
		DirectX::XMFLOAT3(_param.TEAM_COL_X[playerID], _param.TEAM_COL_Y, (int)US2D::Layer::LOBBY::UI_TEAMCOLOR)
	);
}

void UseTeamColor::GiveTeamID(int myID) {
	int _newID = -1;
	do {
		_newID = newTeamID_(randomEngine_);
		DontDestroy->TeamID[myID] = _newID;
	} while (2 < StandardCalculation::HowManyValuesIn(DontDestroy->TeamID, 4, _newID));
}