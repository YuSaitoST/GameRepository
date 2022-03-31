//
// TemplateScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

// Initialize member variables.
TitleScene::TitleScene()
{
	descriptorHeap_ = nullptr;
	spriteBatch_ = nullptr;

	bgm_			= new SoundPlayer();
	se_decision_	= new SoundPlayer();
	mv_bg_			= new MoviePlayer(Vector3(0.0f, 0.0f, 0.0f), 1.0f);
	mv_demo_		= new DemoPlay(Vector3(0.0f, 0.0f, 0.0f), 1.0f, DEMO_PLAYBACK);
	time_start_		= new OriTimer(2.5f);
	cursor_			= new Cursor(2);
	choices_		= new Choices(MODE);
	ui_arrows_		= new SelectArrows();
	ui_alpha_		= new FadeAlpha(0.0f, SPEED_ALPHA);
	operate_		= new OperateUI();
}

// Initialize a variable and audio resources.
void TitleScene::Initialize()
{
	omp_set_num_threads(4);

	bgm_->Initialize(L"_Sounds\\_BGM\\bgm_title.wav", SOUND_TYPE::BGM);
	se_decision_->Initialize(L"_Sounds\\_SE\\se_decision_title.wav", SOUND_TYPE::SE, 2);

	cursor_->Initialize();
	ui_arrows_->Initialize(917.5f, 328.5f, 455.0f);
	operate_->Initialize();

	for (int _t = 0; _t < CHOICES; ++_t)
		for (int _u = 0; _u < MODE; ++_u)
			nowText_[_t][_u].Initialize(_u, Vector3(640.0f, UI_TEXT_Y[_t], -10.0f));
	text_ = &nowText_[0][0];
}

// Allocate all memory the Direct3D and Direct2D resources.
void TitleScene::LoadAssets()
{
	descriptorHeap_ = DX12::CreateDescriptorHeap(DXTK->Device, 1);

	ResourceUploadBatch resourceUploadBatch(DXTK->Device);
	resourceUploadBatch.Begin();

	RenderTargetState rtState(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
	SpriteBatchPipelineStateDescription pd(rtState, &CommonStates::NonPremultiplied);
	D3D12_VIEWPORT viewport = {
	0.0f, 0.0f, 1280.0f, 720.0f,
	D3D12_MIN_DEPTH, D3D12_MAX_DEPTH
	};

	spriteBatch_ = DX12::CreateSpriteBatch(DXTK->Device, resourceUploadBatch, pd, &viewport);

	dx9GpuDescriptor_ = DXTK->Direct3D9->CreateShaderResourceView(descriptorHeap_.get(), 0);

	auto uploadResourcesFinished = resourceUploadBatch.End(DXTK->CommandQueue);
	uploadResourcesFinished.wait();

	mv_bg_->LoadAsset(L"_Movies\\title.wmv");
	mv_demo_->LoadAssets();
	cursor_->LoadAsset(L"_Images\\_Title\\cursor.png");
	ui_arrows_->LoadAssets();
	operate_->LoadAsset();

	for (int _t = 0; _t < CHOICES; ++_t)
		for (int _u = 0; _u < MODE; ++_u)
			nowText_[_t][_u].LoadAsset(UI_TEXT_FILE_NAME[_t][_u]);

	mv_bg_->Play();
	bgm_->Play();
}

// Releasing resources required for termination.
void TitleScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.

	delete operate_;
	delete ui_alpha_;
	delete ui_arrows_;
	delete choices_;
	delete cursor_;
	delete time_start_;
	delete mv_demo_;
	delete mv_bg_;
	delete se_decision_;
	delete bgm_;
}

// Direct3D resource cleanup.
void TitleScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void TitleScene::OnRestartSound()
{
	bgm_->OnRestartSound();
}

// Updates the scene.
NextScene TitleScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.

	Press.Accepts();

	time_start_->Update(deltaTime);

	if (time_start_->NowTime() <= 0.5f)
		ui_alpha_->Update(deltaTime);

	if (!time_start_->TimeOut())
		return NextScene::Continue;

	mv_demo_->Update(deltaTime);

	if (Press.AnyKey()) {
		mv_demo_->ResetTime();
		if (mv_demo_->IsDisplay())
			return NextScene::Continue;
	}
	else {
		if (mv_demo_->IsDisplay())
			return NextScene::Continue;
	}

	mv_bg_->Update();
	cursor_->Update();

	if (cursor_->SelectNum() == 0) {
		choices_->Update(Press.LeftKey(), Press.RightKey());
		ChooseMode();
	}

	ui_arrows_->Update();
	text_ = &nowText_[cursor_->SelectNum()][choices_->SelectNum()];

	for (int _t = 0; _t < CHOICES; ++_t)
		(_t == cursor_->SelectNum()) ?
			nowText_[_t][choices_->SelectNum()].GetBigger(deltaTime) :
			nowText_[_t][choices_->SelectNum()].GetSmaller(deltaTime);

	/*
		決定ボタンを押したら、選択した項目に合わせた処理を行う
	*/
	if (Press.DecisionKey()) {
		se_decision_->PlayOneShot();
		const int _select = cursor_->SelectNum();

		if (_select == 1)
			operate_->isPut();
		else {
			if (operate_->isDisplayed())
				return NextScene::Continue;

			DontDestroy->GameMode_ = choices_->SelectNum();
			return NextScene::MainScene;
		}
	}

	operate_->Update(deltaTime);

	return NextScene::Continue;
}

// Draws the scene.
void TitleScene::Render()
{
	DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));  // 画面をクリア
	DXTK->Direct3D9->BeginScene();  // シーンの開始を宣言


	DX9::SpriteBatch->Begin();  // スプライトの描画を開始

	DefaultRender();

	DX9::SpriteBatch->End();  // スプライトの描画を終了
	DXTK->Direct3D9->EndScene();  // シーンの終了を宣言

	DXTK->Direct3D9->UpdateResource();

	DXTK->ResetCommand();
	DXTK->ClearRenderTarget(Colors::CornflowerBlue);


	const auto heapes = descriptorHeap_->Heap();
	DXTK->CommandList->SetDescriptorHeaps(1, &heapes);

	spriteBatch_->Begin(DXTK->CommandList);
	spriteBatch_->Draw(
		dx9GpuDescriptor_,
		XMUINT2(1280, 720),   // HD
		SimpleMath::Vector2(0.0f, 0.0f)
	);
	spriteBatch_->End();

	DXTK->Direct3D9->WaitUpdate();
	DXTK->ExecuteCommandList();
}

void TitleScene::ChooseMode() {
	const bool _inRight = Press.RightKey();
	const bool _inLeft	= Press.LeftKey();

	INPUT_SELECT _input = _inRight ? AL_RIGHT : _inLeft ? AL_LEFT : ui_arrows_->NowState();
	ui_arrows_->SetAnimation(_input);
}

void TitleScene::DefaultRender() {
	mv_demo_->Render();

	if (mv_demo_->IsDisplay())
		return;

	mv_bg_->Render();
	cursor_->Render(ui_alpha_->Alpha());
	ui_arrows_->Render(ui_alpha_->Alpha());
	operate_->Render();

	for (int _t = 0; _t < CHOICES; ++_t)
		nowText_[_t][choices_->SelectNum()].Render(ui_alpha_->Alpha());
}