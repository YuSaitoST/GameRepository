//
// LobbyScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Base/DX12Effekseer.h"
#include "SceneFactory.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_InputManager/UseKeyChecker.h"
#include "_Classes/_UI/_UserInputRender/UnSelectedRender.h"
#include "_Classes/_UI/_UserInputRender/SelectedRender.h"
#include "_Classes/_UI/_TeamColor/UseTeamColor.h"
#include "_Classes/_UI/_TeamColor/NullTeamColor.h"

#ifndef _DEBUG
#pragma comment (lib, "BulletDynamics.lib")
#pragma comment (lib, "BulletCollision.lib")
#pragma comment (lib, "LinearMath.lib")
#else
#pragma comment (lib, "BulletDynamics_Debug.lib")
#pragma comment (lib, "BulletCollision_Debug.lib")
#pragma comment (lib, "LinearMath_Debug.lib")
#endif

std::unique_ptr<ObjPlayer> LobbyScene::player_[OBJECT_MAX::PLAYER];

// Initialize member variables.
LobbyScene::LobbyScene()
{
	INPSystem.UDPStart();

	DontDestroy->NowScene_	= NextScene::LobbyScene;

	descriptorHeap_	= nullptr;
	spriteBatch_	= nullptr;

	font_count_		= DX9::SPRITEFONT{};
	font_message_	= DX9::SPRITEFONT{};

	collision_config_ = new btDefaultCollisionConfiguration();
	std::unique_ptr<btCollisionDispatcher>	_collision_dispatcher	= std::make_unique<btCollisionDispatcher>(collision_config_);
	std::unique_ptr<btBroadphaseInterface>	_broadphase				= std::make_unique<btDbvtBroadphase>();						//! ブロードフェーズ法の設定
	std::unique_ptr<btConstraintSolver>		_solver					= std::make_unique<btSequentialImpulseConstraintSolver>();	//! 拘束のソルバ設定
	physics_world_		= std::make_unique<btDiscreteDynamicsWorld>(_collision_dispatcher.release(), _broadphase.release(), _solver.release(), collision_config_);

	bg_movie_			= std::make_unique<MoviePlayer>();
	bgm_				= std::make_unique<SoundPlayer>();
	timer_goNext_		= std::make_unique<CountTimer>(GAMES_PARAM.LB_TIME_AFTER_PREPARATION);
	blackOut_			= std::make_unique<BlackOut>();
	userInputRender_	= { std::make_unique<UnSelectedRender>(), std::make_unique<SelectedRender>() };

	const int _MAX = OBJECT_MAX::PLAYER * 0.5f;
	for (int _i = 0; _i <= _MAX; _i += 2) {
		player_[_i]				= std::make_unique<ObjPlayer>(OPERATE_TYPE::MANUAL, PLAYER_PARAM.START_POS[_i]		, 1.0f);
		player_[_i + 1]			= std::make_unique<ObjPlayer>(OPERATE_TYPE::MANUAL, PLAYER_PARAM.START_POS[_i + 1]	, 1.0f);

		charaSelect_[_i]		= std::make_unique<CharaSelect>();
		charaSelect_[_i + 1]	= std::make_unique<CharaSelect>();
	}

	if (DontDestroy->GameMode_.isDODGEBALL_2ON2())
		teamColor_ = std::make_unique<UseTeamColor>();
	else
		teamColor_ = std::make_unique<NullTeamColor>();

	std::vector<InputSystem> _inpSystem = INPSystem.GetNowInputSystem();
	for (int _i = 0; _i <= _MAX; _i += 2) {
		if (_inpSystem[_i] == InputSystem::COM) {
			infoIcon_[_i] = std::make_unique<COMIcon>();
		}
		else {
			infoIcon_[_i] = std::make_unique<EmptyIcon>();
		}

		if (_inpSystem[_i + 1] == InputSystem::COM) {
			infoIcon_[_i + 1] = std::make_unique<COMIcon>();
		}
		else {
			infoIcon_[_i + 1] = std::make_unique<EmptyIcon>();
		}
	}

	allSet_	= false;
	std::fill(std::begin(DontDestroy->ChoseColor_)	, std::end(DontDestroy->ChoseColor_), 0	);
	std::fill(std::begin(DontDestroy->TeamID)		, std::end(DontDestroy->TeamID)		, -1);
}

