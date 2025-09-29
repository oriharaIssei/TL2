#pragma once

#include <string>

class TextureConverter {
public:
	/// <summary>
	/// 指定されたファイルパスのWICテクスチャをDDS形式に変換します。
	/// </summary>
	/// <param name="_filePath">変換するWICテクスチャファイルのパス。</param>
	void ConvertTextureWICToDDS(const std::string& _filePath);

private:
    /// <summary>
    /// WICテクスチャをファイルから読み込む
    /// </summary>
    void LoadWICTextureFromFile(const std::string& _filePath);
};
