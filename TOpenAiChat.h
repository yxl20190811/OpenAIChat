#pragma once
#include <string>
#include "THttp.h"
class TOpenAiChat: public THttp
{
public:
	TOpenAiChat();
	void post(
		const std::string& model, const std::string& req, std::string& res);
};