// Initialize a variable and audio resources.
void LobbyScene::Initialize()
{
	omp_set_num_threads(4);
	DXTK->SetFixedFrameRate(60);

	DX12Effect.Initialize();
	Camera.Register();

	std::unique_ptr<MainLight> _light = std::make_unique<MainLight>();
	_light->Register();

	bgm_->Initialize(USFN_SOUND::BGM::LOBBY, SOUND_TYPE::BGM, 0.0f);
	blackOut_->Initialize(BLACKOUT_MODE::FADE_OUT);
	teamColor_->Initialize();

	physics_world_->setGravity(btVector3(0.0f, 0.0f, 0.0f));

	const int _MAX = OBJECT_MAX::PLAYER * 0.5f;
	for (int _i = 0; _i <= _MAX; _i += 2) {
		player_[_i]->Initialize(_i);
		player_[_i]->SetInstructor(nullptr, nullptr);
		physics_world_->addRigidBody(player_[_i]->myRigidbody());

		player_[_i + 1]->Initialize(_i + 1);
		player_[_i + 1]->SetInstructor(nullptr, nullptr);
		physics_world_->addRigidBody(player_[_i + 1]->myRigidbody());

		charaSelect_[_i		]->Initialize(_i);
		charaSelect_[_i + 1	]->Initialize(_i + 1);
	}

	font_count_		= DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"MS ゴシック", 20);
	font_message_	= DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"MS ゴシック", 10);
}

// Allocate all memory the Direct3D and Direct2D resources.
void LobbyScene::LoadAssets()
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

	DXTK->Direct3D9->SetRenderState(NormalizeNormals_Enable);

	D3DVIEWPORT9 _view{ 
		US2D::Pos::Get().LobbyParam().VIEW_X, US2D::Pos::Get().LobbyParam().VIEW_Y,
		US2D::Pos::Get().LobbyParam().VIEW_W, US2D::Pos::Get().LobbyParam().VIEW_H,
		0.0f, 1.0f 
	};
	DXTK->Device9->SetViewport(&_view);

	sp_bg_		= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::LOBBY_BG.c_str());
	sp_hole_	= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::HOLE.c_str());
	sp_right_	= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::ARROW_R.c_str());
	sp_left_	= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::ARROW_L.c_str());

	userInputRender_[0]->LoadAssets();
	userInputRender_[1]->LoadAssets();
	teamColor_->LoadAssets();

	const int _MAX = OBJECT_MAX::PLAYER * 0.5f;
	for (int _i = 0; _i <= _MAX; _i += 2) {
		sp_playerIcon_[_i	]	= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::CHOICE_ICON[_i].c_str());
		sp_playerIcon_[_i + 1]	= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::CHOICE_ICON[_i + 1].c_str());

		player_[_i		]->LoadAssets(USFN_MOD::PLAYER[_i		]);
		player_[_i + 1	]->LoadAssets(USFN_MOD::PLAYER[_i + 1	]);

		charaSelect_[_i		]->LoadAssets(sp_right_, sp_left_);
		charaSelect_[_i + 1	]->LoadAssets(sp_right_, sp_left_);

		infoIcon_[_i	]->LoadAssets();
		infoIcon_[_i + 1]->LoadAssets();
	}

	bg_movie_->LoadAsset(USFN_MV::MAIN_BG);
	blackOut_->LoadAsset();

	bg_movie_->Play();
	bgm_->Play();
}

// Releasing resources required for termination.
void LobbyScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.

	for (int _i = OBJECT_MAX::PLAYER - 1; 0 <= _i; --_i)
		physics_world_->removeRigidBody(player_[_i]->myRigidbody());

	delete collision_config_;
}

// Direct3D resource cleanup.
void LobbyScene::OnDeviceLost()
{

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

	INPSystem.Accepts();

	bg_movie_->Update();
	blackOut_->Update(SPEED_FADE[blackOut_->GetMode()] * deltaTime);

	const int _MAX = OBJECT_MAX::PLAYER * 0.5f;
	for (int _i = 0; _i <= _MAX; _i += 2) {
		if (charaSelect_[_i]->IsDecision())
			player_[_i]->Update(deltaTime);

		if (charaSelect_[_i + 1]->IsDecision())
			player_[_i + 1]->Update(deltaTime);
	}

	//全員が選択したら、シーン移行まで待機
	if (AllDecision()) {
		timer_goNext_->Update(deltaTime);

		if (timer_goNext_->TimeOut()) {
			blackOut_->ChangeMode(BLACKOUT_MODE::FADE_IN);

			//ブラックアウトが終了したら本編へ遷移
			if (blackOut_->isDone())
				return NextScene::MainScene;
			else
				return NextScene::Continue;
		}
		else
			return NextScene::Continue;
	}
	else {
		const int _MAX = OBJECT_MAX::PLAYER * 0.5f;
		for (int _i = 0; _i <= _MAX; _i += 2) {
			charaSelect_[_i]->Update(deltaTime, _i);
			charaSelect_[_i + 1]->Update(deltaTime, _i + 1);
		}
	}

	return NextScene::Continue;
}

