#include "stdafx.h"
#include "NetHtml.h"

NetHtml::NetHtml()
{

}

NetHtml::~NetHtml()
{
}
CString  NetHtml::getURLContext(LPCTSTR pstrURL){
	CString myhtml;
	CInternetSession mySession(NULL, 0);
	CHttpFile* htmlFile = NULL;
	TCHAR src[1024];
	try{
	htmlFile = (CHttpFile*)mySession.OpenURL(pstrURL);//�������ӻ�ȡ����;
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
	} 
	return myhtml;
};
