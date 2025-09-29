#include <assert.h>

#include <cstdio>
#include <cstdlib>

#include <Windows.h>

/// local
#include "TextureConverter.h"

///math
#include <cstdint>

enum ArgmentIndex {
    ARG_APPLICATION_PATH,
    ARK_FILE_PATH,
    ARG_NUM
};

static void ComInitialize() {
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    assert(SUCCEEDED(hr) && "Failed to initialize COM library.");
}

int main(int argc, char* argv[]) {
   
    assert(argc >= ARG_NUM);

    ComInitialize();

    TextureConverter converter;
    converter.ConvertTextureWICToDDS(argv[ARK_FILE_PATH]);

    system("pause");

    return 0;
}
