// LogView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HustNet.h"
#include "LogView.h"


// LogView

IMPLEMENT_DYNCREATE(LogView, CView)

LogView::LogView()
{

}

LogView::~LogView()
{
}

BEGIN_MESSAGE_MAP(LogView, CView)
END_MESSAGE_MAP()


// LogView ��ͼ

void LogView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  �ڴ���ӻ��ƴ���
}


// LogView ���

#ifdef _DEBUG
void LogView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void LogView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// LogView ��Ϣ�������
