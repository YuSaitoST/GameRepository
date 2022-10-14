/**
 * @file VPTransceiverTool.h
 * @brief VP用送受信ツール
 * @author 齋藤優宇
 * @date 2021/08/22
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include <string>
#include <sstream>

namespace VPInput {
	/**
	* @brief 初回の送信データを構築する
	* @param playerID プレイヤーID
	* @param titleName タイトル
	* @return 送信データ
	*/
	inline std::string CreatedSendGameMassage(int playerID, const wchar_t* titleName) {
		// プレイヤーID
		std::stringstream ss_id;
		ss_id << playerID;

		// タイトル名
		std::wstring wstr = titleName;

		// タイトル名を数値に変換
		std::stringstream ss_title;
		for (const auto& item : wstr) {
			ss_title << std::hex << int(item) << " ";
		}

		// 送信データを作る
		std::string sendData = ss_title.str();
		sendData[sendData.length() - 1] = *ss_id.str().c_str();

		return sendData;
	}
}