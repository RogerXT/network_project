// ClientSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Serve.h"
#include "ClientSocket.h"


extern void PrintView(CString e);
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
		memset(Buffer, 0, sizeof(Buffer));
		Receive(Buffer, MAXLEN);
	}
PrintView(Buffer);
CAsyncSocket::OnReceive(nErrorCode);
}


void ClientSocket::OnSend(int nErrorCode)
{
	// TODO:  �ڴ����ר�ô����/����û���
	Send(_T("�ɹ�����"), sizeof(_T("�ɹ�����")));
	CAsyncSocket::OnSend(nErrorCode);
}