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
	inline void ResetCountTime() { time_ = max_; };

	/**
	* @brief 今の経過時間を返す
	* @return 経過時間
	*/
	inline float NowTime() const { return time_; };

	/**
	* @brief カウントを開始したかを返す
	* @return カウント開始前ならtrue　カウント中ならfalse
	*/
	inline bool NotYetCounted() const { return (time_ == max_); }

	/**
	* @brief タイマーが終了したかを返す
	* @return タイマーの終了状態
	*/
	inline bool TimeOut() const { return (time_ <= 0.0f); };

private:
	//! タイマーの最大値
	float max_;

	//! 経過時間
	float time_;
};