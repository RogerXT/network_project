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
	if (0x08 == nChar){
		int num, len;
		len = ((CEdit *)this)->LineLength();
		if (len == 9)
			return;
	}
	if (0x0D == nChar){
		CString mystr, strText;
		int num, len;
		num = ((CEdit *)this)->GetLineCount();
		len = ((CEdit *)this)->LineLength();
		((CEdit *)this)->GetLine(num - 1, strText.GetBuffer(len), len);
		strText.ReleaseBuffer();
		int index = strText.Find(_T(':'));
		mystr.Format(_T("%s"), strText);
		prespond->PrintRp(mystr);
	}
	CEditView::OnChar(nChar, nRepCnt, nFlags);
}


void CmdView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
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
