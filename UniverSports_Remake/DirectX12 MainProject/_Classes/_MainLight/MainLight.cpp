#include "MainLight.h"

/**
* @brief ƒ‰ƒCƒg‚Ì“o˜^
*/
void MainLight::Register() {
	D3DLIGHT9 light_;
	light_.Type			= D3DLIGHT_DIRECTIONAL;
	light_.Diffuse		= DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
	light_.Specular		= DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
	light_.Ambient		= DX9::Colors::Value(0.75f, 1.0f, 1.0f, 1.0f);
	light_.Direction	= DX9::VectorSet(0.0f, -1.0f, 1.0f);
	DXTK->Direct3D9->SetLight(0, light_);
	DXTK->Direct3D9->LightEnable(0, true);
}