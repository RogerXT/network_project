// Applayer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CSnet.h"
#include "Applayer.h"
#include "afxdialogex.h"


// Applayer �Ի���

IMPLEMENT_DYNAMIC(Applayer, CDialogEx)

Applayer::Applayer(CWnd* pParent /*=NULL*/)
	: CDialogEx(Applayer::IDD, pParent)
{

}

Applayer::~Applayer()
{
}

void Applayer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Applayer, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Applayer::OnBnClickedButton1)
END_MESSAGE_MAP()


// Applayer ��Ϣ�������


void Applayer::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T("Ӧ�ò�"));
}
