/** @file
* @brief ����URL��ȡHTML����.
* @author ACM2012
* @date 2015/04/12
* @version 0.1
* @note
* ���ļ���������NetHtml�������������װ���ڻ�ȡHTML���ݵĺ���.
* HTTP�����ĸ�ʽ�� (<sp>Ϊ�ո�, " "��������һ���Ϸ��Ŀո�)
* Method <sp> URL <sp> HttpVersion <crlf>
* Header0: <sp> HeaderValue <crlf>
* ...
* HeaderN: <sp> HeaderValue <crlf>
* <crlf> (which is important)
* EntityBody (empty for GET, something for POST)
* @remark
* ���ļ�����������Ҫ�޸ģ��Ա������������ݣ�Ҳ�п��ܲ���HTTPSet.h
*/
#pragma once
#include "afxinet.h"

/**
* @class
* @brief �����װ���ڻ�ȡHTML���ݵĺ���.
* @author ACM2012
* @note
* �����������Ĺ��캯��������������ʵ����getURLContext��������
* ��ȡHTML����.
*/
class NetHtml
{
public:
	/** @brief ���캯��*/
	NetHtml();
	/** @brief ��������*/
	~NetHtml();
	/** @brief ����URL��ȡHTML����*/
	CString NetHtml::getURLContext(LPCTSTR pstrURL);
};

