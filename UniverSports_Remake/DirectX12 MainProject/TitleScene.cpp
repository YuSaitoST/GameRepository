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
	//�p�����[�^�[�̓ǂݍ���
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
	//FPS�w��
	DXTK->SetFixedFrameRate(60);

	//BGM�̓ǂݍ���
	bgm_->Initialize(USFN_SOUND::BGM::TITLE, SOUND_TYPE::BGM, 0.0f);

	//��ʕ\���̏�����
	disp_normal_->Initialize();
	disp_demo_->Initialize();
	disp_config_->Initialize();

	//�Q�[���i�s�֘A�̕ϐ��̏�����
	DontDestroy->Survivor_.Reset();
	std::fill(std::begin(DontDestroy->ChoseColor_), std::end(DontDestroy->ChoseColor_), 0	);
	std::fill(std::begin(DontDestroy->TeamID),		std::end(DontDestroy->TeamID),		-1	);
	std::fill(std::begin(DontDestroy->Score_),		std::end(DontDestroy->Score_),		0	);

	//��O���o�e�L�X�g�t�@�C��������ꍇ�ɒʒm
	std::wstring _str = GAME_TITLE;
	std::wstring _message = _str + L"error_code.txt";
	FILE* _file;
	if (_wfopen_s(&_file, _message.c_str(), L"r") == 0) {
		YUSTK::MessageBox_OK(
			L"�O��̋N�����ɗ�O���������Ă��܂����BAssets�t�H���_���̃e�L�X�g�t�@�C�����J���҂֑����Ă���������ƍK���ł��B",
			L"��O�ʒm"
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

	//��ʕ\���Ɏg�p����t�@�C���̓ǂݍ���
	disp_normal_->LoadAssets();
	disp_demo_->LoadAssets();
	disp_config_->LoadAssets();

	//��ʕ\���̐ݒ�
	SwitchState(DISPLAYMODE::DISPLAY_NORMAL);
	
	//BGM�Đ�
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
	//�f�o�C�X���Z�b�g���ɍĐ�������
	bgm_->OnRestartSound();
}

// Updates the scene.
NextScene TitleScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.

	//���͏�Ԃ𒲂ׂ�
	INPSystem.Accepts();

	//��ʏ�̍X�V
	NextScene _next = display_->Update(deltaTime);

	//�\���̕ύX�����𖞂����Ă���΁A�\����Ԃ�ύX����
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
	DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));  // ��ʂ��N���A
	DXTK->Direct3D9->BeginScene();  // �V�[���̊J�n��錾


	DX9::SpriteBatch->Begin();  // �X�v���C�g�̕`����J�n

	display_->Render();

	DX9::SpriteBatch->End();  // �X�v���C�g�̕`����I��
	DXTK->Direct3D9->EndScene();  // �V�[���̏I����錾

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
		default							: assert(!"TitleScene::SwitchState : �s���ȏ�Ԃł�");
	}

	//����̍Đ�
	display_->ReDisplayInitialize();
}