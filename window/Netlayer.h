#pragma once


// Netlayer �Ի���

class Netlayer : public CDialogEx
{
	DECLARE_DYNAMIC(Netlayer)

public:
	Netlayer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Netlayer();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
