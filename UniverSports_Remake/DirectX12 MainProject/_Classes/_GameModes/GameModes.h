/**
 * @file GameModes.h
 * @brief ゲームモードクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 /**
  * @enum GAMEMODE
  * 実装されているゲームモード
  */
enum GAMEMODE { DODGE_BALL_NOMAL, DODGE_BALL_2ON2, HAND_BALL, BILLIARDS, NONE_GAMEMODE };

class GameModes {
public:
	GameModes() : GameMode_(NONE_GAMEMODE) {}
	virtual ~GameModes() {}

	/**
	* @brief 選択したゲームモードを設定する
	* @param gameMode 選択したゲームモード
	*/
	inline void SelectMode(GAMEMODE gameMode) { GameMode_ = gameMode; }

	/**
	* @brief シングルスのゲームモードかを返す
	* @return シングルスのゲームモードならtrue　異なるならfalse
	*/
	inline bool isSINGLES_GAME() const { return !isDODGEBALL_2ON2(); }

	/**
	* @brief ゴールを用いるゲームモードかを返す
	* @return ゴールを用いるゲームモードならtrue　異なるならfalse
	*/
	inline bool isGAMES_WITH_GOALS() const { return isHANDBALL() || isBILLIARDS(); }

	/**
	* @brief ドッジボール系のモードかを返す
	* @return ドッジボール系のモードならtrue　異なるならfalse
	*/
	inline bool isDODGEBALL() const { return isDODGEBALL_NOMAL() || isDODGEBALL_2ON2();	}

	/**
	* @brief ドッジボールモードかを返す
	* @return ドッジボールモードならtrue　異なるならfalse
	*/
	inline bool isDODGEBALL_NOMAL() const { return GameMode_ == DODGE_BALL_NOMAL;}

	/**
	* @brief ドッジボール2on2モードかを返す
	* @return ドッジボール2on2モードならtrue　異なるならfalse
	*/
	inline bool isDODGEBALL_2ON2() const { return GameMode_ == DODGE_BALL_2ON2;	}

	/**
	* @brief ハンドボールモードかを返す
	* @return ハンドボールモードならtrue　異なるならfalse
	*/
	inline bool isHANDBALL() const { return GameMode_ == HAND_BALL; }

	/**
	* @brief ビリヤードモードかを返す
	* @return ビリヤードモードならtrue　異なるならfalse
	*/
	inline bool isBILLIARDS() const { return GameMode_ == BILLIARDS; }

	/**
	* @brief モードの決定状態を返す
	* @return 決定されていなければtrue
	*/
	inline bool isNotDecision() const { return GameMode_ == NONE_GAMEMODE; }

	/**
	* @brief 今プレイしているモードを返す
	* @return 進行中のモード
	*/
	inline GAMEMODE SelectionMode() const { return GameMode_; }

private:
	//! ゲームモードを保存する変数
	GAMEMODE GameMode_;
};