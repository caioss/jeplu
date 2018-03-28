#include "JepluLibFinder.hpp"

#include <QDebug>
#include <QDirIterator>
#include <QLibrary>

JepluLibFinder::JepluLibFinder(const std::string &path) :
#ifdef _WIN32            // If Windows, set suffix as .dll
    _libSuffix(".dll"),
    _hasLibPrefix(false)
#elif defined __linux__  // If linux, set suffix as .so
    _libSuffix(".so"),
    _hasLibPrefix(true)
#elif defined __APPLE__  // If OSx, set suffix as .dylib
    _libSuffix(".dylib"),
    _hasLibPrefix(true)
#endif
{
    _findLibsPath(path);
}

std::vector<std::string> JepluLibFinder::libsPath() const
{
    return _libsPath;
}

void JepluLibFinder::_findLibsPath(const std::string &path)
{
    QDir pluginsDir(QString::fromStdString(path));
    for (QString pluginPath : pluginsDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        // The lib should be named as path/libname/[osprefix lib]+libname.[so|dll|dylib]
        // unix example: example/libexample.[so|dylib]; Windows example: example/example.dll
        QString libPath = QString::fromStdString(path) + pluginPath +
                          (_hasLibPrefix ? "/lib" : "/") + pluginPath + _libSuffix;

        if (QLibrary::isLibrary(libPath))
        {
            qDebug() << "Lib " << libPath << " found.";
            _libsPath.push_back(libPath.toStdString());
        }
    }
}
