// Trslayer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CSnet.h"
#include "Trslayer.h"
#include "afxdialogex.h"


// Trslayer �Ի���

IMPLEMENT_DYNAMIC(Trslayer, CDialogEx)

Trslayer::Trslayer(CWnd* pParent /*=NULL*/)
	: CDialogEx(Trslayer::IDD, pParent)
{

}

Trslayer::~Trslayer()
{
}

void Trslayer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Trslayer, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Trslayer::OnBnClickedButton1)
END_MESSAGE_MAP()


// Trslayer ��Ϣ�������


void Trslayer::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T("�����"));
}
