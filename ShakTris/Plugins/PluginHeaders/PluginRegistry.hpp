#pragma once
#include <vector>
#include "Tetris.hpp"
#include <concepts>
#include <type_traits>

#define DLL extern "C" __declspec(dllexport)
#define PLUGIN_SETUP(name, author, description) PLUGIN_SETUP_IMPL(PLUGIN_NAME, name, author, description)

#define PLUGIN_SETUP_IMPL(namespaceName, name, author, description)                                \
    namespace namespaceName {                                                                       \
        DLL void initializePlugin();                                                                 \
        DLL const char* getPluginName() { return name; }                                              \
        DLL const char* getPluginAuthor() { return author; }                                           \
        DLL const char* getPluginDescription() { return description; }                                  \
        }                                                                                                \
    void namespaceName::initializePlugin()

namespace Correct {
    extern std::vector<Shakkar::Tetris*> views;
};
namespace Shakkar {
    using std::derived_from;
    //tamplate stuff to make sure they are definitely being derived from my base class with nothing in it

    
    struct Plugins {
        Plugins() = delete;

        template<Shakkar::derived_from<Shakkar::Tetris> T>
        static void add() {
            return add2(new T());
        }

        static std::vector<Tetris*> getEntries();

    private:
        static void add2(Tetris* view);


    };
};
