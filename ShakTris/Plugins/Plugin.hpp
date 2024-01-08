#pragma once

#include <string>
#include <string_view>
#include <filesystem>
#include <algorithm>
#include <string>
#include <vector>

#if defined(_WINDOWS)
#include <windows.h>
#include <shlobj.h>
#include <winuser.h>
#include <dwmapi.h>
#include <windowsx.h>
#elif defined(OS_LINUX)
#include <xdg.hpp>
#endif

#define PLUGIN_SETUP(name, author, description) PLUGIN_SETUP_IMPL(PLUGIN_NAME, name, author, description)

#define PLUGIN_SETUP_IMPL(namespaceName, name, author, description)                                \
    namespace plugin::namespaceName::internal {                                                     \
        [[gnu::visibility("default")]] void initializePlugin();                                      \
        [[gnu::visibility("default")]] const char* getPluginName() { return name; }                   \
        [[gnu::visibility("default")]] const char* getPluginAuthor() { return author; }                \
        [[gnu::visibility("default")]] const char* getPluginDescription() { return description; }       \
        }                                                                                                \
    void plugin::namespaceName::internal::initializePlugin()

class PlayMenuGUI;
class Plugin {
    friend PlayMenuGUI;
public:
    Plugin(std::string_view path);
    Plugin(const Plugin&) = delete;
    Plugin(Plugin&& other) noexcept;
    ~Plugin();

    void initializePlugin() const;
    std::string getPluginName() const;
    std::string getPluginAuthor() const;
    std::string getPluginDescription() const;
    //void setImGuiContext(ImGuiContext* ctx) const;


private:
    using InitializePluginFunc = void(*)();
    using GetPluginNameFunc = const char* (*)();
    using GetPluginAuthorFunc = const char* (*)();
    using GetPluginDescriptionFunc = const char* (*)();
    //using SetImGuiContextFunc = void(*)(ImGuiContext*);

    void* m_handle = nullptr;

    InitializePluginFunc m_initializePluginFunction = nullptr;
    GetPluginNameFunc m_getPluginNameFunction = nullptr;
    GetPluginAuthorFunc m_getPluginAuthorFunction = nullptr;
    GetPluginDescriptionFunc m_getPluginDescriptionFunction = nullptr;
    //SetImGuiContextFunc m_setImGuiContextFunction = nullptr;



    template<typename T>
    auto getPluginFunction(std::string_view pluginName, std::string_view symbol) {
        auto symbolName = format(symbol.data(), pluginName.length(), pluginName.data());
        return reinterpret_cast<T>(dlsym(this->m_handle, symbolName.c_str()));
    };
};

class PluginManager {
public:
    PluginManager() = delete;

    static bool load(std::string_view pluginFolder);
    static void unload();
    static void reload();

    static const auto& getPlugins() {
        return PluginManager::s_plugins;
    }

private:
    static inline std::string s_pluginFolder;
    static inline std::vector<Plugin> s_plugins;
};

bool loadPlugins();
bool unloadPlugins();
std::vector<std::string> getPath();