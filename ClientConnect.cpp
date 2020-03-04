#include "pch.h"
#include "ClientConnect.h"
#include "resource.h"
#include "ClientChatRoomDlg.h"

ClientConnect::ClientConnect(CClientChatRoomDlg* dlg)
{
	clientDlg = dlg;
}

ClientConnect::~ClientConnect()
{
	closesocket(s);
	WSACleanup();
	clientDlg->SetStatus (true);
	clientDlg->GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	clientDlg->GetDlgItem(IDC_BUTTON1)->SetWindowTextW(L"Connect");
	clientDlg->ShowMessage(L"Disconnected");
}

void ClientConnect::Start(CString addr, CString port)
{
	int i_port = _ttoi(port);
	_bstr_t b(addr);
	char* c = b;
	//
	if (WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		CString errcode;
		errcode.Format(_T("%d"), WSAGetLastError());
		AfxMessageBox(L"WSAStartup " + errcode);
		return;
	}
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		CString errcode;
		errcode.Format(_T("%d"), WSAGetLastError());
		AfxMessageBox(L"CreateSocket " + errcode);
		return;
	}

	server.sin_addr.s_addr = inet_addr(c);
	server.sin_family = AF_INET;
	server.sin_port = htons(i_port);
	if (connect(s, (struct sockaddr*) & server, sizeof(server)))
	{
		CString errcode;
		errcode.Format(_T("%d"), WSAGetLastError());
		AfxMessageBox(L"Connect " + errcode);
		return;
	}
	clientDlg->SetStatus(false);
	clientDlg->GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	clientDlg->GetDlgItem(IDC_BUTTON1)->SetWindowTextW(L"Disconnect");
	clientDlg->ShowMessage(L"Connect successfully to " + addr + L":" + port + L"\n");
	int recv_size = 0;
	char buf[10000];
	while ((recv_size = recv(s, buf, 9998, 0)) != SOCKET_ERROR)
	{
		buf[recv_size] = '\0';
		buf[recv_size + 1] = '\0';
		WCHAR* pwchar=reinterpret_cast<WCHAR*>(buf);
		CString cstemp(pwchar);
		clientDlg->ShowMessage(cstemp);
	}
	clientDlg->ShowMessage(L"Server stopped");
	clientDlg->OnBnClickedButton1();
}

void ClientConnect::SendData(CString msg)
{
	const char* buf = reinterpret_cast<const char*> (msg.GetBuffer());
	char x[10000] = { 0 };
	memcpy_s(x, 9998, buf, 9998);
	msg.ReleaseBuffer();
	if ((send(s, x, msg.GetLength() * 2, 0)) == 0)
	{
		CString errcode;
		errcode.Format(_T("%d"), WSAGetLastError());
		AfxMessageBox(L"Send " + errcode);
		return;
	}
	clientDlg->GetDlgItem(IDC_EDIT4)->SetWindowTextW(L"");
}
