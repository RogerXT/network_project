#pragma once


// Phylayer �Ի���

class Phylayer : public CDialogEx
{
	DECLARE_DYNAMIC(Phylayer)

public:
	Phylayer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Phylayer();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
