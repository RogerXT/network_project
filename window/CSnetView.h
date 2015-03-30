
// CSnetView.h : CCSnetView ��Ľӿ�
//

#pragma once


class CCSnetView : public CView
{
protected: // �������л�����
	CCSnetView();
	DECLARE_DYNCREATE(CCSnetView)

// ����
public:
	CCSnetDoc* GetDocument() const;

// ����

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CCSnetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDll();
	afx_msg void OnNetpage();
	afx_msg void OnNetDlg();
};

#ifndef _DEBUG  // CSnetView.cpp �еĵ��԰汾
inline CCSnetDoc* CCSnetView::GetDocument() const
   { return reinterpret_cast<CCSnetDoc*>(m_pDocument); }
#endif

