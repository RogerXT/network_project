#pragma once


// CmdView ��ͼ

class CmdView : public CEditView
{
	DECLARE_DYNCREATE(CmdView)

protected:
	CmdView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CmdView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


