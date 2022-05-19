#include "Goals.h"
#include "_Classes/_CellList/_Object/_Wire/ObjWire.h"

/**
 * @brief 更新
 * @param wire ワイヤー自身
*/
void Goals::Update(ObjWire* wire) {
	//衝突判定
	wire->HitAction(wire->GetHitObject());
}