/**
 * @file CountTimer.h
 * @brief タイマークラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include <algorithm>

class CountTimer {
public:
	CountTimer(float countTime);
	virtual ~CountTimer() {};

	void Update(const float deltaTime);

	/**
	* @brief タイマーをリセットする
	*/
	void ResetCountTime() { time_ = max_; };

	/**
	* @brief 今の経過時間を返す
	* @return 経過時間
	*/
	float NowTime() const { return time_; };

	/**
	* @brief タイマーが終了したかを返す
	* @return タイマーの終了状態
	*/
	bool TimeOut() const { return (time_ <= 0.0f); };

private:
	float				max_;	//!< タイマーの最大値
	float				time_;	//!< 経過時間
};