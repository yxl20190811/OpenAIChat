#include "pch.h"
#include "TOpenAiChatThread.h"
#include "TOpenAiChat.h"

TOpenAiChatThread::TOpenAiChatThread() {
	m_IsReady2Post = false;
	m_IsFree2Add = true;
}
void TOpenAiChatThread::add(const std::string& model, const std::string& req) {
	while(!m_IsFree2Add) {
		Sleep(20);
	}
	m_IsFree2Add = false;
	m_req = req;
	m_model = model;
	m_IsReady2Post = true;
}

UINT AFX_CDECL TOpenAiChatThread::ThreadFun(LPVOID pThis) {
	((TOpenAiChatThread*)pThis)->MyThreadFun();
	return 0;
}
void TOpenAiChatThread::MyThreadFun() {
	std::string res;
	TOpenAiChat chat;
	while (true) {
		while (!m_IsReady2Post) {
			Sleep(20);
		}
		m_IsReady2Post = false;
		chat.post(m_model, m_req, res);
		m_IsFree2Add = true;
		OnRecvFromOpenAI(res);
	}
}
void TOpenAiChatThread::OnRecvFromOpenAI(std::string& text) {
	printf("%s", text.c_str());
}
