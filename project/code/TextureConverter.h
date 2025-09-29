#pragma once

#include <string>

#include <DirectXTex.h>

class TextureConverter {
public:
    /// <summary>
    /// 指定されたファイルパスのWICテクスチャをDDS形式に変換する
    /// </summary>
    /// <param name="_filePath">変換するWICテクスチャファイルのパス</param>
    void ConvertTextureWICToDDS(const std::string& _filePath, int32_t numOptions, char* options[]);

    /// <summary>
    /// 使用方法を出力する
    /// </summary>
    void OutputUsage()const;
private:
    /// <summary>
    /// WICテクスチャをファイルから読み込む
    /// </summary>
    void LoadWICTextureFromFile(const std::string& _filePath);

    /// <summary>
    /// DDSテクスチャをファイルに保存する
    /// </summary>
    void SaveDDSTextureToFile(int32_t numOptions, char* options[]);

private:
    std::wstring directory_;
    std::wstring filename_;
    std::wstring extension_;

    DirectX::TexMetadata metadata_;
    DirectX::ScratchImage scratchImage_;
};
