#pragma once
#include <string>
class THttp
{
public:
	THttp();
	void post(
		const wchar_t* url,
		const wchar_t* path,
		const std::string& req, std::string& res,
		bool IsHttps = true);
protected:
	CStringW m_headers;
};

