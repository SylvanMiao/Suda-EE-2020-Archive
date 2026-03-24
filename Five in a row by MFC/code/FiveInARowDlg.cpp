
// FiveInARowDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "FiveInARow.h"
#include "FiveInARowDlg.h"
#include "afxdialogex.h"
#include "mmsystem.h"
#include "CChessManager.h"
#pragma comment(lib, "winmm.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int losetime = 5;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedBitmapAbout();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_STN_CLICKED(IDB_BITMAP_ABOUT, &CAboutDlg::OnStnClickedBitmapAbout)
END_MESSAGE_MAP()


// CFiveInARowDlg 对话框



CFiveInARowDlg::CFiveInARowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FIVEINAROW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFiveInARowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFiveInARowDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONUP()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CFiveInARowDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFiveInARowDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CFiveInARowDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CFiveInARowDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CFiveInARowDlg::OnBnClickedButton5)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CFiveInARowDlg::OnDtnDatetimechangeDatetimepicker1)
	ON_BN_CLICKED(IDC_RADIO2, &CFiveInARowDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &CFiveInARowDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &CFiveInARowDlg::OnBnClickedRadio3)
END_MESSAGE_MAP()


// CFiveInARowDlg 消息处理程序

BOOL CFiveInARowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	PlaySound(MAKEINTRESOURCE( IDR_WAVE1), AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	SetWindowPos(NULL, 0, 0, 1024, 768, SWP_NOZORDER | SWP_NOMOVE);
	m_FontTimer.CreatePointFont(250, "Segoe UI Semibold", NULL);
	m_FontOver.CreatePointFont(1666, "微软雅黑", NULL);
	m_bState = false;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFiveInARowDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFiveInARowDlg::OnPaint()
{
	
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标 
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CBitmap bmp;
		BITMAP bm;
		bmp.LoadBitmap(IDB_BITMAP_BK);
		bmp.GetObject(sizeof(BITMAP), &bm);
		CDC MemDC;
		MemDC.CreateCompatibleDC(&dc);
		CBitmap* pOldBitmap = MemDC.SelectObject(&bmp);
		dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);
		MemDC.SelectObject(pOldBitmap);
		m_Manager.Show(&dc);
		CDialogEx::OnPaint();
	}

}
void CFiveInARowDlg::OnLButtonUp(UINT nFlags, CPoint point) {

	if (NewGame(point.x, point.y))
		return;
	    
	if (About(point.x, point.y))
		return;
	
	if (!m_bState) {
		AfxMessageBox("请选择“开始”按钮开始新的游戏,按Esc键退出游戏!");
		return;
	}
	
	int r = m_Manager.Add(point.x, point.y);

		
	if (r == 0) {
		
		if (m_iTime >= losetime)
		{
			KillTimer(1);
			CString csTemp;
			csTemp.Format("已超时");
			m_bState = false;
			CClientDC dc(this);
			CFont* pOldFont = dc.SelectObject(&m_FontOver);
			int OldBkMode = dc.GetBkMode();
			COLORREF OldColor, NewColor1 = RGB(60, 60, 60), NewColor2 = RGB(250, 50, 50);
			dc.SetBkMode(TRANSPARENT);
			OldColor = dc.SetTextColor(NewColor1);
			dc.TextOut(158, 208, csTemp);
			dc.SetTextColor(NewColor2);
			dc.TextOut(150, 200, csTemp);
			dc.SetTextColor(OldColor);
			dc.SetBkMode(OldBkMode);
			dc.SelectObject(pOldFont);
		}
		CClientDC dc(this);
		m_Manager.Show(&dc);
		
		m_iTime = 0;
		
		if (m_Manager.GameOver()) {
			KillTimer(1);
			CString csTemp;
			if (m_Manager.GetWinner() == WHITE)
				csTemp.Format("白方胜！");
			else
				csTemp.Format("黑方胜！");
			m_bState = false;
			CClientDC dc(this);
			CFont* pOldFont = dc.SelectObject(&m_FontOver);
			int OldBkMode = dc.GetBkMode();
			COLORREF OldColor, NewColor1 = RGB(60, 60, 60), NewColor2 = RGB(250, 50, 50);
			dc.SetBkMode(TRANSPARENT);
			OldColor = dc.SetTextColor(NewColor1);
			dc.TextOut(158, 208, csTemp);
			dc.SetTextColor(NewColor2);
			dc.TextOut(150, 200, csTemp);
			dc.SetTextColor(OldColor);
			dc.SetBkMode(OldBkMode);
			dc.SelectObject(pOldFont);
		}
		
	}
	if (r == 1)
		AfxMessageBox("请在棋盘交叉点落子！");
	else if (r == 2)
		AfxMessageBox("不可以重复落子！");

	CDialogEx::OnLButtonUp(nFlags, point);
	CClientDC dc(this);                                            
	CFont* pOldFont;
	pOldFont = dc.SelectObject(&m_FontTimer);
	if (m_Manager.GameOver()) {
		if (m_Manager.GetWinner() == WHITE)
			black++;
		else
			white++;
	}
	CString winhz, winbz;
	COLORREF OldColor, NewColor = RGB(128, 128, 129);
	OldColor = dc.SetTextColor(NewColor);
	do {
		winhz.Format("白方胜场：%01d", black);
		winbz.Format("黑方胜场：%01d", white);
		dc.TextOut(750,680,winhz);
		dc.TextOut(400,680, winbz);
		break;
	} while (black < 100);
	dc.SetTextColor(OldColor);
	dc.SelectObject(pOldFont);                                     


}
bool CFiveInARowDlg::NewGame(int x, int y) {
	int x0 = 35, y0 = 150, x1 = 200, y1 = 185;
	if ((x >= x0 && x <= x1) && (y >= y0 && y <= y1)) {
		m_Manager.NewGame();
		Invalidate();
		m_iTime = 0;
		SetTimer(1, 1000, NULL);
		m_bState = true;
		return true;
	}
	return false;
}
bool CFiveInARowDlg::About(int x, int y) {
	int x0 = 35, y0 = 70, x1 = 200, y1 = 95;
	if ((x >= x0 && x <= x1) && (y >= y0 && y <= y1)) {
		CAboutDlg dlg;
		dlg.DoModal();
		CString temp_value = ("");
		temp_value.Format(("%d"), losetime);
		AfxMessageBox("限定落子秒数为： " + temp_value);
		return true;
		
	}
	return false;
}
void CFiveInARowDlg::OnTimer(UINT_PTR nIDEvent) {
	switch (nIDEvent) {
	case 1: {
		CClientDC dc(this);
		CFont* pOldFont;
		pOldFont = dc.SelectObject(&m_FontTimer);
		m_iTime++;
		CString csTemp;
		csTemp.Format(" %04d", m_iTime);
		COLORREF OldColor, NewColor = RGB(150, 50, 50);
		OldColor = dc.SetTextColor(NewColor);
		dc.TextOut(725, 20, csTemp);
		dc.SetTextColor(OldColor);
		dc.SelectObject(pOldFont);
		break;
	}
	}
	CDialogEx::OnTimer(nIDEvent);
}





//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFiveInARowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAboutDlg::OnStnClickedBitmapAbout()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CFiveInARowDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int a;
	a = m_iTime;
	KillTimer(1);
}


void CFiveInARowDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	SetTimer(1, 1000, NULL);
}


void CFiveInARowDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	losetime++;
}


void CFiveInARowDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	losetime--;
}


void CFiveInARowDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Manager.regret();
	m_iTime = 0;
	Invalidate();

	
}


void CFiveInARowDlg::OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CFiveInARowDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	CChessManager::gamemodechange();
}


void CFiveInARowDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	CChessManager::gamemodechange0();
}


void CFiveInARowDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	CChessManager::gamemodechange1();
}
