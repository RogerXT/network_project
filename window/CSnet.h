
// CSnet.h : CSnet Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CCSnetApp:
// �йش����ʵ�֣������ CSnet.cpp
//

class CCSnetApp : public CWinApp
{
public:
	CCSnetApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCSnetApp theApp;
