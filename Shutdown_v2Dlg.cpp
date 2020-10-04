
// Shutdown_v2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Shutdown_v2.h"
#include "Shutdown_v2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CShutdownv2Dlg 대화 상자



CShutdownv2Dlg::CShutdownv2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHUTDOWN_V2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShutdownv2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MAIN, m_Time);
	DDX_Control(pDX, IDC_EDIT_F_HOUR, mFhour);
	DDX_Control(pDX, IDC_EDIT_F_MIN, mFmin);
	DDX_Control(pDX, IDC_EDIT_F_SEC, mFsec);
}

BEGIN_MESSAGE_MAP(CShutdownv2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MAIN, &CShutdownv2Dlg::OnBnClickedButtonMain)
	ON_BN_CLICKED(IDC_BUTTON_MAIN2, &CShutdownv2Dlg::OnBnClickedButtonMain2)
	ON_BN_CLICKED(IDC_BUTTON_MAIN3, &CShutdownv2Dlg::OnBnClickedButtonMain3)
END_MESSAGE_MAP()


// CShutdownv2Dlg 메시지 처리기

BOOL CShutdownv2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CShutdownv2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CStringToChar(CString str, char** ptr)
{
	int n = str.GetLength();
	*ptr = new char[n + 1];
	WideCharToMultiByte(CP_ACP, 0, str, -1, *ptr, n + 1, NULL, NULL);
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CShutdownv2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CShutdownv2Dlg::OnBnClickedButtonMain()
{
	int time;
	CString temp,str;
	char* ptr;

	m_Time.GetWindowTextW(temp);
	time = _ttoi(temp);
	
	str.Format(_T("cmd.exe /K shutdown /s /t %d"), time);
	CStringToChar(str, &ptr);
	//system(ptr);
	WinExec("cmd.exe /K shutdown /a", SW_HIDE);
	Sleep(100);
	WinExec(ptr, SW_HIDE);
	Sleep(100);
	WinExec(ptr, SW_HIDE);

	if (ptr != NULL)delete ptr;
	OnOK();
}


void CShutdownv2Dlg::OnBnClickedButtonMain2()
{
	system("shutdown /a");
}

BOOL CShutdownv2Dlg::PreTranslateMessage(MSG* pMsg)
{
	// 에디트컨트롤에서 WM_KEYDOWN 발생됐는가? 체크
	if (pMsg->message == WM_KEYDOWN && pMsg->hwnd == GetDlgItem(IDC_EDIT_MAIN)->m_hWnd) {// 최상단 초단위 설정 엔터
		// 눌러진 키가 엔터키인가?
		if (pMsg->wParam == VK_RETURN) {
			// 엔터키 입력 후 하고자 하는 기능 코드 추가.
			OnBnClickedButtonMain();
			return TRUE;
		}
	}
	if (pMsg->message == WM_KEYDOWN && 
		((pMsg->hwnd == GetDlgItem(IDC_EDIT_F_HOUR)->m_hWnd || 
		(pMsg->hwnd == GetDlgItem(IDC_EDIT_F_MIN)->m_hWnd) || 
		(pMsg->hwnd == GetDlgItem(IDC_EDIT_F_SEC)->m_hWnd)))) {
		// 눌러진 키가 엔터키인가?
		if (pMsg->wParam == VK_RETURN) {
			// 엔터키 입력 후 하고자 하는 기능 코드 추가.
			OnBnClickedButtonMain3();
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CShutdownv2Dlg::OnBnClickedButtonMain3()
{
	int h,m,s,time;
	CString temp, str;
	char* ptr;

	mFhour.GetWindowTextW(temp);
	h = _ttoi(temp);
	mFmin.GetWindowTextW(temp);
	m = _ttoi(temp);
	mFsec.GetWindowTextW(temp);
	s = _ttoi(temp);

	time = h * 3600 + m * 60 + s;

	str.Format(_T("cmd.exe /K shutdown /s /t %d"), time);
	CStringToChar(str, &ptr);
	//system(ptr);
	WinExec("cmd.exe /K shutdown /a", SW_HIDE);
	Sleep(100);
	WinExec(ptr, SW_HIDE);
	Sleep(100);
	WinExec(ptr, SW_HIDE);

	if (ptr != NULL)delete ptr;
	OnOK();
}

