#pragma once

#include <string>

std::wstring ConvertMultiByteToWide(const std::string& str);

/// <summary>
/// ファイルパスをディレクトリ、ファイル名、拡張子に分離する
/// </summary>
/// <param name="_fullPath">分離するファイルパス</param>
/// <param name="_directory">分離されたディレクトリ</param>
/// <param name="_filename">分離されたファイル名</param>
/// <param name="_extension">分離された拡張子</param
void SeparateFilePath(const std::wstring& _fullPath, std::wstring& _directory, std::wstring& _filename, std::wstring& _extension);