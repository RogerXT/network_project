#pragma once


// Trslayer �Ի���

class Trslayer : public CDialogEx
{
	DECLARE_DYNAMIC(Trslayer)

public:
	Trslayer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Trslayer();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
