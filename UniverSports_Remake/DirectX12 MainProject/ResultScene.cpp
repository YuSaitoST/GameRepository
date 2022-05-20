//
// TemplateScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_UI/_Serials/Serials.h"
#include "_Classes/_InputClasses/UseKeyCheck.h"

#include "_Classes/_ResultDraw/SinglesDraw.h"
#include "_Classes/_ResultDraw/DoublesDraw.h"

// Initialize member variables.
ResultScene::ResultScene()
{
	DontDestroy->NowScene_	= (int)NextScene::ResultScene;

	descriptorHeap_			= nullptr;
	spriteBatch_			= nullptr;

	bgm_					= new SoundPlayer();
	se_decision_			= new SoundPlayer();
	bg_movie_				= new MoviePlayer();
	blackOut_				= new BlackOut();

	if (DontDestroy->GameMode_.isSINGLES_GAME())
		drawingByMode_		= new SinglesDraw();
	else
		drawingByMode_		= new DoublesDraw();

	goNext_					= false;
}

// Initialize a variable and audio resources.
void ResultScene::Initialize()
{
	bgm_		->Initialize(USFN_SOUND::BGM::RESULT, SOUND_TYPE::BGM, 0.0f);
	se_decision_->Initialize(USFN_SOUND::SE::DECISION, SOUND_TYPE::SE, 2.0f);

	blackOut_->Initialize(BLACKOUT_MODE::FADE_OUT);

	drawingByMode_->Initialize();
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

	drawingByMode_->LoadAssets();

	sp_bg_tile_		= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::RESULT_BG.c_str());
	sp_texWin_		= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::TEX_WINNER.c_str());
	sp_texPressB_	= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::TEX_PRESS_B.c_str());

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
	blackOut_->Update(SPEED_FADE[blackOut_->GetMode()] * deltaTime);

	if (!goNext_) {
		if (Press.DecisionKey(0) || Press.DecisionKey(1) || Press.DecisionKey(2) || Press.DecisionKey(3)) {
			blackOut_->ChangeMode(BLACKOUT_MODE::FADE_IN);
			goNext_ = true;
		}
	}
	else {
		if (se_decision_->PlayOneShot(deltaTime) && blackOut_->isDone())
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

	drawingByMode_->Render();

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