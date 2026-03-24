
// FiveInARowDlg.h: 头文件
//

#pragma once
#include "CChessManager.h"
#include "CChess.h"

// CFiveInARowDlg 对话框
class CFiveInARowDlg : public CDialogEx
{
// 构造
	CChessManager m_Manager;
	CChess checkcolor;
	CFont m_FontTimer;
	CFont m_FontOver;
	bool m_bState;
	int black = 0, white = 0;
	
public:
	CFiveInARowDlg(CWnd* pParent = nullptr);	// 标准构造函数
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	bool NewGame(int x, int y);
	bool About(int x, int y);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_iTime;
	int WIN_NUM = 5;
	


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIVEINAROW_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio3();
};
