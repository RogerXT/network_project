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
	enum  CMDMODE { ROOT, USER }  CMDFLAG;
protected:
	TEXTMETRIC tm;
	CFont   myfont;
	CEdit  *myedit;
	CString Hint;
	int HintPLen;    //Hint��Ļ�ߴ糤��
	int HintSLen;    //Hint�ַ�����(�ڴ泤��)
	int HintLine;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnInitialUpdate();
//	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg  LRESULT  OnSetHint(WPARAM wparam, LPARAM lparam);
    afx_msg  LRESULT  OnTakeOverCmd(WPARAM wparam, LPARAM lparam);
	afx_msg  LRESULT  OnDealCmdOver(WPARAM wparam, LPARAM lparam);
	afx_msg  LRESULT  OnEndInput(WPARAM wparam, LPARAM lparam);
protected:
	void DealEnter();
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


