#pragma once
#include <WinSock2.h>
class CClientChatRoomDlg;
class ClientConnect
{
public:
	ClientConnect::ClientConnect(CClientChatRoomDlg* dlg);
	~ClientConnect();
	void Start(CString addr, CString port);
	void SendData(CString msg);
private:
	WSADATA wsa;
	SOCKET s;
	CClientChatRoomDlg *clientDlg;
	struct sockaddr_in server;
};

