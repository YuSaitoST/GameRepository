//
// TemplateScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include "_Classes/_FileNames/FileNames.h"

// Initialize member variables.
TitleScene::TitleScene()
{
	DontDestroy->NowScene_ = (int)NextScene::TitleScene;
	DontDestroy->GameMode_.SelectMode(GAMEMODE::NONE_GAMEMODE);

	descriptorHeap_ = nullptr;
	spriteBatch_	= nullptr;

	bgm_			= new SoundPlayer();
	se_decision_	= new SoundPlayer();
	mv_bg_			= new MoviePlayer();
	mv_demo_		= new DemoPlay(DEMO_PLAYBACK);
	time_start_		= new CountTimer(UI_FADE_STARTTIME);
	cursor_			= new Cursor(CHOICES);
	mode_choices_	= new Choices(MODE);
	ui_arrows_		= new SelectArrows();
	ui_alpha_		= new FadeAlpha(0.0f, SPEED_ALPHA);
	operate_		= new OperateUI();
}

// Initialize a variable and audio resources.
void TitleScene::Initialize()
{
	omp_set_num_threads(4);
	DXTK->SetFixedFrameRate(60);
	GAME_CONST.Initialize();
	
	bgm_->Initialize(USFN_SOUND::BGM::TITLE, SOUND_TYPE::BGM, 0.0f);
	se_decision_->Initialize(USFN_SOUND::SE::DECISION_TITLE, SOUND_TYPE::SE, 2.0f);

	cursor_->Initialize();
	ui_arrows_->Initialize(ARROW_POS_R_X, ARROW_POS_L_X, ARROW_POS_Y);
	operate_->Initialize();

	/*
		選択肢のテキストを初期化
		ループ回数を削減するために、選択肢の数が確定している上下の選択は並べて記述
	*/
	for (int _u = 0; _u < MODE; ++_u) {
		nowText_[0][_u].Initialize(_u, Vector3(TEXT_POS_X, UI_TEXT_Y[0], -10.0f));
		nowText_[1][_u].Initialize(_u, Vector3(TEXT_POS_X, UI_TEXT_Y[1], -10.0f));
	}

	// 最初に選択状態にする選択肢を代入
	text_ = &nowText_[0][0];

	std::fill(std::begin(DontDestroy->ChoseColor_), std::end(DontDestroy->ChoseColor_), 0	);
	std::fill(std::begin(DontDestroy->TeamID),		std::end(DontDestroy->TeamID),		-1	);
	std::fill(std::begin(DontDestroy->Score_),		std::end(DontDestroy->Score_),		0	);
	std::fill(std::begin(DontDestroy->Survivor_),	std::end(DontDestroy->Survivor_),	true);
}

// Allocate all memory the Direct3D and Direct2D resources.
void TitleScene::LoadAssets()
{
	descriptorHeap_ = DX12::CreateDescriptorHeap(DXTK->Device, 1);

	ResourceUploadBatch resourceUploadBatch(DXTK->Device);
	resourceUploadBatch.Begin();

	RenderTargetState rtState(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
	SpriteBatchPipelineStateDescription pd(rtState, &CommonStates::NonPremultiplied);
	D3D12_VIEWPORT viewport = {0.0f, 0.0f, 1280.0f, 720.0f, D3D12_MIN_DEPTH, D3D12_MAX_DEPTH};

	spriteBatch_ = DX12::CreateSpriteBatch(DXTK->Device, resourceUploadBatch, pd, &viewport);

	dx9GpuDescriptor_ = DXTK->Direct3D9->CreateShaderResourceView(descriptorHeap_.get(), 0);

	auto uploadResourcesFinished = resourceUploadBatch.End(DXTK->CommandQueue);
	uploadResourcesFinished.wait();

	mv_bg_->LoadAsset(USFN_MV::TITLE_BG);
	mv_demo_->LoadAssets();
	cursor_->LoadAsset(USFN_SP::CURSOR);
	ui_arrows_->LoadAssets();
	operate_->LoadAsset();

	/*
		選択肢に使用する画像のパスを
		ループ回数を削減するために、選択肢の数が確定している上下の選択は並べて記述
	*/
	for (int _u = 0; _u < MODE; ++_u) {
		nowText_[0][_u].LoadAsset(UI_TEXT_FILE_NAME[0][_u]);
		nowText_[1][_u].LoadAsset(UI_TEXT_FILE_NAME[1][_u]);
	}

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
	delete mode_choices_;
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

	// タイトルの表示に合わせてUIをフェードインさせる
	if (time_start_->NowTime() <= 0.5f)
		ui_alpha_->FadeIn(deltaTime);

	// タイトルが表示されるまで操作不可
	if (!time_start_->TimeOut())
		return NextScene::Continue;

	// 決定音がなり終わったらキャラ選択画面へ
	if (!DontDestroy->GameMode_.isNotDecision()) {
		if (se_decision_->PlayOneShot(deltaTime))
			return NextScene::LobbyScene;
		else
			return NextScene::Continue;
	}

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
		mode_choices_->Update(Press.LeftKey(0), Press.RightKey(0));
		mode_choices_->NextSelectOn(ui_arrows_->Update(0));
	}

	text_ = &nowText_[cursor_->SelectNum()][mode_choices_->SelectNum()];

	for (int _t = 0; _t < CHOICES; ++_t) {
		(_t == cursor_->SelectNum()) ?
			nowText_[_t][mode_choices_->SelectNum()].GetBigger(deltaTime) :
			nowText_[_t][mode_choices_->SelectNum()].GetSmaller(deltaTime);
	}

	/*
		決定ボタンを押したら、選択した項目に合わせた処理を行う
	*/
	if (Press.DecisionKey(0)) {
		se_decision_->PlayOneShot();
		const int _select = cursor_->SelectNum();

		if (_select == 1)
			operate_->isPut();
		else if(!operate_->isDisplayed())
			DontDestroy->GameMode_.SelectMode((GAMEMODE)mode_choices_->SelectNum());
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
	spriteBatch_->Draw(dx9GpuDescriptor_, XMUINT2(1280, 720), SimpleMath::Vector2(0.0f, 0.0f));
	spriteBatch_->End();

	DXTK->Direct3D9->WaitUpdate();
	DXTK->ExecuteCommandList();
}

void TitleScene::DefaultRender() {
	mv_demo_->Render();

	if (mv_demo_->IsDisplay())
		return;

	mv_bg_->Render();
	cursor_->Render(ui_alpha_->Alpha());
	ui_arrows_->Render(ui_alpha_->Alpha());
	operate_->Render();

	/*
		選択肢のテキストを初期化
		ループ回数を削減するために、選択肢の数が確定している上下の選択は並べて記述
	*/
	nowText_[0][mode_choices_->SelectNum()].Render(ui_alpha_->Alpha());
	nowText_[1][mode_choices_->SelectNum()].Render(ui_alpha_->Alpha());
}