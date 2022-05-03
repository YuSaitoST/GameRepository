//
// LobbyScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include "_Classes/FileNames.h"
#include "_Classes/_ConstStrages/ConstStorages.h"

#ifndef _DEBUG
#pragma comment (lib, "BulletDynamics.lib")
#pragma comment (lib, "BulletCollision.lib")
#pragma comment (lib, "LinearMath.lib")
#else
#pragma comment (lib, "BulletDynamics_Debug.lib")
#pragma comment (lib, "BulletCollision_Debug.lib")
#pragma comment (lib, "LinearMath_Debug.lib")
#endif

ObjPlayer* LobbyScene::player_[PLAYER];

// Initialize member variables.
LobbyScene::LobbyScene()
{
	DontDestroy->NowScene_	= (int)NextScene::LobbyScene;

	descriptorHeap_			= nullptr;
	spriteBatch_			= nullptr;

	font_count_				= DX9::SPRITEFONT{};
	font_message_			= DX9::SPRITEFONT{};

	collision_config_		= new btDefaultCollisionConfiguration();
	collision_dispatcher_	= new btCollisionDispatcher(collision_config_);
	broadphase_				= new btDbvtBroadphase();
	solver_					= new btSequentialImpulseConstraintSolver();
	physics_world_			= new btDiscreteDynamicsWorld(collision_dispatcher_, broadphase_, solver_, collision_config_);

	bg_movie_				= new MoviePlayer(SimpleMath::Vector3(288.0f, 96.0f, -50.0f), 0.5625f);
	bgm_					= new SoundPlayer();

	for (int _i = 0; _i < PLAYER; ++_i)
		player_[_i] = new ObjPlayer(OPERATE_TYPE::MANUAL, GAME_CONST.S_POS[_i], 1.0f);

	for (int _i = 0; _i < PLAYER; ++_i)
		charaSelect_[_i]	= new CharaSelect();

	timer_goNext_			= new OriTimer(GAME_CONST.LB_GONEXT + 1.0f);

	allSet_					= false;
}

// Initialize a variable and audio resources.
void LobbyScene::Initialize()
{
	omp_set_num_threads(4);
	DXTK->SetFixedFrameRate(60);

	DX12Effect.Initialize();
	Camera.Initialize();
	Light.Initialize();
	Light.Set();
	Light.Enable();

	for (int _i = 0; _i < PLAYER; ++_i)
		DontDestroy->ChoseColor_[_i] = _i;

	bgm_->Initialize(L"_Sounds\\_BGM\\bgm_charaSelect.wav", SOUND_TYPE::BGM);

	for (int _i = 0; _i < PLAYER; ++_i)
		player_[_i]->Initialize(_i);

	for (int _i = 0; _i < PLAYER; ++_i)
		charaSelect_[_i]->Initialize(_i);

	physics_world_->setGravity(btVector3(0.0f, 0.0f, 0.0f));
	for (ObjPlayer* obj : player_)
		physics_world_->addRigidBody(obj->myRigidbody());

	font_count_		= DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"MS ゴシック", 20);
	font_message_	= DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"MS ゴシック", 10);
}

// Allocate all memory the Direct3D and Direct2D resources.
void LobbyScene::LoadAssets()
{
	DX12Effect.SetCamera((DX12::CAMERA)Camera.GetCamera());

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

	DXTK->Direct3D9->SetRenderState(NormalizeNormals_Enable);

	D3DVIEWPORT9 _view{ VIEW_X, VIEW_Y, VIEW_W, VIEW_H, 0.0f, 1.0f };
	DXTK->Device9->SetViewport(&_view);

	sp_bg			= DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Lobby\\backGround.png");
	sp_right		= DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Lobby\\_Arrow\\arrow_right.png");
	sp_left			= DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Lobby\\_Arrow\\arrow_left.png");
	sp_decisions[0] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Lobby\\_UIText\\tex_decision.png");
	sp_decisions[1] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Lobby\\_UIText\\tex_cancel.png");
	sp_entry		= DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Lobby\\_UIText\\tex_entry.png");
	sp_teamCol_[0]	= DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Lobby\\_TeamColor\\team_a.png");
	sp_teamCol_[1]	= DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Lobby\\_TeamColor\\team_b.png");

	for (int _i = 0; _i < PLAYER; ++_i)
		sp_playerIcon[_i] = DX9::Sprite::CreateFromFile(DXTK->Device9, USFN::SP_CHOICEICON[_i] .c_str());

	bg_movie_->LoadAsset(L"_Movies\\main.wmv");

	for (int _i = 0; _i < PLAYER; ++_i)
		player_[_i]->LoadAssets(USFN::MOD_PLAYER[_i]);

	for (CharaSelect* obj : charaSelect_)
		obj->LoadAssets(sp_right, sp_left);

	EFFECT _eff_dummy = DX12Effect.Create(L"_Effects\\_Down\\HITeffect.efk", "dummy");
	DX12Effect.PlayOneShot("dummy");
	DX12Effect.Stop("dummy");

	bg_movie_->Play();
	bgm_->Play();
}

