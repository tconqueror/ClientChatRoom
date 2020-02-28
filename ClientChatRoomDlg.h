
// ClientChatRoomDlg.h : header file
//

#pragma once
#pragma comment(lib, "ws2_32.lib")
//#pragma comment(lib, "ntdll.lib")
#include <mstcpip.h>
#include <WinSock2.h>
#include <ip2string.h>
#include <comdef.h>
#include "ClientConnect.h"
// CClientChatRoomDlg dialog
class CClientChatRoomDlg : public CDialogEx
{
// Construction
public:
	CClientChatRoomDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENTCHATROOM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CEdit room;
	CEdit message;
	CEdit ip;
	CEdit port;
	void cnt();
	void dcnt();
	bool status = true;
	void AppendText(CString msg);
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	void SetStatus(bool st);
	bool GetStatus();
	void ShowMessage(char* pos);
	void ShowMessage(CString cs);
	ClientConnect* clc;
};
