// RespondView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HustNet.h"
#include "RespondView.h"


// RespondView

IMPLEMENT_DYNCREATE(RespondView, CView)

RespondView::RespondView()
{

}

RespondView::~RespondView()
{
}

BEGIN_MESSAGE_MAP(RespondView, CView)
END_MESSAGE_MAP()


// RespondView ��ͼ

void RespondView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  �ڴ����ӻ��ƴ���
}


// RespondView ���

#ifdef _DEBUG
void RespondView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void RespondView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// RespondView ��Ϣ��������