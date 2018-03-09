#ifndef IPLUGINPROXY_HPP
#define IPLUGINPROXY_HPP

#include "IPlugin.hpp"

#include <memory>
#include <vector>
#include <string>

/**
 *  The \c IPluginProxy interface must be used for converting \c IPlugin objects to an especific type that the only the
 *  proxy and the plugin knows.
 *
 *  It's used for extending any functionality for any kind of application. Each implementation of this interface may
 *  provide an interface so any \c IPlugin object can inherit. That way, after the plugin registration, each \c IPlugin
 *  object will be linked to its \c IPluginProxy, becoming easy to find and cast to the custom type.
 */
class IPluginProxy {
public:
    /**
     *  \brief Initializes this proxy with the given \c IPlugin objects.
     *
     *  \param plugins A vector containing all compatible \c IPlugin references.
     *  \return Returns \c true if initialized. Otherwise, returns \c false.
     */
    virtual bool init(std::vector<std::weak_ptr<IPlugin>> plugins = std::vector<std::weak_ptr<IPlugin>>()) = 0;

    /**
     *  \brief Gets the unique proxy ID.
     *
     *  \return Returns a unique ID representing this \c IPluginProxy.
     */
    virtual std::string proxyId() const = 0;

    /**
     *  \brief Indicates if this proxy is initialized.
     *
     *  \return Returns \c true if this proxy is initialized. \c False otherwise.
     */
    virtual bool initialized() const = 0;

    /**
     *  \brief Gets all \c IPlugin references compatible with this proxy.
     *
     *  \return Returns a vector containing weak references of \c IPlugin objects.
     */
    virtual std::vector<std::weak_ptr<IPlugin>> plugins() const = 0;

    /**
     *  \brief Adds the \c plugin reference to this proxy.
     *
     *  If the \c plugin is not compatible with this \c IPluginProxy, the plugin is not added.
     *
     *  \param plugin A weak reference to the \c IPlugin object.
     *  \return Returns \c true if the plugin is compatible and could be added to this proxy. Otherwise, returns
     *  \c false.
     */
    virtual bool addPlugin(std::weak_ptr<IPlugin> plugin) = 0;
};

#endif
