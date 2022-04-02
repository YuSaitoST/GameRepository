//
// LobbyScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

#ifndef _DEBUG
#pragma comment (lib, "BulletDynamics.lib")
#pragma comment (lib, "BulletCollision.lib")
#pragma comment (lib, "LinearMath.lib")
#else
#pragma comment (lib, "BulletDynamics_Debug.lib")
#pragma comment (lib, "BulletCollision_Debug.lib")
#pragma comment (lib, "LinearMath_Debug.lib")
#endif

// Initialize member variables.
LobbyScene::LobbyScene()
{
	descriptorHeap_ = nullptr;
	spriteBatch_ = nullptr;

	collision_config_ = new btDefaultCollisionConfiguration();
	collision_dispatcher_ = new btCollisionDispatcher(collision_config_);
	broadphase_ = new btDbvtBroadphase();
	solver_ = new btSequentialImpulseConstraintSolver();
	physics_world_ = new btDiscreteDynamicsWorld(collision_dispatcher_, broadphase_, solver_, collision_config_);

	for (int _i = 0; _i < 4; ++_i)
		charaSelect_[_i] = new CharaSelect();
}

// Initialize a variable and audio resources.
void LobbyScene::Initialize()
{
	DX12Effect.Initialize();
	Camera.Initialize();
	Light.Initialize();
	Light.Set();
	Light.Enable();

	for (CharaSelect* obj : charaSelect_)
		obj->Initialize();
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
	D3D12_VIEWPORT viewport = {0.0f, 0.0f, 1280.0f, 720.0f, D3D12_MIN_DEPTH, D3D12_MAX_DEPTH};

	spriteBatch_ = DX12::CreateSpriteBatch(DXTK->Device, resourceUploadBatch, pd, &viewport);

	dx9GpuDescriptor_ = DXTK->Direct3D9->CreateShaderResourceView(descriptorHeap_.get(), 0);

	auto uploadResourcesFinished = resourceUploadBatch.End(DXTK->CommandQueue);
	uploadResourcesFinished.wait();

	sp_bg = DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Lobby\\backGround.png");
	sp_right = DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Lobby\\_Arrow\\arrow_right.png");
	sp_left = DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Lobby\\_Arrow\\arrow_left.png");
	sp_decision = DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Lobby\\_UIText\\tex_decision.png");
	sp_cancel = DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Lobby\\_UIText\\tex_cancel.png");
	sp_entry = DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Lobby\\_UIText\\tex_entry.png");
	sp_teamCol_[0] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Lobby\\_TeamColor\\team_a.png");
	sp_teamCol_[1] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Lobby\\_TeamColor\\team_b.png");

	for (CharaSelect* obj : charaSelect_)
		obj->LoadAssets(sp_right, sp_left);

	EFFECT _eff_dummy = DX12Effect.Create(L"_Effects\\_Down\\HITeffect.efk", "dummy");
	DX12Effect.PlayOneShot("dummy");
	DX12Effect.Stop("dummy");
}

// Releasing resources required for termination.
void LobbyScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.

	for (int _i = 3; 0 <= _i; --_i)
		delete charaSelect_[_i];

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

}

// Updates the scene.
NextScene LobbyScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.

	physics_world_->stepSimulation(deltaTime, 10);  // 与えた値を10分割する(判定が細かくできる)

	DX12Effect.Update(deltaTime);
	Press.Accepts();

	charaSelect_[0]->Update(deltaTime, 0);

	if (Press.DecisionKey())
		return NextScene::MainScene;

	return NextScene::Continue;
}

// Draws the scene.
void LobbyScene::Render()
{
	DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));  // 画面をクリア
	DXTK->Direct3D9->BeginScene();  // シーンの開始を宣言

	Camera.Render();

	DX9::SpriteBatch->Begin();  // スプライトの描画を開始

	charaSelect_[0]->Render();

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

	DX12Effect.Renderer();

	DXTK->Direct3D9->WaitUpdate();
	DXTK->ExecuteCommandList();
}