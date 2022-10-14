/**
 * @file VPManager.h
 * @brief VP用サーバー管理クラス
 * @author 齋藤優宇
 * @date 2021/08/22
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include <stdio.h>
#include "VPTransceiverTool.h"
#include "TCPServer.h"
#include "UDPServer.h"

#define TCP_CONNECT_OK  1
#define TCP_CONNECT_NOK 0

class VPManager {
public:
	VPManager() { udp_server_ = std::make_unique<UDPServer>(); }
	virtual ~VPManager() { udp_server_->Close(); }

	/*
	* @brief TCPによる初回接続
	* @param playerID 接続を試みるプレイヤーのID
	* @return 接続状態メッセージ
	*/
	inline int TCP_Connection(int playerID) {
		std::string					sendData	= VPInput::CreatedSendGameMassage(playerID, titleName);
		std::unique_ptr<TCPServer>	tcp_server	= std::make_unique<TCPServer>();
		int							err			= tcp_server->Initialize();

		switch (err) {
			case VPERR_SAFE			 : 
				tcp_server->Send(sendData);
				tcp_server->Close();
				return TCP_CONNECT_OK;
			case VPERR_CREATE_SOCKET : 
			case VPERR_BIND			 : 
			case VPERR_SELECT_FUNC	 : 
			case VPERR_TIMEOUT		 : 
			case VPERR_LISTEN		 : 
				return TCP_CONNECT_NOK;
		}
	}

	/*
	* @brief UDP通信の初期化
	*/
	inline void UDP_Initialize() { 
		const int err = udp_server_->Initialize();
	}

	/*
	* @brief UDP通信によるデータ受取
	* @return 受信データ
	*/
	inline std::string UDP_Receive() { return udp_server_->Recv(); }

	/*
	* @brief IPアドレスの取得
	* @return IPアドレス
	*/
	inline std::string GetIPAddress() { return udp_server_->GetIPAddress(); }

private:
	const wchar_t* titleName = L"ユニバースポーツ";

	std::unique_ptr<UDPServer>	udp_server_;
};