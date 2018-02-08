#ifndef PLUGIN_H
#define PLUGIN_H

#include <string>

#include "plugindefinitions.h"

/**
 *  \brief Class IPlugin
 *
 *  The \c IPlugin interface is the base class for all the plugins. It's the plugin object which can be created or used
 *  anytime. For it's usage, a \c IPluginProxy should be created to cast this \c IPlugin object to the desired
 *  type and provide a registration interface to the application.
 *
 *  TODO:
 *  doc
 *
 */
class IPlugin
{
    public:
        /**
         *  \brief Default destructor.
         *
         *  Called anytime. Make sure to cleanup everything here.
         */
         virtual ~IPlugin() = 0;

        /**
         *  \brief Plug this plugin to the application.
         */
         virtual void plugin() = 0;

        /**
         *  \brief Gets the plugin name.
         *
         *  The plugin name should be unique and universal. A reverse domain works fine.
         *
         *  \return return a string containing the name of the plugin.
         */
         virtual std::string  pluginName() = 0;
};

#endif
