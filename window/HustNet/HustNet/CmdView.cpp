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

typedef void (*CMDPROC)(CString);
map<CString, CMDPROC> my_map;
enum  STATE  { THREAD_EXIT, THREAD_WAIT, THREAD_RUN }  THREADFLAG;
enum  LINESTATE {OLDLINE,NEWLINE} LINEFLAG;

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
	ON_MESSAGE(TAKEOVERCMD,OnTakeOverCmd)
	ON_MESSAGE(SETHINT, OnSetHint)
	ON_MESSAGE(DEALCMDOVER, OnDealCmdOver)
	ON_MESSAGE(ENDINPUT, OnEndInput)
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
	mycmd.ID = SETTEXT;
	mycmd.agrs = &e;
	pfame->SendMessage(DISPATCH, RPVIEW, LPARAM(&mycmd));
}

void SetHint(CString e)
{
	CMD mycmd;
	mycmd.ID = SETHINT;
	mycmd.agrs = &e;
	pfame->SendMessage(DISPATCH, CMDVIEW, LPARAM(&mycmd));
}

void TakeOverCmd(CString e)
{
	CMD mycmd;
	mycmd.ID = TAKEOVERCMD;
	mycmd.agrs = &e;
	pfame->SendMessage(DISPATCH, CMDVIEW, LPARAM(&mycmd));
}

void EndInput()
{
	CMD mycmd;
	mycmd.ID = ENDINPUT;
	mycmd.agrs = NULL;
	pfame->SendMessage(DISPATCH, CMDVIEW, LPARAM(&mycmd));
}

CString  GetLine()
{
	static CString  myline;
	while (LINEFLAG != NEWLINE)
		;
	myline = command;
	EndInput();
	LINEFLAG = OLDLINE;
	return myline;
}

void   MapTask(){   //����ַ�
	int index;
	TCHAR c;
	CString Ins,args;
	command.TrimLeft();
	command.TrimRight();
	if (command.IsEmpty())
		return;
	index = command.Find(_T(' '));
	if (index == -1){
		Ins = command;
		args.Empty();
	}
	else {
		Ins = command.Mid(0, index);
		args = (command.Mid(index)).TrimLeft();
	}
	if (my_map.find(Ins) == my_map.end()){
		PrintLog(_T("δ֪����"));
	}
	else
    	(my_map[Ins])(args);
}

void DealCmdOver()
{
	CMD mycmd;
	mycmd.ID = DEALCMDOVER;
	mycmd.agrs = NULL;
	pfame->SendMessage(DISPATCH, CMDVIEW, (LPARAM)&mycmd);
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
			DealCmdOver();
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
	my_map.insert(pair<CString, CMDPROC>(_T("test"), Test));
	my_map.insert(pair<CString, CMDPROC>(_T("conn"), Connect));
	my_map.insert(pair<CString, CMDPROC>(_T("setdll"), SetDll));
	my_map.insert(pair<CString, CMDPROC>(_T("gethtml"), GetHtml));
	//my_map.insert(pair<CString, CMDPROC>(_T("Mail"), Mail));
	my_map[_T("Mail")] = Mail;//equal to before
	my_map[_T("Chat")] = Chat;
}


// CmdView
void CmdView::DealEnter()
{
		CString strText;
		int        num, len, nIndex,nline;
		len = myedit->GetWindowTextLength(); //�ƶ���굽��β
		myedit->SetSel(len, len, false);
		myedit->SetFocus();
		num = myedit->GetLineCount();           //����command��
		nIndex = myedit->LineIndex(HintLine); //��ȡ�к�
		len = myedit->LineLength(nIndex);  //��ȡ�г���
		myedit->GetLine(HintLine, strText.GetBuffer(len), len); //��ȡ������
		strText.ReleaseBuffer();
		command = (strText.Mid(HintSLen)).TrimLeft();  
		strText.Empty();
        if (HintLine < num - 1){      //��������
			num = myedit->GetLineCount();
			for (nline= HintLine + 1; nline< num; nline++){
				nIndex = myedit->LineIndex(nline);
				len = myedit->LineLength(nIndex);
				myedit->GetLine(nline, strText.GetBuffer(len), len);
				strText.ReleaseBuffer();
				command += strText;
				strText.Empty();
			}
		}
	   if (THREADFLAG == THREAD_RUN&&CMDFLAG == ROOT)//δ�ӹ�ģʽ�������������
				PrintLog(_T("������Ч����ȴ���һ����ִ����"));	 
	   else if (THREADFLAG == THREAD_WAIT)  //δ�ӹ�ģʽ�·�������
		       THREADFLAG = THREAD_RUN;
	   else  if (CMDFLAG == USER)  //�û�ģʽ��
		   LINEFLAG = NEWLINE;
}

