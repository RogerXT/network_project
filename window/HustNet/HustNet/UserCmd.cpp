#pragma once
#include "UserCmd.h"
#include "CmdView.h"
#include "stdafx.h"

extern void PrintLog(CString);
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
		TCHAR szRecValue[1024] = { 0 };
		CString  rev;
		//�������ݸ�������
		PrintLog(_T("���ӷ������ɹ�"));
		aSocket.Send(e, e.GetLength() + 1);
		aSocket.Receive((void *)szRecValue, 1024);
		rev.Format(_T("%s"), szRecValue);
	}
	else{
		CString error;
		error.Format(_T("����ʧ��:%d"), aSocket.GetLastError());
		PrintLog(error);
	}
	aSocket.Close();
}