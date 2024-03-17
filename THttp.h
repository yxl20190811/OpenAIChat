#pragma once
#include <string>
class THttp
{
public:
	THttp();
	void post(
		const char* url,
		const char* path,
		const std::string& req, std::string& res,
		bool IsHttps = true);
protected:
	std::string m_headers;
};

