#include "SelectedRender.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_ConstStrages/ConstStorages.h"

void SelectedRender::LoadAssets() {
	sp_cancel_	= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::CANCEL.c_str());
	sp_entry_	= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::ENTRY.c_str());
}

void SelectedRender::Render(int playerID) {
	const auto _param = US2D::Pos::Get().LobbyParam();
	DX9::SpriteBatch->DrawSimple(sp_cancel_.Get()	, DirectX::XMFLOAT3(_param.INPUT_X[playerID], _param.INPUT_Y, (int)US2D::Layer::LOBBY::UI_DECISIONS));
	DX9::SpriteBatch->DrawSimple(sp_entry_.Get()	, DirectX::XMFLOAT3(_param.ENTRY_X[playerID], _param.ENTRY_Y, (int)US2D::Layer::LOBBY::UI_ENTRY)	);
}