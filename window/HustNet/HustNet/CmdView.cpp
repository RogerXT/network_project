// CmdView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HustNet.h"
#include "CmdView.h"

CMainFrame *pfame;
CmdView     *pcmd;
LogView       *plog;
RespondView *prespond;
CString cmd;

// CmdView

IMPLEMENT_DYNCREATE(CmdView, CEditView)

CmdView::CmdView()
{

}

CmdView::~CmdView()
{
}

BEGIN_MESSAGE_MAP(CmdView, CEditView)
	ON_WM_CHAR()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CmdView ���

#ifdef _DEBUG
void CmdView::AssertValid() const
{
	CEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CmdView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif
#endif //_DEBUG


// CmdView ��Ϣ�������


void CmdView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ	
	CString mystr, strText;
	CPoint point;
	int num, len;
	switch(nChar)  
	{
	case VK_BACK:
		point = GetCaretPos();
		if (point.x <= length)
			return;
		break;
	case VK_RETURN:
			num = ((CEdit *)this)->GetLineCount();
			len = ((CEdit *)this)->LineLength();
			((CEdit *)this)->GetLine(num - 1, strText.GetBuffer(len), len);
			strText.ReleaseBuffer();
			mystr.Format(_T("%s"), strText);
			prespond->PrintRp(mystr);
			 break;
	default: break;
	}
	CEditView::OnChar(nChar, nRepCnt, nFlags);
}


void CmdView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	CClientDC dc(this);
	CSize  sz;
	sz = dc.GetTextExtent(_T("Commahnd: "));
	length = sz.cx;
	CWnd *pwnd;
	pcmd = this;
	pfame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	pwnd = pfame->s_splitter.GetPane(1, 0);
	plog = DYNAMIC_DOWNCAST(LogView, pwnd);
	pwnd = pfame->m_splitter.GetPane(0, 1);
	prespond = DYNAMIC_DOWNCAST(RespondView, pwnd);
	((CEdit *)this)->ReplaceSel(_T("Command: "));
}


void CmdView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (0x0D == nChar)
		((CEdit *)this)->ReplaceSel(_T("Command: "));
	CEditView::OnKeyUp(nChar, nRepCnt, nFlags);
}


BOOL CmdView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ����ר�ô����/����û���
	m_dwDefaultStyle = AFX_WS_DEFAULT_VIEW | WS_VSCROLL | ES_AUTOVSCROLL |ES_MULTILINE | ES_NOHIDESEL;
	return CCtrlView::PreCreateWindow(cs);
}


void CmdView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return;
	//CEditView::OnLButtonDown(nFlags, point);
}


void CmdView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return;
	//CEditView::OnLButtonDblClk(nFlags, point);
}


void CmdView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int len;
	CPoint point;
	switch (nChar)
	{
	case  VK_UP:
	case  VK_DOWN:return;
	case  VK_LEFT:
		point = GetCaretPos();
		if (point.x <= length)
			return;
	default: break;
	}

	CEditView::OnKeyDown(nChar, nRepCnt, nFlags);
}
