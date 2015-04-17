// ClientSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Serve.h"
#include "ClientSocket.h"
#include <map>

using namespace std;
extern void PrintView(CString e);
extern map <ClientSocket *, int> myclient;
// ClientSocket

ClientSocket::ClientSocket()
{
}

ClientSocket::~ClientSocket()
{
}


// ClientSocket ��Ա����

void ClientSocket::OnReceive(int nErrorCode)
{
// TODO:  �ڴ����ר�ô����/����û���
	if (nErrorCode == 0){
		CString result, back;
		memset(Buffer, 0, sizeof(Buffer));
		Receive(Buffer, MAXLEN);
		result.Format(_T("���Կͻ���%d����Ϣ:%s"), myclient[this], Buffer);
		PrintView(result);
		back.Format(_T("�ɹ�������Ϣ:%s"), Buffer);
		Send(back, back.GetLength()*sizeof(TCHAR));
	}
CAsyncSocket::OnReceive(nErrorCode);
}


void ClientSocket::OnSend(int nErrorCode)
{
	// TODO:  �ڴ����ר�ô����/����û���
	CString back;
	back.Format(_T("�����%dλ��¼��"), myclient[this]);
	Send(back, back.GetLength()*sizeof(TCHAR));
	CAsyncSocket::OnSend(nErrorCode);
}

void ClientSocket::OnClose(int nErrorCode)
{
	// TODO:  �ڴ����ר�ô����/����û���
	CString log;
	log.Format(_T("�ͻ���%d�ѶϿ�����"), myclient[this]);
	PrintView(log);
	CAsyncSocket::OnClose(nErrorCode);
	delete this;
}
