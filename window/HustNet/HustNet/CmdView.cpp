// CmdView.cpp : ʵ���ļ�
#include "stdafx.h"
#include "HustNet.h"
#include "CmdView.h"
#include "MainFrm.h"
#include "UserCmd.h"
#include <map>

CMainFrame *pfame;
CString  command;
using namespace std;
// CmdView
#define TIPLEN 8
typedef void (*CMDPROC)(CString);
map<CString, CMDPROC> my_map;

enum  STATE  { THREAD_EXIT, THREAD_WAIT, THREAD_RUN }  THREADFLAG;
IMPLEMENT_DYNCREATE(CmdView, CEditView)

CmdView::CmdView()
{

}

CmdView::~CmdView()
{
}

BEGIN_MESSAGE_MAP(CmdView, CEditView)
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
	ON_WM_KILLFOCUS()
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
void PrintLog(CString log)
{
	CMD mycmd;
	mycmd.ID = PRINT;
	mycmd.agrs = &log;
	pfame->SendMessage(DISPATCH, LOGVIEW,(LPARAM)(&mycmd));
}

void PrintRp(CString rp)
{
	CMD mycmd;
	mycmd.ID = PRINT;
	mycmd.agrs = &rp;
	pfame->SendMessage(DISPATCH, RPVIEW, (LPARAM)(&mycmd));
}

void CleanRp(CString e)
{
	CMD mycmd;
	mycmd.ID = CLEAN;
	mycmd.agrs = NULL;
	pfame->SendMessage(DISPATCH, RPVIEW, LPARAM(&mycmd));
}

void CleanLog(CString e)
{
	CMD mycmd;
	mycmd.ID = CLEAN;
	mycmd.agrs = NULL;
	pfame->SendMessage(DISPATCH, LOGVIEW, LPARAM(&mycmd));
}

void SetRp(CString e)
{
	CMD mycmd;
	mycmd.ID = SET;
	mycmd.agrs = &e;
	pfame->SendMessage(DISPATCH, RPVIEW, LPARAM(&mycmd));
}

void   MapTask(){   //����ַ�
	int len, i;
	TCHAR c;
	CString Ins,args;
	args.Empty();
	len = command.GetLength();
	for (i = 0; i < command.GetLength(); i++){
		if ((c = command.GetAt(i)) != _T(' ')){
			Ins += c;
		}
		else break;
	}
	while (i < command.GetLength() && (c = command.GetAt(i++)) != _T(' '));
	args = command.Mid(i);
	if (my_map.find(Ins) == my_map.end()){
		PrintLog(_T("δ֪����"));
	}
	else
    	(my_map[Ins])(args);
}

DWORD WINAPI DEALCMD(LPVOID lpParameter){

	while (TRUE){
		if (THREADFLAG == THREAD_EXIT)
			break;
		else if (THREADFLAG == THREAD_WAIT)
			continue;
		else {
			MapTask();
			THREADFLAG = THREAD_WAIT;
		}
	}
	return 0;
}

void Initialcmd()
{
	THREADFLAG = THREAD_WAIT;
	if (CreateThread(NULL, NULL, DEALCMD, NULL, NULL, NULL)){
		PrintLog(_T("������Ϣ�����̳߳ɹ�!\n"));
	}
	else PrintLog(_T("������Ϣ�����߳�ʧ��"));
	my_map.insert(pair<CString, CMDPROC>(_T("printrp"), PrintRp));
	my_map.insert(pair<CString, CMDPROC>(_T("compute"), Compute));
	my_map.insert(pair<CString, CMDPROC>(_T("cleanrp"), CleanRp));
	my_map.insert(pair<CString, CMDPROC>(_T("cleanlog"), CleanLog));
	my_map.insert(pair<CString, CMDPROC>(_T("setrp"), SetRp));
}

