#ifndef QTLOADER_H
#define QTLOADER_H

#include "IPluginLoader.hpp"

#include <memory>
#include <QList>
#include <QFile>

/**
 *  \brief The \c QtLoader class implements \c IPluginLoader.
 *
 *  It loads any dynamic library created using Qt. A compatible dynamic library implements an object of type \c QObject
 *  that inherits from \c IPlugin interface registered into the \c Qt macros.
 *
 *  The file \c ipluginloader.hpp provides the registration of the \c IPlugin interface. This is an example of a supported plugin:
 *
 *  \code
 *  #include "ipluginloader.hpp"
 *
 *  Class CustomClass : public QObject, public IPlugin
 *  {
 *      QOBJECT
 *      Q_PLUGIN_METADATA(IID "customclass.id")
 *      Q_INTERFACE(IPlugin)
 *
 *      ... // overrided methods
 *  }
 *  \endcode
 */
class QtLoader : public IPluginLoader
{
public:
    /**
     *  \brief Default constructor.
     */
    QtLoader();

    LoadingErrors loadPlugin(const std::string &pluginPath, std::shared_ptr<IPlugin> &plugin) override;

    std::string name() const override { return "Qt Loader"; }

    std::string errString() const override;

private:
    /**
     *  \brief Holds the last error string.
     */
    std::string _errStr;
};

#endif // QTLOADER_H
