
// ClientChatRoomDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ClientChatRoom.h"
#include "ClientChatRoomDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientChatRoomDlg dialog



CClientChatRoomDlg::CClientChatRoomDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLIENTCHATROOM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientChatRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, room);
	DDX_Control(pDX, IDC_EDIT4, message);
	DDX_Control(pDX, IDC_EDIT1, ip);
	DDX_Control(pDX, IDC_EDIT2, port);
}

BEGIN_MESSAGE_MAP(CClientChatRoomDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CClientChatRoomDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClientChatRoomDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CClientChatRoomDlg message handlers

BOOL CClientChatRoomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientChatRoomDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientChatRoomDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientChatRoomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CClientChatRoomDlg::cnt()
{
	if (ip.GetWindowTextLengthW() == 0)
	{
		AfxMessageBox(L"You must pass 1 IP address!");
		return;
	}
	CString r_ip;
	ip.GetWindowTextW(r_ip);
	CString r_port;
	if (port.GetWindowTextLengthW() == 0)
	{
		AfxMessageBox(L"You must pass 1 port");
		return;
	}
	port.GetWindowTextW(r_port);
	clc = new ClientConnect(this);
	clc->Start(r_ip, r_port);
}

void CClientChatRoomDlg::dcnt()
{
	delete(clc);
}

void CClientChatRoomDlg::OnBnClickedButton1()
{
	if (status)
	{
		CClientChatRoomDlg::cnt();
		return;
	}
	CClientChatRoomDlg::dcnt();
}


void CClientChatRoomDlg::OnBnClickedButton2()
{
	CString s_msg;
	if (message.GetWindowTextLengthW() == 0)
		return;
	message.GetWindowTextW(s_msg);
	clc->SendData(s_msg);
}

void CClientChatRoomDlg::SetStatus(bool st)
{
	status = st;
}

bool CClientChatRoomDlg::GetStatus()
{
	return status;
}

void CClientChatRoomDlg::ShowMessage(char* pos)
{
	CString* msg = reinterpret_cast<CString*> (pos);
	CString strline;
	strline.Format(_T("%s\r\n"), *msg);
	AppendText(strline);
}

void CClientChatRoomDlg::ShowMessage(CString cs)
{
	CString strline;
	strline.Format(_T("%s\r\n"), cs);
	AppendText(strline);
}

void CClientChatRoomDlg::AppendText(CString msg)
{
	int len = room.GetWindowTextLengthW();
	room.SetSel(len, len);
	room.ReplaceSel(msg);
}

