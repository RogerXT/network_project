#pragma once


// Applayer �Ի���

class Applayer : public CDialogEx
{
	DECLARE_DYNAMIC(Applayer)

public:
	Applayer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Applayer();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
