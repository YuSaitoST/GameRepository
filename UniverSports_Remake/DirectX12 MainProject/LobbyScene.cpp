//
// LobbyScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Base/DX12Effekseer.h"
#include "SceneFactory.h"
#include "_Classes/_FileNames/FileNames.h"

#ifndef _DEBUG
#pragma comment (lib, "BulletDynamics.lib")
#pragma comment (lib, "BulletCollision.lib")
#pragma comment (lib, "LinearMath.lib")
#else
#pragma comment (lib, "BulletDynamics_Debug.lib")
#pragma comment (lib, "BulletCollision_Debug.lib")
#pragma comment (lib, "LinearMath_Debug.lib")
#endif

ObjPlayer* LobbyScene::player_[OBJECT_MAX::PLAYER];

// Initialize member variables.
LobbyScene::LobbyScene()
{
	DontDestroy->NowScene_		= (int)NextScene::LobbyScene;

	descriptorHeap_				= nullptr;
	spriteBatch_				= nullptr;

	std::random_device _seed;
	randomEngine_				= std::mt19937(_seed());
	newTeamID_					= std::uniform_int_distribution<>(0, 1);

	font_count_					= DX9::SPRITEFONT{};
	font_message_				= DX9::SPRITEFONT{};

	collision_config_			= new btDefaultCollisionConfiguration();
	collision_dispatcher_		= new btCollisionDispatcher(collision_config_);
	broadphase_					= new btDbvtBroadphase();
	solver_						= new btSequentialImpulseConstraintSolver();
	physics_world_				= new btDiscreteDynamicsWorld(collision_dispatcher_, broadphase_, solver_, collision_config_);

	bg_movie_					= std::make_unique<MoviePlayer>();
	bgm_						= std::make_unique<SoundPlayer>();

	const int _MAX = OBJECT_MAX::PLAYER * 0.5f;
	for (int _i = 0; _i <= _MAX; _i += 2) {
		player_[_i]				= new ObjPlayer(OPERATE_TYPE::MANUAL, PLAYER_PARAM.START_POS[_i], 1.0f);
		charaSelect_[_i]		= std::make_unique<CharaSelect>();

		player_[_i + 1]			= new ObjPlayer(OPERATE_TYPE::MANUAL, PLAYER_PARAM.START_POS[_i + 1], 1.0f);
		charaSelect_[_i + 1]	= std::make_unique<CharaSelect>();
	}

	timer_goNext_				= std::make_unique<CountTimer>(GAMES_PARAM.LB_TIME_AFTER_PREPARATION);
	blackOut_					= std::make_unique<BlackOut>();

	allSet_						= false;
}