void CmdView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ	
	if (VK_BACK == nChar){  //����ɾ����Χ
		CPoint point;
		int num;
		num = myedit->GetLineCount();
		point = GetCaretPos();
		if (point.x <= HintPLen&&num - 1 == HintLine)
			return;
	}
	if (VK_RETURN == nChar) //����س���Ϣ
		DealEnter();
	CEditView::OnChar(nChar, nRepCnt, nFlags);
}

void CmdView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	pfame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	myedit = (CEdit *)this;
	Initialcmd();

	myfont.CreatePointFont(120,	(LPCTSTR)_T("Times New Roman"));
	myedit->SetFont(&myfont);
	SetHint(_T("Command:"));
	myedit->ReplaceSel(Hint);
	HintLine = 0;
}


BOOL CmdView::PreCreateWindow(CREATESTRUCT& cs)  //����CmdView����
{
	// TODO:  �ڴ����ר�ô����/����û���  
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
		if (point.x <= HintPLen&&HIWORD(nline)==HintLine) 
			return;
	default: break;
	}
	CEditView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CmdView::OnSize(UINT nType, int cx, int cy)
{
	CEditView::OnSize(nType, cx, cy);
	// TODO:  �ڴ˴������Ϣ����������
	int num = ((CEdit *)this)->GetLineCount();   //���»�ȡHintLine�б��
	int nIndex,nline;
	CString strText,temp;
	for (nline = num - 1; nline >= 0; nline--){
		nIndex = ((CEdit*)this)->LineIndex(nline);
		int len = ((CEdit *)this)->LineLength(nIndex);
		((CEdit *)this)->GetLine(nline, strText.GetBuffer(len), len);
		strText.ReleaseBuffer();
		if (len >= HintSLen){
			temp = strText.Mid(0, HintSLen);
			if (temp.Compare(Hint) == 0){
				HintLine = nline;
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

LRESULT CmdView::OnSetHint(WPARAM wparam, LPARAM lparam)
{
	CClientDC dc(this);
	CSize  sz;
	Hint = *((CString *)wparam);
	dc.GetTextMetrics(&tm);
	sz = dc.GetTextExtent(Hint);
	HintSLen = _tcslen(Hint);
	HintPLen = sz.cx + tm.tmWeight / 200;
	return 0;
}

LRESULT CmdView::OnTakeOverCmd(WPARAM wparam, LPARAM lparam)
{	

	if (CMDFLAG==ROOT)
    	CMDFLAG = USER;
	LINEFLAG = OLDLINE;
	Hint = *((CString *)wparam);
	SetHint(Hint);
	myedit->ReplaceSel(Hint);
	HintLine = myedit->GetLineCount() - 1;
	return 0;
}

LRESULT  CmdView::OnDealCmdOver(WPARAM wparam, LPARAM lparam)
{
	if (CMDFLAG == USER){
		myedit->ReplaceSel(_T("�˳��ɹ�\r\n"));
		CMDFLAG = ROOT;
		SetHint(_T("Command:"));
	}
	HintLine = myedit->GetLineCount() - 1;
	POINT cur;
	cur.x = 0;
	cur.y = HintLine*tm.tmHeight;
	SetCaretPos(cur);
	SetFocus();
	myedit->ReplaceSel(Hint);
	return 0;
}

LRESULT  CmdView::OnEndInput(WPARAM wparam, LPARAM lparam)
{
	if (CMDFLAG == USER){
		myedit->ReplaceSel(Hint);
		HintLine = myedit->GetLineCount() - 1;
	}
	return 0;
}

