// ACMNet.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CACMNetApp: 
// �йش����ʵ�֣������ ACMNet.cpp
//

class CACMNetApp : public CWinApp
{
public:
	CACMNetApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CACMNetApp theApp;