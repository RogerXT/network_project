#pragma once
//#include  "ShowWebpage.h"
#include "CWebBrowser2.h"
// GetHtml �Ի���

class GetHtml : public CDialogEx
{
	DECLARE_DYNAMIC(GetHtml)

public:
	GetHtml(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GetHtml();

// �Ի�������
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CWebBrowser2  myweb;
	afx_msg void OnBnClickedButton1();
	CString getURLContext(LPCTSTR pstrURL);
	virtual BOOL OnInitDialog();
};
