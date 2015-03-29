#pragma once
#include "afxwin.h"
#include "Applayer.h"
#include "Trslayer.h"
#include "Netlayer.h"
#include "Linklayer.h"
#include "Phylayer.h"




// NetDlg �Ի���

class NetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(NetDlg)

public:
	NetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~NetDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox mylist;
	CStatic    mysparator;
	Applayer  myApplayer;
	Trslayer   myTrslayer;
	Netlayer  myNetlayer;
	Linklayer myLinklayer;
	Phylayer myPhylayer;
	int Oldsel;
	int status;
	HBRUSH m_hbrush;
	CRect        Rect, ChildRect;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeList1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
