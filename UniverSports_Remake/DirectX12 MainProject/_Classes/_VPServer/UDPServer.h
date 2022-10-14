/**
 * @file UDPServer.h
 * @brief VP用UDP通信サーバークラス
 * @author 齋藤優宇
 * @date 2021/08/22
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------

#include "VPServer.h"


class UDPServer : public VPServer {
public:
	UDPServer() {}
	virtual ~UDPServer() {}

	/**
	* @brief UDP通信の準備
	* @param ipAddress 取得したIPアドレスを格納する
	* @return エラーコード { 0...正常終了 -1...ソケット生成失敗 -2...バインド失敗 }
	*/
	virtual int Initialize() override {
		sockaddr_in addr;
		u_long		val		= 1;
		ip_mreq		mreq;
		
		WSAStartUp();

		char hostname[256];
		gethostname(hostname, sizeof(hostname));
		IN_ADDR inaddr;
		memcpy(&inaddr, gethostbyname(hostname)->h_addr_list[0], 4);
		char ip[256];
		strcpy(ip, inet_ntoa(inaddr));

		AddrSetting(addr, AF_INET, INADDR_ANY);

		socket_ = CreateSocket(addr.sin_family, SOCK_DGRAM, 0);
		if (socket_ == INVALID_SOCKET) {
			WSACleanUp();
			return VPERR_CREATE_SOCKET;
		}

		if (Bind(socket_, addr) == SOCKET_ERROR) {
			WSACleanUp();
			return VPERR_BIND;
		}

		ioctlsocket(socket_, FIONBIO, &val);

		memset(&mreq, 0, sizeof(mreq));
		mreq.imr_interface.S_un.S_addr = INADDR_ANY;
		mreq.imr_multiaddr.S_un.S_addr = inet_addr(ip);
		if (setsockopt(socket_, IPPROTO_IP, IP_MULTICAST_IF, (char*)&mreq, sizeof(mreq)) != 0) {
			WSACleanUp();
			return VPERR_SOCK_OPTION;
		}

		return VPERR_SAFE;
	}

	virtual void Send(std::string sendData) override {

	}

	/**
	* @brief 受信
	* @param recvData 受信データを入れる変数
	*/
	virtual std::string Recv() override {
		char buffer[256]{};
		int count = recv(socket_, buffer, sizeof(buffer), 0);
		if (count < 6) {
			return "";
		}
		return std::string(buffer);
	}
};