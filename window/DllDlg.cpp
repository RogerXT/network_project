// Dll.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CSnet.h"
#include "DllDlg.h"
#include "afxdialogex.h"


// Dll �Ի���

IMPLEMENT_DYNAMIC(Dll, CDialogEx)

Dll::Dll(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dll::IDD, pParent)
{
}

Dll::~Dll()
{
}

void Dll::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Dll, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Dll::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_LOAD, &Dll::OnBnClickedLoad)
END_MESSAGE_MAP()


// Dll ��Ϣ�������


void Dll::OnBnClickedButton1()
{
	// TODO:  ������ȡ���������ִ�ж�̬���ӿ⺯�������д�ؿؼ�
	int num1, num2;
	TCHAR ch1[10], ch2[10], rst[10];
	CString result;
	GetDlgItem(IDC_NUMBER1)->GetWindowText(ch1,10);
	GetDlgItem(IDC_NUMBER2)->GetWindowText(ch2,10);
	num1 = _ttoi(ch1);
	num2 = _ttoi(ch2);
	if (SUM.Hinst == NULL)
		return;
	typedef int(*ADDPROC)(int a, int b);
	ADDPROC Add = (ADDPROC)GetProcAddress(SUM.Hinst, "add");
	result.Format(_T("%d + %d = %d"), num1, num2, Add(num1, num2));
	GetDlgItem(IDC_RESULT)->SetWindowText(result);
}


void Dll::OnBnClickedLoad()
{
	SUM.OpenDll();
}
