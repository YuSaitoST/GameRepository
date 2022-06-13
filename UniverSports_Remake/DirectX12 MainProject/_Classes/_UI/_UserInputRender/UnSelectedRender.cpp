#include "UnSelectedRender.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_ConstStrages/ConstStorages.h"

void UnSelectedRender::LoadAssets() {
	sp_decision_ = DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::DECISION.c_str());
}

void UnSelectedRender::Render(int playerID) {
	const auto _param = US2D::Pos::Get().LobbyParam();
	DX9::SpriteBatch->DrawSimple(sp_decision_.Get(), DirectX::XMFLOAT3(_param.INPUT_X[playerID], _param.INPUT_Y, (int)US2D::Layer::LOBBY::UI_DECISIONS));
}