// Draws the scene.
void LobbyScene::Render()
{
	DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));  // 画面をクリア
	DXTK->Direct3D9->BeginScene();  // シーンの開始を宣言

	const auto _param = US2D::Pos::Get().LobbyParam();
	D3DVIEWPORT9 _view{ 
		_param.VIEW_X, _param.VIEW_Y,
		_param.VIEW_W, _param.VIEW_H,
		0.0f,1.0f 
	};
	DXTK->Device9->SetViewport(&_view);

	const int _MAX = OBJECT_MAX::PLAYER * 0.5f;
	for (int _i = 0; _i <= _MAX; _i += 2) {
		if (charaSelect_[_i]->IsDecision())
			player_[_i]->Render();

		if (charaSelect_[_i + 1]->IsDecision())
			player_[_i + 1]->Render();
	}

	_view.X			= 0.0f;
	_view.Y			= 0.0f;
	_view.Width		= DXTK->ScreenWidth;
	_view.Height	= DXTK->ScreenHeight;
	_view.MinZ		= 0.0f;
	_view.MaxZ		= 1.0f;
	DXTK->Device9->SetViewport(&_view);

	DX9::SpriteBatch->Begin();  // スプライトの描画を開始

	Render_String();
	bg_movie_->Render(XMFLOAT3(_param.VIEW_X, _param.VIEW_Y, (int)US2D::Layer::LOBBY::BG_MOVIE), GAMES_PARAM.LB_MV_SCALE);
	blackOut_->Render();
	DX9::SpriteBatch->DrawSimple(sp_bg_.Get(), XMFLOAT3(0.0f, 0.0f, (int)US2D::Layer::LOBBY::BG_SPRITE));
	DX9::SpriteBatch->Draw(
		sp_hole_.Get(), XMFLOAT3(_param.VIEW_X, _param.VIEW_Y, (int)US2D::Layer::MAIN::UI_HOLE), nullptr,
		DX9::Colors::RGBA(255, 255, 255, 255),
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector2::One * GAMES_PARAM.LB_MV_SCALE
	);
	DX9::SpriteBatch->ResetTransform();

	for (int _i = 0; _i <= _MAX; _i += 2) {
		DX9::SpriteBatch->DrawSimple(sp_playerIcon_[DontDestroy->ChoseColor_[_i		]].Get(), XMFLOAT3(_param.PICON_X[_i	], _param.PICON_Y, (int)US2D::Layer::LOBBY::UI_PLAYERICON));
		DX9::SpriteBatch->DrawSimple(sp_playerIcon_[DontDestroy->ChoseColor_[_i + 1	]].Get(), XMFLOAT3(_param.PICON_X[_i + 1], _param.PICON_Y, (int)US2D::Layer::LOBBY::UI_PLAYERICON));
		charaSelect_[_i		]->Render();
		charaSelect_[_i + 1	]->Render();
		userInputRender_[charaSelect_[_i	]->IsDecision()]->Render(_i		);
		userInputRender_[charaSelect_[_i + 1]->IsDecision()]->Render(_i + 1	);
	}

	for (int _i = 0; _i <= _MAX; _i += 2) {
		// チームカラーの表示
		teamColor_->Render(_i	 );
		teamColor_->Render(_i + 1);
		
		// 付加情報の表示
		infoIcon_[_i	]->Render(_i	);
		infoIcon_[_i + 1]->Render(_i + 1);
	}

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
	player_[plIndex]->ReDecision(plIndex, USFN_MOD::PLAYER[selectID]);
}

void LobbyScene::Render_String() {
	if (allSet_) {
		DX9::SpriteBatch->DrawString(font_count_.Get(), XMFLOAT2(50.0f, 100.0f), DX9::Colors::Black, L"開始まで...");
		DX9::SpriteBatch->DrawString(font_count_.Get(), XMFLOAT2(50.0f, 140.0f), DX9::Colors::Black, L"%i 秒", (int)timer_goNext_->NowTime());
	}

	DX9::SpriteBatch->DrawString(font_message_.Get(), XMFLOAT2(50.0f, 340.0f), DX9::Colors::Black, L"TABを押すと全てのプレイヤーを");
	DX9::SpriteBatch->DrawString(font_message_.Get(), XMFLOAT2(50.0f, 360.0f), DX9::Colors::Black, L"決定にすることができます");
}

bool LobbyScene::AllDecision() {
	int count = 0;

	const int _MAX = OBJECT_MAX::PLAYER * 0.5f;
	for (int _i = 0; _i <= _MAX; _i += 2) {
		count += charaSelect_[_i	]->IsDecision();
		count += charaSelect_[_i + 1]->IsDecision();
	}

	return allSet_ = (count == OBJECT_MAX::PLAYER);
}