// Initialize a variable and audio resources.
void LobbyScene::Initialize()
{
	omp_set_num_threads(4);
	DXTK->SetFixedFrameRate(60);

	DX12Effect.Initialize();
	Camera.Register();

	MainLight _light;
	_light.Register();

	std::fill(std::begin(DontDestroy->ChoseColor_), std::end(DontDestroy->ChoseColor_), 0);
	std::fill(std::begin(DontDestroy->TeamID),		std::end(DontDestroy->TeamID),		-1);

	if (DontDestroy->GameMode_.isDODGEBALL_2ON2()) {
		const int _MAX = OBJECT_MAX::PLAYER * 0.5f;
		for (int _i = 0; _i <= _MAX; _i += 2) {
			GiveTeamID(_i);
			GiveTeamID(_i + 1);
		}
	}

	bgm_->Initialize(USFN_SOUND::BGM::LOBBY, SOUND_TYPE::BGM, 0.0f);
	blackOut_->Initialize(BLACKOUT_MODE::FADE_OUT);

	physics_world_->setGravity(btVector3(0.0f, 0.0f, 0.0f));

	const int _MAX = OBJECT_MAX::PLAYER * 0.5f;
	for (int _i = 0; _i <= _MAX; _i += 2) {
		player_[_i]->Initialize(_i);
		player_[_i]->SetInstructor(nullptr, nullptr);
		physics_world_->addRigidBody(player_[_i]->myRigidbody());

		player_[_i + 1]->Initialize(_i + 1);
		player_[_i + 1]->SetInstructor(nullptr, nullptr);
		physics_world_->addRigidBody(player_[_i + 1]->myRigidbody());

		charaSelect_[_i]->Initialize(_i);
		charaSelect_[_i + 1]->Initialize(_i + 1);
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
		0.0f, 1.0f };
	DXTK->Device9->SetViewport(&_view);

	sp_bg			= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::LOBBY_BG.c_str());
	sp_right		= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::ARROW_R.c_str());
	sp_left			= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::ARROW_L.c_str());
	sp_decisions[0] = DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::DECISION.c_str());
	sp_decisions[1] = DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::CANCEL.c_str());
	sp_entry		= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::ENTRY.c_str());
	sp_teamCol_[0]	= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::TEAM_A.c_str());
	sp_teamCol_[1]	= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::TEAM_B.c_str());

	const int _MAX = OBJECT_MAX::PLAYER * 0.5f;
	for (int _i = 0; _i <= _MAX; _i += 2) {
		sp_playerIcon[_i]		= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::CHOICE_ICON[_i].c_str());
		player_[_i]->LoadAssets(USFN_MOD::PLAYER[_i]);
		charaSelect_[_i]->LoadAssets(sp_right, sp_left);

		sp_playerIcon[_i + 1]	= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::CHOICE_ICON[_i + 1].c_str());
		player_[_i + 1]->LoadAssets(USFN_MOD::PLAYER[_i + 1]);
		charaSelect_[_i + 1]->LoadAssets(sp_right, sp_left);
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

	delete physics_world_;
	delete solver_;
	delete broadphase_;
	delete collision_dispatcher_;
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

	Press.Accepts();

	bg_movie_->Update();
	blackOut_->Update(SPEED_FADE[blackOut_->GetMode()] * deltaTime);

	const int _MAX = OBJECT_MAX::PLAYER * 0.5f;
	for (int _i = 0; _i <= _MAX; _i += 2) {
		if (charaSelect_[_i]->IsDecision())
			player_[_i]->Update(deltaTime);

		if (charaSelect_[_i + 1]->IsDecision())
			player_[_i + 1]->Update(deltaTime);
	}

	if (AllDecision()) {
		timer_goNext_->Update(deltaTime);

		if (timer_goNext_->TimeOut()) {
			blackOut_->ChangeMode(BLACKOUT_MODE::FADE_IN);

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

	D3DVIEWPORT9 _view{ 
		US2D::Pos::Get().LobbyParam().VIEW_X, US2D::Pos::Get().LobbyParam().VIEW_Y,
		US2D::Pos::Get().LobbyParam().VIEW_W, US2D::Pos::Get().LobbyParam().VIEW_H,
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

	_view.X = 0.0f;
	_view.Y = 0.0f;
	_view.Width = DXTK->ScreenWidth;
	_view.Height = DXTK->ScreenHeight;
	_view.MinZ = 0.0f;
	_view.MaxZ = 1.0f;
	DXTK->Device9->SetViewport(&_view);

	DX9::SpriteBatch->Begin();  // スプライトの描画を開始

	Render_String();
	bg_movie_->Render(XMFLOAT3(US2D::Pos::Get().LobbyParam().VIEW_X, US2D::Pos::Get().LobbyParam().VIEW_Y, (int)US2D::Layer::LOBBY::BG_MOVIE), GAMES_PARAM.LB_MV_SCALE);
	blackOut_->Render();
	DX9::SpriteBatch->DrawSimple(sp_bg.Get(), XMFLOAT3(0.0f, 0.0f, (int)US2D::Layer::LOBBY::BG_SPRITE));

	for (int _i = 0; _i <= _MAX; _i += 2) {
		charaSelect_[_i		]->Render(sp_playerIcon[DontDestroy->ChoseColor_[_i		]], sp_decisions[charaSelect_[_i	]->IsDecision()], sp_entry, _i		);
		charaSelect_[_i + 1	]->Render(sp_playerIcon[DontDestroy->ChoseColor_[_i + 1	]], sp_decisions[charaSelect_[_i + 1]->IsDecision()], sp_entry, _i + 1	);
	}

	// チームカラーの表示
	if (DontDestroy->GameMode_.isDODGEBALL_2ON2()) {
		for (int _i = 0; _i <= _MAX; _i += 2) {
			DX9::SpriteBatch->DrawSimple(sp_teamCol_[DontDestroy->TeamID[_i		]].Get(), XMFLOAT3(US2D::Pos::Get().LobbyParam().TEAM_COL_X[_i		], US2D::Pos::Get().LobbyParam().TEAM_COL_Y, (int)US2D::Layer::LOBBY::UI_TEAMCOLOR));
			DX9::SpriteBatch->DrawSimple(sp_teamCol_[DontDestroy->TeamID[_i + 1	]].Get(), XMFLOAT3(US2D::Pos::Get().LobbyParam().TEAM_COL_X[_i + 1	], US2D::Pos::Get().LobbyParam().TEAM_COL_Y, (int)US2D::Layer::LOBBY::UI_TEAMCOLOR));
		}
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

void LobbyScene::ChangeStrategy(const int plIndex) {
	player_[plIndex]->ChangeStrategy();
}

void LobbyScene::Render_String() {
	if (allSet_) {
		DX9::SpriteBatch->DrawString(font_count_.Get(), XMFLOAT2(50.0f, 100.0f), DX9::Colors::Black, L"開始まで...");
		DX9::SpriteBatch->DrawString(font_count_.Get(), XMFLOAT2(50.0f, 140.0f), DX9::Colors::Black, L"%i 秒", (int)timer_goNext_->NowTime());
	}

	DX9::SpriteBatch->DrawString(font_message_.Get(), XMFLOAT2(50.0f, 340.0f), DX9::Colors::Black, L"TABを押すと他のプレイヤーを");
	DX9::SpriteBatch->DrawString(font_message_.Get(), XMFLOAT2(50.0f, 360.0f), DX9::Colors::Black, L"決定にすることができます");
}

void LobbyScene::GiveTeamID(int myID) {
	int _newID = -1;
	do {
		_newID = newTeamID_(randomEngine_);
		DontDestroy->TeamID[myID] = _newID;
	} while (2 < HowManyValuesIn(DontDestroy->TeamID, 4, _newID));
}

int LobbyScene::HowManyValuesIn(const int* list, int size, int findNum) {
	int _count = 0;
	for (int _i = 0; _i < size; ++_i)
		if (list[_i] == findNum)
			_count += 1;
	
	return _count;
}

bool LobbyScene::AllDecision() {
	int count = 0;

	const int _MAX = OBJECT_MAX::PLAYER * 0.5f;
	for (int _i = 0; _i <= _MAX; _i += 2) {
		count += charaSelect_[_i]->IsDecision();
		count += charaSelect_[_i + 1]->IsDecision();
	}

	allSet_ = (count == OBJECT_MAX::PLAYER);

	return allSet_;
}