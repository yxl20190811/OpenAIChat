#include "pch.h"
#include "TOpenAiChat.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
using namespace rapidjson;

void LocalTextFromUtf8(const std::string& req, std::string& res) {
	int nLen1 = MultiByteToWideChar(CP_UTF8, NULL, req.c_str(), -1, NULL, 0);
	std::string textW;
	textW.resize(2 * nLen1 + 2);
	wchar_t* wstr = (wchar_t*)(textW.c_str());
	MultiByteToWideChar(CP_UTF8, NULL, req.c_str(), -1, wstr, nLen1);
	wstr[nLen1 - 1] = 0;
	wstr[nLen1 - 2] = 0;

	int nLen2 = WideCharToMultiByte(CP_ACP, NULL, wstr, -1, NULL, NULL, NULL, NULL);
	res.resize(nLen2 + 1);
	char* text = (char*)(res.c_str());
	WideCharToMultiByte(CP_ACP, NULL, wstr, -1, text, nLen2, NULL, NULL);
	text[nLen2] = 0;
}

void LocalText2Utf8(const std::string& req, std::string& res) {
	int nLen1 = MultiByteToWideChar(CP_ACP, NULL, req.c_str(), -1, NULL, 0);
	std::string textW;
	textW.resize(2 * nLen1 + 2);
	wchar_t* wstr = (wchar_t*)(textW.c_str());
	MultiByteToWideChar(CP_ACP, NULL, req.c_str(), -1, wstr, nLen1);
	wstr[nLen1 - 1] = 0;
	wstr[nLen1 - 2] = 0;

	int nLen2 = WideCharToMultiByte(CP_UTF8, NULL, wstr, -1, NULL, NULL, NULL, NULL);
	res.resize(nLen2 + 1);
	char* text = (char*)(res.c_str());
	WideCharToMultiByte(CP_UTF8, NULL, wstr, -1, text, nLen2, NULL, NULL);
	text[nLen2] = 0;
}

void CreateJsonBuffer(const std::string& model1, const std::string& msg1, StringBuffer& buffer) {
	// 创建一个空的JSON对象
	Document doc;
	doc.SetObject();

	// 添加 "model" 字段
	Value model(model1.c_str(), doc.GetAllocator());
	doc.AddMember("model", model, doc.GetAllocator());

	// 添加 "messages" 字段
	Value messages(kArrayType);
	Value message(kObjectType);
	message.AddMember("role", "user", doc.GetAllocator());
	rapidjson::GenericStringRef<char> tmp(msg1.c_str());
	message.AddMember("content", tmp, doc.GetAllocator());
	messages.PushBack(message, doc.GetAllocator());
	doc.AddMember("messages", messages, doc.GetAllocator());

	// 添加 "temperature" 字段
	doc.AddMember("temperature", 0.7, doc.GetAllocator());

	// 将JSON对象转换为字符串
	Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);
}



TOpenAiChat::TOpenAiChat() {
	char x[1024*100];
	DWORD count = ::GetEnvironmentVariableA("hyt123", x, 1024 * 100);
	if (count <= 0) {
		::MessageBoxA(NULL, "获取OpenAI的key失败，GetEnvironmentVariableW(\"hyt123\")", "错误", MB_ABORTRETRYIGNORE);
		abort();
	}
	m_headers = m_headers + "Authorization: Bearer" + x + "\n";
}

void TOpenAiChat::post(
	const std::string& model, const std::string& req,
	std::string& res) {
	//将req转utf8
	std::string reqUtf8;
	LocalText2Utf8(req, reqUtf8);
	//放到json中转为请求字符串
	StringBuffer req2OpenAi;
	CreateJsonBuffer(model, reqUtf8, req2OpenAi);
	//发送请求
	std::string resFromOpenAI;
	THttp::post("api.openai.com", "/v1/chat/completions", req2OpenAi.GetString(), resFromOpenAI);
	//获取请求，将请求中的返回字符串转为本地编码返回
	Document doc;
	doc.Parse(res.c_str());
	if (!doc.IsObject()) {
		std::cerr << "JSON解析失败" << std::endl;
		return;
	}
	std::string ret;
	{
		const Value& choices = doc["choices"];
		const Value& choice = choices[0];
		const Value& message = choice["message"];
		const Value& content = message["content"];
		ret = content.GetString();
	}
	LocalTextFromUtf8(ret, res);
}

