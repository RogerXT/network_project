#pragma once


// NetSet �Ի���

class NetSet : public CDialogEx
{
	DECLARE_DYNAMIC(NetSet)

public:
	NetSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~NetSet();

// �Ի�������
	enum { IDD = IDD_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLocalBrowse();
	afx_msg void OnBnClickedServerBrowse();
};
