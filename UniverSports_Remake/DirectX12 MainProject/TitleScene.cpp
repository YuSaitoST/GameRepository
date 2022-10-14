//
// TemplateScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include "_Classes/_InputManager/UseKeyChecker.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_UI/_Fade/Fade.h"
#include "_Classes/_MessageBox/OkMessageBox.h"

// Initialize member variables.
TitleScene::TitleScene()
{
	//パラメーターの読み込み
	GAME_CONST.Initialize();

	DontDestroy->NowScene_ = NextScene::TitleScene;
	DontDestroy->GameMode_.SelectMode(GAMEMODE::NONE_GAMEMODE);
	
	descriptorHeap_ = nullptr;
	spriteBatch_	= nullptr;

	bgm_			= std::make_unique<SoundPlayer>();

	display_		= nullptr;
	disp_normal_	= std::make_unique<NormalDisplay>();
	disp_demo_		= std::make_unique<DemoDisplay>();
	disp_config_	= std::make_unique<ConfigDisplay>();
}

// Initialize a variable and audio resources.
void TitleScene::Initialize()
{
	//FPS指定
	DXTK->SetFixedFrameRate(60);

	//BGMの読み込み
	bgm_->Initialize(USFN_SOUND::BGM::TITLE, SOUND_TYPE::BGM, 0.0f);

	//画面表示の初期化
	disp_normal_->Initialize();
	disp_demo_->Initialize();
	disp_config_->Initialize();

	//ゲーム進行関連の変数の初期化
	DontDestroy->Survivor_.Reset();
	std::fill(std::begin(DontDestroy->ChoseColor_), std::end(DontDestroy->ChoseColor_), 0	);
	std::fill(std::begin(DontDestroy->TeamID),		std::end(DontDestroy->TeamID),		-1	);
	std::fill(std::begin(DontDestroy->Score_),		std::end(DontDestroy->Score_),		0	);

	//例外検出テキストファイルがある場合に通知
	std::wstring _str = GAME_TITLE;
	std::wstring _message = _str + L"error_code.txt";
	FILE* _file;
	if (_wfopen_s(&_file, _message.c_str(), L"r") == 0) {
		YUSTK::MessageBox_OK(
			L"前回の起動中に例外が発生していました。Assetsフォルダ内のテキストファイルを開発者へ送っていただけると幸いです。",
			L"例外通知"
		);
	}
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

	//画面表示に使用するファイルの読み込み
	disp_normal_->LoadAssets();
	disp_demo_->LoadAssets();
	disp_config_->LoadAssets();

	//画面表示の設定
	SwitchState(DISPLAYMODE::DISPLAY_NORMAL);
	
	//BGM再生
	bgm_->Play();
}

// Releasing resources required for termination.
void TitleScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.
}

// Direct3D resource cleanup.
void TitleScene::OnDeviceLost()
{
	
}

// Restart any looped sounds here
void TitleScene::OnRestartSound()
{
	//デバイスリセット時に再生し直す
	bgm_->OnRestartSound();
}

// Updates the scene.
NextScene TitleScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.

	//入力状態を調べる
	INPSystem.Accepts();

	//画面上の更新
	NextScene _next = display_->Update(deltaTime);

	//表示の変更条件を満たしていれば、表示状態を変更する
	const DISPLAYMODE _nextDisplay = display_->IsChange();
	if (_nextDisplay != DISPLAYMODE::DISPLAY_NONE) {
		display_->Reset();
		SwitchState(_nextDisplay);
	}

	return _next;
}

// Draws the scene.
void TitleScene::Render()
{
	DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));  // 画面をクリア
	DXTK->Direct3D9->BeginScene();  // シーンの開始を宣言


	DX9::SpriteBatch->Begin();  // スプライトの描画を開始

	display_->Render();

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

void TitleScene::SwitchState(DISPLAYMODE mode) {
	switch (mode) {
		case DISPLAYMODE::DISPLAY_NORMAL: display_ = disp_normal_.get();	break;
		case DISPLAYMODE::DISPLAY_DEMO	: display_ = disp_demo_.get();		break;
		case DISPLAYMODE::DISPLAY_CONFIG: display_ = disp_config_.get();	break;
		default							: assert(!"TitleScene::SwitchState : 不正な状態です");
	}

	//動画の再生
	display_->ReDisplayInitialize();
}