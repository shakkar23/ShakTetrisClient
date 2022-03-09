#include "PluginManager.hpp"
#include<iostream>
#include <chrono>

//#include"NameMangling/NameMangler.hpp"

namespace fs = std::filesystem;


Plugin::Plugin(std::string_view path) {
    this->m_handle = LoadLibraryA(path.data());
    
    if (this->m_handle == nullptr) {
        std::cout << ("loading a plugin failed") << std::endl;
        return;
    }
    std::string initializePlugin("initializePlugin");
    std::string getPluginName("getPluginName");
    std::string GetPluginAuthor("getPluginAuthor");
    std::string GetPluginDescription("getPluginDescription");
    this->m_initializePluginFunction = getPluginFunction<InitializePluginFunc>(initializePlugin);
    this->m_getPluginNameFunction = getPluginFunction<GetPluginNameFunc>(getPluginName);
    this->m_getPluginAuthorFunction = getPluginFunction<GetPluginAuthorFunc>(GetPluginAuthor);
    this->m_getPluginDescriptionFunction = getPluginFunction<GetPluginDescriptionFunc>(GetPluginDescription);
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
        FreeLibrary(this->m_handle);
}

void Plugin::initializePlugin(RenderWindow& window) const {
    if (this->m_initializePluginFunction != nullptr) {
        this->m_initializePluginFunction((void *)&window);
    }
    else {
        std::cout << ":( couldnt initialize" << std::endl;
    }
}

std::string Plugin::getPluginName() const {
    if (this->m_getPluginNameFunction != nullptr)
        return this->m_getPluginNameFunction();
    else
        return ("Unknown Plugin");
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
        return "Unknown Description";
}


Uint32 AudioManager::wav_length = {}; // length of our sample
Uint8* AudioManager::wav_buffer = {}; // buffer containing our audio file

SDL_AudioSpec AudioManager::wav_spec = {}; // the specs of our piece of music
AudioManager::~AudioManager() {
    SDL_FreeWAV(wav_buffer);
}
AudioManager::AudioManager() {
    // make a wav file to be called forever, imm abusing the forever part for cool things and such
    // notice that im not actually playing it, its just for the side affect of being called forever
    if (SDL_LoadWAV(mus2, &wav_spec, &wav_buffer, &wav_length) == NULL) {
        printf("couldnt load music");
    }

    wav_spec.callback = callback;

    /* Open the audio device */
    SDL_OpenAudio(&wav_spec, NULL);

    /* Start playing */
    SDL_PauseAudio(0);
}

void AudioManager::callback(void* userdata, Uint8* stream, int len) {
    //old code i want to keep
    // // simply copy from one buffer into the other
    //SDL_memcpy (stream, audio_pos, len); 		
    //SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME / 8);// mix from one buffer into another

    const int length = len;

    //empty the stream, as it is not done by default :(
    //128 is actual silence
    SDL_memset(stream, 128, length);
    for (auto audio = Shakkar::autoAudio::audios.begin(); audio != Shakkar::autoAudio::audios.end();) {
        if (((*audio)->audio_len == 0) || ((*audio)->audio_len == 1))
        {
            delete (*audio);
            audio = Shakkar::autoAudio::audios.erase(audio);
        }
        else {
            const int bounds = (length > (*audio)->audio_len ? ((*audio)->audio_len - 1) : length);
            //SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
            SDL_MixAudio(stream, (*audio)->audio_pos, bounds, (*audio)->volume);// mix from one buffer into another

            (*audio)->audio_pos += bounds;
            (*audio)->audio_len -= bounds;

            ++audio;
        }
    }

}

bool PluginManager::load(std::string_view pluginFolder) {
    if (!std::filesystem::exists(pluginFolder))
    {
        throw std::runtime_error("Failed to find plugin folder");
        return false;
    }

    PluginManager::s_pluginFolder = pluginFolder;

    for (auto& pluginPath : std::filesystem::directory_iterator(pluginFolder)) {
        if (pluginPath.is_regular_file() && pluginPath.path().extension() == ".tetris")
            PluginManager::s_plugins.emplace_back(pluginPath.path().string());
    }

    if (PluginManager::s_plugins.empty())
    {
        throw std::runtime_error("Plugin Folder Empty");
        return false;
    }

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
    GetModuleFileNameA(nullptr, exePath.data(), exePath.length());
    auto parentDir = std::filesystem::path(exePath).parent_path();

    std::filesystem::path appDataDir;
    {
        LPWSTR wAppDataPath = nullptr;
        if (!SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, nullptr, &wAppDataPath)))
            throw std::runtime_error("Failed to get APPDATA folder path");

        appDataDir = wAppDataPath;
        CoTaskMemFree(wAppDataPath);
    }
        return { (parentDir / "plugins").string()};
#elif defined(OS_MACOS)
    return { getPathForMac(path) };
#else
    std::vector<std::filesystem::path> configDirs = xdg::ConfigDirs();
    std::vector<std::filesystem::path> dataDirs = xdg::DataDirs();

    configDirs.insert(configDirs.begin(), xdg::ConfigHomeDir());
    dataDirs.insert(dataDirs.begin(), xdg::DataHomeDir());

    std::vector<std::string> result;

        std::transform(dataDirs.begin(), dataDirs.end(), std::back_inserter(result),
            [](auto p) { return (p / "bin/plugins").string(); });
        return result;
    }
#endif
}

bool loadPlugins(RenderWindow &window) {
    printf("loading Plugins");
    for (const auto& dir : getPath()) {
        PluginManager::load(dir);
    }

    if (PluginManager::getPlugins().empty()) {
        return false;
    }

    for (const auto& plugin : PluginManager::getPlugins()) {
        plugin.initializePlugin(window);
    }

    return true;
}

bool unloadPlugins() {
    PluginManager::unload();

    return true;
}