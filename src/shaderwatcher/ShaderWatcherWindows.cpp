#if defined(__MINGW32__)

#include "ShaderWatcherWindows.hpp"

#include <windows.h>

#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <locale>
#include <codecvt>

namespace GFX {

void ShaderWatcher::attach(GFX::Shader *shader) {
    this->shaders.insert(std::pair<Shader *, bool>(shader, false));
}

void ShaderWatcher::checkShaders() {
    shadersLock.lock();
    for (auto &shader : shaders) {
        if (shader.second) {
            if (!shader.first->recompile())
                std::cerr << "Shader change detected, but recompilation failed.\n";
            shader.second = false;
        }
    }
    shadersLock.unlock();
}

ShaderWatcher::ShaderWatcher() {
    auto watcher = [&]() {
        LPCSTR shadersDirectory = reinterpret_cast<LPCSTR>(L".\\shaders");

        // Buffer to hold change notifications
        const int bufferLength = 1024;
        char buffer[bufferLength];

        // Create a handle to monitor the directory
        HANDLE hDir = CreateFile(
                shadersDirectory,          // directory to monitor
                FILE_LIST_DIRECTORY,                 // access mask
                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, // share mode
                NULL,                                // security attributes
                OPEN_EXISTING,                       // how to create
                FILE_FLAG_BACKUP_SEMANTICS,          // file attributes
                NULL                                 // template file
        );

        if (hDir == INVALID_HANDLE_VALUE)
        {
            std::cerr << "CreateFile failed: " << GetLastError() << std::endl;
            return;
        }

        while (true)
        {
            DWORD bytesReturned;

            // Read changes to the directory
            if (ReadDirectoryChangesW(
                    hDir,
                    buffer,
                    bufferLength,
                    TRUE,
                    FILE_NOTIFY_CHANGE_FILE_NAME |
                    FILE_NOTIFY_CHANGE_DIR_NAME |
                    FILE_NOTIFY_CHANGE_ATTRIBUTES |
                    FILE_NOTIFY_CHANGE_SIZE |
                    FILE_NOTIFY_CHANGE_LAST_WRITE,
                    &bytesReturned,
                    nullptr,
                    nullptr
            ) == 0)
            {
                std::cerr << "ReadDirectoryChangesW failed: " << GetLastError() << std::endl;
                break;
            }

            auto *fni = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(buffer);
            do
            {
                std::wstring fileName(fni->FileName, fni->FileNameLength / sizeof(WCHAR));
                switch (fni->Action)
                {
                    case FILE_ACTION_MODIFIED:
                        std::wstring shaderName;
                        std::wstringstream ss(fileName);
                        std::getline(ss, shaderName, L'\\');
                        std::getline(ss, shaderName, L'.');

                        this->shadersLock.lock();

                        for (auto &shader : this->shaders) {
                            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
                            std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>> shaderNameW = converter.from_bytes(shader.first->shaderName);
                            if (shaderNameW == shaderName) {
                                shader.second = true;
                            }
                        }

                        this->shadersLock.unlock();

                        break;
                }

                fni = fni->NextEntryOffset ? reinterpret_cast<FILE_NOTIFY_INFORMATION*>(reinterpret_cast<BYTE*>(fni) + fni->NextEntryOffset) : nullptr;
            } while (fni);
        }

        CloseHandle(hDir);
    };

    this->shaderWatcherThread = std::thread(watcher);
}

ShaderWatcher::~ShaderWatcher() {
    this->shaderWatcherThread.detach();
}

}; // namespace GFX

#endif