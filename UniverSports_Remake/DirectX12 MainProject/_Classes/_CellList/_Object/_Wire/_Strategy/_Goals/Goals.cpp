#include "Goals.h"
#include "_Classes/_CellList/_Object/_Wire/ObjWire.h"

/**
 * @brief �X�V
 * @param wire ���C���[���g
*/
void Goals::Update(ObjWire* wire) {
	//�Փ˔���
	wire->HitAction(wire->GetHitObject());
}