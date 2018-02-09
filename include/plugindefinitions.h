#ifndef PLUGINDEFINITIONS_H
#define PLUGINDEFINITIONS_H

#if defined _WIN32 || defined __CYGWIN__
    #define PLUGIN_DLL_IMPORT __declspec(dllimport)
    #define PLUGIN_DLL_EXPORT __declspec(dllexport)
    #define PLUGIN_DLL_LOCAL
#else
    #if __GNUC__ >= 4
        #define PLUGIN_DLL_IMPORT __attribute__ ((visibility("default")))
        #define PLUGIN_DLL_EXPORT __attribute__ ((visibility("default")))
        #define PLUGIN_DLL_LOCAL  __attribute__ ((visibility("hidden")))
    #else
        #define PLUGIN_DLL_IMPORT
        #define PLUGIN_DLL_EXPORT
        #define PLUGIN_DLL_LOCAL
    #endif
#endif

// *< PLUGIN_API is used for the public API symbols.
#define PLUGIN_API	PLUGIN_DLL_EXPORT
// *< PLUGIN_LOCAL is used for non-API symbols.
#define PLUGIN_LOCAL	PLUGIN_DLL_LOCAL

#endif
