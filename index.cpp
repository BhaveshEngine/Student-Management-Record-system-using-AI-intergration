#include <iostream>
#include <windows.h>
#include <winhttp.h>
#include "json.hpp"

#pragma comment(lib, "winhttp.lib")

using namespace std;
using json = nlohmann::json;

int main()
{
    HINTERNET session = WinHttpOpen(
        L"OllamaTest",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0
    );

    HINTERNET connect = WinHttpConnect(
        session,
        L"localhost",
        11434,
        0
    );

    HINTERNET request = WinHttpOpenRequest(
        connect,
        L"POST",
        L"/api/generate",
        NULL,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        0
    );

    // JSON request sent to Ollama
    string requestBody =
        R"({
            "model": "qwen3.5:4b",
            "prompt": "Say hello from C++",
            "stream": false
        })";

    WinHttpSendRequest(
        request,
        L"Content-Type: application/json",
        -1,
        (LPVOID)requestBody.c_str(),
        requestBody.size(),
        requestBody.size(),
        0
    );

    WinHttpReceiveResponse(request, NULL);

    // Receive Ollama response
    char buffer[4096];
    DWORD bytesRead;

    string result;

    while (WinHttpReadData(
        request,
        buffer,
        sizeof(buffer) - 1,
        &bytesRead))
    {
        if (bytesRead == 0)
            break;

        buffer[bytesRead] = '\0';
        result += buffer;
    }

    // Parse JSON
    json data = json::parse(result);

    // Get only AI response
    string response = data["response"];

    cout << "\nAI: " << response << endl;

    WinHttpCloseHandle(request);
    WinHttpCloseHandle(connect);
    WinHttpCloseHandle(session);

    return 0;
}