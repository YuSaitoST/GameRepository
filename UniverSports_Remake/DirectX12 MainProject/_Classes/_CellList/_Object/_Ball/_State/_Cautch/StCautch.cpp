#include "StCautch.h"
#include "_Classes/_CellList/ObjectManager.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "_Classes/_CellList/_Object/_Ball/_State/_Shot/StShot.h"
#include "_Classes/_CellList/_Object/_Ball/_State/_Float/StFloat.h"
#include "_Classes/_CellList/_PlayersInstructor/PlayersInstructor.h"
#include "DontDestroyOnLoad.h"

void StCautch::Initialize() {
	myState_ = B_STATE::CAUTCH;
}

void StCautch::Update(ObjBall* ball) {
	if (!ball->IsInPlayerHands()) {
		StShot* shot = new StShot();
		ball->SwitchState(shot);
		return;
	}
	else if (ball->IsBreaked()) {
		ball->FlagResets();
		ball->SetOwnerID(-1);
		std::unique_ptr<StFloat> flo = std::make_unique<StFloat>();
		ball->SwitchState(std::move(flo).get());
		ball->SwitchColor(ObjBall::COLOR_TYPE::DEFAULT_COLOR);
		return;
	}

	//’Ç”ö
	ball->Following(Z_MIN);
}