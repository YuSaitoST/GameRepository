/**
 * @file VPServer.h
 * @brief VP用ソケット通信クラス
 * @author 齋藤優宇
 * @date 2021/08/22
 */

#pragma once

#pragma comment(lib, "Ws2_32.lib")

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include <memory>
#include <string>
#include <winsock2.h>
#include <WS2tcpip.h>


#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define VPERR_SAFE			 0
#define VPERR_CREATE_SOCKET -1
#define VPERR_BIND			-2
#define VPERR_SELECT_FUNC	-3
#define VPERR_SOCK_OPTION	-4
#define VPERR_TIMEOUT		-5
#define VPERR_LISTEN		-6
#define VPERR_CONNECT		-7

#define VP_PORTNUMBER		 51234


class VPServer {
public:
	VPServer() : socket_(0) {}
	virtual ~VPServer() {}

	virtual int Initialize() = 0;
	virtual void Send(std::string sendData) = 0;
	virtual std::string Recv() = 0;

	/*
	* @brief IPアドレスを調べ取得する
	* @return IPアドレス
	*/
	inline std::string GetIPAddress() {
		WSAStartUp();

		//ホスト名を取得する
		char hostname[256];
		/*puts(hostname);*/
		gethostname(hostname, sizeof(hostname));

		//ホスト名からIPアドレスを取得する
		HOSTENT* hostend = gethostbyname(hostname);
		IN_ADDR inaddr;
		memcpy(&inaddr, hostend->h_addr_list[0], 4);

		char ip[256];
		strcpy(ip, inet_ntoa(inaddr));
		puts(ip);

		WSACleanup();

		return ip;
	}

	/**
	* @brief 通信を終了する
	*/
	inline void Close() {
		CloseSocket(socket_);
		WSACleanUp();
	}

protected:
	/**
	* @brief WinSock初期化
	*/
	inline void WSAStartUp() {
		/*
			第1引数 :	WINSOCK_VERSION ... 最新のバージョン
						MAKEWORD(n, m)	... バージョンn, m
		*/
		WSAData wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			//WinSock初期化失敗
		}
	}

	/**
	* @param アドレス情報の設定
	* @param addr 設定するアドレス
	* @param family アドレスファミリ
	* @param sinAddr IPアドレス
	*/
	inline void AddrSetting(sockaddr_in& addr, ADDRESS_FAMILY family, ULONG sinAddr) {
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = family;
		addr.sin_port = htons(VP_PORTNUMBER);	// 受信ポート(関数通さぬと正しいホストが開けないみたい)
		addr.sin_addr.S_un.S_addr = sinAddr;				// INADDR_ANY : どのIPからでも通信を受け取る状態にする、受信側はこれで大丈夫
		// or 送信アドレスを固定にする場合
		//addr.sin_addr.S_un.S_addr = inet_addr(/*送信アドレス*/"127.0.0.1");
	}

	/**
	* @brief ソケット生成
	* @param family 要求するアドレス・ドメイン { AF_INET(IPv4), AF_INET6, AF_UNIX, AF_RAW }
	* @param type 通信方法 { SOCK_STREAM(TCP), SOCK_DGRAM(UDP), SOCK_RAW }
	* @param protocol プロトコル
	*/
	inline SOCKET CreateSocket(ADDRESS_FAMILY family, int type, int protocol) {
		return socket(family, type, protocol);
	}

	/**
	* @brief ソケットにアドレスを割り当てる
	* @param socket ソケット
	* @param addr アドレス情報
	*/
	inline int Bind(SOCKET socket, sockaddr_in addr) {
		return bind(socket, (sockaddr*)&addr, sizeof(addr));
	}

	/**
	* @brief ソケットの破棄
	* @param socket 破棄するソケット
	*/
	inline void CloseSocket(SOCKET socket) {
		closesocket(socket);
	}

	/**
	* @brief WinSockの解放
	*/
	inline void WSACleanUp() {
		//初期化時に読み込まれたDLLがアンロードされる
		WSACleanup();
	}

	SOCKET socket_;
};