void CmdView::DealEnter()
{
	CString strText;
	int        num, len, index, nIndex;
    len = myedit->GetWindowTextLength(); //�ƶ���굽��β
	myedit->SetSel(len, len, false);
	myedit->SetFocus();
	num = myedit->GetLineCount(); //����command��
	nIndex = myedit->LineIndex(maskline); //��ȡ�к�
	len = myedit->LineLength(nIndex);  //��ȡ�г���
	myedit->GetLine(maskline, strText.GetBuffer(len), len); //��ȡ������
	strText.ReleaseBuffer();
	index = TIPLEN;
	while (index < len&&_T(' ') == strText.GetAt(index))
		index++;  //ȥ���ո�
	if (index == len){
		command.Empty();
		return;
	}
	else
	    command = strText.Mid(index);
	strText.Empty();
	if (maskline == num - 1 && !command.IsEmpty())  //ֻ��һ������
		;
	else if (maskline < num - 1){   //��������
		num = myedit->GetLineCount();
		for (int i = maskline + 1; i < num; i++){
			nIndex = myedit->LineIndex(i);
			len = myedit->LineLength(nIndex);
			myedit->GetLine(i, strText.GetBuffer(len), len);
			strText.ReleaseBuffer();
			command += strText;
			strText.Empty();
		}
	}
	if (THREADFLAG == THREAD_RUN)
		PrintLog(_T("������Ч����ȴ���һ����ִ����"));
	else
    	THREADFLAG = THREAD_RUN;
}

void CmdView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ	
	if (VK_BACK == nChar){  //����ɾ����Χ
		CPoint point;
		int num;
		num = myedit->GetLineCount();
		point = GetCaretPos();
		if (point.x <= masklength&&num - 1 == maskline)
			return;
	}
	if (VK_RETURN == nChar) //����س���Ϣ
		DealEnter();
	CEditView::OnChar(nChar, nRepCnt, nFlags);
	if (VK_RETURN == nChar){
		myedit->ReplaceSel(_T("Command:"));//���Command��ʾ
		maskline = myedit->GetLineCount()-1;
	}
}

void CmdView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	pfame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	myedit = (CEdit *)this;
	Initialcmd();

	CClientDC dc(this);

	myfont.CreatePointFont(120,	(LPCTSTR)_T("Times New Roman"));
	myedit->SetFont(&myfont);
	
	dc.GetTextMetrics(&tm);
	CSize  sz;
	sz = dc.GetTextExtent(_T("Command:"));
	masklength = sz.cx+tm.tmWeight/200;
	myedit->ReplaceSel(_T("Command:"));
	maskline = 0;
}


BOOL CmdView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ����ר�ô����/����û���    //����CmdView����
	m_dwDefaultStyle = AFX_WS_DEFAULT_VIEW | WS_VSCROLL | ES_AUTOVSCROLL |ES_MULTILINE | ES_NOHIDESEL;
	return CCtrlView::PreCreateWindow(cs);
}

void CmdView::OnLButtonDown(UINT nFlags, CPoint point) //���������
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
	CPoint point;
	int nline;
	switch (nChar)
	{
	case  VK_UP:
	case  VK_DOWN:
	case   VK_HOME: return;
	case  VK_LEFT:
		point = GetCaretPos();                        //��ֹ����ƶ���command����:
		nline = myedit->CharFromPos(point);
		if (point.x <= masklength&&HIWORD(nline)==maskline) 
			return;
	default: break;
	}
	CEditView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CmdView::OnSize(UINT nType, int cx, int cy)
{
	CEditView::OnSize(nType, cx, cy);
	// TODO:  �ڴ˴������Ϣ����������
	int num = myedit->GetLineCount();   //���»�ȡmaskline�б��
	int nIndex;
	CString strText,temp;
	for (int i = num - 1; i >= 0; i--){
		nIndex = ((CEdit*)this)->LineIndex(i);
		int len = myedit->LineLength(nIndex);
		myedit->GetLine(i, strText.GetBuffer(len), len);
		strText.ReleaseBuffer();
		if (len >= TIPLEN){
			temp = strText.Mid(0, TIPLEN);
			if (temp.Compare(_T("Command:")) == 0){
				maskline = i;
				break;
			}
		}
	}
}


void CmdView::OnKillFocus(CWnd* pNewWnd)
{
	CEditView::OnKillFocus(pNewWnd);

	// TODO:  �ڴ˴������Ϣ����������   
	int len = myedit->GetWindowTextLength();  //��ȡ���뽹��
	myedit->SetSel(len,len,false);
	myedit->SetFocus();

}
