#include <GS_CompilerSession.h>

//class Key {
//public:
//
//    explicit Key(HKEY key)
//            : _key(key) {}
//
//public:
//
//    ~Key() {
//        Close();
//    }
//
//public:
//
//    static std::unique_ptr<Key> Create(HKEY key) {
//        return std::make_unique<Key>(key);
//    }
//
//    static std::unique_ptr<Key> Create(HKEY key, const std::string &subKey) {
//        HKEY registryKey = nullptr;
//
//        auto status = RegCreateKeyExA(
//                key,
//                subKey.c_str(),
//                0,
//                nullptr,
//                REG_OPTION_NON_VOLATILE,
//                KEY_READ,
//                nullptr,
//                &registryKey,
//                nullptr);
//
//        if (status != ERROR_SUCCESS) {
//            return nullptr;
//        }
//
//        return Key::Create(registryKey);
//    }
//
//public:
//
//    bool Open(HKEY key) {
//        Close();
//
//        _key = key;
//
//        return true;
//    }
//
//    bool Open(HKEY key, const std::string &subKey) {
//        Close();
//
//        auto status = RegCreateKeyExA(
//                key,
//                subKey.c_str(),
//                0,
//                nullptr,
//                REG_OPTION_NON_VOLATILE,
//                KEY_READ,
//                nullptr,
//                &_key,
//                nullptr);
//
//        if (status != ERROR_SUCCESS) {
//            return false;
//        }
//
//        return true;
//    }
//
//    void Close() {
//        RegCloseKey(_key);
//
//        _key = nullptr;
//    }
//
//public:
//
//    std::string GetString(const std::string &value) {
//        DWORD size = 0;
//
//        auto status = RegGetValueA(
//                _key,
//                nullptr,
//                value.c_str(),
//                RRF_RT_REG_SZ,
//                nullptr,
//                nullptr,
//                &size);
//
//        if (status != ERROR_SUCCESS) {
//            return "";
//        }
//
//        auto buffer = new char[size];
//
//        status = RegGetValueA(
//                _key,
//                nullptr,
//                value.c_str(),
//                RRF_RT_REG_SZ,
//                nullptr,
//                buffer,
//                &size);
//
//        if (status != ERROR_SUCCESS) {
//            return "";
//        }
//
//        std::string string(buffer);
//
//        return string;
//    }
//
//private:
//
//    HKEY _key;
//};
//
//inline auto CreateKey(HKEY key) {
//    return Key::Create(key);
//}
//
//inline auto CreateKey(HKEY key, const std::string &subKey) {
//    return Key::Create(key, subKey);
//}

//using Path = std::filesystem::path;
//using Directory = std::filesystem::directory_entry;
//
//auto FindDirectory(ConstLRef<Path> root, ConstLRef<String> directoryName) {
//    for (auto &entry : std::filesystem::recursive_directory_iterator(root)) {
//        if (entry.is_directory()) {
//            auto name = entry.path().string();
//
//            if (name.ends_with(directoryName)) {
//                return std::make_optional<Directory>(entry);
//            }
//        }
//    }
//
//    return std::make_optional<Directory>();
//};
//
//Vector<String> GetWin10SDKPaths() {
//    HKEY registryKey = nullptr;
//
//    auto status = RegCreateKeyExA(
//            HKEY_LOCAL_MACHINE,
//            R"(SOFTWARE\WOW6432Node\Microsoft\Windows Kits\Installed Roots)",
//            0,
//            nullptr,
//            REG_OPTION_NON_VOLATILE,
//            KEY_READ,
//            nullptr,
//            &registryKey,
//            nullptr);
//
//    if (status != ERROR_SUCCESS) {
//        return {};
//    }
//
//    DWORD size = 0;
//
//    status = RegGetValueA(
//            registryKey,
//            nullptr,
//            "KitsRoot10",
//            RRF_RT_REG_SZ,
//            nullptr,
//            nullptr,
//            &size);
//
//    if (status != ERROR_SUCCESS) {
//        return {};
//    }
//
//    auto buffer = new C8[size];
//
//    status = RegGetValueA(
//            registryKey,
//            nullptr,
//            "KitsRoot10",
//            RRF_RT_REG_SZ,
//            nullptr,
//            buffer,
//            &size);
//
//    if (status != ERROR_SUCCESS) {
//        return {};
//    }
//
//    std::string string(buffer);
//
//    Path sdkPath(string);
//
//    auto directory = FindDirectory(sdkPath, "Lib");
//
//    if (!directory) {
//        return {};
//    }
//
//    auto dirPath = directory.value().path();
//
//    Vector<String> paths;
//
//    auto directory_1 = FindDirectory(dirPath, "um");
//    auto directory_2 = FindDirectory(dirPath, "ucrt");
//
//    if (!directory_1 || !directory_2) {
//        return {};
//    }
//
//    paths.emplace_back(directory_1.value().path().string());
//    paths.emplace_back(directory_2.value().path().string());
//
//    return paths;
//}

namespace GSLanguageCompiler::Driver {

    GS_CompilerSession::GS_CompilerSession(GSCompilerSessionConfigPtr compilerSessionConfig)
            : _config(std::move(compilerSessionConfig)) {}

    SharedPtr<GS_CompilerSession> GS_CompilerSession::Create(GSCompilerSessionConfigPtr compilerSessionConfig) {
        return std::make_shared<GS_CompilerSession>(std::move(compilerSessionConfig));
    }

    CompilingResult GS_CompilerSession::Start(I32 argc, Ptr<Ptr<C8>> argv) {
        auto compilerConfig = GS_CompilerSessionConfig::Create(argc, argv);

        if (!compilerConfig) {
            return CompilingResult::Failure;
        }

        auto compiler = GS_CompilerSession::Create(compilerConfig);

        return compiler->Run();
    }

    CompilingResult GS_CompilerSession::Run() {
        auto unitConfigs = _config->GetUnitConfigs();

        auto unitsManager = GS_TranslationUnitsManager::Create();

        for (auto &unitConfig : unitConfigs) {
            auto unit = GS_TranslationUnit::Create(unitConfig);

            unitsManager->AddUnit(unit);
        }

        auto compilingResults = unitsManager->CompileUnits();

        for (auto &compilingResult : compilingResults) {
            if (compilingResult == CompilingResult::Failure) {
                return CompilingResult::Failure;
            }
        }

// TODO move linking code to new linker class
//
//        auto sdkPaths = GetWin10SDKPaths();
//
//        if (sdkPaths.empty()) {
//            result = 1;
//
//            return result;
//        }
//
//        Vector<ConstPtr<C8>> args;
//
//        auto outputName = _config->GetUnitConfigs()[0]->GetInputName().AsString() + ".o";
//
//        args.emplace_back("");
//        args.emplace_back(outputName.c_str());
//
//        args.emplace_back(R"(/libpath:"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\lib\x64")");
//        args.emplace_back(R"(/libpath:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\ucrt\x64")");
//        args.emplace_back(R"(/libpath:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\um\x64")");
//
//        if (!lld::coff::link(args, llvm::outs(), llvm::errs(), false, false)) {
//            result = CompilingResult::Failure;
//
//            return result;
//        }

        return CompilingResult::Success;
    }

    GSCompilerSessionConfigPtr GS_CompilerSession::GetConfig() const {
        return _config;
    }

}
