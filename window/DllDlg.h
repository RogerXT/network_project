#pragma once
#include "NetDll.h"

// Dll �Ի���
typedef int(*ADDPROC)(int a, int b);
class Dll : public CDialogEx
{
	DECLARE_DYNAMIC(Dll)

public:
	Dll(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dll();
	NetDll SUM;
// �Ի�������
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedLoad();
};