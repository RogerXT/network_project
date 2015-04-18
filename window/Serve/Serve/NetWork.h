#include "map"
#include "Tools.h"


namespace NetWork{
	/*HOW IT WORKS
	
	*/
	class AppLayerHttp{
	public:
		string Log;
		AppLayerHttp(){
			Http_init();//init the map
			Listen_launch();//launch a listen thread
		}
		~AppLayerHttp(){
			delete &Function;//remove the map
		}
		/*name: Getpath
		  function: analysis the path send by 
		*/
		string Getpath(){
			string path;
			//div by some char
			//
			return path;
		}
		//map the CMD to the real
		void DealWith(string CMD, vector<string> args){
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
		/*the map struct*/
		typedef void(AppLayerHttp::*DealWithFunciton)(vector<string> data);
		map<string, DealWithFunciton> Function;
		string path;
		string RespondMsg;
		/* the function we choose to deal with the data request*/
		void GET(vector<string> data){

		}
		void HEAD(vector<string> data){

		}
		void POST(vector<string> data){

		}
		void PUT(vector<string> data){

		}
		void DELETE(vector<string> data){

		}
		void OPTIONS(vector<string> data){

		}
		void TRACE(vector<string> data){

		}
		void CONNECT(vector<string> data){

		}
		
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
		}


	};
}
