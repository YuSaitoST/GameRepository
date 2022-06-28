/**
 * @file UIPosition.h
 * @brief UIの座標管理クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_ConstStrages/US2DLayer.h"
#include "_Classes/_LoadCSV/LoadCSV.h"

namespace US2D {

	class Pos {
	private:
		struct TITLE {
			float LeftArrowX;
			float RightArrowX;
			float ArrowY;
			float TextX;
			float TextY[2];
		};

		struct LOBBY {
			float ARROW_L_X[4];
			float ARROW_R_X[4];
			float ARROW_Y;
			float PICON_X[4];
			float PICON_Y;
			float TEAM_COL_X[4];
			float TEAM_COL_Y;
			float INPUT_X[4];
			float INPUT_Y;
			float ENTRY_X[4];
			float ENTRY_Y;
			float VIEW_X;
			float VIEW_Y;
			float VIEW_W;
			float VIEW_H;
		};

		struct MAIN {
			DirectX::XMFLOAT3 LIFEICON_LPOS[4];
			int LIFEICON_SIZE;
			DirectX::XMFLOAT2 TIMER;
		};

		struct RESULT {
			float NUMBER_POS_X;
			float NUMBER_POS_Y;
			float NUMBER_RECT_X;
			float NUMBER_RECT_Y;
			int NUMBER_MAX;
			float PLAYER_POS_X;
			float PLAYER_POS_Y;
			float PLAYER_RECT_X;
			float PLAYER_RECT_Y;
			int PLAYER_MAX;
			float WINNER_A_X;
			float WINNER_B_X;
			float WINNERNAME_SPACE;
		};

	public:
		static Pos& Get() { 
			static Pos instance; 
			return instance; 
		}

		void Initialize();

		inline TITLE TitleParam() const { return title_; }
		inline LOBBY LobbyParam() const { return lobby_; }
		inline MAIN	MainParam() const { return main_; }
		inline RESULT ResultParam()	const { return result_; }

	private:
		Pos() {}
		virtual ~Pos() {}

		TITLE title_;
		LOBBY lobby_;
		MAIN main_;
		RESULT result_;
	};

}  //namespace US2D