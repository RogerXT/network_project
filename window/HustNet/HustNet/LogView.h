#pragma once


// LogView ��ͼ

class LogView : public CView
{
	DECLARE_DYNCREATE(LogView)

protected:
	LogView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~LogView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


