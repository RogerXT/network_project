#pragma once
//#include  "ShowWebpage.h"
#include "CWebBrowser2.h"
#include "NetHtml.h"
// HtmlDlg �Ի���

class HtmlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HtmlDlg)

public:
	HtmlDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~HtmlDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CWebBrowser2  myweb;
	NetHtml   Html;
	afx_msg void OnBnClickedButton1();
	CString getURLContext(LPCTSTR pstrURL);
	virtual BOOL OnInitDialog();
};
