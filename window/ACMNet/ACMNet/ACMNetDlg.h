// ACMNetDlg.h : ͷ�ļ�
//
#pragma once
#include "afxwin.h"

#include "Tools.h"
using namespace Tools;
//#include "ACMBrow.h"
// CACMNetDlg �Ի���
class CACMNetDlg : public CDialogEx
{
// ����
public:
	CACMNetDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ACMNET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit  mycmd;
	Dlluser dlltest;
	afx_msg void OnClose();
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSetting();
	afx_msg void OnShowset();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
