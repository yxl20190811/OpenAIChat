#pragma once
#include <string>
class TOpenAiChatThread
{
public:
	TOpenAiChatThread();
	void add(const std::string& model, const std::string& req);
protected:
	std::string m_req;
	std::string m_model;
	bool m_IsReady2Post;
	bool m_IsFree2Add;
protected:
	static UINT AFX_CDECL ThreadFun(LPVOID pThis);
	void MyThreadFun();
	virtual void OnRecvFromOpenAI(std::string& text);
};

