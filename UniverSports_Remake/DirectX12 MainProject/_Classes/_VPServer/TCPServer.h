/**
 * @file TCPServer.h
 * @brief VP用TCP通信サーバークラス
 * @author 齋藤優宇
 * @date 2021/08/22
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "VPServer.h"


class TCPServer : public VPServer {
private:
	const unsigned int TIME_SEC		= 30;		// タイムアウト時間 (秒単位
	const unsigned int TIME_USEC	= 3000000;	// タイムアウト時間 (マイクロ秒単位

public:
	TCPServer() {}
	virtual ~TCPServer() {}

	/**
	* @brief UDP通信の準備
	* @return エラーコード { 0...正常終了 -1...ソケット生成失敗 -2...バインド失敗 -3...接続失敗}
	*/
	virtual int Initialize() override {
		sockaddr_in addr;
		SOCKET		sockListen;

		//timeval		tv;
		//fd_set		readfds;
		//int			ret_select; 

		//// タイムアウト時間を設定
		//tv.tv_sec	= TIME_SEC;
		//tv.tv_usec	= TIME_USEC;
		

		WSAStartUp();
		AddrSetting(addr, AF_INET, INADDR_ANY);

		sockListen = CreateSocket(addr.sin_family, SOCK_STREAM, 0);
		if (sockListen == INVALID_SOCKET) {
			WSACleanUp();
			return VPERR_CREATE_SOCKET;
		}

		if (Bind(sockListen, addr) == SOCKET_ERROR) {
			WSACleanUp();
			return VPERR_BIND;
		}

		//// 読み込みFD集合を空にする
		//FD_ZERO(&readfds);

		//// 読み込みFD集合にソケットを追加
		//FD_SET(sockListen, &readfds);

		//// selectでreadfdsのどれかが読み込み可能になるまでorタイムアウトまで待つ
		//ret_select = select(sockListen + 1, &readfds, NULL, NULL, &tv);

		//// 戻り値チェック
		//if (ret_select == -1) {
		//	// select関数がエラー
		//	WSACleanUp();
		//	return VPERR_SELECT_FUNC;
		//}
		//else if (ret_select == 0) {
		//	// 読み込み可能になったFDの数が0なのでタイムアウトと判断
		//	WSACleanUp();
		//	return VPERR_TIMEOUT;
		//}

		// これ以降でタイムアウト処理をしたい処理を記述する
		// (正常につながればここに処理が来る)

		if (Listen(sockListen, 5) == SOCKET_ERROR) {
			CloseSocket(sockListen);
			WSACleanUp();
			return VPERR_LISTEN;
		}

		if (Connect(sockListen) == VPERR_CONNECT) {
			return VPERR_CONNECT;
		}

		//// 指定したFDを読み込みFD集合から削除
		//FD_CLR(socket_, &readfds);

		return VPERR_SAFE;
	}

	/**
	* @brief 送信
	* @param sendData 送信データ
	*/
	virtual void Send(std::string sendData) override {
		send(socket_, sendData.c_str(), sizeof(sendData), 0);
	}


	virtual std::string Recv() override {
		return "";
	}

	SOCKET& GetSocket() { return socket_; }

private:
	/**
	* @brief ソケットを接続待ちにする
	*/
	inline int Listen(SOCKET socket, int backlog) {
		return listen(socket, backlog);
	}

	/**
	* @brief クライアントからの接続を待つ
	* @param socket ソケット
	*/
	inline int Connect(SOCKET socket) {
		sockaddr_in client{};
		int			clientlen = sizeof(client);
		char		buf[256];
		memset(buf, 0, sizeof(buf));
		
		try {
			socket_ = accept(socket, (sockaddr*)&client, &clientlen);
		}catch(std::exception e) {
			return VPERR_CONNECT;
		}

		return VPERR_SAFE;
	}
};
