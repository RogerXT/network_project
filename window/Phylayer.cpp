// Phylayer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CSnet.h"
#include "Phylayer.h"
#include "afxdialogex.h"


// Phylayer �Ի���

IMPLEMENT_DYNAMIC(Phylayer, CDialogEx)

Phylayer::Phylayer(CWnd* pParent /*=NULL*/)
	: CDialogEx(Phylayer::IDD, pParent)
{

}

Phylayer::~Phylayer()
{
}

void Phylayer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Phylayer, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Phylayer::OnBnClickedButton1)
END_MESSAGE_MAP()


// Phylayer ��Ϣ�������


void Phylayer::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T("�����"));
}
