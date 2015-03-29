//tools for other to use
#include <cstring>
#include <thread>
#include <windows.h>
#include "CWebBrowser2.h"
#include "afxinet.h"
#include "stdafx.h"
#include "afxhtml.H "
#pragma once
using namespace std;
namespace Tools{
	//overload : it don't need to use _T anymore
    void AfxMessageBox(string Msg){
		AfxMessageBox(Msg);
	}
	//self make function 
	string Tchar2string(TCHAR *smsg){
		int iLen = WideCharToMultiByte(CP_ACP, 0, smsg, -1, NULL, 0, NULL, NULL);
		char* chRtn = new char[iLen*sizeof(char)];
		WideCharToMultiByte(CP_ACP, 0, smsg, -1, chRtn, iLen, NULL, NULL);
		string str(chRtn);
		return str;
	}

	//Dllusr
	class Dlluser{


	public :
		void Getpath(string path){
			this->path = path;
		}

	private:
		string path;
	};
	
	//get html 
	class Htmlget{
	public:
		void GetUrl(LPCTSTR url){
			this->url = url;
		}
		string GetText(){
			return this->document;
		}
		bool MainAsk(){
			//open a thread to Request
			this->finish = false;
			hThread = CreateThread(NULL, 0, this->Request, 0, 0, &thread_id);
			if (hThread == NULL) {
				AfxMessageBox(" ϵͳ�����߳�ʧ�ܣ�û�л�ȡ��Ϣ\n ");
				return false;//_T()
			}
			while (true){
				if (finish) break;
			}
			//destory
			ExitThread(thread_id);
			return true;
		}
	private:
		//string url;
		LPCTSTR url;
		string document;
		bool finish;
		DWORD thread_id;
		HANDLE hThread;
		CWebBrowser2 thisweb;
		void Request(){
			//set the document acconding to the path
			document = "";
			CInternetSession mySession(NULL, 0);
			CHttpFile* htmlFile = NULL;
			TCHAR src[1024];
			try{
				htmlFile = (CHttpFile*)mySession.OpenURL(url);//�������ӻ�ȡ������
			    if (htmlFile != NULL){//��ʾ��ҳ
					COleVariant noArg;
					/* thisweb is amazing ! it can't use the method Navigate*/
					//thisweb.Navigate(url, &noArg, &noArg, &noArg, &noArg);
					//thisweb.accNavigate(url, &noArg, &noArg);
					
			    }
				while (htmlFile->ReadString(src, 1024)){//��������ÿһ��
					int nBufferSize = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)src, -1, NULL, 0);
			        TCHAR *pBuffer = new TCHAR[nBufferSize + 1];
			        memset(pBuffer, 0, (nBufferSize + 1)*sizeof(TCHAR));
			        MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)src, -1, pBuffer, nBufferSize*sizeof(TCHAR));//UTF-8תUnicode
			        document += Tchar2string(pBuffer);
			        document += "\r\n";
			        delete pBuffer;
		    	}
			    htmlFile->Close();
		    	mySession.Close(); //�رջỰ
			}
			catch (CException *e) {  //�쳣����
				AfxMessageBox( "��ȡ����ʧ��\n" );
			}
		}
	};
}