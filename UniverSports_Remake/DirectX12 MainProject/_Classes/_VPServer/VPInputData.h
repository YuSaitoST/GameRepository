/**
 * @file VPInputData.h
 * @brief VP用入力データ変換
 * @author 齋藤優宇
 * @date 2021/08/22
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include <string>

namespace VPInput {

	/*
	* @brief 入力情報
	*/
	struct VPInpSet {
		int			ID				: 3;
		int			BUTTON_ID		: 3;
		bool		PRESS			: 1;
		float		X;
		float		Y;
		std::string INPUT_PATTERN;
	};

	/*
	* @brief 受け取った入力情報を変換する
	* @param recvData 入力情報
	* @return キー入力データ
	*/
	inline VPInpSet GetInputData(std::string recvData) {
		std::string data(recvData);
		VPInpSet	input{};

		if (data.empty()) {
			input.ID			= 0;
			input.BUTTON_ID		= 0;
			input.PRESS			= false;
			input.X				= 0.0;
			input.Y				= 0.0f;
			input.INPUT_PATTERN = "N";
			return input;
		}

		// プレイヤーIDの取得
		input.ID = std::atoi(data.substr(0, 1).c_str());

		// 形式文字の取得
		input.INPUT_PATTERN = data.substr(2, 1);
		data.erase(0, 4);

		// 形式ごとのパラメータ取得
		if (input.INPUT_PATTERN == "B") {
			input.BUTTON_ID = std::atoi(data.substr(0, 1).c_str());
			input.PRESS		= (bool)std::atoi(data.substr(2, 1).c_str());
		}
		else if (input.INPUT_PATTERN == "S") {
			int	pos = data.find(" ");
			input.X = std::stof(data.substr(0, pos).c_str());

			data.erase(0, pos + 1);

			input.Y = std::stof(data.substr(0, data.find(" ")).c_str());
		}

		data.erase();

		return input;
	}
}