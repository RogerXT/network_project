
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "HustNet.h"

#include "MainFrm.h"
#include "CmdView.h"
#include "LogView.h"
#include "RespondView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO:  �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style &= ~FWS_ADDTOTITLE;
	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO:  �ڴ����ר�ô����/����û���
	CRect rect;
	GetClientRect(&rect);
	//m_spliter.Create(this, 2, 2, CSize(10, 10), pContext);
	BOOL bCreateSplit = m_splitter.CreateStatic(this, 1, 2);
	if (!s_splitter.CreateStatic(&m_splitter, 2, 1, WS_CHILD | WS_VISIBLE, m_splitter.IdFromRowCol(0, 0)))
	{
		return FALSE;
	}
	s_splitter.CreateView(0, 0, RUNTIME_CLASS(CmdView), CSize(rect.Width() / 2, rect.Height() / 2), pContext);
	s_splitter.CreateView(1, 0, RUNTIME_CLASS(LogView), CSize(rect.Width() / 2, rect.Height() / 4), pContext);
	m_splitter.CreateView(0, 1, RUNTIME_CLASS(RespondView), CSize(rect.Width() / 2, rect.Height()), pContext);
	CMainFrame *pframe;
	pframe = (CMainFrame *)AfxGetApp()->GetMainWnd();
	return bCreateSplit;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (nType != SIZE_MINIMIZED){
		CRect rect;
		GetClientRect(&rect);
		m_splitter.SetRowInfo(0, cy, 50);
		m_splitter.SetColumnInfo(0, rect.Width() / 3, 50);
		 s_splitter.SetColumnInfo(0, rect.Width() / 3, 50);
		 m_splitter.RecalcLayout();
	}
}
