#include "SelectArrows.h"
#include "_Classes/_ConstStrages/US2DLayer.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_InputClasses/UseKeyCheck.h"

using namespace DirectX;

SelectArrows::SelectArrows() : sp_right_(DX9::SPRITE()), sp_left_(DX9::SPRITE()) {
	input_			= AL_NONE;

	pos_right_x_	= 0.0f;
	pos_left_x_		= 0.0f;
	pos_y_			= 0.0f;

	scale_right_	= 0.0f;
	scale_left_		= 0.0f;

	isFinBigger		= false;
	isFinSmaller	= false;
}

void SelectArrows::Initialize(float x_right, float x_left, float y) {
	pos_right_x_	= x_right	+ RECT;
	pos_left_x_		= x_left	+ RECT;
	pos_y_			= y			+ RECT;

	scale_right_	= 1.0f;
	scale_left_		= 1.0f;

	isFinSmaller	= true;
}

void SelectArrows::LoadAssets() {
	sp_right_		= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::ARROW_R.c_str());
	sp_left_		= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::ARROW_L.c_str());
}

void SelectArrows::LoadAssets(DX9::SPRITE right, DX9::SPRITE left) {
	sp_right_		= right;
	sp_left_		= left;
}

bool SelectArrows::Update(const int index) {
	input_ =	Press.RightKey(index)	? AL_RIGHT	: 
				Press.LeftKey(index)	? AL_LEFT	: input_;

	if (input_ == AL_NONE)
		return false;

	(input_ == AL_RIGHT) ? Animations(scale_right_) : Animations(scale_left_);
	(input_ == AL_RIGHT) ? GetSmaller(scale_left_)  : GetSmaller(scale_right_);

	return true;
}

void SelectArrows::Render(float alpha) {
	DX9::SpriteBatch->Draw(
		sp_right_.Get(),
		DirectX::XMFLOAT3(pos_right_x_, pos_y_, (int)US2D::Layer::GENERIC::UI_ARROW),
		nullptr,
		DX9::Colors::RGBA(255, 255, 255, alpha),
		DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
		DirectX::XMFLOAT3(RECT, RECT, 0.0f),
		DirectX::SimpleMath::Vector2::One * scale_right_
	);
	
	DX9::SpriteBatch->Draw(
		sp_left_.Get(),
		DirectX::XMFLOAT3(pos_left_x_, pos_y_, (int)US2D::Layer::GENERIC::UI_ARROW),
		nullptr,
		DX9::Colors::RGBA(255, 255, 255, alpha),
		DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
		DirectX::XMFLOAT3(RECT, RECT, 0.0f),
		DirectX::SimpleMath::Vector2::One * scale_left_
	);

	DX9::SpriteBatch->ResetTransform();
}

void SelectArrows::Animations(float& scale) {
	isFinBigger		= isFinSmaller	? (scale == SCALE_MAX)	: true;
	isFinSmaller	= isFinBigger	? (scale == 1.0f)		: true;

	if (!isFinBigger && isFinSmaller)
		GetBigger(scale);
	
	if ((isFinBigger && !isFinSmaller))
		GetSmaller(scale);

	input_			= (isFinBigger && isFinSmaller) ? AL_NONE : input_;
}