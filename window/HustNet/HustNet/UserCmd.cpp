#pragma once
//#include "UserCmd.h"
//#include "CmdView.h"
#include "stdafx.h"
#include "Tools.h"
#include "NetDll.h"
#include "NetHtml.h"
#include "NetWork.h"
using namespace Tools;
using namespace NetWork;

NetDll mydll;
extern void PrintLog (CString);
extern void PrintRp(CString);
extern void CleanLog();
extern void CleanRp();
extern void SetRp(CString);
extern void TakeOverCmd(CString e);
extern void SetHint(CString e);
extern CString GetLine();

void Compute(CString e){
	int pos;
	CString a, b,result;
	int c1, c2;
	pos=e.Find(_T('+'));
	a.Format(_T("%s"), e.Mid(0, pos));
	b.Format(_T("%s"), e.Mid(pos));
	c1=  _wtoi(a);
	c2 = _wtoi(b);
	typedef int(*ADDPROC)(int, int);
	ADDPROC Add = (ADDPROC)mydll.GetFun("add");
	result.Format(_T("%d+%d=%d"), c1, c2, Add(c1 , c2));
	PrintRp(result);
}

void Test(CString e){
	CString mystr;
	TakeOverCmd(_T("myTest>"));
	while ((mystr = GetLine()).Compare(_T("exit"))!=0)
	     PrintRp(mystr);
}

void  Connect(CString e){
		AfxSocketInit();

		//���� CSocket ����
		CSocket aSocket;

		CString strIP;
		strIP.Format(_T("%s"), _T("127.0.0.1"));
		if (!aSocket.Create())
		{
			CString error;
			error.Format(_T("����ʧ��:%d"), aSocket.GetLastError());
			PrintLog(error);
			return;
		}
		//ת����Ҫ���ӵĶ˿���������
		PrintLog(_T("�׽��ִ����ɹ�"));
		//����ָ���ĵ�ַ�Ͷ˿�
		if (aSocket.Connect(strIP, 6500))
		{
			PrintLog(_T("���ӷ������ɹ�"));
			TCHAR szRecValue[1024] = { 0 };
			CString  sed, rev;
			int times = 0;
			TakeOverCmd(_T("client>: "));
			aSocket.Receive((void *)szRecValue, 1024);
			rev.Format(_T("���Է���������Ϣ:%s"), szRecValue);
			PrintRp(rev);
			while ((sed = GetLine()).Compare(_T("exit")) != 0){
				aSocket.Send(sed, sed.GetLength()*sizeof(TCHAR));
				memset(szRecValue, 0, 1024 * sizeof(TCHAR));
				aSocket.Receive((void *)szRecValue, 1024);
				rev.Format(_T("���Է���������Ϣ:%s"), szRecValue);
				PrintRp(rev);
			}
		}
		else{
			CString error;
			error.Format(_T("���ӷ�����ʧ��:%d"), aSocket.GetLastError());
			PrintLog(error);
		}
		aSocket.Close();
 }

void Mail(CString e)
{
	//MailSend mail;
	//mail.Begin();
}

void Chat(CString e){
	ChatWork chat;
	chat.Begin();
}

void SetDll(CString e){
	if (mydll.LoadDll(e) == FALSE){
		PrintLog(_T("δ�ҵ�ָ���Ķ�̬���ӿ�"));
		return;
	}
}

void GetHtml(CString url){
	NetHtml myhtml;
	CString html = myhtml.getURLContext(url);
	SetRp(html);
}