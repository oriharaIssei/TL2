#include "TextureConverter.h"

#include "StringUtil.h"

void TextureConverter::ConvertTextureWICToDDS(const std::string& _filePath) {
    /// ==================================================================
    // 1. テクスチャの読み込み
    /// ==================================================================
    LoadWICTextureFromFile(_filePath);

    /// ==================================================================
    // 2. DDS 形式に変換
    /// ==================================================================
    SaveDDSTextureToFile();
}

void TextureConverter::LoadWICTextureFromFile(const std::string& _filePath) {
    HRESULT result = S_OK;

    std::wstring wFilePath = ConvertMultiByteToWide(_filePath);

    /// ==================================================================
    // 1. WICテクスチャの読み込み
    /// ==================================================================
    result = DirectX::LoadFromWICFile(wFilePath.c_str(), DirectX::WIC_FLAGS_NONE, &metadata_, scratchImage_);
    if (FAILED(result)) {
        assert(0 && "Failed to load WIC texture from file.");
        return;
    }
    SeparateFilePath(wFilePath, directory_, filename_, extension_);

    /// ==================================================================
    // 2. 読み込んだディフーズテクスチャを SRGBとして扱う
    /// ==================================================================
    metadata_.format = DirectX::MakeSRGB(metadata_.format);
}

void TextureConverter::SaveDDSTextureToFile() {
    HRESULT result = S_OK;

    result = DirectX::SaveToDDSFile(
        scratchImage_.GetImages(),
        scratchImage_.GetImageCount(),
        metadata_,
        DirectX::DDS_FLAGS_NONE,
        (directory_ + filename_ + L".dds").c_str());

    assert(SUCCEEDED(result) && "Failed to save DDS texture to file.");
}
