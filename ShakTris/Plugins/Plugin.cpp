#include "Plugin.hpp"
#include<iostream>

namespace fs = std::filesystem;

constexpr auto InitializePluginSymbol = "_ZN6plugin{0}{1}8internal16initializePluginEv";
constexpr auto GetPluginNameSymbol = "_ZN6plugin{0}{1}8internal13getPluginNameEv";
constexpr auto GetPluginAuthorSymbol = "_ZN6plugin{0}{1}8internal15getPluginAuthorEv";
constexpr auto GetPluginDescriptionSymbol = "_ZN6plugin{0}{1}8internal20getPluginDescriptionEv";
constexpr auto SetImGuiContextSymbol = "_ZN6plugin{0}{1}8internal15setImGuiContextEP12ImGuiContext";


Plugin::Plugin(std::string_view path) {
    this->m_handle = dlopen(path.data(), RTLD_LAZY);
    
    if (this->m_handle == nullptr) {
        std::cout << ("dlopen failed: {}", dlerror()) << std::endl<;
        return;
    }

    auto pluginName = fs::path(path).stem().string();

    this->m_initializePluginFunction = getPluginFunction<InitializePluginFunc>(pluginName, InitializePluginSymbol);
    this->m_getPluginNameFunction = getPluginFunction<GetPluginNameFunc>(pluginName, GetPluginNameSymbol);
    this->m_getPluginAuthorFunction = getPluginFunction<GetPluginAuthorFunc>(pluginName, GetPluginAuthorSymbol);
    this->m_getPluginDescriptionFunction = getPluginFunction<GetPluginDescriptionFunc>(pluginName, GetPluginDescriptionSymbol);
    
}

Plugin::Plugin(Plugin&& other) noexcept {
    this->m_handle = other.m_handle;
    this->m_initializePluginFunction = other.m_initializePluginFunction;
    this->m_getPluginNameFunction = other.m_getPluginNameFunction;
    this->m_getPluginAuthorFunction = other.m_getPluginAuthorFunction;
    this->m_getPluginDescriptionFunction = other.m_getPluginDescriptionFunction;

    other.m_handle = nullptr;
    other.m_initializePluginFunction = nullptr;
    other.m_getPluginNameFunction = nullptr;
    other.m_getPluginAuthorFunction = nullptr;
    other.m_getPluginDescriptionFunction = nullptr;
}

Plugin::~Plugin() {
    if (this->m_handle != nullptr)
        dlclose(this->m_handle);
}

void Plugin::initializePlugin() const {
    if (this->m_initializePluginFunction != nullptr)
        this->m_initializePluginFunction();
}

std::string Plugin::getPluginName() const {
    if (this->m_getPluginNameFunction != nullptr)
        return this->m_getPluginNameFunction();
    else
        return hex::format("Unknown Plugin @ 0x{0:016X}", reinterpret_cast<intptr_t>(this->m_handle));
}

std::string Plugin::getPluginAuthor() const {
    if (this->m_getPluginAuthorFunction != nullptr)
        return this->m_getPluginAuthorFunction();
    else
        return "Unknown";
}

std::string Plugin::getPluginDescription() const {
    if (this->m_getPluginDescriptionFunction != nullptr)
        return this->m_getPluginDescriptionFunction();
    else
        return "";
}

bool PluginManager::load(std::string_view pluginFolder) {
    if (!std::filesystem::exists(pluginFolder))
        return false;

    PluginManager::s_pluginFolder = pluginFolder;

    for (auto& pluginPath : std::filesystem::directory_iterator(pluginFolder)) {
        if (pluginPath.is_regular_file() && pluginPath.path().extension() == ".tetris")
            PluginManager::s_plugins.emplace_back(pluginPath.path().string());
    }

    if (PluginManager::s_plugins.empty())
        return false;

    return true;
}

void PluginManager::unload() {
    PluginManager::s_plugins.clear();
    PluginManager::s_pluginFolder.clear();
}

void PluginManager::reload() {
    PluginManager::unload();
    PluginManager::load(PluginManager::s_pluginFolder);
}

std::vector<std::string> getPath() {
#if defined(WIN32)
    std::string exePath(MAX_PATH, '\0');
    GetModuleFileName(nullptr, exePath.data(), exePath.length());
    auto parentDir = std::filesystem::path(exePath).parent_path();

    std::filesystem::path appDataDir;
    {
        LPWSTR wAppDataPath = nullptr;
        if (!SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, nullptr, &wAppDataPath)))
            throw std::runtime_error("Failed to get APPDATA folder path");

        appDataDir = wAppDataPath;
        CoTaskMemFree(wAppDataPath);
    }

        return { (parentDir / "plugins").string() };
#elif defined(OS_MACOS)
    return { getPathForMac(path) };
#else
    std::vector<std::filesystem::path> configDirs = xdg::ConfigDirs();
    std::vector<std::filesystem::path> dataDirs = xdg::DataDirs();

    configDirs.insert(configDirs.begin(), xdg::ConfigHomeDir());
    dataDirs.insert(dataDirs.begin(), xdg::DataHomeDir());

    std::vector<std::string> result;

        std::transform(dataDirs.begin(), dataDirs.end(), std::back_inserter(result),
            [](auto p) { return (p / "ShakTris" / "plugins").string(); });
        return result;
    }
#endif
}

bool loadPlugins() {
    for (const auto& dir : getPath()) {
        PluginManager::load(dir);
    }

    if (PluginManager::getPlugins().empty()) {
        return false;
    }

    for (const auto& plugin : PluginManager::getPlugins()) {
        plugin.initializePlugin(); 
    }

    return true;
}

bool unloadPlugins() {
    PluginManager::unload();

    return true;
}