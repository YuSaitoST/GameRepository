//
// TemplateScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include "_Classes/FileNames.h"
#include "_Classes/_InputClasses/UseKeyCheck.h"

// Initialize member variables.
ResultScene::ResultScene()
{
	DontDestroy->NowScene_ = (int)NextScene::ResultScene;

	bgm_			= new SoundPlayer();
	se_decision_	= new SoundPlayer();
	bg_movie_		= new MoviePlayer(Vector3::Zero, 1.0f);
	blackOut_		= new BlackOut();

	goNext_			= false;
}

// Initialize a variable and audio resources.
void ResultScene::Initialize()
{
	bgm_		->Initialize(L"_Sounds\\_BGM\\bgm_result.wav", SOUND_TYPE::BGM);
	se_decision_->Initialize(L"_Sounds\\_SE\\se_decision.wav", SOUND_TYPE::SE, 2);

	blackOut_->Initialize(BLACKOUT_MODE::FADE_OUT);

	if (DontDestroy->GameMode_.isSINGLES_GAME()) {
		// シングルスのスコア計算(一番多いプレイヤーが優勝)
		int _maxScore = 0;
		for (int _i = 0; _i < 4; ++_i) {
			if (_maxScore < DontDestroy->Score_[_i]) {
				_maxScore = DontDestroy->Score_[_i];
				winPlayerID_[0] = _i;
			}
		}
	}
	else {
		// ダブルス

		// チームごとにPlayerIDをまとめる
		int _indexOfTeam0 = 0;
		int _indexOfTeam1 = 0;
		int _IDofTeam0[2];
		int _IDofTeam1[2];
		for (int _i = 0; _i < 4; ++_i) {
			if (DontDestroy->TeamID[_i] == 0) {
				_IDofTeam0[_indexOfTeam0] = _i;
				_indexOfTeam0 += 1;
			}
			else {
				_IDofTeam1[_indexOfTeam1] = _i;
				_indexOfTeam1 += 1;
			}
		}

		const int _scoreOfTeam0 = DontDestroy->Score_[_IDofTeam0[0]] + DontDestroy->Score_[_IDofTeam0[1]];
		const int _scoreOfTeam1 = DontDestroy->Score_[_IDofTeam1[0]] + DontDestroy->Score_[_IDofTeam1[1]];
		if (_scoreOfTeam0 < _scoreOfTeam1) {
			// チーム1勝利
			maxScore_ = _scoreOfTeam1;
			SetPlayerIDofTheWinningTeam(_IDofTeam1);
		}
		else if (_scoreOfTeam1 < _scoreOfTeam0) {
			// チーム0勝利
			maxScore_ = _scoreOfTeam0;
			SetPlayerIDofTheWinningTeam(_IDofTeam0);
		}
		else {
			// 同点
			maxScore_ = _scoreOfTeam0;
			winPlayerID_[0] = 99;
			winPlayerID_[1] = 99;
		}
	}

	// 数字連番の表示範囲を決める
	if (DontDestroy->GameMode_.isDODGEBALL_NOMAL())
		Mode_0();
	else if (DontDestroy->GameMode_.isHANDBALL())
		Mode_1();
	else if (DontDestroy->GameMode_.isDODGEBALL_2ON2())
		Mode_2();

	// プレイヤー名の連番の表示範囲を決める
	player_rect_x[0] = (DontDestroy->GameMode_.isSINGLES_GAME()) ? std::min(std::max(0, PLAYER::RECT_X * winPlayerID_[0]), PLAYER::RECT_X * 3)	: std::min(std::max(0, PLAYER::RECT_X * winPlayerID_[0]), PLAYER::RECT_X * 3);
	player_rect_x[1] = (DontDestroy->GameMode_.isSINGLES_GAME()) ? 0																				: std::min(std::max(0, PLAYER::RECT_X * winPlayerID_[1]), PLAYER::RECT_X * 3);
}

