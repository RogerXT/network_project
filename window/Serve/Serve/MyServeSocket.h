#pragma once

// MyServeSocket ����Ŀ��


class MyServeSocket : public CAsyncSocket
{
public:
	MyServeSocket();
	virtual ~MyServeSocket();
	virtual void OnAccept(int nErrorCode);
};


