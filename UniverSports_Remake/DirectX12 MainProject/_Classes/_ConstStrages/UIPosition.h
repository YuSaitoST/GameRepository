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
			int NUMBER_POS_X;
			int NUMBER_POS_Y;
			int NUMBER_RECT_X;
			int NUMBER_RECT_Y;
			int NUMBER_MAX;

			int PLAYER_POS_X;
			int PLAYER_POS_Y;
			int PLAYER_RECT_X;
			int PLAYER_RECT_Y;
			int PLAYER_MAX;

			int WINNER_A_X;
			int WINNER_B_X;
			int WINNERNAME_SPACE;
		};

	public:
		static Pos& Get() { static Pos instance; return instance; }

		inline TITLE TitleParam() const { return title_; }
		inline LOBBY LobbyParam() const { return lobby_; }
		inline MAIN	MainParam() const { return main_; }
		inline RESULT ResultParam()	const { return result_; }

	private:
		Pos() {
			CSV::Schan(L"_Parameters\\_UI\\TitleUIPosition.csv", "%f,%f,%f,%f,%f,%f",
				&title_.LeftArrowX, &title_.RightArrowX, &title_.ArrowY, &title_.TextX, &title_.TextY[0], &title_.TextY[1]
			);
			CSV::Schan(
				L"_Parameters\\_UI\\LobbyUIPosition.csv",
				"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
				&lobby_.ARROW_L_X[0], &lobby_.ARROW_R_X[0],
				&lobby_.ARROW_L_X[1], &lobby_.ARROW_R_X[1],
				&lobby_.ARROW_L_X[2], &lobby_.ARROW_R_X[2],
				&lobby_.ARROW_L_X[3], &lobby_.ARROW_R_X[3], &lobby_.ARROW_Y,
				&lobby_.PICON_X[0], &lobby_.PICON_X[1], &lobby_.PICON_X[2], &lobby_.PICON_X[3], &lobby_.PICON_Y,
				&lobby_.TEAM_COL_X[0], &lobby_.TEAM_COL_X[1], &lobby_.TEAM_COL_X[2], &lobby_.TEAM_COL_X[3], &lobby_.TEAM_COL_Y,
				&lobby_.INPUT_X[0], &lobby_.INPUT_X[1], &lobby_.INPUT_X[2], &lobby_.INPUT_X[3], &lobby_.INPUT_Y,
				&lobby_.ENTRY_X[0], &lobby_.ENTRY_X[1], &lobby_.ENTRY_X[2], &lobby_.ENTRY_X[3], &lobby_.ENTRY_Y,
				&lobby_.VIEW_X, &lobby_.VIEW_Y, &lobby_.VIEW_W, &lobby_.VIEW_H
			);
			int LeftX, RightX, UpY, DownY;
			CSV::Schan(L"_Parameters\\_UI\\MainUIPosition.csv", "%i,%i,%i,%i,%i,%i,%i", 
				&LeftX, &RightX, &UpY, &DownY, &main_.LIFEICON_SIZE, &main_.TIMER.x, &main_.TIMER.y
			);
			main_.LIFEICON_LPOS[0] = DirectX::XMFLOAT3(LeftX, UpY, 0.0f);
			main_.LIFEICON_LPOS[1] = DirectX::XMFLOAT3(RightX, UpY, 0.0f);
			main_.LIFEICON_LPOS[2] = DirectX::XMFLOAT3(LeftX, DownY, 0.0f);
			main_.LIFEICON_LPOS[3] = DirectX::XMFLOAT3(RightX, DownY, 0.0f);
			CSV::Schan(L"_Parameters\\_UI\\ResultUIPosition.csv", "%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i",
				&result_.NUMBER_POS_X, &result_.NUMBER_POS_Y,
				&result_.NUMBER_RECT_X, &result_.NUMBER_RECT_Y, &result_.NUMBER_MAX,
				&result_.PLAYER_POS_X, &result_.PLAYER_POS_Y,
				&result_.PLAYER_RECT_X, &result_.PLAYER_RECT_Y, &result_.PLAYER_MAX,
				&result_.WINNER_A_X, &result_.WINNER_B_X, &result_.WINNERNAME_SPACE
			);
		}

		TITLE title_;
		LOBBY lobby_;
		MAIN main_;
		RESULT result_;
	};

}  //namespace US2D