/**
 * @file MainCamera.h
 * @brief カメラクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include"Base/pch.h"
#include"Base/dxtk.h"

//マクロ
#define Camera MainCamera::GetInstance()

class MainCamera {
public:
	MainCamera();
	virtual ~MainCamera() {};

	static MainCamera& GetInstance() {
		static MainCamera _inctance;
		return _inctance;
	}

	void Register();

	/**
	* @brief カメラを返す
	* @return カメラ
	*/
	DX9::CAMERA GetCamera() const { return camera_; };

private:
	DX9::CAMERA camera_;
};