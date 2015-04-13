#pragma once
//#include "UserCmd.h"
//#include "CmdView.h"
#include "stdafx.h"
#include "Tools.h"
#include "NetWork.h"
using namespace Tools;
using namespace NetWork;

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
	result.Format(_T("%d+%d=%d"), c1, c2, c1 + c2);
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
<<<<<<< HEAD

		//���� CSocket ����
		CSocket aSocket;

		CString strIP;

		strIP.Format(_T("%s"), _T("172.16.162.1"));
		if (!aSocket.Create())
		{
			CString error;
			error.Format(_T("����ʧ��:%d"), aSocket.GetLastError());
=======
		//���� CSocket ����
		CSocket csocket;
		CString strIP;
		strIP.Format(_T("%s"), _T("127.0.0.1"));
		if (!csocket.Create())
		{
			CString error;
			error.Format(_T("����ʧ��:%d"), csocket.GetLastError());
>>>>>>> 3835134ad337e9fc8be3c67283f4b10897d81200
			PrintLog(error);
			return;
		}
		//ת����Ҫ���ӵĶ˿���������
		PrintLog(_T("�׽��ִ����ɹ�"));
<<<<<<< HEAD
		
		//����ָ���ĵ�ַ�Ͷ˿�
		if (aSocket.Connect(strIP, 6500))
		{
			PrintLog(_T("���ӷ������ɹ�"));
			TCHAR szRecValue[1024] = { 0 };
			CString  sed, rev;
			int times = 0;
			TakeOverCmd(_T("clinet>: "));
			aSocket.Receive((void *)szRecValue, 1024);
			rev.Format(_T("���Է���������Ϣ:%s"), szRecValue);
			PrintRp(rev);
			while ((sed = GetLine()).Compare(_T("exit")) != 0){
				aSocket.Send(sed, sed.GetLength()*sizeof(TCHAR));
				aSocket.Receive((void *)szRecValue, 1024);
				rev.Format(_T("���Է���������Ϣ:%s"), szRecValue);
				PrintRp(rev);
			}
		}
		else{
			CString error;
			error.Format(_T("����ʧ��:%d"), aSocket.GetLastError());
			PrintLog(error);
		}
		aSocket.Close();
}
=======
		//����ָ���ĵ�ַ�Ͷ˿�
		if (csocket.Connect(strIP, 6500))
		{
			TCHAR szRecValue[1024] = { 0 };
			CString  rev;
			//�������ݸ�������
			PrintLog(_T("���ӷ������ɹ�"));
			csocket.Send(e, e.GetLength() + 1);
			csocket.Receive((void *)szRecValue, 1024);
			rev.Format(_T("%s"), szRecValue);
		}
		else{
			CString error;
			error.Format(_T("����ʧ��:%d"), csocket.GetLastError());
			PrintLog(error);
		}
		csocket.Close();
}

>>>>>>> 3835134ad337e9fc8be3c67283f4b10897d81200
void Mail(CString e){
	//PrintLog(_T("Wait for being finished\n"));
	MailSend mail;
	mail.Begin();
}

void Chat(CString e){
	ChatWork chat;
	chat.Begin();
}
