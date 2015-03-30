
// CSnetView.cpp : CCSnetView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CSnet.h"
#endif

#include "CSnetDoc.h"
#include "CSnetView.h"
#include "NetDlg.h"
#include "DllDlg.h"
#include "HtmlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCSnetView

IMPLEMENT_DYNCREATE(CCSnetView, CView)

BEGIN_MESSAGE_MAP(CCSnetView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DLL, &CCSnetView::OnDll)
	ON_COMMAND(ID_NETPAGE, &CCSnetView::OnNetpage)
	ON_COMMAND(32785, &CCSnetView::OnNetDlg)
END_MESSAGE_MAP()

// CCSnetView ����/����

CCSnetView::CCSnetView()
{
	// TODO:  �ڴ˴���ӹ������

}

CCSnetView::~CCSnetView()
{
}

BOOL CCSnetView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCSnetView ����

void CCSnetView::OnDraw(CDC* /*pDC*/)
{
	CCSnetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CCSnetView ��ӡ

BOOL CCSnetView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCSnetView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCSnetView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CCSnetView ���

#ifdef _DEBUG
void CCSnetView::AssertValid() const
{
	CView::AssertValid();
}

void CCSnetView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCSnetDoc* CCSnetView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCSnetDoc)));
	return (CCSnetDoc*)m_pDocument;
}
#endif //_DEBUG


// CCSnetView ��Ϣ�������

void CCSnetView::OnDll()
{
	Dll  Dlg;
	Dlg.DoModal();
}


void CCSnetView::OnNetpage()
{
	// TODO:  �ڴ���������������
	HtmlDlg Dlg;
	Dlg.DoModal();

}




void CCSnetView::OnNetDlg()
{
	// TODO:  �ڴ���������������
	NetDlg Dlg;
	Dlg.DoModal();
}
