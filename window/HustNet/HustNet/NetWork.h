#pragma once
#include "stdafx.h"
#include "map"
#include "Tools.h"
//#import "dll/Jmail.dll"

extern void PrintLog(CString);
extern void PrintRp(CString);
extern void CleanLog();
extern void CleanRp();
extern void SetRp(CString);
extern void TakeOverCmd(CString e);
extern void SetHint(CString e);
extern CString GetLine();

using namespace std;
using namespace Tools;

namespace NetWork{
	//Socket
	class ChatWork{
	public:
		ChatWork(){
			init();
			Obj = _T("Public");
			No = -1;//local
			TNo = _T("-1");//server
			this->Name = "No1";
		}
		ChatWork(CString name){
			ChatWork();
			this->Name = name;
		}
		~ChatWork(){
		}
		void Begin(){
			CString mystr;
			CString Code = _T("Chat ") + this->Name + _T(">");
			TakeOverCmd(Code);
			while ((mystr = GetLine()).Compare(_T("exit")) != 0){
				CStringArray cmd;
				Tstr::CCarg(&cmd, mystr, _T(' '));
				PrintLog(_T("Accept ") + cmd[0]);
				switch (exp[cmd[0]]){
				case 0: break;//keep
				case 1:
					if (cmd.GetSize() < 2){
						PrintLog(_T("Error code for no Msg"));
						break;
					}
					SendMsg(cmd[1]);
					break;//send
				case 2: break;//link
				case 3: 
					if (cmd.GetSize() < 2){
						PrintLog(_T("Error code for no Msg"));
						break;
					}
					ConnMsg(cmd[1]);
					break;
				case 10: 
					CNo.Format(_T("%d"), this->No);
					PrintRp(_T("the no of client is ") + CNo);
					PrintRp(_T("the aim of client is ") + TNo);
					break;
				default: PrintLog(_T("Error Code"));
				}
			}
			if (!Finish()) { PrintLog(_T("Delete CSocket failed\n")); }
		}
		bool Finish(){
			csocket.Close();
			return true;
		}
	private:
		map<CString, int> exp;
		CString Name;
		int No;
		//CString Msg;
		CString Obj;
		CString CNo, TNo;
		CSocket csocket;
		CString strIP;//IP
		TCHAR szRecValue[1024];
		void init(){
			exp[_T("Send")] = exp[_T("send")] = 1;//Send message to someone
			exp[_T("Link")] = exp[_T("link")] = 2;//link to somebody
			exp[_T("Conn")] = exp[_T("conn")] = 3;//connect
			exp[_T("Info")] = 10;
		}
		void SendMsg(CString Msg){
			CString rev;
			memset(szRecValue, 0, sizeof(szRecValue));
			//�������ݸ�������
			PrintLog(_T("���ӷ������ɹ�"));
			csocket.Send(Msg, Msg.GetLength()*sizeof(TCHAR));
			csocket.Receive((void *)szRecValue, 1024);
			rev.Format(_T("%s"), szRecValue);
			PrintRp(rev);
		}
		void ConnMsg(CString Msg){
			AfxSocketInit();
			strIP.Format(_T("%s"), _T("127.0.0.1"));
			if (!csocket.Create())
			{
				CString error;
				error.Format(_T("����ʧ��:%d"), csocket.GetLastError());
				PrintLog(error);
				return;
			}
			//ת����Ҫ���ӵĶ˿���������
			PrintLog(_T("�׽��ִ����ɹ�"));
			//����ָ���ĵ�ַ�Ͷ˿�
			if (csocket.Connect(strIP, 6500))
			{
				CString rev;
				memset(szRecValue, 0, sizeof(szRecValue));
				//�������ݸ�������
				PrintLog(_T("���ӷ������ɹ�"));
				csocket.Send(Msg, Msg.GetLength()*sizeof(TCHAR));
				csocket.Receive((void *)szRecValue, 1024);
				rev.Format(_T("%s"), szRecValue);
			}
			else{
				CString error;
				error.Format(_T("����ʧ��:%d"), csocket.GetLastError());
				PrintLog(error);
			}
		}

	};
	
