#include "TextureConverter.h"

/// stl
#include <filesystem>
#include <windows.h>

/// local
#include "StringUtil.h"

void TextureConverter::ConvertTextureWICToDDS(const std::string& _filePath, int32_t numOptions, char* options[]) {
    /// ==================================================================
    // 1. テクスチャの読み込み
    /// ==================================================================
    LoadWICTextureFromFile(_filePath);

    /// ==================================================================
    // 2. DDS 形式に変換
    /// ==================================================================
    SaveDDSTextureToFile(numOptions, options);
}

void TextureConverter::OutputUsage() const {
    // コンソールのコードページをUTF-8(65001)に設定
    system("chcp 65001");

    printf("画像ファイルをWIC形式からDDS形式に変換します。\n");
    printf("\n");
    printf("TextureConverter [ドライブ:][パス][ファイル名] \n");
    printf("\n");
    printf("[ドライブ:][パス][ファイル名]: 変換したいWIC形式の画像ファイルを指定します｡\n");
    printf("\n");
    printf("オプション:\n");
    printf("-ml [ミップレベル]: ミップレベルを指定します｡ 0を指定するとフルミップマップチェーンを生成します｡\n");
    printf("-output or -o [出力先]: 指定されたpathに出力されます。(ファイル名まで指定する事ができます。)\n");
}

void TextureConverter::LoadWICTextureFromFile(const std::string& _filePath) {
    HRESULT result = S_OK;

    std::wstring wFilePath = ConvertMultiByteToWide(_filePath);

    /// ==================================================================
    // WICテクスチャの読み込み
    /// ==================================================================
    result = DirectX::LoadFromWICFile(wFilePath.c_str(), DirectX::WIC_FLAGS_NONE, &metadata_, scratchImage_);
    if (FAILED(result)) {
        assert(0 && "Failed to load WIC texture from file.");
        return;
    }
    SeparateFilePath(wFilePath, directory_, filename_, extension_);

    // out ファイル名とディレクトリを初期化
    outDirectory_ = directory_;
    outFilename_  = filename_;
}

void TextureConverter::SaveDDSTextureToFile(int32_t numOptions, char* options[]) {
    HRESULT result = S_OK;

    /// ==================================================================
    // options の解析
    /// ==================================================================
    int32_t mipLevels = 0;
    for (int32_t i = 0; i < numOptions; ++i) {
        std::string optionStr = options[i];
        if (optionStr == "-ml") {
            mipLevels = std::stoi(options[i + 1]);
            break;
        } else if (optionStr == "-output" || optionStr == "-o") {
            // 出力ファイル名の指定
            std::filesystem::path outputPath = options[i + 1];
            if (outputPath.has_parent_path()) {
                outDirectory_ = ConvertMultiByteToWide(outputPath.parent_path().string());
            }
            if (outputPath.has_filename()) {
                outFilename_ = ConvertMultiByteToWide(outputPath.stem().string());
            }
        } else {
            printf("不明なオプションです: %s\n", options[i]);
            OutputUsage();
            return;
        }
    }

    /// ==================================================================
    // mipMapの生成
    /// ==================================================================
    DirectX::ScratchImage mipChain;
    result = DirectX::GenerateMipMaps(
        scratchImage_.GetImages(),
        scratchImage_.GetImageCount(),
        scratchImage_.GetMetadata(),
        DirectX::TEX_FILTER_DEFAULT,
        mipLevels,
        mipChain);

    if (SUCCEEDED(result)) {
        scratchImage_ = std::move(mipChain); // コピーは禁止なのでムーブ
        metadata_     = scratchImage_.GetMetadata();
    }
    /// ==================================================================
    // 圧縮テクスチャへの変換
    /// ==================================================================
    DirectX::ScratchImage converted;
    result = DirectX::Compress(
        scratchImage_.GetImages(),
        scratchImage_.GetImageCount(),
        metadata_,
        DXGI_FORMAT_BC7_UNORM_SRGB,
        DirectX::TEX_COMPRESS_BC7_QUICK | DirectX::TEX_COMPRESS_SRGB_OUT | DirectX::TEX_COMPRESS_PARALLEL,
        1.f,
        converted);

    if (SUCCEEDED(result)) {
        scratchImage_ = std::move(converted); // コピーは禁止なのでムーブ
        metadata_     = scratchImage_.GetMetadata();
    }

    /// ==================================================================
    // 読み込んだディフーズテクスチャを SRGBとして扱う
    /// ==================================================================
    metadata_.format = DirectX::MakeSRGB(metadata_.format);

    /// ==================================================================
    // DDS テクスチャの保存
    /// ==================================================================
    result = DirectX::SaveToDDSFile(
        scratchImage_.GetImages(),
        scratchImage_.GetImageCount(),
        metadata_,
        DirectX::DDS_FLAGS_NONE,
        (outDirectory_ + outFilename_ + L".dds").c_str());

    assert(SUCCEEDED(result) && "Failed to save DDS texture to file.");
}