#pragma once


// Linklayer �Ի���

class Linklayer : public CDialogEx
{
	DECLARE_DYNAMIC(Linklayer)

public:
	Linklayer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Linklayer();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
