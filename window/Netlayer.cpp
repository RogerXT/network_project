// Netlayer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CSnet.h"
#include "Netlayer.h"
#include "afxdialogex.h"


// Netlayer �Ի���

IMPLEMENT_DYNAMIC(Netlayer, CDialogEx)

Netlayer::Netlayer(CWnd* pParent /*=NULL*/)
	: CDialogEx(Netlayer::IDD, pParent)
{

}

Netlayer::~Netlayer()
{
}

void Netlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Netlayer, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Netlayer::OnBnClickedButton1)
END_MESSAGE_MAP()


// Netlayer ��Ϣ�������


void Netlayer::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T("�����"));
}
