// Linklayer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CSnet.h"
#include "Linklayer.h"
#include "afxdialogex.h"


// Linklayer �Ի���

IMPLEMENT_DYNAMIC(Linklayer, CDialogEx)

Linklayer::Linklayer(CWnd* pParent /*=NULL*/)
	: CDialogEx(Linklayer::IDD, pParent)
{

}

Linklayer::~Linklayer()
{
}

void Linklayer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Linklayer, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Linklayer::OnBnClickedButton1)
END_MESSAGE_MAP()


// Linklayer ��Ϣ�������


void Linklayer::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T("��·��"));
}