	class FTPWork{

	};
	/*HOW IT WORKS
	
	
	*/
	class AppLayerHttp{
	public:

	private:

	};
}


	/*
	//send a mail
	class MailSend // use the 
	{
	public:
		MailSend(){
			init();
			CoInitialize(NULL);
			UserName = _T("wangluokecs2012@163.com");
			PassWord = _T("111111z");
			SendAddr = _T("smtp.163.com");
			Subject = _T("Hello World\n");
			MsgText = _T("World Beautiful\n");
			RevAddr = _T("authwork2@163.com");
		}
		~MailSend(){
		}
		void Begin(){
			CString mystr;
			TakeOverCmd(_T("Mail>"));
			while ((mystr = GetLine()).Compare(_T("exit")) != 0){
				PrintLog(_T("Accept ") + mystr);
				switch (MailCmd[mystr]){
				case 0: break;
				case 1: break;
				case 2: break;
				case 3: break;
				case 4:
					SendMail();
					break;
				case 5: SetRev(mystr); PrintRp(_T("set to send to ") + this->RevAddr); break;
				default: PrintLog(_T("Error Code"));
				}
			}
		}
		void SetRev(CString Addr){ this->RevAddr = Addr; }
		void SetSub(CString Sub){ this->Subject = Sub; }
		void SetMsg(CString Msg){ this->MsgText = Msg; }
	private:
		map<CString, int> MailCmd;
		CString UserName, PassWord;
		CString RevAddr, SendAddr;
		CString Subject, MsgText;
		//stmp name passw
		//sender
		//http://hi.baidu.com/alalmn/item/48c2e0d33e959494260ae7a5

		void init(){
			MailCmd[_T("exit")] = 0;//exit
			MailCmd[_T("user")] = MailCmd[_T("User")] = 1;//u
			MailCmd[_T("password")] = MailCmd[_T("Password")] = 2;//pw
			MailCmd[_T("STMP")] = 3;//set stmp
			MailCmd[_T("Send")] = MailCmd[_T("send")] = 4;//send mail
			MailCmd[_T("To")] = MailCmd[_T("to")] = 5;//to someone
		}
		void SendMail(){
			try{
			    jmail::IMessagePtr pMsg("JMail.Message");//waitjmail::Message
		     	pMsg->Priority = 3;
		    	pMsg->Charset = "GB2312";
				pMsg->From = "wangluokecs2012@163.com";//Tstr::CS2S(UserName).c_str();
				pMsg->FromName = "wlk";//Tstr::CS2S(UserName).c_str();
		    	//const char *res[] = {Tstr::CS2S(RevAddr).c_str()};
		    	//const char *rens[] = {Tstr::CS2S(RevAddr).c_str()};
		    	//pMsg->AddRecipient(res[0], rens[0]��"");
	     		//pMsg->AddRecipient(res[0], rens[0], "");authwork2@163.com
				pMsg->AddRecipient("834658870@qq.com", "", "");//authwork2@163.com"834658870@qq.com"
				pMsg->Subject = "abcd";//Tstr::CS2S(Subject).c_str();
				pMsg->Body = "123456789";//Tstr::CS2S(MsgText).c_str();
		    	pMsg->AppendText("You can add any words when you want\n");
				//pMsg->MailServerUserName = "wangluokecs2012@163.com";//Tstr::CS2S(UserName).c_str();
				//pMsg->MailServerPassWord = "111111z";// Tstr::CS2S(PassWord).c_str();
				//CString SendInfo = _T("");
		    	//SendInfo += UserName;
				//SendInfo += _T(":");
				//SendInfo += UserName;
		    	//SendInfo += PassWord;
		    	//SendInfo += _T("@");
		    	//SendInfo += SendAddr;
				//_bstr_t(SendInfo)
				pMsg->Send("wangluokecs2012:111111z@smtp��163.com", VARIANT_FALSE);
			}
			catch(_com_error e){
				PrintLog(e.ErrorMessage());
				PrintRp(_T("ȷ������ȷ��װ��Jmail���"));
			}
		}
	};
	*/

