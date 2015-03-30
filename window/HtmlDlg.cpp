// HtmlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "afxinet.h"
#include "CSnet.h"
#include "NetHtml.h"
#include "HtmlDlg.h"
#include "afxdialogex.h"


IMPLEMENT_DYNAMIC(HtmlDlg, CDialogEx)

HtmlDlg::HtmlDlg(CWnd* pParent /*=NULL*/)
	:CDialogEx(HtmlDlg::IDD, pParent)
{
}

HtmlDlg::~HtmlDlg()
{
}

void HtmlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HtmlDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &HtmlDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

struct ARG { LPCTSTR pstrURL; NetHtml *pHtml; CString *HtmlData; };
// HtmlDlg ��Ϣ�������
DWORD WINAPI GetHtml(LPVOID args)
{
	ARG *myarg = (ARG *)args;
	*(myarg->HtmlData) = (myarg->pHtml)->getURLContext(myarg->pstrURL);
	return 1;
}

void HtmlDlg::OnBnClickedButton1() //��ȡURL�ַ��������ú�����ȡ��ҳ���ݣ������������뵽ָ���༭��ؼ�
{
	TCHAR url[100];
	CString myhtml;
	ARG     myarg;
	HANDLE  sonthread;
	GetDlgItem(IDC_URL)->GetWindowText(url, 100);  //��ȡurl
	myarg.pstrURL = url;
	myarg.pHtml = &(this->Html);
	myarg.HtmlData = &myhtml;
	sonthread = CreateThread(NULL, NULL, GetHtml,(LPVOID)(&myarg),NULL,NULL);
	COleVariant noArg;
	myweb.Navigate(url, &noArg, &noArg, &noArg, &noArg);
	WaitForSingleObject(sonthread, INFINITE);
	GetDlgItem(IDC_HTML)->SetWindowText(myhtml); //��ʾ�ı�
}


BOOL HtmlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	GetDlgItem(IDC_PAGE)->GetWindowRect(&rect);
	ScreenToClient(&rect);    
	GetDlgItem(IDC_PAGE)->ShowWindow(SW_HIDE);
	if (!myweb.Create(NULL, NULL, WS_VISIBLE, rect, this, 101))  
	{
		return NULL;   
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}
