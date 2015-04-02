
// ACMNetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NetSet.h"
#include "ACMNet.h"
#include "ACMNetDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum  STATE  { THREAD_EXIT, THREAD_WAIT, THREAD_RUN }  FLAG;
CACMNetDlg *mynet;
CString  cmd;
CWebBrowser2 myweb;
NetHtml   myhtml;

void PrintRP(LPCTSTR txt){     //将txt输出到Response编辑框
	CString res;
	res.Format(_T("Response: %s\r\n"), txt);
	((CEdit *)(mynet->GetDlgItem(IDC_RESPONSE)))->ReplaceSel(res);
}

void PrintLog(LPCTSTR str)   //将log信息输出到Log编辑框
{
	CString log;
	log.Format(_T("%s\r\n"), str);
	((CEdit *)(mynet->GetDlgItem(IDC_LOG)))->ReplaceSel(log);
}

void  GetPage(CString url){
	mynet->GetDlgItem(IDC_RESPONSE)->ShowWindow(SW_HIDE);
	COleVariant noArg;
	myweb.Navigate(url, &noArg, &noArg, &noArg, &noArg);
	myweb.get_Visible();
}

void  GetHtml(CString url){
	CString html;
	if (myweb.IsWindowVisible()){
		myweb.put_Visible(FALSE);
		mynet->GetDlgItem(IDC_RESPONSE)->ShowWindow(SW_SHOW);
	}
	html = myhtml.getURLContext(url);
	mynet->GetDlgItem(IDC_RESPONSE)->SetWindowText(html);
}

void Switch(){
	if (mynet->GetDlgItem(IDC_RESPONSE)->IsWindowVisible()){	
		mynet->GetDlgItem(IDC_RESPONSE)->ShowWindow(SW_HIDE);
		myweb.put_Visible(TRUE);
	}
	else {
		myweb.put_Visible(FALSE);
		mynet->GetDlgItem(IDC_RESPONSE)->ShowWindow(SW_SHOW);
	}
}

void SetDll(CString args){
	mynet->mydll.LoadDll(args);
	if (mynet->mydll.Hinst != NULL){
		PrintLog(_T("加载链接库成功!"));
	}
	else 
		PrintLog(_T("加载链接库失败!"));
}

void Compute(CString equation){
	CString rst;
	int a, b;
	typedef int(*ADDPROC)(int, int);
	ADDPROC Add = (ADDPROC)GetProcAddress(mynet->mydll.Hinst, "add");
	int pos = equation.Find(_T("+"));
	a = _ttoi(equation.Mid(0, pos));
	b = _ttoi(equation.Mid(pos + 1));
	rst.Format(_T("%d + %d = %d"), a, b, Add(a,b));
	PrintRP(rst);
}

void CleanRP()
{
	mynet->GetDlgItem(IDC_RESPONSE)->SetWindowText(_T(""));
}

void   MapTask(){
	int len, i;
	TCHAR c;
	CString Ins;
	static CString args;
	args.Empty();
	len = cmd.GetLength();
	for (i = 0; i < cmd.GetLength(); i++){
		if ((c = cmd.GetAt(i)) != _T(' ')){
			Ins += c;
		}
		else break;
	}
	while (i < cmd.GetLength() && (c = cmd.GetAt(i++)) != _T(' '));
	args = cmd.Mid(i);
	if (Ins.Compare(_T("gethtml")) == 0)
		GetHtml(args);
	else if (Ins.Compare(_T("compute")) == 0)
		Compute(args);
	else if (Ins.Compare(_T("getpage")) == 0)
		GetPage(args);
	else if (Ins.Compare(_T("setdll")) == 0)
		SetDll(args);
	else if (Ins.Compare(_T("switch")) == 0)
		Switch();
	else if (Ins.Compare(_T("cleanrp")) == 0)
		CleanRP();
	else{
		PrintLog(_T("命令未定义"));
	}
}

DWORD WINAPI DEALCMD(LPVOID lpParameter){

	while (TRUE){
		if (FLAG == THREAD_EXIT)
			break;
		else if (FLAG == THREAD_WAIT)
			continue;
		else {
			MapTask();
			FLAG = THREAD_WAIT;
		}

	}
	return 0;
}



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CACMNetDlg 对话框



CACMNetDlg::CACMNetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CACMNetDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_CONN);
}

void CACMNetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMMAND, mycmd);
}

BEGIN_MESSAGE_MAP(CACMNetDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SEND, &CACMNetDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_CANCEL, &CACMNetDlg::OnBnClickedCancel)
	ON_COMMAND(ID_SETTING, &CACMNetDlg::OnSetting)
	ON_COMMAND(ID_SHOWSET, &CACMNetDlg::OnShowset)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CACMNetDlg 消息处理程序

BOOL CACMNetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// TODO:  在此添加额外的初始化代码
	CRect rect;
	mynet = this;
	GetDlgItem(IDC_RESPONSE)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	myweb.Create(NULL, NULL, WS_VISIBLE|WS_CHILD, rect, this, 101);
	//myweb.ShowWindow(SW_HIDE);
	FLAG = THREAD_WAIT;
	if (CreateThread(NULL, NULL, DEALCMD, NULL, NULL, NULL)){
		PrintLog(_T("创建消息处理线程成功!\n"));
	}
	else PrintLog(_T("创建消息处理线程失败"));
	mycmd.ReplaceSel(_T("Command: "));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CACMNetDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CACMNetDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CACMNetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CACMNetDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}


void CACMNetDlg::OnBnClickedSend()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strLine, strText;
	int count=mycmd.GetLineCount();
	int len = mycmd.LineLength(mycmd.LineIndex(count-1));
	mycmd.GetLine(count - 1, strText.GetBuffer(len), len);
	strText.ReleaseBuffer(len);
	strLine.Format(_T("%s"), strText);
	mycmd.ReplaceSel(_T("\r\n\r\nCommand: "));
	mycmd.SetFocus();
	int i;
	for (i = 9;;i++)
	if (strLine.GetAt(i) != _T(' '))
		break;
	cmd = strLine.Mid(i);
	if (!cmd.IsEmpty()){
		FLAG = THREAD_RUN;
		PrintLog(_T("命令发送成功"));
	}
}


void CACMNetDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_COMMAND)->SetWindowText(_T("Command: "));
}


void CACMNetDlg::OnSetting()
{
	// TODO:  在此添加命令处理程序代码
	NetSet  Dlg;
	Dlg.DoModal();
}


void CACMNetDlg::OnShowset()
{
	// TODO:  在此添加命令处理程序代码
}


int CACMNetDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  在此添加您专用的创建代码

	return 0;
}


HBRUSH CACMNetDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{	
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_RESPONSE) //静态文本 
	{
		  pDC->SetBkMode(TRANSPARENT); 
		  HBRUSH B= CreateSolidBrush(RGB(0XFA, 0XFA, 0XD2));
	      pDC->SetTextColor(RGB(255, 0, 0)); //控件中的文字的颜色
		  return B;
	}
	else if (pWnd->GetDlgCtrlID() == IDC_LOG){
		pDC->SetBkMode(TRANSPARENT); 
		HBRUSH B = CreateSolidBrush(RGB(0xEE, 0xD2, 0xEE));
		pDC->SetTextColor(RGB(255, 0, 0)); //控件中的文字的颜色
		return B;
	}
	return hbr;
}
