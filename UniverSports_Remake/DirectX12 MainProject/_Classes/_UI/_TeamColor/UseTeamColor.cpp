#include "UseTeamColor.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "DontDestroyOnLoad.h"

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