#pragma once


// RespondView ��ͼ

class RespondView : public CView
{
	DECLARE_DYNCREATE(RespondView)

protected:
	RespondView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~RespondView();

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


