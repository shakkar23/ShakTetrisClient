#pragma once
#ifndef PLUGIN_MANAGER
#define PLUGIN_MANAGER
#include <string>
#include <string_view>
#include <filesystem>
#include <algorithm>
#include <string>
#include <vector>
#include "../../Platform/SDL2/headers/RenderWindow.hpp"

#if defined(_WINDOWS)
#include <windows.h>
#include <shlobj.h>
#include <winuser.h>
#include <dwmapi.h>
#include <windowsx.h>
#elif defined(OS_LINUX)
#include <xdg.hpp>
#endif
class Plugin {
public:
    Plugin(std::string_view path);
    Plugin(const Plugin&) = delete;
    Plugin(Plugin&& other) noexcept;
    Plugin() {}
    ~Plugin();

    void initializePlugin(RenderWindow& window) const;
    std::string getPluginName() const;
    std::string getPluginAuthor() const;
    std::string getPluginDescription() const;
    //void setImGuiContext(ImGuiContext* ctx) const;


private:
    using InitializePluginFunc = void(*)(void *window);
    using GetPluginNameFunc = const char* (*)();
    using GetPluginAuthorFunc = const char* (*)();
    using GetPluginDescriptionFunc = const char* (*)();
    //using SetImGuiContextFunc = void(*)(ImGuiContext*);

    HMODULE m_handle = nullptr;

    InitializePluginFunc m_initializePluginFunction = nullptr;
    GetPluginNameFunc m_getPluginNameFunction = nullptr;
    GetPluginAuthorFunc m_getPluginAuthorFunction = nullptr;
    GetPluginDescriptionFunc m_getPluginDescriptionFunction = nullptr;
    //SetImGuiContextFunc m_setImGuiContextFunction = nullptr;



    template<typename T>
    auto getPluginFunction(std::string &symbol) {
        return reinterpret_cast<T>(GetProcAddress(this->m_handle, symbol.data()));
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

bool loadPlugins(RenderWindow& window);
bool unloadPlugins();
std::vector<std::string> getPath();

#endif