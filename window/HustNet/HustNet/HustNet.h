
// HustNet.h : HustNet Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

#define CMDVIEW   0
#define RPVIEW   1
#define LOGVIEW   2


#define PRINT       WM_USER+1000
#define CLEAN      WM_USER+1001
#define SET          WM_USER+1002
#define DISPATCH WM_USER+1003

struct  CMD{
	int ID;
	void * agrs;
};


// CHustNetApp:
// �йش����ʵ�֣������ HustNet.cpp
//

class CHustNetApp : public CWinApp
{
public:
	CHustNetApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHustNetApp theApp;
