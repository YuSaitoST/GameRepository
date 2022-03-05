#include "DemoPlay.h"

DemoPlay::DemoPlay(SimpleMath::Vector3 pos, float scale, float playBack) {
	mv_demo_	= new MoviePlayer(pos, scale);
	timer_		= new OriTimer(playBack);
	isDisplay_	= false;
}

DemoPlay::~DemoPlay() {
	delete timer_;
	delete mv_demo_;
}

void DemoPlay::LoadAssets() {
	mv_demo_->LoadAsset(L"_Movies\\DemoPlay.wmv");
}

void DemoPlay::Update(const float deltaTime) {
	timer_->Update(deltaTime);

	if (timer_->TimeOut() && !isDisplay_)
		mv_demo_->Play();

	isDisplay_ = timer_->TimeOut();
}

void DemoPlay::Render() {
	if (isDisplay_)
		mv_demo_->Render();
}