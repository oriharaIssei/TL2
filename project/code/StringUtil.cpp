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

void SeparateFilePath(const std::wstring& _fullPath, std::wstring& _directory, std::wstring& _filename, std::wstring& _extension) {
    size_t dotPos;
    std::wstring exceptExtension;

    /// ディレクトリとファイル名の分離
    // dotの最後の位置を検索
    dotPos = _fullPath.rfind('.');

    // 検索が成功した場合
    if (dotPos != std::wstring::npos) {
        // 区切り文字の前をディレクトリとファイル名として 取得
        exceptExtension = _fullPath.substr(0, dotPos);
        // 区切り文字の後ろを拡張子として 取得
        _extension = _fullPath.substr(dotPos + 1, _fullPath.size() - dotPos - 1);
    } else { // 検索が失敗した場合
        exceptExtension = _fullPath;
        _extension      = L"";
    }

    // 区切り文字の最後の位置を検索
    size_t slashPos = exceptExtension.rfind('\\');
    if (slashPos != std::wstring::npos) {
        _directory = exceptExtension.substr(0, slashPos + 1);
        _filename  = exceptExtension.substr(slashPos + 1, exceptExtension.size() - slashPos - 1);
        return;
    }

    slashPos = exceptExtension.rfind('/');
    if (slashPos != std::wstring::npos) {
        _directory = exceptExtension.substr(0, slashPos + 1);
        _filename  = exceptExtension.substr(slashPos + 1, exceptExtension.size() - slashPos - 1);
        return;
    }

    // 失敗
    _directory = L"";
    _filename  = exceptExtension;
}
