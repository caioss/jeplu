#ifndef JEPLULIBFINDER_HPP
#define JEPLULIBFINDER_HPP

#include "ILibFinder.hpp"

#include <QString>

/**
 *  \brief The class JepluLibFinder implements \c ILibFinder to find and retrieve libraries path.
 *
 *  This module looks for any dynamic library that is inside a dir with the library name. For example, given the file
 *  structure:
 *  plugins/
 *      example/
 *          libexample.so
 *      custom-example/
 *          libcustomexample.so
 *
 * In that case, the library "libexample.so" will be given as found and "libcustomexample.so" will never be found
 * because "-" is missing in its name.
 *
 * In Windows system, the prefix "lib" is ignored by default. So if the DLL actually have "lib" on its name
 * (e.g: libmodulex.dll), it should be inside a dir that also have prefix "lib" (libmodulex/libmodulex.dll).
 */
class JepluLibFinder : public ILibFinder
{
public:
    /**
     *  \brief Default constructor.
     */
    JepluLibFinder(const std::string &path);

    std::vector<std::string> libsPath() const override;

private:
    /**
     *  \brief Look inside each subdir of \c path for a library file.
     *
     *  The library file should be named as its dir name. If looking dir "example-module" the lib inside this dir should
     *  be named as "libexample-module.[so|dylib]", for Linux and OSx and named as "example-module.dll" for Windows.
     *
     *  \param path The root path where the libraries will be located inside its own subdir.
     */
    void _findLibsPath(const std::string &path);

    /**
     *  \brief A vector containing all library paths that was found.
     */
    std::vector<std::string> _libsPath;

    /**
     *  \brief Hold the suffix of the lib that will be loaded.
     *  It can be .so, .dll or .dylib for Linux, Windows and OSx respectively.
     */
    const QString _libSuffix;

    /**
     *  \brief Indicates if the lib name has the prefix "lib". On Windows system it's \c false and on Unix \c true.
     */
    const bool _hasLibPrefix;
};

#endif //JEPLULIBFINDER_HPP
