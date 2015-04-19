#pragma once
#include "map"
#include "Tools.h"
#include "MyServeSocket.h"
#define SCOKETNUM 1024
//
#define NO_SOCKET 1
//
#define NO_REV_DATA 2
//
#define PORT 6500
//
#define MSG_OK 200
//
#define BAD_REQUEST 400
//
#define NO_FOUND 404
/*
Rev sample Msg Data
CMD + " " + PATH + " " + HOST
Send
FILE TYPE + " " + FILE LEN + " " + FILE
*/
using namespace Tools;
namespace NetWork{
	/*HOW IT WORKS
	*/
	class AppLayerHttp{
	public:
		string Log;
		AppLayerHttp(){
			Http_init();//init the map function
			//new the object, and there must be none connected
			Listen_launch();//launch a listen thread
		}
		~AppLayerHttp(){
			delete &Function;//remove the map
		}
		/*name: Getpath
		  function: analysis the path send by 
		*/
		/* divide the data recived
		using tools::Split
		*/
		void GetData(string RevData){
			//div by some char ' '
			//save them in data
			STR::Split(RevData, &data, ' ');
		}
		//map the CMD to the real function
		void DealWith(string CMD, vector<string> args){
			if (Function.find(CMD)==Function.end()){
				//DON'T HAVE THIS CMD
				//return BADxxx
				ErrorCode = BAD_REQUEST;
			}
			try{
				//ע��1���������ʹ��this->���������error C2171: ��*��: 
				//��void (__thiscall CUtil::* )(int)�����͵Ĳ������Ƿ��Ĵ���
				//ע��2���������ʹ��*�����ã�����ʵ�ֺ������ã�
				//�������error C2064: ������Ϊ���� 1 �������ĺ����Ĵ���
				(this->*Function[CMD])(args);
			}
			catch (exception e){
				Log = e.what();
				return ;
			}
		}
	private :
		/*the deal function struct*/
		typedef void(AppLayerHttp::*DealWithFunciton)(vector<string> data);
		/*the map struct*/
		map<string, DealWithFunciton> Function;
		/*the divided data*/
		vector<string> data;
		//
		bool Mark[SCOKETNUM];
		//turn 
		MyServeSocket *mysocket[SCOKETNUM];
		//
		/*the Socket is the class we design, map it to the count*/
		//map <ClientSocket *, int> myclient;
		//the file in the "/" path
		int ErrorCode;
		//the Msg respond to client
		string RespondMsg;
		/* the function we choose to deal with the data request*/
		/*����URI�б�ʶ��Դ��һ��������, Map it to 1*/
		/*TOYOU : find GET message from net and copy them to here*/
		void GET(vector<string> data){
			//path >> data[1]
			//host >> data[2]
			/*
			1 find the file according to the path
			2 if not exist return NO_FOUND
			3 else use byte cache[1024] to divide the file
			4 read file into IO
			5 use a loop to do{
			    move parts of file into cache
				use the sender to send the cache out
				check the return value
			}
			*/
		}
		/*��GET������ͬ��������ֻ����״̬�к�ͷ�꣬
		�������������ĵ�, Map it to 2*/
		/*TOYOU : find HEAD message from net and copy them to here*/
		void HEAD(vector<string> data){
			//path >> data[1]
			//host >> data[2]
			/*
			1 find the file according to the path
			2 if not exist return (NO_FOUND,"NOT FOUND")
			given the Msg like (no of state, and text Msg)
			use sender to send it out
			}
			*/
		}
		/*���������ܱ�д��ͻ���������е����ݵ�����,
		Map it to 3*/
		/*TOYOU : find POST message from net and copy them to here*/
		void POST(vector<string> data){
			//path >> data[1]
			//host >> data[2]
			/*
			1 analysis the data from client
			2 save it the Socket conn to it
			return OK
			}
			*/
		}
		/*��������������������Ϊָ��URI�����ݵ�����,
		Map it to 4*/
		/*TOYOU : find PUT message from net and copy them to here*/
		void PUT(vector<string> data){
			//path >> data[1]
			//host >> data[2]
			/*
			1 find the file in path?
			2 no -> save it in this path ,return OK
			3 yes -> 
			  3.1 rewrite it in this path , return OK
			  3.2 return HAVE_EXISTED
			*/
		}
		/*������ɾ��URI����������Դ������, Map it to 5*/
		/*TOYOU : find DELETE message from net and copy them to here*/
		void DELETE(vector<string> data){
			//path >> data[1]
			//host >> data[2]
			/*
			1 find the file in path?
			2 yes -> delete it in this path ,return OK
			3 no ->
			3.1 return OK anyway
			3.2 return warnning "NOT_EXIST"
			*/
		}
		/*���ڷ�����֧�ֵ����󷽷���Ϣ������,
		Map it to 6*/
		/*TOYOU : find OPTIONS message from net and copy them to here*/
		void OPTIONS(vector<string> data){
			/*just tell the people things this serve support
			1 return OK
			2 return "GET HEAD POST PUT DELETE OPTIONS TRACE CONNECT"
			  as Msg
			*/
		}
		/*Web����������Http�������ͷ�������,
		Map it to 7*/
		/*TOYOU : find TRACE message from net and copy them to here*/
		void TRACE(vector<string> data){
			//I don't Know what's it meaning?
		}
		//NOT USE FUNCTION
		/*���ĵ�������ǰδʵ�ֵ�һ��������
		Ԥ�����������, Map it to 8*/
		void CONNECT(vector<string> data){
			//this function leaved to satifiy other function
			//and it doesn't has a function now
		}
		//LIKE COPY MOVE LINK UNLINK and so on
		/*
		  Name : Http_init
		  function: init the Http Object
		  Init the Map 
		  ��ӳ�䲻�ֱ��Сд
		*/
		void Http_init(){
			/*����URI�б�ʶ��Դ��һ��������, Map it to 1*/
			Function["GET"] = Function["get"] = &AppLayerHttp::GET;
			/*��GET������ͬ��������ֻ����״̬�к�ͷ�꣬
			  �������������ĵ�, Map it to 2*/
			Function["HEAD"] = Function["head"] = &AppLayerHttp::HEAD;
			/*���������ܱ�д��ͻ���������е����ݵ�����,
			  Map it to 3*/
			Function["POST"] = Function["post"] = &AppLayerHttp::POST;
			/*��������������������Ϊָ��URI�����ݵ�����,
			  Map it to 4*/
			Function["PUT"] = Function["put"] = &AppLayerHttp::PUT;
			/*������ɾ��URI����������Դ������, Map it to 5*/
			Function["DELETE"] = Function["delete"] = &AppLayerHttp::DELETE;
			/*���ڷ�����֧�ֵ����󷽷���Ϣ������, 
			  Map it to 6*/
			Function["OPTIONS"] = Function["options"] = &AppLayerHttp::OPTIONS;
			/*Web����������Http�������ͷ�������,
			  Map it to 7*/
			Function["TRACE"] = Function["trace"] = &AppLayerHttp::TRACE;
			/*���ĵ�������ǰδʵ�ֵ�һ��������
			  Ԥ�����������, Map it to 8*/
			Function["CONNECT"] = Function["connet"] = &AppLayerHttp::CONNECT;
		}
		
		/*name: Listen_launch
		  function: 

		*/

		bool Listen_launch(){
			//launch a listen thread
			//if failed return false;
			//else return true
			//new a socket to listen from the request from client
			/*STEP:
			1 FREE A CSocket
			2 USE THE No.0
			3 0 to do other things
			4 Open the listener
			return ture, else return false
			*/
		}


	};
}
