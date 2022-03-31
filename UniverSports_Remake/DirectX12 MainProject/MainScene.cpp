//
// MainScene.cpp
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

CellList cellList = CellList{};

// Initialize member variables.
MainScene::MainScene()
{
	GAME_CONST.Initialize();

	descriptorHeap_			= nullptr;
	spriteBatch_			= nullptr;

	collision_config_		= new btDefaultCollisionConfiguration();
	collision_dispatcher_	= new btCollisionDispatcher(collision_config_);
	broadphase_				= new btDbvtBroadphase();
	solver_					= new btSequentialImpulseConstraintSolver();
	physics_world_			= new btDiscreteDynamicsWorld(collision_dispatcher_, broadphase_, solver_, collision_config_);

	icon_animator_			= new IconAnimator();
	field_					= new GameField(Vector3(0.0f, 0.0f, BACKGROUND), HOLE_FLONT, 1.0f);

	m_object_				= new ObjectManager();
}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{
#ifdef DEBUG
	omp_set_num_threads(4);
#endif // DEBUG

	DXTK->SetFixedFrameRate(60);

	DX12Effect.Initialize();
	Camera.Initialize();
	Light.Initialize();
	Light.Set();
	Light.Enable();

	icon_animator_->Initialize();
	m_object_->Initialize();

	physics_world_->setGravity(btVector3(0.0f, 0.0f, 0.0f));
	m_object_->AddWorld(physics_world_);

#ifdef DEBUG
	DebugList.PushList(L"Player1 Score : %i", DontDestroy->Score_[0]);
#endif // DEBUG
}

// Allocate all memory the Direct3D and Direct2D resources.
void MainScene::LoadAssets()
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

	icon_animator_->LoadAssets();
	field_->LoadAsset(L"_Movies\\main.wmv", L"_Images\\_Main\\holeFlont.png");
	m_object_->LoadAssets();

	// 一応なくても問題はないが、何かあったらこれを処理する
	EFFECT _eff_dummy = DX12Effect.Create(L"_Effects\\_Down\\HITeffect.efk", "dummy");
	DX12Effect.PlayOneShot("dummy");
	DX12Effect.Stop("dummy");
}

// Releasing resources required for termination.
void MainScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.

	m_object_->RemoveWorld(physics_world_);

	delete m_object_;

	delete field_;
	delete icon_animator_;

	delete physics_world_;
	delete solver_;
	delete broadphase_;
	delete collision_dispatcher_;
	delete collision_config_;
}

// Direct3D resource cleanup.
void MainScene::OnDeviceLost()
{
	DX12Effect.Reset();
}

// Restart any looped sounds here
void MainScene::OnRestartSound()
{

}

// Updates the scene.
NextScene MainScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.

	physics_world_->stepSimulation(deltaTime, 10);  // 与えた値を10分割する(判定が細かくできる)

	DX12Effect.Update(deltaTime);
	Press.Accepts();

	//DX12Effect.PlayOneShot("dummy");

	icon_animator_->Update(deltaTime);
	field_->Update();

	m_object_->Update(deltaTime);


	return NextScene::Continue;
}

// Draws the scene.
void MainScene::Render()
{
	DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));  // 画面をクリア
	DXTK->Direct3D9->BeginScene();  // シーンの開始を宣言

	Camera.Render();

	m_object_->RenderModels();


	DX9::SpriteBatch->Begin();  // スプライトの描画を開始

	for (int _i = 0; _i < 2; ++_i)
		icon_animator_->Render(m_object_->PlayerLife(_i), _i);

	field_->Render();
	m_object_->RenderSprites();


#ifdef DEBUG
	DebugList.Render();
#endif // DEBUG

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

	DX12Effect.Renderer();

	DXTK->Direct3D9->WaitUpdate();
	DXTK->ExecuteCommandList();
}