// Releasing resources required for termination.
void LobbyScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.

	for (int _i = PLAYER - 1; 0 <= _i; --_i)
		physics_world_->removeRigidBody(player_[_i]->myRigidbody());

	delete timer_goNext_;

	for (int _i = PLAYER - 1; 0 <= _i; --_i)
		delete charaSelect_[_i];

	delete bgm_;
	delete bg_movie_;

	delete physics_world_;
	delete solver_;
	delete broadphase_;
	delete collision_dispatcher_;
	delete collision_config_;
}

// Direct3D resource cleanup.
void LobbyScene::OnDeviceLost()
{
	DX12Effect.Reset();
}

// Restart any looped sounds here
void LobbyScene::OnRestartSound()
{
	bgm_->OnRestartSound();
}

// Updates the scene.
NextScene LobbyScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.

	physics_world_->stepSimulation(deltaTime, 10);  // 与えた値を10分割する(判定が細かくできる)

	Press.Accepts();

	bg_movie_->Update();

	// 操作練習が現状できないためコメントアウト
	for (int _i = 0; _i < PLAYER; ++_i)
		if (charaSelect_[_i]->IsDecision())
			player_[_i]->Update(deltaTime);

	if (AllDecision()) {
		timer_goNext_->Update(deltaTime);

		if (timer_goNext_->TimeOut())
			return NextScene::MainScene;
		else
			return NextScene::Continue;
	}

	for (int _i = 0; _i < PLAYER; ++_i)
		charaSelect_[_i]->Update(deltaTime, _i);



	return NextScene::Continue;
}

// Draws the scene.
void LobbyScene::Render()
{
	DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));  // 画面をクリア
	DXTK->Direct3D9->BeginScene();  // シーンの開始を宣言

	D3DVIEWPORT9 _view{ VIEW_X,VIEW_Y,VIEW_W,VIEW_H, 0.0f,1.0f };
	DXTK->Device9->SetViewport(&_view);

	Camera.Render();

	for (int _i = 0; _i < PLAYER; ++_i)
		if (charaSelect_[_i]->IsDecision())
			player_[_i]->Render();

	_view.X = 0.0f;
	_view.Y = 0.0f;
	_view.Width = DXTK->ScreenWidth;
	_view.Height = DXTK->ScreenHeight;
	_view.MinZ = 0.0f;
	_view.MaxZ = 1.0f;
	DXTK->Device9->SetViewport(&_view);

	DX9::SpriteBatch->Begin();  // スプライトの描画を開始

	Render_String();
	bg_movie_->Render();
	DX9::SpriteBatch->DrawSimple(sp_bg.Get(), Vector3(0.0f, 0.0f, 1100.0f));

	for (int _i = 0; _i < PLAYER; ++_i)
		charaSelect_[_i]->Render(sp_playerIcon[DontDestroy->ChoseColor_[_i]], sp_decisions[charaSelect_[_i]->IsDecision()], sp_entry, _i);

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

void LobbyScene::ChangeModel(const int plIndex, const int selectID) {
	player_[plIndex]->ReDecision(plIndex, USFN::MOD_PLAYER[selectID]);
}

void LobbyScene::ChangeStrategy(const int plIndex) {
	player_[plIndex]->ChangeStrategy();
}

void LobbyScene::Render_String() {
	if (allSet_) {
		DX9::SpriteBatch->DrawString(font_count_.Get(), SimpleMath::Vector2(50.0f, 100.0f), DX9::Colors::Black, L"開始まで...");
		DX9::SpriteBatch->DrawString(font_count_.Get(), SimpleMath::Vector2(50.0f, 140.0f), DX9::Colors::Black, L"%i 秒", (int)timer_goNext_->NowTime());
	}

	DX9::SpriteBatch->DrawString(font_message_.Get(), SimpleMath::Vector2(50.0f, 340.0f), DX9::Colors::Black, L"TABを押すと残りのプレイヤーを");
	DX9::SpriteBatch->DrawString(font_message_.Get(), SimpleMath::Vector2(50.0f, 360.0f), DX9::Colors::Black, L"決定にすることができます");
}

bool LobbyScene::AllDecision() {
	int count = 0;

	for (int _i = 0; _i < PLAYER; ++_i)
		count += charaSelect_[_i]->IsDecision();

	allSet_ = (count == PLAYER);

	return allSet_;
}