
// Shutdown_v2Dlg.h: 헤더 파일
//

#pragma once


// CShutdownv2Dlg 대화 상자
class CShutdownv2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CShutdownv2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHUTDOWN_V2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonMain();
	CEdit m_Time;
	afx_msg void OnBnClickedButtonMain2();
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonMain3();
	afx_msg void OnEnChangeEditFHour();
	CEdit mFhour;
	CEdit mFmin;
	CEdit mFsec;
};
