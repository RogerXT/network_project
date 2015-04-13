
// ServeView.cpp : CServeView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Serve.h"
#endif

#include "ServeDoc.h"
#include "ServeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServeView

IMPLEMENT_DYNCREATE(CServeView, CEditView)

BEGIN_MESSAGE_MAP(CServeView, CEditView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CServeView ����/����

CServeView::CServeView()
{
	// TODO:  �ڴ˴���ӹ������

}

CServeView::~CServeView()
{
}

BOOL CServeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// ���û���

	return bPreCreated;
}


// CServeView ��ӡ

BOOL CServeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ׼��
	return CEditView::OnPreparePrinting(pInfo);
}

void CServeView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ��ʼ��ӡ
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CServeView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ������ӡ
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CServeView ���

#ifdef _DEBUG
void CServeView::AssertValid() const
{
	CEditView::AssertValid();
}

void CServeView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CServeDoc* CServeView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CServeDoc)));
	return (CServeDoc*)m_pDocument;
}
#endif //_DEBUG


// CServeView ��Ϣ�������
