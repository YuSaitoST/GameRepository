//
// TemplateScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_InputClasses/UseKeyCheck.h"

// Initialize member variables.
ResultScene::ResultScene() : maxScore_(0)
{
	DontDestroy->NowScene_ = (int)NextScene::ResultScene;

	bgm_			= new SoundPlayer();
	se_decision_	= new SoundPlayer();
	bg_movie_		= new MoviePlayer();
	blackOut_		= new BlackOut();

	goNext_			= false;

	const int _numberOfWinner = DontDestroy->GameMode_.isSINGLES_GAME() ? 1 : 2;
	sp_winPlayer_.reserve(_numberOfWinner);
}

// Initialize a variable and audio resources.
void ResultScene::Initialize()
{
	bgm_		->Initialize(USFN_SOUND::BGM::RESULT, SOUND_TYPE::BGM, 0.0f);
	se_decision_->Initialize(USFN_SOUND::SE::DECISION, SOUND_TYPE::SE, 2.0f);

	blackOut_->Initialize(BLACKOUT_MODE::FADE_OUT);

	int _winPlayerID[2] = { -1,-1 };

	if (DontDestroy->GameMode_.isSINGLES_GAME()) {
		// シングルスのスコア計算(一番多いプレイヤーが優勝)
		for (int _i = 0; _i < 4; ++_i) {
			if (maxScore_ < DontDestroy->Score_[_i]) {
				maxScore_ = DontDestroy->Score_[_i];
				_winPlayerID[0] = _i;
			}
		}
	}
	else {
		// ダブルス

		// チームごとにPlayerIDをまとめる
		int _indexOfTeam0 = 0;
		int _indexOfTeam1 = 0;
		int _IDofTeam0[2] = { 0, 0 };
		int _IDofTeam1[2] = { 0, 0 };
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
			_winPlayerID[0] = _IDofTeam1[0];
			_winPlayerID[1] = _IDofTeam1[1];
		}
		else if (_scoreOfTeam1 < _scoreOfTeam0) {
			// チーム0勝利
			maxScore_ = _scoreOfTeam0;
			_winPlayerID[0] = _IDofTeam0[0];
			_winPlayerID[1] = _IDofTeam0[1];
		}
		else {
			// 同点
			maxScore_ = _scoreOfTeam0;
			_winPlayerID[0] = 99;
			_winPlayerID[1] = 99;
		}
	}

	// 数字連番の表示範囲を決める
	const int _oneDigit = maxScore_ % 10;
	const int _twoDigit = (maxScore_ - _oneDigit) * 0.5f;

	oneDigit_x = GetRectX(_oneDigit, SERIALNUMBERS_MAX, SERIAL_NUMBER::RECT_X);
	twoDigit_x = GetRectX(_twoDigit, SERIALNUMBERS_MAX, SERIAL_NUMBER::RECT_X);


	// プレイヤー名の連番の表示範囲を決める
	player_rect_x[0] = GetRectX(_winPlayerID[0], SERIAL_PLAYER::RECT_X * 3, SERIAL_PLAYER::RECT_X);
	player_rect_x[1] = (DontDestroy->GameMode_.isSINGLES_GAME()) ? 0 : GetRectX(_winPlayerID[1], SERIAL_PLAYER::RECT_X * 3, SERIAL_PLAYER::RECT_X);
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

	const int _winPlayerID_0 = player_rect_x[0] / SERIAL_PLAYER::RECT_X;
	const int _winPlayerID_1 = player_rect_x[1] / SERIAL_PLAYER::RECT_X;

	if (DontDestroy->GameMode_.isSINGLES_GAME())
		sp_winPlayer_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::WINNERCHARA[_winPlayerID_0].c_str()));
	else {
		sp_winPlayer_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::WINNERCHARA[_winPlayerID_0].c_str()));
		sp_winPlayer_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::WINNERCHARA[_winPlayerID_1].c_str()));
	}

	sp_bg_tile_		= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::RESULT_BG.c_str());
	sp_texWin_		= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::TEX_WINNER.c_str());
	sp_texPressB_	= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::TEX_PRESS_B.c_str());
	sp_playerName_	= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::TEX_PLAYER.c_str());
	sp_number_		= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::NUMBER.c_str());

	// GameMode { 0(撃破) , 1(スコア) , 2(撃破) , 3(スコア) }
	sp_texCrushing_	= (DontDestroy->GameMode_.isDODGEBALL()) ?
		DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::GEKIHA.c_str()) :
		DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::SCORE.c_str());

	bg_movie_->LoadAsset(USFN_MV::MAIN_BG);
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
			goNext_ = true;
		}
	}
	else {
		if (se_decision_->PlayOneShot(deltaTime))
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
	DX9::SpriteBatch->DrawSimple(sp_number_.Get(), Vector3(SERIAL_NUMBER::POS_X, SERIAL_NUMBER::POS_Y, -3.0f), RECT(twoDigit_x, 0, twoDigit_x + SERIAL_NUMBER::RECT_X, SERIAL_NUMBER::RECT_Y));
	DX9::SpriteBatch->DrawSimple(sp_number_.Get(), Vector3(SERIAL_NUMBER::POS_X + SERIAL_NUMBER::RECT_X, SERIAL_NUMBER::POS_Y, -3.0f), RECT(oneDigit_x, 0, oneDigit_x + SERIAL_NUMBER::RECT_X, SERIAL_NUMBER::RECT_Y));

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
		DX9::SpriteBatch->DrawSimple(sp_winPlayer_[0].Get(), Vector3(100.0f, 0.0f, -3.0f));
		DX9::SpriteBatch->DrawSimple(sp_winPlayer_[1].Get(), Vector3(-226.0f, 0.0f, -2.0f));
	}
}

void ResultScene::Render_WinCName() {
	if (DontDestroy->GameMode_.isSINGLES_GAME())
		DX9::SpriteBatch->DrawSimple(sp_playerName_.Get(), Vector3(SERIAL_PLAYER::POS_X, SERIAL_PLAYER::POS_Y, -3.0f), RECT(player_rect_x[0], 0, player_rect_x[0] + SERIAL_PLAYER::RECT_X, SERIAL_PLAYER::RECT_Y));
	else {
		DX9::SpriteBatch->DrawSimple(sp_playerName_.Get(), Vector3(SERIAL_PLAYER::POS_X - 50.0f, SERIAL_PLAYER::POS_Y, -3.0f), RECT(player_rect_x[0], 0, player_rect_x[0] + SERIAL_PLAYER::RECT_X, SERIAL_PLAYER::RECT_Y));
		DX9::SpriteBatch->DrawSimple(sp_playerName_.Get(), Vector3(SERIAL_PLAYER::POS_X + SERIAL_PLAYER::RECT_X - 50.0f, SERIAL_PLAYER::POS_Y, -3.0f), RECT(player_rect_x[1], 0, player_rect_x[1] + SERIAL_PLAYER::RECT_X, SERIAL_PLAYER::RECT_Y));
	}
}

float ResultScene::GetRectX(int number, int numbersMax, int wight) {
	return std::min(number, numbersMax) * wight;
}