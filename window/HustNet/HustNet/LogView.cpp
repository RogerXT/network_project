// LogView.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "HustNet.h"
#include "LogView.h"

// LogView
IMPLEMENT_DYNCREATE(LogView, CEditView)

LogView::LogView()
{
	Res.Empty();
	logcount = 0;
}

LogView::~LogView()
{
}

BEGIN_MESSAGE_MAP(LogView, CEditView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CHAR()
	ON_MESSAGE(PRINT, Print)
	ON_MESSAGE(CLEAN, Clean)
END_MESSAGE_MAP()


// LogView ��ͼ

void LogView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  �ڴ���ӻ��ƴ���
	SetWindowText(Res);
}


// LogView ���

#ifdef _DEBUG
void LogView::AssertValid() const
{
	CEditView::AssertValid();
}

#ifndef _WIN32_WCE
void LogView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif
#endif //_DEBUG


// LogView ��Ϣ�������


void LogView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	CClientDC dc(this);
	dc.GetTextMetrics(&tm);
	static CFont  myfont;
	myfont.CreatePointFont(120, (LPCTSTR)_T("Times New Roman"));
	((CEdit *)this)->SetFont(&myfont);
}


BOOL LogView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ����ר�ô����/����û���
	m_dwDefaultStyle = AFX_WS_DEFAULT_VIEW | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_NOHIDESEL;
	return CCtrlView::PreCreateWindow(cs);
}


void LogView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//return;
	CEditView::OnLButtonDown(nFlags, point);
}


void LogView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return;
	//CEditView::OnLButtonDblClk(nFlags, point);
}


void LogView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return;
	//CEditView::OnChar(nChar, nRepCnt, nFlags);
}

LRESULT LogView::Print(WPARAM wparam, LPARAM lparam)
{
	CString mystr = *((CString *)wparam);
	CString temp;
	temp.Format(_T("log%d:%s\r\n "), logcount++, mystr);
	Res += temp;
	SetWindowText(Res);
	int l = ((CEdit *)this)->GetWindowTextLength();
	((CEdit *)this)->SetSel(l, l, false);
	((CEdit *)this)->SetFocus();
	return 0;
}

LRESULT LogView::Clean(WPARAM wparam, LPARAM lparam)
{
	CString mystr;
	mystr.Empty();
	SetWindowText(mystr);
	logcount = 0;
	int l = ((CEdit *)this)->GetWindowTextLength();
	((CEdit *)this)->SetSel(l, l, false);
	((CEdit *)this)->SetFocus();
	return 0;
}