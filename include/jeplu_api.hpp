// MSVC needs these specifications to export and import a class or function to/from a dll.
// see: https://msdn.microsoft.com/en-us/library/dabb5z75.aspx
#ifdef _WIN32
    #ifdef JEPLU_EXPORTS
        // If marked to export, mark as dllexport to MSVC mark a symbol as exported from a DLL.
        #define JEPLULIB_API __declspec(dllexport)
    #else
        // If not marked to export, use dllimport to import that exported symbol to another file.
        #define JEPLULIB_API __declspec(dllimport)
    #endif
#else
    #define JEPLULIB_API
#endif