// Allocate all memory the Direct3D and Direct2D resources.
void ResultScene::LoadAssets()
{
	descriptorHeap_ = DX12::CreateDescriptorHeap(DXTK->Device, 1);

	ResourceUploadBatch resourceUploadBatch(DXTK->Device);
	resourceUploadBatch.Begin();

	RenderTargetState rtState(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
	SpriteBatchPipelineStateDescription pd(rtState, &CommonStates::NonPremultiplied);
	D3D12_VIEWPORT viewport = { 0.0f, 0.0f, 1280.0f, 720.0f, D3D12_MIN_DEPTH, D3D12_MAX_DEPTH };

	spriteBatch_ = DX12::CreateSpriteBatch(DXTK->Device, resourceUploadBatch, pd, &viewport);

	dx9GpuDescriptor_ = DXTK->Direct3D9->CreateShaderResourceView(descriptorHeap_.get(), 0);

	auto uploadResourcesFinished = resourceUploadBatch.End(DXTK->CommandQueue);
	uploadResourcesFinished.wait();

	if (DontDestroy->GameMode_.isSINGLES_GAME())
		sp_winPlayer_[0] = DX9::Sprite::CreateFromFile(DXTK->Device9, USFN::SP_WINNERCHARA[winPlayerID_[0]].c_str());
	else {
		sp_winPlayer_[0] = DX9::Sprite::CreateFromFile(DXTK->Device9, USFN::SP_WINNERCHARA[winPlayerID_[0]].c_str());
		sp_winPlayer_[1] = DX9::Sprite::CreateFromFile(DXTK->Device9, USFN::SP_WINNERCHARA[winPlayerID_[1]].c_str());
	}

	sp_bg_tile_		= DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Result\\bg_tile.png");
	sp_texWin_		= DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Result\\_UIText\\tex_winner.png");
	sp_texPressB_	= DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Result\\_UIText\\tex_pressB.png");
	sp_playerName_	= DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Result\\_UIText\\tex_player.png");
	sp_number_		= DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Result\\_UIText\\number.png");

	// GameMode { 0(撃破) , 1(スコア) , 2(撃破) , 3(スコア) }
	sp_texCrushing_	= (DontDestroy->GameMode_.isDODGEBALL()) ?
		DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Result\\_UIText\\tex_gekiha.png") :
		DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Result\\_UIText\\tex_score.png");


	bg_movie_->LoadAsset(L"_Movies\\main.wmv");
	blackOut_->LoadAsset();

	bg_movie_->Play();
	bgm_->Play();
}

// Releasing resources required for termination.
void ResultScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.

	delete blackOut_;
	delete bg_movie_;
	delete se_decision_;
	delete bgm_;
}

// Direct3D resource cleanup.
void ResultScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void ResultScene::OnRestartSound()
{
	bgm_->OnRestartSound();
}

// Updates the scene.
NextScene ResultScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.

	Press.Accepts();

	bg_movie_->Update();
	blackOut_->Update(deltaTime);

	if (!goNext_) {
		if (Press.DecisionKey(0) || Press.DecisionKey(1) || Press.DecisionKey(2) || Press.DecisionKey(3)) {
			se_decision_->PlayOneShot();
			goNext_ = true;
		}
	}
	else {
		se_decision_->Update(deltaTime);
		if (se_decision_->isFined())
			return NextScene::TitleScene;
	}

	return NextScene::Continue;
}

// Draws the scene.
void ResultScene::Render()
{
	DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));  // 画面をクリア
	DXTK->Direct3D9->BeginScene();  // シーンの開始を宣言


	DX9::SpriteBatch->Begin();  // スプライトの描画を開始

	blackOut_->Render();
	bg_movie_->Render();

	DX9::SpriteBatch->DrawSimple(sp_bg_tile_.Get(), Vector3(0.0f, 0.0f, -1.0f));
	DX9::SpriteBatch->DrawSimple(sp_texWin_.Get(), Vector3(0.0f, 0.0f, -3.0f));
	DX9::SpriteBatch->DrawSimple(sp_texCrushing_.Get(), Vector3(0.0f, 0.0f, -3.0f));
	DX9::SpriteBatch->DrawSimple(sp_texPressB_.Get(), Vector3(0.0f, 0.0f, -3.0f));
	DX9::SpriteBatch->DrawSimple(sp_number_.Get(), Vector3(NUMBER::POS_X, NUMBER::POS_Y, -3.0f), RECT(twoDigit_x, 0, twoDigit_x + NUMBER::RECT_X, NUMBER::RECT_Y));
	DX9::SpriteBatch->DrawSimple(sp_number_.Get(), Vector3(NUMBER::POS_X + NUMBER::RECT_X, NUMBER::POS_Y, -3.0f), RECT(oneDigit_x, 0, oneDigit_x + NUMBER::RECT_X, NUMBER::RECT_Y));

	Render_WinCName();
	Render_WinChara();

	DX9::SpriteBatch->End();  // スプライトの描画を終了
	DXTK->Direct3D9->EndScene();  // シーンの終了を宣言

	DXTK->Direct3D9->UpdateResource();

	DXTK->ResetCommand();
	DXTK->ClearRenderTarget(Colors::CornflowerBlue);

	const auto heapes = descriptorHeap_->Heap();
	DXTK->CommandList->SetDescriptorHeaps(1, &heapes);

	spriteBatch_->Begin(DXTK->CommandList);
	spriteBatch_->Draw(dx9GpuDescriptor_, XMUINT2(1280, 720), SimpleMath::Vector2(0.0f, 0.0f));
	spriteBatch_->End();

	DXTK->Direct3D9->WaitUpdate();
	DXTK->ExecuteCommandList();
}

