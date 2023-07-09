#pragma once
#include <vector>
#include "Tetris.hpp"
#include "../PluginManager.hpp"
#include <concepts>
#include <type_traits>

#define DLL extern "C" __declspec(dllexport)

#define PLUGIN_SETUP(name, author, description) PLUGIN_SETUP_IMPL(PLUGIN_NAME, name, author, description)

#define PLUGIN_SETUP_IMPL(namespaceName, name, author, description)                                \
    namespace namespaceName {                                                                       \
        DLL void initializePlugin(void *window);                                                     \
        DLL const char* getPluginName() { return name; }                                              \
        DLL const char* getPluginAuthor() { return author; }                                           \
        DLL const char* getPluginDescription() { return description; }                                  \
        }                                                                                                \
    void namespaceName::initializePlugin(void *window)

namespace Shakkar {
    using std::derived_from;
    //tamplate stuff to make sure they are definitely being derived from my base class

    
    struct Plugins {
        Plugins() = delete;
        template<Shakkar::derived_from<Shakkar::Tetris> T, typename ... Args>
        static void addorig(Args&& ... args) {
            return add2(new T(std::forward<Args>(args)...));
        }
        template<Shakkar::derived_from<Shakkar::Tetris> T>
            static void addnew() {
            return add2(new T());
        }

        static std::vector<Tetris*> &getEntries();

        static void add2(Tetris* game);


    };



    
};
