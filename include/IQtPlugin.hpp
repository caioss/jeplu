#ifndef IQTPLUGIN_HPP
#define IQTPLUGIN_HPP

#include "IPlugin.hpp"
#include <QObject>

/**
 *  This is necessary for those plugins that will be loaded by the default loader `QtLoader`.
 *  In case that the user (developer) wants to develops a new solution for the loader, this is no longer
 *  necessary and another solution should be created for loading the \c IPlugin object from a dynamic
 *  library using the new \c IPluginLoader.
 *
 *  \sa IPlugin \sa Jeplu \sa QtLoader
 */
Q_DECLARE_INTERFACE(IPlugin, "jeplu.interfaces.iplugin")

#endif // IQTPLUGIN_HPP
