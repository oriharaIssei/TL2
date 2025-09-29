#include "StringUtil.h"

#include <Windows.h>

std::wstring ConvertMultiByteToWide(const std::string& str) {
    if (str.empty()) {
        return std::wstring();
    }
    int wideSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
    std::wstring wstrTo(wideSize, 0);
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &wstrTo[0], wideSize);

    return wstrTo;
}