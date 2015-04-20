/** @file
* @brief ����URL��ȡHTML����.
* @author ACM2012
* @date 2015/04/12
* @version 0.1
* @note
* ���ļ���������NetHtml�к�����ʵ�֣�����
* �������캯��������������HTML��ȡ����.
* HTTP�����ĸ�ʽ�� (<sp>Ϊ�ո�, " "��������һ���Ϸ��Ŀո�)
* Method <sp> URL <sp> HttpVersion <crlf>
* Header0: <sp> HeaderValue <crlf>
* ...
* HeaderN: <sp> HeaderValue <crlf>
* <crlf> (which is important)
* EntityBody (empty for GET, something for POST)
* @remark
* ���ļ�����������Ҫ�޸ģ��Ա������������ݣ�Ҳ�п��ܲ���HTTPSet.cpp
*/

#include "stdafx.h"
#include "NetHtml.h"
#include "Tools.h"
using namespace Tools;

#define MAXLEN 1024

extern void PrintLog(CString);

/**
* @author ACM2012
* @note
* ���캯�����Ա���չ
* @since 0.1
*/
NetHtml::NetHtml()
{

}

/**
* @author ACM2012
* @note
* �����������Ա���չ
* @since 0.1
*/
NetHtml::~NetHtml()
{

}

/**
* @author ACM2012
* @param[in] pstrURL ����URL��LPCTSTR����
* @return ��ȡ��HTML���ݣ�ĿǰΪ��ȡ��������Ӧ���ģ���Unicode���룬CString����
* @note
* ����������URL���ú������仮��Ϊ�������֣�
* ��һ������Ϊ������������ָ�������Ҫ��ȡ��HTML�ļ��ķ�������
* �ڶ�������Ϊ·��+��ѯ��+Ƭ�η�������·��Ϊ�����·��������ļ�ϵͳ·������ѯ��Ϊ
* �ύ��������̨���н����Ĵ������ڶ�̬�ط����û�����������ݣ�Ƭ�η����������û�
* �����ǰ������������Դ�е�λ�ã���ʱ�������ڲ�ѯ���У�
* ���ڶ�����Ϊ�գ�����ΪĬ�ϡ�/������ʾ��ǰĿ¼��.
* ���������������������֮�䴴�����ӣ�֮��ʹ��GET���������������ĵڶ����ֻ�ȡ
* HTML����.
* @remark
* ���ʹ�����ڲ��ؼ���Ŀǰ����CSocketʵ�֣�����Ԥ��ʹ�ñ���Ŀ�ع���Socket��ʵ��.
* @since 0.1
*/
CString NetHtml::getURLContext(LPCTSTR pstrURL){
	/*CString myhtml;
	CInternetSession mySession(NULL, 0);
	CHttpFile* htmlFile = NULL;
	TCHAR src[1024];
	try{
	PrintLog(_T("��������!"));
	htmlFile = (CHttpFile*)mySession.OpenURL(pstrURL);
	PrintLog(_T("����ȡ�ر���!"));
	while (htmlFile->ReadString(src, 1024)){
	
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
		PrintLog(_T("��ȡ����ʧ��!"));
	} 
	return myhtml;*/
	/** @brief ��ʼ��Socket*/
	AfxSocketInit();
	CString myhtml;
	/** @brief ����һ��Socket*/
	CSocket mySocket;
	CString tempURL = pstrURL;
	string pHost;
	string GET;
	/** @brief ��URL���ҵ���һ��б�ܣ����ڷֿ���������*/
	int i = tempURL.Find(_T('/'), 0);
	if (i == -1)
	{
		/** @brief �ڶ�����Ϊ��*/
		i = tempURL.GetLength();
		GET = "/";
	}
	else
	{
		/** @brief ��ȡ�ڶ����ֲ�ת��*/
		CString tempGET = tempURL.Mid(i);
		GET = Tstr::Tchar2string(tempGET.GetBuffer());
	}
	/** @brief ��ȡ����������һ���֣���ת��*/
	CString tempHOST = tempURL.Mid(0, i);
	pHost = Tstr::Tchar2string(tempHOST.GetBuffer());
	LPCWSTR host_name = Tstr::String2LPCWSTR(pHost);
	string header = "";
	char buf[MAXLEN];
	TCHAR TCHAR_buf[MAXLEN];
	try{
		/** @brief ����һ��Socket*/
		mySocket.Create();
		/** @brief ��ʽ�����ӵ���������80�˿�*/
		mySocket.Connect(host_name, 80);	// ����80�˿�
		/** @brief ��װ����ͷ*/
		header = "GET " + GET + " HTTP/1.1\nHOST: " + pHost + "\n\n";
		/** @brief ����ͷת��*/
		char *temp = Tstr::S2Cstar(header);
		/** @brief ������װ�õ�������*/
		mySocket.Send(temp, header.length() + 1, 0);
		/** @brief �رյ������������ӣ����򳤵ȴ�ֱ��������ʧ����*/
		mySocket.Send("Connection: Close\n\n", 20, 0);
		/** @brief �ͷ�ת�����õ��ַ����Ŀռ�*/
		free(temp);
		/** @brief ���շ��ص���Ӧ���Ĳ�ת��*/
		while (mySocket.Receive(buf, MAXLEN, 0) > 0)
		{
			int nBufferSize = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)buf, -1, NULL, 0);
			TCHAR *pBuffer = new TCHAR[nBufferSize + 1];
			memset(pBuffer, 0, (nBufferSize + 1)*sizeof(TCHAR));
			MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)buf, -1, pBuffer, nBufferSize*sizeof(TCHAR));//UTF-8תUnicode
			myhtml += pBuffer;
		}
	}
	catch (CException *e)
	{
		/** @brief �쳣����Ϊ��ӡLog��Ϣ*/
		PrintLog(_T("��ȡ����ʧ��!"));
	}
	/** @brief ��������ȡ��Html����*/
	return myhtml;
};