void ResultScene::Render_WinChara() {
	if (DontDestroy->GameMode_.isSINGLES_GAME())
		DX9::SpriteBatch->DrawSimple(sp_winPlayer_[0].Get(), Vector3(0.0f, 0.0f, -2.0f));
	else {
		DX9::SpriteBatch->DrawSimple(sp_winPlayer_[winPlayerID_[0]].Get(), Vector3(100.0f, 0.0f, -3.0f));
		DX9::SpriteBatch->DrawSimple(sp_winPlayer_[winPlayerID_[1]].Get(), Vector3(-226.0f, 0.0f, -2.0f));
	}
}

void ResultScene::Render_WinCName() {
	if (DontDestroy->GameMode_.isSINGLES_GAME())
		DX9::SpriteBatch->DrawSimple(sp_playerName_.Get(), Vector3(PLAYER::POS_X,							PLAYER::POS_Y, -3.0f), RECT(player_rect_x[0], 0, player_rect_x[0] + PLAYER::RECT_X, PLAYER::RECT_Y));
	else {
		DX9::SpriteBatch->DrawSimple(sp_playerName_.Get(), Vector3(PLAYER::POS_X - 50.0f,					PLAYER::POS_Y, -3.0f), RECT(player_rect_x[0], 0, player_rect_x[0] + PLAYER::RECT_X, PLAYER::RECT_Y));
		DX9::SpriteBatch->DrawSimple(sp_playerName_.Get(), Vector3(PLAYER::POS_X + PLAYER::RECT_X - 50.0f,	PLAYER::POS_Y, -3.0f), RECT(player_rect_x[1], 0, player_rect_x[1] + PLAYER::RECT_X, PLAYER::RECT_Y));
	}
}

// ドッジ
void ResultScene::Mode_0() {
	oneDigit_x = std::min(std::max(0, NUMBER::RECT_X * maxScore_), NUMBER::RECT_X * 9);
}

// ハンド
void ResultScene::Mode_1() {
	if (maxScore_ < 10) {
		oneDigit_x = std::min(std::max(0, NUMBER::RECT_X * maxScore_), NUMBER::RECT_X * 9);
		twoDigit_x = 0;
	}
	else {
		const int _oneDigit = maxScore_ % 10;
		const int _twoDigit = (maxScore_ - _oneDigit) * 0.5f;

		oneDigit_x = std::min(std::max(0, NUMBER::RECT_X * _oneDigit), NUMBER::RECT_X * 9);
		twoDigit_x = std::min(std::max(0, NUMBER::RECT_X * _twoDigit), NUMBER::RECT_X * 9);
	}
}

// 2on2
void ResultScene::Mode_2() {
	if (maxScore_ < 10) {
		oneDigit_x = std::min(std::max(0, NUMBER::RECT_X * maxScore_), NUMBER::RECT_X * 9);
		twoDigit_x = 0;
	}
	else {
		const int _oneDigit = maxScore_ % 10;
		const int _twoDigit = (maxScore_ - _oneDigit) * 0.1f;

		oneDigit_x = std::min(std::max(0, NUMBER::RECT_X * _oneDigit), NUMBER::RECT_X * 9);
		twoDigit_x = std::min(std::max(0, NUMBER::RECT_X * _twoDigit), NUMBER::RECT_X * 9);
	}
}

void ResultScene::SetPlayerIDofTheWinningTeam(const int teamMember[2]) {
	winPlayerID_[0] = teamMember[0];
	winPlayerID_[1] = teamMember[1];
}