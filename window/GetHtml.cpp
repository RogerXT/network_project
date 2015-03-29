// GetHtml.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "afxinet.h"
#include "CSnet.h"
#include "GetHtml.h"
#include "afxdialogex.h"

CString  GetHtml::getURLContext(LPCTSTR pstrURL){
	CString myhtml;	
	/*CInternetSession mySession(NULL, 0);
	CHttpFile* htmlFile = NULL;
	TCHAR src[1024];
	try{
		htmlFile = (CHttpFile*)mySession.OpenURL(pstrURL);//�������ӻ�ȡ������
		if (htmlFile != NULL){//��ʾ��ҳ
			COleVariant noArg;
			myweb.Navigate(pstrURL, &noArg, &noArg, &noArg, &noArg);
		}
		while (htmlFile->ReadString(src, 1024)){//��������ÿһ��
			int nBufferSize = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)src, -1, NULL, 0); 
			TCHAR *pBuffer = new TCHAR[nBufferSize + 1];
			memset(pBuffer, 0, (nBufferSize + 1)*sizeof(TCHAR));
			MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)src, -1, pBuffer, nBufferSize*sizeof(TCHAR));//UTF-8תUnicode
			myhtml += pBuffer; 
			myhtml += _T("\r\n");
			delete pBuffer;
		}
		htmlFile->Close();
		mySession.Close(); //�رջỰ
	}
	catch (CException *e) {  //�쳣����
	       AfxMessageBox(_T("��ȡ����ʧ��"));
		  } */
	return myhtml; 
};

IMPLEMENT_DYNAMIC(GetHtml, CDialogEx)

GetHtml::GetHtml(CWnd* pParent /*=NULL*/)
	: CDialogEx(GetHtml::IDD, pParent)
{

}

GetHtml::~GetHtml()
{
}

void GetHtml::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GetHtml, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &GetHtml::OnBnClickedButton1)
END_MESSAGE_MAP()


// GetHtml ��Ϣ�������


void GetHtml::OnBnClickedButton1() //��ȡURL�ַ��������ú�����ȡ��ҳ���ݣ������������뵽ָ���༭��ؼ�
{
	TCHAR url[100];
	CString myhtml;
	GetDlgItem(IDC_URL)->GetWindowText(url, 100);  //��ȡurl		
	myhtml = getURLContext(url);        //��ȡ������
	GetDlgItem(IDC_HTML)->SetWindowText(myhtml); //��ʾ�ı�
}


BOOL GetHtml::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	GetDlgItem(IDC_PAGE)->GetWindowRect(&rect);
	ScreenToClient(&rect);    
	GetDlgItem(IDC_PAGE)->ShowWindow(SW_HIDE);
	if (!myweb.Create(NULL, NULL, WS_VISIBLE, rect, this, 101))  
	{
		return NULL;   
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
