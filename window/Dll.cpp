// Dll.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CSnet.h"
#include "Dll.h"
#include "afxdialogex.h"


// Dll �Ի���

IMPLEMENT_DYNAMIC(Dll, CDialogEx)

Dll::Dll(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dll::IDD, pParent)
{
	Add = NULL;

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
	/*int num1, num2;
	TCHAR ch1[10], ch2[10], rst[10];
	CString result;
	GetDlgItem(IDC_NUMBER1)->GetWindowText(ch1,10);
	GetDlgItem(IDC_NUMBER2)->GetWindowText(ch2,10);
	num1 = _ttoi(ch1);
	num2 = _ttoi(ch2);
	if (Add == NULL)
		return;
	result.Format(_T("%d + %d = %d"), num1, num2, Add(num1, num2));
	GetDlgItem(IDC_RESULT)->SetWindowText(result);*/
}


void Dll::OnBnClickedLoad()
{
	// TODO:  �ڴ˼��ض�̬���ӿ⣬��Dll���еĺ���ָ��ָ��ö�̬���ӿ⵼������(PS:ʾ��ΪAdd)
	/*HINSTANCE Hinst;
	TCHAR  format[100] = _T("Files (*.dll)|*.dll||");
	CFileDialog file((int)TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,format);//���ļ��Ի���
	file.DoModal(); 
	CString path;
	path = file.GetPathName();//��ȡ���ӿ�·��
	Hinst = LoadLibrary(path); //��ȡ���ӿ�ʵ�����
	if (Hinst == NULL)
		return;
	Add = (ADDPROC)GetProcAddress(Hinst, "add");*/   //��ȡ���ӿ⵼������ָ��
}
