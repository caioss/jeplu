#ifndef PLUGIN_H
#define PLUGIN_H

#include <string>

/**
 *  \brief Class IPlugin
 *
 *  The \c IPlugin interface is the base class for all the plugins. It's the plugin object which can be created or used
 *  anytime. For it's usage, a \c IPluginProxy should be created to cast this \c IPlugin object to the desired type and
 *  also to provide a registration interface between the \c IPlugin and the application.
 */
class IPlugin
{
public:
    /**
     *  \brief Default destructor.
     */
    virtual ~IPlugin() {}

    /**
     *  \brief Plug this plugin to the application.
     *
     *  \param pluginWorkinPath represents the path which this plugin are able to work.
     *  If this plugin needs to create or access some file, it should be done inside this path.
     *
     *  \return Returns 0 if success, otherwise returns a negative number.
     */
    virtual int plugin(const std::string &pluginWorkingPath) = 0;

    /**
     *  \brief Gets the plugin name.
     *
     *  The plugin name should be unique and universal. A reverse domain works fine.
     *
     *  \return return a string containing the name of the plugin.
     */
    virtual std::string  pluginName() const = 0;

    /**
     *  \brief Gets the plugin unique ID.
     *
     *  The ID should be unique. Reverse domain is recomended.
     *
     *  \return A unique plugin ID.
     */
    virtual std::string pluginId() const = 0;

    /**
     *  \brief Gets the plugin version.
     *
     *  \return The version of the plugin.
     */
    virtual int pluginVersion() const = 0;

    /**
     *  \brief Gets the plugin proxy id.
     *
     *  If the given proxy ID is not registered, the plugin will not be loaded.
     *
     *  \return Returns a string representing the proxy ID.
     */
    virtual std::string proxyId() const = 0;
};

#endif
