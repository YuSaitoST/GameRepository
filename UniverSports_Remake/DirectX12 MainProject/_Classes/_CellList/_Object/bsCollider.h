#pragma once

#include "Base/pch.h"

using namespace DirectX;

class bsCollider {
public:
	struct Sphere {

	};
	bsCollider() { colli = BoundingSphere{}; };
	virtual ~bsCollider() = default;

	void SetPosition(SimpleMath::Vector3 pos) { colli.Center = pos; };
	void SetColli(BoundingSphere bound) { colli = bound; };
	void SetColliScale(float scale) { colli.Radius* scale; };

	BoundingSphere GetBounding() const { return colli; };

private:
	BoundingSphere colli;
};