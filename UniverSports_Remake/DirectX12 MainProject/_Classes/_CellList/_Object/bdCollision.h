#pragma once

#include "Base/pch.h"

using namespace DirectX;

enum COLLI_TYPE{ SPHRER, ORIENTEDBOX, NONE_COLLI_TYPE };

class bdCollision {
public:
	bdCollision(COLLI_TYPE collision) { type_ = collision; }
	virtual ~bdCollision() {}

	void SetPosition(SimpleMath::Vector3 pos) { (type_ == SPHRER) ? sph_.Center = pos : (type_ == ORIENTEDBOX) ? box_.Center = pos : XMFLOAT3(0.0f, 0.0f, 0.0f); }

	void SetColli(BoundingOrientedBox bound) { box_ = bound; }
	void SetColli(BoundingSphere bound) { sph_ = bound; }
	void SetColliScale(float scale) { sph_.Radius *= scale; }

	BoundingOrientedBox GetBoundingBox() const { return box_; }
	BoundingSphere GetBoundingSph() const { return sph_; }
	COLLI_TYPE GetType() const { return type_; }
	
private:
	COLLI_TYPE type_;
	BoundingSphere sph_;
	BoundingOrientedBox box_;
};