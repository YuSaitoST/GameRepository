#include "EffThrasher.h"
#include "_Classes/_GameController/GameController.h"

EffThrasher::EffThrasher() : EffectBase(THRUSTER_PARAM.TIME_UPDATEPOSITION), usedThrasher_(false) {
	timer_roop_		= std::make_unique<CountTimer>(0.2f);
}

void EffThrasher::Update(const float deltaTime, float rotate_x, Vector3 position, Vector3 direction, float proportion) {
	if (!GameController::GamePlay())
		Stop();

	Set_Position(position);

	TimerCount(deltaTime);
	Play();

	// 座標の更新
	if (isOver()) {
		ResetTime();
		Set_Position(position);
	}
	
	const bool _isUsedThruster = usedThrasher_ && (THRUSTER_PARAM.GAUGE_STOP < proportion);

	// 強出力
	if (_isUsedThruster) {
		timer_roop_->Update(deltaTime);
		if (timer_roop_->TimeOut()) {
			timer_roop_->Reset();
			Set_Position(position);
		}
		Move(-direction * THRUSTER_PARAM.MOVEMENT_NOMAL);
	}
	else
		Move(-direction * THRUSTER_PARAM.MOVEMENT_ACCEL);

	Set_Rotate(Vector3(0.0f, THRUSTER_PARAM.ROTATE_Y, -rotate_x));
	Set_Scale(Vector3::One * THRUSTER_PARAM.SCALE[_isUsedThruster]);
}