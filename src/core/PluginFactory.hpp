#ifndef PLUGINFACTORY_H
#define PLUGINFACTORY_H

#include <memory>

#include "IPluginFactory.hpp"
#include "IPluginLoader.hpp"

/**
 *  \brief The \c PluginFactory implements the interface \c IPluginFactory.
 *
 *  \sa IPluginFactory
 */
class PluginFactory : public IPluginFactory
{
private:
    /**
     *  \brief _plugins Holds all \c IPlugin references createdd by \c createPlugins().
     */
    std::vector<std::shared_ptr<IPlugin>> _plugins;

    /**
     *  \brief _loaders Holds all loaders registered by \c registerLoader().
     */
    std::vector<std::shared_ptr<IPluginLoader>> _loaders;

public:
    /**
     *  \brief Default constructor.
     */
    PluginFactory();

    int createPlugins(const std::vector<std::string> &pluginsPaths) override;

    std::vector<std::shared_ptr<IPlugin>> getPlugins() const override;

    bool registerLoader(std::shared_ptr<IPluginLoader> loader) override;

//    template <typename T> int getPluginsWithInterface(QList<std::weak_ptr<T>> &plugins) {} //TODO

//    template <typename T> std::vector<std::string> getPluginsID() const {} //TODO
};

#endif
