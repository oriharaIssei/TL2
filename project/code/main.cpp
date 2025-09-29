#include <assert.h>

#include <cstdio>
#include <cstdlib>

#include <Windows.h>

/// local
#include "TextureConverter.h"

/// math
#include <cstdint>

enum ArgmentIndex {
    ARG_APPLICATION_PATH,
    ARG_FILE_PATH,
    ARG_NUM
};

static void ComInitialize() {
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    assert(SUCCEEDED(hr) && "Failed to initialize COM library.");
}

int main(int argc, char* argv[]) {

    TextureConverter converter;

    // コマンドラインに引数が足りない場合は使用方法を出力して終了
    if (argc < ARG_NUM) {
        converter.OutputUsage();
        return 0;
    }

    // COMライブラリの初期化
    ComInitialize();
    // WICテクスチャをDDS形式に変換
    int numOptions = argc - ARG_NUM;
    char** options = argv + ARG_NUM;
    converter.ConvertTextureWICToDDS(argv[ARG_FILE_PATH], numOptions,options);

    return 0;
}
