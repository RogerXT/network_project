#pragma once
#include "ACMNetDlg.h"
#include "ACMBrow.h"

namespace viewContrls{
	/*
	class Print{
	public :
		void setForm(CACMNetDlg *mynet){
			this->mynet = mynet;
		}
		void setBrow(ACMBrow *myweb){
			this->myweb = myweb;
		}
		void PrintLog(LPCTSTR str)   //��log��Ϣ�����Log�༭��
		{
			CString log;
			log.Format(_T("%s\r\n"), str);
			((CEdit *)(mynet->GetDlgItem(IDC_LOG)))->ReplaceSel(log);
		}
		void PrintRP(LPCTSTR txt){     //��txt�����Response�༭��
			CString res;
			res.Format(_T("Response: %s\r\n"), txt);
			((CEdit *)(mynet->GetDlgItem(IDC_RESPONSE)))->ReplaceSel(res);
		}
		void  GetPage(CString url){
			mynet->GetDlgItem(IDC_RESPONSE)->ShowWindow(SW_HIDE);
			COleVariant noArg;
			myweb->Navigate(url, &noArg, &noArg, &noArg, &noArg);
			myweb->get_Visible();
		}
		void  GetHtml(CString url){
			CString html;
			if (myweb->IsWindowVisible()){
				myweb->put_Visible(FALSE);
				mynet->GetDlgItem(IDC_RESPONSE)->ShowWindow(SW_SHOW);
			}
			html = myhtml.getURLContext(url);
			mynet->GetDlgItem(IDC_RESPONSE)->SetWindowText(html);
		}
	private:
		CACMNetDlg *mynet;
		ACMBrow *myweb;
	};*/
}
