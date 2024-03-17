#include "pch.h"
#include "THttp.h"
#include <afxinet.h> 
#include <atlenc.h>
#include <string>


THttp::THttp() {
	m_headers = "Content-Type: application/json\n";
}

void THttp::post(
	const char* url,const char* path,
	const std::string& body, std::string& res,
	bool IsHttps) {

	HINTERNET hInternet = nullptr;
	HINTERNET hConnect = nullptr;
	HINTERNET hRequest = nullptr;
	try {
		// Initialize WinINet session
		hInternet = InternetOpenA(nullptr, INTERNET_OPEN_TYPE_DIRECT, nullptr, nullptr, 0);
		if (!hInternet)
			throw "Failed to initialize WinINet session";

		// Connect to the server
		hConnect = InternetConnectA(hInternet, url, INTERNET_DEFAULT_HTTPS_PORT, nullptr, nullptr, INTERNET_SERVICE_HTTP, 0, 1);
		if (!hConnect)
			throw "Failed to connect to the server";

		// Open an HTTPS request
		if (IsHttps) {
			hRequest = HttpOpenRequestA(hConnect, "POST", path, nullptr, nullptr, nullptr, INTERNET_FLAG_SECURE, 1);
		}
		else {
			hRequest = HttpOpenRequestA(hConnect, "POST", path, nullptr, nullptr, nullptr, 0, 1);
		}
		if (!hRequest)
			throw "Failed to open HTTPS request";

		// Send the request
		if (!HttpSendRequestA(hRequest, m_headers.c_str(), m_headers.length(),
			(LPVOID)body.c_str(), body.length() - 1)) {
			throw "Failed to send HTTPS request";
		}

		// Read the response
		const int bufferSize = 1024;
		char buffer[bufferSize + 10];
		DWORD bytesRead = 0;
		while (InternetReadFile(hRequest, buffer, bufferSize, &bytesRead) && bytesRead > 0) {
			buffer[bytesRead] = '\0';
			res += buffer;
		}
	}
	catch (const char* errorMessage) {
		// Handle errors
		AfxMessageBox(CString(errorMessage));
	}

	// Clean up
	if (hRequest)
		InternetCloseHandle(hRequest);
	if (hConnect)
		InternetCloseHandle(hConnect);
	if (hInternet)
		InternetCloseHandle(hInternet);
}